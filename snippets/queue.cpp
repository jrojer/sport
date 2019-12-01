#include <iostream>
#include <cstddef>

using namespace std; 

struct Queue
{
    int pop()
    {
        int val =  array_[i];
        i = (i+1) % max_size;
        return val;
    }
    void push(int x)
    {
        array_[j] = x;
        j = (j+1) % max_size;
    }
    static const size_t max_size = 100000;
    int array_[max_size];
    size_t i = 0;
    size_t j = 0;
};

int main()
{
    //freopen("input.txt","r",stdin);
    Queue queue;
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; ++i)
    {
        char cmd[2];
        scanf("%s",cmd);
        if(*cmd == '+')
        {
            int val;
            scanf("%d",&val);
            queue.push(val);
        }
        else
        {
            printf("%d\n",queue.pop());
        }
    }
    return 0;
}