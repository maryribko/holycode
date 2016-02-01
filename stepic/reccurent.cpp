#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    int n;
    std::cin >> n;

    std::vector<int> A(n);

    for (int i = 0; i < n; i++)
        std::cin >> A[i];

    std::nth_element (A.begin(), A.begin()+(n/2), A.end());
    int count = std::count (A.begin(), A.end(), *(A.begin()+(n/2)));

    if (count > float(n)/2)
        std::cout << "1";
    else
        std::cout << "0";

    return 0;
}
