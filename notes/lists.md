# Lists


## Reorder
https://leetcode.com/problems/reorder-list/  
Based on:
 * Middle. https://leetcode.com/problems/middle-of-the-linked-list/
 * Merge. https://leetcode.com/problems/merge-two-sorted-lists/
 * Reverse. https://leetcode.com/problems/reverse-linked-list/
```c++
ListNode* middle(ListNode* head)
{
    if(!head || !head->next)
    {
        return head;
    }
    // at least 2 elements
    ListNode* node1_prev = nullptr;
    auto* node1 = head;
    auto* node2 = head;
    while(node2 && node2->next)
    {
        node1_prev = node1;
        node1 = node1->next;
        node2 = node2->next->next;
    }
    if(node2)
    {
        return node1; // exact middle
    }
    else
    {
        return node1_prev; // left middle
    }
}

/*
1  2 3 4
13 2

2 1 3 4
3 1 2

3 2 1 4
3   1 2

4 3 2 1
3     1 2
*/
ListNode* reverse(ListNode* head)
{
    if(!head || !head->next)
    {
        return head;
    }
    auto* first = head;
    auto* last = head;
    auto* next = head->next;
    while(next)
    {
        last->next = next->next;
        next->next = first;
        
        first = next;
        next = last->next;
    }
    return first;
}

ListNode* merge(ListNode* l1, ListNode* l2)
{
    ListNode dummy(0);
    auto* head = &dummy;
    int c = 0;
    while(l1 && l2)
    {
        if(c == 0)
        {
            head->next = l1;
            l1 = l1->next;
        }
        else
        {
            head->next = l2;
            l2 = l2->next;
        }
        head = head->next;
        c ^= 1;
    }
    while(l1)
    {
        head->next = l1;
        l1 = l1->next;
    }
    while(l2)
    {
        head->next = l2;
        l2 = l2->next;
    }
    return dummy.next;
}

ListNode* reorderList(ListNode* head)
{
    if(!head || !head->next)        // check input
    {
        return head;
    }
    auto* mid = middle(head);       // find middle
    auto* l1 = reverse(mid->next);  // reverse the second half
    mid->next = nullptr;            // null terminate the first half
    auto* l2 = head;                // the first half
    return merge(l2,l1);            // merge halves
}
```


## Find cycle
https://leetcode.com/problems/linked-list-cycle/

Let 2 pointers run forward. The first runs 1 step at a time, the second -- 2 steps.  
**Statement**: if there is a cycle then these 2 pointers will eventually meet.  
**Proof**: the distance between the pointers is increasing by 1 at each iteration, so eventually the distance must become a multiple of the length of cycle.
```c++
bool hasCycle(ListNode *head) 
{
    if(!head) 
    {
        return false;
    }
    auto* node1 = head;
    auto* node2 = head->next;
    while(node2 && node2->next && node1 != node2)
    {
        node1 = node1->next;
        node2 = node2->next->next;
    }
    return node1 == node2;
}
```

## Find and remove n-th element
https://leetcode.com/problems/remove-nth-node-from-end-of-list/  
**Idea:** 2 pointers with the distance _n_ between them.
```c++
 ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
    if(n<=0 || !head)
    {
        return head;
    }
    ListNode* node1 = head;
    ListNode* node2 = head;
    int i=0;
    for(;i<n && node2;++i)
    {
        node2 = node2->next;
    }
    if(i<n)
    {
        return head;
    }
    if(!node2)
    {
        return head->next;
    }
    while(node2->next) // when loop finishes, node1 points to the element one before the n-th
    {
        node2=node2->next;
        node1=node1->next;
    }
    node1->next = node1->next->next;
    return head;
}
```

## Delete node, given only access to that node
https://leetcode.com/problems/delete-node-in-a-linked-list/
```c++
    void deleteNode(ListNode* node) 
    {
        std::swap(*node,*node->next);
    }
```

## Filter list
https://leetcode.com/problems/remove-linked-list-elements/  
**Idea:** access each node via a previous node, handle the first node separately. The `node->next` changes on each iteration either because of the next node was deleted or the current node was advanced forward. 

```c++
ListNode* removeElements(ListNode* head, int val) 
{
    if(!head)
    {
        return head;
    }
    auto* node = head;
    while(node && node->next)
    {
        if(node->next->val == val)
        {
            node->next = node->next->next;
        }
        else
        {
            node = node->next;
        }
    }
    if(head->val == val)
    {
        head = head->next;
    }
    return head;
}
```

## Check palindrome
```c++
ListNode* reverse(ListNode* head)
{
    if(!head)
    {
        return head;
    }
    auto* node1 = head;
    auto* node2 = head->next;
    auto* node3 = head;
    
    while(node2)
    {
        node1->next = node2->next; 
        node2->next = node3;
        node3 = node2;
        node2 = node1->next;
    }
    return node3;
}

bool equal(ListNode* l1, ListNode* l2) // for this particular case
{
    while(l1 && l2)
    {
        if(l1->val != l2->val)
        {
            return false;
        }
        l1 = l1->next;
        l2 = l2->next;
    }
    //return l1 && l2;
    return true; // |len(l1) - len(l2)| <= 1
}

/*
1 1 2 1
  m
1 1 1 2
  m n
*/
bool isPalindrome(ListNode* head) 
{
    if(!head)
    {
        return true;
    }
    auto* l1_last = middle(head);
    auto* l2_head = reverse(l1_last->next);
    auto* tmp = l1_last->next; // save
    l1_last->next = nullptr; // modify
    bool answer = equal(head, l2_head); //modify
    reverse(l2_head); // restore
    l1_last->next = tmp; // restore
    return answer;
}
```

## Intersection
https://leetcode.com/problems/intersection-of-two-linked-lists/
```c++
```

https://leetcode.com/problems/linked-list-cycle-ii/  
https://leetcode.com/problems/palindrome-linked-list/  
https://leetcode.com/problems/sort-list/ - тут Merge Sort  