#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <crtdbg.h> 


#include <stdio.h>
#include "for_all.h"
#include <string.h>

const char* msgs[] = { "0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show" };
const int N = sizeof(msgs) / sizeof(msgs[0]);

void dialog(Tree* tree)
{
    int rc = 0;
    while (1) {
        printf("\n-------------------\n");
        for (int i = 0; i < N; i++) {
            puts(msgs[i]);
        }
        puts("Make your choice: --> ");
        scan_int(&rc);
        if (rc == 0) {
            rc = -1;
            break;
        }
        else if (rc == 1) {
            D_Add(tree);
        }
        else if (rc == 4) {
            D_Show(tree);
        }
        else if (rc == 2) {
            D_Find(tree);
        }
        else if (rc == 3) {
            D_Delete(tree);
        }
    }
}

void scan_int(int* n) {
    int i = 0;
    do {
        i = scanf("%d", n);
        if (i != 1) {
            printf("You`re wrong! Please, try again!\n");
            scanf("%*c");
        }
    } while (i != 1);
}

char* scan_string(char* n) {
    int k = 0;
    n = (char*)malloc(100);
    do {
        k = scanf("%s", n);
        if (k != 1) {
            printf("Please, try again!\n");
        }
    } while (k != 1);
    unsigned int i = strlen(n);
    n = (char*)realloc(n, (i + 1) * sizeof(char));
    return n;
}

Info* scan_info(struct Info* info) {
    info = (Info*)malloc(sizeof(struct Info));
    printf("First int-->");
    scan_int(&info->first);
    printf("Second int-->");
    scan_int(&info->second);
    printf("Text-->");
    info->word = scan_string(info->word);
    return info;
}