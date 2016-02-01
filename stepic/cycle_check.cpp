#include <iostream>
#include <vector>

int time_cnt;
std::vector<std::vector<int> > edges;
std::vector<bool> visited;
std::vector<int> start_time;
std::vector<int> finish_time;

bool Explore (int u)
{
	//std::cout << u << " is processing...\n";
	if (!visited[u])
	{
		visited[u] = true;
		start_time[u] = time_cnt++;
	}
	
	bool flag_cycle = false;
	
	for (int i = 0; i < edges[u].size(); i++)
	{
		int v = edges[u][i];
		
		if (!visited[v])
		{
			if (Explore(v))
				return true;
		}
		else 
			if (finish_time[v] == -1)
				return true;			
	}
	
	finish_time[u] = time_cnt++;
	
	return false;
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
	start_time.resize(n,-1);
	finish_time.resize(n,-1);
	time_cnt = 0;
		
	for (int v = 0; v < n; v++)
	{		
		if (!visited[v])		
			if (Explore(v))
			{
				std::cout << "1";
				return 0;
				//break;
			}	
	}
	
	std::cout << "0";
	
	/*
	std::cout << std::endl;
	for (int v = 0; v < n; v++)
	{
		if (start_time[v] != -1)
		{
			std::cout << v << ":"
				<< " start_time = " << start_time[v]
				<< " finish_time = " << finish_time[v]
				<< std::endl;
		}
	}
	*/
		
	return 0;
}
