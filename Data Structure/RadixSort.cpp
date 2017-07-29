
namespace RadixSort{
    const int NMAX = 100000;
    const int Width = 32, CHUNK = 8;
    const int bitmask = (1 << CHUNK) - 1;

    unsigned int bucket[1 << CHUNK], temp[NMAX + 10];
    void sort(unsigned int* ar, int n)
    {
        int i, j, x;
        for (i = 0; i < Width; i += CHUNK) {
            clr(bucket);
            for (j = 0; j < n; j++) bucket[(ar[j] >> i) & bitmask]++;
            for (j = 1; j <= bitmask; j++) {
                bucket[j] += bucket[j - 1];
            }
            for (j = n - 1; j >= 0; j--) temp[--bucket[(ar[j] >> i) & bitmask]] = ar[j];
            for (j = 0; j < n; j++) ar[j] = temp[j];
        }
    }
};
