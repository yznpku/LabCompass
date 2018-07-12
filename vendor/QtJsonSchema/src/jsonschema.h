#ifndef JSONSCHEMA_H
#define JSONSCHEMA_H

#include <QtCore>
#include "jsonschemaversion.h"

class JsonSchemaPrivate;
class JsonSchema
{

public:
  JsonSchema(const JsonSchema& other) noexcept;
  JsonSchema(JsonSchema&& other) noexcept
    : d(other.d) { other.d = nullptr; }
  JsonSchema& operator=(const JsonSchema& other) noexcept;
  JsonSchema& operator=(JsonSchema&& other) noexcept
    { swap(other); return *this; }
  void swap(JsonSchema& other) noexcept
    { qSwap(d, other.d); }
  ~JsonSchema();

  static JsonSchema fromJson(const QJsonValue& json, JsonSchemaVersion::Version version = JsonSchemaVersion::Draft07);
  static JsonSchema fromVariant(const QVariant& variant, JsonSchemaVersion::Version version = JsonSchemaVersion::Draft07);
  static JsonSchema fromJsonDocument(const QJsonDocument& document, JsonSchemaVersion::Version version = JsonSchemaVersion::Draft07);
  static JsonSchema fromJsonString(const QByteArray& json, JsonSchemaVersion::Version version = JsonSchemaVersion::Draft07);
  static JsonSchema metaSchema(JsonSchemaVersion::Version version);

public:
  bool validate(const QJsonValue& instance) const;
  bool validate(const QVariant& instance) const;
  bool validate(const QJsonDocument& instance) const;
  bool validate(const QByteArray& instance) const;
  bool isValid() const;

protected:
  JsonSchema(JsonSchemaVersion::Version version);
  JsonSchemaPrivate* d;
};

#endif // JSONSCHEMA_H
