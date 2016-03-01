#include "SearchTree.h"
#include "fatal.h"

struct TreeNode
{
    ElementType Element;
    SearchTree  Left;
    SearchTree  Right;
};

/*                    */
/* function prototype */
/*                    */

SearchTree MakeEmpty( SearchTree T )
{
    if( T != NULL ){
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}/* MakeEmpty */

Position Find( ElementType X, SearchTree T )
{
    if( T == NULL ){
        return NULL;
    }
    if( X < T->Element ){
        /* search in left child tree */
        return Find( X, T->Left );
    }
    else{
        if( X > T->Element ){
            /* search in right child tree */
            return Find( X, T->Right );
        }
        else{
            /* found it */
            return T;
        }
    }
}/* Find */

Position FindMin( SearchTree T )
{
    if( T != NULL ){
        while( T->Left != NULL ){
            T = T->Left;
        }
    }
    return T;
}/* FindMin */

Position FindMax( SearchTree T )
{
    if( T != NULL ){
        while( T->Right != NULL ){
            T = T->Right;
        }
    }
    return T;
}/* FindMax */

SearchTree Insert( ElementType X, SearchTree T )
{
    if( T == NULL ){
        /* Creat and Return */
        T = malloc( sizeof( struct TreeNode ) );
        if( T == NULL ){
            FatalError( "Heap Over Flow!" );
        }
        else{
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    }
    else{
        if( X < T->Element ){
            T->Left = Insert( X, T->Left );
        }
        else{
            T->Right = Insert( X, T->Right );
        }
        /* Else X is in the tree already; we'll do nothing */
    }

    return T;
}/* Insert */

SearchTree Delete( ElementType X, SearchTree T )
{
    if( T == NULL ){
        Error( "Element not found" );
    }
    else
    if( X < T->Element ){ /* Go left */
        T->Left = Delete( X, T->Left );
    }
    else
    if( X > T->Element ){ /* Go right */
        T->Right = Delete( X, T->Right );
    }
    else
    if( T->Left && T->Right ){ /* Two children */
        /* Replace with smallest in right subtree */
        Position node = FindMin( T->Right );
        T->Element = node->Element;
        T->Right = Delete( T->Element, T->Right );
    }
    else{ /* One or Zero childre */
        Position node = T;
        if( node->Left != NULL ) T = T->Left;
        else
        if( node->Right != NULL ) T = T->Right;
        free( node );
    }

    return T;
}/* Delete */

ElementType Retrieve( Position P )
{
    if( P != NULL ){
        return P->Element;
    }
    FatalError( "NULL Pointer!" );
}/* Retrieve */
