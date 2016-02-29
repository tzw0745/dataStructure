#ifndef LIST_H
#define LIST_H

typedef int ElementType;

/* storage */

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

/* function declaration */

List MakeEmpty( List L );
int IsEmpty( List L );
int IsLast( Position P, List L );
Position Find( ElementType X, List L );
void Delete( ElementType X, List L );
Position FindPrevious( ElementType X, List L);
void Insert( ElementType X, List L, Position P);
void DeleteList( List L );
Position Header( List L );
Position First( List L );
Position Next( Position P );
ElementType Retrieve( Position P );

#endif    /* LIST_H */