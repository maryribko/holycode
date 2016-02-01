#include <iostream>

int main()
{
  int n1, n2, k1, k2;
  std::cin >> n1 >> n2 >> k1 >> k2;

  if (n1 > n2)
    std::cout << "First";
  else
    std::cout << "Second";

  return 0;
}