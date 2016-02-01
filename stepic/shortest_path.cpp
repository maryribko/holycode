#include <iostream>
#include <vector>
#include <queue>

void BFS (std::vector<std::vector<int> > &G, 
		  int s, std::vector<int> &dists)
{	
	dists[s] = 0;

	std::queue<int> Q;
	Q.push(s);
	
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		std::cout << (u+1) << " is ejected\n";
		
		for (int i = 0; i < G[u].size(); i++)
		{			
			int v = G[u][i];
			
			if (dists[v] == -1)
			{
				Q.push(v);
				dists[v] = dists[u] + 1;				
			}		
		}
	}
}
		  
int main()
{
	int n,m;
	std::cin >> n >> m;
	
	std::vector<std::vector<int> > G(n);
	std::vector<int> dists(n, -1);	
		
	for (int i = 0; i < m; i++)
	{
		int u,v;
		std::cin >> u >> v;
		G[u-1].push_back(v-1);
		G[v-1].push_back(u-1);
	}
	
	int s,t;
	std::cin >> s >> t;	

	BFS(G,s-1,dists);
	
	std::cout << dists[t-1];
	
	return 0;
}
