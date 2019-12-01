#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdint>
#include <algorithm>

int randint(int a, int b)
{
    return rand()%(b-a)+a;
}

void swap(int64_t& a,int64_t& b)
{
    int64_t t = a;
    a = b;
    b = t;
}

void shuffle(int64_t* arr, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        int j = randint(i,size);
        swap(arr[i],arr[j]);
    }
}

struct Node
{
    int64_t value;
    Node* parent;
    Node* left;
    Node* right;
};

struct BST
{
    BST(): nodes_(new Node[1000000]()),size_(0),root_(nullptr), median_(nullptr)
    {
    }
    ~BST()
    {
        delete[] nodes_;
    }
    Node* FindNode(int64_t value)
    {
        Node* node = root_;
        while(node && node->value != value)
        {
            node = value < node->value ? node->left : node->right;
        }
        return node ? node : nullptr;
    }
    bool Remove(int64_t value)
    {
        Node* node = FindNode(value);
        if(!node)
            return false;
        RemoveNode(node);
        return true;
    }
    std::vector<int64_t> Print()
    {
        std::vector<int64_t> res;
        Node* node = root_;
        Node* prev = Prev(node);
        while(prev)
        {
            node = prev;
            prev = Prev(node);
        }
        while(node)
        {
            res.push_back(node->value);
            node = Next(node);
        }
        return res;
    }
    bool AddOrMove(Node*& node, Node*& child, int64_t value)
    {
        if(child)
        {
            node = child;
        }
        else
        {
            nodes_[size_++] = {value,node,nullptr,nullptr};
            child = &nodes_[size_-1];
            return true;
        }
        return false;
    }
    void Insert(int64_t value)
    {
        if(size_ == 0)
        {
            nodes_[size_++] = {value,nullptr,nullptr,nullptr};
            root_ = &nodes_[size_-1];
            median_ = root_;
            return;
        }
        Node* node = root_;
        while(node)
        {
            if(value < node->value)
            {
                if(AddOrMove(node, node->left, value))
                    break;
            }
            else 
            {
                if(AddOrMove(node, node->right, value))
                    break;
            }
        }
        if(value < median_->value)
        {
            if(size_%2==0)
                median_ = Prev(median_);
        }
        else if(size_%2!=0)
        {
            median_ = Next(median_);
        }
    }
    Node* Next(Node* node)
    {
        if(node->right)
        {
            node = node->right;
            while(node->left)
                node = node->left;
            return node;
        }
        else
        {
            while(node->parent && node->parent->left != node)
                node = node->parent;
            return node->parent;
        }
    }
    Node* Prev(Node* node)
    {
        if(node->left)
        {
            node = node->left;
            while(node->right)
                node = node->right;
            return node;
        }
        else
        {
            while(node->parent && node->parent->right != node)
                node = node->parent;
            return node->parent;
        }
    }
    void Delete(Node* node, Node* other_child)
    {
        if(node->parent)
        {
            if(node->parent->left == node)
                node->parent->left = other_child;
            else
                node->parent->right = other_child;
        }
        else
        {
            root_ = other_child;
        }
        if(other_child)
            other_child->parent = node->parent;
        Node* last = &nodes_[--size_];
        if(node != last)
        {
            *node = *last;
            if(last->parent)
            {
                if(last->parent->left == last)
                    node->parent->left = node;
                else
                    node->parent->right = node;
            }
            if(last->left)
                last->left->parent = node;
            if(last->right)
                last->right->parent = node;
            if(root_ == last)
                root_ = node;
            if(median_ == last)
                median_ = node;
            if(next_median_ == last)
                next_median_ = node;
        }
    }
    void RemoveNode(Node* node)
    {
        if(node->left != nullptr && node->right != nullptr)
        {
            Node* next = Next(node);
            if(next == next_median_)
                next_median_ = node;
            node->value = next->value;
            node = next;
        }
        if(node->left)
        {
            Delete(node,node->left);
        }
        else if(node->right)
        {
            Delete(node,node->right);
        }
        else 
        {
            Delete(node,nullptr);
        }
    }
    int64_t ExtractMedian()
    {
        int64_t val = median_->value;
        next_median_ = size_%2 == 0 ? Next(median_) : Prev(median_);
        if(next_median_)
        {
            //int64_t next_val = next_median->value;
            RemoveNode(median_);
            //median_ = FindNode(next_val);
            median_ = next_median_;
        }
        else
        {
            RemoveNode(median_);
            median_ = nullptr;
        }
        return val;
    }
    void Clear()
    {
        root_=nullptr;
        median_=nullptr;
        size_ = 0;
    }
    Node* nodes_;
    size_t size_;
    Node* root_;
    Node* median_;
    Node* next_median_;
};


bool Equals(const std::vector<int64_t>& a, const std::vector<int64_t>& b)
{
    bool val = a==b;
    if(val)
        puts("OK");
    else
        puts("FAIL");
    return val;
}

void test()
{
    BST bst;
    const std::vector<int64_t> range = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    auto values = range;
    //print test
    shuffle(values.data(), values.size());
    for(size_t i = 0; i < values.size(); i++)
        bst.Insert(values[i]);
    Equals(range,bst.Print());
    bst.Remove(0);
    Equals({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},bst.Print());
    bst.Remove(11);
    Equals({1,2,3,4,5,6,7,8,9,10,12,13,14,15,16,17,18,19},bst.Print());
    bst.Remove(12);
    Equals({1,2,3,4,5,6,7,8,9,10,13,14,15,16,17,18,19},bst.Print());
    bst.Remove(15);
    Equals({1,2,3,4,5,6,7,8,9,10,13,14,16,17,18,19},bst.Print());
    bst.Insert(2);
    bst.Insert(10);
    bst.Insert(10);
    bst.Insert(19);
    bst.Insert(1);
    Equals({1,1,2,2,3,4,5,6,7,8,9,10,10,10,13,14,16,17,18,19,19},bst.Print());
    bst.Remove(3);
    Equals({1,1,2,2,4,5,6,7,8,9,10,10,10,13,14,16,17,18,19,19},bst.Print());
    bst.Clear();
    //linked list root tail remove
    values = range;
    for(size_t i = 0; i < values.size(); i++)
        bst.Insert(values[i]);
    bst.Remove(0);
    Equals({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},bst.Print());
    bst.Remove(19);
    Equals({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18},bst.Print());
    bst.Remove(3);
    Equals({1,2,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18},bst.Print());
    bst.Clear();
    //rev linked list root tail remove
    values = range;
    for(size_t i = 0; i < values.size(); i++)
        bst.Insert(values[values.size()-1-i]);
    bst.Remove(0);
    Equals({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},bst.Print());
    bst.Remove(19);
    Equals({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18},bst.Print());
    bst.Remove(3);
    Equals({1,2,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18},bst.Print());
    bst.Clear();
    bst.Insert(0);
    bst.Insert(1);
    Equals({0,1},bst.Print());
    bst.Remove(0);
    Equals({1},bst.Print());
    bst.Remove(1);
    bst.Insert(10);
    Equals({10},bst.Print());
    bst.Clear();
    //median
    bst.Insert(1);
    bst.Insert(2);
    bst.Insert(3);
    bst.Insert(4);
    bst.Insert(5);
    puts(bst.ExtractMedian() == 3 ? "OK" : "FAIL");
    puts(bst.ExtractMedian() == 2 ? "OK" : "FAIL");
    puts(bst.ExtractMedian() == 4 ? "OK" : "FAIL");
    puts(bst.ExtractMedian() == 1 ? "OK" : "FAIL");
    puts(bst.ExtractMedian() == 5 ? "OK" : "FAIL");
    bst.Insert(5);
    bst.Insert(5);
    bst.Insert(5);
    puts(bst.ExtractMedian() == 5 ? "OK" : "FAIL");
    bst.Insert(1);
    bst.Insert(1);
    Equals({1,1,5,5},bst.Print());
    puts(bst.ExtractMedian() == 1 ? "OK" : "FAIL");
    puts(bst.ExtractMedian() == 5 ? "OK" : "FAIL");
}

struct PseudoBST
{
    void Insert(int64_t value)
    {
        buffer_.push_back(value);
        std::sort(buffer_.begin(),buffer_.end());
    }
    int64_t ExtractMedian()
    {
        size_t mid = (buffer_.size()-1)/2;
        auto value = buffer_[mid];
        buffer_.erase(buffer_.begin() + mid);
        return value;
    }
    std::vector<int64_t> buffer_;
};

int main(int argc, char const *argv[])
{
    test();
    return 0;
    //if(!freopen ("/home/jrojer/Documents/work/sport/rmid/test/rmid_test.txt", "r", stdin))
    {
        //puts("bad freopen");
        //return 0;
    }
    std::vector<int64_t> buffer;
    BST bst;
    PseudoBST pbst;
    int num_test_cases = 0;
    scanf("%d",&num_test_cases);
    //int counter = 0;
    //int input_line_counter = 0;
    for(int i = 0; i < num_test_cases; i++)
    {
        int64_t input = 0;
        scanf("%lld",&input);
        while(input != 0)
        {
            if(input == -1)
            {
                //++counter;
                shuffle(buffer.data(),buffer.size());
                for(auto x: buffer)
                {
                    bst.Insert(x);
                    //pbst.Insert(x);
                }
                buffer.clear();
                //auto pbst_median = pbst.ExtractMedian();
                auto bst_median = bst.ExtractMedian();

                printf("%lld\n", bst_median);
            }
            else
            {
                buffer.push_back(input);
            }
            scanf("%lld",&input);
            //printf("input line:%d\n", input_line_counter++);
        }
        bst.Clear();
        printf("\n");
    }
    return 0;
}
