#pragma once
#include <stdbool.h>    // bool
#include <stdlib.h>     // size_t

typedef struct VariantList VariantList;

typedef enum {
    DT_NONE,

    DT_INTEGER,
    DT_BOOLEAN,
    DT_FLOAT,
    DT_STRING,
} DType;

VariantList* VariantList_Create(void);
void VariantList_Destroy(VariantList* list);

bool VariantList_IsEmpty(VariantList* list);
size_t VariantList_GetSize(VariantList* list);
bool VariantList_MultiPush(VariantList* list, ...);
DType VariantList_Get(VariantList* list, size_t index, DType dtype, void* dst);
bool VariantList_ToString(VariantList* list, char* buffer, size_t buffer_size);

#define VariantList_ManyPush(list, ...) \
    VariantList_MultiPush(list, __VA_ARGS__, DT_NONE)

