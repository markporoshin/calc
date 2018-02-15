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

void pushBack(list **L, void *el);
void push(list **L, void *el);
void * popBack(list **L);
void * pop(list **L);
void parser(list **L0, list **vars0);
void  getEl(list * L, int number, void ** data);
int getSize(list * L);
void printList(list *L, void (*print)(void *));
void printReList(list *L, void (*print)(void *));
#endif //CALC2_0_LIST_H
