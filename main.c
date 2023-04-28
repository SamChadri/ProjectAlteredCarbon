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
      if ((Outfile = fopen("out.asm", "w")) == NULL) {
        fprintf(stderr, "Unable to create out.asm: %s\n", strerror(errno));
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
    //root = r_create_tree(NULL, NULL,NULL,NULL);
    root = pratt_create_tree(0, NULL);
    int result = interpretAST(root);
    printf("Done doing things\n");
    printf("%d\n", result);
    printf("Done interpreting...\n");
    genereate_code(root);

    fclose(Outfile);

    exit(0);

}