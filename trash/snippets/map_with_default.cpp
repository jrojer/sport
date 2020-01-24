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

// Complete the sherlockAndAnagrams function below.
/*
0123
abba

0 - 3
01 - 23
1 - 2
012 - 123

0123
kkkk

1
0 - 1, 0 - 2, 0 - 3, 1 - 2, 1 - 3, 2 - 3
2
01 - 12, 01 - 23, 12 - 23
3
012 - 123

for len = 1 .. n
  for subst of len = 1 .. all substr
    for substr of len = next .. all substr
      if match
        ++count

0123456789
ifailuhkqq

*/
int sherlockAndAnagrams(const string& s) 
{
    struct Count
    {
        size_t val = 0;
        bool operator==(const Count& other) const
        {
            return other.val == val;
        }
    };
    size_t n = s.size();
    int count = 0;
    for(size_t len = 1; len < n; ++len)
    {
        unordered_map<char,Count> map1;
        for(size_t i = 0; i < len; ++i)
        {
            ++map1[s[i]].val;
        }
        for(size_t p1 = 0; p1 + len < n; ++p1)
        {
            auto map2 = map1;
            for(size_t p2 = p1; p2 + len <= n; ++p2)
            {
                ++map2[s[len + p2]].val;
                auto iter = map2.find(s[p2]);
                if(--iter->second.val == 0)
                {
                    map2.erase(iter);
                }
                count += map1 == map2;
            }
            ++map1[s[len + p1]].val;
            auto iter = map1.find(s[p1]);
            if(--iter->second.val == 0)
            {
                map1.erase(iter);
            }
        }
    }
    return count;
}

int main()
{
    freopen("input.txt","r",stdin);
    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        cout << result << "\n";
    }


    return 0;
}

