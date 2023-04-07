#include "defs.h"
#include <stdio.h>

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

