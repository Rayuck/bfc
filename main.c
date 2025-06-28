#include <stdio.h>
#include <stdlib.h>
#include "assembly.c"


int main(int argc, char **argv){

    FILE *f = fopen(*(argv+1), "r");

    fseek(f, 0, SEEK_END);
    int fsize = ftell(f);
    rewind(f);

    char *bfContent = calloc(fsize, sizeof(char));
    int bfSize=0;

    char cur;
    while((cur=getc(f))!=EOF){
        switch(cur){
            case '+':
                *(bfContent+bfSize)='+';
                bfSize++;
                break;
            case '-':
                *(bfContent+bfSize)='-';
                bfSize++;
                break;
            case '.':
                *(bfContent+bfSize)='.';
                bfSize++;
                break;
            case ',':
                *(bfContent+bfSize)=',';
                bfSize++;
                break;
            case '[':
                *(bfContent+bfSize)='[';
                bfSize++;
                break;
            case ']':
                *(bfContent+bfSize)=']';
                bfSize++;
                break;
            case '>':
                *(bfContent+bfSize)='>';
                bfSize++;
                break;
            case '<':
                *(bfContent+bfSize)='<';
                bfSize++;
                break;
            
        }
    }
    fclose(f);
    FILE *asmF = fopen("main.asm", "w");

    int *stack=malloc(sizeof(int)*512);
    int stackIndex=0;
    int loopCount=0;

    init(asmF);

    for(int i=0;i<bfSize;i++){
        switch(*(bfContent+i)){
            case '+': {
                if(*(bfContent+i-1)=='['&&*(bfContent+i+1)==']'){
                    fprintf(asmF, "mov byte [r9], 0\n");
                    break;
                }
                if(*(bfContent+i+1)=='+'){
                    int j=0;
                    while(*(bfContent+i+j)=='+'){
                        j++;
                    }
                    fprintf(asmF, "add byte [r9], %i\n",j);
                    i+=j-1;
                    break;
                }
                if(*(bfContent+i+1)!='-'){
                    fprintf(asmF, "inc byte [r9]\n");
                    break;
                }
            }
                

            case '-': {
                if(*(bfContent+i-1)=='['&&*(bfContent+i+1)==']'){
                    fprintf(asmF, "mov byte [r9], 0\n");
                    break;
                }
                if(*(bfContent+i+1)=='-'){
                    int j=0;
                    while(*(bfContent+i+j)=='-'){
                        j++;
                    }
                    fprintf(asmF, "sub byte [r9], %i\n",j);
                    i+=j-1;
                    break;
                }
                if(*(bfContent+i+1)!='-'){
                    fprintf(asmF, "dec byte [r9]\n");
                    break;
                }
            }

            case '>': {
                if(*(bfContent+i+1)=='>'){
                    int j=0;
                    while(*(bfContent+i+j)=='>'){
                        j++;
                    }
                    fprintf(asmF, "add r9, %i\n",j);
                    i+=j-1;
                    break;
                }
                if(*(bfContent+i+1)!='>'){
                    fprintf(asmF, "inc r9\n");
                    break;
                }
            }

            case '<': {
                if(*(bfContent+i+1)=='<'){
                    int j=0;
                    while(*(bfContent+i+j)=='<'){
                        j++;
                    }
                    fprintf(asmF, "sub r9, %i\n",j);
                    i+=j-1;
                    break;
                }
                if(*(bfContent+i+1)!='<'){
                    fprintf(asmF, "dec r9\n");
                    break;
                }
            }

            case '.': {
                fprintf(asmF, "mov rax, 1\n");
                fprintf(asmF, "mov rdi, 1\n");
                fprintf(asmF, "mov rsi, r9\n");
                fprintf(asmF, "mov rdx, 1\n");
                fprintf(asmF, "syscall\n");
                break;
            }
            
            case '[': {
                stackIndex++;
                *(stack+stackIndex) = loopCount;
                fprintf(asmF, "cmp byte [r9], 0\n");
                fprintf(asmF, "je loopEnd_%i\n",*(stack+stackIndex));
                fprintf(asmF, "loopStart_%i:\n",*(stack+stackIndex));
                loopCount++;
                break;
            }

            case ']': {
                fprintf(asmF, "cmp byte [r9], 0\n");
                fprintf(asmF, "jne loopStart_%i\n", *(stack+stackIndex));
                fprintf(asmF, "loopEnd_%i:\n", *(stack+stackIndex));
                stackIndex--;
                break;
            }

                
        }
    }
    

    finish(asmF);

    free(stack);
    free(bfContent);
    return 0;
}