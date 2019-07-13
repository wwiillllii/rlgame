#include <stdio.h>
#include <dlfcn.h>
#include "fib.h"

void (*print_hello)(void);

int main()
{
	void * dl = dlopen("./lib.so", RTLD_LAZY);
	print_hello = dlsym(dl, "print_hello");
	(*print_hello)();
	printf("Fib(8) = %d\n", fib(8));
	return 0;
}
