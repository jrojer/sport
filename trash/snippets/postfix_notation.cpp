#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main()
{
    //freopen("input.txt","r",stdin);
    const size_t size = 201;
    char s[size] = {};
    cin.getline(s,size);
    vector<int> stack;
    for(char ch: s)
    {
        if(ch == 0)
        {
            break;
        }
        if(ch == ' ')
        {
            continue;
        }
        if(isdigit(ch))
        {
            stack.push_back(ch-'0');
        }
        else 
        {
            int a = stack.back();
            stack.pop_back();
            int b = stack.back();
            stack.pop_back();
            if(ch == '+')
            {
                stack.push_back(a+b);
            }
            else if(ch == '-')
            {
                stack.push_back(b-a);
            }
            else if(ch == '*')
            {
                stack.push_back(a*b);
            }
        }
    }
    cout << stack.back() << endl;
    return 0;
}