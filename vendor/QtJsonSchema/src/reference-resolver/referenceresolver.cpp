#include "referenceresolver.h"
#include "../hashfunctions.h"

ReferenceResolver::ReferenceResolver()
{
  subschemaKeywordList.append({
    "items",
    "additionalItems",
    "contains",
    "additionalProperties",
    "propertyNames",
    "if",
    "then",
    "else",
    "not",
  });
  subschemaArrayKeywordList.append({
    "items",
    "allOf",
    "anyOf",
    "oneOf",
  });
  subschemaObjectKeywordList.append({
    "properties",
    "patternProperties",
    "dependencies",
    "definitions",
  });
}

void ReferenceResolver::parseSchema(const QJsonValue& root)
{
  baseUrlCache.clear();
  referenceCache.clear();

  if (root.isObject() && root.toObject().contains("$id"))
    rootUrl = QUrl(root["$id"].toString()).resolved(QUrl()).adjusted(QUrl::NormalizePathSegments);
  else
    rootUrl = QUrl();

  traverseForBaseUrl(QUrl(), JsonPointer(root));
  traverseForReferences(JsonPointer(root));
}

JsonPointer ReferenceResolver::resolve(const JsonPointer& ptr) const
{
  return referenceCache.value(ptr, JsonPointer());
}

bool ReferenceResolver::isValid() const
{
  return errors.isEmpty();
}

void ReferenceResolver::traverseForBaseUrl(QUrl baseUrl, const JsonPointer& ptr)
{
  if (!ptr.v.isObject())
    return;

  const auto& v = ptr.v.toObject();

  if (v.contains("$id")) {
    baseUrl = baseUrl.resolved(v["$id"].toString()).adjusted(QUrl::NormalizePathSegments);
    if (baseUrl.fragment().isEmpty())
      baseUrl = baseUrl.adjusted(QUrl::RemoveFragment);

    baseUrlCache[baseUrl] = ptr;
  }

  for (const auto& property: subschemaKeywordList) {
    if (v.contains(property))
      traverseForBaseUrl(baseUrl, ptr[property]);
  }

  for (const auto& property: subschemaArrayKeywordList) {
    if (v.contains(property) && v[property].isArray()) {
      int n = v[property].toArray().size();
      for (int i = 0; i < n; i++)
        traverseForBaseUrl(baseUrl, ptr[property][i]);
    }
  }

  for (const auto& property: subschemaObjectKeywordList) {
    if (v.contains(property) && v[property].isObject()) {
      for (auto key: v[property].toObject().keys())
        traverseForBaseUrl(baseUrl, ptr[property][key]);
    }
  }
}

void ReferenceResolver::traverseForReferences(const JsonPointer& ptr)
{
  if (!ptr.v.isObject())
    return;

  const auto& v = ptr.v.toObject();

  if (v.contains("$ref")) {
    const auto& reference = resolveString(v["$ref"].toString());
    if (reference.isValid())
      referenceCache[ptr] = reference;
    else
      errors.append(ptr);
  }

  for (const auto& property: subschemaKeywordList) {
    if (v.contains(property))
      traverseForReferences(ptr[property]);
  }

  for (const auto& property: subschemaArrayKeywordList) {
    if (v.contains(property) && v[property].isArray()) {
      int n = v[property].toArray().size();
      for (int i = 0; i < n; i++)
        traverseForReferences(ptr[property][i]);
    }
  }

  for (const auto& property: subschemaObjectKeywordList) {
    if (v.contains(property) && v[property].isObject()) {
      for (auto key: v[property].toObject().keys())
        traverseForReferences(ptr[property][key]);
    }
  }
}

JsonPointer ReferenceResolver::resolveString(const QString& ref) const
{
  static const QRegularExpression regex("^([^#]*+(?:#[^\\/]+)?)(?:#?(.*+))?$");

  const auto& match = regex.match(ref);
  if (!match.hasMatch())
    return JsonPointer();

  const auto& baseUrl = rootUrl.resolved(match.captured(1)).adjusted(QUrl::NormalizePathSegments);
  if (!baseUrlCache.contains(baseUrl))
    return JsonPointer();

  const auto& basePtr = baseUrlCache[baseUrl];
  if (match.captured(2).isEmpty())
    return basePtr;
  else
    return basePtr.resolve(match.captured(2));
}
