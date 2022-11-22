#include <stdio.h>
#include <stdlib.h>

typedef struct node *tree;
struct node { int key; tree left, right; };

tree createNode(int n, tree l, tree r)
{
    tree root = (tree) malloc(sizeof(struct node));
    root->key = n;
    root->left = l;
    root->right = r;

    return root;
}

void insertl(tree *tp, int n) //insert n at leftmost position
{
    while((*tp) != NULL)
    {tp = &((*tp)->left);}

    (*tp) = (tree) malloc(sizeof(struct node));
    (*tp)->key = n;
    (*tp)->left = NULL;
    (*tp)->right = NULL;
}

int leafprod(tree t) //product of keys of all nodes with no connections (leaves)
{
    if (t == NULL)
        return 1;

    if (t->left == NULL && t->right == NULL)
     return t->key;

    return leafprod(t->left) * leafprod(t->right);
}

int prom(tree t) //calculates the distances from the furthest left leaf to the root
{
    if (t == NULL)
        return 0;

    if (t->left == NULL && t->right == NULL)
        return 1;

    else if(t->left != NULL)
        return 1 + prom(t->left);

    else
        return 1 + prom(t->right);
}

void printTree(tree root, int space)
{
    if (root == NULL)
        return;

    space += 10;

    printTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
    {printf(" ");}
    printf("%d\n", root->key);

    printTree(root->left, space);
}

int isRightist(tree t)
{
    if (t == NULL) //if the tree has no nodes, it is trivially decided to be rightist
        return 1;
    return (prom(t->left)) <= prom(t->right);
}

int main()
{
    //Tree 1
    tree rl1 = createNode(1, 0, 0);
    tree l1 = createNode(1, 0, 0);
    tree r1 = createNode(2, rl1, 0);
    tree root1= createNode(3, l1, r1);

    insertl(&root1, 9);

    //Tree 2
    tree lrr2 = createNode(10, 0, 0);
    tree lr2 = createNode(0, 0, lrr2);
    tree rl2 = createNode(1, 0, 0);
    tree rr2 = createNode(3, 0, 0);
    tree l2= createNode(2, 0, lr2);
    tree r2 = createNode(8, rl2, rr2);
    tree root2 = createNode(4, l2, r2);

    tree t = root1;

    printTree(t, 0);

    printf("Leaf product: %d", leafprod(t));

    printf("\nProm of t is: %d", prom(t));

    if (isRightist(t) == 1)
        printf("\nT is rightist");
    else
        printf("\nT is not rightist");


    return 0;
}