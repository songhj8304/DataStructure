
#include<stdio.h>
#include<stdlib.h>
#include "Stack.h"

// 스택 생성
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

// 스택이 비어 있다면 1을 반환. 스택에 데이터가 있다면 0 반환
int StkEmpty(const Stack* stack) 
{
	return stack && stack->top == -1;
}

// 스택에 e 추가
int StkPush(Stack* stack, Element e) {
	if (stack && stack->darr && DAAdd(stack->darr, e)) {
		stack->top++;
		return 1;
	}
	return 0;
}

// 스택의 가장 윗부분에 있는 데이터를 pe로 저장해서 반환
// 스택의 가장 윗부분에 있는 데이터는 제거
int StkPop(Stack* stack, Element* pe) 
{
	if (stack && stack->darr && pe && stack->top != -1 && DAGet(stack->darr, stack->top, pe)) {
		stack->top--;
		return 1;
	}
	return 0;
}

// 스택의 가장 윗부분에 있는 데이터를 pe로 저장해서 반환
// 스택의 가장 윗부분에 있는 데이터는 제거 안함
int StkTop(const Stack* stack, Element* pe) 
{
	return stack && stack->darr && pe && stack->top != -1 && DAGet(stack->darr, stack->top, pe);
	
}

// 스택의 가장 윗부분에 있는 데이터부터 순서대로 화면에 출력
void StkPrint(const Stack* stack, PrintFunc func) {
	if (stack && stack->darr) {
		for (int i = stack->top; i >= 0; i--) {
			Element e;
			DAGet(stack->darr, i, &e);
			func(e);
		}
	}
}

// 스택 제거
void StkDestroy(Stack* stack) 
{
	if (stack){
		if (DADestroy(stack->darr));
		free(stack);
	}
}


