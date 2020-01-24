#include <iostream>
#include <vector>
#include <string>
#include <cstddef>

using namespace std;

struct DisjointSetUnion
{
    void AddSet(int v)
    {
        parent[v] = v;
        rank[v] = 0;
    }

    int Get(int v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = Get(parent[v]);
    }

    bool Union(int a, int b)
    {
        a = Get(a);
        b = Get(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                ++rank[a];
            return true;
        }
        return false;
    }
    void Clear()
    {
        size_ = 0;
    }
    static const size_t kMaxSize = 100000;
    int parent[kMaxSize];
    int rank[kMaxSize];
    size_t size_ = 0;
};

int main()
{
    freopen("dsu_input.txt", "r", stdin);
    DisjointSetUnion dsu;
    while (!cin.eof())
    {
        string cmd;
        cin >> cmd;
        if (cmd == "RESET")
        {
            dsu.Clear();
            int size;
            cin >> size;
            for (int i = 0; i < size; ++i)
            {
                dsu.AddSet(i);
            }
            cout << "RESET DONE" << endl;
        }
        else if (cmd == "CHECK")
        {
            int a;
            int b;
            cin >> a;
            cin >> b;
            cout << (dsu.Get(a) == dsu.Get(b) ? "YES" : "NO") << endl;
        }
        else if (cmd == "JOIN")
        {
            int a;
            int b;
            cin >> a;
            cin >> b;
            if (!dsu.Union(a, b))
            {
                cout << "ALREADY " << a << " " << b << endl;
            }
        }
    }

    return 0;
}