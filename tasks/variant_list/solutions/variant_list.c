#include "variant_list.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>


struct VariantElement
{
    DType dtype;
    union
    {
        int   integer;
        bool  boolean;
        float real;
        char* string;
    };
};

struct VariantList
{
    struct VariantElement* contents;
    size_t size, capacity;
};


VariantList* VariantList_Create(void)
{
    return calloc(1, sizeof(VariantList)); // size = 0
}

void VariantList_Destroy(VariantList* list)
{
    for(size_t i = 0; i < list->size; ++i)
    {
        if(list->contents[i].dtype == DT_STRING)
        {
            free(list->contents[i].string);
        }
    }
    free(list->contents);
    free(list);
}

bool VariantList_IsEmpty(VariantList* list)
{
    return list->size == 0;
}

size_t VariantList_GetSize(VariantList* list)
{
    return list->size;
}

bool VariantList_MultiPush(VariantList* list, ...)
{
    va_list args;
    va_start(args, list);
    DType dt;
    while((dt = va_arg(args, DType)) != DT_NONE)
    {
        if(list->size == list->capacity)
        {
            size_t new_cap = list->capacity*2;
            if(new_cap == 0)
                new_cap = 1;

            if(new_cap*sizeof(struct VariantElement)/sizeof(struct VariantElement) != new_cap)
                return false; // overflow

            void* new_mem = realloc(list->contents, new_cap*sizeof(struct VariantElement));
            if(new_mem == NULL)
                return false; // out of memory

            list->capacity = new_cap;
            list->contents = new_mem;
        }

        switch(dt)
        {
            case DT_INTEGER:
            {
                list->contents[list->size++] = (struct VariantElement){
                    .dtype = DT_INTEGER,
                    .integer = va_arg(args, int),
                };
                break;
            }

            case DT_BOOLEAN:
            {
                list->contents[list->size++] = (struct VariantElement){
                    .dtype = DT_BOOLEAN,
                    .boolean = (bool)va_arg(args, int), // bool promoted to int
                };
                break;
            }

            case DT_FLOAT:
            {
                list->contents[list->size++] = (struct VariantElement){
                    .dtype = DT_FLOAT,
                    .real = (float)va_arg(args, double), // float promoted to double
                };
                break;
            }

            case DT_STRING:
            {
                char* str = va_arg(args, char*);
                char* new_str = malloc(strlen(str) + 1);
                if(new_str == NULL)
                    return NULL; // out of memory
                strcpy(new_str, str);

                list->contents[list->size++] = (struct VariantElement){
                    .dtype = DT_STRING,
                    .string = new_str,
                };
                break;
            }
        }
    }
    va_end(args);
    return true;
}


DType VariantList_Get(VariantList* list, size_t index, DType dtype, void* dst)
{
    if(list->contents[index].dtype != dtype)
        return list->contents[index].dtype; // type mismatch

    switch(dtype)
    {
        case DT_INTEGER:
            *(int*)dst = list->contents[index].integer;
            break;

        case DT_BOOLEAN:
            *(bool*)dst = list->contents[index].boolean;
            break;

        case DT_FLOAT:
            *(float*)dst = list->contents[index].real;
            break;

        case DT_STRING:
            *(char**)dst = list->contents[index].string;
            break;
    }
    return dtype;
}


bool VariantList_ToString(VariantList* list, char* buffer, size_t buffer_size)
{
    int written;
    written = snprintf(buffer, buffer_size, "[");
    if(written >= buffer_size) return false;
    buffer += written;
    buffer_size -= written;

    bool first = true;
    for(size_t i = 0; i < list->size; ++i)
    {
        if(!first) 
        {
            written = snprintf(buffer, buffer_size, ", ");
            if(written >= buffer_size) return false;
            buffer += written;
            buffer_size -= written;
        }
        else
        {
            first = false;
        }

        switch(list->contents[i].dtype)
        {
            case DT_INTEGER:
                written = snprintf(buffer, buffer_size, "%i", list->contents[i].integer);
                if(written >= buffer_size) return false;
                buffer += written;
                buffer_size -= written;
                break;
                
            case DT_BOOLEAN:
                written = snprintf(buffer, buffer_size, "%s", 
                    (list->contents[i].boolean) ? "true" : "false");
                if(written >= buffer_size) return false;
                buffer += written;
                buffer_size -= written;
                break;

            case DT_FLOAT:
                written = snprintf(buffer, buffer_size, "%g", list->contents[i].real);
                if(written >= buffer_size) return false;
                buffer += written;
                buffer_size -= written;
                break;

            case DT_STRING:
                written = snprintf(buffer, buffer_size, "\"%s\"", list->contents[i].string);
                if(written >= buffer_size) return false;
                buffer += written;
                buffer_size -= written;
                break;
        }
    }

    written = snprintf(buffer, buffer_size, "]");
    if(written >= buffer_size) return false;
    //buffer += written;
    //buffer_size -= written;

    return true;
}
