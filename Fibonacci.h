#ifndef __FIBONACCI_H
#define __FIBONACCI_H

#define INIT_MEMO_SIZE 44

typedef struct Memo
{
	// dynamically allocated HugeInteger array to store our Fibonacci numbers
	struct HugeInteger *F;

	// the current length (i.e., capacity) of this array
	int length;
} Memo;


// Functional Prototypes

Memo *createMemo(void);

int expandMemo(Memo *memo, int n);

Memo *destroyMemo(Memo *memo);

struct HugeInteger *fib(int n, Memo *memo);


#endif
