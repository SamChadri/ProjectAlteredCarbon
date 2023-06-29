#include "defs.h"
#include "data.h"
#include <stdio.h>
#include <stdbool.h>



static int Globs = 0;

struct SYMNode * find_symbol(char *s)
{
    struct SYMNode * counter = SymHead;

    while(counter != NULL)
    {
        printf("COUNTER SYMBOL %s\n", counter->name);
        if(!strcmp(counter->name, s))
        {
            printf("FOUND SYMBOL %s\n", s);
            return counter;
        }
        counter = counter->next;
    }

    return NULL;
}
struct SYMNode * find_symbol_pos(char *s)
{
    struct SYMNode * counter = SymHead;

    int index = 0;
    while(counter != NULL)
    {
        if(!strcmp(counter->name, s))
        {
            return index;
        }
        index ++;
        counter = counter->next;
    }

    return index;

}

struct SYMNode * get_symbol(int position)
{
    struct SYMNode * counter = SymHead;
    for(int i = 0; i < position; i++)
    {
        counter = counter->next;
    }

    return counter;

}

struct SYMNode * create_symbol(char * s, struct SYMNode * next, int priority)
{
    struct SYMNode * retval;

    retval = (struct SYMNode *) malloc(sizeof(struct SYMNode));

    if(retval == NULL)
    {
        fprintf(stderr, "sym::create_symbol::Cannot allocate memory NESTNode. Malloc error \n");
        exit(1);
    }
    retval->name = strdup(s);
    retval->next = next;
    retval->priority = priority;

    return retval;
}

void add_symbol(struct SYMNode * node)
{
    struct SYMNode * oldhead = SymHead;
    
    node->next = oldhead;
    SymHead = node;


}


