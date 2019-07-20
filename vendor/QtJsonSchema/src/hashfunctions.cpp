#include "hashfunctions.h"
#include "pointer/jsonpointer.h"

uint qHash(const JsonPointer& ptr, uint seed)
{
  return qHash(ptr.path, seed);
}
