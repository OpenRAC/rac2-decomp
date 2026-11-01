#include "include_asm.h"

typedef struct {
    char pad0[0x8];
    int unk08;
    int *unk0C;
    char pad10[0x38];
    short unk48;
    short unk4A;
    char pad4C[0x4];
    int unk50;
    int unk54;
    int w;
    int h;
    int flags;
    char pad64[0x8];
    int unk6C;
    unsigned char cnt[4];
    int unk74;
    int unk78;
    int unk7C;
    void *unk80;
} HudElem;
typedef unsigned char u8;

void func_PAL_0028C418(HudElem *a0) { a0->unk7C = 0xB4; a0->unk48 = 0; a0->unk4A = 0; func_0028B950((u8 *)a0); }

extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00282C10(float);
extern void func_PAL_0028E800(void *);

void func_PAL_0028C450(HudElem *p)
{
    unsigned char *c = p->cnt;
    int delta, limit, step;
    if (p->unk0C) {
        int value = *p->unk0C;
        if (value < 0) value = 0;
        p->unk78 = value;
        if (p->unk08 < value) p->unk78 = p->unk08;
    }
    if (p->unk74 != p->unk78) {
        p->unk7C = 150;
        if (p->unk6C >= 24) {
            delta = __builtin_abs(p->unk74 - p->unk78);
            if (delta) {
                step = func_00283CF0(func_00282C10(func_00283CE0(delta) * 0.04f) * 5.0f);
                limit = delta / 4;
                if (step < limit) step = limit;
                if (step > 121) step = 121;
                else if (step < 1) step = 1;
                c[3] += step;
                if (c[3] >= 3) {
                    step = c[3] / 2;
                    if (p->unk78 < p->unk74) p->unk74 -= step;
                    else p->unk74 += step;
                    c[3] -= step * 2;
                }
            }
        }
    }
    if (p->unk7C >= 4) {
        if (c[0] < 7) c[0]++;
        else if (c[1] < 7) c[1]++;
    } else {
        if (c[1] != 0 || c[0] != 0) p->unk6C = 1;
        {
            int fade = c[1];
            if (fade) c[1] = fade - 1;
            else {
                if (c[0]) c[0]--;
            }
        }
    }
    func_PAL_0028E800((char *)p + 0x40);
}

