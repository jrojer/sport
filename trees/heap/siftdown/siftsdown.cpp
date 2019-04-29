#include <iostream>

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
        array_[i] -= x;
        return SiftDown(i);
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

    size_t SiftDown(size_t i)
    {
        while(2*i <= size_) // at least one
        {
            int& a = array_[i];
            int& b = array_[2*i];
            if(2*i + 1 <= size_) // both
            {
                int& c = array_[2*i+1];

                if(a <= b && b <= c)        {swap(a,c); i = 2*i+1;}
                else if(a <= c && c <= b)   {swap(a,b); i = 2*i;}
                else if(b <= a && a <= c)   {swap(a,c); i = 2*i+1;}
                else if(c <= a && a <= b)   {swap(a,b); i = 2*i;}
                else 
                    break; 
            }
            else // only one 
            {
                if(b > a) {swap(b,a); i = 2*i;} 
            }
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