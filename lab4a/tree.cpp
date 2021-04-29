#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <crtdbg.h> 

#include "tree.h"
#include <stdio.h>
#include "for_all.h"
#include <string.h>

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
    int result = strcmp(key, node->data.key);//сравнение по ASCII
    if (result > 0) {//ключ больше узла (идем вправо)
        if (node->right == NULL) {
            node->right = new_node(node->right, key, info);
            node->right->parent = node;
        }
        else {
            add_tree_no_null(node->right, key, info);
        }
    }
    else if (result < 0) {//ключ меньше узла (идем влево)
        if (node->left == NULL) {
            node->left = new_node(node->left, key, info);
            node->left->parent = node;
        }
        else {
            add_tree_no_null(node->left, key, info);
        }
    }
    else {//ключи свопадают --> делаем список
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
    /*int choose;
    printf("Do you want to see tree like usual (choose 2) or back (choose 1)\nChoose-->");
    scan_int(&choose);
    if (choose == 1){*/
    show_tree(tree->node);
    printf("\n");
}

void show_tree(struct Node* node) {
    if (node == NULL) {
        printf("");
    }
    else {
        show_tree(node->left);
        show_tree(node->right);
        show_node(node);
    }
}

void show_node(struct Node* node) {
    int i = 0;
    printf("%s //", node->data.key);
    print_info(node->data.info, i);
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
        print_info(info, i);
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
        int result = strcmp(key, node->data.key);//сравнение по ASCII
        if (result > 0) {//ключ больше узла (идем вправо)
            return find_info_node(node->right, key);
        }
        else if (result < 0) {//ключ меньше узла (идем влево)
            return find_info_node(node->left, key);
        }
        return node;
    }
}

void print_info(struct Info* info, int i) {
    if (info == NULL) {
        return;
    }
    else {
        i++;
        printf("%d//%d//%s//release-->%d\n", info->first, info->second, info->word, i);
        print_info(info->next, i);
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
    node = find_info_node(node, key);//находим узел по ключу
    if (node->data.info->next == NULL) {
        node = del_node_1(tree, node);//листья
        if (node == NULL) {//учпешно удалили листок (последний элемент в ведке)
            return;
        }
        else if (node->right != NULL && node->left != NULL) {//и слева и справа есть элемены
            del_node_2(node);
            return;
        }
        else {
            del_node_3(tree, node);// есть либо справа либо слева
            return;
        }
    }
    else {
        del_node_old(node);
        return;
    }
}

Node* del_node_1(Tree* tree, Node* node) {
    if (node == NULL) {//мы вообще не нашли такой элемент
        return NULL;
    }
    else if (node->left != NULL || node->right != NULL) {//есть хотя бы 1 потомок (мы хотим удалить только последнии элементы)
        return node;
    }
    Node* parent = node->parent;
    if (parent == NULL) {//ксли дерево состоит из одного узла
        tree->node = NULL;
    }
    else if (parent->left == node) {//если наш искомый узел являтеся дочкой слева
        parent->left = NULL;
    }
    else {//справа
        parent->right = NULL;
    }
    free(node->data.info->word);
    free(node->data.key);
    free(node->data.info);
    free(node);
    return NULL;
}

void del_node_2(Node* node) {//случай, когда есть обе дочки
    Node* ptr = node->right;//сдвинулись вправо и идем до конца ведово, чтобы взять этот элемент и поменять на искомый(удобно подставлять)
    struct Node* parent = NULL;
    while (ptr->left != NULL) {
        ptr = ptr->left;
    }
    node->data.key = node->data.key;//целиком перезаписываем значения црайне левого листка
    node->data.info = node->data.info;
    parent = ptr->parent;
    if (parent->left == ptr) {//обрываем связи
        parent->left = NULL;
    }
    else {
        parent->right = NULL;
    }
    free(ptr->data.info->word);
    free(ptr->data.key);
    free(ptr->data.info);
    free(ptr);
}

void del_node_3(Tree* tree, Node* node) {//смысл- соеденить родителя с 1 дочкой, чтобы удалить промежуточный элемент
    Node* parent = node->parent, * ptr = NULL;
    if (node->right != NULL) {//есть единтсвенный потомк справа
        ptr = node->right;
    }
    else {
        ptr = node->left;
    }
    if (parent == NULL) {//только 1 элемент
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
    struct Node* node = NULL;
    node = tree->node;
    node = find_info_node(node, key);
    node = go_to_right(node);
    printf("%s//", node->data.key);
    print_info(node->data.info, 0);
}

Node* go_to_right(Node* node) {
    if (node->right != NULL) {
        node = go_to_right(node->right);
    }
    else {
        return node;
    }
}


////////////////////////////

/*void show_tree_like(struct Node* node, Tree* tree){
    Node *time = go_to_left(tree->node);
    int n = time->n;
    show_tree_like_tree(node, tree, n);
}

struct Node* go_to_left(Node* node){
    if (node->left != NULL){
        node = go_to_left(node->left);
        node->n++;
    } else{
        return node;
    }
}

void show_tree_like_tree(struct Node* node, Tree* tree, int n){
    if (node == NULL){
        printf("");
    } else{
        show_tree_like_tree(node->left, tree, n);
        show_node(node);
        show_tree_like_tree(node->right, tree, n);
    }
}
*/