#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <climits>

using namespace std;

int RangeMin(const vector<int> &values, int i, int j)
{
    if (i > j)
    {
        swap(i, j);
    }
    int min = values[i];
    for (int k = i; k <= j; ++k)
    {
        if (values[k] < min)
        {
            min = values[k];
        }
    }
    return min;
}

struct Rmq
{
    explicit Rmq(const vector<int> &values_)
    {
        size_t n = values_.size() - 1;
        log_.resize(n + 1);
        for (size_t i = 1; i <= n; ++i)
        {
            log_[i] = flog(i);
        }
        sparse_table_ = vector<vector<int>>(n + 1, vector<int>((log_[n] + 1), INT_MAX));
        for (size_t j = 0; j <= log_[n]; ++j)
        {
            for (size_t i = 1; i <= n; ++i)
            {
                if (j == 0)
                {
                    sparse_table_[i][j] = values_[i];
                }
                else if (i + (1 << (j - 1)) <= n)
                {
                    sparse_table_[i][j] = min(sparse_table_[i][j - 1], sparse_table_[i + (1 << (j - 1))][j - 1]);
                }
            }
        }
    }
    int GetMin(int l, int r)
    {
        if (l > r)
        {
            swap(l, r);
        }
        size_t j = log_[r - l + 1];
        return min(sparse_table_[l][j], sparse_table_[r - (1 << j) + 1][j]);
    }
    size_t flog(size_t len)
    {
        if (len == 1)
        {
            return 0;
        }
        else
        {
            return flog(len / 2) + 1;
        }
    }
    vector<vector<int>> sparse_table_;
    vector<size_t> log_;
};

void Test()
{
    int n = 1000;
    vector<int> values(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        values[i] = rand();
    }
    Rmq rmq(values);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int correct_min = RangeMin(values, i, j);
            int rmq_min = rmq.GetMin(i, j);
            assert(rmq_min == correct_min);
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin );
    //Test();
    int n, m, a1;
    cin >> n >> m >> a1;
    int u, v;
    cin >> u >> v;
    vector<int> a(n + 1);
    a[1] = a1;
    for (int i = 1; i + 1 <= n; ++i)
    {
        a[i + 1] = (23 * a[i] + 21563) % 16714589;
    }
    Rmq rmq(a);
    for (int i = 1; i < m; ++i)
    {
        int r = rmq.GetMin(u, v);
        u = ((17 * u + 751 + r + 2 * i) % n) + 1;
        v = ((13 * v + 593 + r + 5 * i) % n) + 1;
    }
    cout << u << " " << v << " " << rmq.GetMin(u, v) << endl;
    return 0;
}