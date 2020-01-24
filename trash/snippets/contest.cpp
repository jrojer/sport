#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <set>

using namespace std;

int main()
{
    freopen("input.txt","r",stdin);
    int n;
    scanf("%d",&n);
    vector<int> arr(n+1);
    set<int> vals;
    for(int i = 0; i < n; ++i)
    {
        vals.insert(i+1);
    }
    for(int i = 0; i < n; ++i)
    {
        int a;
        scanf("%d",&a);
        if(a != 0)
        {
            vals.erase(a);
        }
        arr[i] = a;
    }
    auto iter = vals.rbegin();
    for(int i = 0; i < n; ++i)
    {
        int a = arr[i];
        if(a == 0)
        {
            a = *iter;
            iter = next(iter);
        }
        printf("%d ", a);
    }
    puts("");
    return 0;
}