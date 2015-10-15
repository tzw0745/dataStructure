#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "define.h"

#include <stdio.h>
#include <stdlib.h>

//----单链队列的存储表示----//
//----该单链队列具有一个不存放元素的头结点----//
//----队头元素为Q.front->next->data----//

typedef struct QNode{
	int data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct{
	QueuePtr front;		//队头指针
	QueuePtr rear;		//队尾指针
}LinkQueue;

//----基本操作的函数原型----//

Status InitQueue_L(LinkQueue *Q){
	//构造一个空队列
	Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q->front) exit(OVERFLOW);			//存储分配失败
	Q->front->next=NULL;
	return OK;
}//InitQueue_L

Status DestroyQueue_L(LinkQueue *Q){
	//销毁队列 Q不再存在
	while(Q->front){
		Q->rear=Q->front->next;
		free(Q->front);
		Q->front=Q->rear;
	}
	return OK;
}//DestroyQueue_L

Status ClearQueue_L(LinkQueue *Q){
	//将Q清为空队列
	while(Q->front->next){
		Q->rear=Q->front->next;
		free(Q->front);
		Q->front=Q->rear;
	}
	return OK;
}//ClearQueue_L

Status QueueEmpty_L(LinkQueue Q){
	//若队列Q为空队列 返回TRUE 否则返回FALSE
	return Q.front==Q.rear?TRUE:FALSE;
}//QueueEmpty_L

int QueueLength_L(LinkQueue Q){
	//返回Q的元素个数 即为队列的长度
	int len=0;
	QueuePtr index=Q.front->next;
	while(index){
		len++;
		index=index->next;
	}
	return len;
}//QueueLength_L

Status GetHead_L(LinkQueue Q, int *e){
	//若队列不空 则用e返回Q点队头元素 并返回Ok 否则返回ERROR
	if(Q.front==Q.rear) return ERROR;
	*e=Q.front->next->data;			//返回队头元素
	return OK;
}//GetHead_L

Status EnQueue_L(LinkQueue *Q, int e){
	//插入元素e为Q的新的队尾元素
	QueuePtr newNode;
	newNode=(QueuePtr)malloc(sizeof(QNode));
	if(!newNode) exit(OVERFLOW);	//存储分配失败
	newNode->data=e;				//存入数据
	newNode->next=NULL;				//队尾的next指针为空
	Q->rear->next=newNode;			//链接到原队列的队尾
	Q->rear=newNode;				//rear指针指向新的队尾节点
	return OK;
}//EnQueue_L

Status DeQueue_L(LinkQueue *Q, int *e){
	//若队列不空 则删除Q的队头元素 用e返回其值 并返回OK
	//否则返回ERROR
	if(Q->front==Q->rear) return ERROR;
	QueuePtr oldFront;
	oldFront=Q->front->next;		//oldFront指向队头
	*e=oldFront->data;				//e返回队头值
	Q->front->next=oldFront->next;	//队头指针后移
	if(Q->rear==oldFront) Q->rear=Q->front;	//如果原队列只有队头一个元素 则新队列为空队列
	free(oldFront);
	return OK;
}//DeQueue_L

Status QueueTraverse_L(LinkQueue Q, Status visit(int) ){
	//从队头到队尾一次队队列Q中每个元素调用函数visit() 一旦visit失败 则操作失败
	QueuePtr index;
	index=Q.front->next;
	while(index){					//遍历
		if(!visit(index->data)) return ERROR;
		index=index->next;
	}
	return OK;
}//QueueTraverse_L

#endif
