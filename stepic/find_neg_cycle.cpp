#include <iostream>
#include <vector>
#include <limits>

typedef std::pair<int,int> VertWeight;
typedef std::vector<std::vector<VertWeight> > WeightedGraph;

bool BellmanFord (WeightedGraph &G, int s, std::vector<int> &dist)
{
    int n = G.size();

    dist.resize(n,std::numeric_limits<int>::max()-1000);
    dist[s] = 0;

    bool changed;

    for (int iter = 0; iter < n; iter++)
    {
        changed = false;

        for (int v_idx = 0; v_idx < n; v_idx++)
            for (int i = 0; i < G[v_idx].size(); i++)
            {
                int v = G[v_idx][i].first;
                int w = G[v_idx][i].second;

                if (dist[v] > dist[v_idx] + w)
                {
                    changed = true;
                    dist[v] = dist[v_idx] + w;
                }
            }

        if (!changed)
            return changed;
    }

    return changed;
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    WeightedGraph G(n);

    for (int i = 0; i < m; i++)
    {
        int u;
        VertWeight vw;
        std::cin >> u >> vw.first >> vw.second;
        vw.first--;
        G[u-1].push_back(vw);
    }

    std::vector<int> dist;
    bool is_neg_cycle = BellmanFord(G,0,dist);
    std::cout << is_neg_cycle;

    return 0;
}
