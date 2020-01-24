#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <array>
#include <map>

using namespace std;

vector<vector<int>> collect(const vector<int> &arr1, const vector<int> &arr2)
{
    vector<vector<int>> result;
    int k = 0;
    while (k < arr1.size())
    {
        int p = arr1[k];
        int i = 0;
        int j = arr2.size() - 1;
        while (i < j)
        {
            int expr = p + arr2[i] + arr2[j];
            if (expr == 0)
            {
                result.push_back({p, arr2[i], arr2[j]});
            }
            if (expr <= 0)
            {
                int val = arr2[i];
                while (i < arr2.size() && arr2[i] == val)
                    ++i;
            }
            if (expr >= 0)
            {
                int val = arr2[j];
                while (j >= 0 && arr2[j] == val)
                    --j;
            }
        }
        while (k < arr1.size() && arr1[k] == p)
            ++k;
    }
    return result;
}

vector<vector<int>> solution(const vector<int> &arr)
{
    vector<int> positive;
    vector<int> nonpositive;
    vector<vector<int>> result;
    for (int a : arr)
    {
        if (a > 0)
            positive.push_back(a);
        else
            nonpositive.push_back(a);
    }

    int num_zeros = 0;
    for(int p: nonpositive)
    {
        if(p==0)
        {
            ++num_zeros;
            if(num_zeros >= 3)
            {
                result.push_back({0,0,0});
                break;
            }
        }
    }

    if (positive.empty() || nonpositive.empty())
        return result;

    sort(positive.begin(), positive.end());
    sort(nonpositive.begin(), nonpositive.end());

    auto arr1 = collect(positive, nonpositive);
    auto arr2 = collect(nonpositive, positive);
    result.insert(result.end(), arr1.begin(), arr1.end());
    result.insert(result.end(), arr2.begin(), arr2.end());
    return result;
}

struct TestCase
{
    vector<int> arr;
    vector<vector<int>> ans;
};

static const vector<TestCase> kTestCases = {
    {{0,0,0,-1,-1,2},{{0,0,0},{2,-1,-1}}},
    {{0,0,0},{{0,0,0}}},
    {{-18, 1, 2}, {}},
    {{0, -1, -2}, {}},
    {{0, 1, 2}, {}},
    {{-1, 0, 1, 2, -1, 4}, {{1, -1, 0}, {2, -1, -1}}},
    {{-5,-4,-3,-3,-2,-2,-2,-1,0,0,1,1,2,3,4,4,5,6}, {}},
    {{-1, -1, 2}, {{2,-1, -1}}},
};

void test()
{
    int i = 0;
    for (const auto &tc : kTestCases)
    {
        auto answer = solution(tc.arr);
        auto correct = tc.ans;
        if (correct == answer || correct.empty())
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