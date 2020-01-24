#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

struct Lca3
{
    Lca3(const vector<vector<int>> &g) : g(g)
    {
        n = g.size();
        tin.resize(n);
        tout.resize(n);
        up.resize(n);
        depth.resize(n);
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
        int depth;
    };

    void dfs(int v, int p = 0)
    {
        vector<StackItem> stack;
        stack.push_back({v, p, 0, false, 0});
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

                depth[v] = item.depth;
            }
            int i = item.i;
            if (i < g[v].size())
            {
                int to = g[v][i];
                if (to == p)
                {
                    ++i;
                }
                if (i < g[v].size())
                {
                    to = g[v][i];
                    stack.push_back({v, p, i + 1, true, item.depth});
                    stack.push_back({to, v, 0, false, item.depth + 1});
                }
                else
                {
                    tout[v] = ++timer;
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
    vector<int> depth;
};

struct DisjointSetUnion
{
    DisjointSetUnion(size_t n, const vector<int> &depth) : parent(n), rank(n), least_deep_node(n), depth(depth)
    {
        for (size_t i = 0; i < n; ++i)
        {
            parent[i] = i;
            least_deep_node[i] = i;
        }
    }

    int Get(int v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = Get(parent[v]);
    }

    int GetLeastDeepNode(int v)
    {
        return least_deep_node[Get(v)];
    }

    bool Union(int a, int b)
    {
        a = Get(a);
        b = Get(b);
        int union_ldn = depth[least_deep_node[a]] < depth[least_deep_node[b]] ? least_deep_node[a] : least_deep_node[b];
        if (a != b)
        {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            least_deep_node[a] = union_ldn;
            if (rank[a] == rank[b])
                ++rank[a];
            return true;
        }
        return false;
    }
    vector<int> parent;
    vector<int> rank;
    vector<int> least_deep_node;
    vector<int> depth;
};

int main()
{
    // read n
    // read incidence list
    // init dsu with n
    // init lca
    // node 1 is the root
    // get parent array from lca
    // for each request
    //   find lca
    //   join node with lca up to lca node
    //   join second branch as well
    //   count used edges

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("unused_edges_in_tree_input.txt", "r", stdin);
    int n;
    cin >> n;
    vector<vector<int>> incidence_list(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        incidence_list[u].push_back(v);
        incidence_list[v].push_back(u);
    }
    Lca3 lca3(incidence_list);
    DisjointSetUnion dsu(n, lca3.depth);
    int m;
    cin >> m;
    int num_used_edges = 0;
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        x = dsu.GetLeastDeepNode(x);
        y = dsu.GetLeastDeepNode(y);
        int l = lca3.lca(x, y);
        while(dsu.Get(x) != dsu.Get(l))
        {
            int u = lca3.up[x][0];
            if (dsu.Union(x, u))
            {
                ++num_used_edges;
            }
            x = dsu.GetLeastDeepNode(u);
        }
        while(dsu.Get(y) != dsu.Get(l))
        {
            int u = lca3.up[y][0];
            if (dsu.Union(y, u))
            {
                ++num_used_edges;
            }
            y = dsu.GetLeastDeepNode(u);
        }
    }
    cout << n - 1 - num_used_edges << "\n";
    return 0;
}