#include "common.h"

/* func_L11_003DCEB0: a Joba moby's update. State 0 moves it along its velocity and, on a
   func_002761F8 hit, snaps to the hit point and switches to state 1; state 1 counts frames
   at 0x96. It is removed with an effect (func_002ABBB8) when func_002A9640 finds a target,
   or from frame 0x79 of state 1.
   Built -O2 -G8 in its own unit. The flag takes the state value (1) only once the count
   reaches 0x79, which gives retail's movn; the effect table is the sda incomplete array
   most callers declare, so its address is one macro load beside the argument moves. */
extern f32 D_L11_001B0170 __attribute__((sda));
extern f32 D_L11_001B016C __attribute__((sda));
extern f32 D_L11_001B0174 __attribute__((sda));
extern u8 D_L11_001C0D20[];
extern u8 D_L11_001A8F20[] __attribute__((sda));
extern s32 CollLine(void *, void *, s32, void *, s32);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int PlayMobySound(s32, s32, u8 *);
extern void moby_mark_spawned(u8 *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void moby_set_state(void *, int, int);

/* Updates the Hoverbike Race Bomb (moby class 2679). It flies along its path, lands on a
   hit, and blows up when something touches it or after a short time. */
void hoverbike_bomb_update(u8 *moby) {
    u8 vec[16] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    s32 expired = 0;
    u8 state = moby[0x20];

    switch (state) {
    case 0:
        FastVecAdd(vec, moby + 0x10, vars);
        *(f32 *)(vars + 8) = *(f32 *)(vars + 8) - *(f32 *)(vars + 0xC);
        if (CollLine(moby + 0x10, vec, 2, 0, 0) != 0) {
            qcopy(moby + 0x10, D_L11_001C0D20);
            *(f32 *)(moby + 0x18) = *(f32 *)(moby + 0x18) + D_L11_001B0170 * D_L11_001B016C;
            moby_set_state(moby, 1, -1);
        } else {
            qcopy(moby + 0x10, vec);
        }
        break;
    case 1:
        *(u16 *)(moby + 0x96) += 1;
        if (*(u16 *)(moby + 0x96) >= 0x79) expired = state;
        break;
    }
    if (part_find_owned_effect_slot(moby, -1, 0) != 0 || expired != 0) {
        SpawnExplosionEffects(moby, D_L11_001A8F20, moby + 0x10, D_L11_001B0174, 1.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        PlayMobySound(0, 0, moby);
        moby_mark_spawned(moby);
    }
}
