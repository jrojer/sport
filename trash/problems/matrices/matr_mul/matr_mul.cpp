#include <iostream>
#include <vector>
typedef std::vector<int> row_t;
typedef std::vector<row_t> matr_t;

void read_input(matr_t& a,int n,int m)
{
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            std::cin >> a[i][j];
}

void print_row(const row_t& row,int n)
{
   int j=0;
   for(;j+1<n;++j)
      std::cout << row[j] << " ";
    std::cout << row[j] << std::endl;
}

void write_output(const matr_t& a,int n,int m)
{
   for(int i=0;i<n;++i)
        print_row(a[i],m);
}

matr_t product(const matr_t& a, const matr_t& b, int n, int m, int k)
{
    matr_t c(n,row_t(k));
    for(int i =0 ;i< n;++i)
        for(int j =0 ;j< k;++j)
            for(int t =0 ;t< m;++t)
                c[i][j] += a[i][t]*b[t][j];
    return c;
}

int main() {
    int n,m,k;
    std::cin >> n >> m >> k;
    matr_t a(n,row_t(m));
    matr_t b(m,row_t(k));
    read_input(a,n,m);
    read_input(b,m,k);
    write_output(product(a,b,n,m,k),n,k);
    return 0;
}