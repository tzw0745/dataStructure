#ifndef SEARCHTREE_H
#define SEARCHTREE_H

typedef int ElementType;

/* storage */

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

/* function declaration */
SearchTree MakeEmpty( SearchTree T );
Position Find( ElementType X, SearchTree T );
Position FindMin( SearchTree T );
Position FindMax( SearchTree T );
SearchTree Insert( ElementType X, SearchTree T );
SearchTree Delete( ElementType X, SearchTree T );
ElementType Retrieve( Position P );

#endif