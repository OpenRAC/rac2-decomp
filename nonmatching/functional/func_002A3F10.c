/* functional: high. Same reads, writes and call in the same order. Retail keeps its arguments and ra in the upper halves of $s4-$s7/$ra across the call instead of on the stack; that has no C meaning. The 64-byte copies read each 64-byte scratchpad block whole before writing it, as retail's four lq then four sq. */
extern unsigned char D_001CD640[];
extern int func_002A4078(unsigned int obj, unsigned int flags);

/* Mark which bone slots `count` animation parts use: clear the 128-byte table D_001CD640, set byte [slot] = 1 for every slot
   listed by each part (obj+0x24 -> +0x1C table, entry parts[i]: u16 n, then n slot bytes at +4), keep each part's last
   slot at D_001CD640+0x80+i, store max+1 at +0x7F and 0xFF at [max]; run func_002A4078(obj, table), then copy each
   part's 64-byte scratchpad matrix (0x70000000 + slot*64) to out[i]. */
void func_002A3F10(void *obj, int count, int *parts, void *out)
{
    unsigned char *t = D_001CD640;
    char *tab = *(char **)(*(char **)((char *)obj + 0x24) + 0x1C);
    unsigned char *last = t + 128;
    int *ip = parts;
    int max = 0;
    int n = count;
    unsigned char *d;
    int i;

    for (i = 0; i < 128; i++) {
        t[i] = 0;
    }
    do {
        unsigned char *p = *(unsigned char **)(tab + *ip++ * 4 + 4);
        int k = *(unsigned short *)p;
        unsigned int s;

        do {
            s = p[4];
            p++;
            k--;
            t[s] = 1;
        } while (k > 0);
        *last++ = s;
        n--;
        if ((int)s > max) {
            max = s;
        }
    } while (n > 0);
    t[127] = max + 1;
    t[max] = 0xFF;

    func_002A4078((unsigned int)obj, (unsigned int)t);

    last = t + 128;
    d = out;
    n = count;
    do {
        unsigned int *src = (unsigned int *)(0x70000000 + *last++ * 64);
        unsigned int b[16];

        n--;
        for (i = 0; i < 16; i++) {
            b[i] = src[i];
        }
        for (i = 0; i < 16; i++) {
            ((unsigned int *)d)[i] = b[i];
        }
        d += 64;
    } while (n > 0);
}
