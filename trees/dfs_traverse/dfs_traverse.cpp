#include <iostream>


struct Node
{
    int value;
    Node* next;
};

template<typename T>
struct ArrayList 
{
    ArrayList(size_t capacity): array_(new T[capacity]()), size_(0)
    {}
    ~ArrayList()
    {
        delete[] array_;
    }
    T& operator[](size_t i)
    {
        return array_[i];
    }
    T& push(const T& item)
    {
        array_[size_++] = item;
        return array_[size_-1];
    }
    T pop()
    {
        return array_[--size_];
    }
    bool empty()
    {
        return size_==0;
    }
    T* array_;
    size_t size_;
};


void sort(Node* linked_list)
{
    Node* head = linked_list;
    while(head)
    {
        Node* node = head->next;
        while(node)
        {
            if(node->value > head->value)
            {
                int t = node->value;
                node->value = head->value;
                head->value = t;
            }
            node = node->next;
        }
        head = head->next;
    }
}


struct AdjacencyList
{
    AdjacencyList(size_t num_vertices): node_pool_(2*num_vertices), heads_(num_vertices), tails_(num_vertices), num_vertices_(num_vertices)
    {}
    void AddEdge(int i, int j)
    {
        Node& new_node = node_pool_.push({j,nullptr});
        Node* tail = tails_[i];
        if(tail != nullptr)
        {
            tail->next = &new_node;
        }
        else
        {
            heads_[i] = &new_node;
        }
        tails_[i] = &new_node;
    }
    Node* GetHead(int i)
    {
        return heads_[i];
    }
    void Sort()
    {
        for(size_t i = 0; i < num_vertices_; ++i)
        {
            sort(heads_[i]);
        }
    }
    ArrayList<Node> node_pool_;
    ArrayList<Node*> heads_;
    ArrayList<Node*> tails_;
    size_t num_vertices_;
};


void Dfs(AdjacencyList& adj_list, size_t num_vertices, int root)
{
    ArrayList<bool> visited(num_vertices);
    ArrayList<int> result(num_vertices);
    ArrayList<int> stack(num_vertices);
    stack.push(root);

    while(!stack.empty())
    {
        int v = stack.pop();
        result.push(v);
        visited[v] = true;
        Node* node = adj_list.GetHead(v);
        while(node)
        {
            int u = node->value;
            if(!visited[u])
                stack.push(u);
            node = node->next;
        }
    }
    size_t i = 0;
    for(;i+1<num_vertices; ++i)
    {
        printf("%d ",result[i]);
    }
    printf("%d\n",result[i]);
}

int main() 
{
    int n = 0;
    int root = 0;
    scanf("%d",&n);
    scanf("%d",&root);

    AdjacencyList adj_list(n);

    for(int i=0;i<n-1;++i)
    {
        int x = 0;
        int y = 0;
        scanf("%d %d",&x,&y);
        adj_list.AddEdge(x,y);
        adj_list.AddEdge(y,x);
    }

    adj_list.Sort();

    Dfs(adj_list, n, root);

    return 0;
}