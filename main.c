#include <stdio.h>
#include <stdlib.h>
#include "cfile.h"

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

    char curchar=0;

    int lcount=0;
    while(curchar!=EOF){
        curchar = fgetc(f);
        if(curchar=='[') lcount++;
        else if (curchar==']') lcount++;
    }
    int *lstack = malloc(sizeof(int)*lcount);
    rewind(f);
    curchar=0;
	lcount=0;
    int i;
    while(curchar!=EOF){
	curchar = fgetc(f);
        switch(curchar){
            case '+':
                i=1;
                while(*f->_IO_read_ptr=='+'){
                    i++;
                    f->_IO_read_ptr++;
                }
                inc(outFile, i);
                break;
            case '-':
                i=1;
                while(*f->_IO_read_ptr=='-'){
                    i++;
                    f->_IO_read_ptr++;
                }
                dec(outFile, i);
                break;
            case '>':
                i=1;
                while(*f->_IO_read_ptr=='>'){
                    i++;
                    f->_IO_read_ptr++;
                }
                mvr(outFile, i);
                break;
            case '<':
                i=1;
                while(*f->_IO_read_ptr=='<'){
                    i++;
                    f->_IO_read_ptr++;
                }
                mvl(outFile, i);
                break;
            case '[':
                if(
                    *f->_IO_read_ptr=='-'&&
                    *(f->_IO_read_ptr+1)==']'
                    ){
                        fprintf(outFile, "mov byte [r9], 0\n");
                        f->_IO_read_ptr+=2;
                        break;
                    }
				lcount++;
				*lstack = lcount;
				lstack++;
		        fprintf(outFile, "cmp byte [r9], 0\n");
		        fprintf(outFile, "jz le%d\n",*(lstack-1));
		        fprintf(outFile, "ls%d:\n",*(lstack-1));
                break;
            case ']':
		        fprintf(outFile, "cmp byte [r9], 0\n");
		        fprintf(outFile, "jnz ls%d\n",*(lstack-1));
		        fprintf(outFile, "le%d:\n",*(lstack-1));
				lstack--;
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
    free(lstack);


    return 0;
}