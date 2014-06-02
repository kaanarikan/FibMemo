//Kaan Arikan
//Professor Sean Szumlanski
//23 June 2013
//Assignmen #2

#include "Fibonacci.h"
#include "HugeInteger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Memo *createMemo(void)
{
    int i;
    Memo *rValue;

    rValue = (Memo *)malloc(sizeof(Memo));
    if(rValue == 0)
        panic("ERROR: out of memory in createMemo()\n");

    rValue->F = (HugeInteger*) malloc (INIT_MEMO_SIZE * sizeof(HugeInteger));

    if(rValue->F == 0)
        panic("ERROR: out of memory in createMemo()\n");

    rValue->length = INIT_MEMO_SIZE;

    HugeInit(&(rValue->F[0]), 0);
    HugeInit(&(rValue->F[1]), 1);
    for(i=2; i<rValue->length; i++)
    {
        rValue->F[i].digits = 0;
        rValue->F[i].length = 0;
    }

    return rValue;
}

int expandMemo(Memo *memo, int n)
{
    int i;
    int newLength = 2*n + 1;
    struct HugeInteger* newArray;

    if(n < memo->length)
        newLength = 2*memo->length + 1;
    newArray = (HugeInteger*) malloc (newLength * sizeof(HugeInteger));
    if(newArray == 0)
        panic("ERROR: out of memory in expandMemo()\n");

    memcpy(newArray, memo->F, memo->length * sizeof(HugeInteger));
    for(i=memo->length; i<newLength; i++)
    {
        newArray[i].digits = 0;
        newArray[i].length = 0;
    }

    free(memo->F);
    memo->F = newArray;
    memo->length = newLength;

    printf("-> Expanded memo capacity to %d.\n", memo->length);
    return memo->length;
}

Memo *destroyMemo(Memo *memo)
{
    int i;
    if(memo == 0)
        return 0;

    for(i=0; i<memo->length; i++)
        if(memo->F[i].digits != 0)
            free(memo->F[i].digits);
    free(memo->F);
    return 0;
}

struct HugeInteger *fib(int n, Memo *memo)
{
    if(n >= memo->length)
        expandMemo(memo, n);

    if(n<0)
        return 0;

    if (memo->F[n].length != 0)
        return &(memo->F[n]);

    // these calls ensure that F(n-1) and F(n-2) end up in memo
    fib(n-1, memo);
    fib(n-2, memo);

    // we’re now ready to compute this result and store it in memo
    HugeAdd(&(memo->F[n-1]), &(memo->F[n-2]), &(memo->F[n]));
    return &(memo->F[n]);
}

void HugePrint(HugeInteger *p)
{
    int i;
    if(p == 0)
        printf("(undefined)\n");
    else
    {
        for(i=p->length-1; i>=0; i--)
            printf("%d", p->digits[i]);
        printf("\n");
    }

}

int HugeInit(HugeInteger *p, int n)
{
    if(p == 0 || n<0 || n>9)
        return 0;
    p->length = 1;
    p->digits = (int *)malloc(p->length * sizeof(int));
    if(p->digits == 0)
    {
        panic("ERROR: out of memory in HugeInit()\n");
        return 0;
    }
    p->digits[0] = n;
    return 1;
}

int main(int argc, char **argv)
{
    int i;
    Memo* memory;
    struct HugeInteger* result;

    foo(argc, argv);

    if(argc<2)
        return 0;

    memory = createMemo();
    for(i=1; i<argc; i++)
    {
        result = fib(atoi(argv[i]), memory);
        printf("F(%s): ", argv[i]);
        HugePrint(result);
    }
    destroyMemo(memory);
    return 0;
}
