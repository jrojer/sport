#include <iostream>
#include <vector>
#include <algorithm>

using row_t = std::vector<float>;
using matr_t = std::vector<row_t>;


matr_t ToUpperTriangle(const matr_t& matrix)
{
    const float eps = 0.0001;
    auto M = matrix;
    const size_t nrows = M.size();
    const size_t ncols = M.begin()->size();

    for(size_t i = 0; i < nrows && i < ncols; ++i)
    {
        for(size_t k = i; k < nrows; ++k)
        {
            if(M[k][i] < eps)
            {
                std::swap(M[k],M[i]);
                break;
            }
        }
        if(M[i][i] < eps)
        {
            break;
        }
        for(size_t k = i+1; k < nrows; ++k)
        {
            for(size_t j = i; j < ncols; ++j)
            {
                M[k][j] -= M[i][j] * M[k][i] / M[i][i];
            }
        }
    }
    return M;
}

matr_t ReadInput()
{
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    matr_t matrix(n,row_t(m));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            int val = 0;
            std::cin >> val;
            matrix[i][j] = val;
        }
    }
    return matrix;
}

void PrintRow(const row_t& row)
{
    size_t i = 0;
    for(; i < row.size(); ++i)
        std::cout << row[i] << " ";
    std::cout << row.back() << std::endl;
}

void PrintOutput(const matr_t& m)
{
    for(const auto& r:m)
        PrintRow(r);
}

int main()
{
    PrintOutput(ToUpperTriangle(ReadInput()));
    return 0;
}


