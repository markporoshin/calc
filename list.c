//
// Created by Марк on 14.02.18.
//

#include "list.h"

error pushBack(list **L, void *el)
{
    list *L1;
    if (*L == NULL)
    {
        *L = (list *)malloc(sizeof(list));
        (*L)->data = el;
        (*L)->next = NULL;
    }
    else
    {
        L1 = *L;
        while (L1->next != NULL)
        {
            L1 = L1->next;
        }
        L1 -> next = (list *) malloc(sizeof(list));
        if (L1 -> next == NULL) {
            return E_MEMORY;
        }
        L1 -> next -> data = el;
        L1 -> next -> next = NULL;
    }
    return DEFAULT;
}

error push(list **L, void *el)
{
    list *L1;
    if (*L == NULL)
    {
        *L = (list *)malloc(sizeof(list));
        (*L)->data = el;
        (*L)->next = NULL;
    }
    else
    {
        L1 = malloc(sizeof(list));
        if (L1 == NULL) {
            return E_MEMORY;
        }
        L1->data = el;
        L1->next = *L;
        *L = L1;
    }
    return DEFAULT;
}

void * pop(list **L)
{
    void * data;
    list *L1 = *L;
    if (L1 == NULL)
        return NULL;
    *L = (*L)->next;
    data = (L1->data);
    free(L1);
    return data;
}

void * popBack(list **L)
{
    void * data;
    list *L1 = *L;
    if (*L == NULL)
        return NULL;
    if (L1 -> next == NULL)
    {
        data = L1->data;
        free(L1);
        *L = NULL;
        return data;
    }
    while (L1 -> next -> next != NULL)
        L1 = L1 -> next;
    data = L1 -> next -> data;
    free(L1->next);
    L1 -> next = NULL;
    return data;
}

void delList(list **L)
{
    list *L1 = *L;
    while (L1 != NULL)
    {
        free(pop(&L1));
    }
    *L = NULL;
}

void  getEl(list * L, int number, void **data)
{
    list *L1 = L;
    if(L1 == NULL) {
        *data = NULL;
        return;
    }

    for (; L1 ->next != NULL && number > 0; L1 = L1 -> next, number--);
    *data = L1->data;
}

int getSize(list * L)
{
    int i = 0;
    list *L1 = L;
    for (; L1 != NULL; L1 = L1 -> next, i++);
    return i;

}

void printList(list *L, void (*print)(void *, FILE *), FILE *output) {
    list *L1 = L;
    for (;L1 != NULL; L1 = L1->next) {
        print(L1->data, output);
    }
}

void printReList(list *L, void (*print)(void *, FILE *), FILE *output) {
    if(L != NULL)
    {
        if (L->next != NULL)
            printReList(L->next, print, output);
        print(L->data, output);
    }
}

void printError(error er, FILE * output)
{
    fprintf(output, "  ERROR: ");
    switch(er) {
        case E_MEMORY:
            fprintf(output, "not enough memory\n");
            break;
        case E_BKT:
            fprintf(output, "скобка error\n");
            break;
        case E_EXPRESSION_NOT_ENOUGH_OP:
            fprintf(output, "need more operation\n");
            break;
        case E_EXPRESSION_NOT_ENOUGH_NUM:
            fprintf(output, "need more digit\n");
            break;
        case E_NOT_VAR_BEFORE_EQUATE:
            fprintf(output, "expression error (not a variable before equate)\n");
            break;
        case E_DIVIDE_BY_ZERO:
            fprintf(output, "division by zero\n");
            break;
        case E_NOT_INIT_VAR:
            fprintf(output, "variable is not initialized\n");
            break;
        case E_FORBADE_SYM:
            fprintf(output, "this symbols is not allow\n");
            break;
        default:
            fprintf(output, "error\n");
            break;
    }
}

