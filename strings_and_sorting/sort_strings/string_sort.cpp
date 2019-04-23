#include<iostream>

bool less(const char* s1, const char* s2)
{
    int i =0;
    while(!((s1[i] == 0 && s2[i] == 0) || s1[i]!=s2[i]))
        ++i;
    return s1[i] < s2[i];
}

template<typename T>
void swap(T& a, T&b)
{
    T t = a;
    a = b;
    b = t;
}

class Strings
{
public:
    Strings(int n, int k):
        num_strings_(n), 
        string_max_len_(k), 
        memory_(new char[n*k]()), 
        strings_(new char*[n]())
    {
        for(int  i = 0; i < n; ++i)
        {
            strings_[i] = memory_ + k*i;
        }
    }
    ~Strings()
    {
        delete[] strings_;
        delete[] memory_;
    }
    void ReadInput()
    {
        for(int i = 0; i < num_strings_; ++i)
        {
            scanf("%s",strings_[i]);
        }
    }
    void PrintOutput()
    {
        for(int i = 0; i < num_strings_; ++i)
        {
            printf("%s\n",strings_[i]);
        }
    }
    void Sort()
    {
        for(int k=1;k < num_strings_;++k)
        {
            int i = k;
            while(i > 0 && less(strings_[i],strings_[i-1]))
            {
                swap(strings_[i],strings_[i-1]);
                --i;
            }
        }
    }
private:
    const int num_strings_;
    const int string_max_len_;
    char* memory_;
    char** strings_;
};

int main()
{
    const int k = 100;
    int n =0;
    std::cin >> n;
    Strings s(n,k);
    s.ReadInput();
    s.Sort();
    s.PrintOutput();
    return 0;
}