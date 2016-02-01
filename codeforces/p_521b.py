# -*- coding: utf-8 -*-
"""
Created on Fri Dec 18 15:18:39 2015

@author: Mary
"""

input_file = ''
#input_file = 'test.txt'

def get_max_min_stabset (get_max):

    res_coords = (-1,-1)

    if get_max:
        max_val = -1
    
        for coords in stabset:
            if cubes[coords] > max_val:
                max_val = cubes[coords]
                res_coords = coords
    else:
        min_val = m
    
        for coords in stabset:
            if cubes[coords] < min_val:
                min_val = cubes[coords]
                res_coords = coords

    return res_coords

def has_one_more_below (coords_below, coords_up):
    
    if cubes.get(coords_up) is None:
        return True

    x_b, y_b = coords_below
    x_u, y_u = coords_up

    coords_b1 = (x_u-1, y_u-1)
    coords_b2 = (x_u  , y_u-1)
    coords_b3 = (x_u+1, y_u-1)

    res = False
    res |= (coords_b1 != coords_below) and (cubes.get(coords_b1) is not None)
    res |= (coords_b2 != coords_below) and (cubes.get(coords_b2) is not None)
    res |= (coords_b3 != coords_below) and (cubes.get(coords_b3) is not None)

    return res

def add2stabset(coords):
    
    x, y = coords

    added = False

    if cubes.get((x,y)) is not None and \
       has_one_more_below (coords, (x-1,y+1)) and \
       has_one_more_below (coords, (x  ,y+1)) and \
       has_one_more_below (coords, (x+1,y+1)):
        stabset.add(coords)
        added = True
    
    return added

def update_stabset_item(coords):
    
    if coords in stabset and not add2stabset(coords):
        stabset.remove(coords)        

def update_stabset(coords2pop):

    x, y = coords2pop

    add2stabset((x-1,y-1))
    add2stabset((x  ,y-1))
    add2stabset((x+1,y-1))
    
    update_stabset_item((x+1,y))
    update_stabset_item((x+2,y))
    update_stabset_item((x-1,y))
    update_stabset_item((x-2,y))

if input_file:
    f = open(input_file, 'r')
    m = int(f.readline())
else:
    m = int(input())

cubes = {}

for i in range(m):

    if input_file:
        x, y = map(int, f.readline().strip().split())
    else:
        x, y = map(int, input().split())

    cubes[(x,y)] = i

stabset = set()

for coords, value in cubes.items():
    add2stabset(coords)

res = []
get_max = True

while stabset:

    coords2pop = get_max_min_stabset(get_max)

    res.append(cubes[coords2pop])

    stabset.remove(coords2pop)
    cubes.pop(coords2pop)
    
    update_stabset(coords2pop)
    
    get_max = not get_max

res_dec = 0

for i in res:
    res_dec += res[i] * pow(m, len(res)-i-1)

print(res_dec % (pow(10,9)+9))