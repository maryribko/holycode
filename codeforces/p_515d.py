# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:09:30 2015

@author: l.maria
"""

input_file = 'test.txt'

n = 0
m = 0
num_not_marked = 0

def read_data():
    
    global n, m

    if input_file:
        f = open(input_file, 'r')
        n, m = map(int, f.readline().strip().split())
    else:
        n, m = map(int, input().split())

    field = [[]] * n

    for i in range(n):

        if input_file:
            raw = f.readline().strip()            
        else:
            raw = input()

        field[i] = [s for s in raw]

    return field

def count_neighbours (field):

    global num_not_marked
    num_not_marked = n * m

    num_neibs = [[0]*m for i in range(n)]

    for i in range(n):
        for j in range(m):
    
            if field[i][j] == '*':
                num_not_marked -= 1
                continue

            if j > 0 and field[i][j-1] == '.':
                num_neibs[i][j] += 1
                num_neibs[i][j-1] += 1
                
            if i > 0 and field[i-1][j] == '.':
                num_neibs[i][j] += 1
                num_neibs[i-1][j] += 1

    return num_neibs

def init_stack (num_neibs):

    stack = []

    for i in range(n):
        for j in range(m):  

            if num_neibs[i][j] == 1:
                stack.append((i,j))

    return stack

def mark_cell (stack, field, num_neibs):
    
    i, j = stack.pop()

    if num_neibs[i][j] == 0:
        return
    
    global num_not_marked
    num_not_marked -= 2

    if j > 0 and field[i][j-1] == '.':
        i_n, j_n = i, j-1
        field[i][j] = '>'
        field[i_n][j_n] = '<'

    elif j < m-1 and field[i][j+1] == '.':
        i_n, j_n = i, j+1
        field[i][j] = '<'
        field[i_n][j_n] = '>'

    elif i > 0 and field[i-1][j] == '.':
        i_n, j_n = i-1, j
        field[i][j] = 'v'
        field[i_n][j_n] = '^'

    else:
        i_n, j_n = i+1, j
        field[i][j] = '^'
        field[i_n][j_n] = 'v'
        
    num_neibs[i][j] = 0
    num_neibs[i_n][j_n] = 0
    
    if j_n > 0 and num_neibs[i_n][j_n-1] > 0:
        num_neibs[i_n][j_n-1] -= 1
        if num_neibs[i_n][j_n-1] == 1:
            stack.append((i_n,j_n-1))

    if j_n < m-1 and num_neibs[i_n][j_n+1] > 0:
        num_neibs[i_n][j_n+1] -= 1
        if num_neibs[i_n][j_n+1] == 1:
            stack.append((i_n,j_n+1))

    if i_n > 0 and num_neibs[i_n-1][j_n] > 0:
        num_neibs[i_n-1][j_n] -= 1
        if num_neibs[i_n-1][j_n] == 1:
            stack.append((i_n-1,j_n))

    if i_n < n-1 and num_neibs[i_n+1][j_n] > 0:
        num_neibs[i_n+1][j_n] -= 1
        if num_neibs[i_n+1][j_n] == 1:
            stack.append((i_n+1,j_n))

def main():

    field = read_data()
    num_neibs = count_neighbours(field)
#    stack = init_stack(num_neibs)
#
#    while stack:
#        mark_cell(stack, field, num_neibs)
#    
#    if num_not_marked > 0:
#        print('Not unique')
#    else:
#        print('\n'.join(map(lambda x: ''.join(x), field)))
#        
#if __name__ == '__main__':
#    main()