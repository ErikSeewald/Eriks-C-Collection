#include <stdio.h>
#include <stdlib.h>
#include "Binary_Tree.h"

void lRot(tree *tp) //left AVL rotation
{
    tree S = *tp;
    tree R = S->right;
    tree RL = R->left;

    *tp = R;
    R->left = S;
    S->right = RL;
}

void rRot(tree *tp) //right AVL rotation
{
    tree S = *tp;
    tree L = S->left;
    tree LR = L->right;

    *tp = L;
    L->right = S;
    S->left = LR;
}

int main()
{
    tree lrr = createNode(5, 0, 0);
    tree lr = createNode(4, 0, lrr);
    tree rl = createNode(7, 0, 0);
    tree rr = createNode(9, 0, 0);
    tree l= createNode(2, 0, lr);
    tree r = createNode(8, rl, rr);
    tree t = createNode(6, l, r);

    puts("Before rotation:");
    printTree(t, 0);

    lRot(&(t->left));
    puts("\nAfter rotation:");

    printTree(t,0);


    return 0;
}