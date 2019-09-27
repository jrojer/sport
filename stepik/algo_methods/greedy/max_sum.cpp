#include <iostream>
#include <cmath>

int main()
{
    int n;
    scanf("%d",&n);
    int k = trunc((sqrt(1+8*n)-1)/2);
    int rem = (n-(k+1)*k/2);
    int i = 1;
    printf("%d\n",k);
    while(n >= i+i+1)
    {
        printf("%d ",i);
        n -= i;
        i += 1;
    }
    printf("%d\n",rem+i);
    return 0;
}
