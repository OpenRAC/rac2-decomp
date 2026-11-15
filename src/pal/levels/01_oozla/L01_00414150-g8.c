#include "include_asm.h"

#include "common.h"
extern int D_L01_001AEC38 SDATA(D_L01_001AEC38);
extern int counter_abs __asm__("D_L01_001AEC38");
extern int active_abs __asm__("D_L01_001B3468");
extern float D_L01_001B208C __attribute__((sda));
extern float D_L01_001B2090 __attribute__((sda));
extern int D_L01_001B15E0 __attribute__((nosda));
extern int D_L01_001B3468 SDATA(D_L01_001B3468);
extern void moby_set_state(char *, int, int);
extern void *part_find_owned_effect_slot(char *, int, int);
extern void FastVecScale(char *, char *, float);
extern void func_PAL_002B15D8(char *, int, void *, float, float, float, float, int);
extern void func_PAL_L00_003281C0(char *, float, int);
extern int PlayMobySound(int, int, char *);
extern int flag_set_first_pending(char *);
extern void moby_mark_spawned(char *);
typedef struct { char pad0[0x31]; u8 active; u16 pad32; u16 flags; char pad36[0x62]; int target; } RetiringObject;

void func_PAL_L01_00414150(char *a0)
{
    char *s0 = a0;
    char *s1 = *(char **)(a0 + 0x68);
    float buf[4];
    int current;

    switch (*(u8 *)(s0 + 0x20)) {
    case 0:
        D_L01_001AEC38 = D_L01_001AEC38 + 1;
        moby_set_state(s0, 1, -1);
        return;
    case 1:
        if (part_find_owned_effect_slot(s0, 0x4010000, 0) != 0 && *(int *)s1 == 0) {
            D_L01_001AEC38 = counter_abs - 1;
            moby_set_state(s0, 2, -1);
        }
        *(u8 *)(s0 + 0xA8) = 0xFF;
        return;
    case 2:
        FastVecScale((char *)buf, s0 + 0xD0, -0.120000005f);
        if (*(u8 *)(s0 + 0x31) != 0 && D_L01_001B2090 < 0.9f &&
            D_L01_001B208C < 0.9f && (current = D_L01_001B3468, current < D_L01_001B15E0)) {
            func_PAL_002B15D8(s0, 0x3FF, buf, 1.0f, 3.0f, 2.0f, 4.0f, 0xFF);
        } else {
            func_PAL_002B15D8(s0, 0xF, buf, 1.0f, 3.0f, 2.0f, 4.0f, 0xFF);
        }
        func_PAL_L00_003281C0(s0, 0.0f, 4);
        PlayMobySound(0, 0, s0);
        moby_set_state(s0, 3, -1);
        return;
    case 3:
        if (flag_set_first_pending(s0) != 0) {
            RetiringObject *retiring = (RetiringObject *)s0;
            unsigned int flags = retiring->flags;
            int count;
            retiring->active = 0;
            retiring->target = 0;
            count = active_abs;
            retiring->flags = flags | 1;
            *(int *)(s1 + 4) = 0x64;
            active_abs = count + 1;
        }
        if (math_fast_float_d(s1 + 4) != 0) {
            D_L01_001B3468 = D_L01_001B3468 - 1;
            moby_mark_spawned(s0);
        }
        return;
    }
}
