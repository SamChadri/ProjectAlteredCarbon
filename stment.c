#include "defs.h"
#include "decl.h"
#include "data.h"
#include <stdio.h>
#include <stdbool.h>


struct NESTNode * build(int statement_token, char * statement, struct NESTNode * head )
{
    if(token.token == statement_token){
        struct ASTNode * tree = pratt_create_tree(100, NULL);
        struct NESTNode * node = make_nest_node(tree, NULL, statement_token, 0 );
        return insert_nest_node(node, head);
    }else{
        printf("%s expected on line %d\n", statement, Line);
        exit(1);
    }
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

            case T_EOF:
                return head;
            default:
                printf("Unexpected token %s on line %d", token.token, Line);
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
            case T_EOF:
                return head;
            default:
                printf("Unexpected token %d on line %d", token.token, Line);
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
                printf("TOKEN: %d, T_PRINT: %d\n", counter->token, T_PRINT);
                reg = interpret_asm_AST(counter->nest);
                asprint(reg);
                break;
            default:
                printf("Unexpected error occured with token %d\n", counter->token);
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
            default:
                printf("Unexpected error occured with token %d\n", counter->token);
                exit(1);
       }
       counter = counter->next;
    }
}




