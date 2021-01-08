int countBits(int i) {
    int count = 0;
    while (i != 0) {
        count += (i & 1);
        i >>= 1;
    }
    return count;
}