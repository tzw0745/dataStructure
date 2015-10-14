#ifndef SQLIST_H
#define SQLIST_H

#include "define.h"

#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE      100
#define LISTINCREMENT       10

typedef struct{
    int *elem;
    int length;
    int listsize;
}SqList;

Status InitList_Sq(SqList *L){
    //构造一个空线性表L
    L->elem=(int *)malloc(LIST_INIT_SIZE * sizeof(int) );
    if(!L->elem) exit(OVERFLOW); //存储分配失败
    L->length=0;                 //空表长度为0
    L->listsize=LIST_INIT_SIZE;  //初始存储容量
    return OK;
}//InitList_Sq

void DestroyList_Sq(SqList *L){
    //销毁线性表L
    free(L->elem);               //释放内存空间
    L->elem=NULL;
    L->length=0;                 //长度置0
    L->listsize=0;               //容量置0
}//DestroyList_Sq

void ClearList_Sq(SqList *L){
    //清空线性表L
    L->length=0;                 //长度置0
}//ClearList_Sq

Status ListEmpty_Sq(SqList L){
    //若L为空表 返回TRUE 否则返回FALSE
    return (L.length==0) ?TRUE:FALSE;
}//ListEmpty_Sq

int ListLength_Sq(SqList L){
	//返回L中数据元素的个数
	return L.length;
}//ListLength_Sq

Status GetElem_Sq(SqList L, int i, int *e){
	//用e返回L中第i个数据元素的值
	//i的合法值为[1,L.length]
	if(i<1||i>L.length) exit(ERROR);	//i值不合法
	*e=L.elem[i-1];
	return OK;
}//GetElem_Sq

int LocateElem_Sq(SqList L, int e, Status compare(int, int) ){
	//返回L中第一个与e满足compare关系的元素的位序 若不存在 返回0
	int index;
	for(index=0;index<L.length;index++){
		if(compare(L.elem[index], e)){	//存在compare关系
			return index+1;			//返回位序
		}
	}
	return 0;
}//LocateElem_Sq

Status PriorElem_Sq(SqList L, int cur_e, int *pre_e){
	//若cur_e是L的数据元素且不是第一个 用pre_e返回它的前驱 否则操作失败 pre_e无定义
	int index;
	for(index=1;index<L.length;index++){		//查找范围为[1, L.length) 不包括第一个
		if(L.elem[index]==cur_e){
			*pre_e=L.elem[index-1];
			return OK;
		}
	}
	return ERROR;
}//PriorElem_Sq

Status NextElem_Sq(SqList L, int cur_e, int *next_e){
	//若cur_e是L的数据元素且不是最后一个 用next_e返回它的后继 否则操作失败 next_e无定义
	int index;
	for(index=0;index<L.length-1;index++){		//查找范围为[0, L.length-1) 不包括最后一个
		if(L.elem[index]==cur_e){
			*next_e=L.elem[index+1];
			return OK;
		}
	}
	return ERROR;
}//NextElem_Sq

Status ListInsert_Sq(SqList *L, int i, int e){
	//在顺序线性表L中第i个位置之前插入新的元素e
	//i的合法值为[1,L.length+1]
	if(i<1||i>L->length+1) return ERROR;		//i值不合法
	if(L->length>=L->listsize){					//当前存储空间已满 增加分配
		int *newbase;
		newbase=(int *)realloc(L->elem, (L->listsize+LISTINCREMENT)*sizeof(int));
		if(!newbase) exit(OVERFLOW);			//存储分配失败
		L->elem=newbase;						//新基址
		L->listsize+=LISTINCREMENT;				//增加存储容量
	}
	int *ptr_mid, *ptr_tail;
	ptr_mid=L->elem+i-1;						//ptr_mid为插入位置
	for(ptr_tail=L->elem+L->length-1;ptr_tail>=ptr_mid;--ptr_tail) *(ptr_tail+1)=*ptr_tail;			//插入位置及之后的元素右移
	*ptr_mid=e;									//插入e
	++L->length;								//表长增1
	return OK;
}//ListInsert_Sq

Status ListDelete_Sq(SqList *L, int i, int *e){
	//删除L的第i个数据元素 并用e返回其值 L的长度减1
	//i的合法值为[1,L.length]
	if(i<1||i>L->length) return ERROR;			//i值不合法
	int *ptr_mid, *ptr_tail;
	ptr_mid=L->elem+i-1;						//ptr_mid为被删除元素的位置
	*e=*ptr_mid;								//被删除元素的值赋给e
	for(ptr_tail=L->elem+L->length-1;ptr_mid<ptr_tail;++ptr_mid) *ptr_mid=*(ptr_mid+1);				//被删除元素之后的元素左移
	--L->length;								//表长减1
	return OK;
}//ListDelete_Sq

Status ListTraverse_Sq(SqList L, Status visit(int) ){
	//一次对L的每个数据元素调用函数visit() 一旦visit()失败则操作失败
	int index;
	for(index=0;index<L.length;index++){
		if(ERROR==visit(L.elem[index])) return ERROR; //调用失败
	}
	return OK;
}//ListTraverse_Sq
 
#endif
