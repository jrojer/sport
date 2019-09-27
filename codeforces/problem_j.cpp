#include<iostream>
#include<cmath>


double f(double x)
{
    return x*x + sqrt(x);
}

double FindIntersection(double c)
{
    double a = 0.0;
    double b = 100000.0; // 10**5
    double eps = 0.0000000001;
    double m = (a+b)/2;
    while(!(fabs(f(m)-c) <  eps))
    {
        if(f(m) < c)
        {
            a = m;
        }
        else
        {
            b = m;
        }
        m = (a+b)/2;
    }
    return m;
}

int main()
{
    double c;
    scanf("%lf",&c);
    printf("%f\n",FindIntersection(c));
    return 0;
}
