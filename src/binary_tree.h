#pragma once
#include "objects.h"

typedef struct Node node_t;

typedef enum NodeReprMethod {
    PREFIX,
    INFIX,
    POSTFIX
} node_repr_method_t;

typedef struct Node {
    object_t *value;
    node_t *left;
    node_t *right;
} node_t;

node_t *get_node(object_t *obj);
void set_left_node(node_t *root, node_t *left);
void set_right_node(node_t *root, node_t *right);
void free_node(node_t *node);
void prefix_represent_node(node_t *node, char *output);
void infix_represent_node(node_t *node, char *output);
void postfix_represent_node(node_t *node, char *output);
void append_node(node_t *node);
