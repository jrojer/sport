#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cstdint>
#include <cstddef>
#include <climits>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
1 2 2
1 2 1


2 4 2 6 1 7 8 9 2 1
1 2 1 2 1 2 3 4 2 1 | 19


2 4 3 5 2 6 4 5 
1 2 1 2 1 2 1 2


1 2 3 4 4 4 4 2
1 2 3 4 1 1 2 1

1 2 3 4 4 4 4 2 1
1 2 3 4 1 1 3 2 1


       6 7 7 6 6 6 6 5 2 1 1 1 3 2 1
answer 1 2 2 1 1 1 4 3 2 1 1 1 3 2 1
depth  0 0 1 0 0 0 3 2 1 0 0 0 2 1 0

1 2 3 4 5 6 6 6 6 6 6 6
1 1 1 2 2 2
1 1 1 2 1 1
ans[]
len[] descent 

    1 2 2
len 0 0 0 
ans 1 2
*/

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    vector<int> up(n);
    up[0] = 1;
    for (int i = 1; i < n; ++i)
    {
        if (arr[i - 1] < arr[i])
        {
            up[i] = up[i - 1] + 1;
        }
        else
        {
            up[i] = 1;
        }
    }

    vector<int> down(n);
    down[n-1] = 1;
    for (int i = n-1; i > 0; --i)
    {
        if(arr[i - 1]  > arr[i])
        {
            down[i-1] = down[i] + 1;
        }
        else
        {
            down[i-1] = 1;
        }
    }

    long long int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += max(up[i], down[i]);
    }

    cout << ans;

    return 0;
}

long candies2(int n, vector<int> &arr)
{
    vector<int> dep(arr.size());
    vector<int> ans(arr.size());
    ans[0] = 1;
    for (int i = 1; i < arr.size(); ++i)
    {
        if (arr[i] >= arr[i - 1])
        {
            int j = i + 1;
            while (j < arr.size() && arr[j - 1] > arr[j])
            {
                ++j;
                ++dep[i];
            }
        }
        else
        {
            dep[i] = dep[i - 1] - 1;
        }
        if (arr[i] > arr[i - 1])
        {
            ans[i] = max(ans[i - 1], dep[i]) + 1;
        }
        else
        {
            ans[i] = dep[i] + 1;
        }
    }
    return accumulate(ans.begin(), ans.end(), 0);
}

int main2()
{
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        int arr_item;
        cin >> arr_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        arr[i] = arr_item;
    }

    long result = candies2(n, arr);

    cout << result << "\n";

    return 0;
}
