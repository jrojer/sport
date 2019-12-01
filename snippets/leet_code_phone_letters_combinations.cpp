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

struct Item
{
    const vector<char> &v;
    size_t idx;
    size_t end;
};

bool Increment(vector<Item> &items)
{
    bool end = false;
    auto iter = items.rbegin();
    ++iter->idx;
    while (iter->idx >= iter->end)
    {
        iter->idx = 0;
        iter = next(iter);
        if (iter == items.rend())
        {
            end = true;
            break;
        }
        else
        {
            ++iter->idx;
        }
    }
    return end;
}

vector<string> letterCombinations(string digits)
{
    if(digits.empty())
    {
        return {};
    }
    vector<Item> items;
    for (char ch : digits)
    {
        const auto &letters = table[ch - '0' - 2];
        items.push_back({letters, 0, letters.size()});
    }
    vector<string> result;
    bool end = false;
    while (!end)
    {
        string s;
        for (auto &x : items)
        {
            s += x.v[x.idx];
        }
        result.push_back(s);
        end = Increment(items);
    }
    return result;
}

int main()
{
    letterCombinations("2");

    return 0;
}