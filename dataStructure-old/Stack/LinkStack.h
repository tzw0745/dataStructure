#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "define.h"

#include <stdio.h>
#include <stdlib.h>

//----栈的链式存储表示----//

typedef struct SNode{//节点类型
	int data;
	struct SNode *next;
}*Link, *Position;

typedef struct{
	Link top;		//栈顶指针
}LinkStack;

//----基本操作的函数原型----//

Status InitStack_L(LinkStack *S){
	//构造一个空栈S
	S->top=NULL;
	return OK;
}//InitStack_L

Status DestroyStack_L(LinkStack *S){
	//销毁栈S S不再存在
	while(S->top!=NULL){
		Link current=S->top;
		S->top=S->top->next;
		free(current);
	}
	return OK;
}//DestroyStack_L

Status ClearStack_L(LinkStack *S){
	//把S置为空栈
	DestroyStack_L(S);
	return OK;
}//ClearStack_L

Status StackEmpty_L(LinkStack S){
	//若栈S为空栈 则返回TRUE 否则返回FALSE
	return NULL==S.top?TRUE:FALSE;
}//StackEmpty_L

int StackLength_L(LinkStack S){
	//返回S的元素个数 即栈的长度
	int len=0;
	Link current=S.top;
	while(current!=NULL){
		len++;
		current=current->next;
	}
	return len;
}//StackLength_L

Status GetTop_L(LinkStack S, int *e){
	//若栈不空 则用e返回S的栈顶元素 并返回OK 否则返回ERROR
	if(NULL==S.top) return ERROR;			//栈为空
	*e=S.top->data;
	return OK;
}//GetTop_L

Status Push_L(LinkStack *S, int e){
	//插入元素e作为新的栈顶元素
	Link current;
	current=(Link)malloc(sizeof(struct SNode));	//Link即为SNode的指针
	if(!current) exit(OVERFLOW);
	current->data=e;						//值给节点
	current->next=S->top;					//节点链接到链表头(栈顶)
	S->top=current;							//重新定位链表头(栈顶)到新节点
	return OK;
}//Push_L

Status Pop_L(LinkStack *S, int *e){
	//若栈不空 则删除S的栈顶元素 用e返回其值 并返回OK 否则返回ERROR
	if(NULL==S->top) return ERROR;
	*e=S->top->data;						//取出栈顶
	Link pre=S->top;						//pre指向栈顶
	S->top=S->top->next;					//top指针后移(删除原先的栈顶节点)
	free(pre);								//释放空间
	return OK;
}//Pop_L

Status StackTraverse_L(LinkStack S, Status visit(int) ){
	//从栈底到栈顶依次对栈中每个元素调用函数visit() 一旦visit()失败 则操作失败
	Link index;
	for(index=S.top;NULL!=index;index=index->next){
		if(ERROR==visit(index->data)) return ERROR;	//操作失败
	}
	return OK;
}//StackTraverse_L

#endif
