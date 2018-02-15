#include <stdio.h>
#include "list.h"
#include "variable.h"
#include "executer.h"

int main() {
    list *l = NULL;
    list *vars = NULL;

    variable e = {"e", 1, (double)2.7182818284590452353602874713527};
    variable pi = {"pi", 1, (double)3.1415926535897932384626433832795};
    push(&vars, &e);
    push(&vars, &pi);
    parser(&l, &vars);
    printf("\n");
    interpreter(l);
    return 0;
}