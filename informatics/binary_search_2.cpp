#include <fstream>
#include <iostream>
#include <algorithm>

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
	long num_dipl, width, height;
	input_file >> width >> height >> num_dipl;
					
	
	int l = 0;
	int r = num_dipl * std::max(width,height);
	
	int cur_n;
		
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
	
	input_file.close();	
	output_file.close();
	
	return 0;
}
