# -*- coding: utf-8 -*-
"""
Created on Fri Jul  3 15:27:59 2015

@author: l.maria
"""

# Problem A: reverse number
print raw_input().strip('0')[-1::-1]

# Problem C: My father has more money
print '9'*100 + '1'

# Problem D: counting poem
print zip(raw_input().strip('\n').split(), raw_input().strip('\n').split() * 34)[-1][1]