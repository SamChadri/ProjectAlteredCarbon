#include "defs.h"
#include "data.h"
#include "decl.h"


static char * creg_list [] = {"r1","r2","r3"};
static char * qreg_list [] = {"q1","q2", "psum1", "psum2"};
enum {
    Q1,
    Q2,
    PSUM1,
    PSUM2
};


int pos_reg[2] = {0,0};
int free_qreg[2] = {FREE_REG,FREE_REG};
int free_creg[2] = {0,0};
int num_creg = 2;
int num_qreg = 2;
int bit_size = 4;



static void free_q_registers(){
    for(int i =0; i < num_qreg; i ++){
        free_qreg[0] = 0;
    }
}


static void free_c_registers(){
    for(int i =0; i < num_creg; i ++){
        free_creg[0] = 0;
    }
}

static int allocate_creg(){
    for(int i = 0; i < num_creg; i++){
        if(free_creg[i] == 0){
            free_creg[i] = 1;
            return i;
        }
    }
    fprintf(stderr, "Out of c_registers!\n");
    exit(1);
}
//PRECEDENCE ALLOCATION DUE TO QUBIT RESTRICTIONS
static int allocate_qreg(int position){
    printf("Allocating register...\n");
    for(int i = 0; i < num_qreg; i++){
        if(pos_reg[position] == 1 && free_qreg[i] == ALLOCATED_REG)
        {
            //CREATE POSITION ENUM LATER MAYBE
            printf("Found position register that has already been allocated\n");
            free_qreg[i] = ALLOCATED_REG;
            printf("New register allocation takes precedence %s\n", qreg_list[i]);
            return i;

        }
        if(free_qreg[i] == FREE_ALLOC_REG){
            printf("FOUND 2...\n");
            free_qreg[i] = 1;
            pos_reg[position] = 1;
            printf("Found already created register %s\n", qreg_list[i]);

            return i;
        }
        if(free_qreg[i] == FREE_REG){
            printf("FOUND 0...at %d\n", i);
            free_qreg[i] = ALLOCATED_REG;
            pos_reg[position] = 1;
            printf("creating new register %s\n", qreg_list[i]);
            fprintf(Outfile, "qreg %s[%d];\n", qreg_list[i], bit_size);

            return i;
        }

    }

    fprintf(stderr, "Out of q_registers!\n");
    exit(1);
}



static int num_bits(int num){
    int num_array[8];
    int count = 0;

    for(;num > 0; count++){
        num_array[count] = num % 2;
        num = num/2;
    }

    return count;
}
static void create_adder_gates(){
    fputs("gate majority c,b,a{ \n" 
          "\tcx a,b;\n" 
          "\tcx a,c;\n"
          "\tccx c,b,a;\n" 
          "}\n",
          Outfile
    );

    fputs("gate unmaj c,b,a{ \n" 
          "\tccx c,b,a;\n" 
          "\tcx a,c;\n"
          "\tcx c,b;\n" 
          "}\n",
          Outfile
    );

    fputs("gate subout c,b,a{ \n"
	      "\tccx a,b,c;\n"
	      "\tcx a,b;\n"
	      "\tcx b,a;\n"
	      "\tcx c,a;\n"
	      "\tccx b,c,a;\n"
         "}\n",
         Outfile
    );

    fputs("gate diff c,b,a{ \n"
	      "\tccx b,c,a;\n"
	      "\tcx c,a;\n"
	      "\tcx b,a;\n"
	      "\tcx a,b;\n"
	      "\tccx a,b,c;\n"
	      "\tmajority c,b,a;\n"
	      "\tx a;\n"
	      "\tx b;\n"
	      "\tx c;\n"
	      "\tccx c,b,a;\n"
          "}\n",
          Outfile
    );

    fputs("gate sub4 a0,a1,a2,a3,b0,b1,b2,b3,cin,cout {\n "
	      "\tsubout cin,b0,a0;\n"
	      "\tsubout a0,b1,a1;\n"
	      "\tsubout a1,b2,a2;\n"
	      "\tsubout a2,b3,a3;\n" 
         "}\n",
          Outfile);

    fputs("gate add4 a0,a1,a2,a3,b0,b1,b2,b3,cin,cout { \n" 
          "\tmajority cin,b0,a0;\n" 
          "\tmajority a0,b1,a1;\n"
          "\tmajority a1,b2,a2;\n"
          "\tmajority a2,b3,a3;\n"
          "\tcx a3,cout;\n"
          "\tunmaj a2,b3,a3;\n"
          "\tunmaj a1,b2,a2;\n"
          "\tunmaj a0,b1,a1;\n"
          "\tunmaj cin,b0,a0;\n" 
          "}\n",
          Outfile
    );

    fputs("gate add5 a0,a1,a2,a3,a4,b0,b1,b2,b3,b4,cin,cout { \n"
	      "\tmajority cin,b0,a0;\n"
	      "\tmajority a0,b1,a1;\n"
	      "\tmajority a1,b2,a2;\n"
	      "\tmajority a2,b3,a3;\n"
          "\tmajority a3,b4,a4;\n"
	      "\tcx a4,cout;\n"
          "\tunmaj a3,b4,a4;\n"
	      "\tunmaj a2,b3,a3;\n"
	      "\tunmaj a1,b2,a2;\n"
	      "\tunmaj a0,b1,a1;\n"
	      "\tunmaj cin,b0,a0;\n"
          "}\n"
        ,Outfile
    );

    fputs("gate mult31 a1,a2,a3,b1,c1,c2,c3{ \n"
          "ccx a1,b1,c1;\n"
          "ccx a2,b1,c2;\n"
          "ccx a3,b1,c3;\n"
          "}\n",
          Outfile
    );

    fputs("qreg carry[2];\n", Outfile);
    fputs("creg ans[6];\n", Outfile);
    fputs("qreg psum1[5];\n"
          "qreg psum2[5];\n"
          ,Outfile);
}

void q_load_preamble(){
    printf("Loading Preamble...\n");
    fputs("OPENQASM 2.0;\n"
          "include \"qelib1.inc\";\n", Outfile);
    printf("Loading adder gates...\n");
    create_adder_gates();
    printf("Done with preamble...\n");


}


static load_int(int num_bits, int num){

}


static void create_cregister(int val){
    int creg_num = allocate_creg();
    fprintf(Outfile, "creg %s[%d]",creg_list[creg_num], Outfile);
    
}


static void reset_qreg(int reg){
    fprintf(Outfile, "reset %s; \n", qreg_list[reg]);
    free_qreg[reg] = FREE_ALLOC_REG;
}

struct RegOp load_qregister(int val, int position){

    int qreg_num = allocate_qreg(position);
    printf("Loading register %s with value %d\n", qreg_list[qreg_num], val);
    for(int i = 0; val > 0; i++){
        int bit_val = val % 2;
        val = val / 2;
        if(bit_val == 1){
            fprintf(Outfile, "x %s[%d];\n",qreg_list[qreg_num],i );
        }
    }
    //printf("Loading register %s with value %d\n", qreg_list[qreg_num], val);
    struct RegOp retval = {qreg_num, NO_OP};
    return retval;
}
//TODO: FIGURE OUT HOW TO CHAIN CARRY BITS
struct RegOp q_add(int r1, int r2){
    printf("Adding gates %s %s\n", qreg_list[r1], qreg_list[r2]);

    fprintf(Outfile, "add4 %s[0], %s[1], %s[2], %s[3], %s[0], %s[1], %s[2], %s[3], carry[0], carry[1];\n",
        qreg_list[r1], qreg_list[r1], qreg_list[r1], qreg_list[r1],
        qreg_list[r2], qreg_list[r2], qreg_list[r2], qreg_list[r2]);
    
    fprintf(Outfile,
            "measure carry[0] -> ans[4];\n"
            "reset carry[1];\n"
            "reset carry[0];\n"
    );
    reset_qreg(r1);
    struct RegOp retval = {r2, ADD_REG};
    return retval;
}
struct RegOp q_subtract(int r1, int r2){
    printf("Adding gates %s %s\n", qreg_list[r1], qreg_list[r2]);


    //fprintf(Outfile, "sub4 %s[0], %s[1], %s[2], %s[3], %s[0], %s[1], %s[2], %s[3], carry[0], carry[1];\n \n",
    //    qreg_list[r1], qreg_list[r1], qreg_list[r1], qreg_list[r1],
    //    qreg_list[r2], qreg_list[r2], qreg_list[r2], qreg_list[r2]);
    
    fprintf(Outfile,
           "\t//-----------SUBTRACTION ROUTINE START--------------\n"
           "subout carry[0], %s[0], %s[0];\n"
           "reset carry[0];\n"
           "cx %s[0], carry[0];\n\n"
           "subout carry[0], %s[1], %s[1];\n"
           "reset carry[0];\n"
           "cx %s[1], carry[0];\n\n"
           "subout carry[0], %s[2], %s[2];\n"
           "reset carry[0];\n"
           "cx %s[2], carry[0];\n\n"
           "subout carry[0], %s[3], %s[3];\n"
           "reset carry[0];\n\n",
           qreg_list[r2],qreg_list[r1],
           qreg_list[r1],
           qreg_list[r2],qreg_list[r1],
           qreg_list[r1],
           qreg_list[r2],qreg_list[r1],
           qreg_list[r1],        
           qreg_list[r2],qreg_list[r1]
    );

    fprintf(Outfile,
            "cx %s[2],carry[1];\n"
            "diff carry[1],%s[3],%s[3];\n"
            "reset carry[1];\n"
            "cx %s[1], carry[1];\n"
            "diff carry[1],%s[2],%s[2];\n"
            "reset carry[1];\n"
            "cx %s[0], carry[1];\n"
            "diff carry[1],%s[1],%s[1];\n"
            "diff carry[0],%s[0],%s[0];\n"
            "reset carry[1];\n"
            "reset carry[0];\n"
            "\t//-----------SUBTRACTION ROUTINE END--------------\n\n",
            qreg_list[r1],
            qreg_list[r2],qreg_list[r1],
            qreg_list[r1],
            qreg_list[r2],qreg_list[r1],
            qreg_list[r1],
            qreg_list[r2],qreg_list[r1],
            qreg_list[r2],qreg_list[r1]
    );

    reset_qreg(r2);
    struct RegOp retval = {r1, SUBTRACT_REG};
    return retval;

}

struct RegOp q_multiply(int r1, int r2){
    fprintf(Outfile,
           "\t//-----------MULTIPLICATION ROUTINE START--------------\n"
           "mult31 %s[0],%s[1],%s[2],%s[0],psum1[0],psum1[1],psum1[2];\n"
           "mult31 %s[0],%s[1],%s[2],%s[1],psum2[1],psum2[2],psum2[3];\n"
           "add5 psum1[0],psum1[1],psum1[2],psum1[3],psum1[4],psum2[0],psum2[1],psum2[2],psum2[3],psum2[4],carry[0],carry[1];\n"
           "reset psum1;\n"
           "reset carry[0];\n"
           "reset carry[1];\n"
           "mult31 %s[0],%s[1],%s[2],%s[2],psum1[2],psum1[3],psum1[4];\n"
           "add5 psum1[0],psum1[1],psum1[2],psum1[3],psum1[4],psum2[0],psum2[1],psum2[2],psum2[3],psum2[4],carry[0],carry[1];\n"
           "reset psum1;\n"
           "reset carry[0];\n"
            "\t//-----------MULTIPLICATION ROUTINE END--------------\n\n",
           qreg_list[r1],qreg_list[r1],qreg_list[r1],qreg_list[r2],
           qreg_list[r1],qreg_list[r1],qreg_list[r1],qreg_list[r2],
           qreg_list[r1],qreg_list[r1],qreg_list[r1],qreg_list[r2]
    );
    struct RegOp retval = {PSUM2, SUBTRACT_REG};
    return retval;
}

int measure_result(int reg){

    fprintf(Outfile, "measure %s[0] -> ans[0];\n", qreg_list[reg]);
    fprintf(Outfile, "measure %s[1] -> ans[1];\n", qreg_list[reg]);
    fprintf(Outfile, "measure %s[2] -> ans[2];\n", qreg_list[reg]);
    fprintf(Outfile, "measure %s[3] -> ans[3];\n", qreg_list[reg]);

    if(reg == PSUM2 || reg == PSUM1){
        fprintf(Outfile, "measure %s[4] -> ans[4];\n",qreg_list[reg]);
        fprintf(Outfile, "measure carry[1] -> ans[5];\n");
    }
}




// Quantum addition using qubits
