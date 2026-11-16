#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;

extern int math_random_int_below(int);
extern void anim_start_immediate(void *, int, int);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern u8 *moby_l00_spawn_child(void *, int, int);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void SpawnTintedEffects(void *, void *, int, int, void *, unsigned int, void *, float, float, float, float);
extern void moby_mark_spawned(void *);
/* Required component/range reads do not establish the complete owning allocations. */
extern float g_death_piece_params_a[] SDATA(D_L09_001AF9E0);
extern float g_death_piece_params_b[] SDATA(D_L09_001AF9D8);
extern float g_death_piece_params_c[] SDATA(D_L09_001AF9D0);

/* Death of a three-state object: it picks its animation, waits for the hit, then spawns the
   closing effects and retires itself. */
/* Per-frame update that plays a death sequence in three steps and then removes the object. */
void death_sequence_update(u8 *self)
{
    EffectVector v;
    u8 *effect;

    switch (self[0x20]) {
    case 0:
        anim_start_immediate(self, 0, math_random_int_below(*(u8 *)(*(u8 **)(*(u8 **)(self + 0x24) + 0x48) + 0x10)));
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (*(short *)(self + 0xAA) == 0x852 /* moby class 2130 */) {
            if (part_find_owned_effect_slot(self, 0x4010000, 0)) {
                PlayMobySound(0, 0, self);
                moby_set_state(self, 2, -1);
            }
            self[0xA8] = 0xFF;
        }
        break;
    case 2:
        effect = moby_l00_spawn_child(self, 0x12A1, 0);
        if (effect)
            part_explode_object_into_pieces(effect, g_death_piece_params_a, g_death_piece_params_b, g_death_piece_params_c, 0xFFFF, 0,
                              -1, 0x16, 0xFFFF, 0xFF, 0);
        SpawnExplosion(self + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        v.bits = 0;
        v.value[2] = 0.20000002f;
        SpawnTintedEffects(self, self + 0x10, 0x14, 0, &v, 0x80804040, 0, 6.0f, 3.0f, 1.5f, 7.0f);
        moby_mark_spawned(effect);
        moby_mark_spawned(self);
        break;
    }
}
