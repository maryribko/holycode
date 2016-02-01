#include <iostream>

int main ()
{
    int n, m;
    std::cin >> n >> m;


    bool is_snake_at_first = false;

    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < m; j++)
                std::cout << "#";
            std::cout << "\n";
        }
        else
        {
            if (is_snake_at_first)
                std::cout << "#";
            else
                std::cout << ".";

            for (int j = 1; j < m-1; j++)
                std::cout << ".";

            if (!is_snake_at_first)
                std::cout << "#";
            else
                std::cout << ".";

            std::cout << "\n";

            is_snake_at_first = !is_snake_at_first;
        }
    }

    return 0;
}
