#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <array>

using namespace std;

struct Item
{
    int value;
    string text;
};

string solution(int n)
{
    const std::vector<Item> table = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"},
    };

    string ans = "";
    int i = 0;
    while (n)
    {
        if (table[i].value <= n)
        {
            n -= table[i].value;
            ans += table[i].text;
        }
        else
        {
            ++i;
        }
    }
    return ans;
}

struct TestCase
{
    int n;
    string ans;
};

static const vector<TestCase> kTestCases = {
    {1, "I"},
    {2, "II"},
    {3, "III"},
    {4, "IV"},
    {5, "V"},
    {6, "VI"},
    {7, "VII"},
    {8, "VIII"},
    {9, "IX"},
    {10, "X"},
    {11, "XI"},
    {14, "XIV"},
    {15, "XV"},
    {58, "LVIII"},
    {1994, "MCMXCIV"},
    {2000, "MM"},
};

void test()
{
    int i = 0;
    for (const auto &tc : kTestCases)
    {
        auto answer = solution(tc.n);
        auto correct = tc.ans;
        if (correct == answer)
            printf("%d OK\n", i);
        else
            printf("%d FAIL\n", i);
        ++i;
    };
};

int main()
{
    test();
    return 0;
}