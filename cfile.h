#include <stdio.h>

void initCFile(FILE *file){
    fprintf(file, "section .data\narray times 30000 db 0\n");
    fprintf(file, "section .text\nglobal _start\n");
    fprintf(file, "_start:\n");
    fprintf(file, "mov r9, array\n");
}

void finalizeCFile(FILE *file){
    fprintf(file, "mov rax, 60\n");
    fprintf(file, "mov rdi, 0\n");
    fprintf(file, "syscall\n");
}

void inc(FILE *file){
    fprintf(file, "inc byte [r9]\n");
}

void dec(FILE *file){
    fprintf(file, "dec byte [r9]\n");
}

void mvr(FILE *file){
    fprintf(file, "inc r9\n");
}

void mvl(FILE *file){
    fprintf(file, "dec r9\n");
}

/*
void handle_input(FILE *file){
    fprintf(file, "if(**argv==0){*(*argv)--;*cells=**argv;}\n");
    fprintf(file, "else{*cells=**argv;*(*argv)++;}\n");
}
*/
