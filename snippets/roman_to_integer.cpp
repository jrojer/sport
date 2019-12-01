#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <array>
#include <map>

using namespace std;


int solution(string s)
{

}

struct TestCase
{
    int ans;
    string n;
};

static const vector<TestCase> kTestCases = {

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