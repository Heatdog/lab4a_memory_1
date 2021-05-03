#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "for_all.h"
#include <string.h>
#include <time.h>

Tree* new_tree(Tree* tree) {
    tree = (Tree*)malloc(sizeof(Tree));
    tree->node = NULL;
    return tree;
}

///////////////////////////////////////////////////////////////////

void D_Add(Tree* tree) {
    char* key = NULL;
    struct Info* inf = NULL;
    printf("Please, enter key\nKey--->\n");
    key = scan_string(key);
    printf("Please, enter info (two int and one string types)\n");
    inf = scan_info(inf);
    add_tree(tree, key, inf);
}

void add_tree(Tree* tree, char* key, struct Info* info) {
    if (tree->node == NULL) {
        tree->node = new_node(tree->node, key, info);
    }
    else {
        add_tree_no_null(tree->node, key, info);
    }
}

struct Node* new_node(struct Node* node, char* key, struct Info* info) {
    node = (struct Node*)malloc(sizeof(struct Node));
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->data.info = info;
    node->data.key = key;
    node->data.info->next = NULL;
    return node;
}


void add_tree_no_null(struct Node* node, char* key, struct Info* info) {
    int result = strcmp(key, node->data.key);//ñðàâíåíèå ïî ASCII
    if (result > 0) {//êëþ÷ áîëüøå óçëà (èäåì âïðàâî)
        if (node->right == NULL) {
            node->right = new_node(node->right, key, info);
            node->right->parent = node;
        }
        else {
            add_tree_no_null(node->right, key, info);
        }
    }
    else if (result < 0) {//êëþ÷ ìåíüøå óçëà (èäåì âëåâî)
        if (node->left == NULL) {
            node->left = new_node(node->left, key, info);
            node->left->parent = node;
        }
        else {
            add_tree_no_null(node->left, key, info);
        }
    }
    else {//êëþ÷è ñâîïàäàþò --> äåëàåì ñïèñîê
        add_next_node(node, info);
        free(key);
    }
}

void add_next_node(struct Node* node, struct Info* info) {
    add_next_node_next(node->data.info, info);
}

void add_next_node_next(struct Info* info, struct Info* add) {
    if (info->next == NULL) {
        info->next = add;
        add->next = NULL;
    }
    else {
        add_next_node_next(info->next, add);
    }
}

///////////////////////////////////////////////////////////////////

void D_Show(Tree* tree) {
    int choose;
    printf("Do you want to see all tree like a normal tree (print 1) or back tree(print 2)?\nChoose-->");
    scan_int(&choose);
    if (choose == 1){
        int k = print_tree(tree->node, " ", 0);
        if (k == 1){
            printf("Tree is empty!\n");
        }
    } else{
        show_tree(tree->node);
        printf("\n");
    }
}

void show_tree(struct Node* node) {
    if (node == NULL) {
        printf("");
    }
    else {
        show_tree(node->left);
        show_tree(node->right);
        show_node(node, 0);
    }
}

void show_node(struct Node* node, int offset) {
    int i = 0;
    printf("%s //", node->data.key);
    print_info(node->data.info, i, offset);
}

///////////////////////////////////////////////////////////////////

void delete_tree(Tree* tree) {
    delete_node(tree->node);
    free(tree);
}

void delete_node(struct Node* node) {
    if (node == NULL) {
        return;
    }
    else {
        delete_node(node->left);
        delete_node(node->right);
        delete_node_next(node->data.info);
        free(node->data.key);
        free(node);
    }
}

void delete_node_next(struct Info* info) {
    if (info == NULL) {
        return;
    }
    else {
        delete_node_next(info->next);
        free(info->word);
        free(info);
    }
}

///////////////////////////////////////////////////////////////////

void D_Find(Tree* tree) {
    char* key = NULL;
    struct Info* info = NULL;
    int i = 0, choose;
    printf("Do you want to find certain (print 1) or the most different element (print 2)?\nChoose-->");
    scan_int(&choose);
    printf("Please, enter key\nKey-->");
    key = scan_string(key);
    if (choose == 1) {
        info = find_info(tree, key);
        if (info == NULL) {
            return;
        }
        print_info(info, i, 0);
    }
    else {
        find_different(tree, key);
    }
    free(key);
}


struct Info* find_info(Tree* tree, char* key) {
    struct Node* node = NULL;
    node = tree->node;
    node = find_info_node(node, key);
    if (node == NULL) {
        printf("We can`t find this element!\n");
        return NULL;
    }
    return node->data.info;
}

struct Node* find_info_node(struct Node* node, char* key) {
    if (node == NULL) {
        return NULL;
    }
    else {
        int result = strcmp(key, node->data.key);//ñðàâíåíèå ïî ASCII
        if (result > 0) {//êëþ÷ áîëüøå óçëà (èäåì âïðàâî)
            return find_info_node(node->right, key);
        }
        else if (result < 0) {//êëþ÷ ìåíüøå óçëà (èäåì âëåâî)
            return find_info_node(node->left, key);
        }
        return node;
    }
}

void print_info(struct Info* info, int i, int offset) {
    if (info == NULL) {
        return;
    }
    else {
        i++;
        printf("%d//%d//%s//release-->%d\n", info->first, info->second, info->word, i);
        if (info->next != NULL) {
            for (int k = 0; k < offset; k++) {
                printf("\t");
            }
        }
        print_info(info->next, i, offset);
    }
}


///////////////////////////////////////////////////////////////////

void D_Delete(Tree* tree) {
    char* key = NULL;
    printf("Enter key-->");
    key = scan_string(key);
    del_node(tree, key);
    free(key);
}

void del_node(Tree* tree, char* key) {
    struct Node* node = NULL;
    node = tree->node;
    node = find_info_node(node, key);//íàõîäèì óçåë ïî êëþ÷ó
    if (node == NULL){
        return;
    }
    if (node->data.info->next == NULL) {
        node = del_node_1(tree, node);//ëèñòüÿ
        if (node == NULL) {//ó÷ïåøíî óäàëèëè ëèñòîê (ïîñëåäíèé ýëåìåíò â âåäêå)
            return;
        }
        else if (node->right != NULL && node->left != NULL) {//è ñëåâà è ñïðàâà åñòü ýëåìåíû
            del_node_2(node);
            return;
        }
        else {
            del_node_3(tree, node);// åñòü ëèáî ñïðàâà ëèáî ñëåâà
            return;
        }
    }
    else {
        del_node_old(node);
        return;
    }
}

Node* del_node_1(Tree* tree, Node* node) {
    if (node == NULL) {//ìû âîîáùå íå íàøëè òàêîé ýëåìåíò
        return NULL;
    }
    else if (node->left != NULL || node->right != NULL) {//åñòü õîòÿ áû 1 ïîòîìîê (ìû õîòèì óäàëèòü òîëüêî ïîñëåäíèè ýëåìåíòû)
        return node;
    }
    Node* parent = node->parent;
    if (parent == NULL) {//êñëè äåðåâî ñîñòîèò èç îäíîãî óçëà
        tree->node = NULL;
    }
    else if (parent->left == node) {//åñëè íàø èñêîìûé óçåë ÿâëÿòåñÿ äî÷êîé ñëåâà
        parent->left = NULL;
    }
    else {//ñïðàâà
        parent->right = NULL;
    }
    free(node->data.info->word);
    free(node->data.key);
    free(node->data.info);
    free(node);
    return NULL;
}

void del_node_2(Node* node) {
    Node* ptr = node->right;
    Node *ptr_prev = (Node*)malloc(sizeof (struct Node));
    struct Node* parent = NULL;
    while (ptr->left != NULL) {
        ptr = ptr->left;
    }
    ptr_prev->data.key = node->data.key;
    ptr_prev->data.info = node->data.info;
    node->data.key = ptr->data.key;
    node->data.info = ptr->data.info;
    parent = ptr->parent;
    if (parent->left == ptr) {
        parent->left = NULL;
    }
    else {
        parent->right = NULL;
    }
    free(ptr_prev->data.info->word);
    free(ptr_prev->data.key);
    free(ptr_prev->data.info);
    free(ptr_prev);
    free(ptr);
}

void del_node_3(Tree* tree, Node* node) {//ñìûñë- ñîåäåíèòü ðîäèòåëÿ ñ 1 äî÷êîé, ÷òîáû óäàëèòü ïðîìåæóòî÷íûé ýëåìåíò
    Node* parent = node->parent, *ptr = NULL;
    if (node->right != NULL) {//åñòü åäèíòñâåííûé ïîòîìê ñïðàâà
        ptr = node->right;
    }
    else {
        ptr = node->left;
    }
    if (parent == NULL) {//òîëüêî 1 ýëåìåíò
        tree->node = ptr;
    }
    else if (parent->left == node) {
        parent->left = ptr;
    }
    else {
        parent->right = ptr;
    }
    ptr->parent = parent;
    free(node->data.info->word);
    free(node->data.key);
    free(node->data.info);
    free(node);
}

void del_node_old(struct Node* node) {
    Info* info = NULL;
    if (node->data.info->next == NULL) {
        free(node->data.info->word);
        free(node->data.key);
        free(node->data.info);
        free(node);
    }
    else {
        info = node->data.info;
        node->data.info = node->data.info->next;
        free(info->word);
        free(info);
    }
}

/////////////////////////////////////

void find_different(Tree* tree, char* key) {
    struct Node* node = NULL, *max = NULL, *min = NULL;
    node = tree->node;
    node = find_info_node(node, key);
    max = go_to_right(tree->node);
    min = go_to_left(tree->node);
    node = comparison(max, min, node);
    printf("%s//", node->data.key);
    print_info(node->data.info, 0, 0);
}

Node* go_to_right(Node* node) {
    if (node->right != NULL) {
        node = go_to_right(node->right);
    }
    else {
        return node;
    }
}


Node *go_to_left(Node* node){
    if (node->left != NULL){
        node = go_to_left(node->left);
    } else{
        return node;
    }
}

Node *comparison(struct Node* max, Node *min, Node *node){
    int result_max, result_min;
    result_max = comparison_back(node->data.key, max->data.key);
    result_min = comparison_back(min->data.key, node->data.key);
    if (result_max > result_min){
        return max;
    } else if (result_min > result_max){
        return min;
    } else{
        return node;
    }
}

int comparison_back(char *key1, char *key2){
    int i;
    if (strcmp(key2, key1) == 0){
        return 0;//ключи равны -- возвращаем разницу 0
    } else{
        for (i = 0; i < strlen(key1); i++){
            if (key1[i] != key2[i]){
                return ((int)key2[i] - (int)key1[i]);//нашли не совпадающий - возвращаем разницу
            }
        }
        return ((int)key2[i+1]);//иначе- возвращаем первый элемент, при условии что ключи разные при это длина ключа 1 меньше длины ключа 2
    }
}


////////////////////////////

void D_Timing(){
    Tree *tree_timing = NULL;
    tree_timing = new_tree(tree_timing);
    char *key = NULL;
    Info *info = NULL;
    int N;
    printf("Enter count of repeating\nEnter-->");
    scan_int(&N);
    char **key_mass = NULL;
    key_mass = (char **)calloc(N*10, sizeof (char ));
    printf("Start testing...\n");
    clock_t begin_add = clock();
    for (int i = 0; i < N; i++){
        key = key_random(key);
        key_mass[i] = key;
        info = info_rand(info);
        add_tree(tree_timing, key, info);
    }
    clock_t end_add = clock();
    clock_t begin_find = clock();
    for (int j = 0; j < N; j++){
        find_info(tree_timing, key_mass[j]);
    }
    clock_t end_find = clock();
    double time_spent_add = (double )(end_add - begin_add)/CLOCKS_PER_SEC;
    double time_spent_find = (double )(end_find - begin_find)/CLOCKS_PER_SEC;
    printf("Testing complete, result of adding-->%f//result of finding-->%f", time_spent_add, time_spent_find);
    delete_tree(tree_timing);
    free(key_mass);
}

char *key_random(char *key){
    key = (char *)calloc(10, sizeof (char));
    int i;
    for (i = 0; i < 10-1; i++){
        key[i] = 'a'+rand()%26;
    }
    key[i] = '\0';
    return key;
}

Info *info_rand(struct Info* info){
    info = (struct Info*)malloc(sizeof (struct Info));
    info->first = 0;
    info->second = 0;
    info->next = NULL;
    info->word = (char *)malloc(sizeof (char ));
    *info->word = 'a';
    return info;
}

//////////////////////////////////////////////

int print_tree(struct Node* parent, char *key, int offset) {
    Node *ptr = parent;
    if (ptr == NULL) {
        return 1;
    }
    if (strcmp(ptr->data.key, key) > 0) {
        print_tree(ptr->left, key, offset + 1);
        for (int i = 0; i < offset; i++) {
            printf("\t");
        }
        if (ptr != NULL){
            show_node(ptr, offset);
        }
        print_tree(ptr->right, key, offset + 1);
    } else {
        print_tree(ptr->right, key, offset);
    }
    return 0;
}
