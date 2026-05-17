#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "objects.h"
#include "binary_tree.h"

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
        case ARRAY: {
            for (size_t i = 0; i < obj->value.v_array.size; i++) {
                free_object(obj->value.v_array.elements[i]);
            }
            free(obj->value.v_array.elements);
            break;
        }
        case NODE:
            free_node(obj->value.v_node);
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

object_t *new_node(object_t *root) {
    if (root == NULL) {
        return NULL;
    }

    object_t *obj = malloc(sizeof(object_t));
    if (obj == NULL) {
        return NULL;
    }

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        free(obj);
        return NULL;
    }

    node->value = root;
    node->left = NULL;
    node->right = NULL;
    obj->type = NODE;
    obj->value.v_node = node;

    return obj;
}

object_t *new_array(size_t size) {
    object_t *obj = malloc(sizeof(object_t));
    if (obj == NULL) {
        return NULL;
    }

    object_t **elements = calloc(size, sizeof(object_t *));
    if (elements == NULL) {
        free(obj);
        return NULL;
    }

    obj->type = ARRAY;
    obj->value.v_array = (array_object_t){.size = size, .elements = elements};
    //printf("help\n");

    return obj;
}

bool array_set(object_t *arr, size_t index, object_t *value) {
    if (arr == NULL || value == NULL) {
        return false;
    }

    if (arr->type != ARRAY) {
        return false;
    }

    if (index >= arr->value.v_array.size) {
        return false;
    }

    arr->value.v_array.elements[index] = value;
    return true;
}

object_t *array_get(object_t *arr, size_t index) {
    if (arr == NULL) {
        return NULL;
    }

    if (arr->type != ARRAY) {
        return NULL;
    }

    if (index >= arr->value.v_array.size) {
        return NULL;
    }

    object_t *obj = arr->value.v_array.elements[index];
    return obj;
}

void *get_object_val(object_t *obj) {
    if (obj == NULL) {
        return NULL;
    }

    switch (obj->type) {
        case INT:
            return (void *) &obj->value.v_int;
        case FLOAT:
            return (void *) &obj->value.v_float;
        case STRING:
            return (void *) obj->value.v_string;
        case NODE:
            return (void *) &obj->value.v_node;
        case ARRAY:
            return (void *) &obj->value.v_array;
        default:
            return NULL;
    }
}

int *get_integer(object_t *obj) {
    if (obj == NULL) {
        return NULL;
    }

    switch (obj->type) {
        case INT:
            return &obj->value.v_int;
        case FLOAT:
            return (int *) &obj->value.v_float;
        default:
            return NULL;
    }
}

float *get_float(object_t *obj) {
    if (obj == NULL) {
        return NULL;
    }

    switch (obj->type) {
        case INT:
            return (float *) &obj->value.v_int;
        case FLOAT:
            return &obj->value.v_float;
        default:
            return NULL;
    }
}

char *represent_object(object_t *obj) {
    if (obj == NULL) {
        return NULL;
    }

    char *buffer = calloc(1024, sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

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
        case ARRAY: {
            strcat(buffer, "[");
            for (size_t i = 0; i < obj->value.v_array.size; i++) {
                char *repr = represent_object(obj->value.v_array.elements[i]);
                if (repr != NULL) {
                    strcat(buffer, repr);
                    free(repr);
                }

                if (i != obj->value.v_array.size - 1) {
                    strcat(buffer, ", ");
                }
            }
            strcat(buffer, "]");
            break;
        }
        case NODE:{
            prefix_represent_node(obj->value.v_node, buffer);
            break;
            /*if (obj->value.v_node->repr_method == PREFIX) {
                prefix_represent_node(obj->value.v_node, buffer);
            } else if (obj->value.v_node->repr_method == INFIX) {
                infix_represent_node(obj->value.v_node, buffer);
            } else {
                postfix_represent_node(obj->value.v_node, buffer);
                }*/
        }
        default:
          break;
    }
    //printf("repr: %s", buffer);
    return buffer;
}
