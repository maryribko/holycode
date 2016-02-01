#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

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
	
	// Read sorted array
	int sorted_array_size, search4_array_size;
	input_file >> sorted_array_size >> search4_array_size;
					
	std::vector<long> array(sorted_array_size);
		
	for (auto &array_elem: array)
		input_file >> array_elem;

	for (int i = 0; i < search4_array_size; i++)
	{
		int search_num;
		input_file >> search_num;
		
		int l = 0;
		int r = sorted_array_size - 1;
		int cur_ind;
		
		while (l < r)
		{
			cur_ind = float((l+r)) / 2;
						
			if (array[cur_ind] < search_num)
				l = cur_ind + 1;
			else
				r = cur_ind;			
		}
		
		long appr_val;
		
		if (l == 0)
		 appr_val = array[0];
		else
		{
			if (std::abs(array[l]-search_num) < std::abs(array[l-1]-search_num)) 		
				appr_val = array[l];
			else
				appr_val = array[l-1];
		}
		output_file << appr_val << std::endl;		 	
	}
	
	input_file.close();	
	output_file.close();
	
	return 0;
}
