#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "objects.h"

void free_object(object_t *obj) {
    if (obj == NULL) {
        return;
    }
    switch (obj->type) {
        case INT:
        case FLOAT:
            break;
        case STRING:
            free(obj->value.v_string);
            break;
        default:
            break;
    }
    free(obj);
}

object_t *_new_object() {
    object_t *obj = calloc(1, sizeof(object_t));
    if (obj == NULL) {
        return NULL;
    }
    return obj;
}

object_t *new_integer(int value) {
    object_t *obj = _new_object();
    if (obj == NULL) {
        return NULL;
    }
    obj->type = INT;
    obj->value.v_int = value;
    return obj;
}

object_t *new_float(float value) {
    object_t *obj = _new_object();
    if (obj == NULL) {
        return NULL;
    }
    obj->type = FLOAT;
    obj->value.v_float = value;
    return obj;
}

object_t *new_string(char *value) {
    object_t *obj = _new_object();
    if (obj == NULL) {
        return NULL;
    }
    obj->type = STRING;
    char *buffer = malloc(sizeof(value));
    strcat(buffer, value);
    obj->value.v_string = buffer;
    return obj;
}

char *represent_object(object_t obj[]) {
    if (obj == NULL) {
        return "";
    }

    char *buffer = malloc(64);
    if (buffer == NULL) {
        return NULL;
    }

    switch (obj->type) {
        case INT:
          sprintf(buffer, "%d", obj->value.v_int);
          break;
        case FLOAT:
          sprintf(buffer, "%.2f", obj->value.v_float);
          break;
        case STRING:
          sprintf(buffer, "%s", obj->value.v_string);
          break;
        default:
          break;
    }
    //printf("repr: %s", buffer);
    return buffer;
}
