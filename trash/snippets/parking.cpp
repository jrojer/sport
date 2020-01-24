#include <iostream>
#include <set>
#include <cstdint>

using namespace std;

int main()
{
    //freopen("input.txt","r",stdin);
    int n;
    scanf("%d", &n);
    std::set<int> set;
    for (int i = 1; i <= n; ++i)
    {
        set.insert(i);
    }
    for (int i = 0; i < n; ++i)
    {
        int p;
        scanf("%d",&p);
        auto iter = set.lower_bound(p);
        if(iter == set.end())
        {
            iter = set.lower_bound(1);
        }
        printf("%d ", *iter);
        set.erase(iter);
    }
    puts("");
    return 0;
}