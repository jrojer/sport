#include <iostream>
#include <cstddef>

using namespace std; 

struct Stack
{
    int pop()
    {
        return array_[--i];
    }
    void push(int x)
    {
        array_[i++] = x;
    }
    static const size_t max_size = 100000;
    int array_[max_size];
    size_t i = 0;
};

int main()
{
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
        else
        {
            printf("%d\n",stack.pop());
        }
    }
    return 0;
}