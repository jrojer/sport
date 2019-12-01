#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdlib>

using namespace std;


int MaxArea(const vector<int>& h)
{
    int max = 0;
    int l =0 ;
    int r = h.size()-1;

    while(l < r)
    {
        int s = (r-l) * std::min(h[l],h[r]);
        max = std::max(max,s);
        if(h[l] < h[r])
        {
            ++l;
        }
        else if(h[l] > h[r])
        {
            --r;
        }
        else if(h[l] == h[r])
        {
            ++l;
            --r;
        }
    }

    return max;
} 

int MaxArea2(const vector<int>& h)
{
    int count = h.size();
    int max=0;
    for(int i=0;i<count;++i)
    {
        for (int j=i+1; j < count; ++j)
        {
            int s = (j-i) * std::min(h[i],h[j]);
            if(s>max)
                max = s;
        }
    }
    return max;
} 

struct TestCase
{
    vector<int> array;
};

static const vector<TestCase> kTestCases = {
    {{3,4,2,2,5,1,3,5,6,4}},
    {{1,2,3,4,5}},
    {{2,1,4,4,5}},
    {{1}},
    {{1,2}},
    {{2,1}},
    {{3,2,1}},
    {{5,4,3,2,1}},
    {{1,2,3,4,5}},
    {{4,4,4,4,4}},
    {{4,4,1,4,4}},
    {{1,4,1,4,1}},
    {{1,4,100,4,1}},
    {{}},
    {{1,2,3}},
    {{3,2,3}},
    {{4,2}},
    {{0,1,2,3,0}},
    {{0}},
    {{0,0,0,0}},
    {{1,0,0,0}},
};

void test()
{
    int i = 0;
    for(const auto& tc: kTestCases)
    {
        int correct = MaxArea2(tc.array);
        int answer = MaxArea(tc.array);
        if(correct == answer)
            printf("%d OK\n",i);
        else
            printf("%d FAIL\n",i);
        ++i;
    };
};

int main()
{
    test();
    return 0;
}