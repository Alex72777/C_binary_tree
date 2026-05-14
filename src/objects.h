#pragma once

typedef enum ObjectType {
    INT,
    FLOAT,
    STRING
} object_type_t;

typedef union Value {
    int v_int;
    float v_float;
    char *v_string;
} value_t;

typedef struct Object {
    value_t value;
    object_type_t type;
} object_t;

void free_object(object_t *object);
char *represent_object(object_t *obj);

object_t *_new_object();
object_t *new_integer(int value);
object_t *new_float(float value);
object_t *new_string(char *value);
