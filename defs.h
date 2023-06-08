#include <stdlib.h>
#include <string.h>
#include <ctype.h>





enum {
    T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_EOF, T_SEMI, T_PRINT, T_MEASURE
};


enum {
    A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT
};

enum{
    NO_OP,
    ADD_REG,
    SUBTRACT_REG,
    MULTI_REG,
};

enum {

    LEFT_REG,
    RIGHT_REG,
    FREE_REG,
    FREE_ALLOC_REG,
    ALLOCATED_REG
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
    int position;
};

struct NESTNode{
    struct ASTNode *nest;
    struct NESTNode *next;
    int priority;
    int token;

};
