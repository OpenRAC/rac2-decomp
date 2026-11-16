#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F38c810;
extern float g_default_l13_effect_vector;
extern void moby_set_state(char *, s32, s32);
extern void *part_find_owned_effect_slot(char *, s32, s32);
extern void *part_spawn_object_following_effect(void *, char *, s32, s32, float, float, s32, s32, s32, s32);
extern int PlayMobySound(s32, s32, char *);
extern void part_spawn_scaled_bolts_pal(char *, s32, float);
extern char *SpawnExplosion_pal(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern float FastAddRotations(float, float);
extern void euler_rotation_basis(void *, void *);
extern void func_PAL_002B15D8(char *, s32, float *, float, float, float, float, s32);
extern void moby_mark_spawned(char *);

/* Three-state effect object: arms its emitter, waits for the trigger, then spins a burst of four sprites and retires. */
void spinning_sprite_burst_update_pal(char *obj)
{
    V4_F38c810 v;
    s32 *rec = *(s32 **)(obj + 0x68);
    s32 i;
    char *pos, *rot;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        v.q = 0;
        v.f[2] = 2.0f;
        part_spawn_object_following_effect(&v, obj, 0x40204080, -1, 420000.0f, 1.0f, 1, -1, 0, -1);
        moby_set_state(obj, 1, -1);
        return;
    case 1:
        if (part_find_owned_effect_slot(obj, 0x04010000, 0) != 0 && *rec == 0)
            moby_set_state(obj, 2, -1);
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    case 2:
        PlayMobySound(0, 0, obj);
        part_spawn_scaled_bolts_pal(obj, 4, 0.0f);
        pos = obj + 0xC0;
        rot = obj + 0xF0;
        SpawnExplosion_pal(obj + 0x10, 0, 0x19, 0x14, 0.5f, 20.0f, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0);
        i = 3;
        do {
            i--;
            *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8), 1.5707964f);
            euler_rotation_basis(pos, rot);
            func_PAL_002B15D8(obj, 0xF, &g_default_l13_effect_vector, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
            *(short *)(obj + 0x7C) = 0;
        } while (i >= 0);
        moby_mark_spawned(obj);
        return;
    }
}
