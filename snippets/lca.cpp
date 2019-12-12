#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <climits>

using namespace std;

struct Lca
{
    explicit Lca(const vector<int> &parent)
    {
        size_t n = parent.size() - 1;
        logn = flog(n) + 1;
        dp_ = vector<vector<int>>(n, vector<int>(logn));
        for (int i = 1; i <= n; ++i)
        {
            dp_[i][0] = parent[i];
        }
        for (int j = 1; j <= logn; ++j)
        {
            for (int i = 1; i <= n; ++i)
            {
                dp_[i][j] = dp_[dp_[i][j - 1]][j - 1];
            }
        }
    }
    int Get(int u, int v)
    {
        if (d_[v] > d_[u])
        {
            swap(v, u);
        }
        for (int i = logn; i >= 0; --i)
        {
            if (d_[u] - d_[v])
            {
                u = dp_[u][i];
            }
        }
        if (v == u)
        {
            return v;
        }
        for (int i = logn; i >= 0; --i)
        {
            if (dp_[v][i] != dp_[u][i])
            {
                v = dp_[v][i];
                u = dp_[u][i];
            }
        }
        return parent[v];
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
    vector<int> d_;
    vector<vector<int>> dp_;
    vector<size_t> log_;
    size_t logn;
};

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    std::vector<int> parent(n + 1);
    for (int i = 1; i + 1 <= n; ++i)
    {
        int x;
        cin >> x;
        parent[i] = x;
    }
    Lca lca(parent);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        cout << lca.Get(u, v) << endl;
    }
    return 0;
}