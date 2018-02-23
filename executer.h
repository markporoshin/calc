//
// Created by Марк on 14.02.18.
//

#ifndef CALC_EXECUTER_H
#define CALC_EXECUTER_H


#include "list.h"

list * interpreter(list **inf, FILE * output);
int executer(list **pol, double *res, FILE * output);
#endif //CALC_EXECUTER_H
