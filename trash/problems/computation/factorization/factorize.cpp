#include <iostream>
#include <vector>

std::vector<int> FastFactorize(int n)
{
    std::vector<int> res;
    int k = n;
    int l = 2;
    while(k > 1)
    {
        while(k%l > 0)
        {
            ++l;
        }
        res.push_back(l);
        k /= l;
    }
    return res;
}

void PrintArray(const std::vector<int>& array)
{
    size_t i = 0;
    for(; i+1 < array.size(); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("%d\n", array[i]);
}

int main()
{
    int n;
    scanf("%d", &n);
    PrintArray(FastFactorize(n));
    return 0;
}
