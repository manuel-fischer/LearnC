#include "variant_list.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>


struct VariantList
{
    // TODO
};


VariantList* VariantList_Create(void)
{
    // TODO
}

void VariantList_Destroy(VariantList* list)
{
    // TODO
}

bool VariantList_IsEmpty(VariantList* list)
{
    // TODO
}

size_t VariantList_GetSize(VariantList* list)
{
    // TODO
}

bool VariantList_MultiPush(VariantList* list, ...)
{
    // TODO
}


DType VariantList_Get(VariantList* list, size_t index, DType dtype, void* dst)
{
    // TODO
}


bool VariantList_ToString(VariantList* list, char* buffer, size_t buffer_size)
{
    // TODO
}
