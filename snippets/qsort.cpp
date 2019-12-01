#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdlib>

using namespace std;

int partition(vector<int>& array, int begin, int end)
{
    int len = end-begin;
    swap(array[begin],array[rand()%len + begin]);
    int pivot = array[begin];
    int l=begin+1;
    int g=begin+1;
    while(l<end)
    {
        if(array[l] <= pivot)
        {
            swap(array[l],array[g]);
            ++g;
        }
        ++l;
    }
    swap(array[begin],array[g-1]);
    return g-1;
}

void qsort(vector<int>& array, int begin, int end)
{
    int m = partition(array,begin,end);
    if(m - begin > 1)
        qsort(array,begin,m);
    if(end - m > 1)
        qsort(array,m,end);
}

struct TestCase
{
    vector<int> array;
};

static const vector<TestCase> kTestCases = {
    {{1,2,3,4,5}},
    {{2,1,4,4,5}},
    {{1}},
    {{1,2}},
    {{2,1}},
    {{3,2,1}},
    {{3,4,2,2,5,1,3,5,6,4}},
};

void test()
{
    int i = 0;
    for(const auto& tc: kTestCases)
    {
        auto correct = tc.array;
        auto answer = tc.array;
        sort(correct.begin(),correct.end());
        qsort(answer,0,answer.size());
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