#include <iostream>
#include <cstdlib>
#include <cassert>
#include <deque>
#include <vector>

void PrintArray(int* items, int size)
{
    int i=0;
    for(;i+1<size;++i)
    {
        std::cout << items[i] << " ";
    }
    if(i<size)
        std::cout << items[i] << std::endl;
}

struct Node
{
    int value;
    Node *parent;
    Node *less;
    Node *greater;
};

struct BST
{
    BST(size_t capacity) : capacity_(capacity), nodes_(new Node[capacity_]), size_(0), root_(nullptr)
    {
    }
    
    ~BST()
    {
        delete[] nodes_;
    }

    bool insert(int item)
    {
        if(size_ == capacity_)
        {
            return false;
        }

        if(root_ == nullptr)
        {
            nodes_[size_++] = {item, nullptr, nullptr, nullptr}; 
            root_ = &nodes_[size_-1];
            return true;
        }

        Node* node = root_;

        while(node)
        {
            if(item == node->value)
            {
                return false;
            }

            if(item > node->value)
            {
                if(node->greater == nullptr)
                {
                    nodes_[size_++] = {item, node, nullptr, nullptr}; 
                    node->greater = &nodes_[size_-1];
                    return true;
                }
                else
                {
                    node = node->greater;
                }
            }
            else
            {
                if(node->less == nullptr)
                {
                    nodes_[size_++] = {item, node, nullptr, nullptr}; 
                    node->less = &nodes_[size_-1];
                    return true;
                }
                else
                {
                    node = node->less;
                }
            }
        }
        return false;
    }  
    
    void print()
    {
        std::deque<Node*> fifo;
        fifo.push_back(root_);
        while(!fifo.empty())
        {
            size_t level_len = fifo.size();
            std::vector<int> values;
            for(size_t i = 0; i < level_len; ++i)
            {
                Node* node = fifo.front();
                if(node != nullptr)
                {
                    values.push_back(node->value);
                    fifo.push_back(node->less);
                    fifo.push_back(node->greater);
                }
                fifo.pop_front();
            }
            PrintArray(values.data(),values.size());
        }
    }
    
    size_t capacity_;
    Node *nodes_;
    size_t size_;
    Node* root_;
};


int main()
{
    BST bst(10000);
    int n =0;
    std::cin >> n;
    for(int i=0;i<n;++i)
    {
        int k =0 ;
        std::cin >> k;
        bst.insert(k);
    }
    bst.print();
    return 0;
}

