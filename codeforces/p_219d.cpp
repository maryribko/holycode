#include <iostream>

struct Node
{
    Node(int _v, int _isreversed, Node *_next){
        v = _v;
        isreversed = _isreversed;
        next = _next;
    }

    int v;
    int isreversed;
    Node *next;
};

#define MAX_N 200005
Node* roads[MAX_N];
int n;
int capitals[MAX_N];
int num_capitals;
int min_changed;

void add_road(int u, int v, int isreversed)
{
    if (roads[u])
    {
        Node *road = new Node(v, isreversed, roads[u]->next);
        roads[u]->next = road;
    }
    else
        roads[u] = new Node(v, isreversed, 0);
}

void delete_roads(Node *roads)
{
    if (roads)
    {
        if (roads->next)
            delete_roads(roads->next);

        delete roads;
    }
}

int dfs(int u, int from)
{
    int num_changed = 0;
    Node *p = roads[u];

    while(p)
    {
        if (p->v != from)
        {
            num_changed += p->isreversed;
            num_changed += dfs(p->v, u);
        }
        p = p->next;
    }

    return num_changed;
}

void print_roads()
{
    for (int u = 1; u <= n; u++)
    {
        Node *p = roads[u];
        while (p)
        {
            std::cout << u << ' ' << p->v << ' ' << p->isreversed << '\n';
            p = p->next;
        }
    }
}

int dfs2(int u, int from, int u_changed)
{
    if (u_changed < min_changed)
    {
        min_changed = u_changed;
        num_capitals = 1;
        capitals[num_capitals-1] = u;
    }
    else if (u_changed == min_changed)
    {
        capitals[num_capitals] = u;
        num_capitals++;
    }

    Node *p = roads[u];
    while(p)
    {
        if (p->v != from)
        {
            int v_changed = u_changed + 1 - 2 * p->isreversed;
            dfs2(p->v, u, v_changed);
        }
        p = p->next;
    }
}


int main()
{
    // Process input data
    std::cin >> n;
    for (int i = 0; i < MAX_N; i++)
        roads[i] = 0;

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        std::cin >> u >> v;
        add_road(u, v, 0);
        add_road(v, u, 1);
    }

    // DFS for finding num changes if city 1 is the capital
    int changed_1 = dfs(1, 0);

    // DFS for computing num changes for all other cities
    min_changed = changed_1 + 1;
    dfs2(1, 0, changed_1);

    // Sort capitals
    int capitals_bool[MAX_N];
    for (int i = 1; i <= n; i++)
        capitals_bool[i] = 0;

    for (int i = 0; i < num_capitals; i++)
        capitals_bool[capitals[i]] = 1;

    // Output result
    std::cout << min_changed << '\n';
    for (int i = 1; i <= n; i++)
        if (capitals_bool[i])
            std::cout << i << ' ';

    // Delete used Nodes
    for (int u = 1; u <= n; u++)
        delete_roads(roads[u]);
}