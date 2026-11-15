#include "common.h"
extern void *part_find_owned_effect_slot(void *, int, int);
extern float moby_update_aim_target_strength(void *, void *);
extern float ApproachValue(float *, float, float);
extern void SetDeathBits(void *, int, int);
extern int PlayMobySound(int, int, char *);
extern void moby_set_state(u8 *, int, int);
extern u8 *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void anim_start_immediate(void *, int, int);
/* Counts the object's fuse down. When it runs out the object explodes with a sound and effect and resets. */
void fuse_tick_explode(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float position[4] __attribute__((aligned(16)));
    float zero = 0.0f;
    float step = moby_update_aim_target_strength(moby, part_find_owned_effect_slot(moby, 0x10000, 0));
    u16 flags;
    ApproachValue((float *)(vars + 0x20), zero, step);
    if (*(float *)(vars + 0x20) <= zero) {
        SetDeathBits(moby, 0, 3);
        PlayMobySound(1, 0, (char *)moby);
        moby_set_state(moby, 1, -1);
        flags = *(u16 *)(moby + 0x34);
        moby[0xA8] = 255;
        flags |= 0x41;
        *(u32 *)(moby + 0x98) = 0;
        flags &= 0xEFFF;
        *(u16 *)(moby + 0x34) = flags;
        qcopy(position, moby + 0x10);
        position[2] += 0.5f;
        SpawnExplosion(moby + 0x10, 0, 0, 0, 0, 10, 20, 0, 1.0f, 20.0f, 1, 0, 0, 0);
        anim_start_immediate(moby, 2, 0);
    }
}
