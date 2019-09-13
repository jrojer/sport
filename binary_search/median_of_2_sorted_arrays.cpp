#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


double Median(const std::vector<int>& a)
{
    int m = a.size()/2; 
    if(a.size()%2==0)
    {
        return (a[m-1]+a[m])/2.0;
    }
    else
    {
        return a[m];
    }
}


double Median(const std::vector<int>& a, const std::vector<int>& b)
{
    const int n = a.size();
    const int m = b.size();

    if(n==0)
    {
        return Median(b);
    }
    else if(m==0)
    {
        return Median(a);
    }

    int a_beg = 0;
    int a_end = n;

    int i = (a_end+a_beg)/2;
    int j = (n+m)/2 - i;

    auto condition_1 = [&]()
    {
        return (j<=0 || i>=n || (j<=m && b[j-1] <= a[i]));
    };

    auto condition_2 = [&]()
    {
        return (i==0 || j>=m || (i-1 <= n && j >= 0 && a[i-1] <= b[j]));
    };

    while(!(condition_1() && condition_2()))
    {
        if(!condition_1())
        {
            a_beg = i+1;
        }
        else if(!condition_2())
        {
            a_end = i;
        }
        i = (a_end+a_beg)/2;
        j = (n+m)/2 - i;
    } // j in [0,m], i in [0,n]

    assert(0<=j && j<=m);
    assert(0<=i && i<=n);

    int left_max = 0;
    if(i>0 && j>0)
        left_max = std::max(a[i-1],b[j-1]);
    else if(i>0)
        left_max = a[i-1];
    else 
        left_max = b[j-1];

    int right_min = 0;
    if(i<n && j<m)
        right_min = std::min(a[i],b[j]);
    else if(i<n)
        right_min = a[i];
    else 
        right_min = b[j];

    if( (n+m) % 2 == 0)
    {
        return (left_max + right_min)/2.0;
    }
    else
    {
        return right_min;
    }
}

struct TestCase
{
    std::vector<int> a;
    std::vector<int> b;
    double answer;
};

void Test(const TestCase& t,int i)
{
    printf(Median(t.a,t.b) == t.answer ? "%d OK\n" : "%d FAIL\n",i);
}


static const std::vector<TestCase> kTestCases = {

    {{1,2,3,5,6},{4},3.5},
    {{1,2},{},1.5},
    {{1},{},1.0},
    {{8,8,8},{3,3,3},5.5},
    {{8,8},{3,3,3},3.0},
    {{1,2},{3,3,3},3.0},
    {{},{1,2,2,3,3,3},2.5},
    {{1},{2,2,3,3,3},2.5},
    {{1},{2,2,2,2,2},2.0},
    {{2,2,2,2,2,2,2,2,2,2,2},{1,1,1},2.0},
    {{2,2,2,2,2},{1},2.0},
    {{1,1,1,1,1},{1},1.0},
    {{1},{1},1.0},
    {{1},{2,3},2.0},
    {{1},{4},2.5},
    {{4},{1},2.5},
    {{4,5,6},{1,2,3},3.5},
    {{4,5,6},{1,2,3},3.5},
    {{1,2,3},{4,5,6},3.5},
    {{2,2,2,3},{2,3},2.0},
    {{1,2,3,4},{0,1,1,5,6,6},2.5},
};

void test()
{
    for(int i=0;i<kTestCases.size();++i)
    {
        Test(kTestCases[i],i);
    }
}


int main()
{
    //freopen(R"(E:\projects\csc\input.txt)","r",stdin);

    test();

    return 0;
}
