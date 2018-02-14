//
// Created by Марк on 14.02.18.
//



#ifndef CALC_PARSER_H
#define CALC_PARSER_H

#include <ctype.h>
#include <string.h>
#include "list.h"
#include "variable.h"


typedef enum {DIGIT, OPERATION} type;
typedef enum {U_MINUS, PLUS, MINUS, MULTI, RATIO, POWER, OBKT, CBKT, SIN, COS, LN, TG, CTG, ARCSIN, ARCCOS, ARCTG, FLOOR, CEIL, SQRT} action;
int prior[] = {6, 1, 1, 2, 2, 3, 10, -10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

typedef struct {
    type type;
    union {
        double digit;
        action action;
    } value;
} lexeme;



#endif //CALC_PARSER_H
