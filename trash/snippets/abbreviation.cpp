#include <vector>
#include <iostream>
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

bool Abbreviation(string& a, string& b) 
{
    if(b.empty())
    {
        return all_of(a.begin(),a.end(),[](char ch){return islower(ch);});
    }
    else if(a.empty())
    {
        return false;
    }
    // dp[i][j] := a[0..j-1] matches b[0..i-1]
    vector<vector<bool>> dp(b.size()+1,vector<bool>(a.size()+1,false));
    dp[0][0] = true;
    for(int i = 1; i <= a.size() && islower(a[i-1]); ++i)
    {
        dp[0][i] = true;
    }
    for(int i = 1; i <= b.size(); ++i)
    {
        for(int j = 1; j <= a.size(); ++j)
        {
            bool b1 = dp[i-1][j-1];
            bool b2 = (a[j-1] == b[i-1] || toupper(a[j-1]) == b[i-1]);
            bool b3 = dp[i][j-1];
            bool b4 = islower(a[j-1]);
            dp[i][j] =  b1 && b2 || b3 && b4;
        }
    }
    return dp[b.size()][a.size()];
}

string abbreviation(string& a, string& b) 
{
   return Abbreviation(a,b) ? "YES" : "NO"; 
}

int main()
{
    freopen("input.txt","r",stdin);
    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = abbreviation(a, b);

        cout << result << "\n";
    }

    return 0;
}
