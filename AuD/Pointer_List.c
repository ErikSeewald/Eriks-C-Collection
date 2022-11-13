#include <stdio.h>
#include <stdlib.h>

typedef struct element *list;
struct element { int value; list next; };

void printList(list *lp)
{
    list printP = *lp;
    while (printP != NULL)
    {
        printf("%d\n", printP->value);
        printP = printP->next;
    }
}

int sum(list *lp)
{
    int sum = 0;
    list sumP = *lp;
    while (sumP != NULL)
    {
        sum+= sumP->value;
        sumP = sumP->next;
    }
    return sum;
}

void rmEvens(list *lp)
{
    while (*lp != NULL)
    {
        if ((*lp)->value % 2 == 0)
        {*lp = (*lp)->next;}
        lp = &((*lp)->next);
    }
}

void append(list *lp, int n)
{
    //while the value at the address that local lp points to is NOT NULL
    //set the value of local lp to the address that local lp used to point to
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
    append(&lp, 5);
    append(&lp, 2);
    append(&lp, 1);
    append(&lp, 0);
    append(&lp, 3);
    append(&lp, 8);
    append(&lp, 9);
    append(&lp, 11);

    printList(&lp);

    printf("\nThe total sum of all values is: %d\n", sum(&lp));

    rmEvens(&lp);
    printf("The list without even numbers:\n");
    printList(&lp);

    return 0;
}