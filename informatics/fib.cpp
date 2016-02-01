#include <iostream>
#include <new>

long long Fib2(int n)
{
    if (n < 2)
        return n;

    long long * fib_all = new long long[n+1];
    fib_all[0] = 0;
    fib_all[1] = 1;

    for (int i = 2; i <= n; i++)
        fib_all[i] = fib_all[i-1] + fib_all[i-2];

    delete[] fib_all;

    return fib_all[n];
}

int main() {

  int n;
  std::cin >> n;

  std::cout << Fib2(n) << std::endl;

  return 0;
}
