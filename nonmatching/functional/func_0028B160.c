/* functional: medium. Starts from the near-miss draft; same reads, writes and calls in retail order; byte differences are register allocation only. */
/* Best retained candidate: 280 bytes versus 292; 0/28 in us, pal and us2. */
extern int *D_001B1888;
extern unsigned int *D_001B1894;
extern int D_001A7308;
extern void func_0028AE88(int);
extern void func_0028F948(int, int, int, int, int, int);

void func_0028B160(int index, int unused, int param_2)
{
    int offset;
    int first;
    int last;
    int i;

    if (D_001B1888[index + 0x74 / 4] == 0)
        func_0028AE88(0);

    offset = D_001A7308;
    first = 0;
    if (index != 0)
        first = D_001B1888[index + 0x34 / 4 - 1];
    last = D_001B1888[index + 0x34 / 4];

    i = first;
    while (i < last) {
        int row_offset = i << 3;
        unsigned char *row =
            (unsigned char *)((unsigned int)D_001B1894 + row_offset);
        unsigned char width = row[6];
        unsigned char height = row[7];
        int position = offset >> 8;
        int mask = 1 << (width + height);

        i++;
        func_0028F948(*(int *)row, position, 0x1B,
                width, height, param_2);
        offset += mask << 2;
        *(short *)((unsigned int)D_001B1894 + row_offset + 4) = position;
    }
}
