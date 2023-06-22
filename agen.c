#include "defs.h"
#include "data.h"
#include "decl.h"



static const int num_reg = 4;
static int free_reg[num_reg];
static char *reglist[4] = { "%r8", "%r9", "%r10", "%r11" };


void free_all_registers(){
    for(int i = 0; i < num_reg; i++ ){
        free_reg[i] = 0;
    }
}


static int allocate_register(){
    for(int i = 0; i < num_reg; i++){
        if(free_reg[i] == 0){
            free_reg[i] = 1;
            return i;
        }
    }
    fprintf(stderr, "Out of registers!\n");
    exit(1);
}


static void free_register(int reg){

    if(free_reg[reg] != 1){
        fprintf(stderr, "Error trying to free register %d\n", reg);
        exit(1);      
    }

    free_reg[reg] = 0;
}

void aspreamble()
{
    free_all_registers();
    fputs(
        "\t.text\n"
        ".LC0:\n"
        "\t.string\t\"%d\\n\"\n"
        "printint:\n"
        "\tpushq\t%rbp\n"
        "\tmovq\t%rsp, %rbp\n"
        "\tsubq\t$16, %rsp\n"
        "\tmovl\t%edi, -4(%rbp)\n"
        "\tmovl\t-4(%rbp), %eax\n"
        "\tmovl\t%eax, %esi\n"
        "\tleaq	.LC0(%rip), %rdi\n"
        "\tmovl	$0, %eax\n"
        "\tcall	_printf\n"
        "\tnop\n"
        "\tleave\n"
        "\tret\n"
        "\n"
        "\t.globl\t_main\n"
        "_main:\n"
        "\tpushq\t%rbp\n"
        "\tmovq	%rsp, %rbp\n",
    Outfile);
}


void aspostamble(){
    fputs(
        "\tmovl	$0, %eax\n"
        "\tpopq	%rbp\n"
        "\tret\n",
    Outfile);  
}

int asprint(int reg){
    fprintf(Outfile, "\tmovq\t%s, %%rdi\n",reglist[reg]);
    fprintf(Outfile, "\tcall\tprintint\n");
}

int asloadint(int val){

    int r = allocate_register();

    fprintf(Outfile, "\tmovq\t$%d, %s\n", val, reglist[r]);

    return r;

}

int asloadsymbol(char *symbol) {
  // Get a new register
  int r = alloc_register();

  // Print out the code to initialise it
  fprintf(Outfile, "\tmovq\t%s(\%%rip), %s\n", symbol, reglist[r]);
  return (r);
}


int asstoresymbol(int r, char *symbol) {
  fprintf(Outfile, "\tmovq\t%s, %s(\%%rip)\n", reglist[r], symbol);
  return (r);
}

void ascreatesymbol(char * symbol)
{
    fprintf(Outfile, "\t.comm\t%s,8,8\n", symbol);
}


int asadd(int r1, int r2){
    fprintf(Outfile, "\taddq\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r1);

    return r2;
}


int assub(int r1, int r2){
    fprintf(Outfile, "\tsubq\t%s, %s\n", reglist[r2], reglist[r1]);
    free_register(r2);

    return r1;
}


int asmultiply(int r1, int r2){
    fprintf(Outfile, "\timulq\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r1);

    return r2;
}


int asdivide(int r1, int r2){
    fprintf(Outfile,"\tmovq\t%s, %%rax\n",reglist[r1]);
    fprintf(Outfile, "\tcqo\n");
    //fprintf(Outfile,"\tmovq\t%s, %%rbx\n", reglist[r2]);
    fprintf(Outfile, "\tidivq\t%s\n",reglist[r2]);
    fprintf(Outfile, "\tmovq\t%%rax, %s\n",reglist[r1]);
    
    free_register(r2);

    return r1;
}

