#include <stdlib.h>
#include <string.h>
#include <ctype.h>





enum {
    T_PLUS, T_MINUS, T_STAR, T_SLASH,
    T_EOF, T_EQ, T_NE, T_LT, T_GT,T_LE, T_GE,
    T_SEMI, T_PRINT, T_MEASURE, T_INT, T_ASSIGN, T_IDENT, T_INTLIT,
};


enum {
    A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE,
    A_EQ, A_NE, A_LT, A_GT, A_LE, A_GE,
    A_INTLIT,A_IDENT, A_LVIDENT, A_ASSIGN
};

enum{
    NO_OP,
    ADD_REG,
    SUBTRACT_REG,
    MULTI_REG,
    COMP_REG
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
    union{
        int int_value;
        char * id;
    }value;
    int position;
};

struct NESTNode{
    struct ASTNode *nest;
    struct NESTNode *next;
    int priority;
    int token;

};

struct SYMNode{
    char *name;
    struct SYMNode * next;
    int priority;
};


