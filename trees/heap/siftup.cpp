#include <iostream>


class Heap
{
    public:
    Heap(size_t size): size_(size), array_(new int[size]())
    {
    }
    ~Heap()
    {
        delete[] array_;
    }
    void Insert(int v)
    {

    }
    void Print()
    {

    }
    int Change(int i, int x)
    {

    }

private:

    int SiftUp()
    {

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