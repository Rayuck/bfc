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

void inc(FILE *file, int value){
    fprintf(file, "add byte [r9], %d\n", value);
}

void dec(FILE *file, int value){
    fprintf(file, "sub byte [r9], %d\n", value);
}

void mvr(FILE *file, int value){
    fprintf(file, "add r9, %d\n", value);
}

void mvl(FILE *file, int value){
    fprintf(file, "sub r9, %d\n", value);
}

/*
void handle_input(FILE *file){
    fprintf(file, "if(**argv==0){*(*argv)--;*cells=**argv;}\n");
    fprintf(file, "else{*cells=**argv;*(*argv)++;}\n");
}
*/
