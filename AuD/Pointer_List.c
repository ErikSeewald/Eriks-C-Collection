#include <stdio.h>
#include <stdlib.h>

typedef struct element *list;
struct element { int value; list next; };

void printList(list *lp)
{
    while (*lp != NULL)
    {
        printf("%d, ", (*lp)->value);
        lp = &((*lp)->next);
    }
}

int sum(list lp)
{
    int sum = 0;
    while (lp != NULL)
    {
        sum+= lp->value;
        lp = lp->next;
    }
    return sum;
}

void rmEvens(list *lp)
{
    while (*lp != NULL)
    {
        if ((*lp)->value % 2 == 0)
        {
            list templP = *lp;
            *lp = (*lp)->next;
            free(templP);
        }
        else {lp = &((*lp)->next);}
    }
}

int getMax(list lp)
{
    int max = 0;
    while (lp != NULL)
    {
        if (lp->value > max)
        {max = lp->value;}

        lp = lp->next;
    }
    return max;
}

void delmax(list *lp) //deletes the elements with the highest value
{
    int max = getMax(*lp);

    while (*lp != NULL)
    {
        if ((*lp)->value == max)
        {
            list templP = *lp;
            *lp = (*lp)->next;
            free(templP);
        }
        else {lp = &((*lp)->next);}
    }
}

void append(list *lp, int n)
{

    //remember, lp->value does not work in this function because lp points to another list pointer, not to a list

    //while the value at the address that local lp points to is NOT NULL
    //set the address local lp will point to to the address of next elements pointer
    //-> Means moving the pointer of local lp to "next" of  element further down the list
    while (*lp != NULL)
    {lp = &((*lp)->next);}

    //have the address that local lp now points to be opened up with malloc for a new element
    (*lp) = (list) malloc(sizeof(struct element));
    (*lp)->value = n;
    (*lp)->next = NULL;
}

int main()
{
    list lp;
    append(&lp, 4); //send in the address of lp
    append(&lp, 2);
    append(&lp, 0);
    append(&lp, 1);
    append(&lp, 0);
    append(&lp, 3);
    append(&lp, 6);
    append(&lp, 8);
    append(&lp, 9);
    append(&lp, 14);
    append(&lp, 11);

    printList(&lp);

    printf("\nThe total sum of all values is: %d\n", sum(lp));

/*
    rmEvens(&lp);
    printf("The list without even numbers:\n");
    printList(&lp);
*/

    delmax(&lp);
    printf("The list without max values:\n");
    printList(&lp);

    return 0;
}