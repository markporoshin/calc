//
// Created by Марк on 14.02.18.
//

#ifndef CALC_VARIABLE_H
#define CALC_VARIABLE_H

#include <stdio.h>

typedef struct {
    char * name;
    int isFill;
    double value;
} variable;


void printVar(variable * data, FILE *output);
#endif //CALC_VARIABLE_H
