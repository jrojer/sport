# Algorithm problems on trees

## Max depth
https://leetcode.com/problems/maximum-depth-of-binary-tree/  
**Idea:** DFS with stack.
```c++
struct StackItem
{
    TreeNode* node;
    int depth;
};
int maxDepth(TreeNode* root) 
{
    int max_depth = 0;
    vector<StackItem> stack(1,{root,1});
    while(!stack.empty())
    {
        auto item = stack.back();
        stack.pop_back();
        if(item.node)
        {
            if(item.depth > max_depth)
            {
                max_depth = item.depth;
            }
            if(item.node->left)
            {
                stack.push_back({item.node->left,item.depth+1});
            }
            if(item.node->right)
            {
                stack.push_back({item.node->right,item.depth+1});
            }
        }
    }   
    return max_depth;
}
```

## Same tree
https://leetcode.com/problems/same-tree/solution/  
**Idea:** simultaneous WFS.
```c++
bool isSameTree(TreeNode* t1, TreeNode* t2) 
{
    deque<TreeNode*> q1;
    deque<TreeNode*> q2;
    q1.push_back(t1);
    q2.push_back(t2);
    while(!q1.empty() && !q2.empty())
    {
        auto* node1 = q1.back();
        auto* node2 = q2.back();
        q1.pop_back();
        q2.pop_back();
        if((node1 || node2) && (!node1 && node2 || !node2 && node1 || node1->val != node2->val))
        {
           return false; 
        }
        if(node1)
        {
            q1.push_back(node1->left);
            q1.push_back(node1->right);
        }
        if(node2)
        {
            q2.push_back(node2->left);
            q2.push_back(node2->right);
        }
    }
    return q1.empty() && q2.empty();
}
```


## Trie

https://leetcode.com/problems/implement-trie-prefix-tree/  
https://neerc.ifmo.ru/wiki/index.php?title=%D0%91%D0%BE%D1%80  
```c++

class Trie {
    struct Node;
    using NodePtr = shared_ptr<Node>;
    
public:

    Trie() : root_(new Node{})
    {

    }

    void insert(const string& word) 
    {
        assert(!word.empty());
        auto node = root_;
        for(char ch: word)
        {
            assert('a' <= ch && ch <= 'z');
            int idx = ch - 'a';
            if(!node->next[idx])
            {
                node->next[idx] = NodePtr(new Node{});
            }
            node = node->next[idx];
        }
        node->last = true;
    }

    bool search(const string& word) const
    {
        assert(!word.empty());
        auto node = root_;
        for(char ch: word)
        {
            assert('a' <= ch && ch <= 'z');
            int idx = ch - 'a';
            if(node->next[idx])
            {
                node = node->next[idx];
            }
            else
            {
                return false;
            }
        }
        return node->last;
    }

    bool startsWith(const string& word) const
    {
        assert(!word.empty());
        auto node = root_;
        for(char ch: word)
        {
            assert('a' <= ch && ch <= 'z');
            int idx = ch - 'a';
            if(node->next[idx])
            {
                node = node->next[idx];
            }
            else
            {
                return false;
            }
        }
        return true;
    }

private: 
    static const size_t kAlphabetSize = 'z'-'a'+1;
    struct Node
    {
        array<NodePtr,kAlphabetSize> next;
        bool last;
    };
    NodePtr root_;
};
```


## Binary tree level order traversal
https://leetcode.com/problems/binary-tree-level-order-traversal/  
**Idea:** perform WFS and count number of nodes on the current level and the number of nodes on the next level. If current level has null node the number of nodes on the next level is decreased by 2. The last level will be empty.

```c++
vector<vector<int>> levelOrder(TreeNode* root) 
{
    int level_size = 1;
    int next_level_size = 2;
    int count = 0;
    vector<vector<int>> res;
    vector<int> level;
    deque<TreeNode*> q(1,root);
    while(!q.empty())
    {
        auto* node = q.front();
        q.pop_front();
        ++count;
        if(node)
        {
            level.push_back(node->val);
            q.push_back(node->left);
            q.push_back(node->right);
        }
        else
        {
            next_level_size -= 2;
        }
        if(count == level_size && !level.empty())
        {
            level_size = next_level_size;
            count = 0;
            next_level_size = 2*level_size;
            res.emplace_back(move(level));
        }
    }
    return res;
}
```
