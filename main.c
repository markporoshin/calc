#include <stdio.h>
#include "list.h"
#include "variable.h"
#include "executer.h"
#include "parser.h"


#define PART_STR 10

errno_t _fgets(FILE * f, char **str)
{
    int i = 0;
    char c, *buf;
    *str = malloc(sizeof(char) * 0);
    c = (char)fgetc(f);
    while (!feof(f) && c != '\n')
    {
        if ((i + 1) % PART_STR == 0)
        {
            if((buf = realloc(*str, (i + 1 + PART_STR) * sizeof(char))) != NULL)
                *str = buf;
            else
                return E_MEMORY;

        }
        (*str)[i++] = c;
        c = (char)fgetc(f);
    }
    if (feof(f))
        return END_OF_FILE;
    if (i % 100 == 0)
    {
        if((buf = realloc(*str, (i+2) * sizeof(char))) != NULL)
            *str = buf;
        else
            return E_MEMORY;

    }
    (*str)[i++] = '\n';


    return DEFAULT;
}


void Procces(FILE * in, FILE * out)
{
    int eof = 0;
    double res;
    list *l = NULL;
    list *vars = NULL;
    list *pol = NULL;
    variable e = {"e", 1, (double)2.7182818284590452353602874713527};
    variable pi = {"pi", 1, (double)3.1415926535897932384626433832795};
    push(&vars, &e);
    push(&vars, &pi);
    char *buf;

    _fgets(in, &buf);
    while( l == NULL && pol == NULL &&  eof != 2) {
        parser(&l, &vars, buf, out);
        pol = interpreter(&l, out);
        if (pol != NULL)
        {
            if (executer(&pol, &res, out) == 0)
                fprintf(out, " == %lf\n", res);
        }
        free(buf);
        //printList(vars, printVar, out);
        if(_fgets(in, &buf)==END_OF_FILE)
            eof++;
    }
}


int main() {
    int i;
    FILE * input = fopen("/Users/mark/CLionProjects/calc/input.txt", "r");
    FILE * output = fopen("/Users/mark/CLionProjects/calc/output.txt", "w");
    Procces(input, output);
    //Procces(stdin, stdout);
    fclose(input);
    fclose(output);
    return 0;
}

