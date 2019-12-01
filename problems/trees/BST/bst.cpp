#include <iostream>
#include <cstdlib>
#include <cassert>


struct Node
{
    int value;
    Node *parent;
    Node *less;
    Node *greater;
};

struct FIFO
{
    FIFO(): array_size_(100), array_(new Node*[array_size_]), start_(0), end_(0)
    {
    }
    ~FIFO()
    {
        delete[] array_;
    }
    Node *pop()
    {
        Node* item = array_[start_];
        start_ = (start_+1)%array_size_;
        return item;
    }
    void push(Node *a)
    {
        array_[end_] = a;
        end_ = (end_+1)%array_size_;
    }
    bool empty()
    {
        return end_ == start_;
    }
    size_t size()
    {
        return end_ > start_ ? end_-start_ : start_-end_;
    }
    const size_t array_size_;
    Node** array_;
    size_t start_;
    size_t end_;
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

    void RemoveNode(Node* node)
    {
        //replace
        Node* old_ptr = &nodes_[size_-1];
        *node = nodes_[--size_];
        //fix
        if(node->parent)
        {
            if(node->parent->less == old_ptr)
                node->parent->less = node;
            else
                node->parent->greater = node;
        }
    }

    void Detach(Node* node, Node* new_child)
    {
        if(node->parent)
        {
            if (node->parent->less == node)
                node->parent->less = new_child;
            else 
                node->parent->greater = new_child;
        }
    }

    bool remove(int item)
    {
        Node* node = FindNode(item);

        if(node == nullptr)
            return false;

        Node* child = nullptr;
        if(node->less != nullptr && node->greater != nullptr)
        {
            Node* s = successor(node);
            assert(s!=nullptr);
            node->value = s->value;
            node = s;
        }
        if(node->less != nullptr)
        {
            child = node->less;
        }
        else if(node->greater != nullptr)
        {
            child = node->greater;
        }
        Detach(node,child);
        RemoveNode(node);
        return true;
    }
    bool find(int item)
    {
        return FindNode(item) != nullptr;
    }
    Node* FindNode(int item)
    {
        Node* node = root_;
        while(node)
        {
            if(item == node->value)
                return node;
            else if(item > node->value)
                node = node->greater;
            else
                node = node->less;
        }
        return nullptr;
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
    size_t size()
    {
        return size_;
    }
    void clear()
    {
        root_ = nullptr;
        size_ = 0;
    }
    bool empty()
    {
        return size_ == 0;
    }
    void print2()
    {
        FIFO fifo;
        fifo.push(root_);
        while(!fifo.empty())
        {
            size_t level_len = fifo.size();
            for(size_t i = 0; i < level_len; ++i)
            {
                Node* node = fifo.pop();
                if(node != nullptr)
                {
                    printf("%d ", node->value);
                    fifo.push(node->less);
                    fifo.push(node->greater);
                }
            }
            printf("\n");
        }
    }
    void print()
    {
        FIFO fifo;
        fifo.push(root_);
        while(!fifo.empty())
        {
            size_t level_len = fifo.size();
            for(size_t i = 0; i < level_len; ++i)
            {
                Node* node = fifo.pop();
                if(node != nullptr)
                {
                    printf(" %3d ", node->value);
                    fifo.push(node->less);
                    fifo.push(node->greater);
                }
                else
                {
                    printf(" --- ");
                }
            }
            printf("\n");
        }
    }
    Node* successor(Node* current)
    {
        if(current->greater)
        {
            Node* node = current->greater;
            while(node->less) 
                node = node->less;
            return node;
        }
        else
        {
            Node* node = current;
            while(node->parent && node->parent->less != node)
            {
                node = node->parent;
            }
            return node->parent;
        }
        return nullptr;
    }
    void PrintContents()
    {
        Node* node = root_;
        while(node->less)
        {
            node = node->less;
        }
        while(node)
        {
            printf("%d ",node->value);
            node = successor(node);
        }
        puts("");
    }
    size_t capacity_;
    Node *nodes_;
    size_t size_;
    Node* root_;
};

int randint(int a, int b)
{
    return rand()%(b-a) + a;
}

void test()
{
    BST bst(100);

    for(int i= 0 ; i < 20; ++i)
    {
        bst.insert(randint(0,90));
        //bst.insert(i);
    }
    bst.print();

    for(int i= 0 ; i < 0; ++i)
    {
        int val = randint(0,90);
        if(bst.find(val))
            printf("%d found\n",val);
        else
            printf("%d -\n",val);
    }

    bst.remove(27);

    puts("");
    bst.print();

    bst.PrintContents();
}

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
    bst.print2();
    return 0;
}