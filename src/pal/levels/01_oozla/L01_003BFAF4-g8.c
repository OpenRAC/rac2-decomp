/* func_PAL_L01_003BFAF4, the PAL copy of func_L01_003BBF68: the same C with 50 Hz timings. */
#include "common.h"
typedef struct {
    char pad0[0x80];
    float pos[4];
    char pad90[0x60];
    float vel[4];
    char pad100[0x10];
    float v110[4], v120[4], v130[4];
    char pad140[0xB0];
    short control;
    char pad1F2[0x12A];
    float f31C;
    char pad320[0x1C];
    char *obj;
    int active;
    char pad344[0x1F4C];
    int query;
    int action;
    char pad2298[0x1D];
    char flag;
    char pad22B6[0x216];
    int f24CC;
} L01_003BBF68_HERO;
extern L01_003BBF68_HERO g_hero_state;
extern float g_grabber_field_value __attribute__((sda));
extern float g_grabber_scale_factor __attribute__((sda));
extern float moby_get_anim_value(void *);
extern void moby_set_state(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int FloatToInt(float);
extern int queue_copy_record_by_index(int);
extern void slot_reset_active(int);
extern int math_fast_float_d(void *);
extern int PlayMobySound(int, int, void *);
extern int math_random_int_below(int);
extern void hero_record_play_counters_pal(void);
extern void part_init_effect_record(void *, void *, int, float);
extern void QueueMobyImpact(int, void *);
extern void hero_start_move_state_walk_or_run(int);
extern s32 func_PAL_L01_002BEC60(int, int);
extern void set_hero_animation_pal(int, int, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_clamp_length(void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_clear_128(void *);

void func_PAL_L01_003BFAF4(char *obj)
{
    union {
        char query[0x24];
        struct { float pos[4], delta[4]; } vec;
    } scratch;
    char *s = *(char **)(obj + 0x68);
    float frame = moby_get_anim_value(obj);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        moby_set_state(obj, 1, -1);
        if (*(unsigned char *)(obj + 0x43) != 0) func_PAL_002A7E68(obj, 0, 0, 2);
        *(int *)(obj + 0x9C) = 3;
        *(unsigned short *)(obj + 0x34) &= 0xEFFF;
        *(int *)(s + 0x78) = -1;
        break;
    case 1:
        if (g_hero_state.obj == obj && g_hero_state.active) {
            moby_set_state(obj, 2, -1);
            *(int *)(s + 0x60) = FloatToInt((*(float *)(s + 0x50) * 300.0f + 2.0f) * 0.16666667f);
            *(int *)(s + 0x78) = queue_copy_record_by_index(7);
            if (*(unsigned char *)(obj + 0x43) != 1) func_PAL_002A7E68(obj, 1, 0, 8);
        }
        break;
    case 2:
        if (g_hero_state.obj == obj && g_hero_state.active) {
            *(int *)(s + 0x78) = queue_copy_record_by_index(4);
        } else if (*(int *)(s + 0x78) != -1) {
            slot_reset_active(*(int *)(s + 0x78));
            *(int *)(s + 0x78) = -1;
        }
        if (math_fast_float_d(s + 0x70) && math_fast_float_d(s + 0x60)) {
            if (*(int *)(s + 0x78) != -1) {
                slot_reset_active(*(int *)(s + 0x78));
                *(int *)(s + 0x78) = -1;
            }
            moby_set_state(obj, 3, -1);
            PlayMobySound(0, 0, obj);
            if (*(unsigned char *)(obj + 0x43) != 2) func_PAL_002A7E68(obj, 2, 0, 5);
            if (g_hero_state.obj == obj && g_hero_state.active)
                *(int *)(s + 0x78) = queue_copy_record_by_index(5);
            *(float *)(obj + 0x48) = g_grabber_field_value;
        }
        break;
    case 3:
        if (*(float *)(s + 0x74) < 4.0f && frame > 4.0f) {
            *(unsigned short *)(obj + 0x34) |= 0x1000;
            *(int *)(s + 0x64) = 500;
            if (g_hero_state.obj == obj && g_hero_state.f31C < 0.5f) {
                *(int *)(s + 0x78) = queue_copy_record_by_index(5);
                *(int *)(s + 0x68) = 1;
                *(int *)(obj + 0x9C) = -1;
            } else {
                if (*(int *)(s + 0x78) != -1) {
                    slot_reset_active(*(int *)(s + 0x78));
                    *(int *)(s + 0x78) = -1;
                }
                *(int *)(obj + 0x9C) = 0x80000000;
            }
            moby_set_state(obj, 4, -1);
        }
        break;
    case 4:
        if (*(int *)(s + 0x68) && !math_random_int_below(11)) *(int *)(s + 0x78) = queue_copy_record_by_index(5);
        if (*(float *)(s + 0x74) < 46.0f && frame > 46.0f) {
            if (*(int *)(s + 0x68)) {
                if (g_hero_state.f24CC < 2) hero_record_play_counters_pal();
                else {
                    part_init_effect_record(scratch.query, obj, 1, (float)*(unsigned char *)(s + 0x34));
                    QueueMobyImpact(g_hero_state.query, scratch.query);
                }
                g_hero_state.flag = 0;
                hero_start_move_state_walk_or_run(0);
                *(int *)(s + 0x68) = 0;
                *(int *)(s + 0x70) = 100;
            }
            *(int *)(obj + 0x9C) = 3;
            *(unsigned short *)(obj + 0x34) &= 0xEFFF;
        }
        if (*(unsigned char *)(obj + 0x60) & 2) {
            if (*(int *)(s + 0x78) != -1) {
                slot_reset_active(*(int *)(s + 0x78));
                *(int *)(s + 0x78) = -1;
            }
            moby_set_state(obj, 1, -1);
            if (*(unsigned char *)(obj + 0x43) != 0) func_PAL_002A7E68(obj, 0, 0, 8);
        } else if (*(int *)(s + 0x68)) {
            if (g_hero_state.action != 111) {
                func_PAL_L01_002BEC60(111, 1);
                set_hero_animation_pal(10, 0, 8.0f);
            }
            g_hero_state.control = 2;
            qcopy(scratch.vec.pos, obj + 0x10);
            scratch.vec.pos[2] += 2.0f;
            FastVecSub(scratch.vec.delta, scratch.vec.pos, g_hero_state.pos);
            vec_clamp_length(scratch.vec.delta, 0.080000006f);
            FastVecAdd(g_hero_state.pos, g_hero_state.pos, scratch.vec.delta);
            vec_clear_128(g_hero_state.vel);
            vec_clear_128(g_hero_state.v110);
            vec_clear_128(g_hero_state.v120);
            vec_clear_128(g_hero_state.v130);
            if (*(int *)(s + 0x64) > 50) *(int *)(s + 0x64) = 50;
        }
        break;
    }
    *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * g_grabber_scale_factor;
    *(unsigned char *)(obj + 0xA8) = 255;
    *(float *)(s + 0x74) = frame;
}
