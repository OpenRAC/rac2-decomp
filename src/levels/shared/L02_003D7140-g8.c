#include "common.h"

extern float D_L02_001B038C __attribute__((sda));
extern float D_L02_001B0388 __attribute__((sda));
extern char D_00189E20[];
extern u8 *D_001C49C0[];

extern int func_00277F48(float, void *, int, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8F70(void *, void *, int, void *, void *, float);

void func_L02_003D7140(u8 *self)
{
    f32 seen[4] __attribute__((aligned(16)));
    f32 diff[4] __attribute__((aligned(16)));
    f32 push[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(self + 0x68);
    u8 *obj;
    u8 *pos;
    int n;
    int i;
    char *game;

    n = func_00277F48(D_L02_001B038C, self + 0x10, 0, self, 0);
    if (n == 0)
        return;
    for (i = 0; i < n; i++) {
        game = D_00189E20;
        obj = D_001C49C0[i];
        if (obj == *(u8 **)(game + 0x2290)) {
            qcopy(seen, game + 0x80);
            if (*(s32 *)(game + 0x340) == 0)
                continue;
            pos = obj + 0x10;
        } else {
            qcopy(seen, obj + 0x10);
            pos = obj + 0x10;
            if (*(u16 *)(obj + 0x34) & 0x20) {
                u8 *other = *(u8 **)(*(u8 **)(obj + 0x68) + 0x18);

                if (other != 0 && *(s16 *)(other + 0xC0) == 0)
                    continue;
                if (self[0x31] == 0)
                    continue;
                if (obj[0x31] == 0)
                    continue;
                if (*(s16 *)(obj + 0xAA) == 0xA44)
                    continue;
                if (*(s16 *)(obj + 0xAA) == 0xA4B)
                    continue;
            }
        }
        FastVecSub(diff, pos, self + 0x10);
        push[0] = -diff[1];
        push[1] = diff[0];
        push[2] = 0.0f;
        vec_scale_to_length(push, push, D_L02_001B0388);
        push[2] = 1.0f;
        push[3] = 5627.9248046875f;
        func_002A8F70(obj, self, 0x10001, pos, push, (float)state[0x14]);
    }
}
