#include <stdlib.h>
#include <string.h>
#include <ctype.h>





enum {
    T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_EOF
};


enum {
    A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT
};

struct ASTNode{
    int op; 
    struct ASTNode *left;
    struct ASTNode *right;
    int value;
};
