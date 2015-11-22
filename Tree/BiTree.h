#ifndef BITREE_H
#define BITREE_H

#include "define.h"

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

//----二叉树的二叉链表存储表示----//

typedef struct BiTNode{//节点类型
	ElementType data;
	struct BiTNode *lchild, *rchild;	//左右孩子指针
}BiTNode, *BiTree;

//----基本操作的函数原型----//

Status CreateBiTree(BiTree *T){
	//按先序次序输入二叉树中节点的值(一个字符) 空格字符表示空树
	//构造二叉链表表示二叉树T
	ElementType ch;
	//如果ElementType不为char 下面这条输入语句需要重写
	ch=getchar();
	if(ch==' ') *T=NULL;
	else{
		*T=(BiTree)malloc(sizeof(BiTNode) );
		if(!(*T)) exit(OVERFLOW);
		(*T)->data=ch;
		CreateBiTree(&((*T)->lchild));
		CreateBiTree(&((*T)->rchild));
	}
	return OK;
}//CreateBiTree

void DestroyBiTree(BiTree *T){
	//销毁二叉树
	BiTree *list;						//创建一个队列
										//队列的值为节点指针
	int index=0, last=1,len=1000;
	const int APPEND=500;
	list=(BiTree*)malloc(sizeof(BiTNode)*(len+2));
	if(!list) exit(OVERFLOW);
	list[index]=*T;						//二叉树头入队
	while(list[index]){
		if(last>=len) list=(BiTree*)realloc(list, sizeof(BiTNode)*(len+APPEND+2));
		if(!list) exit(OVERFLOW);
		len+=APPEND;
		//同一级的元素在list中的一段连续区域
		//从左到右分别入队
		if(list[index]->lchild) list[last++]=list[index]->lchild;
		if(list[index]->rchild) list[last++]=list[index]->rchild;
		index++;
	}
	for(index=0;index<last;index++){	//遍历队列
		free(list[index]);
	}
	free(list);
	*T=NULL;
}//DestroyBiTree

Status PreOrderTraverse(const BiTree T, Status visit(ElementType) ){
	//先序遍历二叉树T 对每个节点调用visit函数一次且仅一次
	//一旦visit()失败 则操作失败
	if(T){
		if(visit(T->data)){
			if(PreOrderTraverse(T->lchild, visit)){
				if(PreOrderTraverse(T->rchild, visit)) return OK;
			}//if
		}//if
		return ERROR;
	}//if
	else return OK;
}//PreOrderTraverse

Status InOrderTraverse(const BiTree T, Status visit(ElementType) ){
	//中序遍历二叉树T 对每个节点调用visit函数一次且仅一次
	//一旦visit()失败 则操作失败
	if(T){
		if(InOrderTraverse(T->lchild, visit)){
			if(visit(T->data)){
				if(InOrderTraverse(T->rchild, visit)) return OK;
			}//if
		}//if
		return ERROR;
	}//if
	else return OK;
}//InOrderTraverse

Status PostOrderTraverse(const BiTree T, Status visit(ElementType) ){
	//后序遍历二叉树T 对每个节点调用visit函数一次且仅一次
	//一旦visit()失败 则操作失败
	if(T){
		if(PostOrderTraverse(T->lchild, visit)){
			if(PostOrderTraverse(T->rchild, visit)){
				if(visit(T->data)) return OK;
			}//if
		}//if
		return ERROR;
	}//if
	else return OK;
}//PostOrderTraverse

Status LevelOrderTraverse(const BiTree T, Status visit(ElementType) ){
	//层序遍历二叉树T 对每个节点调用visit函数一次且仅一次
	//一旦visit()失败 则操作失败
	BiTree *list;						//创建一个队列
										//队列的值为节点指针
	int index=0, last=1,len=1000;
	const int APPEND=500;
	list=(BiTree*)malloc(sizeof(BiTNode)*(len+2));
	if(!list) exit(OVERFLOW);
	list[index]=T;						//二叉树头入队
	while(list[index]){
		//空间不足
		if(last>=len) list=(BiTree*)realloc(list, sizeof(BiTNode)*(len+APPEND+2));
		if(!list) exit(OVERFLOW);
		len+=APPEND;
		//同一级的元素在list中的一段连续区域
		//从左到右分别入队
		if(list[index]->lchild) list[last++]=list[index]->lchild;
		if(list[index]->rchild) list[last++]=list[index]->rchild;
		index++;
	}
	for(index=0;index<last;index++){	//遍历队列
		if(!visit(list[index]->data)) return ERROR;
	}
	return OK;
}//LevelOrderTraverse

int Depth(const BiTree T){
	//求二叉树的深度
	int depthval,depthLeft,depthRight;
	if(!T) depthval=0;					//空二叉树
	else{
		depthLeft=Depth(T->lchild);		//求左子树的深度
		depthRight=Depth(T->rchild);	//求右子树的深度
		depthval=1+(depthLeft>depthRight?depthLeft:depthRight);
	}
	return depthval;
}//Depth

int Size(const BiTree T){
	//求二叉树的节点个数
	BiTree *list;						//创建一个队列
										//队列的值为节点指针
	int index=0, last=1,len=1000;
	const int APPEND=500;
	list=(BiTree*)malloc(sizeof(BiTNode)*(len+2));
	if(!list) exit(OVERFLOW);
	list[index]=T;						//二叉树头入队
	while(list[index]){
		//空间不足
		if(last>=len) list=(BiTree*)realloc(list, sizeof(BiTNode)*(len+APPEND+2));
		if(!list) exit(OVERFLOW);
		len+=APPEND;
		//同一级的元素在list中的一段连续区域
		//从左到右分别入队
		if(list[index]->lchild) list[last++]=list[index]->lchild;
		if(list[index]->rchild) list[last++]=list[index]->rchild;
		index++;
	}
	return last;
}//Size


#endif
