#include <stdio.h>
#include <stdlib.h>

#define LINECHAR 256
#define MAXLINE 25

int get_choice(){
	char ch;
	puts("[more?]");
	while((ch = getchar()) != EOF){
		if(ch == 'q')
			return 0;
		else if(ch == '\n')
			return 1;
		else if(ch == ' ')
			return MAXLINE;
	}
	return 0;
}


void more(FILE *fp){
	char line[LINECHAR];
	char *ln;
	int i;
	char ch;

	i = 0;
	while((ln = fgets(line, LINECHAR, fp)) != NULL){ //while(fgets(line, LINECHAR,fp))
		fputs(line, stdout);
		i++;
		if(i >= MAXLINE -1){
			int rt;
			rt = get_choice();
			if(rt == 0)
				break;
			else if(rt == MAXLINE)
				i = 0;
			else if(rt == 1)
				;
		}
	}
}

int main(int argc, char **argv){
	int i;
	FILE *fp;

	if(argc == 1){
		more(stdin);
	}else{
		for(i = 1; i < argc; i++){
			if((fp = fopen(argv[i], "r")) == NULL){
				perror("ERROR: file open failure.");
				exit(1);
			}
			more(fp);
			fclose(fp);
		}
	}
	return 0;
}
