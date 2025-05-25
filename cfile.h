#include <stdio.h>

void initCFile(FILE *file){
    fprintf(file, "#include <stdio.h>\n#include <stdlib.h>\n");
    fprintf(file, "int main(int argc, char **argv){\n");
    fprintf(file, "++argv;\n");
    fprintf(file, "char *cells=malloc(30000);\n");
    fprintf(file, "int cell_ptr=0;\n");
}

void finalizeCFile(FILE *file){
    fprintf(file, "cells=0;\n");
    fprintf(file, "free(cells);\n");
    fprintf(file, "return 0;\n");
    fprintf(file, "}");
}

void inc(FILE *file,int value){
    fprintf(file, "*(cells+cell_ptr)+=%i;\n",value);
}

void dec(FILE *file,int value){
    fprintf(file, "*(cells+cell_ptr)-=%i;\n",value);
}

void mvr(FILE *file,int value){
    fprintf(file, "if(cell_ptr==29999){cell_ptr=0;}");
    fprintf(file, "else{cell_ptr+=%i;}\n",value);
}

void mvl(FILE *file,int value){
    fprintf(file, "if(cell_ptr==0){cell_ptr=29999;}");
    fprintf(file, "else{cell_ptr-=%i;}\n",value);
}

void handle_input(FILE *file){
    fprintf(file, "if(**argv==0){*(*argv)--;*(cells+cell_ptr)=**argv;}\n");
    fprintf(file, "else{*(cells+cell_ptr)=**argv;*(*argv)++;}\n");
}
