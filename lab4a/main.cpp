#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 

#include <stdio.h>
#include "tree.h"
#include "for_all.h"



int main() {
    Tree* tree = NULL;
    tree = new_tree(tree);
    dialog(tree);
    printf("That's all. Bye!\n");
    delete_tree(tree);
    _CrtDumpMemoryLeaks();
    return 0;
}