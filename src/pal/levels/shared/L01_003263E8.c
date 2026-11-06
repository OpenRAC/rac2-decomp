#include "common.h"
#include "include_asm.h"

extern int func_00115AC0(char *dst, char *src, int len);
extern void func_L01_003242C8(char *dst, int x, int idx);
extern unsigned char D_PAL_001A7C3C MACRO_ADDR;

/* func_PAL_L01_003263E8, the PAL copy of func_L01_00324410: the same C, where the
 * separator index 0 becomes the byte D_PAL_001A7C3C. */
void func_PAL_L01_003263E8(char *out, char *src, int *nums)
{
    int tab[10];
    unsigned char buf[32];
    int i;
    int *p;
    int *q;
    unsigned char *s;
    char *w;
    int n;
    int cnt;
    int v;

    p = nums;
    i = 0;
    func_00115AC0((char *)0x70000000, src, 0xFF);

    q = tab;
    for (;;) {
        p += 2;
        v = p[-2];
        if (v == -1)
            break;
        *q++ = v;
        i++;
        if (i >= 10)
            break;
    }

    s = (unsigned char *)0x70000000;
    w = out;
    cnt = 0;
    while (*s != 0) {
        if (*s == '%') {
            if (s[1] == 'd') {
                v = cnt++;
                s += 2;
            } else {
                v = s[1] - '0';
                s += 3;
            }
            func_L01_003242C8((char *)buf, tab[v], D_PAL_001A7C3C);
            n = 0;
            if (*buf != 0) {
                while (buf[n] != 0 && n < 32) {
                    *w = buf[n];
                    n++;
                    w++;
                }
            }
            *w = 0;
        } else {
            *w = *s;
            s++;
            w++;
        }
    }
    *w = 0;
}
