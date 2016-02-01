# -*- coding: utf-8 -*-
"""
Created on Tue Jun 30 16:42:23 2015

@author: l.maria
"""

from fractions import gcd

n, m = map(int, raw_input().split())

happy_boys_idx = set(map(int, raw_input().split())[1:])

happy_girls_idx = set(map(int, raw_input().split())[1:])

k = gcd(n,m)

all_happy = True

for i in range(k):
    
    all_happy &= bool(set(xrange(i,n,k)) & happy_boys_idx) | bool(set(xrange(i,m,k)) & happy_girls_idx)

if all_happy:
    print 'Yes'
else:
    print 'No'