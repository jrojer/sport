#include <iostream>

int max(int a, int b)
{
    return a > b ? a : b;
}

int StringLen(const char* a)
{
    int len =0 ;
    while(a[len++]>0);
    return len-1;
}

void Swap(char& a,char& b)
{
    char t = a;
    a = b;
    b = t;
}

void Revert(char* s)
{
    int len_s = StringLen(s);
    for(int i=0;i<len_s/2;++i)
    {
        Swap(s[i],s[len_s-1-i]);
    }
}

void Zero(char* s)
{
    int len_s = StringLen(s);
    for(int i= 0;i<len_s;++i)
    {
        s[i] = 0;
    }
}

char* Add(const char* a, const char* b, char* c)
{
    Zero(c);
    int a_len = StringLen(a);
    int b_len = StringLen(b);
    
    for(int i = 0; i < max(a_len,b_len); ++i)
    {
        int da = i < a_len ? (a[a_len-1-i] - '0') : 0;
        int db = i < b_len ? (b[b_len-1-i] - '0') : 0;
        
        int t = da+db+c[i];
        c[i]    = t%10;
        c[i+1] += t/10;
    }
    int len_c= StringLen(c);
    for(int i=0;i<len_c;++i)
    {
        c[i] += '0';
    }
    printf("%s\n",c);
    Revert(c);
    return c;
}



void test()
{
    puts("a");
    char s1[] = {'a','b','c','d','e',0};
    char s2[] = {'a','b','c','d',0};
    printf("%s\n",s1);
    // Len test
    printf("%d == 5\n",StringLen(s1));
    printf("%d == 4\n",StringLen(s2));
    // Revert test
    Revert(s1);
    Revert(s2);
    printf("%s\n",s1);
    printf("%s\n",s2);
    //Swap test
    char a = 'a';
    char b = 'b';
    Swap(a,b);
    printf("%c %c\n",a,b);
    //Add test
    char ans[100] = {};
    printf("%s\n",Add("1","1",ans));    
    printf("%s\n",Add("12","1",ans));
    printf("%s\n",Add("123","123",ans));
    
}

int main() 
{  
    test();
    return 0;
    
    const int max_input_len = 10001;
    
    char a[max_input_len] = {};
    char b[max_input_len] = {};
    char c[max_input_len] = {};
    
    scanf("%s",a);
    scanf("%s",b);
    
    Add(a,b,c);
    
    printf("%s\n",c);
    
    return 0;
}