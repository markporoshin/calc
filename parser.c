//
// Created by Марк on 14.02.18.
//


#include "parser.h"
#include "variable.h"



int prior[] = {6, 1, 1, 2, 2, 3, 10, -10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0};

void printLex(lexeme *l, FILE *output) {
    char name_op[NUM_OF_OP][10] = {"~", "+", "-", "*", "/", "^", "(", ")", "sin", "cos", "ln", "tg", "ctg", "arcsin", "arccos", "arctg", "floor", "ceil", "sqrt", "="};
    switch (l->type) {
        case DIGIT:
            fprintf(output, "%1.0lf", l->value.digit);
            break;
        case OPERATION:
            fprintf(output, "%s", name_op[l->value.action]);
            break;
        case VARIABLE:
            fprintf(output, "%s", l->value.var->name);
            break;
    }
}

int isoper(int c){
    if (c == '+' || c == '-' || c == '^' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=')
        return 1;
    return 0;
}


int parser(list **L, list **vars, char *str, FILE *output)
{
    error er = DEFAULT;
    variable *var;
    list * vars1;
    char name[NUM_OF_FUNC][10] = {"sin", "cos", "ln", "tg", "ctg", "arcsin", "arccos", "arctg", "floor", "ceil", "sqrt"};
    int pow, size = 0, i = 0, j = 0, flag;
    char c, *buf;
    double digit;
    lexeme * l, * buf_l;
    c = str[j];
    do {
        l = malloc(sizeof(lexeme));
        digit = 0;
        if (isalnum(c) || isoper(c)) {
            if (isdigit(c)) {
                l->type = DIGIT;
                while (isdigit(c)) {
                    digit *= 10;
                    digit += c - '0';
                    c = str[++j];
                }
                pow = 1;
                if (c == '.') {
                    c = str[++j];
                    while (isdigit(c)) {
                        digit += (c - '0') / (double)(pow *= 10);
                        c = str[++j];
                    }
                }
                l->value.digit = digit;
            } else if(isoper(c)) {
                l->type = OPERATION;
                switch (c) {
                    case '+':
                        l->value.action = PLUS;
                        break;
                    case '-':
                        if (*L != NULL) {
                            getEl(*L, 0, (void **)&buf_l);
                            if (buf_l->type== DIGIT || (buf_l->type == OPERATION && buf_l->value.action == CBKT) )
                                l->value.action = MINUS;
                            else if (buf_l->type == OPERATION && (buf_l->value.action >= SIN))
                                l->value.action = MINUS;
                            else
                                l->value.action = U_MINUS;
                        } else
                            l->value.action = U_MINUS;
                        break;
                    case '*':
                        l->value.action = MULTI;
                        break;
                    case '/':
                        l->value.action = RATIO;
                        break;
                    case '^':
                        l->value.action = POWER;
                        break;
                    case '(':
                        l->value.action = OBKT;
                        break;
                    case ')':
                        l->value.action = CBKT;
                        break;
                    case '=':
                        l->value.action = EQUATE;
                        break;
                }
                c = str[++j];
            } else {
                size = 1;
                buf = malloc(sizeof(char) * size);
                while (!isdigit(c) && !isoper(c) && c != ' ' && c != '\n' && c != '\0') {
                    if(realloc(buf, size * sizeof(char)) == NULL) {
                        printf("Error: memory error");
                        exit(1);
                    }
                    buf[size - 1] = c;
                    c = str[++j];
                    size++;
                }
                flag = 0;
                if (strcmp(buf, "Z^") == 0)
                    return 0;
                for (i = 0; i < NUM_OF_FUNC && !flag; i++)
                    if (strcmp(buf, name[i]) == 0)
                        flag = 1;
                if (flag) {
                    l->type = OPERATION;
                    l->value.action = i - 1 + SIN;
                } else {
                    vars1 = *vars;
                    for (;vars1 != NULL; vars1 = vars1->next) {
                        var = (variable *)vars1->data;
                        if (strcmp(buf, var->name) == 0) {
                            l = malloc(sizeof(lexeme));
                            l->type = VARIABLE;
                            l->value.var = var;
                            flag = 1;
                        }
                    }
                    if(!flag) {
                        var = malloc(sizeof(variable));
                        var->name = malloc(sizeof(char) * (size-1));
                        memcpy(var->name, buf, size-1);
                        var->isFill = 0;
                        l = malloc(sizeof(lexeme));
                        l->type = VARIABLE;
                        l->value.var = var;
                        push(vars, var);
                    }
                }
                free(buf);
                buf = NULL;
            }
            er = push(L, l);
        } else {
            if (!isspace(c) && c != '\0' && c != '\n') {
                er = E_FORBADE_SYM;
                break;
            }
            c = str[++j];
        }

    } while(c != '\n' && c != '\0');
    printReList(*L, printLex, output);
    if (er != DEFAULT) {
        printError(er,output);
        delList(L);
    }
    return er;
}