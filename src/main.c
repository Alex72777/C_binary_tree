#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "objects.h"

void manual_binary_trees(void) {
    object_t *num1 = new_integer(3);
    object_t *num2 = new_integer(1);
    object_t *num3 = new_float(5.12);
    object_t *num4 = new_string("hi");
    //object_t *num5 = new_integer(4);
    //object_t *num6 = new_float(4.5);
    //printf("declared nums\n");

    node_t *root = new_node(num1);
    node_t *sag = new_node(num2);
    node_t *sad = new_node(num3);
    node_t *ssag = new_node(num4);
    //node_t *ssag2 = new_node(num5);
    //node_t *sssad = new_node(num6);
    //printf("declared nodes\n");

    set_left_node(root, sag);
    set_right_node(root, sad);
    set_left_node(sag, ssag);
    //set_left_node(sad, ssag2);
    //set_right_node(ssag2, sssad);
    //printf("assigned sub nodes\n");

    char *buffer = calloc(1024, sizeof(char));
    if (buffer == NULL) {
        printf("Couldn't allocate mem for buffer.\n");
        return;
    }
    prefix_represent_node(root, buffer);
    printf("Prefix: %s\n", buffer);
    buffer[0] = '\0';

    infix_represent_node(root, buffer);
    printf("Infix: %s\n", buffer);
    buffer[0] = '\0';

    postfix_represent_node(root, buffer);
    printf("Postfix: %s\n", buffer);

    free(buffer);
    free_node(root);
}

int main() {
    //printf("Hello, World!\n");
    manual_binary_trees();
    return 0;
}
