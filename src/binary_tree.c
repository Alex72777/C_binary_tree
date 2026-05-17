#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
#include "objects.h"

void free_node(node_t *node) {
    /*
     * Recursively frees nodes
     */
    if (node == NULL) {
        return;
    }
    free_node(node->left);
    free_node(node->right);
    free_object(node->value);
    free(node);
}

node_t *get_node(object_t *obj) {
    if (obj == NULL) {
        return NULL;
    }

    if (obj->type != NODE) {
        return NULL;
    }

    return obj->value.v_node;
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

void append_node(node_t *root, node_t *node) {
    if (root == NULL || node == NULL) {
        return;
    }
    object_t *object_root = root->value;
    object_t *object_node = node->value;

    void *val_root = get_object_val(object_root);
    void *val_node = get_object_val(object_node);

    if (object_root->type == INT) {
        if (object_node->type == INT) {
            int val_r = *(int *) val_root;
            int val_n = *(int *) val_node;

            if (val_n < val_r && root->left != NULL) {
                append_node(root->left, node);
            } else if (val_n > val_r && root->right != NULL) {
                append_node(root->right, node);
            } else if (val_n < val_r && root->left == NULL) {
                root->left = node;
            } else {
                root->right = node;
            }
        } else if (object_node->type == FLOAT) {
            return;
        }
    } else if (object_root->type == FLOAT) {
        if (object_node->type == INT) {
            return;
        } else if (object_node->type == FLOAT) {
            return;
        }
    }

}
