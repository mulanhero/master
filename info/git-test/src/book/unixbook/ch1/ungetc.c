/*
 * ungetc.c
 *
 *  Created on: Nov 19, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * #include <stdio.h>
   void clearerr(FILE *stream);
   int feof(FILE *stream);
   int ferror(FILE *stream);
   int fileno(FILE *stream);
*/

/**
 * int ungetc(int c, FILE *stream);
 * ungetc() pushes c back to stream, cast to unsigned char,
 * where it  is  available  for  subsequent  read  operations.
 */
int main(int argc, char **argv){
	FILE *fp;
	int count = 0;
	if((fp = fopen(argv[1], "rt")) == NULL){ //'t' means text, not binary
		perror("ERROR: fopen");
		exit(1);
	}

	while(!feof(fp)){
		char ch = getc(fp);
		if(ch == 'x'){
//			putc(ch, stdout);
			ungetc(ch, fp);

			char str[5];
			fgets(str, 5, fp); //fgets will read n-1 chars, and add '\0' at the end
//			printf("str=%s\n", str);
			if(strcmp(str, "xian") == 0)
				count++;
		}
	}

	fclose(fp);

	printf("xian appears %d times in  file %s\n", count, argv[1]);
	return 0;
}
