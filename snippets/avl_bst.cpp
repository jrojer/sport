#include <climits>
#include <iostream>
#include <memory>
#include <string>

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
                    ++node->parent->diff;
                }
                else
                {
                    node->parent->right = node->left;
                    --node->parent->diff;
                }
                Rebalance(node->parent);
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
                    ++node->parent->diff;
                }
                else
                {
                    node->parent->right = node->right;
                    --node->parent->diff;
                }
                Rebalance(node->parent);
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
                    ++node->parent->diff;
                }
                else
                {
                    node->parent->right = nullptr;
                    --node->parent->diff;
                }
                Rebalance(node->parent);
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
        if (res.inserted)
        {
            Delete(node);
        }
        return next_node == nullptr ? kNone : next_node->val;
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
        shared_ptr<Node> node;
    };
    void Rebalance(node_t node /*, may be need diff change count to pass it upwards*/)
    {
        if(node->diff == -2)
        {
            if(node->right)
            {
                if(node->right->diff < 1)
                {
                    // small left rotatiton
                }
                else
                {
                    // big left rotation
                }
            }
            else
            {
                // ???
            }
        }
        else if(node->diff == 2)
        {
            if(node->left)
            {
                if(node->left->diff > -1)
                {
                    // small right rotatiton
                }
                else
                {
                    // big right rotation
                }
            }
            else
            {
                // ???
            }
        }
        // probably we know beforehand how the rotation changes the height 
        // update diff upwards
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
                        --node->diff; 
                        Rebalance(node);
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
                        ++node->diff; 
                        Rebalance(node);
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
    static const int kNone = INT_MAX;
    struct Node
    {
        Node(int x) : val(x) {}
        int val;
        shared_ptr<Node> parent;
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        int diff = 0;
    };
    shared_ptr<Node> root_;
};

int main()
{
    freopen("input.txt", "r", stdin);
    Bst bst;
    while (!cin.eof())
    {
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
