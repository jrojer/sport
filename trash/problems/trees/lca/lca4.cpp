#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

struct Lca4
{
    static const int MAXN = 200 * 1000 + 1;
    static const int MAXLIST = MAXN * 2;
    static const int LOG_MAXLIST = 19;
    static const int SQRT_MAXLIST = 633;
    static const int MAXBLOCKS = MAXLIST / ((LOG_MAXLIST + 1) / 2) + 1;

    int n;
    int root;
    vector<vector<int>> g;
    //int h[MAXN];                                              // vertex height
    vector<int> h; // vertex height
    vector<int> a; // dfs list
    //int a_pos[MAXN];                                          // positions in dfs list
    vector<int> a_pos;                                        // positions in dfs list
    int block;                                                // block size = 0.5 log A.size()
    int bt[MAXBLOCKS][LOG_MAXLIST + 1];                       // sparse table on blocks (relative minimum positions in blocks)
    int bhash[MAXBLOCKS];                                     // block hashes
    int brmq[SQRT_MAXLIST][LOG_MAXLIST / 2][LOG_MAXLIST / 2]; // rmq inside each block, indexed by block hash
    //int log2[2 * MAXN];                                       // precalced logarithms (floored values)
    vector<int> log2; // precalced logarithms (floored values)

    Lca4(const vector<vector<int>> &inc_list) : n(inc_list.size()), root(0), g(inc_list), h(MAXN, -1), a_pos(MAXN), log2(2*MAXN)
    {
        g.resize(MAXN);
        dfs(0, 0);
        build_lca();
    }
    // walk graph
    void dfs2(int v, int curh)
    {
        h[v] = curh;
        a_pos[v] = (int)a.size();
        a.push_back(v);
        for (size_t i = 0; i < g[v].size(); ++i)
            if (h[g[v][i]] == -1)
            {
                dfs(g[v][i], curh + 1);
                a.push_back(v);
            }
    }

    struct StackItem
    {
        int v;
        int h;
        int i;
        bool visited;
    };

    void dfs(int v, int curh)
    {
        vector<StackItem> stack;
        stack.push_back({v, curh, 0, false});
        while (!stack.empty())
        {
            auto item = stack.back();
            stack.pop_back();

            v = item.v;
            curh = item.h;

            if(!item.visited)
            {
                h[v] = curh;
                a_pos[v] = (int)a.size();
                a.push_back(v);
            }
            else
            {
                a.push_back(v);
            }

            int i = item.i;
            //for (size_t i = 0; i < g[v].size(); ++i)
            while (i < g[v].size() && h[g[v][i]] != -1)
            {
                ++i;
            }
            if(i < g[v].size())
            {
                //if (h[g[v][i]] == -1)
                {
                    //dfs(g[v][i], curh + 1);
                    stack.push_back({v,curh,i+1, true});
                    stack.push_back({g[v][i],curh+1,0, false});
                    //a.push_back(v);
                }
            }
        }
    }

    int log(int n)
    {
        int res = 1;
        while (1 << res < n)
            ++res;
        return res;
    }

    // compares two indices in a
    inline int min_h(int i, int j)
    {
        return h[a[i]] < h[a[j]] ? i : j;
    }

    // O(N) preprocessing
    void build_lca()
    {
        int sz = (int)a.size();
        block = (log(sz) + 1) / 2;
        int blocks = sz / block + (sz % block ? 1 : 0);

        // precalc in each block and build sparse table
        memset(bt, 255, sizeof bt);
        for (int i = 0, bl = 0, j = 0; i < sz; ++i, ++j)
        {
            if (j == block)
                j = 0, ++bl;
            if (bt[bl][0] == -1 || min_h(i, bt[bl][0]) == i)
                bt[bl][0] = i;
        }
        for (int j = 1; j <= log(sz); ++j)
            for (int i = 0; i < blocks; ++i)
            {
                int ni = i + (1 << (j - 1));
                if (ni >= blocks)
                    bt[i][j] = bt[i][j - 1];
                else
                    bt[i][j] = min_h(bt[i][j - 1], bt[ni][j - 1]);
            }

        // calc hashes of blocks
        memset(bhash, 0, sizeof bhash);
        for (int i = 0, bl = 0, j = 0; i < sz || j < block; ++i, ++j)
        {
            if (j == block)
                j = 0, ++bl;
            if (j > 0 && (i >= sz || min_h(i - 1, i) == i - 1))
                bhash[bl] += 1 << (j - 1);
        }

        // precalc RMQ inside each unique block
        memset(brmq, 255, sizeof brmq);
        for (int i = 0; i < blocks; ++i)
        {
            int id = bhash[i];
            if (brmq[id][0][0] != -1)
                continue;
            for (int l = 0; l < block; ++l)
            {
                brmq[id][l][l] = l;
                for (int r = l + 1; r < block; ++r)
                {
                    brmq[id][l][r] = brmq[id][l][r - 1];
                    if (i * block + r < sz)
                        brmq[id][l][r] =
                            min_h(i * block + brmq[id][l][r], i * block + r) - i * block;
                }
            }
        }

        // precalc logarithms
        for (int i = 0, j = 0; i < sz; ++i)
        {
            if (1 << (j + 1) <= i)
                ++j;
            log2[i] = j;
        }
    }

    // answers RMQ in block #bl [l;r] in O(1)
    inline int lca_in_block(int bl, int l, int r)
    {
        return brmq[bhash[bl]][l][r] + bl * block;
    }

    // answers LCA in O(1)
    int lca(int v1, int v2)
    {
        int l = a_pos[v1], r = a_pos[v2];
        if (l > r)
            swap(l, r);
        int bl = l / block, br = r / block;
        if (bl == br)
            return a[lca_in_block(bl, l % block, r % block)];
        int ans1 = lca_in_block(bl, l % block, block - 1);
        int ans2 = lca_in_block(br, 0, r % block);
        int ans = min_h(ans1, ans2);
        if (bl < br - 1)
        {
            int pw2 = log2[br - bl - 1];
            int ans3 = bt[bl + 1][pw2];
            int ans4 = bt[br - (1 << pw2)][pw2];
            ans = min_h(ans, min_h(ans3, ans4));
        }
        return a[ans];
    }
};



int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("lca_input.txt", "r", stdin);
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
    Lca4 lca(incidence_list);
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