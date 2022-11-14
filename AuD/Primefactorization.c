# include <stdio.h>
# include <math.h>

int primfac(int a[], int s)
{
    int arrIndex = 0;

    while (s%2 == 0)
    {
        a[arrIndex] = 2;
        ++arrIndex;
        s = s/2;
    }

    // n is odd at this point
    for (int i = 3; i <= sqrt(s); i = i+2)
    {
        while (s%i == 0)
        {
            a[arrIndex] = i;
            ++arrIndex;
            s = s/i;
        }
    }

    //means we just exited out of the for loop instead of going immediately from the first loop to the end
    //only needed if you only go to sqrt(s)
    if (s > 2)
    {
        a[arrIndex] = s;
        ++arrIndex;
    }

    return arrIndex;
}

void printArray(int a[], int z)
{
    for (int i = 0; i < z; i++)
    {
        printf("%d\n", a[i]);
    }
}

int main()
{
    int a[24];
    int s = sizeof(a) / sizeof(a[0]);
    int z = primfac(a, s);
    printf("Amount of prime factors: %d\n",z);
    printf("Prime factorization:\n");
    printArray(a, z);
    return 0;
}