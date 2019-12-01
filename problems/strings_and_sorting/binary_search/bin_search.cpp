#include <iostream>
#include <vector>
#include <algorithm>

struct SearchResult
{
    size_t value;
    bool found;
};

struct Item
{
    int value;
    size_t pos;
};

SearchResult BinarySearch(const std::vector<Item>& seq, int value)
{
    size_t a = 0;
    size_t b = seq.size();
    while(b-a > 1)
    {
        size_t m = (b+a)/2;
        if(value < seq[m].value)
            b = m;
        else 
            a = m;
    }
    return !seq.empty() && seq[a].value == value ? SearchResult{seq[a].pos,true} : SearchResult{0,false};
}

std::vector<Item> ReadSeq(size_t count)
{
    std::vector<Item> result;
    for(size_t i=0;i<count;++i)
    {
        int value;
        std::cin >> value;
        result.push_back({value,i});
    }
    return result;
}

void Print(const SearchResult& search_res)
{
    if(search_res.found)
    {
        std::cout << search_res.value << std::endl;
    }
    else
    {
        std::cout << "not found" << std::endl;
    }
}

int main()
{
    size_t n,k;
    std::cin >> n;
    auto seq = ReadSeq(n);
    std::cin >> k;
    std::stable_sort(seq.begin(),seq.end(),[](const auto& i, const auto& j){return i.value <= j.value;});
    for(size_t i= 0; i< k;++i)
    {
        int val;
        std::cin >> val;
        Print(BinarySearch(seq,val));
    }
    return 0;
}