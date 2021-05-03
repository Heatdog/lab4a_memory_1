

#include <stdio.h>
#include "tree.h"
#include "for_all.h"



int main() {
    Tree* tree = NULL;
    tree = new_tree(tree);
    dialog(tree);
    printf("That's all. Bye!\n");
    delete_tree(tree);
    return 0;
}
