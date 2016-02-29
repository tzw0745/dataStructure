#ifndef STACK_ARR_H
#define STACK_ARR_H

#define EmptyTOS ( -1 )
#define MinStackSize ( 5 )

typedef int ElementType;

/* storage */

struct StackRecord;
typedef struct StackRecord *Stack;

/* function declaration */

Stack CreateStack( int MaxElements );
Stack MakeEmpty( Stack S );
int isEmpty( Stack S );
int isFull( Stack S );
void DestroyStack( Stack S );
void Push( ElementType X, Stack S );
void Pop( Stack S );
ElementType Top( Stack S );
ElementType TopAndPop( Stack S );

#endif    /* STACK_ARR_H */