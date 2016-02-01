#include <iostream>
#include <vector>

std::vector<bool> visited;

void Explore (int u, std::vector<std::vector<int> > &edges, 
			  std::vector<int> &toposort_verts)
{
	//std::cout << u << " is processing...\n";
	if (!visited[u])
		visited[u] = true;		
	
	for (int i = 0; i < edges[u].size(); i++)
	{
		int v = edges[u][i];
		
		if (!visited[v])
			Explore(v, edges, toposort_verts);		
	}
	
	toposort_verts.push_back(u);
}

int main()
{
	int n,m;
	std::cin >> n >> m;
	
	std::vector<std::vector<int> > G(n);
	std::vector<std::vector<int> > G_r(n);	
		
	for (int i = 0; i < m; i++)
	{
		int u,v;
		std::cin >> u >> v;
		G[u-1].push_back(v-1);
		G_r[v-1].push_back(u-1);
	}
	
	// G_r
	visited.resize(n,false);
		
	std::vector<int> toposort_g_r;
	
	for (int v = 0; v < n; v++)	
		if (!visited[v])		
			Explore(v, G_r, toposort_g_r);	
	
	// G
	visited.assign(n,false);	
	std::vector<int> trash;
	int scc_cnt = 0;
	
	for (int i = n-1; i >= 0; i--)
	{	
		int v = toposort_g_r[i];
		//std::cout << v << std::endl;
		if (!visited[v])
		{	
			Explore(v, G, trash);	
			scc_cnt++;		
		}
	}
	
	std::cout << scc_cnt;
	
	return 0;
}
