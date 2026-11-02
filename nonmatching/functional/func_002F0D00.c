/* functional: high. Plain C; same tests in the same order. */
extern unsigned char *D_001B2170;

/* For each 16-bit index in [first, end): the 64-byte record at D_001B2170 + index * 64 has a 16-bit mask of four nibbles at +54. The lowest nibble equal to `value` is dropped (the nibbles above it move down and the top becomes 0xF); when the mask becomes 0xFFFF the byte at +53 is set to 1. */
void func_002F0D00(void *first, void *end, int value)
{
    unsigned short *p = first, *e = end;
    unsigned char *base = D_001B2170;

    while (p != e) {
        unsigned char *rec = base + (*p++ << 6);
        unsigned int v = *(unsigned short *)(rec + 54);
        unsigned int low;

        if ((int)(v & 0xF) == value) {
            v = (v >> 4) | 0xF000;
        } else if ((int)(v & 0xF0) == (value << 4)) {
            low = v & 0xF;
            v = ((v >> 4) & 0xFF0) | (low | 0xF000);
        } else if ((int)(v & 0xF00) == (value << 8)) {
            low = v & 0xFF;
            v = ((v >> 4) & 0xF00) | (low | 0xF000);
        } else if ((int)(v & 0xF000) == (value << 12)) {
            v = v | 0xF000;
        } else {
            continue;
        }
        *(unsigned short *)(rec + 54) = (unsigned short)v;
        if (v == 0xFFFF) {
            rec[53] = 1;
        }
    }
}
