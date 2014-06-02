#ifndef __HUGEINTEGER_H
#define __HUGEINTEGER_H

typedef struct HugeInteger
{
	// a dynamically allocated array to hold the digits of a huge integer
	int *digits;

	// the length of the array (i.e., number of digits in the huge integer)
	int length;
} HugeInteger;


// Functional Prototypes

void HugeAdd(HugeInteger *a, HugeInteger *b, HugeInteger *result);

void HugePrint(HugeInteger *p);

int HugeInit(HugeInteger *p, int n);

void panic(char *s);

void foo(int argc, char **argv);


#endif
