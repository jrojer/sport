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
    int max_depth;
};

DepthInfo CalculateDepth(const vector<vector<int>> &incidence_list, size_t n)
{
    int max_depth = 0;
    vector<int> depth(n + 1);
    int root = 1;
    vector<int> stack;
    stack.push_back(root);
    depth[root] = 0;
    while(!stack.empty())
    {
        int node = stack.back();
        stack.pop_back();
        if(depth[node] > max_depth)
        {
            max_depth = depth[node];
        }
        for(int child: incidence_list[node])
        {
            depth[child] = depth[node] + 1;
            stack.push_back(child);
        }
    }
    return {depth, max_depth};
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
    explicit Lca(const vector<int> &parent, const DepthInfo &di, size_t n) : di_(di),
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
        for (int p2 = dp_.size() - 1; p2 >= 0; --p2)
        {
            if (d >= (1 << p2))
            {
                d -= (1 << p2);
                u = dp_[p2][u];
            }
        }
        assert(di_.depth[u] == di_.depth[v]);
        if (v == u)
        {
            return v;
        }
        else
        {
            int x = u;
            int y = v;
            int k0 = 0;
            while (dp_[k0][x] != dp_[k0][y])
            {
                ++k0;
            }
            for (int k = k0; k >= 0; --k)
            {
                if (dp_[k][x] != dp_[k][y])
                {
                    x = dp_[k][x];
                    y = dp_[k][y];
                }
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
    vector<vector<int>> incidence_list(n + 1);
    std::vector<int> parent(n + 1);
    parent[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        int x;
        cin >> x;
        parent[i] = x;
        incidence_list[x].push_back(i);
    }
    Lca lca(parent, CalculateDepth(incidence_list, n), n);
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