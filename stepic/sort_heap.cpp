#include <iostream>
#include <vector>
#include <math.h>

class HeapSort
{
public:
	void sort (std::vector<int> &A);	
	
private:    
	void buildMaxHeap (std::vector<int> &A);
	void siftDown (std::vector<int> &A, int size, int idx);
    void swap (std::vector<int> &A, int idx_1, int idx_2);
};

void
HeapSort::swap (std::vector<int> &A, int idx_1, int idx_2)
{
    int tmp = A[idx_1];
    A[idx_1] = A[idx_2];
    A[idx_2] = tmp;
}

void
HeapSort::sort (std::vector<int> &A)
{
    buildMaxHeap (A);   

    int heap_size = A.size();

    for (int i = A.size()-1; i > 0; i--)
    {
        swap (A, i, 0);
        heap_size--;
        siftDown(A, heap_size, 0);
    }
}

void 
HeapSort::buildMaxHeap (std::vector<int> &A)
{
    int n = A.size();

    for (int i = floor(n/2.0f)-1; i >= 0; i--)   
        siftDown (A, n, i);
}

void 
HeapSort::siftDown (std::vector<int> &A, int size, int idx)
{
	int child_idx_1 = 2 * idx + 1;
	int child_idx_2 = 2 * idx + 2;

    int swap_idx = -1;
	
    if (child_idx_1 < size && A[idx] < A[child_idx_1])
        swap_idx = child_idx_1;

    if (child_idx_2 < size && A[idx] < A[child_idx_2])
        if (A[child_idx_1] < A[child_idx_2])
            swap_idx = child_idx_2;

    if (swap_idx != -1)
    {
        swap(A, idx, swap_idx);
        siftDown (A, size, swap_idx);
    }
}

int main ()
{
    int n;
    std::cin >> n;
	
    std::vector<int> A(n);
    for (int i = 0; i < n; i++)
        std::cin >> A[i];

    HeapSort hs;
    hs.sort(A);

    std::cout << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << A[i] << " ";
    std::cout << std::endl;

    return 0;
}


//#include <algorithm>
//#include <ctime>        // std::time
//#include <cstdlib>      // std::rand, std::srand

//int RandomNumber () { return (std::rand()%100); }

//int main ()
//{
//    std::srand ( unsigned ( std::time(0) ) );

//    int n = 10;
//    std::vector<int> A(n), B(n), C(n);

//    HeapSort hs;

//    while (true)
//    {
//        std::generate (A.begin(), A.end(), RandomNumber);
//        std::copy (A.begin(), A.end(), B.begin());
//        std::copy (A.begin(), A.end(), C.begin());

//        hs.sort(A);
//        std::sort (B.begin(), B.end());

//        if (!std::equal (A.begin(), A.end(), B.begin()))
//            break;
//    }

//    std::cout << std::endl;
//    for (int i = 0; i < n; i++)
//        std::cout << C[i] << " ";
//    std::cout << std::endl;

//    return 0;
//}
