#include "variant_list.h"
#include <stdio.h>

#define TRY(...) do \
{ \
    if(!(__VA_ARGS__)) \
    { \
        fprintf(stderr, "Statement failed: " #__VA_ARGS__ "\n"); \
        return 1; \
    } \
} while(0)


const char* DType_ToString(DType dt)
{
    switch(dt)
    {
        case DT_INTEGER: return "DT_INTEGER";
        case DT_BOOLEAN: return "DT_BOOLEAN";
        case DT_FLOAT:   return "DT_FLOAT";
        case DT_STRING:  return "DT_STRING";
        case DT_NONE:    return "DT_NONE";
    }
}


int main()
{
    char buffer[1024];

    VariantList* list = VariantList_Create();
    TRY(list);

    TRY(VariantList_MultiPush(list,
        DT_FLOAT,   3.141f,
        DT_INTEGER, 42,
        DT_BOOLEAN, true,
        DT_STRING,  "Hello World",
        DT_NONE
    ));

    int fortytwo;
    TRY(VariantList_Get(list, 1, DT_INTEGER, &fortytwo) == DT_INTEGER);
    printf("list[1] = %i\n", fortytwo);

    DType dt = VariantList_Get(list, 3, DT_NONE, NULL);
    printf("type(list[3]) = %s\n", DType_ToString(dt));

    TRY(VariantList_ToString(list, buffer, sizeof(buffer)));
    printf("list = %s\n", buffer);

    TRY(VariantList_ManyPush(list,
        DT_BOOLEAN, false,
        DT_FLOAT,   1.5f,
        DT_STRING,  "int main() { return 42; }",
        DT_INTEGER, 12345
    ));

    TRY(VariantList_ToString(list, buffer, sizeof(buffer)));
    printf("list = %s\n", buffer);

    VariantList_Destroy(list);
}
