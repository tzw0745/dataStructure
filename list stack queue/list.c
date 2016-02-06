#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "fatal.h"

struct Node
{
	ElementType Element;
	Position	Next;
};

/*                    */
/* function prototype */
/*                    */


List MakeEmpty( List L )
{
	if( L != NULL )
		DeleteList( L );
	L = ( PtrToNode )malloc( sizeof( struct Node ) );
	if( L == NULL )
		FatalError( "Heap Over Flow!" );
	L->Next = NULL;
	return L;
}	/* MakeEmpty */

/* Return true if L is empty */
int IsEmpty( List L )
{
	return L->Next == NULL;
}	/* IsEmpty */

/* Return true if P is the last Postion in list L */
/* Parameter L is unused in this function */
int IsLast( Position P, List L )
{
	return P->Next == NULL;
}	/* IsLast */

/* Return the position of X in L; NULL if not found */
Position Find( ElementType X, List L )
{
	Position p = L->Next;
	while( p != NULL && p->Element != X)
		p = p->Next;
	return p;
}	/* Find */

/* Delete from a list */
void Delete( ElementType X, List L )
{
	Position pre = FindPrevious(X, L);

	if ( !IsLast( pre, L ) ){
		/* X is found; delete it */
		Position tempNode = pre->Next;
		pre->Next = tempNode->Next;
		free(tempNode);
	}
}	/* Delete */

/* If X is not found, then Next field of returned value is NULL */
Position FindPrevious( ElementType X, List L)
{
	Position pre = L;
	while( pre->Next != NULL && pre->Next->Element != X )
		pre = pre->Next;
	return pre;
}	/* FindPrevious */

/* Insert (after legal position P) */
void Insert( ElementType X, List L, Position P)
{
	Position newNode = malloc( sizeof( struct Node) );
	if( newNode == NULL )
		FatalError( "Heap Over Flow!" );

	newNode->Element = X;
	newNode->Next = P->Next;
	P->Next = newNode;
}	/* Insert */

/* Delete all node */
void DeleteList( List L )
{
	while( !IsEmpty( L ) ){
		Delete( L->Next->Element, L );
	}
}	/* DeleteList */

Position Header( List L )
{
	return L;
}	/* Header */

Position First( List L )
{
	return L->Next;
}	/* First */

Position Next( Position P )
{
	return P->Next;
}	/* Next */

ElementType Retrieve( Position P )
{
	return P->Element;
}	/* Retrieve */
