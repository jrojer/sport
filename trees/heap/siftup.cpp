#include <iostream>

//Задача №1164. Увеличение приоритета. PDF стр. 9, задача 1.
//https://informatics.msk.ru/mod/statements/view.php?id=1234#1


template<typename T>
void swap(T& a,T& b)
{
    T t  = a;
    a = b;
    b = t;
}

class Heap
{
    public:
    Heap(size_t size): size_(0), array_(new int[size+1]())
    {
    }
    ~Heap()
    {
        delete[] array_;
    }
    void Insert(int v)
    {
        array_[++size_] = v;
        SiftUp(size_);
    }
    void Print()
    {
        size_t i = 1;
        for(; i < size_; ++i)
        {
            printf("%d ",array_[i]);
        }
        printf("%d\n",array_[i]);
    }
    int Change(int i, int x)
    {
        array_[i] += x;
        return SiftUp(i);
    }

private:

    int SiftUp(int i)
    {
        while(i/2 > 0 && array_[i/2] < array_[i])
        {
            swap(array_[i/2], array_[i]);
            i/=2;
        }
        return i;
    }

    size_t size_;
    int* array_;
};

int main()
{
    int n;
    scanf("%d",&n);
    Heap heap(n);
    for(int i = 0; i < n; ++i)
    {
        int v ;
        scanf("%d",&v);
        heap.Insert(v);
    }
    int k;
    scanf("%d",&k);
    for(int i = 0; i < k; ++i)
    {
        int j,x;
        scanf("%d %d",&j,&x);
        printf("%d\n",heap.Change(j,x));
    }
    heap.Print();
    return 0;
}