#include<vector>
#include<deque>
#include<iostream>

std::vector<int> Merge(const std::vector<int>& a, const std::vector<int>& b)
{
    std::vector<int> c;

    size_t i = 0;
    size_t j = 0;

    while(i < a.size() && j < b.size())
    {
        if(a[i]<b[j])
            c.push_back(a[i++]);
        else
            c.push_back(b[j++]);
    }
    while(i < a.size())
    {
        c.push_back(a[i++]);
    }
    while(j < b.size())
    {
        c.push_back(b[j++]);
    }

    return c;
}


std::vector<int> MergeSort(const std::vector<int>& array)
{
    std::deque<std::vector<int>> fifo(array.size(), {0});

    for(size_t i=0 ;i<array.size();++i)
    {
        fifo[i][0]=array[i];
    }

    while(fifo.size()>1)
    {
        const auto& a = fifo[fifo.size()-1];
        const auto& b = fifo[fifo.size()-2];
        const auto& c = Merge(a,b);
        fifo.pop_back();
        fifo.pop_back();
        fifo.push_front(c);
    }
    return fifo[0];
}

void test()
{
    std::vector<int> a = {5,7,1,2,3,3,8,6,6};

    auto c = MergeSort(a);

    for(auto x : c) printf("%d ",x);

}

int main()
{
    test();
    return 0;
}
