def main():

    # Read "N M" from standart input, N > M,
    # N -- vector size, M -- number of parts
    N, M = map(int, raw_input().split())

    part_len = N / M

    # shift of first part
    shift = N % M / 2

    for i in xrange(M):

        part_begin_idx = i * part_len + shift

        part_end_idx = part_begin_idx + part_len - 1

        print ('part %d: (%d %d)' % (i, part_begin_idx, part_end_idx))

if __name__ == "__main__":
    main()
