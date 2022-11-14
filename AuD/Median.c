#include <stdio.h>

int median(int a[], int s)
{
    int low, high;

    for (int i = 0; i < s; i++)
    {
        low = 0;
        high = 0;

        for (int j = 0; j < s; j++)
        {
            if (a[j] > a[i])
            {++high;}
            else if (a[j] < a[i])
            {++low;}
        }

        if (low <= s/2 && high <= s/2)
        {return a[i];}
    }
}

int main()
{
    int a[] = {3,6,4,3,3,5,7,8,9};
    int s = sizeof(a) / sizeof(a[0]);
    int m = median(a,s); //only gives you one median, but multiple medians are possible
    printf("The median is: %d", m);

    return 0;
}