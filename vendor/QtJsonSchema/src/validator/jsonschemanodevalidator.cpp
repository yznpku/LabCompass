#include "jsonschemanodevalidator.h"
#include "../hashfunctions.h"
#include <cmath>
#include "jsonschemanodevalidator07.h"

JsonSchemaNodeValidator* JsonSchemaNodeValidator::getValidator(JsonSchemaVersion::Version version)
{
  return new JsonSchemaNodeValidator07();
}

void JsonSchemaNodeValidator::setSchema(const QJsonValue& schema)
{
  this->schemaRoot = schema;
  referenceResolver->parseSchema(schemaRoot);
}

bool JsonSchemaNodeValidator::isValid() const
{
  return !schemaRoot.isNull() && referenceResolver->isValid();
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::validate(const JsonPointer& instancePtr)
{
  return validateNode(JsonPointer(schemaRoot), instancePtr);
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::validateNode(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schema = schemaPtr.v;

  if (schema.isBool()) {
    if (schema.toBool())
      return {};
    else
      return {{ schemaPtr, instancePtr, "schema is false" }};
  }

  const auto& o = schema.toObject();
  QList<JsonSchemaValidationError> errors;

  if (o.contains("$ref")) {
    const auto& reference = referenceResolver->resolve(schemaPtr);
    return validateNode(reference, instancePtr);
  }

  if (o.contains("type"))
    errors.append(typeClause(schemaPtr, instancePtr));

  if (o.contains("enum"))
    errors.append(enumClause(schemaPtr, instancePtr));

  if (o.contains("const"))
    errors.append(constClause(schemaPtr, instancePtr));

  if (instancePtr.v.isDouble()) {
    if (o.contains("multipleOf"))
      errors.append(multipleOfClause(schemaPtr, instancePtr));

    if (o.contains("maximum"))
      errors.append(maximumClause(schemaPtr, instancePtr));

    if (o.contains("exclusiveMaximum"))
      errors.append(exclusiveMaximumClause(schemaPtr, instancePtr));

    if (o.contains("minimum"))
      errors.append(minimumClause(schemaPtr, instancePtr));

    if (o.contains("exclusiveMinimum"))
      errors.append(exclusiveMinimumClause(schemaPtr, instancePtr));
  }

  else if (instancePtr.v.isString()) {
    if (o.contains("maxLength"))
      errors.append(maxLengthClause(schemaPtr, instancePtr));

    if (o.contains("minLength"))
      errors.append(minLengthClause(schemaPtr, instancePtr));

    if (o.contains("pattern"))
      errors.append(patternClause(schemaPtr, instancePtr));
  }

  else if (instancePtr.v.isArray()) {
    if (o.contains("items"))
      errors.append(itemsClause(schemaPtr, instancePtr));

    if (o.contains("additionalItems"))
      errors.append(additionalItemsClause(schemaPtr, instancePtr));

    if (o.contains("maxItems"))
      errors.append(maxItemsClause(schemaPtr, instancePtr));

    if (o.contains("minItems"))
      errors.append(minItemsClause(schemaPtr, instancePtr));

    if (o.contains("uniqueItems"))
      errors.append(uniqueItemsClause(schemaPtr, instancePtr));

    if (o.contains("contains"))
      errors.append(containsClause(schemaPtr, instancePtr));
  }

  else if (instancePtr.v.isObject()) {
    if (o.contains("maxProperties"))
      errors.append(maxPropertiesClause(schemaPtr, instancePtr));

    if (o.contains("minProperties"))
      errors.append(minPropertiesClause(schemaPtr, instancePtr));

    if (o.contains("required"))
      errors.append(requiredClause(schemaPtr, instancePtr));

    if (o.contains("properties") || o.contains("patternProperties") || o.contains("additionalProperties"))
      errors.append(propertiesClauseGroup(schemaPtr, instancePtr));

    if (o.contains("dependencies"))
      errors.append(dependenciesClause(schemaPtr, instancePtr));

    if (o.contains("propertyNames"))
      errors.append(propertyNamesClause(schemaPtr, instancePtr));
  }

  if (o.contains("if"))
    errors.append(conditionalClauseGroup(schemaPtr, instancePtr));

  if (o.contains("allOf"))
    errors.append(allOfClause(schemaPtr, instancePtr));

  if (o.contains("anyOf"))
    errors.append(anyOfClause(schemaPtr, instancePtr));

  if (o.contains("oneOf"))
    errors.append(oneOfClause(schemaPtr, instancePtr));

  if (o.contains("not"))
    errors.append(notClause(schemaPtr, instancePtr));

  return errors;
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::typeClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  enum Type {
    TYPE_NULL = 1,
    TYPE_BOOLEAN,
    TYPE_OBJECT,
    TYPE_ARRAY,
    TYPE_NUMBER,
    TYPE_STRING,
    TYPE_INTEGER,
  };
  static QHash<QString, Type> typeHash {
    { "null", TYPE_NULL },
    { "boolean", TYPE_BOOLEAN },
    { "object", TYPE_OBJECT },
    { "array", TYPE_ARRAY },
    { "number", TYPE_NUMBER },
    { "string", TYPE_STRING },
    { "integer", TYPE_INTEGER },
  };
  bool acceptType[] = { false, false, false, false, false, false, false, false };

  const auto& schemaValue = schemaPtr.v["type"];
  const auto& instance = instancePtr.v;

  if (schemaValue.isString())
    acceptType[typeHash[schemaValue.toString()]] = true;

  else if (schemaValue.isArray()) {
    const auto& array = schemaValue.toArray();
    for (int i = 0; i < array.size(); i++)
      acceptType[typeHash[array[i].toString()]] = true;
  }

  if (acceptType[TYPE_NULL])
    if (instance.isNull())
      return {};

  if (acceptType[TYPE_BOOLEAN])
    if (instance.isBool())
      return {};

  if (acceptType[TYPE_OBJECT])
    if (instance.isObject())
      return {};

  if (acceptType[TYPE_ARRAY])
    if (instance.isArray())
      return {};

  if (acceptType[TYPE_NUMBER])
    if (instance.isDouble())
      return {};

  if (acceptType[TYPE_STRING])
    if (instance.isString())
      return {};

  if (acceptType[TYPE_INTEGER])
    if (instance.isDouble()) {
      double intpart;
      if (std::modf(instance.toDouble(), &intpart) == 0.0)
        return {};
    }

  return {{ schemaPtr, instancePtr, "type" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::enumClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["enum"];
  const auto& instance = instancePtr.v;

  if (schemaValue.toArray().contains(instance))
    return {};

  return {{ schemaPtr, instancePtr, "enum" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::constClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["const"];
  const auto& instance = instancePtr.v;

  if (schemaValue == instance)
    return {};

  return {{ schemaPtr, instancePtr, "const" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::multipleOfClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["multipleOf"].toDouble();
  const auto& instance = instancePtr.v.toDouble();

  if (std::fmod(instance, schemaValue) == 0)
    return {};

  return {{ schemaPtr, instancePtr, "multipleOf" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::maximumClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["maximum"].toDouble();
  const auto& instance = instancePtr.v.toDouble();

  if (instance <= schemaValue)
    return {};

  return {{ schemaPtr, instancePtr, "maximum" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::exclusiveMaximumClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["exclusiveMaximum"].toDouble();
  const auto& instance = instancePtr.v.toDouble();

  if (instance < schemaValue)
    return {};

  return {{ schemaPtr, instancePtr, "exclusiveMaximum" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::minimumClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["minimum"].toDouble();
  const auto& instance = instancePtr.v.toDouble();

  if (instance >= schemaValue)
    return {};

  return {{ schemaPtr, instancePtr, "minimum" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::exclusiveMinimumClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["exclusiveMinimum"].toDouble();
  const auto& instance = instancePtr.v.toDouble();

  if (instance > schemaValue)
    return {};

  return {{ schemaPtr, instancePtr, "exclusiveMinimum" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::maxLengthClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["maxLength"].toInt();
  const auto& instance = instancePtr.v.toString();

  if (instance.length() <= schemaValue)
    return {};

  return {{ schemaPtr, instancePtr, "maxLength" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::minLengthClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["minLength"].toInt();
  const auto& instance = instancePtr.v.toString();

  if (instance.length() >= schemaValue)
    return {};

  return {{ schemaPtr, instancePtr, "minLength" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::patternClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["pattern"].toString();
  const auto& instance = instancePtr.v.toString();

  auto pattern = QRegularExpression(schemaValue);
  if (pattern.match(instance).hasMatch())
    return {};

  return {{ schemaPtr, instancePtr, "pattern" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::itemsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["items"];
  const auto& instance = instancePtr.v.toArray();

  QList<JsonSchemaValidationError> errors;

  if (schemaValue.isArray()) {
    int n = std::min(schemaValue.toArray().size(), instance.size());
    for (int i = 0; i < n; i++)
      errors.append(validateNode(schemaPtr["items"][i], instancePtr[i]));

  } else {
    for (int i = 0; i < instance.size(); i++)
      errors.append(validateNode(schemaPtr["items"], instancePtr[i]));
  }

  return errors;
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::additionalItemsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& instance = instancePtr.v.toArray();

  QList<JsonSchemaValidationError> errors;

  if (!schemaPtr.v.toObject().contains("items") || schemaPtr.v["items"].isArray()) {
    int start = schemaPtr.v.toObject().contains("items") ? schemaPtr.v["items"].toArray().size() : 0;

    for (int i = start; i < instance.size(); i++)
      errors.append(validateNode(schemaPtr["additionalItems"], instancePtr[i]));
  }

  return errors;
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::maxItemsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["maxItems"].toInt();
  const auto& instance = instancePtr.v.toArray();

  if (instance.size() <= schemaValue)
    return {};

  return {{ schemaPtr, instancePtr, "maxItems" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::minItemsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["minItems"].toInt();
  const auto& instance = instancePtr.v.toArray();

  if (instance.size() >= schemaValue)
    return {};

  return {{ schemaPtr, instancePtr, "minItems" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::uniqueItemsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["uniqueItems"].toBool();
  const auto& instance = instancePtr.v.toArray();

  if (schemaValue) {
    QSet<QJsonValue> set;
    for (auto i = instance.constBegin(); i != instance.constEnd(); i++)
      set.insert(*i);

    if (set.size() == instance.size())
      return {};

    return {{ schemaPtr, instancePtr, "uniqueItems" }};
  }

  return {};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::containsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& instance = instancePtr.v.toArray();

  QList<JsonSchemaValidationError> errors;

  for (int i = 0; i < instance.size(); i++)
    if (validateNode(schemaPtr["contains"], instancePtr[i]).isEmpty())
      return {};

  return {{ schemaPtr, instancePtr, "contains" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::maxPropertiesClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["maxProperties"].toInt();
  const auto& instance = instancePtr.v.toObject();

  if (instance.size() <= schemaValue)
    return {};

  return {{ schemaPtr, instancePtr, "maxProperties" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::minPropertiesClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["minProperties"].toInt();
  const auto& instance = instancePtr.v.toObject();

  if (instance.size() >= schemaValue)
    return {};

  return {{ schemaPtr, instancePtr, "minProperties" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::requiredClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["required"].toArray();
  const auto& instance = instancePtr.v.toObject();

  QStringList missingProperties;
  for (auto i = schemaValue.constBegin(); i != schemaValue.constEnd(); i++)
    if (!instance.contains(i->toString()))
      missingProperties.append(i->toString());

  if (missingProperties.isEmpty())
    return {};

  return {{ schemaPtr, instancePtr, "required" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::propertiesClauseGroup(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schema = schemaPtr.v.toObject();
  const auto& instance = instancePtr.v.toObject();

  QList<JsonSchemaValidationError> errors;
  QSet<QString> remainingProperties;

  for (auto i = instance.constBegin(); i != instance.constEnd(); i++)
    remainingProperties.insert(i.key());

  if (schema.contains("properties")) {
    const auto& schemaValue = schemaPtr.v["properties"].toObject();
    for (auto i = remainingProperties.begin(); i != remainingProperties.end();) {
      if (schemaValue.contains(*i)) {
        errors.append(validateNode(schemaPtr["properties"][*i], instancePtr[*i]));
        i = remainingProperties.erase(i);
      } else {
        i++;
      }
    }
  }

  if (schema.contains("patternProperties")) {
    const auto& schemaValue = schemaPtr.v["patternProperties"].toObject();
    for (auto i = remainingProperties.begin(); i != remainingProperties.end();) {
      bool hasMatch = false;

      for (auto j = schemaValue.constBegin(); j != schemaValue.constEnd(); j++) {
        auto pattern = QRegularExpression(j.key());
        auto match = pattern.match(*i);
        if (match.hasMatch()) {
          errors.append(validateNode(schemaPtr["patternProperties"][j.key()], instancePtr[*i]));
          hasMatch = true;
          break;
        }
      }

      if (hasMatch)
        i = remainingProperties.erase(i);
      else
        i++;
    }
  }

  if (schema.contains("additionalProperties")) {
    for (auto i = remainingProperties.constBegin(); i != remainingProperties.constEnd(); i++)
      errors.append(validateNode(schemaPtr["additionalProperties"], instancePtr[*i]));
  }

  return errors;
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::dependenciesClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schemaValue = schemaPtr.v["dependencies"].toObject();
  const auto& instance = instancePtr.v.toObject();

  QList<JsonSchemaValidationError> errors;

  for (auto i = schemaValue.constBegin(); i != schemaValue.constEnd(); i++) {
    if (instance.contains(i.key())) {

      // property dependencies
      if (i.value().isArray()) {
        const auto& dependencies = i.value().toArray();
        for (auto j = dependencies.constBegin(); j != dependencies.constEnd(); j++)
          if (!instance.contains(j->toString()))
            errors.append({{ schemaPtr, instancePtr, "dependencies" }});
      }

      // schema dependencies
      else {
        errors.append(validateNode(schemaPtr["dependencies"][i.key()], instancePtr));
      }
    }
  }

  return errors;
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::propertyNamesClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& instance = instancePtr.v.toObject();

  QList<JsonSchemaValidationError> errors;

  for (auto i = instance.constBegin(); i != instance.constEnd(); i++) {
    auto propertyName = i.key();

    const auto& propertyErrors = validateNode(schemaPtr["propertyNames"], JsonPointer(propertyName));
    if (!propertyErrors.isEmpty())
      errors.append({{ schemaPtr, instancePtr, "propertyNames" }});
  }

  return errors;
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::conditionalClauseGroup(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  const auto& schema = schemaPtr.v.toObject();

  if (validateNode(schemaPtr["if"], instancePtr).isEmpty()) {
    if (schema.contains("then"))
      return validateNode(schemaPtr["then"], instancePtr);
  }

  else {
    if (schema.contains("else"))
      return validateNode(schemaPtr["else"], instancePtr);
  }

  return {};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::allOfClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  int n = schemaPtr.v["allOf"].toArray().size();

  for (int i = 0; i < n; i++)
    if (!validateNode(schemaPtr["allOf"][i], instancePtr).isEmpty())
      return {{ schemaPtr, instancePtr, "allOf" }};

  return {};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::anyOfClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  int n = schemaPtr.v["anyOf"].toArray().size();

  for (int i = 0; i < n; i++)
    if (validateNode(schemaPtr["anyOf"][i], instancePtr).isEmpty())
      return {};

  return {{ schemaPtr, instancePtr, "anyOf" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::oneOfClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  int n = schemaPtr.v["oneOf"].toArray().size();
  int valid = 0;

  for (int i = 0; i < n; i++)
    if (validateNode(schemaPtr["oneOf"][i], instancePtr).isEmpty())
      valid += 1;

  if (valid == 1)
    return {};

  return {{ schemaPtr, instancePtr, "oneOf" }};
}

QList<JsonSchemaValidationError> JsonSchemaNodeValidator::notClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr)
{
  if (validateNode(schemaPtr["not"], instancePtr).isEmpty())
    return {{ schemaPtr, instancePtr, "not" }};

  return {};
}
