#pragma once

#ifndef LAB4A_SEM2_TREE_H
#define LAB4A_SEM2_TREE_H


typedef struct Info {
    int first;
    int second;
    char* word;
    struct Info* next;
}Info;


typedef struct Node {
    struct {
        char* key;
        struct Info* info;
    }data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

typedef struct tree {
    struct Node* node;
}Tree;


Tree* new_tree(Tree*);
void D_Add(Tree*);
void D_Find(Tree*);
void D_Delete(Tree*);
void D_Show(Tree*);
void add_tree(Tree*, char*, struct Info*);
void show_tree(struct Node*);
void delete_tree(Tree*);
struct Node* new_node(struct Node*, char*, struct Info*);
void add_tree_no_null(struct Node*, char*, struct Info*);
void add_next_node(struct Node*, struct Info*);
void show_node(struct Node*);
void delete_node(struct Node*);
void delete_node_next(struct Info*);
struct Info* find_info(Tree*, char*);
struct Node* find_info_node(struct Node*, char*);
void print_info(struct Info*, int);
void add_next_node_next(struct Info*, struct Info*);
void del_node(Tree*, char*);
struct Node* del_node_1(Tree*, struct Node*);
void del_node_2(struct Node*);
void del_node_3(Tree*, struct Node*);
void del_node_old(struct Node*);
void find_different(Tree*, char*);
Node* go_to_right(Node*);
struct Node* go_to_left(Node*);
//void show_tree_like_tree(Node*, struct tree*, int);
//void show_tree_like(struct Node*, struct tree*);



#endif //LAB4A_SEM2_TREE_H
