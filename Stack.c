#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

Stack* StkCreate()
{
    Stack* pstack = (Stack*)malloc(sizeof(Stack));
    if (pstack) {
        pstack->darr = DACreate();
        if (pstack->darr == NULL) {
            free(pstack);
            return NULL;
        }
        pstack->top = -1;
        return pstack;
    }
    return NULL;
}

int StkEmpty(const Stack* stack)
{
    return stack && stack->top == -1;
}

int StkPush(Stack* stack, Element e)
{
    if (stack && stack->darr && DAAdd(stack->darr, e)) {
        stack->top++;
        return 1;
    }
    return 0;
}

int StkPop(Stack* stack, Element* pe)
{
    if (stack && stack->darr && pe && stack->top != -1 && DAGet(stack->darr, stack->top, pe)) {
        stack->top--;
        return 1;
    }
    return 0;
}

int StkTop(const Stack* stack, Element* pe)
{
    return stack && stack->darr && pe && stack->top != -1 && DAGet(stack->darr, stack->top, pe);
}

void StkPrint(const Stack* stack, PrintFunc func)
{
    if (stack) {
        for (int i = stack->top; i >= 0; i--) {
            Element e;
            if (DAGet(stack->darr, i, &e)) {
                func(e);
            }
        }
    }
}

void StkDestroy(Stack* stack)
{
    if (stack) {
        if (DADestroy(stack->darr)) {
            free(stack);
        }
    }
}