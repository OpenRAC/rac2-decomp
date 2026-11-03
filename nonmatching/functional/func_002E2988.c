/* functional: high. Same reads and writes in the same order; shift counts are masked to 5 bits as sllv does; retail's 128-bit template copies (lq from $gp-0x28E0 = D_001AC710.. then sq) are written as four words each, and the zero quadwords as four zero words. */
extern int D_001B2090;
extern char *D_001B22A8;
extern int D_001B20B0;
extern unsigned int D_001AC710[20];
extern int D_00213F20[];
extern int D_00214020[];
extern unsigned char D_00214520[];
extern unsigned short D_00213B20[];
extern unsigned int D_00213720[];

static void packet_002E2988(unsigned int *q, unsigned int base, unsigned int lv, unsigned int addr, unsigned int *pv)
{
    unsigned int sz, n;
    int i;

    for (i = 0; i < 16; i++) {
        q[i] = D_001AC710[i];
    }
    q[16] = 0;
    q[17] = 0;
    q[18] = 0;
    q[19] = 0;
    for (i = 0; i < 4; i++) {
        q[20 + i] = D_001AC710[16 + i];
    }
    q[18] = 83;
    *(unsigned short *)((char *)q + 36) = base;
    if ((int)(lv - 6) > 0) {
        *((unsigned char *)q + 38) = 1 << ((lv - 6) & 31);
    }
    q[12] = 1 << (lv & 31);
    q[13] = 1 << (lv & 31);
    sz = (1 << (lv & 31)) << (lv & 31);
    n = sz >> 4;
    *pv = sz;
    q[20] = 0x8000 + n;
    q[24] = 0;
    q[25] = 0;
    q[26] = 0;
    q[27] = 0;
    q[25] = addr;
    q[24] = 0x30000000 + n;
    q[27] = 0x50000000 + n;
}

/* Build the texture upload packets for this frame's mip levels: mark, in a 256-byte table at scratchpad 0x70003600, the
   textures each visible entry needs (bit 1: the level below the top; bit 2: also the top level), listing those entries in
   D_00214020 (-1 terminated); then for each marked texture write one or two 112-byte GS upload packets at D_001B22A8 from the
   template at D_001AC710, giving each its VRAM block (from base>>8, halfwords in D_00213B20), until VRAM passes 16379
   blocks. Returns the next free VRAM address (blocks << 8). */
int func_002E2988(unsigned int base)
{
    unsigned char *mask = (unsigned char *)0x70003600;
    int *dist = (int *)0x70003100;
    int *lim = D_00213F20;
    int *list = D_00214020;
    unsigned char *tex = D_00214520;
    unsigned int t9 = base >> 8;
    unsigned int *pk = (unsigned int *)D_001B22A8;
    int count = D_001B2090;
    int i = 0;
    unsigned short *slot;
    unsigned int *src;
    unsigned char *m, *mend;

    for (m = mask; m != mask + 256; m += 16) {
        int k;
        for (k = 0; k < 16; k++) {
            m[k] = 0;
        }
    }

    while (i != count) {
        int d, l;
        unsigned char *b;
        unsigned int flag;

        i++;
        d = *dist++;
        l = *lim++;
        tex += 16;
        if (d == 0x7FFFFFFF) {
            continue;
        }
        *list = i - 1;
        if (l * 2 - d <= 0) {
            continue;
        }
        flag = (l - d > 0) ? 3 : 1;
        list++;
        for (b = tex - 16; *b != 255; b++) {
            mask[*b] |= flag;
        }
    }
    *list = -1;

    slot = D_00213B20;
    src = D_00213720;
    m = mask;
    mend = mask + D_001B20B0;
    while (m != mend) {
        unsigned int f = *m++;
        unsigned int a = *src++;
        unsigned int lv, addr, sz;

        *(unsigned int *)slot = 0;
        slot += 2;
        if (f == 0) {
            continue;
        }
        lv = a >> 28;
        addr = (a << 4) >> 4;
        if (f & 2) {
            packet_002E2988(pk, t9, lv, addr, &sz);
            slot[-2] = t9;
            t9 += sz >> 8;
            pk += 28;
            if ((int)(t9 - 16379) > 0) {
                pk -= 28;
                break;
            }
        }
        lv = lv - 1;
        {
            unsigned int s2 = (1 << (lv & 31)) << (lv & 31);
            packet_002E2988(pk, t9, lv, addr + (s2 << 2), &sz);
        }
        slot[-1] = t9;
        t9 += sz >> 8;
        pk += 28;
        if ((int)(t9 - 16379) > 0) {
            pk -= 28;
            break;
        }
    }
    D_001B22A8 = (char *)pk;
    return t9 << 8;
}
