/* functional: high. Hand-written retail (the twin of func_002A3F10, which differs only in the copy-out): same reads, writes and call in the same order. Retail keeps its arguments and ra in the upper halves of $s4-$s7/$ra across the call instead of on the stack; that has no C meaning. Each 16-byte copy reads its source quadword whole before writing it (lq then sq). Its only caller, func_0029FD48, passes all four arguments through untouched registers: its C in src/game/0029DE38.c must be called as func_002A3DB8(p1, n, p3, p4), not func_002A3DB8(p1). */
extern unsigned char D_001CD640[];
extern int func_002A4078(unsigned int obj, unsigned int flags);

/* Translation of `count` animated joints: clear the 128-byte table D_001CD640, set byte [slot] = 1 for every slot
   listed by each part (obj+0x24 -> +0x1C table, entry parts[i]: u16 n, then n slot bytes at +4), keep each part's last
   slot at D_001CD640+0x80+i, store max+1 at +0x7F and 0xFF at [max]; run func_002A4078(obj, table) (the pose of the
   marked joints into the scratchpad), then copy row 3 (+0x30, the translation) of each part's 64-byte scratchpad
   matrix (0x70000000 + slot*64) to out[i] (16 bytes each). */
void func_002A3DB8(void *obj, int count, int *parts, void *out)
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
        unsigned int *src = (unsigned int *)(0x70000000 + *last++ * 64 + 48);
        unsigned int b[4];

        n--;
        for (i = 0; i < 4; i++) {
            b[i] = src[i];
        }
        for (i = 0; i < 4; i++) {
            ((unsigned int *)d)[i] = b[i];
        }
        d += 16;
    } while (n > 0);
}
