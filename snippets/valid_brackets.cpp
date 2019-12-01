#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool solve(const string& s)
{
    vector<char> stack;
    for (char ch : s)
    {
        if (ch == '(' || ch == '[' || ch == '{')
        {
            stack.push_back(ch);
        }
        else if (stack.empty())
        {
            return false;
        }
        else
        {
            if (ch == ')' && stack.back() == '(' || ch == '}' && stack.back() == '{' || ch == ']' && stack.back() == '[')
            {
                stack.pop_back();
            }
            else
            {
                return false;
            }
        }
    }
    return stack.empty();
}

int main()
{
    string s;
    cin >> s;
    cout << (solve(s) ? "YES" : "NO") << endl;
    return 0;
}