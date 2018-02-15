//
// Created by Марк on 14.02.18.
//

#include "executer.h"
#include "parser.h"

//int prior1[] = {6, 1, 1, 2, 2, 3, 10, -10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0};

int interpreter(list *inf) {
    int bp = 0;
    list *pol = NULL;
    list *op = NULL;
    lexeme *buf, *buf1;
    while(inf != NULL) {
        buf = (lexeme *)popBack(&inf);
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
                               prior[buf1->value.action] + buf1->bp >= prior[buf->value.action] + buf->bp) {
                            push(&pol, pop(&op));
                            getEl(op, 0, (void **) &buf1);
                        }
                        push(&op, buf);
                    }
                }
                break;
        }
    }

    while (op != NULL)
        push(&pol, pop(&op));
    printReList(pol, printLex);
}