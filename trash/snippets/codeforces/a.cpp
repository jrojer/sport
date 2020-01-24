#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <set>

using namespace std;

int main()
{
    freopen("./codeforces/input.txt","r",stdin);
    int q = 0;
    int x = 0;
    scanf("%d %d", &q, &x);
    set<int> s;
    int t = 0;
    int count = 0;
    for (int i = 0; i < q; ++i)
    {
        int y;
        scanf("%d", &y);
        s.insert(y % x);
        if (s.size() == x)
        {
            ++t;
            s.clear();
            count = 0;
        }
        else
        {
            count = *s.lower_bound(count)+1;
        }
        printf("%d\n", t * x + count);
    }
    return 0;
}