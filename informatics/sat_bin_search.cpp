#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int
countNumGroups (std::vector<long long> &heights, 
				long long dif_height, 
				long long num_groups, 
				long long num_2group)
{
	long long start = 0;	
	long long end = 0;
	long long gr_counter = 0;

	int delta = (num_2group > 1) ? 1 : 0;
	
	while (end < heights.size()-1)
	{		
		if (heights[end+delta] - heights[start] > dif_height)
		{
			start++;
			continue;
		}
		else
		{
			end += delta;
		}
		
		if (end-start+1 == num_2group)
		{
			gr_counter++;
			start = end + 1;
			end = start;
		}
	}
	return gr_counter;
}


int main()
{	
	// Open files
	std::ifstream input_file ("input.txt");
	if (!input_file.is_open())
	{
		std::cout << "Can't open input.txt\n";
		return 1;
	}
	
	std::ofstream output_file ("output.txt");
	if (!output_file.is_open())
	{
		std::cout << "Can't open output.txt\n";
		return 1;
	}

	long long num_slaves, num_groups, num_slaves2group;			
	input_file >> num_slaves >> num_groups >> num_slaves2group;
	
	std::vector<long long> heights(num_slaves);
	for (auto &height: heights)
		input_file >> height;
	std::sort (heights.begin(), heights.end());
		
	long long l = 0;
	long long r = heights[num_slaves-1] - heights[0];
	long long minmax_dif;	
	
	while (l < r)
	{
		minmax_dif = (l+r)/2;
		
		long long counter = countNumGroups(heights, minmax_dif, num_groups, num_slaves2group);
		
		if (counter >= num_groups)
			r = minmax_dif;
		else
			l = minmax_dif + 1;			
	}	
	
	output_file << r;
	
	input_file.close();
	output_file.close();
	
	return 0;
}
