#include "defs.h"
#include <stdio.h>
#include <stdbool.h>

struct NESTNode * make_nest_node(struct ASTNode * root, struct NESTNode * next, int token ,int priority)
{
    struct NESTNode * n;

    n = (struct NESTNode *) malloc(sizeof(struct NESTNode));
    if(n == NULL){
        fprintf(stderr, "Cannot allocate memory NESTNode. Malloc error \n");
        exit(1);
    }
    n->nest = root;
    n->next = next;
    n->token = token;
    n->priority = priority;

    return (n);
}


struct NESTNode * insert_nest_node(struct NESTNode * node, struct NESTNode * head)
{
    struct NESTNode * newHead;
    node->next = head;
    newHead = node;

    return newHead;
}
