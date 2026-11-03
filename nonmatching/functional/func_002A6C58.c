/* functional: medium. Written from the assembly: same reads, writes and calls with the same arguments in the same order; retail's divide-by-zero traps (div by 50, by 2*count and by the weight sum) are dropped, and the two-slot search is a plain loop. Unrun blocks (the D_001A9E70 slot path, the weighted split, the 10x value, the 2.0 spread) read against retail. */
extern char D_00189E20[];          /* the player/global block: +0x80, +0x2294, +0x22B4, +0x22C2 */
extern char D_00139868[];          /* 56 int counters */
extern char D_00188610[];          /* int per D_001A9E70 slot */
extern char D_0019B2E8[];          /* byte flags, [index + D_001A79F0 * 16] */
extern char D_0019B4A8[];          /* nibble pairs, [(id >> 1) + D_001A79F0 * 1024] */
extern int D_001A79F0;             /* also read as gp-0x7600 */
extern int D_001A7A0C;
extern int D_001A7A10;
extern int D_001A7A14;
extern unsigned char D_001A7A32;
extern char D_001A8678[], D_001A8680[], D_001A8688[], D_001A8690[];
extern char D_001A8698[];          /* short per slot */
extern char D_001A86C0[];          /* short per slot */
extern short D_001A86E6;           /* gp-0x690A */
extern short D_001A86E8;
extern int D_001A9E70;             /* gp-0x5180 */
extern char D_001A9E78[];
extern char D_001B19A0[];
extern int D_001B1A80;
extern char D_001B1D30[];          /* two object pointers, then (as [1]) D_001B1D34 */
extern char D_001F1B78[];          /* 2 x 56 int weights (224 bytes each) */
extern char D_00210D40[];
extern char D_002119B0[];

extern void func_002A6AE0(char *p, int type);
extern void func_0026FEB8(const char *, ...);
extern int func_00279B70(unsigned char *a0, int a1, int a2);
extern char *func_002AB1F0(char *);
extern void func_0029B720(int);
extern float func_00282E48(void *, void *);
extern int func_00283CF0(float);
extern void func_002ADB78(char *object, int low, int high, int flags, int surface, int maximum, float height);

void func_002A6C58(char *self, int flags, int maximum)
{
    int scale;
    int slot;
    int id182;
    int bit100, bit400;
    int amount;     /* s0 */
    int share;      /* s4 */
    int total;
    int extra;
    int f;
    float value;
    char *info;

    if (*(short *)(self + 178) < 0)
        return;
    if (*(unsigned char *)(self + 177) & 0x80)
        return;

    scale = 1;
    self[127] = (char)(*(unsigned char *)(self + 127) + 1);
    if (*(char **)(self + 36) != 0 && *(short *)(*(char **)(self + 36) + 70) == 5) {
        if (D_001A7A32 != 0)
            scale = D_001A7A32;
        func_002A6AE0(self, 0);
    }

    slot = 1;
    id182 = *(unsigned short *)(self + 182);
    bit100 = flags & 0x100;
    bit400 = flags & 0x400;
    if (self != ((char **)D_001B1D30)[1]) {
        for (slot = 0; slot >= 0; slot--) {
            if (self == ((char **)D_001B1D30)[slot])
                break;
        }
    }

    if ((id182 != 0 || D_001A9E70 != -1)
        && (unsigned char)(*(unsigned char *)(D_00189E20 + 8884) - 1) >= 2) {
        share = (D_001A7A10 + 49) / 50;
        if (D_001A9E70 != -1 && slot < 0) {
            int t = D_001A9E70;
            short base = ((short *)D_001A86C0)[t];
            int count2 = ((int *)D_00188610)[t] * 2;
            short have = ((short *)D_001A8698)[t];
            amount = base;
            if (have < count2)
                amount = base * have / count2;
            if (amount == 0)
                amount = 1;
            func_0026FEB8(D_001A9E78, t, (int)base, amount);
        } else {
            int id178 = *(unsigned short *)(self + 178);
            unsigned char b = (unsigned char)D_0019B4A8[((short)id178 >> 1) + (D_001A79F0 << 10)];
            if ((id178 & 1) ? ((b >> 4) & 8) : (b & 8))
                amount = func_00279B70((unsigned char *)D_001A8690, (short)id182, (short)id178);
            else
                amount = func_00279B70((unsigned char *)D_001A8688, (short)id182, (short)id178);
        }

        info = func_002AB1F0(self);
        total = amount + share;
        if (info != 0 && *(unsigned char *)(info + 23) != 255) {
            if (slot >= 0) {
                int *w = (int *)(D_001F1B78 + slot * 224);
                int sum = 0;
                int i;
                for (i = 0; i < 56; i++)
                    sum += w[i];
                if (sum != 0) {
                    for (i = 0; i < 56; i++)
                        ((int *)D_00139868)[i] += w[i] * total / sum;
                }
                ((int *)D_001B1D30)[slot] = 0;
            } else {
                ((int *)D_00139868)[*(unsigned char *)(info + 23)] += total;
            }
        }
        D_001A7A10 -= share;
        D_001A7A0C += total;
        func_0029B720(720);
    }

    {
        int left = D_001A7A14;
        extra = (left + 49) / 50;
        D_001A7A14 = left - extra;
    }

    if (D_001A9E70 != -1) {
        short s = D_001A86E6;
        if (D_001A79F0 == 2)
            s = D_001A86E8;
        value = (float)s;
        if (slot >= 0)
            value = value * 10.0f;
    } else {
        int id178 = *(unsigned short *)(self + 178);
        unsigned char b = (unsigned char)D_0019B4A8[((short)id178 >> 1) + (D_001A79F0 << 10)];
        unsigned char *table = ((id178 & 1) ? ((b >> 4) & 8) : (b & 8)) ? (unsigned char *)D_001A8680
                                                                         : (unsigned char *)D_001A8678;
        value = (float)func_00279B70(table, *(short *)(self + 180), *(short *)(self + 178));
    }

    if (*(short *)(self + 178) >= 0 && !(*(unsigned char *)(self + 177) & 0x80)) {
        int id;
        unsigned char *p;
        unsigned int kind;

        if (D_001A9E70 != -1)
            ((int *)D_00188610)[D_001A9E70] += 1;

        id = *(unsigned short *)(self + 178);
        p = (unsigned char *)&D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
        if (id & 1) {
            if (((*p >> 4) & 7) != 7)
                *p = (unsigned char)(*p + 16);
        } else {
            if ((*p & 7) != 7)
                *p = (unsigned char)(*p + 1);
        }

        D_00210D40[*(short *)(self + 178) + 1124] = (char)(*(unsigned char *)(self + 176) + 2);
        kind = *(unsigned char *)(self + 176);
        if (kind == 255
            || (!(D_001B19A0[kind] & 0x80) && (D_0019B2E8[kind + D_001A79F0 * 16] & 0x80))) {
            D_002119B0[*(short *)(self + 178) + 1124] = (char)(kind + 2);
        }
    }

    if (D_001A9E70 == -1)
        value = value * (float)scale;
    value = value + (float)extra;

    f = bit100 ? 5 : 1;
    if (*(unsigned char *)(D_00189E20 + 8898) != 0 || (flags & 0x200))
        f |= 2;
    if (*(int *)(D_00189E20 + 8852) == 16) {
        if (func_00282E48(D_00189E20 + 128, self + 16) < 4.0f)
            f |= 2;
    }
    if (bit400)
        f |= 0x10;
    f |= 8;
    if (!(99 < D_001B1A80))
        f |= 2;

    if (value < 0.0f)
        value = 0.0f;
    if (0.0f < value) {
        int spread = 0;
        int mid;
        if (8.0f <= value)
            spread = func_00283CF0(value * 0.25f);
        else if (2.0f <= value)
            spread = 1;
        mid = func_00283CF0(value);
        func_002ADB78(self, mid - spread, mid + spread, f, -1, maximum, 0.0f);
    }
}
