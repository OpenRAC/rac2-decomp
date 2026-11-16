#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

typedef struct {
    s32 busy;
} Vars43FB08;

typedef struct {
    u8 pad00[0x20];
    u8 state;
    u8 pad21[0x68 - 0x21];
    Vars43FB08 *vars;
    u8 pad6C[0xA8 - 0x6C];
    u8 alpha;
    u8 padA9;
    s16 uid;
    u8 padAC[0xD0 - 0xAC];
    f32 dir[4];
} Moby43FB08;

extern s32 g_debris2_piece_speed_range[2] __attribute__((sda));
extern s32 g_debris2_piece_spread_range[2] __attribute__((sda));
extern s32 g_debris2_piece_lifetime_a __attribute__((sda));
extern s32 g_debris2_piece_flags __attribute__((sda));
extern s32 g_debris2_piece_lifetime_b __attribute__((sda));

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
extern float math_random_float_range(float, float);
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int, int, int, int);

/* Waits until it is hit, then bursts into a spray of debris, plays a sound and removes itself. */
void breakable_l18_debris_update_2(Moby43FB08 *self) {
    f32 lo[4] __attribute__((aligned(16)));
    f32 hi[4] __attribute__((aligned(16)));
    f32 ext[4] __attribute__((aligned(16)));
    Vars43FB08 *vars = self->vars;

    switch (self->state) {
    case 0:
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(self, 0x4010000, 0) != 0 && vars->busy == 0) {
            *(TI *)ext = 0;
            ext[0] = 3.0f;
            ext[1] = 3.0f;
            FastVecScale(lo, self->dir, -math_random_float_range(6.0f, 8.0f));
            qcopy(hi, lo);
            FastVecSub(lo, lo, ext);
            FastVecAdd(hi, hi, ext);
            part_explode_object_into_pieces(self, lo, g_debris2_piece_spread_range, g_debris2_piece_speed_range, g_debris2_piece_flags, -1,
                              g_debris2_piece_lifetime_a, 9, g_debris2_piece_lifetime_b, 0xFF, 0);
            snd_play_from_class_bank(0, 0, self, self->uid);
            moby_mark_spawned(self);
        } else {
            self->alpha = 0xFF;
        }
        break;
    case 2:
        break;
    }
}
