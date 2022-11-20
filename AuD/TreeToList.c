#include <stdio.h>
#include <stdlib.h>

typedef struct element *list;
struct element { int value; list next; };

typedef struct node *tree;
struct node { int key; tree left, right; };

tree createNode(int n, tree l, tree r)
{
    tree root = (tree) malloc(sizeof(struct node));
    root->key = n;
    root->left = l;
    root->right = r;
}

void printList(list *lp)
{
    while (*lp != NULL)
    {
        printf("%d\n", (*lp)->value);
        lp = &((*lp)->next);
    }
}

void append(list *lp, int n)
{
    while (*lp != NULL)
    {lp = &((*lp)->next);}

    (*lp) = (list) malloc(sizeof(struct element));
    (*lp)->value = n;
    (*lp)->next = NULL;
}

void treeToEvenList(tree t, list *lp)
{
    //a list of only even keys of t (first those of the left half, then the root, then the right half)
    //this order applies to every subtree further down

    if(t->left != NULL)
    {treeToEvenList(t->left, lp);}

    if (t->key % 2 == 0)
        append(lp, t->key);

    if(t->right != NULL)
    {treeToEvenList(t->right, lp);}
}

int main()
{
    //Tree 1
    tree rrr1 = createNode(8, 0, 0);
    tree ll1 = createNode(9, 0, 0);
    tree rl1 = createNode(12, 0, 0);
    tree rr1 = createNode(3, 0, rrr1);
    tree l1 = createNode(6, ll1, 0);
    tree r1 = createNode(2, rl1, rr1);
    tree root1= createNode(4, l1, r1);

    //Tree 2
    tree lrr2 = createNode(10, 0, 0);
    tree lr2 = createNode(0, 0, lrr2);
    tree rl2 = createNode(1, 0, 0);
    tree rr2 = createNode(3, 0, 0);
    tree l2= createNode(2, 0, lr2);
    tree r2 = createNode(8, rl2, rr2);
    tree root2 = createNode(4, l2, r2);

    tree t = root2;

    printf("Tree as list: \n");
    list lp;
    treeToEvenList(t, &lp);
    printList(&lp);

    return 0;
}
