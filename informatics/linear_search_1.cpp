#include <fstream>
#include <iostream>
#include <vector>

int main()
{
	int array_size;
	int search_num;
	std::vector<int> array;
	
	// Read everything
	std::ifstream input_file ("input.txt");
	if (input_file.is_open())
	{
		input_file >> array_size;
		
		if (array_size <= 0)
		{
			std::cout << "Whyyyyyy? Why you want to give me array with nonpositive size?\n";
			return 1;
		}
		
		array.resize(array_size);
		
		for (auto &array_elem: array)
			input_file >> array_elem;
			
		input_file >> search_num;
		
		input_file.close();				
	}
	else
	{
		std::cout << "Can't open input.txt\n";
		return 1;
	}
	
	int search_num_counter = 0;
	// Count search_num
	for (auto &array_elem: array)
		search_num_counter += array_elem == search_num;
	
	// Write answer
	std::ofstream output_file ("output.txt");
	if (output_file.is_open())
	{
		output_file << search_num_counter;
		output_file.close();
	}
	else
	{
		std::cout << "Can't open output.txt\n";
		return 1;
	}
	
	return 0;
}


