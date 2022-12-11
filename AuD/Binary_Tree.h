#ifndef ERIKS_C_COLLECTION_BINARY_TREE_H
#define ERIKS_C_COLLECTION_BINARY_TREE_H

typedef struct node *tree;
struct node { int key; tree left, right; };

tree createNode(int n, tree l, tree r);

void insertl(tree *tp, int n); //insert n at leftmost position


int leafprod(tree t); //product of keys of all nodes with no connections (leaves)


void printTree(tree root, int space);

int height(tree t);

tree balanceFactorS(tree t);

int isRightist(tree t);

#endif //ERIKS_C_COLLECTION_BINARY_TREE_H
