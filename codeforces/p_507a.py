# -*- coding: utf-8 -*-
"""
Created on Sat Nov 21 16:38:19 2015

@author: Mary
"""

from operator import itemgetter

n, k = map(int, input().split())
    
lst_a = list(zip(range(1,n+1), (map(int, input().split()))))

lst_a_sorted = sorted(lst_a, key=itemgetter(1))

res_a = []
sum_res_a = 0

for tuple_idx_a in lst_a_sorted:

    if sum_res_a + tuple_idx_a[1] <= k:
        res_a.append(tuple_idx_a[0])
        sum_res_a += tuple_idx_a[1]
    else:
        break

print(len(res_a))
print(' '.join([str(x) for x in res_a]))