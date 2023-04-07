#include "decl.h"
#include <errno.h>
#include "defs.h"
#define extern_
#include "data.h"
#undef extern_


void init(char * file){
    Line = 0;
    Putback= '\n';
    if((Infile = fopen(file, "r")) == NULL){
        fprintf(stderr,"Unable to open %s: %s\n", file, strerror(errno));
        exit(1);
    }
}

char *tokstr[] = { "+", "-", "*", "/", "intlit" };

static void scanfile(){
    struct Token T;
    while(scan(&T)){
        printf("Token %s", tokstr[T.token]);
        if(T.token == T_INTLIT){
            printf(", integer value: %d", T.int_value);
        }
        printf("\n");
    }
}




void main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s infile\n", argv[0]);
        exit(1);
    }

    init(argv[1]);

    struct ASTNode *root;
    printf("Starting main\n");
    root = r_create_tree(NULL, NULL,NULL,NULL);
    printf("%d\n", interpretAST(root));

    exit(0);

}