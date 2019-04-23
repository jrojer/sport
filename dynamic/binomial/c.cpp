#include <iostream>
#include <cstdint>


struct Binomial 
{
    uint64_t Compute(int n, int k)
    {
        if(cached[n][k])
            return cache[n][k];
           
        if(k == 0)
            return 1;

        if(n == 0)
            return 0;
        
        uint64_t value = Compute(n-1,k-1) + Compute(n-1,k);
        
        cache[n][k] = value;
        cached[n][k] = true;
        
        return value;
    }  
    
    uint64_t cache[64][64] = {};
    bool cached[64][64] = {};
};


void check(uint64_t value, uint64_t answer, int i)
{
    if(value == answer)
        printf("test %d OK\n",i);
    else
        printf("test %d FAIL: value == %ld, answer == %ld\n",i,value,answer);
}


void test()
{
    Binomial c;
    check(c.Compute(6,3),20,0);
    check(c.Compute(0,0),1,1);
    check(c.Compute(0,2),0,2);
    check(c.Compute(5,1),5,3);
    check(c.Compute(5,5),1,4);
    check(c.Compute(3,2),3,5);
    check(c.Compute(3,2),3,5);
    check(c.Compute(63,63),1,6);
    check(c.Compute(63,32),1,7);
}

int main() {
    // Делаем тесты перед отправкой
    //test();
    //return 0;
    int n = 0;
    int k = 0;
    Binomial c;
    scanf("%d %d\n", &n, &k);
    printf("%ld\n", c.Compute(n,k));
    return 0;
}