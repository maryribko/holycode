#include <iostream>
#include <vector>
#include <string>
#include <set>

#define NUM_LATIN_LETTERS 26

typedef std::vector<std::set<int>> OrderGraph;

bool fillOrderGraph (OrderGraph & order_graph, std::vector<int> & num_in)
{
    bool possible = true;

    order_graph.resize(NUM_LATIN_LETTERS);
    num_in.resize(NUM_LATIN_LETTERS, 0);

    int n;
    std::cin >> n;

    std::string prev;
    std::string cur;

    std::cin >> prev;

    for (int i = 1; i < n; i++)
    {
        std::cin >> cur;

        int first_dif_idx = 0;

        while (first_dif_idx < prev.size()
               && first_dif_idx < cur.size()
               && prev[first_dif_idx] == cur[first_dif_idx])
            first_dif_idx++;

        if (first_dif_idx == prev.size() || first_dif_idx == cur.size())
        {
            if (prev.size() > cur.size())
                possible = false;
            continue;
        }

        int prev_letter_idx = prev[first_dif_idx] - 'a';
        int cur_letter_idx  = cur [first_dif_idx] - 'a';

        order_graph[prev_letter_idx].insert(cur_letter_idx);
        num_in[cur_letter_idx]++;

        prev = cur;
    }

    return possible;
}

struct VertInfo
{
    VertInfo() : visited(false), start_time(-1), finish_time(-1) {}

    bool visited;
    int start_time;
    int finish_time;
};

bool Explore (int u, const OrderGraph & order_graph, std::vector<VertInfo> & verts_info, int & time_cnt)
{
    if (!verts_info[u].visited)
    {
        verts_info[u].visited = true;
        verts_info[u].start_time = time_cnt++;
    }

    for (int v: order_graph[u])
    {
        if (!verts_info[v].visited)
        {
            if (Explore(v, order_graph, verts_info, time_cnt))
                return true;
        }
        else
            if (verts_info[v].finish_time == -1)
                return true;
    }

    verts_info[u].finish_time = time_cnt++;

    return false;
}

bool findCycle (const OrderGraph & order_graph)
{
    int time_cnt = 0;
    std::vector<VertInfo> verts_info (NUM_LATIN_LETTERS);

    for (int v = 0; v < NUM_LATIN_LETTERS; v++)
    {
        if (!verts_info[v].visited)
            if (Explore(v, order_graph, verts_info, time_cnt))
                return true;
    }

    return false;
}

void ExploreTopoSort (int u, const OrderGraph & order_graph,
                      std::vector<bool> & visited,
                      std::vector<int> & topo_sort)
{
    if (!visited[u])
        visited[u] = true;

    for (int v: order_graph[u])
        if (!visited[v])
            ExploreTopoSort (v, order_graph, visited, topo_sort);

    topo_sort.push_back(u);
}

void outputOrder (const OrderGraph & order_graph, const std::vector<int> & num_in)
{
    std::vector<bool> visited(NUM_LATIN_LETTERS,false);
    std::vector<int> topo_sort;

    for (int v = 0; v < NUM_LATIN_LETTERS; v++)
        if (!visited[v] && num_in[v] == 0)
            ExploreTopoSort (v, order_graph, visited, topo_sort);

    for (int i = NUM_LATIN_LETTERS-1; i >= 0; i--)
        std::cout << char(topo_sort[i] + 'a');
}

int main()
{
    OrderGraph order_graph;
    std::vector<int> num_in;

    if (!fillOrderGraph (order_graph, num_in))
    {
        std::cout << "Impossible";
        return 0;
    }

    bool found_cycle = findCycle(order_graph);

    if (found_cycle)
        std::cout << "Impossible";
    else
        outputOrder(order_graph, num_in);

    return 0;
}
