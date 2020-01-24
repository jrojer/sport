#include <climits>
#include <iostream>
#include <memory>
#include <string>
#include <cassert>
#include <deque>
#include <algorithm>

using namespace std;

struct Bst
{
    struct Node;
    using node_t = shared_ptr<Node>;

    void Insert(int x) { Find(x, true); }
    void Delete(int x)
    {
        Delete(Find(x, false).node);
    }
    void Delete(shared_ptr<Node> node)
    {
        if (!node)
        {
            return;
        }
        if (node->left && !node->right)
        {
            if (node->parent)
            {
                node->left->parent = node->parent;
                if (node->parent->left == node)
                {
                    node->parent->left = node->left;
                }
                else
                {
                    node->parent->right = node->left;
                }
                Rebalance(node->parent, kDelete);
            }
            else
            {
                root_ = node->left;
                node->left->parent = nullptr;
            }
        }
        else if (!node->left && node->right)
        {
            if (node->parent)
            {
                node->right->parent = node->parent;
                if (node->parent->left == node)
                {
                    node->parent->left = node->right;
                }
                else
                {
                    node->parent->right = node->right;
                }
                Rebalance(node->parent, kDelete);
            }
            else
            {
                root_ = node->right;
                node->right->parent = nullptr;
            }
        }
        else if (!node->left && !node->right)
        {
            if (node->parent)
            {
                if (node->parent->left == node)
                {
                    node->parent->left = nullptr;
                }
                else
                {
                    node->parent->right = nullptr;
                }
                Rebalance(node->parent, kDelete);
            }
            else
            {
                root_ = nullptr;
            }
        }
        else
        {
            auto next_node = Next(node, false);
            std::swap(node->val, next_node->val);
            Delete(next_node);
        }
    }
    bool Exists(int x) { return static_cast<bool>(Find(x, false).node); }
    int Next(int x, bool reversed = false)
    {
        auto res = Find(x, true);
        auto node = res.node;
        auto next_node = Next(node, reversed);
        int next_val = next_node == nullptr ? kNone : next_node->val;
        if (res.inserted)
        {
            Delete(node);
        }
        return next_val;
    }
    int Prev(int x)
    {
        return Next(x, true);
    }
    shared_ptr<Node> Next(shared_ptr<Node> node, bool reversed)
    {
        if (!node)
        {
            return nullptr;
        }
        if (reversed)
        {
            if (node->left)
            {
                node = node->left;
                while (node->right)
                {
                    node = node->right;
                }
                return node;
            }
        }
        else
        {
            if (node->right)
            {
                node = node->right;
                while (node->left)
                {
                    node = node->left;
                }
                return node;
            }
        }
        if (reversed && !node->left || !reversed && !node->right)
        {
            while (node->parent)
            {
                auto node2 = reversed ? node->parent->left : node->parent->right;
                if (node2 == node)
                {
                    node = node->parent;
                }
                else
                {
                    return node->parent;
                }
            }
            return nullptr;
        }
    }
    struct FindResult
    {
        bool inserted;
        node_t node;
    };
    void RotateLeft(node_t a)
    {
        node_t b = a->right;
        a->right = b->left;
        if(b->left)
        {
            b->left->parent = a;
        }
        b->left = a;
        b->parent = a->parent;
        if(a->parent)
        {
            if (a->parent->left == a)
            {
                a->parent->left = b;
            }
            else
            {
                a->parent->right = b;
            }
        }
        a->parent = b;
        if(root_ == a) // a was root
        {
            root_ = b;
        }
        UpdateHeight(a);
        UpdateHeight(b);
    }
    void RotateRight(node_t b)
    {
        node_t a = b->left;
        b->left = a->right;
        if(a->right)
        {
            a->right->parent = b;
        }
        a->right = b;
        a->parent = b->parent;
        if(b->parent)
        {
            if (b->parent->left == b)
            {
                b->parent->left = a;
            }
            else
            {
                b->parent->right = a;
            }
        }
        b->parent = a;
        if(root_ == b) // b was root
        {
            root_ = a;
        }
        UpdateHeight(b);
        UpdateHeight(a);
    }
    void BigRotateLeft(node_t a)
    {
        RotateRight(a->right);
        RotateLeft(a);
    }
    void BigRotateRight(node_t a)
    {
        RotateLeft(a->left);
        RotateRight(a);
    }
    enum RebalanceMode {kDelete, kInsert};
    void Rebalance(node_t node, RebalanceMode mode)
    {
        UpdateHeight(node);
        const int diff_node = diff(node);
        if(!node || (diff_node == 0 && mode == kInsert || abs(diff_node) == 1 && mode == kDelete))
        {
            return;
        }
        if (diff_node == -2)
        {
            if (diff(node->right) < 1)
            {
                RotateLeft(node); 
            }
            else
            {
                BigRotateLeft(node); 
            }
        }
        else if (diff_node == 2)
        {
            if (diff(node->left) > -1)
            {
                RotateRight(node);
            }
            else
            {
                BigRotateRight(node);
            }
        }
        Rebalance(node->parent, mode);
    }
    FindResult Find(int x, bool insert)
    {
        auto node = root_;
        bool found_insert_position = false;
        shared_ptr<Node> requested_node = nullptr;
        bool inserted = false;
        if (!node)
        {
            if (insert)
            {
                root_ = make_shared<Node>(x);
                requested_node = root_;
                inserted = true;
            }
            found_insert_position = true;
        }
        while (!found_insert_position)
        {
            if (x > node->val)
            {
                if (node->right)
                {
                    node = node->right;
                }
                else
                {
                    if (insert)
                    {
                        requested_node = make_shared<Node>(x);
                        requested_node->parent = node;
                        node->right = requested_node;
                        inserted = true;
                        Rebalance(node, kInsert);
                    }
                    found_insert_position = true;
                }
            }
            else if (x < node->val)
            {
                if (node->left)
                {
                    node = node->left;
                }
                else
                {
                    if (insert)
                    {
                        requested_node = make_shared<Node>(x);
                        requested_node->parent = node;
                        node->left = requested_node;
                        inserted = true;
                        Rebalance(node, kInsert);
                    }
                    found_insert_position = true;
                }
            }
            else
            {
                found_insert_position = true;
                requested_node = node;
            }
        }
        return FindResult{inserted, requested_node};
    }
    void Print()
    {
        deque<node_t> fifo;
        fifo.push_back(root_);
        while(!fifo.empty())
        {
            size_t level_len = fifo.size();
            for(size_t i = 0; i < level_len; ++i)
            {
                node_t node = fifo.front();
                fifo.pop_front();
                if(node != nullptr)
                {
                    printf(" %3d ", node->val);
                    fifo.push_back(node->left);
                    fifo.push_back(node->right);
                }
                else
                {
                    printf(" --- ");
                }
            }
            printf("\n");
        }
        puts("_______________________");
    }
    static const int kNone = INT_MAX;
    struct Node
    {
        Node(int x) : val(x) {}
        int val;
        node_t parent;
        node_t left;
        node_t right;
        int color;
    };
    node_t root_;
};

int main()
{
    freopen("input.txt", "r", stdin);
    Bst bst;
    while (!cin.eof())
    {
        bst.Print();
        string cmd;
        cin >> cmd;
        int val;
        cin >> val;
        if (cmd == "insert")
        {
            bst.Insert(val);
        }
        else if (cmd == "exists")
        {
            cout << (bst.Exists(val) ? "true" : "false") << endl;
        }
        else if (cmd == "next")
        {
            val = bst.Next(val);
            if (val == Bst::kNone)
            {
                cout << "none";
            }
            else
            {
                cout << val;
            }
            cout << endl;
        }
        else if (cmd == "prev")
        {
            val = bst.Prev(val);
            if (val == Bst::kNone)
            {
                cout << "none";
            }
            else
            {
                cout << val;
            }
            cout << endl;
        }
        else if (cmd == "delete")
        {
            bst.Delete(val);
        }
    }
    return 0;
}
