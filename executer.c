//
// Created by Марк on 14.02.18.
//

#include <math.h>
#include <float.h>
#include "executer.h"
#include "parser.h"
#include "variable.h"


list * interpreter(list **inf, FILE * output) {
    int bp = 0;
    list *pol = NULL;
    list *op = NULL;
    lexeme *buf = NULL, *buf1 = NULL;
    while(*inf != NULL) {
        buf = (lexeme *)popBack(inf);
        switch (buf->type) {
            case VARIABLE:
            case DIGIT:
                push(&pol, buf);
                break;
            case OPERATION:
                if (buf->value.action == OBKT || buf->value.action == CBKT)
                    bp += prior[buf->value.action];
                else {
                    buf->bp = bp;
                    if (op == NULL)
                        push(&op, buf);
                    else {
                        getEl(op, 0, (void **) &buf1);

                        while (op != NULL &&
                               prior[buf1->value.action] + buf1->bp > prior[buf->value.action] + buf->bp) {
                            push(&pol, pop(&op));
                            getEl(op, 0, (void **) &buf1);
                        }
                        push(&op, buf);
                    }
                }
                break;
        }
    }
    if (bp != 0)
    {
        printError(E_BKT, output);
        delList(&pol);
        delList(&op);
        delList(inf);
    }
    else
        while (op != NULL)
            push(&pol, pop(&op));
    return pol;
}

lexeme * calculate_un(lexeme * num, lexeme * op) {
    lexeme *res;
    res = malloc(sizeof(lexeme));
    res->type = DIGIT;
    switch (op->value.action) {
        case SIN:
            res->value.digit = sin(num->value.digit);
            break;
        case COS :
            res->value.digit = cos(num->value.digit);
            break;
        case TG:
            res->value.digit = tan(num->value.digit);
            break;
        case CTG:
            res->value.digit = 1. / tan(num->value.digit);
            break;
        case SQRT:
            res->value.digit = sqrt(num->value.digit);
            break;
        case ARCCOS:
            res->value.digit = acos(num->value.digit);
            break;
        case ARCSIN:
            res->value.digit = asin(num->value.digit);
            break;
        case ARCTG:
            res->value.digit = atan(num->value.digit);
            break;
        case FLOOR:
            res->value.digit = floor(num->value.digit);
            break;
        case CEIL:
            res->value.digit = ceil(num->value.digit);
            break;
        case LN:
            break;
        default:
            break;
    }
    free(num);
    free(op);
    return res;
}

lexeme * calculate_bin(lexeme *num1, lexeme *num2, lexeme *op, error *er) {
    lexeme *res;
    res = malloc(sizeof(lexeme));
    res->type = DIGIT;
    switch (op->value.action) {
        case PLUS:
            res->value.digit = num1->value.digit + num2->value.digit;
            break;
        case MINUS:
            res->value.digit = num1->value.digit - num2->value.digit;
            break;
        case MULTI:
            res->value.digit = num1->value.digit * num2->value.digit;
            break;
        case RATIO:
            if (fabs(num2->value.digit - 0.) <= 16 * DBL_EPSILON * fmax(fabs(num2->value.digit),fabs(0.)))
                *er = E_DIVIDE_BY_ZERO;
            else
                res->value.digit = num1->value.digit / num2->value.digit;
            break;
        case POWER:
            res->value.digit = pow(num1->value.digit, num2->value.digit);
            break;
        case EQUATE:
            if (num1->type != VARIABLE)
                *er = E_NOT_VAR_BEFORE_EQUATE;
            else
            {
                num1->value.var->value = num2->value.digit;
                num1->value.var->isFill = 1;
                res = num1;
            }
            free(op);
            free(num2);
            return res;
        default:
            break;
    }
    free(op);
    free(num1);
    free(num2);
    return res;
}

int executer(list **pol, double *res, FILE * output) {
    list * digit = NULL;
    lexeme * buf, * num1, * num2;
    error er = DEFAULT;
    while (*pol != NULL) {
        fflush(stdout);
        buf = popBack(pol);
        switch (buf->type) {
            case DIGIT:
            case VARIABLE:
                push(&digit, buf);
                break;
            case OPERATION:
                switch (buf->value.action) {
                    case PLUS:
                    case MINUS:
                    case MULTI:
                    case RATIO:
                    case POWER:
                    case EQUATE:
                        if ((num2 = pop(&digit)) == NULL || (num1 = pop(&digit)) == NULL )
                        {
                            er = E_EXPRESSION_NOT_ENOUGH_NUM;
                            break;
                        }
                        push(&digit, calculate_bin(num1, num2, buf, &er));
                        break;
                    default:
                        if ((num1 = pop(&digit)) == NULL)
                        {
                            er = E_EXPRESSION_NOT_ENOUGH_NUM;
                            break;
                        }

                        push(&digit, calculate_un(num1, buf));
                        break;
                }
                break;
        }
    }
    if (getSize(digit) != 1)
    {
        er = E_EXPRESSION_NOT_ENOUGH_OP;
    }
    else {
        buf = pop(&digit);
        switch (buf->type) {
            case DIGIT:
                *res = buf->value.digit;
                free(buf);
                break;
            case VARIABLE:
                if (buf->value.var->isFill == 0)
                    er = E_NOT_INIT_VAR;
                *res = buf->value.var->value;
                free(buf);
                break;
            default:
                er = E_ERROR;
                return -1;
        }
    }
    if (er != DEFAULT)
    {
        printError(er, output);
        delList(&digit);
        delList(pol);
        return -1;
    }
    return 0;
}
