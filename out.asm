OPENQASM 2.0;
include "qelib1.inc";
gate majority c,b,a{ 
	cx a,b;
	cx a,c;
	ccx c,b,a;
}
gate unmaj c,b,a{ 
	ccx c,b,a;
	cx a,c;
	cx c,b;
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
gate add5 a0,a1,a2,a3,a4,b0,b1,b2,b3,b4,cin,cout { 
	majority cin,b0,a0;
	majority a0,b1,a1;
	majority a1,b2,a2;
	majority a2,b3,a3;
	majority a3,b4,a4;
	cx a4,cout;
	unmaj a3,b4,a4;
	unmaj a2,b3,a3;
	unmaj a1,b2,a2;
	unmaj a0,b1,a1;
	unmaj cin,b0,a0;
}
gate mult31 a1,a2,a3,b1,c1,c2,c3{ 
ccx a1,b1,c1;
ccx a2,b1,c2;
ccx a3,b1,c3;
}
qreg carry[2];
creg ans[6];
qreg psum1[5];
qreg psum2[5];
qreg q1[4];
x q1[0];
x q1[1];
qreg q2[4];
x q2[1];
	//-----------MULTIPLICATION ROUTINE START--------------
mult31 q1[0],q1[1],q1[2],q2[0],psum1[0],psum1[1],psum1[2];
mult31 q1[0],q1[1],q1[2],q2[1],psum2[1],psum2[2],psum2[3];
add5 psum1[0],psum1[1],psum1[2],psum1[3],psum1[4],psum2[0],psum2[1],psum2[2],psum2[3],psum2[4],carry[0],carry[1];
reset psum1;
reset carry[0];
reset carry[1];
mult31 q1[0],q1[1],q1[2],q2[2],psum1[2],psum1[3],psum1[4];
add5 psum1[0],psum1[1],psum1[2],psum1[3],psum1[4],psum2[0],psum2[1],psum2[2],psum2[3],psum2[4],carry[0],carry[1];
reset psum1;
reset carry[0];
	//-----------MULTIPLICATION ROUTINE END--------------

measure psum2[0] -> ans[0];
measure psum2[1] -> ans[1];
measure psum2[2] -> ans[2];
measure psum2[3] -> ans[3];
measure psum2[4] -> ans[4];
measure carry[1] -> ans[5];
