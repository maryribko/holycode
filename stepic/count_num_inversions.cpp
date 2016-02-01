#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

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

long long
count_num_inversions_in_block (std::vector<int> &A, int start_idx, int block_len)
{
	long long num_invs = 0;
	
	std::vector<int> sorted;
	sorted.reserve(2*block_len);
	
	int idx_1 = start_idx;
	int idx_2 = start_idx + block_len;	
	
	while ((idx_1 < start_idx + block_len) && (idx_2 < start_idx + 2 * block_len))
	{
		if (A[idx_1] <= A[idx_2])
		{
			sorted.push_back(A[idx_1]);
			idx_1++;
		}
		else
		{
			sorted.push_back(A[idx_2]);
			idx_2++;
			num_invs += start_idx + block_len - idx_1;
		}
	}
	
	while (idx_1 < start_idx + block_len)
	{
		sorted.push_back(A[idx_1]);
		idx_1++;
	}
	
	while (idx_2 < start_idx + 2 * block_len)
	{
		sorted.push_back(A[idx_2]);
		idx_2++;
	}
	
	/*std::cout << "start_idx = " << start_idx 
	<< ", block_len = " << block_len 
	<< ", num_invs = " << num_invs << std::endl;
    for (int i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
    std::cout << std::endl;*/
    
	std::copy (sorted.begin(), sorted.end(), A.begin()+start_idx);
	
	return num_invs;		
}

long long
count_num_inversions (std::vector<int> &A)
{		
	long long num_invs = 0;
	
	for (int block_len = 1; block_len < A.size(); block_len *= 2)	
		for (int start_idx = 0; start_idx < A.size(); start_idx += 2*block_len)
			num_invs += count_num_inversions_in_block (A, start_idx, block_len);	
	
	return num_invs;
}

int main ()
{
	int n;
	std::cin >> n;
	
	int n_ext = pow (2, up2power(n));
	
	std::vector<int> A(n_ext,0);
	
	for (int i = n_ext-n; i < n_ext; i++)
		std::cin >> A[i];    
		
	long long num_invs = count_num_inversions (A);	
	
	std::cout << std::endl << num_invs << std::endl;	
	
	/*for (int i = 0; i < n_ext; i++)
		std::cout << A[i] << " ";
    std::cout << std::endl;*/
	
	return 0;
}


int main ()
{
	int n;
	std::cin >> n;

	std::vector<int> A(n);
	
	for (int i = 0; i < n; i++)
		std::cin >> A[i];    
		
	int num_invs = 0;	
	
	for (int i = 0; i < n-1; i++)
		for (int j = i+1; j < n; j++)
			if (B[i] > B[j])
				num_inv_real++;
	
	std::cout << num_invs;						
	
	return 0;
}



/*#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

int RandomNumber () { return (std::rand()%100); }

int main ()
{
    std::srand ( unsigned ( std::time(0) ) );    

    for (int n = 1; n < 100; n++)
    {
		int n_ext = pow (2, up2power(n));
		
		for (int it = 1; it < 1000; it++)
		{
			int num_inv_my = 0;
			int num_inv_real = 0;   
			
			std::vector<int> A(n_ext,0), B(n);			
			std::generate (B.begin(), B.end(), RandomNumber);
			
			for (int i = n_ext-n; i < n_ext; i++)
				A[i] = B[i-(n_ext-n)];                      
	
			num_inv_my = count_num_inversions(A);
					
			for (int i = 0; i < n-1; i++)
				for (int j = i+1; j < n; j++)
					if (B[i] > B[j])
						num_inv_real++;
        
			if (num_inv_my != num_inv_real)
			{
				std::cout << "A sorted: " << std::endl;
				for (int i = 0; i < n_ext; i++)
					std::cout << A[i] << " ";
				std::cout << std::endl;
			
				std::cout << "A was: " << std::endl;
				for (int i = 0; i < n; i++)
					std::cout << B[i] << " ";
				std::cout << std::endl;
		
				std::cout << "num_inv_my = " << num_inv_my
				<< ", num_inv_real = " << num_inv_real << std::endl;
				return 0;
			}
		}
	}
	
    return 0;
}*/
