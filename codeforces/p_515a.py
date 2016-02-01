# -*- coding: utf-8 -*-
"""
Created on Tue Jun 30 16:15:41 2015

@author: l.maria
"""

a, b, s = [abs(int(x)) for x in raw_input().split()]

if (a + b <= s) and ((s - a - b) % 2 == 0):    
    print 'Yes'    
else:    
    print 'No'
        