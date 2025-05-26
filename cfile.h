#include <stdio.h>

void initCFile(FILE *file){
    fprintf(file, "#include <stdio.h>\n#include <stdlib.h>\n");
    fprintf(file, "int main(int argc, char **argv){\n");
    fprintf(file, "++argv;\n");
    fprintf(file, "char *cells=malloc(30000);\n");
    fprintf(file, "char *c_end=cells+29999;\n");
    fprintf(file, "char *c_start=cells;\n");
}

void finalizeCFile(FILE *file){
    fprintf(file, "cells=c_start;\n");
    fprintf(file, "free(cells);\n");
    fprintf(file, "return 0;\n");
    fprintf(file, "}");
}

void inc(FILE *file,int value){
    fprintf(file, "*cells+=%i;\n",value);
}

void dec(FILE *file,int value){
    fprintf(file, "*cells-=%i;\n",value);
}

void mvr(FILE *file,int value){
    fprintf(file, "if(cells==c_end){cells-=29999;}");
    fprintf(file, "else{cells+=%i;}\n",value);
}

void mvl(FILE *file,int value){
    fprintf(file, "if(cells==c_start){cells+=29999;}");
    fprintf(file, "else{cells-=%i;}\n",value);
}

void handle_input(FILE *file){
    fprintf(file, "if(**argv==0){*(*argv)--;*cells=**argv;}\n");
    fprintf(file, "else{*cells=**argv;*(*argv)++;}\n");
}
