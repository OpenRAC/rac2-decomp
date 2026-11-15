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
extern float D_L01_001AFE2C __attribute__((sda));
extern float D_L01_001AFE28 __attribute__((sda));
extern float moby_get_anim_value(void *);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern int FloatToInt(float);
extern int queue_copy_record_by_index(int);
extern void slot_reset_active(int);
extern int math_fast_float_d(void *);
extern void PlayMobySound(int, int, void *);
extern int math_random_int_below(int);
extern void hero_record_play_counters(void);
extern void part_init_effect_record(void *, void *, int, float);
extern void QueueMobyImpact(int, void *);
extern void hero_start_move_state_walk_or_run(int);
extern void SetHeroMoveState(int, int);
extern void set_hero_animation(int, int, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_clamp_length(void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_clear_128(void *);

/* Updates a creature that waits for the player, grabs and holds him while it plays its animation, then lets go. The player is dragged towards it while he is held. */
void hero_grabber_update(char *moby)
{
    union {
        char query[0x24];
        struct { float pos[4], delta[4]; } vec;
    } scratch;
    char *vars = *(char **)(moby + 0x68);
    float frame = moby_get_anim_value(moby);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        moby_set_state(moby, 1, -1);
        if (*(unsigned char *)(moby + 0x43) != 0) anim_start_blended(moby, 0, 0, 2);
        *(int *)(moby + 0x9C) = 3;
        *(unsigned short *)(moby + 0x34) &= 0xEFFF;
        *(int *)(vars + 0x78) = -1;
        break;
    case 1:
        if (g_hero_state.obj == moby && g_hero_state.active) {
            moby_set_state(moby, 2, -1);
            *(int *)(vars + 0x60) = FloatToInt(*(float *)(vars + 0x50) * 60.0f);
            *(int *)(vars + 0x78) = queue_copy_record_by_index(7);
            if (*(unsigned char *)(moby + 0x43) != 1) anim_start_blended(moby, 1, 0, 10);
        }
        break;
    case 2:
        if (g_hero_state.obj == moby && g_hero_state.active) {
            *(int *)(vars + 0x78) = queue_copy_record_by_index(4);
        } else if (*(int *)(vars + 0x78) != -1) {
            slot_reset_active(*(int *)(vars + 0x78));
            *(int *)(vars + 0x78) = -1;
        }
        if (math_fast_float_d(vars + 0x70) && math_fast_float_d(vars + 0x60)) {
            if (*(int *)(vars + 0x78) != -1) {
                slot_reset_active(*(int *)(vars + 0x78));
                *(int *)(vars + 0x78) = -1;
            }
            moby_set_state(moby, 3, -1);
            PlayMobySound(0, 0, moby);
            if (*(unsigned char *)(moby + 0x43) != 2) anim_start_blended(moby, 2, 0, 6);
            if (g_hero_state.obj == moby && g_hero_state.active)
                *(int *)(vars + 0x78) = queue_copy_record_by_index(5);
            *(float *)(moby + 0x48) = D_L01_001AFE2C;
        }
        break;
    case 3:
        if (*(float *)(vars + 0x74) < 4.0f && frame > 4.0f) {
            *(unsigned short *)(moby + 0x34) |= 0x1000;
            *(int *)(vars + 0x64) = 600;
            if (g_hero_state.obj == moby && g_hero_state.f31C < 0.5f) {
                *(int *)(vars + 0x78) = queue_copy_record_by_index(5);
                *(int *)(vars + 0x68) = 1;
                *(int *)(moby + 0x9C) = -1;
            } else {
                if (*(int *)(vars + 0x78) != -1) {
                    slot_reset_active(*(int *)(vars + 0x78));
                    *(int *)(vars + 0x78) = -1;
                }
                *(int *)(moby + 0x9C) = 0x80000000;
            }
            moby_set_state(moby, 4, -1);
        }
        break;
    case 4:
        if (*(int *)(vars + 0x68) && !math_random_int_below(11)) *(int *)(vars + 0x78) = queue_copy_record_by_index(5);
        if (*(float *)(vars + 0x74) < 46.0f && frame > 46.0f) {
            if (*(int *)(vars + 0x68)) {
                if (g_hero_state.f24CC < 2) hero_record_play_counters();
                else {
                    part_init_effect_record(scratch.query, moby, 1, (float)*(unsigned char *)(vars + 0x34));
                    QueueMobyImpact(g_hero_state.query, scratch.query);
                }
                g_hero_state.flag = 0;
                hero_start_move_state_walk_or_run(0);
                *(int *)(vars + 0x68) = 0;
                *(int *)(vars + 0x70) = 120;
            }
            *(int *)(moby + 0x9C) = 3;
            *(unsigned short *)(moby + 0x34) &= 0xEFFF;
        }
        if (*(unsigned char *)(moby + 0x60) & 2) {
            if (*(int *)(vars + 0x78) != -1) {
                slot_reset_active(*(int *)(vars + 0x78));
                *(int *)(vars + 0x78) = -1;
            }
            moby_set_state(moby, 1, -1);
            if (*(unsigned char *)(moby + 0x43) != 0) anim_start_blended(moby, 0, 0, 10);
        } else if (*(int *)(vars + 0x68)) {
            if (g_hero_state.action != 111) {
                SetHeroMoveState(111, 1);
                set_hero_animation(10, 0, 10.0f);
            }
            g_hero_state.control = 2;
            qcopy(scratch.vec.pos, moby + 0x10);
            scratch.vec.pos[2] += 2.0f;
            FastVecSub(scratch.vec.delta, scratch.vec.pos, g_hero_state.pos);
            vec_clamp_length(scratch.vec.delta, 0.06666667f);
            FastVecAdd(g_hero_state.pos, g_hero_state.pos, scratch.vec.delta);
            vec_clear_128(g_hero_state.vel);
            vec_clear_128(g_hero_state.v110);
            vec_clear_128(g_hero_state.v120);
            vec_clear_128(g_hero_state.v130);
            if (*(int *)(vars + 0x64) > 60) *(int *)(vars + 0x64) = 60;
        }
        break;
    }
    *(float *)(moby + 0x2C) = *(float *)(*(char **)(moby + 0x24) + 0x24) * D_L01_001AFE28;
    *(unsigned char *)(moby + 0xA8) = 255;
    *(float *)(vars + 0x74) = frame;
}
