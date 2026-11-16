#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef float f32;
extern s32 g_moby_array __attribute__((sda));
extern f32 math_random_float_range(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern char g_hero_position[];
extern void FastVecSub(void *, void *, void *);
extern f32 FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void moby_update_ground_probe(char *);
extern int moby_apply_damage_to_object_pal(char *, char *, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char g_hero_position[];
extern s32 g_beam_slot_state[];
extern s32 g_beam_start_light_ids[];
extern s32 g_beam_end_light_ids[];
extern s32 g_beam_slot_key[];

/* The record's whole per-frame pass: the sibling step, the aim vector copied out of the
   sub-object, the shared sprite pass, then the dispatch the shared tag call returns. */
void creature_update_hit_reaction_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    int result;

    moby_update_ground_probe(moby);
    *(f32 *)(moby + 0x2C) = *(f32 *)(*(char **)(moby + 0x24) + 0x24);
    moby_halve_linked_scale(moby);
    result = moby_apply_damage_to_object_pal(moby, vars + 0x50, 0);
    if (result == 0) {
        return;
    }
    if (result == 1) {
        float vec[4];

        FastVecSub(vec, moby + 0x10, g_hero_position);
        vec_scale_to_length(vars + 0x1A0, vec, 0.20000002f);
    } else {
        if (result == 4) {
            *(unsigned char *)(vars + 0xC6) = 0;
            *(s32 *)(vars + 0xCC) = -1;
        }
        group_advance_turn(moby);
    }
    creature_release_sounds(moby);
}


