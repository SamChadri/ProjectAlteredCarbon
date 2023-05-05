OPENQASM 2.0;
include "qelib1.inc";
gate majority a,b,c{ 
	cx c,b;
	cx c,a;
	ccx a,b,c;
}
gate unmaj a,b,c{ 
	ccx a,b,c;
	cx c,a;
	cx a,b;
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
	subout a2,b3,a3;
}
gate add4 a0,a1,a2,a3,b0,b1,b2,b3,cin,cout { 
	majority cin,b0,a0;
	majority a0,b1,a1;
	majority a1,b2,a2;
	majority a2,b3,a3;
	cx a3,cout;
	unmaj a2,b3,a3;
	unmaj a1,b2,a2;
	unmaj a0,b1,a1;
	unmaj cin,b0,a0;
}
qreg carry[2];
creg ans[5];
qreg q1[4];
x q1[0];
x q1[2];
qreg q2[4];
x q2[2];
sub4 q1[0], q1[1], q1[2], q1[3], q2[0], q2[1], q2[2], q2[3], carry[0], carry[1];
 
cx q1[2],carry[1];
diff carry[1],q2[3],q1[3];
reset carry[1];
cx q1[1], carry[1];
diff carry[1],q2[2],q1[2];
reset carry[1];
cx q1[0], carry[1];
diff carry[1],q2[1],q1[1];
diff carry[0],q2[0],q1[0];
reset carry[1];
reset carry[0];

measure q2[0] -> ans[0];
measure q2[1] -> ans[1];
measure q2[2] -> ans[2];
measure q2[3] -> ans[3];
measure carry[1] -> ans[4];
