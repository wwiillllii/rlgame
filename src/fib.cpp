#include "fib.h"

unsigned int fib(unsigned int n)
{
	if (n < 2) return 1;
	return fib(n-1) + fib(n-2);
}
