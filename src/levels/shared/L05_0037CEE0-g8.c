#include "common.h"
extern unsigned short *D_L05_001FB220[];
extern char *D_L05_001B251C;
extern char *D_L05_001B2614;
extern char *ref_L05_0037CEE0_0 __attribute__((sda));
extern char *ref_L05_0037CEE0_1 __attribute__((sda));
struct CountListCE {
    char pad[0x90];
    int count;
    int pad94, pad98;
    int list[1];
};
extern struct CountListCE D_L05_00221D10;
extern float func_332C18(void);
extern void func_33B330(void *, float, float, float);
extern void func_306630(void *, void *, void *);
extern void func_306660(void *, void *, void *);
extern void func_306AD8(void *, void *, void *);
extern void func_3068F8(void *, void *, float);
extern int func_338168(void *, int);
/* Moves the object's cached pieces by a random nudge and pushes them away from any list
   entries they touch. */
void func_L05_0037CEE0(char *obj, void *matrix, float scale)
{
    float a[4], b[4], c[4];
    int off, i, j;
    unsigned short *p;
    float x, y;
    char *table;
    short t;
    if (!D_L05_001FB220[*(unsigned char *)(obj + 0x21)])
        return;
    p = D_L05_001FB220[*(unsigned char *)(obj + 0x21)];
    do {
        off = *p & 0x7fff;
        x = func_332C18();
        y = func_332C18();
        func_33B330(a, scale, x, y);
        func_306630(D_L05_001B251C + off * 256 + 0x10, a, matrix);
        for (i = 0; i < D_L05_00221D10.count; i++) {
            if (func_338168(D_L05_001B251C + off * 256 + 0x10, D_L05_00221D10.list[i])) {
                table = D_L05_001B2614 + D_L05_00221D10.list[i] * 128;
                func_306660(b, ref_L05_0037CEE0_0 + off * 256 + 0x10, table + 0x30);
                b[3] = 0;
                func_306AD8(c, b, table + 0x40);
                func_3068F8(c, c, 1.05f);
                func_306AD8(c, c, table);
                func_306630(D_L05_001B251C + off * 256 + 0x10, c, table + 0x30);
                for (j = 0; j < D_L05_00221D10.count; j++)
                    if (func_338168(D_L05_001B251C + off * 256 + 0x10, D_L05_00221D10.list[j]))
                        qcopy(obj + 0x10, ref_L05_0037CEE0_1 + D_L05_00221D10.list[j] * 128 + 0x30);
            }
        }
        t = *(short *)p;
        p++;
    } while (t >= 0);
}
