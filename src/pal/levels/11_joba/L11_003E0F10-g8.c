#include "names.h"
/* func_PAL_L11_003E0F10, the PAL copy of func_L11_003DD068: the same C, with the speed scaled to 50 Hz. */
#include "common.h"

/* Spawns class 0xA77, copies its position and initializes its travel vector. */
extern u8 *CreateMoby(s32 arg0);

extern void moby_init_child_from_parent(void *a0, void *a1);

extern void FastVecSub(f32 *dst, f32 *a, f32 *b);

extern f32 FastVecLength(f32 *a);

extern void vec_scale_to_length(f32 *dst, f32 *a, f32 len);

extern f32 weapon_compute_shot_launch_speed(char *a0, char *a1, s32 a2, f32 f12, f32 f13);

extern f32 g_bomb_velocity_scale __attribute__((sda));

extern f32 g_bomb_speed __attribute__((sda));

typedef int TI128 __attribute__((mode(TI)));

u8 *func_PAL_L11_003E0F10(u8 *arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    u8 *s0 = arg0;
    u8 *s2 = arg1;
    u8 *s3 = arg2;
    f32 f21 = arg3;
    u8 *s1 = CreateMoby(0xA77);

    if (s1 != 0) {
        u8 *v1;
        TI128 *dst;
        f32 f20;

        v1 = s0;
        s0 = *(u8 **)(s1 + 0x68);
        moby_init_child_from_parent(s1, v1);
        v1 = *(u8 **)(s1 + 0x24);
        dst = (TI128 *)(s1 + 0x10);

        *(f32 *)(s1 + 0x2C) = *(f32 *)(v1 + 0x24) * g_bomb_velocity_scale;
        *(u16 *)(s1 + 0x34) |= 0x5000;
        *dst = *(TI128 *)s2;
        FastVecSub((f32 *)s0, (f32 *)s3, (f32 *)s2);
        *(s32 *)(s0 + 0x8) = 0;
        f20 = FastVecLength((f32 *)s0) / ((g_bomb_speed * 5.0f + 2.0f) * 0.16666667f);
        vec_scale_to_length((f32 *)s0, (f32 *)s0, f20);
        *(f32 *)(s0 + 0x8) = weapon_compute_shot_launch_speed((char *)s2, (char *)s3, 0, f20, -f21);
        *(f32 *)(s0 + 0xC) = f21;
    }
    return s1;
}
