#ifndef STACK_LINK_H
#define STACK_LINK_H

typedef int ElementType;

/* storage */

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

/* function declaration */

Stack CreateStack( void );
Stack MakeEmpty( Stack S );
int isEmpty( Stack S );
void DestroyStack( Stack S );
void Push( ElementType X, Stack S );
void Pop( Stack S );
ElementType Top( Stack S );

#endif    /* STACK_LINK_H */