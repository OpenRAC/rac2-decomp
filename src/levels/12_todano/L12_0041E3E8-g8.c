#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* The callee reads component bounds through +0x18 and two-float ranges.
 * Keep the owning allocations incomplete; SDATA describes their measured GP binding. */
extern f32 g_burst_piece_params_a[] SDATA(D_L12_001B1F50);
extern f32 g_burst_piece_params_b[] SDATA(D_L12_001B1F58);
extern f32 g_burst_piece_params_c[] SDATA(D_L12_001B1F60);
extern s32 g_burst_piece_effect_id __attribute__((sda));
extern f32 g_burst_offset_x __attribute__((sda));
extern f32 g_burst_offset_y __attribute__((nosda));
extern f32 g_burst_offset_z __attribute__((nosda));
extern char g_burst_piece_params_d[];

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
        part_explode_object_into_pieces(self, g_burst_piece_params_c, g_burst_piece_params_b, g_burst_piece_params_a, 0xFFFF, 0,
                          g_burst_piece_effect_id, 0, 1, 0xFF, 0);
        part_explode_object_into_pieces(self, g_burst_piece_params_d, g_burst_piece_params_b, g_burst_piece_params_a, 0xFFFF, 0,
                          g_burst_piece_effect_id, 1, 0x1FE, 0xFF, 0);
        vec_local_offset_to_world(self, pos, g_burst_offset_x, g_burst_offset_y, g_burst_offset_z);
        SpawnExplosion(pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, *(f32 *)(self + 0x2C) * 20.0f, 20.0f,
                      1, 0, 1, 0);
        moby_mark_spawned(self);
        break;
    }
}

extern u8 *g_moby_list_start MACRO_ADDR;
extern s32 g_frame_l12_counter __attribute__((sda));
extern u8 *g_tracked_object_ptr __attribute__((nosda));
extern u8 *g_second_tracked_object __attribute__((nosda));
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
        rec = g_moby_list_start + (vars[1] << 8);
        if (rec[0x31] != 0) {
            phase = IntToFloat(g_frame_l12_counter % 60);
            period = IntToFloat(60);
            phase *= 6.2831855f;
            phase /= period;
            *(s32 *)(rec + 0x78) = PulseColor(0x802020A0, 0x80202050, phase - 3.1415927f);
        }
        if (vars[0] == -1)
            break;
        obj = g_tracked_object_ptr;
        if (obj != 0) {
            if (IsPointInCuboid(obj + 0x10, vars[0])) {
                *(s32 *)(rec + 0x78) = 0x80A02020;
                moby_set_state(self, 2, -1);
                if (vars[2] != -1)
                    moby_set_flag_bit(g_moby_list_start + (vars[2] << 8), 1);
            }
        } else if (second_tracked_object_is_open()) {
            if (IsPointInCuboid(g_second_tracked_object + 0x10, vars[0])) {
                *(s32 *)(rec + 0x78) = 0x80A02020;
                moby_set_state(self, 2, -1);
                if (vars[2] != -1)
                    moby_set_flag_bit(g_moby_list_start + (vars[2] << 8), 1);
            }
        }
        break;
    }
}

extern s32 g_explosion_piece_effect __attribute__((sda));
/* These are also unknown-sized component/range blocks, not scalar tuning words. */
extern f32 g_explosion_piece_table_c[] SDATA(D_L12_001B2280);
extern f32 g_explosion_piece_table_b[] SDATA(D_L12_001B2288);
extern f32 g_explosion_piece_offsets[] SDATA(D_L12_001B22B0);
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
                part_explode_object_into_pieces(obj, g_explosion_piece_offsets, g_explosion_piece_table_b, g_explosion_piece_table_c, 0xFF, -1,
                                  g_explosion_piece_effect, 0xF, 0xFF, 0xFF, 0);
                moby_mark_spawned(obj);
            }
            moby_mark_spawned(self);
        } else {
            *(s16 *)((u8 *)vars + 0x34) = life - 1;
        }
        break;
    }
}
