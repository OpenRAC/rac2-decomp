#include "include_asm.h"

typedef int Q128 __attribute__((mode(TI)));
typedef struct {
    char pad0[0xAA4];
    int fAA4;
    char padAA8[0xAD4 - 0xAA8];
    int fAD4;
    char padAD8[0x2294 - 0xAD8];
    int state;
} Hero_428F00;
typedef struct {
    char pad0[0x194];
    char *dst;
    char pad198[0x314 - 0x198];
    int f314;
} Ctl_428F00;
extern Hero_428F00 D_00189E20;
extern Ctl_428F00 D_L00_001B8C80;
extern void func_PAL_L00_0042DA78(char *);
extern void ref_L00_00428F00_00(char *);
extern void func_L00_002DA1E0(char *, float);

void func_PAL_L00_0042E3F0(char *o)
{
    int *t = (int *)(*(char **)(o + 0x70) + 0xB8);
    int st = D_00189E20.state;
    char *pos;
    int x, y;

    if (st == 0x2B) {
        x = t[2];
        pos = o + 0x30;
        y = D_00189E20.fAD4;
    } else {
        pos = o + 0x30;
        if ((unsigned int)(st - 0x23) >= 3)
            goto done;
        x = t[2];
        y = D_00189E20.fAA4;
    }
    if (x != y) {
        char *p = D_L00_001B8C80.dst;
        *(Q128 *)(p + 0x30) = *(Q128 *)pos;
        *(Q128 *)p = *(Q128 *)o;
        *(Q128 *)(p + 0x10) = *(Q128 *)(o + 0x10);
        *(Q128 *)(p + 0x20) = *(Q128 *)(o + 0x20);
        func_PAL_L00_0042DA78(o);
        D_L00_001B8C80.f314 = 0x25;
    }
done:
    ref_L00_00428F00_00(o);
    func_L00_002DA1E0(pos, 0.5f);
    *(int *)(*(char **)(o + 0x70) + 0x80) = 0;
}
