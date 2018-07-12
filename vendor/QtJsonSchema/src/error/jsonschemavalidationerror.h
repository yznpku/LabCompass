#ifndef JSONSCHEMAVALIDATIONERROR_H
#define JSONSCHEMAVALIDATIONERROR_H

#include <QtCore>
#include "../pointer/jsonpointer.h"

class JsonSchemaValidationError
{
  JsonPointer schemaPtr;
  JsonPointer instancePtr;
  QString error;

public:
  JsonSchemaValidationError(const JsonPointer& schemaPtr, const JsonPointer& instancePtr, const QString& error = QString());

  QString toString() const;
};

QDebug operator<<(QDebug debug, const JsonSchemaValidationError& o);

#endif // JSONSCHEMAVALIDATIONERROR_H
