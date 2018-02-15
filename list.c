//
// Created by Марк on 14.02.18.
//

#include "list.h"

void pushBack(list **L, void *el)
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
            return;
        }
        L1 -> next -> data = el;
        L1 -> next -> next = NULL;
    }

}

void push(list **L, void *el)
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
            return;
        }
        L1->data = el;
        L1->next = *L;
        *L = L1;
    }

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

void printList(list *L, void (*print)(void *)) {
    list *L1 = L;
    for (;L1 != NULL; L1 = L1->next) {
        print(L1->data);
    }
}

void printReList(list *L, void (*print)(void *)) {
    if (L->next!=NULL)
        printReList(L->next, print);
    print(L->data);

}

