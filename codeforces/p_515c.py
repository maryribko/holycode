# -*- coding: utf-8 -*-
"""
Created on Tue Jun 30 18:49:08 2015

@author: l.maria
"""

n = input()

l1 = map(int,raw_input())

l2 = []
   
for digit in l1:
    
    if digit == 4:
        
        l2.extend([2,2,3])
        
    elif digit == 6:
            
        l2.extend([3,5])
        
    elif digit == 8:
            
        l2.extend([2,2,2,7])
        
    elif digit == 9:
            
        l2.extend([2,3,3,7])

    else:

        l2.append(digit)
        
l2.sort(reverse=True)

print ''.join([str(x) for x in l2 if x > 1])