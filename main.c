#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cfile.h"
#include <stdint.h>

int main(int argc, char **argv){
    if(argc<3){
        printf("Invalid Usage!");
        argv++;
        printf("%c", *(*argv+1));
        exit(1);
    }


    FILE *f = fopen(argv[1], "r");
    FILE *outFile = fopen(argv[2], "w");
    initCFile(outFile);

    char curchar=1;

    int lcount=0;
    
    while(curchar!=EOF){
	curchar = fgetc(f);
        switch(curchar){
            case '+':
                inc(outFile);
                break;
            case '-':
                dec(outFile);
                break;
            case '>':
                mvr(outFile);
                break;
            case '<':
                mvl(outFile);
                break;
            case '[':
		fprintf(outFile, "cmp byte [r9], 0\n");
		fprintf(outFile, "jz le%d\n",lcount);
		fprintf(outFile, "jmp ls%d\n",lcount);
		fprintf(outFile, "ls%d:\n",lcount);
		lcount++;
                break;
            case ']':
                lcount--;
		fprintf(outFile, "cmp byte [r9], 0\n");
		fprintf(outFile, "jz le%d\n",lcount);
		fprintf(outFile, "jmp ls%d\n",lcount);
		fprintf(outFile, "le%d:\n",lcount);
                break;
            case '.':
                fprintf(outFile, "mov rax, 1\n");
		fprintf(outFile, "mov rdi, 1\n");
		fprintf(outFile, "mov rsi, r9\n");
		fprintf(outFile, "mov rdx, 1\n");
		fprintf(outFile, "syscall\n");
                break;
            case ',':
                //handle_input(outFile);
                break;
        }
    }

    finalizeCFile(outFile);
    fclose(outFile);
    
    fclose(f);


    return 0;
}
