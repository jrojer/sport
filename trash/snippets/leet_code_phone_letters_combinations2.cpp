#include <vector>
#include <string>

using namespace std;

const vector<vector<char>> table = {
    {'a', 'b', 'c'},
    {'d', 'e', 'f'},
    {'g', 'h', 'i'},
    {'j', 'k', 'l'},
    {'m', 'n', 'o'},
    {'q', 'p', 'r', 's'},
    {'t', 'u', 'v'},
    {'w', 'x', 'y', 'z'}};


void recurse(const string& pat, string& s, size_t i, vector<string>& result)
{
    if(i == pat.size())
    {
        result.push_back(s);
        return;
    }
    const auto& letters = table[pat[i]-'0'-2];
    for(char l : letters)
    {
        s += l;
        recurse(pat,s,i+1,result);
        s.pop_back();
    }
}

vector<string> letterCombinations(string digits)
{
    string s;
    vector<string> result;
    recurse(digits,s,0,result);
    return result;
}

int main()
{
    letterCombinations("");

    return 0;
}