#include <iostream>
#include <vector>
#include <string>
#include <cstddef>

using namespace std;

struct DisjointSetUnion
{
    void AddSet()
    {
        parent_[size_] = size_;
        height_[size_] = 0;
        ++size_;
    }
    int Get(int x)
    {
        while(parent_[x] != x)
        {
            x = parent_[x];
        }
        return x;
    }
    bool Union(int x, int y)
    {
        x = Get(x);
        y = Get(y);
        if(x == y)
        {
            return false;
        }
        if(height_[x] == height_[y])
        {
            parent_[x] = y;
            ++height_[y];
        }
        else if(height_[x] < height_[y])
        {
            parent_[x] = y;
        }
        else 
        {
            parent_[y] = x;
        }
        return true;
    }
    void Clear()
    {
        size_ = 0;
    }
    static const size_t kMaxSize = 100000;
    int parent_[kMaxSize];
    int height_[kMaxSize];
    size_t size_ = 0;
};

int main()
{
    freopen("input.txt", "r", stdin);
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
                dsu.AddSet();
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
        else if(cmd == "JOIN")
        {
            int a;
            int b;
            cin >> a;
            cin >> b;
            if(!dsu.Union(a,b)) 
            {
                cout << "ALREADY " << a << " " << b << endl;
            }
        }
    }

    return 0;
}