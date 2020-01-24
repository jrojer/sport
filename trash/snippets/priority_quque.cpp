#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>

using namespace std;

class Heap
{
public:
    struct Item
    {
        size_t cmd_id;
        int val;
        bool operator>(const Item& a) const
        {
            if(val == a.val)
            {
                return cmd_id > a.cmd_id;
            }
            else
            {
                return val > a.val;
            }
        }
        bool operator==(const Item& a) const 
        {
            return val == a.val && cmd_id == a.cmd_id;
        }
        bool operator>=(const Item& a) const
        {
            return *this > a || *this == a;
        }
    };
    void Insert(size_t cmd_id, int val)
    {
        array_.push_back({cmd_id, val});
        SiftUp(Size());
    }
    void Change(size_t cmd_id, int val)
    {
        auto item = find_if(array_.begin(), array_.end(), [cmd_id](Item item) { return item.cmd_id == cmd_id; });
        assert(item != array_.end()); //, "item with item.cmd_id is guaranteed to exist"
        item->val = val;
        SiftUp(distance(array_.begin(),item));
        SiftDown(distance(array_.begin(),item));
    }
    bool Empty()
    {
        return array_.size() == 1;
    }
    Item ExtractMin()
    {
        assert(!Empty());

        auto &first = *(array_.begin()+1);
        auto &last = array_.back();
        swap(first, last);
        auto val = array_.back();
        array_.pop_back();
        SiftDown(1);
        return val;
    }

private:
    int SiftUp(int i)
    {
        while (i / 2 > 0 && array_[i / 2].val > array_[i].val)
        {
            swap(array_[i / 2], array_[i]);
            i /= 2;
        }
        return i;
    }
    size_t SiftDown(size_t i)
    {
        while (2 * i <= Size()) // at least one
        {
            auto &a = array_[i];
            auto &b = array_[2 * i];
            if (2 * i + 1 <= Size()) // both
            {
                auto &c = array_[2 * i + 1];

                if (a >= b && b > c)
                {
                    swap(a, c);
                    i = 2 * i + 1;
                }
                else if (a >= c && c > b)
                {
                    swap(a, b);
                    i = 2 * i;
                }
                else if (b > a && a > c)
                {
                    swap(a, c);
                    i = 2 * i + 1;
                }
                else if (c > a && a > b)
                {
                    swap(a, b);
                    i = 2 * i;
                }
                else
                {
                    break;
                }
            }
            else // only one
            {
                if (a > b)
                {
                    swap(b, a);
                    i = 2 * i;
                }
                else
                {
                    break;
                }
            }
        }
        return i;
    }
    size_t Size()
    {
        return array_.size() - 1;
    }
    vector<Item> array_{{}}; // size == 1
};

int main()
{
    freopen("input.txt", "r", stdin);
    Heap q;
    size_t cmd_id = 0;
    while (!cin.eof())
    {
        ++cmd_id;
        string cmd;
        cin >> cmd;
        if (cmd == "push")
        {
            int val;
            cin >> val;
            q.Insert(cmd_id, val);
        }
        else if (cmd == "extract-min")
        {
            if(q.Empty())
            {
                cout << "*" << endl;
            }
            else
            {
                auto item = q.ExtractMin();
                cout << item.val << " " << item.cmd_id << endl;
            }
        }
        else if (cmd == "decrease-key")
        {
            int x;
            int v;
            cin >> x;
            cin >> v;
            q.Change(x, v);
        }
    }
    return 0;
}