#include "defs.h"
#include <stdio.h>
#include <stdbool.h>

struct ASTNode * make_ast_node(int op, struct ASTNode * left, struct ASTNode* right, int value){

    struct ASTNode * node;

    node = (struct ASTNode *) malloc(sizeof(struct ASTNode));
    if(node == NULL){
        fprintf(stderr, "Cannot allocate memory ASTNode. Malloc error \n");
        exit(1);
    }

    node->op = op;
    node->right = right;
    node->left = left;
    node->value.int_value = value;

    return (node);

}

struct ASTNode * cmake_ast_node(int op, struct ASTNode * left, struct ASTNode* right, char * value){
    
    struct ASTNode * node;

    node = (struct ASTNode *) malloc(sizeof(struct ASTNode));
    if(node == NULL){
        fprintf(stderr, "Cannot allocate memory ASTNode. Malloc error \n");
        exit(1);
    }

    node->op = op;
    node->right = right;
    node->left = left;
    node->value.id = strdup(value);

    return (node);    
}

struct ASTNode * make_leaf_node(int op, int value){
    
    return make_ast_node(op, NULL, NULL, value);

}

struct ASTNode * cmake_leaf_node(int op, char * id)
{
    return cmake_ast_node(op, NULL, NULL, id);
}

struct ASTNode * make_unary_node(int op, struct ASTNode * node, int value)
{
    return make_ast_node(op, node, NULL, value);

}




