#include <stdio.h>
#include <stdlib.h>
#include "Binary_Tree.h"

typedef struct node *tree;

int main()
{
    tree lrr2 = createNode(10, 0, 0);
    tree lr2 = createNode(0, 0, lrr2);
    tree rl2 = createNode(1, 0, 0);
    tree rr2 = createNode(3, 0, 0);
    tree l2= createNode(2, 0, lr2);
    tree r2 = createNode(8, rl2, rr2);
    tree root2 = createNode(4, l2, r2);

    tree t = root2;

    printTree(t, 0);

    return 0;
}