#include <stdio.h>


void init(FILE *f){
    fprintf(f, "section .data\n");
    fprintf(f, "array times 30000 db 0\n");
    fprintf(f, "section .text\n");
    fprintf(f, "global _start\n");
    fprintf(f, "_start:\n");
    fprintf(f, "mov r9, array\n");
}


void finish(FILE *f){
    fprintf(f, "mov rax, 60\n");
    fprintf(f, "mov rdi, 0\n");
    fprintf(f, "syscall");
}

void genBuildScript(){
    FILE *f = fopen("build.sh", "wr");
    fprintf(f, "nasm *.asm -f elf64\nld *.o");
    fclose(f);
}

