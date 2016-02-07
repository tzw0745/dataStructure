#include <stdio.h>
#include <stdlib.h>
#include "stack_arr.h"
#include "fatal.h"

/* Stack implementation is a dynamically allocated arr */

struct StackRecord
{
	int Capacity;
	int TopOfStack;
	ElementType *Array;
};

/*                    */
/* function prototype */
/*                    */

Stack CreateStack( int MaxElements )
{
	if( MaxElements < MinStackSize ){
		Error( "Stack size is too small" );
		printf( "increase to %d\n", MinStackSize );
		MaxElements = MinStackSize;
	}

	Stack s = malloc( sizeof( struct StackRecord ) );
	if( s == NULL)
		FatalError( "Heap Over Flow!" );

	s->Array = malloc( sizeof( ElementType ) * MaxElements );
	if( s->Array == NULL)
		FatalError( "Heap Over Flow!" );

	s->Capacity = MaxElements;
	MakeEmpty( s );
	return s;
}	/* CreateStack */

Stack MakeEmpty( Stack S )
{
	S->TopOfStack = EmptyTOS;
}	/* MakeEmpty */

int isEmpty( Stack S )
{
	return S->TopOfStack == EmptyTOS;
}	/* isEmpty */

int isFull( Stack S )
{
	return S->TopOfStack == S->Capacity - 1;
}	/* isFull */

void DestroyStack( Stack S )
{
	if( S != NULL ){
		free( S->Array );
		free( S );
	}
}	/* DestroyStack */

void Push( ElementType X, Stack S )
{
	if( isFull( S ) )
		Error( "Full stack!" );
	else
		S->Array[ ++S->TopOfStack ] = X;
}	/* Push */

void Pop( Stack S )
{
	if( isEmpty( S ) )
		Error( "Empty stack" );
	else
		--S->TopOfStack;
}	/* Pop */

/* Return the top element in stack */
/* Return 0 if the stack is empty */
ElementType Top( Stack S )
{
	if( !isEmpty( S ) )
		return ( S->Array )[ S->TopOfStack ];
	Error( "Empty stack" );
	return 0;
}	/* Top */

/* Return the top element in stack and pop top element */
/* Return 0 if the stack is empty */
ElementType TopAndPop( Stack S )
{
	if( !isEmpty( S ) )
		return ( S->Array )[ S->TopOfStack-- ];
	Error( "Empty stack" );
	return 0;
}