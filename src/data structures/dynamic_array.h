#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Dynamic_Array {
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
};

void init_dynamic_array(Dynamic_Array *arr, size_t element_size) {

}


#endif