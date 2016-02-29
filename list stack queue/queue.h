#ifndef QUEUE_H
#define QUEUE_H

#define MinQueueSize ( 5 )

typedef int ElementType;

/* storage */

struct QueueRecord;
typedef struct QueueRecord *Queue;

/* function declaration */

Queue CreateQueue( int MaxElements );
void DestroyQueue( Queue Q );
void MakeEmpty( Queue Q );
int IsEmpty( Queue Q );
int IsFull( Queue Q );
void Enqueue( ElementType X, Queue Q );
void Dequeu( Queue Q );
ElementType Front( Queue Q );
ElementType FrontAndDequeue( Queue Q );

#endif    /* QUEUE_H */