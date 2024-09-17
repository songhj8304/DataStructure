
#include<stdio.h>
#include<stdlib.h>
#include "Stack.h"

// ���� ����
Stack* StkCreate() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack) {
		stack->darr = DACreate();
		if (stack->darr==NULL) {
			free(stack);
			return NULL;
		}
		stack->top = -1;
		return stack;
	}
	return NULL;
}

// ������ ��� �ִٸ� 1�� ��ȯ. ���ÿ� �����Ͱ� �ִٸ� 0 ��ȯ
int StkEmpty(const Stack* stack) 
{
	return stack && stack->top == -1;
}

// ���ÿ� e �߰�
int StkPush(Stack* stack, Element e) {
	if (stack && stack->darr && DAAdd(stack->darr, e)) {
		stack->top++;
		return 1;
	}
	return 0;
}

// ������ ���� ���κп� �ִ� �����͸� pe�� �����ؼ� ��ȯ
// ������ ���� ���κп� �ִ� �����ʹ� ����
int StkPop(Stack* stack, Element* pe) 
{
	if (stack && stack->darr && pe && stack->top != -1 && DAGet(stack->darr, stack->top, pe)) {
		stack->top--;
		return 1;
	}
	return 0;
}

// ������ ���� ���κп� �ִ� �����͸� pe�� �����ؼ� ��ȯ
// ������ ���� ���κп� �ִ� �����ʹ� ���� ����
int StkTop(const Stack* stack, Element* pe) 
{
	return stack && stack->darr && pe && stack->top != -1 && DAGet(stack->darr, stack->top, pe);
	
}

// ������ ���� ���κп� �ִ� �����ͺ��� ������� ȭ�鿡 ���
void StkPrint(const Stack* stack, PrintFunc func) {
	if (stack && stack->darr) {
		for (int i = stack->top; i >= 0; i--) {
			Element e;
			DAGet(stack->darr, i, &e);
			func(e);
		}
	}
}

// ���� ����
void StkDestroy(Stack* stack) 
{
	if (stack){
		if (DADestroy(stack->darr));
		free(stack);
	}
}


