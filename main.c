#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

    uint32_t count = 0;
    uint8_t shouldExit = 0;
    char curchar=1;
    
    while(curchar!=EOF){
	curchar = fgetc(f);
        switch(curchar){
            case '+':
                inc(outFile, 1);
                break;
            case '-':
                dec(outFile, 1);
                break;
            case '>':
                mvr(outFile, 1);
                break;
            case '<':
                mvl(outFile, 1);
                break;
            case '[':
                fprintf(outFile, "while(*(cells+cell_ptr)!=0){\n");
                break;
            case ']':
                fprintf(outFile, "}\n");
                break;
            case '.':
                fprintf(outFile, "putc(*(cells+cell_ptr), stdout);\n");
                break;
            case ',':
                handle_input(outFile);
                break;
        }
    }

    finalizeCFile(outFile);
    fclose(outFile);
    
    fclose(f);


    return 0;
}
