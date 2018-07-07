#include "jsonschemanodevalidator07.h"
#include "../reference-resolver/referenceresolver.h"

JsonSchemaNodeValidator07::JsonSchemaNodeValidator07()
{
  referenceResolver.reset(new ReferenceResolver());
}
