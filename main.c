#include "decl.h"
#include <errno.h>
#include "defs.h"
#define extern_
#include "data.h"
#undef extern_


void init(char * file, int type){
    Line = 0;
    Putback= '\n';
    char * outfile_name;
    if(type == 1){
        outfile_name = "out.s";
    }else{
        outfile_name = "out.asm";
    }
    if((Infile = fopen(file, "r")) == NULL){
        fprintf(stderr,"Unable to open %s: %s\n", file, strerror(errno));
        exit(1);
    }
    if((Outfile = fopen(outfile_name, "w")) == NULL) {
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

static void compile_asm()
{
    aspreamble();
    struct NESTNode * head = build_astat_nest();
    interpret_astat_nest(head);
    aspostamble();

}

static void compile_qasm()
{
    q_load_preamble();
    struct NESTNode * head = build_qstat_nest();
    interpret_qstat_nest(head);
    
}

static void compile(int qasm_flag)
{
    if(qasm_flag == 1)
    {
        printf("Compiling for x86 Assembly....\n");
        compile_asm();
    }
    else
    {
        printf("Compiling for QASM...\n");
        compile_qasm();
    }
}




void main(int argc, char *argv[]){
    int q_comp = 1;
    if(argc < 2){
        fprintf(stderr, "Usage: %s infile\n", argv[0]);
        exit(1);
    }

    else if(argc == 3)
    {
        if(!strcmp("-q", argv[2]))
        {
            q_comp = 0;
        }
        
    }

    init(argv[1], q_comp);

    struct ASTNode *root;
    printf("Starting main\n");
    //root = r_create_tree(NULL, NULL,NULL,NULL);

    /*
    LESSON 4 ASSEMBLY
    root = pratt_create_tree(100, NULL);
    int result = interpretAST(root);
    printf("Done doing things\n");
    printf("%d\n", result);
    printf("Done interpreting...\n");
    generate_asm(root);
    */
    compile(q_comp);

    fclose(Outfile);

    exit(0);

}