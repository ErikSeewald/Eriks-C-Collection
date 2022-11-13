#include <stdio.h>

void AckermannFunction();
int ack(int x, int y);

void palindromInput();
int palindrom(char str[], int n);

void swapInput();
void swap(int *x, int *y);


int main()
{
    int programIndex = 2;

    switch (programIndex)
    {
        case 0: AckermannFunction();
        break;
        case 1: palindromInput();
        break;
        case 2: swapInput();
    }
    return 0;
}

//Übung 4
void AckermannFunction()
{
    int x, y;
    scanf("%d", &x);
    scanf("%d", &y);
    int ackX = ack(x,y);
    if (ackX == -1){ printf("No negative numbers!");}
    else {printf("%d", ackX);}
}

int ack(int x, int y)
{
    if (x == 0 && y >= 0) {return y+1;}
    else if (y == 0 && x > 0) {return ack(x-1, 1);}
    else if (x > 0 && y > 0){return ack(x-1,ack(x, y-1));}

    else {return -1;}
}


void palindromInput()
{
    char str[] = "";
    int n;
    scanf("%s", &str);
    scanf("%d", &n);

    if (palindrom(str, n) == 1) { printf("%s ist ein Palindrom", str);}
    else { printf("%s ist kein Palindrom", str);}
}

int palindrom(char str[], int n)
{
    //to lower case
    for (int i = 0; i < n; i++)
    {
        if (str[i] > 64 && str[i] < 91)
        {str[i]+=32;}
    }

    int highP = n-1;
    int lowP = 0;

    while (highP > lowP)
    {
        if (str[highP] != str[lowP]) {return 0;}
        --highP;
        ++lowP;
    }
    return 1;
}

void swapInput()
{
    int x,y;
    scanf("%d", &x);
    scanf("%d", &y);

    swap(&x,&y);

    printf("%d,%d", x,y);
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

//Übung 5

