//
// Created by Марк on 14.02.18.
//

#ifndef CALC2_0_LIST_H
#define CALC2_0_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tag_list list;
struct tag_list
{
    void *data;
    list * next;
};

typedef enum {
    E_BKT, E_MEMORY,  E_ERROR,  DEFAULT, END_OF_FILE, E_EXPRESSION_NOT_ENOUGH_NUM, E_EXPRESSION_NOT_ENOUGH_OP,
    E_DIVIDE_BY_ZERO, E_NOT_VAR_BEFORE_EQUATE, E_NOT_INIT_VAR, E_FORBADE_SYM
} error;

error pushBack(list **L, void *el);
error push(list **L, void *el);
void * popBack(list **L);
void * pop(list **L);
void delList(list **L);
int parser(list **L0, list **vars0, char *str, FILE *output);
void  getEl(list * L, int number, void ** data);
int getSize(list * L);
void printList(list *L, void (*print)(void *, FILE *), FILE *output);
void printReList(list *L, void (*print)(void *, FILE *), FILE *output);
void printError(error er, FILE * output);
#endif //CALC2_0_LIST_H
