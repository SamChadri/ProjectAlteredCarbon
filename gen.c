#include "defs.h"
#include <stdio.h>
#include "data.h"
#include "decl.h"

static char *ASTop[] = { "+", "-", "*", "/" };

int interpretAST(struct ASTNode * node){
   int lresult, rresult; 
    if(node->left != NULL){
        lresult = interpretAST(node->left);
    }
    if(node->right != NULL){
        rresult = interpretAST(node->right);
    }

      // Debug: Print what we are about to do
    if (node->op == A_INTLIT)
        printf("int %d\n", node->value);
    else
        printf("%d %s %d\n", lresult, ASTop[node->op], rresult);


    switch(node->op){
        case A_ADD:
            return (lresult + rresult);
        case A_SUBTRACT:
            return (lresult - rresult);
        case A_MULTIPLY:
            return (lresult * rresult);
        case A_DIVIDE:
            return (lresult / rresult);
        case A_INTLIT:
            return (node->value);
        default:
            fprintf(stderr, "Do not recognize this symbol");
            exit(1);
    }
}


static int generate_AST(struct ASTNode *node)
{
    printf("Running generate_ast\n");
    int left_reg, right_reg; 
    if(node->left != NULL){
        left_reg = generate_AST(node->left);
    }
    if(node->right != NULL){
        right_reg = generate_AST(node->right);
    }




    switch(node->op){
        case A_ADD:
            return q_add(left_reg, right_reg);
        case A_INTLIT:
            printf("Running load register\n");
            return load_qregister(node->value);
        default:
            fprintf(stderr, "Do not recognize this symbol");
            exit(1);
    }
}


void genereate_code(struct ASTNode * node)
{
    q_load_preamble();
    int reg = generate_AST(node);
    int result = measure_result(reg);

    
}

