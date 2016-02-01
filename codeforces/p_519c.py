# -*- coding: utf-8 -*-
"""
Created on Tue Dec  1 15:39:30 2015

@author: Mary
"""

num_pairs = 0

n, m = map(int, input().split())

if n > m:        
    n, m = m, n

while n >= 1 and m >= 2:

    n -= 1
    m -= 2
    num_pairs += 1
    
    if n > m:        
        n, m = m, n
        
print (num_pairs)