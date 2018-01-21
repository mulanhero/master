#include <stdio.h>
#include <dlfcn.h> /* for "dlopen" */
#include <stdlib.h> /* for "system" */

int some_symbol;

int main() 
{
	/* Write some code at runtime */
	FILE *code=fopen("code.c","w");
	fprintf(code,"#include <stdio.h>\n"
	"void funkyfunc(void) {printf(\"Hello, World!\\n\");}\n");
	fclose(code);				
	/* Compile the new code */
	system("gcc -shared code.c -o code.so; rm code.c");
	{ /* Open the freshly-compiled shared library and run it */
	void *lib=dlopen("./code.so",RTLD_LAZY);
	typedef void (*void_fn_t)(void);
	void_fn_t func=(void_fn_t)dlsym(lib,"funkyfunc");
	func();
	}	
	return 0;
}
