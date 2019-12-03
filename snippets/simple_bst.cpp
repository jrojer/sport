#include <climits>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct Bst
{
    struct Node;
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
    FindResult Find(int x, bool insert)
    {
        auto node = root_;
        bool found_insert_position = false;
        shared_ptr<Node> existing_node = nullptr;
        bool inserted = false;
        if (!node)
        {
            if (insert)
            {
                root_ = make_shared<Node>(x);
                existing_node = root_;
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
                        auto new_node = make_shared<Node>(x);
                        new_node->parent = node;
                        node->right = new_node;
                        existing_node = node->right;
                        inserted = true;
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
                        auto new_node = make_shared<Node>(x);
                        new_node->parent = node;
                        node->left = new_node;
                        existing_node = node->left;
                        inserted = true;
                    }
                    found_insert_position = true;
                }
            }
            else
            {
                found_insert_position = true;
                existing_node = node;
            }
        }
        return FindResult{inserted, existing_node};
    }
    static const int kNone = INT_MAX;
    struct Node
    {
        Node(int x) : val(x) {}
        int val;
        shared_ptr<Node> parent;
        shared_ptr<Node> left;
        shared_ptr<Node> right;
    };
    shared_ptr<Node> root_;
};

int main()
{
    //freopen("input.txt", "r", stdin);
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
