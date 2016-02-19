#include <iostream>

struct Node
{
    int value;
    Node * next;
};

Node * create_range_n_lst (int n)
{
    if (n < 1)
        return 0;
        
    Node * head = new Node;
    head->value = 0;
    head->next  = 0;

    Node * p = head;

    for (int i = 1; i < n; i++)
    {
        p->next = new Node;
        p->next->value = i;
        p->next->next = 0;

        p = p->next;
    }
    
    return head;
}

void print_lst (Node * head)
{
    Node * p = head;

    while (p)
    {
        std::cout << p->value;

        if (p->next)
            std::cout << '-';

        p = p->next;
    } 

    std::cout << '\n';
}

void delete_lst (Node * p)
{
    if (!p)
        return;

    if (p->next)
    {
        if (p->next->next)
            delete_lst (p->next);
        else
            delete p->next;
    }
    else
        delete p;
}

Node * reverse_lst (Node * head)
{
    Node * p = head;
    Node * prev = 0;
    Node * next = 0;

    while (p)
    {
        next = p->next;

        p->next = prev;

        prev = p;

        p = next;
    }

    return prev;
}

void alternate_merge (Node * head1, Node * head2)
{
    Node * p1 = head1;
    Node * p2 = head2;
    Node * p1_next = 0;

    // In loop: add from first list, add from second one 
    while (p2)
    {
        p1_next = p1->next;

        p1->next = p2;

        p1 = p2;

        p2 = p1_next;
    }
}

Node * rearrange_lst (Node * head)
{
    // Do nothing if lenght of list is 0/1/2
    if (!head || !head->next || !head->next->next)
        return head;

    // Find middle point -- O(n)
    Node * slow = head;
    Node * fast = head->next;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse second part of list -- O(n)
    Node * head_reversed = reverse_lst (slow->next);

    // Split list -- for merging
    slow->next = 0;

    // Merge two parts -- O(n)
    alternate_merge (head, head_reversed);

    return head;
}

int main()
{
    // Create test list
    const int lst_length = 100;

    Node * head = create_range_n_lst (lst_length);

    // Print source list
    print_lst (head);

    // Process list of length n
    // Time  complexity -- O(n)
    // Space complexity -- O(1)
    head = rearrange_lst (head);

    // Print rearranged list
    print_lst (head);

    // Delete list
    delete_lst (head);

    return 0;
}
