/* functional: high. Plain C; same tests in the same order. */
extern unsigned char *D_001B21B4;

/* For each 16-bit index in [first, end): the 32-byte record at D_001B21B4 + index * 32 has a 16-bit mask of four nibbles at +26. The lowest nibble equal to `value` is dropped (the nibbles above it move down and the top becomes 0xF); when the mask becomes 0xFFFF the byte at +30 gets bit 0 set. */
void func_002F5118(void *first, void *end, int value)
{
    unsigned short *p = first, *e = end;
    unsigned char *base = D_001B21B4;

    while (p != e) {
        unsigned char *rec = base + (*p++ << 5);
        unsigned int v = *(unsigned short *)(rec + 26);
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
        *(unsigned short *)(rec + 26) = (unsigned short)v;
        if (v == 0xFFFF) {
            rec[30] = rec[30] | 1;
        }
    }
}
