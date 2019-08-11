#include <stdio.h>
#include <dlfcn.h>
#include "fib.h"

#include "directory.h"

void (*print_hello)(void);

int main()
{
	void * dl = dlopen("./lib.so", RTLD_LAZY);
	print_hello = (void (*)())dlsym(dl, "print_hello");
	(*print_hello)();
	printf("Fib(8) = %d\n\n", fib(8));

	Directory dir(".");
	for (auto path : dir.getFiles())
		printf("%s\n", path.c_str());
	return 0;
}
