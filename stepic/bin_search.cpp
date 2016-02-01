#include <iostream>
#include <vector>

int main()
{
	int n;
	std::cin >> n;
	
	std::vector<int> search_in_array(n);
	
	for (int i = 0; i < search_in_array.size(); i++)
		std::cin >> search_in_array[i];
		
	int k;
	std::cin >> k;
	
	for (int i = 0; i < k; i++)
	{
		int search_num;
		std::cin >> search_num;
		
		int l = 0;
		int r = n-1;
		
		while (l!=r)
		{
			int mid = (l + r) / 2;
			
			if (search_in_array[mid] >= search_num)
				r = mid;
			else
				l = mid+1;			
		}
		
		if (search_in_array[r] == search_num)
			std::cout << r+1 << " ";
		else
			std::cout << "-1 ";
	}	
}
