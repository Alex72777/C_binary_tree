#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
#include "objects.h"

node_t *new_node(object_t *object) {
    if (object == NULL) {
        return NULL;
    }

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        return NULL;
    }
    node->value = object;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void free_node(node_t *node) {
    /*
     * Recursively frees nodes in a post-fix process
     */
    if (node == NULL) {
        return;
    }
    free_node(node->left);
    free_node(node->right);
    free_object(node->value);
    free(node);
}

void prefix_represent_node(node_t *node, char *output) {
    if (node == NULL) {
        strcat(output, "None");
        return;
    }

    char *val = represent_object(node->value);
    strcat(output, "[");
    strcat(output, val);
    free(val);
    strcat(output, ", ");
    prefix_represent_node(node->left, output);
    strcat(output, ", ");
    prefix_represent_node(node->right, output);
    strcat(output, "]");
}

void infix_represent_node(node_t *node, char *output) {
    if (node == NULL) {
        strcat(output, "None");
        return;
    }

    strcat(output, "[");
    prefix_represent_node(node->left, output);

    strcat(output, ", ");
    char *val = represent_object(node->value);
    strcat(output, val);
    free(val);
    strcat(output, ", ");

    prefix_represent_node(node->right, output);
    strcat(output, "]");
}

void postfix_represent_node(node_t *node, char *output) {
    if (node == NULL) {
        strcat(output, "None");
        return;
    }

    strcat(output, "[");
    prefix_represent_node(node->left, output);

    strcat(output, ", ");
    prefix_represent_node(node->right, output);
    strcat(output, ", ");

    char *val = represent_object(node->value);
    strcat(output, val);
    free(val);
    strcat(output, "]");
}

void set_left_node(node_t *root, node_t *left) {
    if (root == NULL || left == NULL) {
        return;
    }

    root->left = left;
}

void set_right_node(node_t *root, node_t *right) {
    if (root == NULL || right == NULL) {
        return;
    }

    root->right = right;
}
