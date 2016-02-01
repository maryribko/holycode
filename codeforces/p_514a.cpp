#include <iostream>
#include <cmath>

int main()
{
    long long x;
    std::cin >> x;    
     
    long long inv_x = 0;
    long long t, cur_d = 1;
    bool stop = false;
    
    while (!stop)
    {
        if (x < 10)
            stop = true;
        
        if (x == 9)        
            t = x;
        else
        {
            t = x % 10;
            x /= 10;            
            
            if (9 - t < t)
                t = 9 - t;
        }
        
        inv_x += t * cur_d;
        cur_d *= 10;
    }
    
    std::cout << inv_x;
    return 0;
}