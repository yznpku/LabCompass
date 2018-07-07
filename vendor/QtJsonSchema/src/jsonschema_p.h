#ifndef JSONSCHEMA_P_H
#define JSONSCHEMA_P_H

#include "jsonschema.h"
#include <memory>
#include "validator/jsonschemanodevalidator.h"

class JsonSchemaPrivate
{
public:
  QAtomicInt ref;

  JsonSchemaVersion::Version version;
  std::unique_ptr<JsonSchemaNodeValidator> validator;
  bool validAgainstMetaSchema {true};

public:
  JsonSchemaPrivate(JsonSchemaVersion::Version version);

  void setSchema(const QJsonValue& schema);
};

#endif // JSONSCHEMA_P_H
