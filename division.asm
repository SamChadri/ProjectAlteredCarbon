OPENQASM 3.0;
include "stdgates.inc";

gate majority c,b,a{ 
	cx a,b;
	cx a,c;
	ccx c,b,a;
}


gate subout c,b,a{
	ccx a,b,c;
	cx a,b;
	cx b,a;
	cx c,a;
	ccx b,c,a;
}


gate diff c,b,a{
	ccx b,c,a;
	cx c,a;
	cx b,a;
	cx a,b;
	ccx a,b,c;
	majority c,b,a;
	x a;
	x b;
	x c;
	ccx c,b,a;
}

gate sub4 a0,a1,a2,a3,b0,b1,b2,b3,cin,cout { 
	subout cin,b0,a0;
	subout a0,b1,a1;
	subout a1,b2,a2;
	subout a2,b3,a3; //Assuming no extra borrow for the last digit

}


gate greaterThan a,b,c{
    cx a,c;
    cx b,c;

}

def greater_than(qubit[4] a, qubit[4] b) -> bit {
    bit gt;
    bit[2] val;
    for int i in [3:0]{
        measure a[i] -> val[0];
        measure a[i] -> val[1]; 
        if(ans == 2){
            gt = 1;
            return gt;
        }
        if(ans == 1){
            return gt;
        }
        if(i == 0){
            gt = 1;
            return gt;
        }
    }

}

qreg carry[2];
creg ans[5];
qreg q1[4];
x q1[3];
qreg q2[4];
x q2[1];



measure q1[3] -> ans[0];
measure q2[3] -> ans[1];

for int i in [3:0]{
    if(ans == 0 || ans == 3){
        measure
    }
    if(ans == 2){
        gt
    }`
    if(ans == 1){

    }
}





//sub4 q1[0], q1[1], q1[2], q1[3], q2[0], q2[1], q2[2], q2[3], carry[0], carry[1];

subout carry[0],q2[0],q1[0];
reset carry[0];
cx q1[0], carry[0];

subout carry[0],q2[1],q1[1];
reset carry[0];
cx q1[1], carry[0];

subout carry[0],q2[2],q1[2];
reset carry[0];
cx q1[2], carry[0];

subout carry[0],q2[3],q1[3];
reset carry[0];




cx q1[2],carry[1];
diff carry[1],q2[3],q1[3];
reset carry[1];
cx q1[1], carry[1];
diff carry[1],q2[2],q1[2];
reset carry[1];
cx q1[0], carry[1];
diff carry[1],q2[1],q1[1];
diff carry[0],q2[0],q1[0];

measure q1[0] -> ans[0];
measure q1[1] -> ans[1];
measure q1[2] -> ans[2];
measure q1[3] -> ans[3];