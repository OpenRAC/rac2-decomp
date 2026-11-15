#include "common.h"

/* Spawns class 0xA77, copies its position and initializes its travel vector. */
extern u8 *CreateMoby(s32 arg0);

extern void moby_init_child_from_parent(void *a0, void *a1);

extern void FastVecSub(f32 *dst, f32 *a, f32 *b);

extern f32 FastVecLength(f32 *a);

extern void vec_scale_to_length(f32 *dst, f32 *a, f32 len);

extern f32 weapon_compute_shot_launch_speed(char *a0, char *a1, s32 a2, f32 f12, f32 f13);

extern f32 D_L11_001B016C __attribute__((sda));

extern f32 D_L11_001B0168 __attribute__((sda));

typedef int TI128 __attribute__((mode(TI)));

/* Creates a Hoverbike Race Bomb and sets its starting position and travel direction. */
u8 *hoverbike_bomb_spawn(u8 *owner, u8 *startPos, u8 *targetPos, f32 gravity) {
    u8 *ownerOrVars = owner;
    u8 *start = startPos;
    u8 *target = targetPos;
    f32 fallRate = gravity;
    u8 *bomb = CreateMoby(0xA77 /* Hoverbike Race Bomb */);

    if (bomb != 0) {
        u8 *v1;
        TI128 *dst;
        f32 travelTime;

        v1 = ownerOrVars;
        ownerOrVars = *(u8 **)(bomb + 0x68);
        moby_init_child_from_parent(bomb, v1);
        v1 = *(u8 **)(bomb + 0x24);
        dst = (TI128 *)(bomb + 0x10);

        *(f32 *)(bomb + 0x2C) = *(f32 *)(v1 + 0x24) * D_L11_001B016C;
        *(u16 *)(bomb + 0x34) |= 0x5000;
        *dst = *(TI128 *)start;
        FastVecSub((f32 *)ownerOrVars, (f32 *)target, (f32 *)start);
        *(s32 *)(ownerOrVars + 0x8) = 0;
        travelTime = FastVecLength((f32 *)ownerOrVars) / D_L11_001B0168;
        vec_scale_to_length((f32 *)ownerOrVars, (f32 *)ownerOrVars, travelTime);
        *(f32 *)(ownerOrVars + 0x8) = weapon_compute_shot_launch_speed((char *)start, (char *)target, 0, travelTime, -fallRate);
        *(f32 *)(ownerOrVars + 0xC) = fallRate;
    }
    return bomb;
}
