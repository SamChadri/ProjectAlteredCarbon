#include "defs.h"
#include "decl.h"
#include "data.h"
#include <stdio.h>
#include <stdbool.h>

static void match(int statement_token, char * statement)
{
    printf("current token %d\n", token.token);
    if(statement_token == token.token){
        scan(&token);
    }else{
        printf("stment::build::%s expected on line %d\n", statement, Line);
        exit(1);
    }
}

static void semi()
{
    if(T_SEMI != token.token)
    {
        printf("stment::build::%s expected on line %d\n", ";", Line);
        exit(1);
    }
}
struct NESTNode * build(int statement_token, char * statement, struct NESTNode * head )
{
    if(token.token == statement_token){
        printf("Making Pratt Tree\n");
        struct ASTNode * tree = pratt_create_tree(100, NULL);
        printf("Making Nest Node\n");
        struct NESTNode * node = make_nest_node(tree, NULL, statement_token, 0 );
        return insert_nest_node(node, head);
    }else{
        printf("stment::build::%s expected on line %d\n", statement, Line);
        exit(1);
    }
}

struct NESTNode * print_build()
{
    
}
static void int_build()
{
    match(T_INT, "int");

    match(T_IDENT, "identifier");

    struct SYMNode * node = create_symbol(Text,NULL, 0);
    add_symbol(node);
    acreate_symbol(node->name);
    //BACKEND SAVE SYMBOL HERE
    semi();
    
}

static void quint_build()
{
    match(T_INT, "int");

    match(T_IDENT, "identifier");

    struct SYMNode * node = create_symbol(Text,NULL, 0);
    add_symbol(node);
    qcreate_symbol(node->name);
    //BACKEND SAVE SYMBOL HERE
    semi();   
}

struct NESTNode * assignment_build(struct NESTNode * head)
{
    struct ASTNode * left,  * right, * tree;
    match(T_IDENT, "identifier");
    left =  cmake_leaf_node(A_LVIDENT, Text);

    if(T_EQUALS != token.token)
    {
        printf("stment::build:: = expected on line %d\n", ";", Line);
        exit(1);
    }
    right = pratt_create_tree(100, NULL);
    tree = make_ast_node(A_ASSIGN, left, right, 0);
    struct NESTNode * node = make_nest_node(tree, NULL, T_IDENT, 0 );
    return insert_nest_node(node, head);
    
    
}




struct NESTNode * build_astat_nest()
{
    struct NESTNode * head = NULL;
    scan(&token);

    while(1)
    {
        struct ASTNode * tree;
        int statement_token = token.token;

        switch (token.token)
        {
            case T_PRINT:
                head = build(T_PRINT, "print", head);
                break;
            case T_INT:
                printf("stment::build_astat_nest:: Integer Initialization Build\n");
                int_build();
                break;
            case T_IDENT:
                printf("stment::build_astat_nest:: Assignment Build\n");
                head = assignment_build(head);
                break;
            case T_EOF:
                printf("stment::build_astat_nest:: EOF file reached \n");
                return head;
            default:
                printf("stment::build_astat_nest::Unexpected token %s on line %d", token.token, Line);
                exit(1);
        }
        scan(&token);


    }
    return head;

}
struct NESTNode * build_qstat_nest()
{
    struct NESTNode * head = NULL;
    scan(&token);

    while(1)
    {
        struct ASTNode * tree;
        int statement_token = token.token;
        switch (token.token)
        {
            case T_MEASURE:
                head = build(T_MEASURE, "measure", head);
                break;
            case T_INT:
                printf("stment::build_qstat_nest:: Qubit Integer Initialization Build\n");
                quint_build();
                break;
            case T_IDENT:
                printf("stment::build_qstat_nest:: Assignment Build\n");
                head = assignment_build(head);
                break;
            case T_EOF:
                printf("stment::build_qstat_nest:: EOF file reached \n");
                return head;
            default:
                printf("stment::build_qstat_nest::Unexpected token %d on line %d", token.token, Line);
                exit(1);
        }

        scan(&token);
    }
    return head;

}

void interpret_astat_nest(struct NESTNode * head)
{
    struct NESTNode * counter = head;
    while(counter != NULL)
    {
       int reg;
       switch(counter->token)
       {
            case T_PRINT:
                printf("stment::interpret_astat_nest::Interpreting TOKEN: %d, T_PRINT: %d to assembly\n", counter->token, T_PRINT);
                reg = interpret_asm_AST(counter->nest);
                asprint(reg);
                break;
            case T_INT:
                printf("stment::interpret_astat_nest:: Integer initialization already interpreted\n");
                break;
            case T_IDENT:
                printf("stment::interpret_astat_nest:: Interpreting identifiers to assembly\n");
                reg = interpret_asm_AST(counter->nest);
                break;
            default:
                printf("stment::interpret_astat_nest::Unexpected error occured with token %d\n", counter->token);
                exit(1);
       }
       counter = counter->next;
       if(counter == NULL){
            printf("Counter now NULL\n");
       }
    }
}

void interpret_qstat_nest(struct NESTNode * head)
{
    struct NESTNode * counter = head;
    while(counter != NULL)
    {
       int reg;
       switch(counter->token)
       {
            case T_MEASURE:
                reg = interpret_qasm_AST(counter->nest);
                measure_result(reg);
                break;
            case T_INT:
                printf("stment::interpret_qstat_nest:: Integer initialization already interpreted\n");
                break;
            case T_IDENT:
                printf("stment::interpret_qstat_nest:: Interpreting identifiers to assembly\n");
                reg = interpret_qasm_AST(counter->nest);
                break;
            default:
                printf("stment::interpret_qstat_nest::Unexpected error occured with token %d\n", counter->token);
                exit(1);
       }
       counter = counter->next;
    }
}




