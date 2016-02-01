#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int field_size = 9;
const int square_size = 3;

void set_next_idx_row (int & i, int & j)
{
	if (j < field_size-1)
		j++;
	else
	{
		j = 0;
		i++;
	}
}

void set_next_idx_column (int & i, int & j)
{
	if (i < field_size-1)
		i++;
	else
	{
		i = 0;
		j++;
	}
}
	
void set_next_idx_square (int & i, int & j)
{       
    int block_i    = i / square_size;
    int block_j    = j / square_size;
    int in_block_i = i % square_size;
    int in_block_j = j % square_size;
    
    if (in_block_j < 2)
        in_block_j += 1;
        
    else
    {
        if (in_block_i < 2)
        {
            in_block_j = 0;
            in_block_i += 1;
        }
        else
        {
            in_block_j = 0;
            in_block_i = 0;
            
            if (block_j < 2)
                block_j += 1;
                
            else
            {
                block_j = 0;
                block_i += 1;
			}
		}
    }
                
    i = block_i * 3 + in_block_i;
    j = block_j * 3 + in_block_j;  
}
    
void set_next_idx (const std::string & check_block_type, int & i, int & j)
{
	if (check_block_type == "row")
		set_next_idx_row (i,j);
	
	else if (check_block_type == "column")
		set_next_idx_column (i,j);

	else if (check_block_type == "square")
		set_next_idx_square (i,j);
}

bool is_sudoku_valid (const std::vector<std::vector<int> > & field,
					  const std::string & check_block_type)
{	
	int i = 0;
	int j = 0;

	for (int idx1 = 0; idx1 < field_size; idx1++)
	{
		// Vector with 1 for numbers that are in block 
		std::vector<int> numbers(field_size, 0);

		for (int idx2 = 0; idx2 < field_size; idx2++)
		{
			// Mark number
			numbers[field[i][j]-1] = 1;
			
			// Move to next
			set_next_idx (check_block_type, i, j);
		}

		// Check if all possible numbers are in check block
		if (!std::all_of (numbers.begin(), numbers.end(), [](int x){return x;}))
			return false;
	}
	
	return true;
}

int main()
{
	// Field with sudoku
	std::vector<std::vector<int> > field (field_size, std::vector<int>(field_size));

	// Fill field from standart input
	for (auto & raw: field)
		for (auto & element: raw)
			std::cin >> element;

	// Check through each type of block
	bool valid = true;
			
	valid &= is_sudoku_valid (field, "row");
	valid &= is_sudoku_valid (field, "column");
	valid &= is_sudoku_valid (field, "square");
	
	// Print result
	if (valid)
		std::cout << "Sudoku is valid\n";
	else
		std::cout << "Sudoku is invalid\n";
		
	return 0;
}
