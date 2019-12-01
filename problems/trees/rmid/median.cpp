#include <iostream>

void swap(int& a,int& b)
{
    int t = a;
    a = b;
    b = t;
}

void PrintArray(int* a, int size)
{
    for(int i = 0; i < size; ++i)
    {
        std::cout<< a[i] << " ";
    }
    std::cout << std::endl;
}

struct Heap
{
    Heap(): array_(new int[10010]()),idx_(1),median_idx_(0)
    {}
    ~Heap()
    {
        delete[] array_;
    }
    void up(int i)
    {
        while(i/2 > 0 && array_[i/2] < array_[i])
        {
            swap(array_[i/2], array_[i]);
            i = i/2;
        }
    }
    void down(int i)
    {
        while(2*i+1 < idx_)
        {
            int j = array_[2*i] > array_[2*i+1] ? 2*i : 2*i+1;
            swap(array_[i],array_[j]);
            i = j;
        }
        if(2*i < idx_ && array_[2*i] > array_[i])
        {
            swap(array_[i],array_[2*i]);
        }
    }
    void insert(int value)
    {
        array_[idx_] = value;
        up(idx_);
        ++idx_;
    }
    int extract()
    {
        int ret = array_[1];
        array_[1] = array_[--idx_];
        down(1);
        return ret;
    }
    void RemoveMedian()
    {
        if(idx_ < 2)
            return;
        int max_item = array_[1];

        int next_median_idx_ = median_idx_/2;
        array_[median_idx_] = max_item;
        up(median_idx_);
    }
    int* array_;
    int idx_;
    int median_idx_;
};

void test()
{
    Heap h;
    int a[] = {9,10,2,5,1,18};
    for(auto item: a)
    {
        h.insert(item);
    }
    PrintArray(h.array_,h.idx_);
}

int main()
{
    test();
    return 0 ;
}