#include <iostream>
#include <climits>
#include <memory>

using namespace std;

struct Bst
{
    struct Node;
    void Insert(int x)
    {
        Find(x, true);
    }
    void Delete(int x)
    {
        auto node = Find(x, false);
        if (!node)
        {
            return;
        }
        //if ...
    }
    bool Exists(int x)
    {
        return static_cast<bool>(Find(x, false));
    }
    int Next(int x)
    {
    }
    int Prev(int x)
    {
    }
    shared_ptr<Node> Find(int x, bool insert)
    {
        auto node = root_;
        bool found_insert_position = false;
        shared_ptr<Node> existing_node = nullptr;
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
                existing_node = node;
            }
        }
        return existing_node;
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
    }

    return 0;
}