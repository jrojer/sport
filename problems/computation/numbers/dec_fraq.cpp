#include <iostream>


void PrintFraq(int x, int d, int n)
{
    int q = x/d;
    int r = x%d;
    x = r*10;
    printf("0.");
    for(int i=0;i<n;++i)
    {
        q = x/d;
        r = x%d;
        x = r*10;
        printf("%d",q);
    }
    printf("\n");
}

int main() 
{
    int x,d,n;
    scanf("%d %d %d",&x,&d,&n);
    PrintFraq(x,d,n);
    return 0;
}


