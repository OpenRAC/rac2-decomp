#include "include_asm.h"

#include "common.h"
extern void moby_set_state(char *, int, int);
extern void moby_mark_spawned(char *);
extern void FastVecScale(char *, char *, float);
extern void *part_find_owned_effect_slot(char *, int, int);
extern void part_spawn_debris_mask_pal(char *, int, void *, int, float, float, float, float);
extern int PlayMobySound(int, int, char *);
extern void part_spawn_scaled_bolts_pal(char *, int, float);

/* Waits until hit, then bursts into fragments and removes itself. */
void fragment_burst_update_pal(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x800;
        moby_set_state((char *)moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot((char *)moby, 0x4010000, 0) != 0) {
            if (*(int *)vars == 0) {
                moby_set_state((char *)moby, 2, -1);
            }
        }
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        char impulse[16];

        FastVecScale(impulse, (char *)(moby + 0xD0), -0.040000003f);
        part_spawn_debris_mask_pal((char *)moby, 3, impulse, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, (char *)moby);
        part_spawn_scaled_bolts_pal((char *)moby, 1, 0.0f);
        moby_mark_spawned((char *)moby);
        break;
    }
    }
}

extern void SpawnExplosionEffects_pal(void *, void *, int, int, int, int, int, int, int, int, int, int,
                          float, float, float, float, float, float, float);
extern void vec_random_direction(float *, float, float);
extern float math_fabs(float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern char *cam_moby_create_pal(char *, int, int, int, char *, char *, float *, int, float, float);
extern void flying_fragment_update_pal(unsigned char *);

/* Looks up the object bound to the given flags; unless the hit object's own field says
   0xFE5, it starts a smoke emitter, spawns one particle with the level's own callback
   and six more in a loop, then clears the object's byte at 0xA8. */
void debris_burst_on_hit_pal(char *moby)
{
    char *hit;
    char *piece;
    float local[3];
    int i;

    hit = (char *)part_find_owned_effect_slot(moby, 0x4010001, 0);
    if (hit != 0 && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        PlayMobySound(0, 0, moby);
        SpawnExplosionEffects_pal(moby, moby + 0x10, 0, 10, 3, 9, -1, 1, 1, -1, 0, 0x810001,
                      0.0f, 0.0f, 4.0f, 2.0f, 9.0f, 0.0f, 15.0f);
        vec_random_direction(local, 0.040000003f, 0.080000006f);
        local[2] = math_fabs(local[2]);
        piece = cam_moby_create_pal(moby, 1, *(short *)(moby + 0xAA), 6, moby + 0x10, moby + 0xF0,
                          local, 1, math_random_signed_float_range(20.0f, 45.0f), 15.0f);
        if (piece != 0) {
            *(void (**)(void))(piece + 0x64) = (void (*)(void))flying_fragment_update_pal;
        }
        for (i = 0; i < 6; i++) {
            vec_random_direction(local, 0.120000005f, 0.24000001f);
            local[2] = math_fabs(local[2]);
            cam_moby_create_pal(moby, 2, *(short *)(moby + 0xAA), i, moby + 0x10, moby + 0xF0,
                          local, 0xFF, math_random_signed_float_range(20.0f, 45.0f),
                          math_random_float_range(15.0f, 25.0f));
        }
        PlayMobySound(1, 0, moby);
        part_spawn_scaled_bolts_pal(moby, 1, 0.0f);
        moby_mark_spawned(moby);
    }
    *(unsigned char *)(moby + 0xA8) = 0xFF;
}
