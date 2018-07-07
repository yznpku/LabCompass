#ifndef JSONSCHEMANODEVALIDATOR_H
#define JSONSCHEMANODEVALIDATOR_H

#include <QtCore>
#include <memory>
#include "../jsonschemaversion.h"
#include "../pointer/jsonpointer.h"
#include "../reference-resolver/referenceresolver.h"
#include "../error/jsonschemavalidationerror.h"

class JsonSchemaNodeValidator
{
protected:
  QJsonValue schemaRoot;

  std::unique_ptr<ReferenceResolver> referenceResolver;

public:
  virtual ~JsonSchemaNodeValidator() {}
  static JsonSchemaNodeValidator* getValidator(JsonSchemaVersion::Version version);

  void setSchema(const QJsonValue& schema);
  bool isValid() const;
  virtual QList<JsonSchemaValidationError> validate(const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> validateNode(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);

protected:
  JsonSchemaNodeValidator() {}

  virtual QList<JsonSchemaValidationError> typeClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> enumClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> constClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);

  virtual QList<JsonSchemaValidationError> multipleOfClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> maximumClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> exclusiveMaximumClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> minimumClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> exclusiveMinimumClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);

  virtual QList<JsonSchemaValidationError> maxLengthClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> minLengthClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> patternClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);

  virtual QList<JsonSchemaValidationError> itemsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> additionalItemsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> maxItemsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> minItemsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> uniqueItemsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> containsClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);

  virtual QList<JsonSchemaValidationError> maxPropertiesClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> minPropertiesClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> requiredClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> propertiesClauseGroup(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> dependenciesClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> propertyNamesClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);

  virtual QList<JsonSchemaValidationError> conditionalClauseGroup(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);

  virtual QList<JsonSchemaValidationError> allOfClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> anyOfClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> oneOfClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
  virtual QList<JsonSchemaValidationError> notClause(const JsonPointer& schemaPtr, const JsonPointer& instancePtr);
};

#endif // JSONSCHEMANODEVALIDATOR_H
