//
// Created by Марк on 14.02.18.
//

#include "variable.h"


void printVar(variable * data, FILE *output) {
    fprintf(output, "%s=%1.2lf ", data->name, data->value);
}