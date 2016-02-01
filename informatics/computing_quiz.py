# -*- coding: utf-8 -*-
"""
Created on Fri Jul  3 15:06:49 2015

@author: l.maria
"""

# Problem 1
2 ** 179

# Problem 2
reduce(lambda res,x: res*x, range(1,21))

# Problem 3
sum([x*x for x in [179, 971]]) ** 0.5

# Problem 4
sum([4 * (1.0/x - 1.0/(x+2)) for x in range(1,20,4)])

# Problem 5
(sum([1.0 / (x**2) for x in range(1,11)]) * 6) ** 0.5

# Problem 6
'A' * 100

# Problem 7
'Python' * 40

# Problem 25
int('179' * 40) ** 2

# Problem 26
pow(int(str(179 ** 10) * 4), 0.1)