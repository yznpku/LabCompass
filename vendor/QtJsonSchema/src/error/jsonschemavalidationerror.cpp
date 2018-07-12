#include "jsonschemavalidationerror.h"

JsonSchemaValidationError::JsonSchemaValidationError(const JsonPointer& schemaPtr, const JsonPointer& instancePtr, const QString& error)
{
  this->schemaPtr = schemaPtr;
  this->instancePtr = instancePtr;
  this->error = error;
}

QString JsonSchemaValidationError::toString() const
{
  return "#" + schemaPtr.path.join('/') + " => #" + instancePtr.path.join('/') + ": " + error;
}

QDebug operator<<(QDebug debug, const JsonSchemaValidationError& o)
{
  QDebugStateSaver saver(debug);
  debug << o.toString();
  return debug;
}
