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
            return (node->value.int_value);
        default:
            fprintf(stderr, "Do not recognize this symbol");
            exit(1);
    }
}

static int interpret_AST(struct ASTNode *node)
{
   int left_register, right_register; 
    if(node->left != NULL){
        left_register = interpret_AST(node->left);
    }
    if(node->right != NULL){
        right_register = interpret_AST(node->right);
    }

      // Debug: Print what we are about to do



    switch(node->op){
        case A_ADD:
            return asadd(left_register, right_register);
        case A_SUBTRACT:
            return assub(left_register, right_register);
        case A_MULTIPLY:
            return asmultiply(left_register, right_register);
        case A_DIVIDE:
            return asdivide(left_register, right_register);
        case A_INTLIT:
            return asloadint(node->value.int_value);
        case A_IDENT:
            return asloadsymbol(node->value.id);
        case A_LVIDENT:
            return find_symbol_pos(node->value.id);
        case A_ASSIGN:
            return asstoresymbol(right_register, get_symbol(right_register)->name);
        default:
            fprintf(stderr, "Unknown AST operator", ASTop[node->op]);
            exit(1);
    }   
}


static struct RegOp q_interpret_AST(struct ASTNode *node)
{
    printf("Running generate_ast\n");
    int left_reg, right_reg;
    struct RegOp retval; 
    if(node->left != NULL){
        retval = q_interpret_AST(node->left);
        left_reg = retval.reg;
    }
    if(node->right != NULL){
        retval = q_interpret_AST(node->right);
        right_reg = retval.reg;
    }



    switch(node->op){
        case A_ADD:
            return q_add(left_reg, right_reg);
        case A_SUBTRACT:
            return q_subtract(left_reg, right_reg);
        case A_MULTIPLY:
            return q_multiply(left_reg, right_reg);
        case A_INTLIT:
            printf("Running load register\n");
            return load_qregister(node->value.int_value, node->position);
        default:
            fprintf(stderr, "Do not recognize this symbol");
            exit(1);
    }
}


void generate_qasm(struct ASTNode * node)
{
    q_load_preamble();
    struct RegOp retval = q_interpret_AST(node);
    
    int result = measure_result(retval.reg);

    
}


void generate_asm(struct ASTNode * node)
{
    aspreamble();
    int reg = interpret_AST(node);
    asprint(reg);
    aspostamble();
}


int interpret_asm_AST(struct ASTNode * node )
{
    return interpret_AST(node);
}

int interpret_qasm_AST(struct ASTNode * node){
    struct RegOp retval = q_interpret_AST(node);
    return retval.reg;
}

void acreate_symbol(char * symbol)
{
    ascreatesymbol(symbol);
}



