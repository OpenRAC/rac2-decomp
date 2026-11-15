#include "common.h"
typedef unsigned int quadword __attribute__((mode(TI)));
extern void moby_set_state(u8 *, int, int);
extern void moby_set_flag_bit(u8 *, int);
extern u8 *D_L03_001B2A20[3] __attribute__((sda));
extern unsigned short D_L03_001B0300 __attribute__((sda));
extern unsigned short D_L03_001B0304 __attribute__((sda));
extern int g_frame_l03_counter[3] __attribute__((sda));
extern int D_L03_001B02F8 __attribute__((sda));
extern int D_L03_001B02FC[3] __attribute__((sda));
extern int D_L03_001B0308;
extern float D_L03_001B030C __attribute__((sda));
extern float D_L03_001B0310 __attribute__((sda));
extern float D_L03_001B0314 __attribute__((sda));
extern float D_L03_001B0318 __attribute__((sda));
extern u8 D_L03_001A8F20[16] __attribute__((sda));
extern void DrawGadgebotSpawnContainer(void);
extern void gfx_add_draw_callback_first(void *, void *);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern int part_find_owned_effect_slot(void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void SpawnTintedEffects(void *, void *, float, float, float, float, int, int, void *, int, int);
extern void part_spawn_masked_debris(void *, int, void *, int, float, float, float, float);
extern int PlayMobySound(int, int, void *);
/* Updates a breakable object (moby class 2418). It waits to be hit, then bursts into effects and sound and switches to its broken state. */
void breakable_moby_update(u8 *moby) {
    float burstPos[4] __attribute__((aligned(16)));
    float burstVel[4] __attribute__((aligned(16)));
    switch (moby[0x20]) {
    case 0:
        if ((int)moby < (int)D_L03_001B2A20[0]) {
            *(int *)(moby+0x9c) = 15;
            moby_set_state(moby, 3, -1);
        } else {
            *(unsigned short *)(moby+0x7c) = D_L03_001B0300;
            moby_set_state(moby, 1, -1);
        }
        break;
    case 1:
        if (moby[0x31]) {
            gfx_add_draw_callback_first(DrawGadgebotSpawnContainer, moby);
            *(int *)(moby+0x78) = FastTweenColor(D_L03_001B02F8, D_L03_001B02FC[0],
                (math_fast_sin_or_cos_b((g_frame_l03_counter[0] % 150) * 0.04188786819577217f - 3.14159f) + 1.0f) * 0.5f);
        }
        if (part_find_owned_effect_slot(moby, 0x10000, 0)) {
            *(quadword *)burstPos = 0; *(quadword *)burstVel = 0;
            burstVel[2] = 0.050000004f;
            burstPos[2] = 0.5f;
            FastVecAdd(burstPos, burstPos, moby+0x10);
            SpawnTintedEffects(moby,burstPos,0.333000004f,3.0f,0.5f,1.0f,5,1,burstVel,0x504040c0,0);
            part_spawn_masked_debris(moby,D_L03_001B0308,D_L03_001A8F20,255,D_L03_001B030C,D_L03_001B0310,D_L03_001B0314,D_L03_001B0318);
            PlayMobySound(0,0,moby);
            *(unsigned short *)(moby+0x7c) = D_L03_001B0304;
            moby_set_flag_bit(moby,1);
            *(int *)(moby+0x9c) = 15;
            *(unsigned short *)(moby+0x34) |= 2;
            moby_set_state(moby,2,-1);
        }
        break;
    }
}
