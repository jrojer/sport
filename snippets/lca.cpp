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
    explicit Lca(const vector<int> &parent, int n)
    {
        logn = flog(n);
        dp_ = vector<vector<int>>(n+1, vector<int>(logn + 1));
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
        d_.resize(n+1);
        for (int i = 1; i <= n; ++i)
        {
            int depth = 0;
            int j = i;
            while(parent[j] != j)
            {
                ++depth;
                j = parent[j];
            }
            d_[i] = depth;
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
        return dp_[v][0];
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
    freopen(R"(E:\projects\csc\sport\sources\input.txt)", "r", stdin);
    int n;
    cin >> n;
    std::vector<int> parent(n + 1);
    parent[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        int x;
        cin >> x;
        parent[i] = x;
    }
    Lca lca(parent, n);
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
