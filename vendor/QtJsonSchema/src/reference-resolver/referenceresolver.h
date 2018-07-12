#ifndef REFERENCERESOLVER_H
#define REFERENCERESOLVER_H

#include <QtCore>
#include "../pointer/jsonpointer.h"

class ReferenceResolver
{
protected:
  QStringList subschemaKeywordList;
  QStringList subschemaArrayKeywordList;
  QStringList subschemaObjectKeywordList;

  QUrl rootUrl;
  QHash<QUrl, JsonPointer> baseUrlCache;
  QHash<JsonPointer, JsonPointer> referenceCache;
  QList<JsonPointer> errors;

public:
  ReferenceResolver();
  virtual void parseSchema(const QJsonValue& root);
  JsonPointer resolve(const JsonPointer& ptr) const;
  bool isValid() const;

protected:
  virtual void traverseForBaseUrl(QUrl baseUrl, const JsonPointer& ptr);
  virtual void traverseForReferences(const JsonPointer& ptr);
  virtual JsonPointer resolveString(const QString& ref) const;
};

#endif // REFERENCERESOLVER_H
