
#include <reg51.h>

char A;
main()
{
    A=P1;
	B=P2;
	A=A+B;
	P3=PSW;          //c ac f0 rs1 rs0 ov . p 
	}