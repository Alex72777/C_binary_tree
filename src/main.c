#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "objects.h"

int main() {
    //printf("Hello, World!\n");
    object_t *num1 = new_integer(3);
    object_t *num2 = new_integer(1);
    object_t *num3 = new_integer(5);
    //printf("declared nums\n");

    node_t *root = new_node(num1);
    node_t *sag = new_node(num2);
    node_t *sad = new_node(num3);
    //printf("declared nodes\n");

    set_left_node(root, sag);
    set_right_node(root, sad);
    //printf("assigned sub nodes\n");

    char *buffer = calloc(1024, sizeof(char));
    if (buffer == NULL) {
        printf("Couldn't allocate mem for buffer.\n");
        return 1;
    }
    represent_node(root, buffer);
    printf("%s\n", buffer);


    return 0;
}
