#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "fatal.h"

/* Queue implementation is a dynamically allocated array */

struct QueueRecord
{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    ElementType *Array;
};

/*                    */
/* function prototype */
/*                    */

Queue CreateQueue( int MaxElements )
{
    if( MaxElements < MinQueueSize ){
        Error( "Queue size is too small" );
        printf( "increase to %d\n", MinQueueSize );
        MaxElements = MinQueueSize;
    }

    Queue q = malloc( sizeof( struct QueueRecord ) );
    if( q == NULL)
        FatalError( "Heap Over Flow!" );

    q->Array = malloc( sizeof( ElementType ) * MaxElements );
    if( q->Array == NULL)
        FatalError( "Heap Over Flow!" );

    q->Capacity = MaxElements;
    MakeEmpty( q );
    return q;
}    /* CreateQueue */

void DestroyQueue( Queue Q )
{
    if( Q != NULL )
    {
        free( Q->Array );
        free( Q );
    }
}    /* DestroyQueue */

void MakeEmpty( Queue Q )
{
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}    /* MakeEmpty */

int IsEmpty( Queue Q )
{
    return Q->Size == 0;
}    /* IsEmpty */

int IsFull( Queue Q )
{
    return Q->Size == Q->Capacity;
}    /* IsFull */

static int Next( int Value, Queue Q )
{
    if( ++Value == Q->Capacity )
        Value = 0;
    return Value;
}    /* Next */

void Enqueue( ElementType X, Queue Q )
{
    if( IsFull( Q ) )
        Error( "Full queue" );
    else{
        Q->Rear = Next( Q->Rear, Q );
        ( Q->Array )[ Q->Rear ] = X;
        ++Q->Size;
    }
}    /* Enqueue */

void Dequeu( Queue Q )
{
    if( IsEmpty( Q ) )
        Error( "Empty queue" );
    else{
        Q->Front = Next( Q->Front, Q );
        --Q->Size;
    }
}    /* Dequeu */

/* Return 0 if queue is empty */
ElementType Front( Queue Q )
{
    if( !IsEmpty( Q ) )
        return ( Q->Array )[ Q->Front ];
    Error( "Empty queue" );
    return 0;
}    /* Front */

/* Return 0 if queue is empty */
ElementType FrontAndDequeue( Queue Q )
{
    if( !IsEmpty( Q ) ){
        int element = ( Q->Array )[ Q->Front ];
        Dequeu( Q );
        return element;
    }
    Error( "Empty queue" );
    return 0;
}    /* FrontAndDequeue */
