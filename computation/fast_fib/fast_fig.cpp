#include <iostream>
#include <cstdint>
#include <array>

typedef std::array<uint64_t,4> matr_t;

matr_t mul(const matr_t a, const matr_t b, int m)
{
    matr_t t;
    t[0] = ((a[0]*b[0])%m + (a[1]*b[2])%m)%m;
    t[1] = ((a[0]*b[1])%m + (a[1]*b[3])%m)%m;
    t[2] = ((a[2]*b[0])%m + (a[3]*b[2])%m)%m;
    t[3] = ((a[2]*b[1])%m + (a[3]*b[3])%m)%m;
    return t;
}

matr_t pow(const matr_t& a, uint64_t n, int m)
{
    matr_t c = a;
    matr_t b = {1,0,0,1};
    uint64_t k = n;
    while(k>0)
    {
        if(k%2==0)
        {
            c = mul(c,c,m);
            k /= 2;
        }
        else
        {
            b = mul(b,c,m);
            k -= 1;
        }
    }
    return b;
}

uint64_t fib(uint64_t n, int m)
{
    if(n == 0)
        return 0;
    if(n < 2)
        return 1;
    matr_t a = pow({1,1,1,0},n-2,m);
    return (a[0]+a[2])%m;
}

int main()
{
    int n = 0;
    std::cin >> n;
    for(int i = 0; i < n; ++i)
    {
        uint64_t v = 0;
        std::cin >> v;
        std::cout << v << std::endl;
        std::cout << fib(v,123456789) << std::endl;
    }
    
    return 0;
}