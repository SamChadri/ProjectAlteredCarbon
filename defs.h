#include <stdlib.h>
#include <string.h>
#include <ctype.h>





enum {
    T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_EOF
};


enum {
    A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT
};

enum{
    NO_OP,
    ADD_REG,
    SUBTRACT_REG,
};

struct RegOp{
    int reg;
    int operation;
};

struct ASTNode{
    int op; 
    struct ASTNode *left;
    struct ASTNode *right;
    int value;
};
