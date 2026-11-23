/* func_US2_L01_002C1D90, the USA v2.00 copy of func_L01_002C1A70: the same C, with three new tests of the
 * short at 0x1E0 that block the item actions (cases 10, the 12/15/17/31 group, and 53). */
#include "include_asm.h"
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
/* A measured resident view, not a claim about the full allocation size. */
typedef struct ActionView {
    unsigned char gap0[0x80];
    float position[4];
    unsigned char gap90[0x8];
    float facing;
    unsigned char gap9C[0x44];
    float origin[4];
    unsigned char gapF0[0xC8];
    int transition_timer;
    unsigned char gap1BC[0x24];
    short item_block;
    unsigned char gap1E2[0x2E];
    unsigned long flags;
    unsigned char gap218[0x104];
    float height;
    unsigned char gap320[0x20];
    int platformMode;
    unsigned char gap344[0x4];
    short stance;
    unsigned char gap34A[0x152];
    unsigned char can_attack;
    unsigned char gap49D[0x1];
    unsigned char high_attack;
    unsigned char gap49F[0x35];
    int air_style;
    unsigned char gap4D8[0x54];
    unsigned char allow_action;
    unsigned char gap52D[0x67];
    int pending_attack;
    unsigned char gap598[0x28];
    char * target;
    float targetAngle;
    unsigned char gap5C8[0x124];
    int attack_block;
    unsigned char gap6F0[0x50C];
    short animation_index;
    unsigned char gap_bfe[0x2E];
    int animation_lock;
    unsigned char gapC30[0x8];
    float animation_frame;
    unsigned char gapC3C[0x5E4];
    char * action_object;
    unsigned char gap1224[0xC];
    unsigned int action_mask;
    unsigned char gap1234[0x6];
    unsigned char action_lock;
    unsigned char gap123B[0x5];
    int action_age;
    int action_mode;
    int request;
    unsigned char gap124C[0x24E];
    unsigned char attack_disabled;
    unsigned char gap149B[0xDF5];
    char * object;
    int action;
    unsigned char gap2298[0x4];
    unsigned int motion;
    unsigned char gap22A0[0x14];
    unsigned char mode;
    unsigned char gap22B5[0x3];
    unsigned char busy;
    unsigned char gap22B9[0x3];
    unsigned char override;
    unsigned char gap22BD[0x27];
    int queued_action;
    unsigned char gap22E8[0x1D0];
    float blend;
} ActionView;
extern ActionView g_hero_state;
typedef union ButtonPair {
    struct { unsigned int buffered; unsigned int pressed; } word;
    unsigned long both;
} ButtonPair;
typedef struct InputView {
    unsigned char prefix[0x1A0];
    ButtonPair buttons;
} InputView;
extern InputView g_pad_state;
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_action_flag;
/* Four per-slot item ids (also read in src/game/002C7748-g8.c); 0x001A739C is element 1. */
extern int g_menu_choice_table[] __attribute__((sda));
extern int g_hero_action_timer __attribute__((sda));
extern char g_hero_anim_timing_table[][44];
typedef struct ActionTableEntry {
    unsigned char prefix[0x14];
    int id;
    unsigned char suffix[0xC8];
} ActionTableEntry;
extern ActionTableEntry g_action_table[];
extern unsigned int PadPressedWithin(unsigned int, int, int *);
extern int moby_is_class_71(unsigned char *);
extern void hero_setup_attached_object_transform(void);
extern int SetHeroMoveState_us2(int, int);
extern int get_ammo(int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern int PlayMobySound(int, int, char *);
extern char *SelectBestEligibleTarget(char *, int, int, float, float, float, float);
extern int CollLine(void *, void *, int, char *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern int FloatToInt(float);
extern int math_fast_float_d(int *);
extern void start_equipped_item_animation(void);

/* Field views retain the measured resident layout without asserting its extent. */

/* Equipped-item input for the current hero state, as in RAC1's
 * process_hero_item_action_input: starts the matching move and returns 1 when
 * the state timer was reset. */
int hero_process_item_action_input_us2(void)
{
    int request;
    int previous_timer;
    unsigned int mask;
    struct {
        Quadword position;
        int attack_buffered;
        int action_buffered;
        int wrench_buffered;
    } scratch;
    char *object;
    char *timing;
    int window;
    float angle;

    if (g_hero_state.override && (g_hero_state.request != 10 || g_hero_state.stance != 1)) return 0;
    if (g_hero_state.mode) return 0;
    if (!g_hero_state.action_object) return 0;
    if (g_hero_state.action_lock) return 0;
    if (g_hero_state.action_mode != 2) return 0;
    request = g_hero_state.request;
    mask = g_hero_state.action_mask;
    previous_timer = g_hero_state.transition_timer;

    switch (request) {
    case 10:
        if (g_hero_state.attack_disabled) break;
        if (!g_hero_state.item_block && (g_hero_state.motion < 2 || (g_hero_state.motion == 4 && g_hero_state.can_attack))) {
            if (PadPressedWithin(mask, 10, &scratch.attack_buffered)) {
                object = g_hero_state.action_object;
                if (!object) goto clear_pending;
                if (!moby_is_class_71((unsigned char *)object) || *(unsigned char *)(object + 0x20))
                    goto clear_pending;
                if ((g_pad_state.buttons.word.buffered & 8) ||
                    ((g_hero_state.action == 1 || g_hero_state.action == 0x1D) && g_hero_state.transition_timer > 20)) {
                    if ((g_hero_state.action == 1 || g_hero_state.action == 0x1D) && g_hero_state.transition_timer > 20) {
                        hero_setup_attached_object_transform();
                        goto clear_pending;
                    }
                    SetHeroMoveState_us2(0x15, 1);
                } else {
                    SetHeroMoveState_us2(0x13, 1);
                }
            }
        } else {
            if (g_hero_state.action == 7 || g_hero_state.action == 9 || g_hero_state.action == 0x89 || g_hero_state.action == 8 || g_hero_state.action == 6 ||
                (g_hero_state.action == 0xE && g_hero_state.animation_frame > 32.0f) ||
                (g_hero_state.action == 0xB && g_hero_state.air_style != 3 && g_hero_state.animation_frame > 18.0f) ||
                (g_hero_state.action == 0xB && g_hero_state.air_style == 3 && g_hero_state.animation_frame > 20.0f) ||
                g_hero_state.action == 0x2C || g_hero_state.action == 0x11) {
                if (g_hero_state.transition_timer > 10) {
                    int air_window = 0xE;
                    if (g_hero_state.action == 0xB || g_hero_state.action == 0xE) air_window = 0x12;
                    if (!PadPressedWithin(mask, air_window, 0)) goto clear_pending;
                    if ((!g_hero_state.high_attack && g_hero_state.height > 0.1f) ||
                        (g_hero_state.high_attack && g_hero_state.height > 0.57f) ||
                        (g_hero_state.action == 8 && g_hero_state.height > 0.57f)) {
                        if (!g_hero_state.attack_block && !g_hero_state.pending_attack)
                            SetHeroMoveState_us2(0x14, 1);
                    } else {
                        SetHeroMoveState_us2(0x13, 1);
                    }
                    goto clear_pending;
                }
            }
            if (g_hero_state.motion == 6) {
                timing = g_hero_anim_timing_table[g_hero_state.animation_index];
                if (g_hero_state.action == 0x15 && g_hero_state.transition_timer > 30) {
                    if (g_hero_state.action_lock) goto check_animation_lock;
                    if (g_hero_state.animation_lock) goto clear_pending;
                    if ((float)*(int *)(timing + 0x10) <= g_hero_state.animation_frame &&
                        (g_pad_state.buttons.word.buffered & 8) && PadPressedWithin(mask, 15, 0)) {
                        SetHeroMoveState_us2(0x15, 1);
                        goto complete;
                    }
                }
check_animation_lock:
                if (!g_hero_state.animation_lock) {
                    if (!g_hero_state.action_lock) {
                        float frame = g_hero_state.animation_frame;
                        if ((float)*(int *)(timing + 0x10) <= frame) {
                            window = (FloatToInt(frame) - *(int *)(timing + 0xC)) * 2;
                            window = window > 0 ? window : 1;
                            if (PadPressedWithin(mask, window < 16 ? window : 15, 0)) {
                                if (g_pad_state.buttons.word.buffered & 8)
                                    SetHeroMoveState_us2(0x15, 1);
                                else
                                    SetHeroMoveState_us2(0x13, 1);
                                goto clear_pending;
                            }
                        }
                    }
                    goto clear_pending;
                }
            }
        }
clear_pending:
        g_hero_state.pending_attack = 0;
        break;

    case 22: case 65:
        if (g_hero_state.action == 1 || g_hero_state.action == 0x1D ||
            (g_hero_state.motion > 1 && g_hero_state.motion != 12 && (g_hero_state.motion != 4 || !g_hero_state.can_attack)) ||
            (g_hero_state.queued_action && g_hero_state.queued_action != 22 && g_hero_state.queued_action != 65)) break;
        if (!(g_pad_state.buttons.word.buffered & 0x20) || g_hero_state.action_age < 23) break;
        if (get_ammo(request)) {
            SetHeroMoveState_us2(0x83, 1);
            goto complete;
        }
        if (g_pad_state.buttons.word.pressed & 0x20)
            snd_play_from_class_bank(0, 0, g_hero_state.object,
                         (g_action_table + g_item_slot_to_record[request])->id);
        break;

    case 46: {
        char *target;
        if (g_pad_state.buttons.word.pressed & mask) {
            if (g_hero_state.target) {
                g_hero_state.target = 0;
                break;
            }
            target = SelectBestEligibleTarget((char *)&g_hero_state, 21, 0, 20.0f, g_hero_state.facing,
                                      0.52359885f, 0.6981318f);
            g_hero_state.target = target;
            if (target) {
                qcopy(&scratch.position, target + 0x10);
                ((float *)&scratch.position)[2] += 0.5f;
                if (CollLine(&scratch.position, g_hero_state.origin, 2, target, 0)) {
                    g_hero_state.target = 0;
                } else {
                    char *aim_target = g_hero_state.target;
                    angle = mat_fast_helper_a(g_hero_state.position[0] - *(float *)(aim_target + 0x10),
                                          g_hero_state.position[1] - *(float *)(aim_target + 0x14));
                    g_hero_state.targetAngle = fast_subtract_rotations(*(float *)(g_hero_state.target + 0xF8), angle);
                }
            }
        }
        break;
    }

    case 12: case 15: case 17: case 31: {
        int action_age;
        int action_window;
        if (((g_hero_state.motion != 0 || g_hero_state.action == 0x1D) && g_hero_state.motion != 1 && g_hero_state.motion != 12 &&
             g_hero_state.motion != 5 && g_hero_state.motion != 15 && (g_hero_state.motion != 4 || !g_hero_state.allow_action) &&
             (g_hero_state.action != 0x22 || !(g_hero_state.animation_frame > 55.0f))) || g_hero_state.busy ||
            g_hero_state.item_block) break;
        action_age = g_hero_state.action_age;
        action_window = action_age;
        if (action_age >= 7) action_window = 7;
        if (!PadPressedWithin(mask, action_window, &scratch.action_buffered) && !(g_pad_state.buttons.word.buffered & 0x20)) break;
        if (action_age < 23) break;
        if (get_ammo(-1)) {
            if (g_hero_state.motion == 12 || g_hero_state.motion == 0 || g_hero_state.action == 3 ||
                (g_hero_state.motion == 1 && g_hero_state.blend < 0.7f)) {
                SetHeroMoveState_us2(0x22, 1);
                goto complete;
            }
            start_equipped_item_animation();
        } else if (g_hero_state.action_object && (g_pad_state.buttons.word.pressed & 0x20)) {
            PlayMobySound(0, 0, g_hero_state.action_object);
        }
        break;
    }

    case 53: {
        int wrench_age;
        int wrench_window;
        if (g_hero_state.item_block) break;
        if (g_hero_state.motion > 1 && (g_hero_state.motion != 4 || !g_hero_state.can_attack)) break;
        if (g_hero_state.action != 1) {
            wrench_age = g_hero_state.action_age;
            wrench_window = 10;
            if (wrench_age < 10) wrench_window = wrench_age;
            if (PadPressedWithin(mask, wrench_window, &scratch.wrench_buffered) && g_hero_state.action_object) {
                SetHeroMoveState_us2(31, 1);
                if (g_hero_state.action_object) PlayMobySound(0, 0, g_hero_state.action_object);
            }
        }
        break;
    }
    }

complete:
    if (g_hero_state.transition_timer == previous_timer) {
        if (g_action_flag && g_menu_choice_table[1] == 0x36 &&
            g_hero_state.action != 0x1D && g_hero_state.action != 1 &&
            !(g_hero_state.flags & 0xFFFFFFFF00000000UL)) {
            math_fast_float_d(&g_hero_action_timer);
            if (g_hero_action_timer &&
                (g_hero_state.motion < 2 || g_hero_state.motion == 12 || ((g_hero_state.motion == 2 || g_hero_state.motion == 4) && g_hero_state.platformMode)) &&
                (g_pad_state.buttons.both & 0x800000008UL) == 0x800000008UL)
                SetHeroMoveState_us2(0x7B, 1);
            if (g_pad_state.buttons.word.pressed & 8) g_hero_action_timer = 30;
        }
    }
    return g_hero_state.transition_timer < previous_timer;
}
