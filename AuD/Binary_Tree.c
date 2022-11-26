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

int height(tree t)
{
    if (t == NULL)
        return 0;

    if (t->left == NULL && t->right == NULL)
        return 1;

    int l = 1 + height(t->left);
    int r = 1 + height(t->right);

    if (l > r)
        return l;
    else
        return r;
}

tree balanceFactorS(tree t)
{
    //creates a new tree S that has the balance factor (height of left tree minus height of right tree)
    //at each node
    if (t == NULL)
        return NULL;

    tree s = (tree) malloc(sizeof(struct node));
    s->key = height(t->right) - height(t->left);
    s->left = balanceFactorS(t->left);
    s->right = balanceFactorS(t->right);

    return s;
}

int isRightist(tree t)
{
    if (t == NULL) //if the tree has no nodes, it is trivially decided to be rightist
        return 1;
    return (height(t->left)) <= height(t->right);
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

    tree t = root2;

    printTree(t, 0);

    printf("Leaf product: %d", leafprod(t));

    if (isRightist(t) == 1)
        printf("\nT is rightist");
    else
        printf("\nT is not rightist");

    printf("\nThe tree has a height of: %d", height(t));

    printf("\n Balance factor tree: \n");
    printTree(balanceFactorS(t), 0);

    return 0;
}