#include <iostream>
#include <cstddef>

using namespace std; 

struct Stack
{
    int pop()
    {
        --i;
        if(array_[i] == min_array_[im-1])
        {
            --im;
        }
        return array_[i];
    }
    void push(int x)
    {
        if(i == 0 || x <= min_array_[im-1])
        {
            min_array_[im++] = x;
        }
        array_[i++] = x;
    }
    int min()
    {
        return min_array_[im-1];
    }
    ~Stack()
    {
        delete[] array_;
        delete[] min_array_;
    }
    static const size_t max_size = 1000000;
    int* array_ = new int[max_size];
    int* min_array_ = new int[max_size];
    size_t i = 0;
    size_t im = 0;
};

int main()
{
    freopen("input.txt","r",stdin);
    Stack stack;
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; ++i)
    {
        int cmd;
        scanf("%d",&cmd);
        if(cmd == 1)
        {
            int val;
            scanf("%d",&val);
            stack.push(val);
        }
        else if(cmd == 2)
        {
            stack.pop();
        }
        else
        {
            printf("%d\n",stack.min());
        }
        
    }
    return 0;
}