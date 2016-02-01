#include <iostream>
#include <vector>
#include <map>

long long
gcd (long long a, long long b )
{
  long long c;
  while ( a != 0 )
  {
     c = a;
     a = b%a;
     b = c;
  }
  return b;
}

int main ()
{
    int n;
    std::cin >> n;

    std::vector<long long> lengths(n), costs(n);

    for (long long & length: lengths)
        std::cin >> length;

    for (long long & cost: costs)
        std::cin >> cost;

    std::map<long long,long long> lc_map;

    for (int i = 0; i < n; i++)
    {
        for (auto & map_el: lc_map)
        {
            long long new_length = gcd(lengths[i], map_el.first);
            long long cost = costs[i] + map_el.second;

            if (lc_map[new_length] == 0 || lc_map[new_length] > cost)
                lc_map[new_length] = cost;
        }

        if (lc_map[lengths[i]] == 0 || lc_map[lengths[i]] > costs[i])
            lc_map[lengths[i]] = costs[i];
    }

    if (lc_map[1] > 0)
        std::cout << lc_map[1];
    else
        std::cout << -1;

    return 0;
}
