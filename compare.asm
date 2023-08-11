OPENQASM 2.0;
include "qelib1.inc";

gate gthan a,b,c{
    cx b, a;
    ccx c, b, a;
}

gate lthan a, b, c{
    cx c, a;
    ccx c, b, a;
}

gate eqauls a,b,c{
    cx b, a;
    cx c, a;
}
qreg q1[4];
qreg q2[4];

qreg gqit[1];
creg gbit[1];

x q1[0];
x q1[3];

x q2[2];
x q2[0];


//-------EQUALS SUBROUTINE---------

equals gqit, q1[3], q2[3];

measure gqit -> gbit;

if(gbit == 0) equals gqit, q1[2], q2[2];

measure gqit -> gbit;

if(gbit == 0) equals gqit, q1[1], q2[1];

measure gqit -> gbit;

if(gbit == 0) equals gqit, q1[0], q2[0];

measure gqit -> gbit;


//-------EQUALS SUBROUTINE----------

//-------GREATER THAN SUBROUTINE
gthan gqit, q1[3], q2[3];

measure gqit -> gbit;

if(gbit == 0) gthan gqit, q1[2], q2[2];

measure gqit -> gbit;

if(gbit == 0) gthan gqit, q1[1], q2[1];

measure gqit -> gbit;

if(gbit == 0) gthan gqit, q1[0], q2[0];

measure gqit -> gbit;
//-------GREATER THAN SUBROUTE