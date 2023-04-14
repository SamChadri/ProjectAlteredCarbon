#include "defs.h"
#include "data.h"
#include "decl.h"


static char * creg_list = {"r1","r2","r3"};
static char * qreg_list = {"q1","q2","q3"};
int free_qreg[3];
int free_creg[3];
int num_creg = 3;
int num_qreg = 3;

static void free_q_registers(){
    for(int i =0; i < 3; i ++){
        free_qreg[0] = 0;
    }
}


static void free_c_registers(){
    for(int i =0; i < 3; i ++){
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

static int allocate_qreg(){
    for(int i = 0; i < num_qreg; i++){
        if(free_qreg[i] == 0){
            free_qreg[i] = 1;
            return i;
        }
    }
    fprintf(stderr, "Out of q_registers!\n");
    exit(1);
}


static int num_bits(int num){
    int num_array[32];
    int count = 0;

    for(;num > 0; count++){
        num_array[count] = num % 2;
        num = num/2;
    }

    return count;
}


static void load_cregister(int val){
    int creg_num = allocate_creg();
    fprintf(Outfile, "creg %s[%d]",creg_list[creg_num], bitnum);
    return creg_num;
}

static void allocate_qregister(int val){
    int qreg_num = allocate_qreg();
    int bit_size = num_bits(val);
    fprintf(Outfile, "creg %s[%d]",creg_list[qreg_num], bitnum);
    return qreg_num;
}
//Classical addition using bits
int qc_add(int r1, int r2){
    
}

// Quantum addition using qubits
int qq_add(int r1, int r2){

}