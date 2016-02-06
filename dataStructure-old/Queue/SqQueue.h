#ifndef SqQUEUE_H
#define SqQUEUE_H

#include "define.h"

#include <stdio.h>
#include <stdlib.h>

//----循环队列的存储表示----//

#define MAXQSIZE 100	//最大队列长度

typedef struct{
	int *base;			//初始化的动态分配存储空间
	int front;			//头指针 若队列不空 指向队列头元素
	int rear;			//尾指针 若队列不空 指向队列尾元素的下一个位置
}SqQueue;

//----基本操作的函数原型----//

Status InitQueue_Sq(SqQueue *Q){
	//构造一个空队列
	Q->base=(int *)malloc(MAXQSIZE*sizeof(int));
	if(!Q->base) exit(OVERFLOW);			//存储分配失败
	Q->front=Q->rear=0;
	return OK;
}//InitQueue_Sq

Status DestroyQueue_Sq(SqQueue *Q){
	//销毁队列 Q不再存在
	free(Q->base);
	Q->base=NULL;
	Q->front=Q->rear=0;
	return OK;
}//DestroyQueue_Sq

Status ClearQueue_Sq(SqQueue *Q){
	//将Q清为空队列
	Q->front=Q->rear=0;
	return OK;
}//ClearQueue_Sq

Status QueueEmpty_Sq(SqQueue Q){
	//若队列Q为空队列 返回TRUE 否则返回FALSE
	return Q.rear==Q.front?TRUE:FALSE;
}//QueueEmpty_Sq

int QueueLength_Sq(SqQueue Q){
	//返回Q的元素个数 即为队列的长度
	if(Q.front<=Q.rear) return Q.rear-Q.front;
	else return MAXQSIZE-(Q.front-Q.rear);
}//QueueLength_Sq

Status GetHead_Sq(SqQueue Q, int *e){
	//若队列不空 则用e返回Q点队头元素 并返回Ok 否则返回ERROR
	if(Q.front==Q.rear) return ERROR;
	*e=Q.base[Q.front];			//返回队头元素
	return OK;
}//GetHead_Sq

Status EnQueue_Sq(SqQueue *Q, int e){
	//插入元素e为Q的新的队尾元素
	if((Q->rear+1)%MAXQSIZE==Q->front) return ERROR;	//队列满
	Q->base[Q->rear]=e;							//插入元素
	Q->rear=(Q->rear+1)%MAXQSIZE;				//队尾后移
	return OK;
}//EnQueue_Sq

Status DeQueue_Sq(SqQueue *Q, int *e){
	//若队列不空 则删除Q的队头元素 用e返回其值 并返回OK
	//否则返回ERROR
	if(Q->front==Q->rear) return ERROR;			//队列空
	*e=Q->base[Q->front];						//返回队头
	Q->front=(Q->front+1)%MAXQSIZE;				//队头后移
	return OK;
}//DeQueue_Sq

Status QueueTraverse_Sq(SqQueue Q, Status visit(int) ){
	//从队头到队尾一次队队列Q中每个元素调用函数visit() 一旦visit失败 则操作失败
	int index=Q.front;
	while(index!=Q.rear){						//遍历
		if(!visit(Q.base[index])) return ERROR;
		index=(index+1)%MAXQSIZE;
	}
	return OK;
}//QueueTraverse_Sq

#endif
