#include <iostream>
#include <vector>
#include <string>


class DisjointSet
{
public:
    DisjointSet (int n);
    bool Check (int a, int b);
    void Union (int a, int b);

private:
    int Find (int a);

    std::vector<int> reprs;
};

DisjointSet::DisjointSet (int n)
{
    reprs.resize(n);

    for (int i = 0; i < n; i++)
        reprs[i] = i;
}

int
DisjointSet::Find (int a)
{
    if (reprs[a] != a)
        reprs[a] = Find(reprs[a]);

    return reprs[a];
}

bool
DisjointSet::Check (int a, int b)
{
    int r_a = Find(a);
    int r_b = Find(b);

    return (r_a == r_b);
}

void
DisjointSet::Union (int a, int b)
{
    int r_a = Find(a);
    int r_b = Find(b);

    reprs[r_a] = r_b;
}

int main()
{	
	int n, m;
	std::cin >> n >> m;
	
    DisjointSet dset(n);
	
	for (int i = 0; i < m; i++)
	{
		std::string command;
		std::cin >> command;
		
        if (command == "Check")
		{
            int a, b;
            std::cin >> a >> b;
            bool res = dset.Check(a-1,b-1);
            std::cout << res << std::endl;
		}
		else
		{
            int a, b;
            std::cin >> a >> b;
            dset.Union(a-1,b-1);
		}
	}
	
	return 0;	
}
