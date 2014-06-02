#include <stdio.h>
#include <stdlib.h>
#include "HugeInteger.h"

void panic(char *s)
{
	fprintf(stdout, "%s", s);
	exit(1);
}

void HugeAdd(HugeInteger *a, HugeInteger *b, HugeInteger *result)
{
	int i, op1, op2, sum, carry = 0;

	result->length = 1 + ((a->length > b->length) ? a->length : b->length);

	result->digits = malloc(sizeof(int) * result->length);

	for (i = 0; i < result->length; i++)
	{
		op1 = (i < a->length) ? a->digits[i] : 0;
		op2 = (i < b->length) ? b->digits[i] : 0;
		sum = op1 + op2 + carry;
		carry = sum / 10;

		result->digits[i] = sum % 10;
	}

	if (result->digits[result->length - 1] == 0)
		result->length--;
}

void foo(int argc, char **argv)
{
	int i;

	printf("PROGRAM CALL: ");

	for (i = 0; i < argc; i++)
		printf("%s%c", argv[i], (i == argc - 1) ? '\n' : ' ');

	printf("\n");
}
