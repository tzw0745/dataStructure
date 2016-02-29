#include <stdio.h>
#include <stdlib.h>
#include "stack_link.h"
#include "fatal.h"

struct Node
{
    ElementType Element;
    PtrToNode Next;
};

/*                    */
/* function prototype */
/*                    */

Stack CreateStack( void )
{
    Stack s = malloc( sizeof( struct Node ) );
    if( s == NULL)
        FatalError( "Heap Over Flow!" );
    s->Next = NULL;
    return s;
}    /* CreateStack */

Stack MakeEmpty( Stack S )
{
    if( S == NULL)
        Error( "Must use CreateStack first" );
    else
        while( !isEmpty( S ) )
            Pop( S );
}    /* MakeEmpty */

int isEmpty( Stack S )
{
    return S->Next == NULL;
}    /* isEmpty */

void DestroyStack( Stack S )
{
    MakeEmpty( S );
    free( S );
}    /* DestroyStack */

void Push( ElementType X, Stack S )
{
    PtrToNode newNode = malloc( sizeof( struct Node ) );
    if(newNode == NULL)
        FatalError( "Heap Over Flow!" );
    else{
        newNode->Element = X;
        newNode->Next = S->Next;
        S->Next = newNode;
    }
}    /* Push */

void Pop( Stack S )
{
    if( isEmpty( S ) )
        Error( "Empty stack" );
    else{
        PtrToNode firstNode = S->Next;
        S->Next = firstNode->Next;
        free( firstNode );
    }
}    /* Pop */

/* Return the top element in stack */
/* Return 0 if the stack is empty */
ElementType Top( Stack S )
{
    if( !isEmpty( S ) )
        return S->Next->Element;
    Error( "Empty stack" );
    return 0;
}    /* Top */
