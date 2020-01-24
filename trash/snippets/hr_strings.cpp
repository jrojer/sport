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

// Complete the isValid function below.
string isValid(string s) 
{
    struct Int
    {
        int val = 0;
    };
    unordered_map<char,Int> char_hist;
    unordered_map<int,Int> freq_hist;
    for(char ch : s)
    {
        ++char_hist[ch].val;
    }
    for(auto pair: char_hist)
    {
        ++freq_hist[pair.second.val].val;
    }
    if(freq_hist.size() == 1)
    {
        return "YES";
    }
    else if(freq_hist.size() == 2)
    {
        auto a = freq_hist.begin();
        auto b = next(freq_hist.begin());
        if(a->second.val == 1 && b->second.val == 1) 
        {
            if(abs(a->first - b->first) <= 1)
            {
                return "YES";
            }
            else
            {
                return "NO";
            }
        }
        else if(a->second.val == 1)
        {
            if(a->first - b->first <= 1)
            {
                return "YES";
            }
            else
            {
                return "NO";
            }
        }
        else if(b->second.val == 1)
        {
            if(b->first - a->first <= 1)
            {
                return "YES";
            }
            else
            {
                return "NO";
            }
        }
        else
        {
            return "NO";
        }
    }
    else
    {
        return "NO";
    }
    
}

int main()
{
    freopen("input.txt", "r", stdin);

    string s;
    getline(cin, s);

    string result = isValid(s);

    cout << result << "\n";


    return 0;
}
