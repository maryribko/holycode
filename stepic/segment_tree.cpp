#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define MAX_VALUE 1e+9

class SegmentTree
{
public:
	void fillTree (int n);
	void set (int i, int x);
	void getMin (int l, int r);
	
private:
	void updateUp(int idx);
	int getMinRec (int l, int r, int l_s, int r_s, int idx);
	
	int n_p2;
	int max_depth;
	int leaves_shift;
	std::vector<int> min_values;	
};

int up2power(int _n)
{
	int power = 0;
	int n = _n;
	
	while (n != 0)
	{
		n = n >> 1;
		power++;
	}
		
	if (pow(2,power-1) == _n)
		power--;
		
	return power;
}

void
SegmentTree::fillTree (int n)
{
	// find min_values size
	max_depth = up2power(n);
	n_p2 = pow(2,max_depth);	
	
	// initialize min_values
	min_values.resize(pow(2,max_depth+1)-1);
	
	for (int i = 0; i < min_values.size(); i++)
		min_values[i] = MAX_VALUE;
	
	// fill leaves
	leaves_shift = pow(2,max_depth)-1;
	for (int i = 0; i < n; i++)
		std::cin >> min_values[leaves_shift+i];
		
	// compute mins
	for (int depth = max_depth-1; depth >= 0; depth--)
	{
		int shift = pow(2,depth)-1;		
		
		for (int i = 0; i < pow(2,depth); i++)
		{
			int idx = shift + i;
			min_values[idx] = std::min (min_values[2*idx+1], min_values[2*idx+2]);
		}		
	}	
}

void
SegmentTree::updateUp (int idx)
{	
	if (idx < 0)
		return;
		
	int min = std::min (min_values[2*idx+1], min_values[2*idx+2]);
	
	if (min != min_values[idx])
	{
		min_values[idx] = min;
		updateUp(floor((idx-1)/2.0f));
	}
}
 
void 
SegmentTree::set (int i, int x)
{	
	int idx = leaves_shift+i;
	min_values[idx] = x;
	
	updateUp(floor((idx-1)/2.0f));
	
	/*for (int j = 0; j < min_values.size(); j++)
		std::cout << min_values[j] << " ";
		
	std::cout << std::endl;*/
}

int
SegmentTree::getMinRec (int l, int r, int l_s, int r_s, int idx)
{
	if (l == l_s && r == r_s)
		return min_values[idx];
		
	int mid = ceil ((l_s + r_s) / 2.0f);
	
	int l_s1 = l_s;
	int r_s1 = mid - 1;
	int l_s2 = mid;
	int r_s2 = r_s;
	
	if (r < mid)
		return getMinRec(l,r,l_s1,r_s1, 2*idx+1);
		
	if (l >= mid)
		return getMinRec(l,r,l_s2,r_s2, 2*idx+2);
		
	int min1 = getMinRec(l,mid-1,l_s1,r_s1, 2*idx+1);
	int min2 = getMinRec(mid,r,l_s2,r_s2, 2*idx+2);
	
	return std::min (min1, min2);
}

void
SegmentTree::getMin (int l, int r)
{		
	int res = getMinRec (l, r, 0, n_p2-1, 0);
	
	std::cout << res << std::endl;
}

int main()
{	
	int n, m;
	std::cin >> n >> m;
	
	SegmentTree stree;
	stree.fillTree(n);
	
	for (int i = 0; i < m; i++)
	{
		std::string command;
		std::cin >> command;
		
		if (command == "Set")
		{
			int i, x;
			std::cin >> i >> x;
			stree.set(i-1,x);
		}
		else
		{
			int l, r;
			std::cin >> l >> r;
			stree.getMin(l-1, r-1);
		}
	}
	
	return 0;	
}
