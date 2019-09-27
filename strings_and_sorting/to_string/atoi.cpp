#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;


bool IsSign(char ch)
{
    return ch == '-' || ch == '+';
}

bool IsDigit(char ch)
{
    return '0' <= ch && ch <= '9';
}

int solve(const string& s) 
{
    int64_t value = 0;
    enum Mode {kSkipping, kReading} mode = kSkipping;
    int sign = 0;
    int i =0;
    while(i<s.size())
    {
        char ch = s[i];
        if(mode == kSkipping)
        {
            if(ch==' ')
            {
                ++i;
            }
            else if(IsSign(ch))
            {
                sign = ch=='-'?-1:1;
                mode = kReading;
                ++i;
            }
            else if(IsDigit(ch))
            {
                sign = 1;
                mode = kReading;
            }
            else
            {
                return 0;
            }
        }
        else // kReading
        {
            if(!IsDigit(ch))
            {
                return sign*value;
            }
            else
            {
                int digit_value = ch-'0';
                value = value*10 + digit_value;
                if(sign*value < INT32_MIN)
                {
                    return INT32_MIN;
                }
                else if(sign*value > INT32_MAX)
                {
                    return INT32_MAX;
                }
                ++i;
            }
        }
    }
    return sign*value;
}

struct TestCase
{
    string s;
    int res;
};

static const vector<TestCase> kTestCases = {
    {"-2147483648",-2147483648},
    {"   -42",-42},
    {"   -42 with words",-42},
    {"91283+472332", 91283},
    {"91283472332", INT32_MAX},
    {"-91283472332", -2147483648},
    {"words and 987",0},
    {"2147483647",2147483647},
    {"+123",123},
    {"-123",-123},
    {"0",0},
    {"12",12},
    {"",0},
    {"      ",0},
    {"   123b456",123},
    {" -",0},
    {"-",0},
    {"+",0},
    {"+abc",0},
};

void test()
{
    int i = 0;
    for(const auto& tc: kTestCases)
    {
        int a = solve(tc.s);
        int b = tc.res;
        printf(a==b?"%d OK\n" : "%d FAIL\n",i);
        //printf("%20d %20d\n",a,b);
        ++i;
    };
};

int main()
{
    test();
    return 0;
}
