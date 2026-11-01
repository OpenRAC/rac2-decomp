/* functional: medium. Written from the assembly: the display-list packets are built word by word instead of with quadword and doubleword copies (the same bytes); the template and index tables at the 0x2A79xx-0x2A7Dxx addresses and the three templates in the data region are read as retail's data. */

extern char *D_L04_001B2C48;                /* the display-list cursor */
extern char D_L04_002A7D40[];               /* 5-quad template */
extern char D_L04_001AD8A0[];               /* 1-quad template */
extern char D_L04_002A7A40[];               /* 23-quad block */
extern char D_L04_001AD8C0[];               /* 1-quad template */
extern short D_L04_002A7920[46];            /* offsets of the words picked from scratch + 0x1088 */
extern char D_L04_001AD8E0[];               /* 1-quad template */
extern short D_L04_002A79E0[46];            /* 23 pairs of offsets of 3-word groups from scratch + 0x2000 */
extern short D_L04_002A7980[46];            /* offsets of the doublewords picked from scratch + 0x780 */

#define SCRATCH_0032F994 ((char *)0x70000000)

static void copy_0032F994(char *dst, char *src, int bytes)
{
    int i;

    for (i = 0; i < bytes; i += 4) {
        *(int *)(dst + i) = *(int *)(src + i);
    }
}

/* Builds two display-list packets at the cursor (D_L04_001B2C48) out of fixed templates and
   values picked from the scratchpad tables indexed by `value`; the first carries `mode` in a
   control word, the second picks doublewords and ends with a call tag back to the first one's
   second block. Both packets' leading tag words get their quadword count ORed in. The cursor is
   left after the call tag. */
void func_L04_0032F994(int mode, int value)
{
    char *start = D_L04_001B2C48;
    char *at = start;
    char *callee;
    char *base;
    int k;

    copy_0032F994(at, D_L04_002A7D40, 80);
    at += 80;
    copy_0032F994(at, D_L04_001AD8A0, 16);
    at += 16;
    copy_0032F994(at, D_L04_002A7A40, 368);
    at += 368;
    callee = at;
    copy_0032F994(at, D_L04_001AD8C0, 16);
    at += 16;
    base = SCRATCH_0032F994 + 0x1088 + value * 4;
    for (k = 0; k < 46; k++) {
        *(int *)at = *(int *)(base + D_L04_002A7920[k]);
        at += 4;
    }
    *(int *)at = 0;
    *(int *)(at + 4) = 0;
    at += 8;
    copy_0032F994(at, D_L04_001AD8E0, 16);
    at += 16;
    base = SCRATCH_0032F994 + 0x2000 + value * 12;
    for (k = 0; k < 23; k++) {
        copy_0032F994(at, base + D_L04_002A79E0[k * 2], 12);
        copy_0032F994(at + 12, base + D_L04_002A79E0[k * 2 + 1], 12);
        at += 24;
    }
    *(int *)(at + 0) = 0x14000000 | mode;
    *(int *)(at + 4) = 0;
    *(int *)(at + 8) = 0;
    *(int *)(at + 12) = 0;
    *(int *)(at + 16) = 0;
    *(int *)(at + 20) = 0x11000000;
    at += 24;
    *(unsigned int *)start |= (unsigned int)(at - start) / 16 - 1;
    D_L04_001B2C48 = at;
    start = at;

    copy_0032F994(at, D_L04_002A7D40, 80);
    at += 80;
    *(int *)(at - 60) |= 0x01000000;
    *(int *)(at - 40) |= 0x01000000;
    copy_0032F994(at, D_L04_001AD8A0, 16);
    at += 16;
    base = SCRATCH_0032F994 + 0x780 + value * 8;
    for (k = 0; k < 46; k++) {
        copy_0032F994(at, base + D_L04_002A7980[k], 8);
        at += 8;
    }
    *(unsigned int *)start |= (unsigned int)(at - start) / 16 - 1;
    D_L04_001B2C48 = at;
    start = at;

    *(int *)(start + 8) = 0;
    *(int *)(start + 12) = 0;
    *(char **)(start + 4) = callee;
    *(int *)start = 0x30000031;
    start += 16;
    D_L04_001B2C48 = start;
}
