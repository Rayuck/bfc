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
    

    char curchar;
    int fsize=0;

    uint32_t count = 0;
    uint8_t shouldExit = 0;

    // init f & reset pointer offset //
    fgetc(f);
    f->_IO_read_ptr--;
    
    while(*f->_IO_read_ptr!=0){
        switch(*f->_IO_read_ptr){
            case '+':
                ++f->_IO_read_ptr;
                count = 1;
                shouldExit=0;
                while(shouldExit==0){
                    switch(*f->_IO_read_ptr){
                        case '+':
                            ++count;
                            ++f->_IO_read_ptr;
                            break;
                        case ' ':
                            ++f->_IO_read_ptr;
                            break;
                        case '\n':
                            ++f->_IO_read_ptr;
                            break;
                        case '\t':
                            ++f->_IO_read_ptr;
                            break;
                        default:
                            shouldExit=1;
                            break;
                    }
                }
                inc(outFile, count);
                --f->_IO_read_ptr;
                break;
            case '-':
                ++f->_IO_read_ptr;
                count = 1;
                shouldExit=0;
                while(shouldExit==0){
                    switch(*f->_IO_read_ptr){
                        case '-':
                            ++count;
                            ++f->_IO_read_ptr;
                            break;
                        case ' ':
                            ++f->_IO_read_ptr;
                            break;
                        case '\n':
                            ++f->_IO_read_ptr;
                            break;
                        case '\t':
                            ++f->_IO_read_ptr;
                            break;
                        default:
                            shouldExit=1;
                            break;
                    }
                }
                dec(outFile, count);
                --f->_IO_read_ptr;
                break;
            case '>':
                ++f->_IO_read_ptr;
                count = 1;
                shouldExit=0;
                while(shouldExit==0){
                    switch(*f->_IO_read_ptr){
                        case '>':
                            ++count;
                            ++f->_IO_read_ptr;
                            break;
                        case ' ':
                            ++f->_IO_read_ptr;
                            break;
                        case '\n':
                            ++f->_IO_read_ptr;
                            break;
                        case '\t':
                            ++f->_IO_read_ptr;
                            break;
                        default:
                            shouldExit=1;
                            break;
                    }
                }
            mvr(outFile, count);
                --f->_IO_read_ptr;
                break;
            case '<':
                ++f->_IO_read_ptr;
                count = 1;
                shouldExit=0;
                while(shouldExit==0){
                    switch(*f->_IO_read_ptr){
                        case '<':
                            ++count;
                            ++f->_IO_read_ptr;
                            break;
                        case ' ':
                            ++f->_IO_read_ptr;
                            break;
                        case '\n':
                            ++f->_IO_read_ptr;
                            break;
                        case '\t':
                            ++f->_IO_read_ptr;
                            break;
                        default:
                            shouldExit=1;
                            break;
                    }
                }
                mvl(outFile, count);
                --f->_IO_read_ptr;
                break;
            case '[':
                fprintf(outFile, "while(*cells!=0){\n");
                break;
            case ']':
                fprintf(outFile, "}\n");
                break;
            case '.':
                fprintf(outFile, "putc(*cells, stdout);\n");
                break;
            case ',':
                handle_input(outFile);
                break;
        }
        ++f->_IO_read_ptr;
    }

    finalizeCFile(outFile);
    fclose(outFile);
    
    fclose(f);


    return 0;
}