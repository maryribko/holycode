#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <limits>

class MinHeap{
public:
  MinHeap (int n, int s, std::vector<int> &_dist);
  void insert(int x);
  int extract();
  void change_priority (int v, int dist_v);

private:
  void siftup(int idx);
  void siftdown(int idx);
  void swap_values(int idx1, int idx2);

public:
  int values_size;
  std::vector<int> values;
  std::vector<int> &dist;
};

MinHeap::MinHeap (int n, int s, std::vector<int> &_dist):
    dist(_dist)
{
  values_size = n;
  values.resize(n);

  values[0] = s;

  int val = 0;

  for (int i = 1; i < n; i++)
  {
      if (val == s)
          val++;
      values[i] = val++;
  }
}

void
MinHeap::swap_values (int idx1, int idx2)
{
    int tmp = values[idx1];
    values[idx1] = values[idx2];
    values[idx2] = tmp;
}

void
MinHeap::siftup (int idx)
{
  if (idx == 0)
    return;

  int parent_idx = (int) floor((idx-1)/2.0f);

  if (dist[values[parent_idx]] < dist[values[idx]])
    return;

  swap_values(parent_idx, idx);
  siftup(parent_idx);
}

void
MinHeap::siftdown (int idx)
{

  int child_idx_1 = 2 * idx + 1;
  int child_idx_2 = 2 * idx + 2;

  if (child_idx_1 > values_size - 1)
    return;

  int next_idx;

  if (child_idx_2 > values_size - 1)
  {
    if (dist[values[idx]] <= dist[values[child_idx_1]])
      return;

    next_idx = child_idx_1;
  }
  else
  {
    if (dist[values[idx]] <= dist[values[child_idx_1]]
      && dist[values[idx]] <= dist[values[child_idx_2]])
    return;

    next_idx = (dist[values[child_idx_1]] < dist[values[child_idx_2]]) ? child_idx_1 : child_idx_2;
  }

  swap_values(next_idx, idx);
  siftdown(next_idx);
}


void
MinHeap::insert (int x)
{
  values.push_back(x);
  siftup(values_size-1);
}

int
MinHeap::extract()
{
  int min = values[0];
  values[0] = values[values_size-1];
  values_size--;
  siftdown(0);

  return min;
}

void
MinHeap::change_priority (int v, int dist_v)
{
    dist[v] = dist_v;

    int idx;

    for (idx = 0; idx < values_size; idx++)
        if (values[idx] == v)
            break;

    siftup(idx);
}

typedef std::pair<int,int> VertWeight;
typedef std::vector<std::vector<VertWeight> > WeightedGraph;

void Dijkstra (WeightedGraph &G, int s, std::vector<int> &dist)
{
    int n = G.size();

    dist.resize(n,std::numeric_limits<int>::max()-1000);
    dist[s] = 0;

    MinHeap min_heap(n,s,dist);

    while (min_heap.values_size > 0)
    {
        int min_idx = min_heap.extract();

        for (int i = 0; i < G[min_idx].size(); i++)
        {
            int v = G[min_idx][i].first;
            int w = G[min_idx][i].second;

            if (dist[v] > dist[min_idx] + w)
            {
                dist[v] = dist[min_idx] + w;
                min_heap.change_priority(v,dist[v]);
            }
        }

    }
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

    int u, v;
    std::cin >> u >> v;
    u--; v--;

    std::vector<int> dist;
    Dijkstra(G,u,dist);

    if (dist[v] < std::numeric_limits<int>::max()-1000)
        std::cout << dist[v];
    else
        std::cout << (-1);


    return 0;
}
