#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;
extern int math_random_int_below(int);
extern void anim_start_immediate(void *, int, int);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern u8 *moby_l00_spawn_child(void *, int, int);
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void part_spawn_glow_fade_effects_pal(void *, void *, int, int, void *, unsigned int, void *, float, float, float, float);
extern void moby_mark_spawned(void *);
extern float g_death_piece_params_a[] SDATA(D_L09_001AF9E0);
extern float g_death_piece_params_b[] SDATA(D_L09_001AF9D8);
extern float g_death_piece_params_c[] SDATA(D_L09_001AF9D0);

/* Death of a three-state object: it picks its animation, waits for the hit, then spawns the
   closing effects and retires itself. */
void death_sequence_update_pal(u8 *moby)
{
    EffectVector offset;
    u8 *effect;

    switch (moby[0x20]) {
    case 0:
        anim_start_immediate(moby, 0, math_random_int_below(*(u8 *)(*(u8 **)(*(u8 **)(moby + 0x24) + 0x48) + 0x10)));
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (*(short *)(moby + 0xAA) == 0x852 /* moby class 2130 */) {
            if (part_find_owned_effect_slot(moby, 0x4010000, 0)) {
                PlayMobySound(0, 0, moby);
                moby_set_state(moby, 2, -1);
            }
            moby[0xA8] = 0xFF;
        }
        break;
    case 2:
        effect = moby_l00_spawn_child(moby, 0x12A1, 0);
        if (effect)
            part_explode_object_into_pieces_pal(effect, g_death_piece_params_a, g_death_piece_params_b, g_death_piece_params_c, 0xFFFF, 0,
                              -1, 0x16, 0xFFFF, 0xFF, 0);
        SpawnExplosion_pal(moby + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        offset.bits = 0;
        offset.value[2] = 0.24000001f;
        part_spawn_glow_fade_effects_pal(moby, moby + 0x10, 0x14, 0, &offset, 0x80804040, 0, 6.0f, 3.0f, 1.5f, 7.0f);
        moby_mark_spawned(effect);
        moby_mark_spawned(moby);
        break;
    }
}
