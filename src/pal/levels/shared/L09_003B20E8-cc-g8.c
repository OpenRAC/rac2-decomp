/* func_PAL_L09_003B20E8, the PAL copy of func_L09_003AE8C8: the same C, where scale func_00283CF0(ticks). */
#include "common.h"

/* func_PAL_L09_003B20E8 needs -g (its divisions keep their two-nop hazard pairs). */

typedef int TI128 __attribute__((mode(TI)));

/* The spawned projectile's state block (object + 0x68). */
typedef struct {
    char pad00[0x30];
    TI128 direction;
    char *owner;
    int pad44;
    int ticks;
    float inverseTicks, d, f, range;
    int pad5c;
    float c;
    int a, b;
} ProjectileState;

extern char *func_0029EFD0(int);
extern char D_0018A0E0[];
extern float D_L09_001AF89C __attribute__((sda));
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern void func_L09_003AEE10(char *);
extern void func_002E5CF8(int, int, char *);
extern void func_002A0F48(char *);

/* Integer arguments stay pos, owner, dir, a, b ($a0-$t0) and float arguments f, range, c, d
   ($f12-$f15); only the interleaving of the two banks is chosen. */
char *func_PAL_L09_003B20E8(void *pos, char *owner, float f, float range, float c, void *dir, int a,
                        int b, float d)
{
    char *obj = func_0029EFD0(0x5DE);

    if (obj) {
        float length, ticks, factor;
        ProjectileState *st = *(ProjectileState **)(obj + 0x68);

        *(unsigned char *)(obj + 0x30) = 255;
        *(short *)(obj + 0x34) = 256;
        *(unsigned char *)(obj + 0x20) = 0;
        qcopy(&st->direction, dir);
        qcopy(obj + 0x10, pos);
        st->range = range;
        qcopy(obj + 0xC0, &st->direction);
        func_00282DD8(obj + 0xD0, obj + 0xC0, D_0018A0E0);
        func_00282F20(obj + 0xD0, obj + 0xD0, -1.0f);
        func_00282DD8(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        length = func_00282DF0(dir);
        ticks = st->range / length;
        st->ticks = (((int)(func_00283CF0(ticks)) * 5 + 2) / 6);
        length = func_00283CE0(st->ticks);
        factor = D_L09_001AF89C;
        st->owner = owner;
        st->f = f;
        st->a = a;
        st->b = b;
        st->inverseTicks = 1.0f / length;
        st->c = c;
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * factor;
        *(unsigned char *)(obj + 0x20) = 0;
        st->d = d;
        func_L09_003AEE10(obj);
        func_002E5CF8(0, 0, obj);
        func_002A0F48(obj);
    }
    return obj;
}
