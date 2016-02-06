#ifndef SQSTACK_H
#define SQSTACK_H

#include "define.h"

#include <stdio.h>
#include <stdlib.h>

//----栈的顺序存储表示----//

#define STACK_INIT_SIZE		100		//存储空间初始分配量
#define STACKINCREMENT		10		//存储空间分配增量

typedef struct {
	int *base;		//栈底指针 在栈构造之前和销毁之后 base的值为NULL
	int *top;		//栈顶指针
	int stacksize;	//当前已分配的存储空间 以元素为单位
}SqStack;

//----基本操作的函数原型----//

Status InitStack_Sq(SqStack *S){
	//构造一个空栈S
	S->base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!S->base) exit(OVERFLOW);	//存储分配失败
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE;
	return OK;
}//InitStack_Sq

Status DestroyStack_Sq(SqStack *S){
	//销毁栈S S不再存在
	free(S->base);	//释放空间
	S->base=S->top=NULL;	//指针置空
	S->stacksize=0;	//长度置0
	return OK;
}//DestroyStack_Sq

Status ClearStack_Sq(SqStack *S){
	//把S置为空栈
	S->top=S->base;
	return OK;
}//ClearStack_Sq

Status StackEmpty_Sq(SqStack S){
	//若栈S为空栈 则返回TRUE 否则返回FALSE
	return S.top==S.base?TRUE:FALSE;
}//StackEmpty_Sq

int StackLength_Sq(SqStack S){
	//返回S的元素个数 即栈的长度
	return S.top-S.base;
}//StackLength_Sq

Status GetTop_Sq(SqStack S, int *e){
	//若栈不空 则用e返回S的栈顶元素 并返回OK 否则返回ERROR
	if(S.top==S.base) return ERROR;
	*e=*(S.top-1);
	return OK;
}//GetTop_Sq

Status Push_Sq(SqStack *S, int e){
	//插入元素e作为新的栈顶元素
	if(S->top-S->base>=S->stacksize){	//栈满 追加存储空间
		S->base=(int *)realloc(S->base, (S->stacksize+STACKINCREMENT)*sizeof(int));
		if(!S->base) exit(OVERFLOW);	//存储分配失败
		S->top=S->base+S->stacksize;
		S->stacksize+=STACKINCREMENT;
	}
	*S->top++=e;
	return OK;
}//Push_Sq

Status Pop_Sq(SqStack *S, int *e){
	//若栈不空 则删除S的栈顶元素 用e返回其值 并返回OK 否则返回ERROR
	if(S->top==S->base) return ERROR;
	*e=*--S->top;
	return OK;
}//Pop_Sq

Status StackTraverse_Sq(SqStack S, Status visit(int) ){
	//从栈底到栈顶依次对栈中每个元素调用函数visit() 一旦visit()失败 则操作失败
	int *index;
	for(index=S.base;index<S.top;index++){
		if(ERROR==visit(*index)) return ERROR;	//操作失败
	}
	return OK;
}//StackTraverse_Sq

#endif
