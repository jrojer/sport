#include <vector>
#include <iostream>

using namespace std;

struct Lca
{
    Lca(const vector<vector<int>> &g) : g(g)
    {
        n = g.size();
        tin.resize(n);
        tout.resize(n);
        up.resize(n);
        l = 1;
        while ((1 << l) <= n)
        {
            ++l;
        }
        for (int i = 0; i < n; ++i)
        {
            up[i].resize(l + 1);
        }
        dfs(0);
    }

    struct StackItem
    {
        int to;
        int v;
        int i;
        bool visited;
    };

    void dfs(int v, int p = 0)
    {
        vector<StackItem> stack;
        stack.push_back({v, p, 0, false});
        while (!stack.empty())
        {
            auto item = stack.back();
            stack.pop_back();

            v = item.to;
            p = item.v;
            if (!item.visited)
            {
                tin[v] = ++timer;

                up[v][0] = p;
                for (int i = 1; i <= l; ++i)
                {
                    up[v][i] = up[up[v][i - 1]][i - 1];
                }
            }
            int i = item.i;
            if (i < g[v].size())
            {
                int to = g[v][i];
                if (to != p)
                {
                    stack.push_back({v, p, i + 1, true});
                    stack.push_back({to, v, 0, false});
                }
            }
            else
            {
                tout[v] = ++timer;
            }
        }
    }

    bool upper(int a, int b)
    {
        return tin[a] <= tin[b] && tout[a] >= tout[b];
    }

    int lca(int a, int b)
    {
        if (upper(a, b))
        {
            return a;
        }
        if (upper(b, a))
        {
            return b;
        }
        for (int i = l; i >= 0; --i)
        {
            if (!upper(up[a][i], b))
            {
                a = up[a][i];
            }
        }
        return up[a][0];
    }

    int n;
    int l;
    vector<vector<int>> g;
    vector<int> tin;
    vector<int> tout;
    int timer = 0;
    vector<vector<int>> up;
};

/* 
 line x
    2 1 
    3 1
    4 2
    5 3

    tree:
        1
      2   3
      4   5
    ___________
 line x
    2 1
    3 1
    4 2
    5 2
    2

    tree:
        1
      2   3
    4   5
*/

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("input.txt", "r", stdin);
    freopen("lca2_large_input.txt", "r", stdin);
    int n;
    cin >> n;
    vector<vector<int>> incidence_list(n);
    for (int i = 2; i <= n; ++i)
    {
        int x;
        cin >> x;
        incidence_list[x - 1].push_back(i - 1);
    }
    Lca lca(incidence_list);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        cout << lca.lca(u - 1, v - 1) + 1 << '\n';
    }
    return 0;
}