#include <iostream>
#include <vector>

std::vector<std::vector<int> > edges;
std::vector<bool> visited;
std::vector<int> toposort_verts;

void Explore (int u)
{
	//std::cout << u << " is processing...\n";
	if (!visited[u])
		visited[u] = true;		
	
	for (int i = 0; i < edges[u].size(); i++)
	{
		int v = edges[u][i];
		
		if (!visited[v])
			Explore(v);		
	}
	
	toposort_verts.push_back(u+1);
}

int main()
{
	int n,m;
	std::cin >> n >> m;
	
	edges.resize(n);
		
	for (int i = 0; i < m; i++)
	{
		int u,v;
		std::cin >> u >> v;
		edges[u-1].push_back(v-1);
	}
	
	visited.resize(n,false);
	toposort_verts.reserve(n);	
		
	for (int v = 0; v < n; v++)
		if (!visited[v])	
			Explore(v);

	for (int i = n-1; i >= 0; i--)	
			std::cout << toposort_verts[i] << " ";
			
	return 0;
}
