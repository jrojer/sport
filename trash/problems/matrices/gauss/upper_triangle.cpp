#include <iostream>
#include <vector>
#include <algorithm>

using row_t = std::vector<double>;
using matr_t = std::vector<row_t>;

static const double eps = 0.00001;

matr_t ToUpperTriangle(const matr_t& matrix)
{
    auto M = matrix;
    const size_t nrows = M.size();
    const size_t ncols = M.begin()->size();

    for(size_t i = 0; i < nrows && i < ncols; ++i)
    {
        for(size_t k = i; k < nrows; ++k)
        {
            if(std::abs(M[k][i]) > eps)
            {
                std::swap(M[k],M[i]);
                break;
            }
        }
        if(std::abs(M[i][i]) < eps)
        {
            break;
        }
        for(size_t k = i+1; k < nrows; ++k)
        {
            auto a = M[k][i];
            auto b = M[i][i];
            for(size_t j = i; j < ncols; ++j)
            {
                M[k][j] -= M[i][j] * a / b ;
            }
        }
    }
    return M;
}

matr_t ReadInput()
{
    int n = 0;
    int m = 0;
    scanf("%d %d",&n,&m);
    matr_t matrix(n,row_t(m));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            double val = 0;
            scanf("%lf", &val);
            matrix[i][j] = val;
        }
    }
    return matrix;
}

double round3(double x)
{
    return abs(x) < eps ? 0.0 : round(x * 10) / 10;
}

void PrintRow(const row_t& row)
{
    size_t i = 0;
    for(; i + 1 < row.size(); ++i)
        printf("%.1f ", round3(row[i]));
    printf("%.1f\n", round3(row.back()));
}

void PrintOutput(const matr_t& m)
{
    for(const auto& r:m)
        PrintRow(r);
}

void test()
{
    printf("%.3f ", round3(-0.000005));
    printf("%.3f ", round3(-1.0005));
    printf("%.3f ", round3(0.0005));
    printf("%.3f ", round3(0.0002));
    printf("%.3f ", round3(-1.0002));
    printf("%.3f ", round3(1.0019));
    puts("");
}

int main()
{
    PrintOutput(ToUpperTriangle(ReadInput()));
    return 0;
}
