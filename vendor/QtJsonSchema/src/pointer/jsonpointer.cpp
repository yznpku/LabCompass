#include "jsonpointer.h"

JsonPointer::JsonPointer(const QJsonValue& root)
{
  this->root = root;
  this->v = root;
}

JsonPointer::JsonPointer(const QJsonValue& root, const QJsonValue& v, const QStringList& path)
{
  this->root = root;
  this->v = v;
  this->path = path;
}

JsonPointer JsonPointer::operator[](const QString& key) const
{
  if (v.isObject() && v.toObject().contains(key))
    return JsonPointer(root, v[key], path + QStringList {key});

  return JsonPointer();
}

JsonPointer JsonPointer::operator[](int index) const
{
  if (index >= 0 && v.isArray() && index < v.toArray().size())
    return JsonPointer(root, v[index], path + QStringList {QString::number(index)});

  return JsonPointer();
}

bool JsonPointer::operator==(const JsonPointer& o) const
{
  return path == o.path && root == o.root && v == o.v;
}

JsonPointer JsonPointer::resolve(const QString& str) const
{
  auto parts = str.split('/');
  parts.pop_front();

  QJsonValue v = this->v;

  for (const auto& part: parts) {
    if (v.isArray()) {
      bool isNumber;
      int index = part.toInt(&isNumber);
      if (isNumber && index >= 0 && index < v.toArray().size())
        v = v[index];
      else
        return JsonPointer();

    } else if (v.isObject()) {
      if (v.toObject().contains(part))
        v = v[part];
      else
        return JsonPointer();

    } else {
      return JsonPointer();
    }
  }

  return JsonPointer(root, v, path + parts);
}

bool JsonPointer::isValid() const
{
  return !root.isNull();
}

QString JsonPointer::toString() const
{
  if (isValid())
    return "#/" + path.join('/');
  else
    return "(Invalid)";
}

QDebug operator<<(QDebug debug, const JsonPointer& o)
{
  QDebugStateSaver saver(debug);
  debug << o.toString();
  return debug;
}
