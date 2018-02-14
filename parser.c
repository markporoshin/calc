//
// Created by Марк on 14.02.18.
//


#include "parser.h"
#include "variable.h"


void printLex(lexeme * l) {
    char name_op[19][10] = {"~","+", "-", "*", "/", "^", "(", ")", "sin", "cos", "ln", "tg", "ctg", "arcsin", "arccos", "arctg", "floor", "ceil", "sqrt"};
    switch (l->type) {
        case DIGIT:
            printf("%lf", l->value.digit);
            break;
        case OPERATION:
            printf("%s", name_op[l->value.action]);
            break;
    }
}

int isoper(int c){
    if (c == '+' || c == '-' || c == '^' || c == '*' || c == '/' || c == '(' || c == ')')
        return 1;
    return 0;
}

void parser(list *L, list *vars)
{
    variable *var;
    list * vars1;
    char name[11][10] = {"sin", "cos", "ln", "tg", "ctg", "arcsin", "arccos", "arctg", "floor", "ceil", "sqrt"};
    int pow, size = 0, i = 0, j = 0, flag;
    char c, *buf;
    double digit;
    lexeme * l, * buf_l;
    scanf("%c", &c);
    do {
        l = malloc(sizeof(lexeme));
        digit = 0;
        if (isalnum(c) || isoper(c)) {
            if (isdigit(c)) {
                l->type = DIGIT;
                while (isdigit(c)) {
                    digit *= 10;
                    digit += c - '0';
                    scanf("%c", &c);
                }
                pow = 1;
                if (c == '.') {
                    scanf("%c", &c);
                    while (isdigit(c)) {
                        digit += (c - '0') / (double)(pow *= 10);
                        scanf("%c", &c);
                    }
                }
                l->value.digit = digit;
                //printLex(l);
                push(&L, l);
            } else if(isoper(c)) {
                l->type = OPERATION;
                switch (c) {
                    case '+':
                        l->value.action = PLUS;
                        break;
                    case '-':
                         if (L != NULL) {
                             getEl(L, 0, (void **)&buf_l);
                             if (buf_l->type == DIGIT)
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
                }
                //printLex(l);
                push(&L, l);
                scanf("%c", &c);
            } else {
                size = 1;
                buf = malloc(sizeof(char) * size);
                while (!isdigit(c) && !isoper(c)) {
                    if(realloc(buf, size * sizeof(char)) == NULL) {
                        printf("Error: memory error");
                        exit(1);
                    }
                    buf[size - 1] = c;
                    scanf("%c", &c);
                    size++;
                }
                flag = 0;
                for (i = 0; i < 11 && !flag; i++)
                    if (strcmp(buf, name[i]) == 0)
                        flag = 1;
                if (flag) {
                    l->type = OPERATION;
                    l->value.action = i - 1 + SIN;
                } else {
                    vars1 = vars;
                    for (;vars1 != NULL; vars1 = vars1->next) {
                        var = (variable *)vars1->data;
                        if (strcmp(buf, var->name) == 0) {
                            l = malloc(sizeof(lexeme));
                            l->type = DIGIT;
                            l->value.digit = var->value;
                            push(&L, l);
                        }

                    }
                }
                push(&L, l);
                free(buf);
            }
            //printf("%c", c);
        } else
            scanf("%c", &c);
    } while(c != '\n' && c != '\0');
    printReList(L, (void *)printLex);
}