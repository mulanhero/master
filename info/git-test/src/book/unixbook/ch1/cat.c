/*
 * more.c
 *
 *  Created on: Nov 16, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define LINE 256

/**
 * #include <stdio.h>
       size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
       size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
 */
void cat1(FILE *fp){
	char line[LINE];
	size_t length;

	while((length = fread(line, 1, LINE, fp)) != 0){
		fwrite(line, 1, length, stdout);
		//instead, if use puts, then the line should end with '\0'
//		line[e_num] = '\0';
//		puts(line);
	}
}

/**
 * #include <stdio.h>
       char *fgets(char *s, int size, FILE *stream);
       int ungetc(int c, FILE *stream);
 *
 * #include <stdio.h>
       int fputs(const char *s, FILE *stream);
 */
void cat2(FILE *fp){
	char line[LINE];
	char *ln;

	while((ln = fgets(line, LINE, fp)) != NULL){
		fputs(line, stdout);
	}
}

/**
	int fgetc(FILE *stream);
	int getc(FILE *stream);

	int fputc(int c, FILE *stream);
	int putc(int c, FILE *stream);
 */
void cat3(FILE *fp){
	int ch;
	while((ch = getc(fp)) != EOF){
		putc(ch, stdout);
	}
}


/**
 *
       int getchar(void);
       int putchar(int c);
 */
void my_echo_char(){
	int ch;
	while((ch = getchar()) != EOF)
		putchar(ch);
}

/**
 * char *gets(char *s); //Never use gets()
 * int puts(const char *s);
 */

/**
 * #include <stdio.h>

       FILE *fopen(const char *path, const char *mode);
       FILE *fdopen(int fildes, const char *mode);
       FILE *freopen(const char *path, const char *mode, FILE *stream);
 *
 * #include <stdio.h>

       int fclose(FILE *fp);
 */
int main(int argc, char **argv){
	FILE *fp;
	int i;

	if(argc < 2){
		perror("ERROR: file is not specified.");
		exit(1);
	}

	for(i = 0; i < argc; i++)
		puts(argv[i]);

	//argv[0] is the ./cat
	for(i = 1; i < argc; i++){
//		puts(argv[i]);
		if((fp = fopen(argv[i], "r")) == NULL){
			perror("ERROR: fopen");
			exit(1);
		}
		puts("============================================");
//		cat1(fp);
		cat2(fp);
//		cat3(fp);
		puts("============================================");
		fclose(fp);
	}

	puts("===============now let's echo:");
	my_echo_char();

	return 0;
}
