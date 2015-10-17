#ifndef LINKLIST_H
#define LINKLIST_H

#include "define.h"

#include <stdio.h>
#include <stdlib.h>

//----线性表的链式存储表示----//
//----链表形式为包含一个不存储元素的头结点的单链表----//

typedef struct LNode{	//节点类型
	int data;
	struct LNode *next;
}*Link, *Position;

typedef struct{			//链表类型
	Link head, tail;	//分别指向线性链表中的头结点和最后一个节点
	int len;			//指示线性链表中数据元素的个数
}LinkList;

//----基本操作的函数原型----//

Status MakeNode_L(Link *p, int e){
	//分配由p指向的值为e的节点 并返回OK 若分配失败 则返回ERROR
	*p=(Link)malloc(sizeof(struct LNode));			//分配空间
	if(!*p) return ERROR;
	(*p)->data=e;								//写入数据
	return OK;
}//MakeNode_L

Status InitList_L(LinkList *L){
	//构造一个空的线性链表L
	L->head=(Link)malloc(sizeof(struct LNode));
	if(!L->head) exit(OVERFLOW);			//分配失败
	L->tail=L->head;						//头尾指向同一个结点(空头结点)
	L->head->next=NULL;
	L->len=0;
	return OK;
}//InitList_L

Status DestroyList_L(LinkList *L){
	//销毁线性链表L L不再存在
	Link index;
	index=L->head;					//从结点开始销毁
	while(index){
		L->head=L->head->next;		//head表示待销毁链表的头结点
		free(index);
		index=L->head;				//index后移
	}
	L->tail=L->head;				//tail=head=NULL
	L->len=0;
	return OK;
}//DestroyList_L

Status ClearList_L(LinkList *L){
	//将线性链表L重置为空表 并释放原链表的节点空间
	Link index;
	index=L->head->next;
	while(index){
		L->tail=index->next;
		free(index);
		index=L->tail;
	}
	L->tail=L->head;				//头尾指向同一个结点(空头结点)
	L->head->next=NULL;
	L->len=0;
	return OK;
}//ClearList_L

Status InsFirst_L(LinkList *L, Link s){
	//将s所指节点插入在线性链表L的第一个节点之前
	Link first;
	first=L->head->next;			//first指向原链表的第一个结点
	L->head->next=s;				//将s插入到h和first之间
	s->next=first;
	++L->len;						//L长度+1
	if(1==L->len) L->tail=s;		//如果L先前是空链表
	return OK;
}//InsFirst_L

Status DelFirst_L(LinkList *L, Link *q){
	//删除线性链表L中的第一个节点并以q返回
	if(0==L->len) return ERROR;		//空链表无法删除结点
	Link first;
	first=L->head->next;			//first指向原链表的第一个结点
	L->head->next=first->next;		//删除first
	*q=first;						//用q返回first的值 即被删除结点的地址
	--L->len;						//L长度-1
	if(0==L->len) L->tail=L->head;	//如果L已经变成空链表
	return OK;
}//DelFirst_L

Status Append_L(LinkList *L, Link s){
	//将指针s所指(彼此已指针相链)的一串结点链接在线性链表L的最后一个结点之后 并改变链表L的尾指针指向新的尾结点
	int lenOfS=1;					//lenOfS表示该串结点的长度
	L->tail->next=s;				//将s连接到L尾部
	while(s->next){					//s后移到该串结点的尾部
		s=s->next;
		lenOfS++;
	}
	L->tail=s;						//tail指向新尾部
	L->len+=lenOfS;					//len变为新链表的长度
	return OK;
}//Append_L

Status Remove_L(LinkList *L, Link *q){
	//删除线性链表L中的尾结点并以q返回 改变链表L的尾指针指向新的尾结点
	if(0==L->len) return ERROR;		//空链表无法删除结点
	L->tail=L->head;
	while(L->tail->next->next){		//tail移动到尾结点的前一个结点
		L->tail=L->tail->next;
	}
	*q=L->tail->next;				//返回尾结点的地址
	L->tail->next=NULL;				//tail指向的结点作为新链表的尾结点
	--L->len;						//L长度-1
	return OK;
}//Remove_L

Status InsBefore_L(LinkList *L, Link *p, Link s){
	//已知p指向线性链表L中的一个结点 将s所指结点插入在p所指结点之前 并修改指针p指向新插入的结点
	Link PriOfP;
	for(PriOfP=L->head;PriOfP->next!=(*p);PriOfP=PriOfP->next) ;	//PriOfP移动到p的前驱
	PriOfP->next=s;					//将s插入到PriOfP和p之间
	s->next=*p;
	*p=s;							//p指向新插入的结点
	++L->len;						//L长度+1
}//InsBefore_L

Status InsAfter_L(LinkList *L, Link *p, Link s){
	//已知p指向线性链表L中的一个结点 将s所指结点插入在p所指结点之后 并修改指针p指向新插入的结点
	Link NextOfP;
	NextOfP=(*p)->next;				//NextOfP指向p的后继
	s->next=NextOfP;				//将s插入到p和NextOfP之间
	(*p)->next=s;
	if(NULL==NextOfP) L->tail=s;	//如果p是原链表的尾结点 那么新链表的尾结点是s
	*p=s;							//p指向新插入的结点
	++L->len;						//L长度+1
	return OK;
}//InsAfter_L

Status SetCurInt_L(Link *p, int e){
	//已知p指向线性链表中的一个结点 用e更新p所指结点中数据元素的值
	(*p)->data=e;
	return OK;
}//SetCurInt_L

int GetCurInt_L(Link p){
	//已知p指向线性链表中的一个结点 返回p所指结点中数据元素的值
	return p->data;
}//GetCurInt_L

Status ListEmpty_L(LinkList L){
	//若线性链表L为空表 则返回TRUE 否则返回FALSE
	return L.len?FALSE:TRUE;
}//ListEmpty_L

int ListLength_L(LinkList L){
	//返回线性链表L中元素个数
	return L.len;
}//ListLength_L

Position GetHead_L(LinkList L){
	//返回线性链表L中第一个结点的位置
	return L.head->next;
}//GetHead_L

Position GetLast_L(LinkList L){
	//返回线性链表L中最后一个结点的位置
	return L.tail;
}//GetLast_L

Position PriorPos_L(LinkList L, Link p){
	//已知p指向线性链表L中的一个结点 返回p所指结点的直接前驱的位置 若无前驱 则返回NULL
	if(p==L.head->next) return NULL;
	Position PriOfP;
	for(PriOfP=L.head->next;PriOfP->next!=p;PriOfP=PriOfP->next) ;	//PriOfP移动到p的前驱
	return PriOfP;
}//PriorPos_L

Position NextPos_L(LinkList L, Link p){
	//已知p指向线性链表L中的一个结点 返回p所指结点的直接后继的位置 若无后继 则返回NULL
	return p->next;
}//NextPos_L

Status LocatePos_L(LinkList L, int i, Link *p){
	//返回p指示线性链表L中第i个结点的位置并返回OK i值不合法时返回ERROR
	if(i<1||i>L.len) return ERROR;		//i值不合法
	*p=L.head;
	while(i--){							//p移动i次
		*p=(*p)->next;
	}
	return OK;
}//LocatePos_L

Position LocateInt_L(LinkList L, int e, Status compare(int, int) ){
	//返回线性链表L中第1个与e满足函数compare()判定关系的元素的位置 若不存在这样的元素 则返回NULL
	Position index;
	for(index=L.head->next;index;index=index->next){	//遍历
		if(compare(index->data, e)) return index;
	}
	return NULL;
}//LocateInt_L

Status ListTraverse_L(LinkList L, Status visit(int) ){
	//依次队L的每个元素调用函数visit() 一旦visit()失败 则操作失败
	Position index;
	for(index=L.head->next;index;index=index->next){	//遍历
		if(!visit(index->data)) return ERROR;
	}
	return OK;
}//ListTraverse_L

#endif
