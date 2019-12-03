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
        Delete(Find(x,false));
    }
    void Delete(shared_ptr<Node> node)
    {
        if (!node)
        {
            return;
        }
        if (node->left && !node->right)
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
        else if (!node->left && node->right)
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
        else if (!node->left && !node->right)
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
            auto next_node = Next(node,false);
            std::swap(node->val, next_node->val);
            Delete(next_node);
        }
    }
    bool Exists(int x) { return static_cast<bool>(Find(x, false)); }
    int  Next(int x)
    {
        auto node      = Find(x, false);
        auto next_node = Next(node, false);
        return next_node == nullptr ? kNone : next_node->val;
    }
    int Prev(int x)
    {
        auto node      = Find(x, false);
        auto next_node = Next(node, true);
        return next_node == nullptr ? kNone : next_node->val;
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
    shared_ptr<Node> Find(int x, bool insert)
    {
        auto             node                  = root_;
        bool             found_insert_position = false;
        shared_ptr<Node> existing_node         = nullptr;
        if (!node)
        {
            if (insert)
            {
                root_ = make_shared<Node>(x);
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
                        node->right = make_shared<Node>(x);
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
                        node->left = make_shared<Node>(x);
                    }
                    found_insert_position = true;
                }
            }
            else
            {
                found_insert_position = true;
                existing_node         = node;
            }
        }
        return existing_node;
    }
    static const int kNone = INT_MAX;
    struct Node
    {
        Node(int x) : val(x) {}
        int              val;
        shared_ptr<Node> parent;
        shared_ptr<Node> left;
        shared_ptr<Node> right;
    };
    shared_ptr<Node> root_;
};

int main()
{
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
            int val = bst.Next(val);
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
            int val = bst.Prev(val);
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
