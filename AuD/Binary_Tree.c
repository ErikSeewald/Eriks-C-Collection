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
}

void insertl(tree *tp, int n) //insert n at leftmost position
{
    while((*tp) != NULL)
    {tp = &((*tp)->left);}

    (*tp) = (tree) malloc(sizeof(struct node));
    (*tp)->key = n;
}

int leafprod(tree t) //product of keys of all nodes with no connections (leaves)
{
    printf("t");
    if (t == NULL)
    {return 1;}

    if (t->left == NULL && t->right == NULL)
    {return t->key;}

    else
    {return leafprod(t->left) * leafprod(t->right);}
}

int main()
{
    tree rl = createNode(1, 0, 0);
    tree l = createNode(1, 0, 0);
    tree r = createNode(2, rl, 0);
    tree root = createNode(3, l, r);

    insertl(&root, 9);

    printf("%d\n", root->key);
    printf("%d %d\n", root->left->key, root->right->key);
    printf("%d ",  root->left->left->key);
    printf("%d\n",  root->right->left->key);

    //printf("Leaf product: %d", leafprod(root));

    return 0;
}