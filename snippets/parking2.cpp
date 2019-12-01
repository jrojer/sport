#include <iostream>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    const int max_num = 30;
    int next_available[max_num];
    for (int i = 1; i <= n; ++i)
    {
        next_available[i] = i;
    }
    for (int i = 0; i < n; ++i)
    {
        int p;
        scanf("%d", &p);
        p = next_available[p];
        printf("%d ", p);
        next_available[p] = p + 1 <= n ? next_available[p + 1] : next_available[1];
    }
    puts("");
    return 0;
}