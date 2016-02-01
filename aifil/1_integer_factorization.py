from math import floor
import sys


def find_smallest_gr1_factor(n):

    # Look through all numbers in [2, n ^ 0.5]
    for i in xrange(2, int(floor(pow(n, 0.5))) + 1):
        if n % i == 0:
            return i

    return n


def write_full_factorization(factorization_in_2, n):

    factor1 = factorization_in_2[n-1][0]
    factor2 = factorization_in_2[n-1][1]

    if factor1 == 1:
        sys.stdout.write('%d ' % (factor2))

    else:
        write_full_factorization(factorization_in_2, factor1)
        write_full_factorization(factorization_in_2, factor2)


def main():

    N = int(raw_input())

    # i-th element -- factorization of (i+1) into 2 factors:
    # smallest factor greater then 1 (equal to 1 in case of i = 0)
    # and appropriate second factor
    factorization_in_2 = [[1, 1] for i in xrange(N)]

    for i in xrange(1, N+1):

        # Find smallest factor > 1
        factor1 = find_smallest_gr1_factor(i)

        # Find second factor
        factor2 = i / factor1

        # 1 is always at first place
        if factor2 == 1:
            factor1, factor2 = factor2, factor1

        # Write info in factorization_in_2
        factorization_in_2[i-1][0] = factor1
        factorization_in_2[i-1][1] = factor2

        # Write result
        write_full_factorization(factorization_in_2, i)
        sys.stdout.write('\n')

if __name__ == "__main__":
    main()
