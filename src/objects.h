#pragma once
#include <stddef.h>
#include <stdbool.h>
typedef struct Node node_t;
typedef struct Object object_t;

typedef enum ObjectType {
    INT,
    FLOAT,
    STRING,
    ARRAY,
    VECTOR3,
    NODE
} object_type_t;

typedef struct ArrayObject {
    size_t size;
    object_t **elements;
} array_object_t;

typedef union Value {
    int v_int;
    float v_float;
    char *v_string;
    array_object_t v_array;
    node_t *v_node;
} value_t;

typedef struct Object {
    value_t value;
    object_type_t type;
} object_t;



void free_object(object_t *object);
char *represent_object(object_t *obj);

object_t *_new_object(void);
object_t *new_integer(int value);
object_t *new_float(float value);
object_t *new_string(char *value);
object_t *new_array(size_t size);
object_t *new_node(object_t *value);

void *get_object_val(object_t *obj);
int get_integer(object_t *obj);
float get_float(object_t *obj);
char *get_string(object_t *obj);
node_t *get_node(object_t *obj);

size_t array_length(object_t *arr);
bool array_set(object_t *arr, size_t index, object_t *value);
object_t *array_get(object_t *arr, size_t index);
