#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* The callee reads component bounds through +0x18 and two-float ranges.
 * Keep the owning allocations incomplete; SDATA describes their measured GP binding. */
extern f32 D_L12_001B1F50[] SDATA(D_L12_001B1F50);
extern f32 D_L12_001B1F58[] SDATA(D_L12_001B1F58);
extern f32 D_L12_001B1F60[] SDATA(D_L12_001B1F60);
extern s32 D_L12_001B1FA0 __attribute__((sda));
extern f32 D_L12_001B1FB0 __attribute__((sda));
extern f32 D_L12_001B1FB4 __attribute__((nosda));
extern f32 D_L12_001B1FB8 __attribute__((nosda));
extern char D_L12_001B1F80[];

extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern s32 PlayMobySound(s32, s32, s32);
extern void moby_mark_spawned(void *);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int, int, unsigned char, int);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

/* Waits until the hero hits it, then shows a flash, a burst of sparks and a sound before removing itself. */
void hit_l12_burst_update(u8 *self)
{
    s32 *vars = *(s32 **)(self + 0x68);
    f32 pos[4];

    switch (self[0x20]) {
    case 0:
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(self, 0x4010000, 0) != 0 && *vars == 0) {
            moby_set_state(self, 2, -1);
            PlayMobySound(0, 0, (s32)self);
        }
        self[0xA8] = 0xFF;
        break;
    case 2:
        part_explode_object_into_pieces(self, D_L12_001B1F60, D_L12_001B1F58, D_L12_001B1F50, 0xFFFF, 0,
                          D_L12_001B1FA0, 0, 1, 0xFF, 0);
        part_explode_object_into_pieces(self, D_L12_001B1F80, D_L12_001B1F58, D_L12_001B1F50, 0xFFFF, 0,
                          D_L12_001B1FA0, 1, 0x1FE, 0xFF, 0);
        vec_local_offset_to_world(self, pos, D_L12_001B1FB0, D_L12_001B1FB4, D_L12_001B1FB8);
        SpawnExplosion(pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, *(f32 *)(self + 0x2C) * 20.0f, 20.0f,
                      1, 0, 1, 0);
        moby_mark_spawned(self);
        break;
    }
}

extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern s32 D_L12_001B29C8 __attribute__((sda));
extern u8 *D_L12_001B090C __attribute__((nosda));
extern u8 *D_L12_001B1360 __attribute__((nosda));
extern float IntToFloat(int);
extern int PulseColor(int, int, float);
extern int IsPointInCuboid(void *, int);
extern void moby_set_flag_bit(u8 *, s32);
extern int second_tracked_object_is_open(void);

/* Pulses the colour of a linked moby. When the hero walks into its zone, it turns the linked moby off and wakes up a third one. */
void zone_color_pulse_update(u8 *self)
{
    s32 *vars = *(s32 **)(self + 0x68);
    u8 *rec;
    u8 *obj;
    f32 phase, period;

    switch (self[0x20]) {
    case 0:
        moby_set_state(self, 1, -1);
        break;
    case 1:
        rec = D_L12_001B2E9C + (vars[1] << 8);
        if (rec[0x31] != 0) {
            phase = IntToFloat(D_L12_001B29C8 % 60);
            period = IntToFloat(60);
            phase *= 6.2831855f;
            phase /= period;
            *(s32 *)(rec + 0x78) = PulseColor(0x802020A0, 0x80202050, phase - 3.1415927f);
        }
        if (vars[0] == -1)
            break;
        obj = D_L12_001B090C;
        if (obj != 0) {
            if (IsPointInCuboid(obj + 0x10, vars[0])) {
                *(s32 *)(rec + 0x78) = 0x80A02020;
                moby_set_state(self, 2, -1);
                if (vars[2] != -1)
                    moby_set_flag_bit(D_L12_001B2E9C + (vars[2] << 8), 1);
            }
        } else if (second_tracked_object_is_open()) {
            if (IsPointInCuboid(D_L12_001B1360 + 0x10, vars[0])) {
                *(s32 *)(rec + 0x78) = 0x80A02020;
                moby_set_state(self, 2, -1);
                if (vars[2] != -1)
                    moby_set_flag_bit(D_L12_001B2E9C + (vars[2] << 8), 1);
            }
        }
        break;
    }
}

extern s32 D_L12_001B22D0 __attribute__((sda));
/* These are also unknown-sized component/range blocks, not scalar tuning words. */
extern f32 D_L12_001B2280[] SDATA(D_L12_001B2280);
extern f32 D_L12_001B2288[] SDATA(D_L12_001B2288);
extern f32 D_L12_001B22B0[] SDATA(D_L12_001B22B0);
extern int math_random_int_range(int, int);
extern int cam_moby_update(unsigned char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern u8 *CreateMoby(int);
extern void mem_copy_aligned(void *, void *, int);

/* Counts down a short timer, then blows up with an explosion and sound and drops a smaller piece of debris. */
void timed_explosion_debris_update(u8 *self)
{
    s32 *vars = *(s32 **)(self + 0x68);
    s32 life;
    u8 *obj;
    u16 flags;
    f32 vec[4];

    int state = self[0x20];

    switch (state) {
    case 0:
        *(s16 *)((u8 *)vars + 0x34) = math_random_int_range(20, 50);
        moby_set_state(self, 1, -1);
        break;
    case 1:
        life = *(s16 *)((u8 *)vars + 0x34);
        if (life < 0 || cam_moby_update(self)) {
            matrix_mul_vec3(vec, (u8 *)vars + 0x20, self + 0xC0);
            obj = 0;
            FastVecAdd(vec, self + 0x10, vec);
            SpawnExplosion(vec, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, state, state, 0, 0);
            snd_play_from_class_bank(2, 0, self, 0x12B1);
            flags = *(u16 *)(self + 0x7C);
            if (flags & 1)
                obj = CreateMoby(0x12E0);
            else if (flags & 2)
                obj = CreateMoby(0x12E1);
            else if (flags & 4)
                obj = CreateMoby(0x12E2);
            if (obj != 0) {
                qcopy(obj + 0x10, vec);
                *(f32 *)(obj + 0x2C) = *(f32 *)(*(u8 **)(obj + 0x24) + 0x24) *
                                       (*(f32 *)(self + 0x2C) / *(f32 *)(*(u8 **)(self + 0x24) + 0x24));
                mem_copy_aligned(obj + 0xC0, self + 0xC0, 0x18);
                part_explode_object_into_pieces(obj, D_L12_001B22B0, D_L12_001B2288, D_L12_001B2280, 0xFF, -1,
                                  D_L12_001B22D0, 0xF, 0xFF, 0xFF, 0);
                moby_mark_spawned(obj);
            }
            moby_mark_spawned(self);
        } else {
            *(s16 *)((u8 *)vars + 0x34) = life - 1;
        }
        break;
    }
}
