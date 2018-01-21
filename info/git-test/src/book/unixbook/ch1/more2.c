/*
 * more2.c
 * in case of "ll /usr/bin | more2", argc == 1, and more(stdin).
 * meanwhile, user's choice come from keyboard(/dev/tty), so in
 * order to get user's input, we need fopen("/dev/tty", "r")
 */

#include <stdio.h>
#include <stdlib.h>

#define LINE 256
#define PAGE 24
/**
 *  /dev/tty
 */
int get_choice(){
	FILE *fp_tty;
	char ch;

	if((fp_tty = fopen("/dev/tty", "r")) == NULL){
		perror("ERROR: open /dev/tty failure.");
		exit(1);
	}

	while((ch = fgetc(fp_tty)) != EOF){
		if(ch == 'q')
			return 0;
		else if(ch == ' ')
			return PAGE;
		else if(ch == '\n')
			return 1;
	}
	return 0;
}

void more(FILE *fp){
	char line[LINE];
	int count;

	count = 0;
	while(fgets(line, LINE, fp) != NULL){
		if(count == PAGE){
			printf("[continue]?");
			int rt = get_choice();
			if(rt == 0)
				break;
			else if(rt == 1)
				count--;
			else if(rt == PAGE)
				count = 0;
		}
		fputs(line, stdout);
		count++;
	}
}

/**
 *  #include <stdio.h>
     extern FILE *stdin;
     extern FILE *stdout;
     extern FILE *stderr;
 */
int main(int argc, char **argv){
	int i;
	FILE *fp;

	if(argc == 1){
		more(stdin);
	}else{
		for(i = 1; i < argc; i++){
			if((fp =  fopen(argv[i], "r")) == NULL){
				perror("ERROR: open file failure.");
				exit(1);
			}
			more(fp);
			fclose(fp);
		}
	}
	return 0;
}
