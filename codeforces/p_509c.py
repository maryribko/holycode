# -*- coding: utf-8 -*-
"""
Created on Mon Nov 30 12:04:02 2015

@author: Mary
"""
n = int(input())
prev_b = 0
r = [0] * 500

for _ in range(n):

    b = int(input())
    
    if b > prev_b:        
        delta = b - prev_b
        i = 0

        while delta > 0:
            if r[i] < 9:
                delta_i = min(delta, 9 - r[i])
                r[i] += delta_i
                delta -= delta_i
            i += 1
    else:
        max_i = -1
        s = 0
        
        while s < prev_b:
            max_i += 1
            s += r[max_i]

        max_i += 1
        sum_ge_max_i = 0

        i = max_i        
        s = 0

        while b > s + r[i-1]:
            
            s += r[i-1]
            i -= 1
            
            if r[i] < 9:
                max_i = i
                sum_ge_max_i = s
        
        r[max_i] += 1
        sum_ge_max_i += 1

        delta = b - sum_ge_max_i 
        
        for i in range(max_i):
            if delta > 0:
                delta_i = min(delta, 9)
                r[i] = delta_i
                delta -= delta_i
            else:
                r[i] = 0
                
    res = ''.join(map(str, reversed(r)))
    print(res.lstrip('0'))
    
    prev_b = b
    
#digs, a, le = [0] * 333, 0, 0
#
#for _ in range(int(input())):
#    
#    b = int(input())
#    
#    delta, a = b - a, b
#    
#    for i, d in enumerate(digs):
#
#        if d < 9 and 0 < delta <= 9 * i + 9 - d:
#            break
#        delta += d
#        digs[i] = 0
#
#    digs[i] += 1
#    le = max(le, i)
#    i, delta = divmod(delta - 1, 9)
#    digs[:i] = [9] * i
#    digs[i] += delta
#  
#    print(''.join(map(str, digs[le::-1])))