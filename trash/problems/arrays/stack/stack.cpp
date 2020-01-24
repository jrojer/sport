#include <iostream>

struct Stack
{
    Stack(int max_size): max_size_(max_size), array_(new int[max_size]), size_(0)
    {}
    ~Stack()
    {
        delete[] array_;
    }
    void push(int a)
    {
        array_[size_++] = a;
    }
    bool empty()
    {
        return size_ == 0;
    }
    bool full()
    {
        return size_ == max_size_;
    }
    int size()
    {
        return size_;
    }
    int top()
    {
        return array_[size_-1];
    }
    int pop()
    {
        return array_[--size_];
    }
    int max_size_;
    int* array_;
    int size_;
};

bool CompareStrings(const char* a, const char* b, int begin, int end)
{
    int i = begin; 
    for(;i < end && a[i] > 0 && b[i] > 0; ++i)
    {
        if(a[i]!=b[i])
            return false;
    }
    return i == end || a[i] == 0 && b[i] == 0;  
}

bool IsEqual(const char* a, const char* b)
{
    int i = 0; 
    for(;a[i] > 0 && b[i] > 0; ++i)
    {
        if(a[i]!=b[i])
            return false;
    }
    return a[i] == 0 && b[i] == 0;  
}

int main() {
    int max_size = 0;
    int num_reqs = 0;
    scanf("%d",&max_size);
    scanf("%d",&num_reqs);
    
    Stack s(max_size);
    
    for(int i=0; i < num_reqs; ++i)
    {
        char str[100]={};
        scanf("%s",str);
        if(IsEqual(str,"push"))
        {
            int val = 0;
            scanf("%d",&val);
            if(s.full())
            {
                printf("FULL\n");
            }
            else
            {
                printf("OK\n");
                s.push(val);
            }
        }
        else if(IsEqual(str,"pop"))
        {
            if(s.empty())
            {
                printf("EMPTY\n");
            }
            else
            {
                printf("%d\n", s.pop());
            }
        }
        else if(IsEqual(str,"top"))
        {
            if(s.empty())
            {
                printf("EMPTY\n");
            }
            else
            {
                printf("%d\n", s.top());
            }
        }
        else if(IsEqual(str,"empty"))
        {
            printf(s.empty() ? "TRUE\n":"FALSE\n");
        }
        else if(IsEqual(str,"size"))
        {
            printf("%d\n", s.size());
        }
    }
    
    return 0;
}