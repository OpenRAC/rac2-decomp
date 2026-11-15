/* func_PAL_L01_00414828, the PAL copy of func_L01_0040F5A8: the same C, where func_L00_0032A258
   becomes func_PAL_L00_0032C328; 0.016666668f becomes 0.020000001f; 0.083333336f becomes
   0.10000001f; func_00273730 becomes func_PAL_002735D0; 0.015000000596046448f becomes
   0.018000001f; func_L01_002E1680 becomes func_PAL_L01_002E2968; 0.0066666672937572f becomes
   0.008f; func_002B0A68 becomes func_PAL_002B15D8; func_L00_00326110 becomes
   func_PAL_L00_003281C0; 0x78 becomes 0x64. */
#include "common.h"

typedef union { int q __attribute__((mode(TI))); float f[4]; } DebrisVector;

extern s32 D_L01_001AEC38 SDATA(D_L01_001AEC38);
extern s32 D_L01_001AEC38_1 __asm__("D_L01_001AEC38");
extern s32 D_L01_001B3468 SDATA(D_L01_001B3468);
extern s32 D_L01_001B3468_1 __asm__("D_L01_001B3468");
extern float D_L01_001B2090 __attribute__((sda));
extern float D_L01_001B208C __attribute__((sda));
extern s32 D_L01_001B15E0 NOT_SDA;
extern float D_L01_001B1600[] SDATA(D_L01_001B1600);
extern float D_L01_001B15F8[] SDATA(D_L01_001B15F8);
extern float D_L01_001B15F0[] SDATA(D_L01_001B15F0);
extern float D_L01_001B1620 __attribute__((sda));
extern float D_L01_001B1624 NOT_SDA;
extern float D_L01_001B1628 NOT_SDA;
extern char D_L01_001A8F60[] NOT_SDA;

extern s32 math_fast_float_d(char *);
extern void moby_mark_spawned(char *);
extern void moby_set_state(char *, s32, s32);
extern s32 part_find_owned_effect_slot(char *, s32, s32);
extern float math_random_float_range(float, float);
extern void *func_PAL_002735D0(char *, s32, s32, s32, char *, char *, void *, s32, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void func_PAL_002B15D8(char *, s32, char *, s32, float, float, float, float);
extern s32 flag_set_first_pending(char *);
extern void PlayMobySound(s32, s32, char *);
extern void vec_local_offset_to_world(char *, void *, float, float, float);
extern void func_PAL_L00_003281C0(char *, s32, float);
extern void func_PAL_L00_0032C328(char *, void *, void *, void *, s32, s32, s32, s32, s32, u8, void *);
extern void func_PAL_L01_002E2968(float, float, float, void *, void *, s32, u32, s32);

typedef struct { char pad0[0x31]; u8 active; u16 pad32; u16 flags; char pad36[0x62]; int target; } RetiringObject;
void func_PAL_L01_00414828(char *obj)
{
    DebrisVector velocity, jitter, position;
    char *rec = *(char **)(obj + 0x68);

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        D_L01_001AEC38 = D_L01_001AEC38_1 + 1;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(obj, 0x04010000, 0) != 0 && *(s32 *)rec == 0) {
            D_L01_001AEC38 = D_L01_001AEC38_1 - 1;
            moby_set_state(obj, 2, -1);
        }
        *(u8 *)(obj + 0xA8) = 0xFF;
        break;
    case 2:
        if (*(u8 *)(obj + 0x31) != 0 && D_L01_001B2090 < 0.9f && D_L01_001B208C < 0.9f
            && D_L01_001B3468 < D_L01_001B15E0) {
            func_PAL_L00_0032C328(obj, D_L01_001B1600, D_L01_001B15F8, D_L01_001B15F0,
                65535, 0, 0, 6, 65535, 255, 0);
            jitter.q = 0;
            jitter.f[0] = math_random_float_range(-1.0f, 1.0f) * 0.020000001f;
            jitter.f[1] = math_random_float_range(-1.0f, 1.0f) * 0.020000001f;
            jitter.f[2] = 0.10000001f;
            velocity.q = jitter.q;
            func_PAL_002735D0(obj, 2, *(s16 *)(obj + 0xaa), 0, obj + 0x10, obj + 0xf0,
                &velocity, 255, math_random_float_range(180.0f, 360.0f), 15.0f);
            jitter.q = 0;
            jitter.f[1] = -0.018000001f;
            vec_local_offset_to_world(obj, &position, D_L01_001B1620, D_L01_001B1624, D_L01_001B1628);
            matrix_mul_vec3(&jitter, &jitter, obj + 0xc0);
            func_PAL_L01_002E2968(0.008f, 1.0f, 1.0299999713897705f, &position, &jitter, 10, 0x80808080, 0);
            moby_set_state(obj, 3, -1);
        } else {
            func_PAL_002B15D8(obj, 17, D_L01_001A8F60, 255, 1.0f, 3.0f, 2.0f, 5.0f);
            func_PAL_L00_003281C0(obj, 1, 0.0f);
            PlayMobySound(0, 0, obj);
        }
        moby_set_state(obj, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(obj) != 0) {
            RetiringObject *retiring = (RetiringObject *)obj;
            unsigned int flags = retiring->flags;
            int count;
            retiring->active = 0;
            retiring->target = 0;
            count = D_L01_001B3468_1;
            retiring->flags = flags | 1;
            *(int *)(rec + 8) = 0x64;
            D_L01_001B3468_1 = count + 1;
        }
        if (math_fast_float_d(rec + 8) != 0) {
            D_L01_001B3468 = D_L01_001B3468 - 1;
            moby_mark_spawned(obj);
        }
        break;
    }
}
