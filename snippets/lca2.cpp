#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <climits>

using namespace std;

struct DepthInfo
{
    vector<int> depth;
    size_t max_depth;
};

DepthInfo CalculateDepth(const vector<int> &parent, size_t n)
{
    vector<int> res(n + 1);
    size_t max_depth = 0;
    for (int i = 1; i <= n; ++i)
    {
        int depth = 0;
        int j = i;
        while (parent[j] != j)
        {
            ++depth;
            j = parent[j];
        }
        res[i] = depth;
        if (depth > max_depth)
        {
            max_depth = depth;
        }
    }
    return {res, max_depth};
}

vector<vector<int>> CalculateDp(const vector<int> &parent, size_t n, size_t height)
{
    vector<vector<int>> dp;
    /*
      i/v 1 2 3 4 5 
      0
      1 
      2
    */
    for (size_t i = 0; (1 << i) <= height; ++i)
    {
        dp.emplace_back(1);
        for (size_t v = 1; v <= n; ++v)
        {
            if (i == 0)
            {
                dp.back().push_back(parent[v]);
            }
            else
            {
                dp.back().push_back(dp[i - 1][dp[i - 1][v]]);
            }
        }
    }
    return dp;
}

struct Lca
{
    explicit Lca(const vector<int> &parent, size_t n) : di_(CalculateDepth(parent, n)),
                                                        dp_(CalculateDp(parent, n, di_.max_depth))
    {
    }
    /*
    2 1 
    3 1
    4 2
    5 3
        1
      2   3
      4   5
    ___________
    2 1
    3 1
    4 2
    5 2
        1
      2   3
    4   5
    */
    int Get(int u, int v)
    {
        if (di_.depth[u] < di_.depth[v])
        {
            swap(u, v);
        }
        int d = di_.depth[u] - di_.depth[v];
        for (int p2 = dp_.size()-1; p2 >= 0; --p2)
        {
            if (d >= (1 << p2))
            {
                d -= (1 << p2);
                u = dp_[p2][u];
            }
        }
        assert (di_.depth[u] == di_.depth[v]);
        if (v == u)
        {
            return v;
        }
        else
        {
            int x = u;
            int y = v;
            int k = 0;
            while(dp_[k][x] != dp_[k][y])
            {
                while (dp_[k][x] != dp_[k][y])
                {
                    ++k;
                }
                --k;
                x = dp_[k][x];
                y = dp_[k][y];
                k = 0;
            }
            return dp_[0][x];
        }
    }
    DepthInfo di_;
    vector<vector<int>> dp_;
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
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
        cout << lca.Get(u, v) << '\n';
    }
    return 0;
}