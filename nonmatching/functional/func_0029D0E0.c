/* functional: high. Plain C: the 112-byte packet is built with the same writes in the same order, later ones over earlier, so the overlaps come out as retail's. */
extern unsigned int D_001AC710[20];
extern int D_001B15FC;
extern unsigned int D_001B22A8;
extern unsigned char D_001B9340[];

static void packet_head_0029D0E0(unsigned char *p)
{
    unsigned int *w = (unsigned int *)p;
    int i;

    for (i = 0; i < 16; i++) {
        w[i] = D_001AC710[i];
    }
    for (i = 16; i < 20; i++) {
        w[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        w[20 + i] = D_001AC710[16 + i];
    }
    w[18] = 83;
}

static void packet_tail_0029D0E0(unsigned char *p, unsigned int at, unsigned int size)
{
    unsigned int *w = (unsigned int *)p;
    int i;

    w[20] = size | 0x8000;
    for (i = 24; i < 28; i++) {
        w[i] = 0;
    }
    w[25] = at;
    w[24] = 0x30000000 + size;
    w[27] = 0x50000000 + size;
}

/* Walks D_001B15FC entries of 16 bytes at D_001B9340 (two slots each: word at +0 or +8 non-zero means in use, with a 16-bit size and a 16-bit value after it) and appends one 112-byte packet per used slot at the pointer D_001B22A8, which advances. */
void func_0029D0E0(void)
{
    int count = D_001B15FC;
    unsigned char *out = (unsigned char *)D_001B22A8;
    unsigned char *entry = D_001B9340;

    while (count != 0) {
        unsigned int at, v0, t1, size;

        count--;
        at = *(unsigned int *)(entry + 0);
        v0 = *(unsigned short *)(entry + 4);
        t1 = *(unsigned short *)(entry + 6);
        if (at != 0) {
            packet_head_0029D0E0(out);
            out[39] = (unsigned char)v0;
            v0 >>= 1;
            *(unsigned short *)(out + 36) = (unsigned short)t1;
            *(unsigned int *)(out + 48) = 16;
            *(unsigned int *)(out + 52) = 16;
            size = 64 >> (v0 & 31);
            packet_tail_0029D0E0(out, at, size);
            out += 112;
        }
        at = *(unsigned int *)(entry + 8);
        v0 = *(unsigned short *)(entry + 12);
        if (at != 0) {
            unsigned int lo, a0, a1;

            packet_head_0029D0E0(out);
            t1 = *(unsigned short *)(entry + 14);
            lo = v0 & 0xFF;
            v0 >>= 8;
            *(unsigned short *)(out + 36) = (unsigned short)t1;
            if ((int)(lo - 6) > 0) {
                out[38] = (unsigned char)(1u << ((lo - 6) & 31));
            }
            a0 = 1u << (v0 & 31);
            a1 = 1u << (lo & 31);
            *(unsigned int *)(out + 52) = a0;
            a0 = a0 << (lo & 31);
            *(unsigned int *)(out + 48) = a1;
            size = a0 >> 4;
            packet_tail_0029D0E0(out, at, size);
            out += 112;
        }
        entry += 16;
    }
    D_001B22A8 = (unsigned int)out;
}
