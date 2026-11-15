#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef struct {
    unsigned char pad_000[128];
    float position[4];
    unsigned char pad_090[8];
    float heading;
    unsigned char pad_09C[284];
    int frame;
    unsigned char pad_1BC[36];
    short attack_cooldown;
    unsigned char pad_1E2[36];
    short control_lock;
    unsigned char pad_208[8];
    u64 motion_flags;
    unsigned char pad_218[260];
    float movement;
    unsigned char pad_320[32];
    int action_ready;
    unsigned char pad_344[4];
    short special_ready;
    unsigned char pad_34A[4];
    short extended_range;
    unsigned char pad_350[332];
    unsigned char grounded;
    unsigned char pad_49D[1];
    unsigned char fast_attack;
    unsigned char pad_49F[53];
    int attack_mode;
    unsigned char pad_4D8[84];
    unsigned char alternate_ready;
    unsigned char pad_52D[103];
    int attack_pending;
    unsigned char pad_598[40];
    char *aim_target;
    float target_angle;
    unsigned char pad_5C8[292];
    int attack_blocked;
    unsigned char pad_6F0[952];
    int nearby_ready;
    unsigned char pad_AAC[24];
    float nearby_distance;
    unsigned char pad_AC8[16];
    float alternate_distance;
    unsigned char pad_ADC[2];
    short alternate_target_ready;
    unsigned char pad_AE0[52];
    int second_target_ready;
    unsigned char pad_B18[228];
    short animation_index;
    unsigned char pad_BFE[46];
    int attack_delay;
    unsigned char pad_C30[8];
    float animation_frame;
    unsigned char pad_C3C[1508];
    char *object;
    unsigned char pad_1224[12];
    u32 buttons;
    unsigned char pad_1234[6];
    unsigned char input_locked;
    unsigned char pad_123B[5];
    int input_window;
    int control_mode;
    int action;
    unsigned char pad_124C[590];
    unsigned char action_locked;
    unsigned char pad_149B[3573];
    char *owner;
    int mode;
    unsigned char pad_2298[4];
    u32 state;
    unsigned char pad_22A0[20];
    unsigned char disabled;
    unsigned char pad_22B5[3];
    unsigned char changing_weapon;
    unsigned char pad_22B9[3];
    unsigned char special_control;
    unsigned char pad_22BD[39];
    int pending_action;
    unsigned char pad_22E8[464];
    float transition_progress;
} HeroActionState;
extern HeroActionState g_hero_state;
typedef union {
    struct { u32 held, pressed; } word;
    u64 both;
} ButtonPair;
typedef struct {
    unsigned char prefix[0x1A0];
    ButtonPair buttons;
} InputState;
extern InputState g_pad_state;
extern unsigned char g_item_slot_to_record[];
extern u8 D_001A7B08[0x40] __attribute__((sda));
extern unsigned int D_001A7390[] __attribute__((sda));
extern int D_L00_001A7CC4 __attribute__((sda));
typedef struct { char pad[12]; int first_frame, trigger_frame; char rest[24]; } AnimationRange;
extern AnimationRange D_L00_0025D990[];
typedef struct { char pad[20]; int sound; char rest[200]; } EffectDefinition;
extern EffectDefinition g_weapon_l00_table[];
extern int PadPressedWithin(u32, int, int *);
extern int moby_is_class_71(unsigned char *);
extern void hero_setup_attached_object_transform(void);
extern int FloatToInt(float);
extern s32 func_US2_L00_002C4560(int, int);
extern int get_ammo(int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern char *SelectBestEligibleTarget(void *, int, int, float, float, float, float);
extern int CollLine(void *, void *, int, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern void hero_find_swingshot_node_in_front(void);
extern int hero_find_active_swingshot_node(void);
extern int hero_find_blue_swingshot_target(void);
extern void start_equipped_item_animation(void);
extern int PlayMobySound(int, int, char *);
extern int math_fast_float_d(int *);

/* Selects context-sensitive hero actions from buffered input and nearby targets.
 * RAC1's process_hero_equipped_item_input is the counterpart. */
int func_US2_L00_002C96D0(void)
{
    struct {
        Quadword point;
        int input_age, action_age, detach_age;
    } scratch;
    int previous_frame, state;
    u32 mask;


    if (g_hero_state.special_control) {
        if (g_hero_state.action != 10)
            return 0;
        if (g_hero_state.special_ready != 1)
            return 0;
    }
    if (g_hero_state.disabled) return 0;
    if (!g_hero_state.object) return 0;
    if (g_hero_state.input_locked) return 0;
    if (g_hero_state.control_mode != 2) return 0;

    previous_frame = g_hero_state.frame;
    mask = g_hero_state.buttons;
    state = g_hero_state.action;
    switch (state) {
    case 10: {
    int action, difference;
    int buffered_window;
    char *object;
    AnimationRange *range;
    float threshold, movement;
    if (g_hero_state.action_locked) break;
    if (g_hero_state.attack_cooldown == 0 && (g_hero_state.state < 2 || (g_hero_state.state == 4 && g_hero_state.grounded))) {
        if (PadPressedWithin(mask, 10, &scratch.input_age)) {
            object = g_hero_state.object;
            if (!object) goto clear_action;
            if (!moby_is_class_71((unsigned char *)object) || *(unsigned char *)(object + 0x20))
                goto clear_action;
            if ((g_pad_state.buttons.word.held & 8) ||
                ((g_hero_state.mode == 1 || g_hero_state.mode == 29) && g_hero_state.frame >= 21)) {
                if ((g_hero_state.mode == 1 || g_hero_state.mode == 29) && g_hero_state.frame >= 21)
                    hero_setup_attached_object_transform();
                else
                    func_US2_L00_002C4560(21, 1);
            } else {
                func_US2_L00_002C4560(19, 1);
            }
            goto clear_action;
        }
        goto clear_action;
    }
    if (g_hero_state.mode == 7 || g_hero_state.mode == 9 || g_hero_state.mode == 137 ||
        g_hero_state.mode == 8 || g_hero_state.mode == 6 ||
        (g_hero_state.mode == 14 && g_hero_state.animation_frame > 32.0f))
        goto buffered_attack;
    if ((g_hero_state.mode == 11 && g_hero_state.attack_mode != 3 && g_hero_state.animation_frame > 18.0f) ||
        (g_hero_state.mode == 11 && g_hero_state.attack_mode == 3 && g_hero_state.animation_frame > 20.0f))
        goto buffered_attack;
    if (g_hero_state.mode == 44 || g_hero_state.mode == 17)
        goto buffered_attack;
    goto ranged_attack;

buffered_attack:
    if (g_hero_state.frame < 11) goto ranged_attack;
    buffered_window = 14;
    if (g_hero_state.mode == 11 || g_hero_state.mode == 14)
        buffered_window = 18;
    if (!PadPressedWithin(mask, buffered_window, 0)) goto clear_action;
    if ((!g_hero_state.fast_attack && g_hero_state.movement > 0.1f) ||
        (g_hero_state.fast_attack && g_hero_state.movement > 0.57f) ||
        (g_hero_state.mode == 8 && g_hero_state.movement > 0.57f)) {
        if (g_hero_state.attack_blocked || g_hero_state.attack_pending) goto clear_action;
        func_US2_L00_002C4560(20, 1);
    } else {
        func_US2_L00_002C4560(19, 1);
    }
    goto clear_action;

ranged_attack:
    if (g_hero_state.state == 6) {
        range = &D_L00_0025D990[g_hero_state.animation_index];
        if (g_hero_state.mode == 21 && g_hero_state.frame >= 31) {
            if (g_hero_state.input_locked) goto check_attack_delay;
            if (g_hero_state.attack_delay) goto clear_action;
            if ((float)range->trigger_frame <= g_hero_state.animation_frame && (g_pad_state.buttons.word.held & 8) &&
                PadPressedWithin(mask, 15, 0)) {
                func_US2_L00_002C4560(21, 1);
                break;
            }
        }
check_attack_delay:
        if (!g_hero_state.attack_delay) {
            if (!g_hero_state.input_locked) {
                float frame = g_hero_state.animation_frame;
                if (!((float)range->trigger_frame <= frame)) goto clear_action;
                difference = (FloatToInt(frame) - range->first_frame) * 2;
                action = difference > 0 ? difference : 1;
                action = action < 16 ? action : 15;
                if (PadPressedWithin(mask, action, 0)) {
                    if (g_pad_state.buttons.word.held & 8) {
                        func_US2_L00_002C4560(21, 1);
                        goto clear_action;
                    }
                    func_US2_L00_002C4560(19, 1);
                }
            }
        }
    }
clear_action:
    g_hero_state.attack_pending = 0;
    break;

    }
    case 22:
    case 65:
    if (g_hero_state.mode == 1 || g_hero_state.mode == 29) break;
    if (!(g_hero_state.state < 2 || g_hero_state.state == 12 ||
          (g_hero_state.state == 4 && g_hero_state.grounded))) break;
    if (g_hero_state.pending_action && g_hero_state.pending_action != 22 && g_hero_state.pending_action != 65)
        break;
    if (!(g_pad_state.buttons.word.held & 32) || g_hero_state.input_window < 23) break;
    if (get_ammo(state)) {
        func_US2_L00_002C4560(131, 1);
        break;
    }
    if (g_pad_state.buttons.word.pressed & 32) {
        EffectDefinition *effect = &g_weapon_l00_table[g_item_slot_to_record[state]];
        snd_play_from_class_bank(0, 0, g_hero_state.owner, effect->sound);
    }
    break;

    case 46: {
    char *target;
    float direction;
    if (!(g_pad_state.buttons.word.pressed & mask)) break;
    if (g_hero_state.aim_target) {
        g_hero_state.aim_target = 0;
        break;
    }
    target = SelectBestEligibleTarget(&g_hero_state, 21, 0, 20.0f, g_hero_state.heading,
                              0.5235988497734069824f, 0.6981317996978759766f);
    g_hero_state.aim_target = target;
    if (target) {
        qcopy(&scratch.point, target + 16);
        ((float *)&scratch.point)[2] += 0.5f;
        if (CollLine(&scratch.point, (char *)&g_hero_state + 0xE0, 2, target, 0))
            g_hero_state.aim_target = 0;
        else {
            char *aim_target = g_hero_state.aim_target;
            direction = mat_fast_helper_a(g_hero_state.position[0] - *(float *)(aim_target + 16),
                                     g_hero_state.position[1] - *(float *)(aim_target + 20));
            g_hero_state.target_angle = fast_subtract_rotations(*(float *)(g_hero_state.aim_target + 0xF8), direction);
        }
    }
    break;

    }
    case 13: {
    int action;
    hero_find_swingshot_node_in_front();
    hero_find_active_swingshot_node();
    hero_find_blue_swingshot_target();
    action = g_hero_state.extended_range ? 8 : 5;
    if (g_hero_state.mode == 40) action = 11;
    if (g_hero_state.mode == 39 && (g_hero_state.alternate_target_ready || g_hero_state.nearby_ready)) {
        if (PadPressedWithin(mask, action, 0) ||
            ((g_pad_state.buttons.word.held & mask) && g_hero_state.input_window >= 16)) {
            func_US2_L00_002C4560(40, 1);
            break;
        }
    }
    if (!(g_hero_state.state < 2 || g_hero_state.state == 12 || g_hero_state.state == 4 ||
          g_hero_state.state == 2 || g_hero_state.state == 30 || g_hero_state.state == 5 ||
          (g_hero_state.mode == 40 && g_hero_state.frame >= 6) || g_hero_state.mode == 29))
        break;
    if (!PadPressedWithin(mask, action, 0) &&
        (!(g_pad_state.buttons.word.held & mask) || g_hero_state.input_window < 16)) break;
    if (g_hero_state.alternate_target_ready) {
        if (g_hero_state.nearby_ready) {
            if (g_hero_state.alternate_distance < g_hero_state.nearby_distance) g_hero_state.nearby_ready = 0;
            else g_hero_state.alternate_target_ready = 0;
        }
        if (g_hero_state.alternate_target_ready && !g_hero_state.control_lock && g_hero_state.mode != 43) {
            func_US2_L00_002C4560(43, 1);
            break;
        }
    }
    if (g_hero_state.nearby_ready && !g_hero_state.control_lock) {
        func_US2_L00_002C4560(35, 1);
        break;
    }
    if (g_hero_state.second_target_ready) {
        func_US2_L00_002C4560(138, 1);
        break;
    }
    break;

    }
    case 12:
    case 15:
    case 17:
    case 31: {
    int action, frame_window;
    if (!((g_hero_state.state == 0 && g_hero_state.mode != 29) || g_hero_state.state == 1 ||
          g_hero_state.state == 12 || g_hero_state.state == 5 || g_hero_state.state == 15 ||
          (g_hero_state.state == 4 && g_hero_state.alternate_ready) ||
          (g_hero_state.mode == 34 && g_hero_state.animation_frame > 55.0f))) break;
    if (g_hero_state.changing_weapon) break;
    if (g_hero_state.attack_cooldown) break;
    frame_window = g_hero_state.input_window;
    action = 7;
    if (frame_window < action) action = frame_window;
    if (!PadPressedWithin(mask, action, &scratch.action_age) && !(g_pad_state.buttons.word.held & 32)) break;
    if (frame_window < 23) break;
    if (get_ammo(-1)) {
        if (g_hero_state.state == 12 || g_hero_state.state == 0 || g_hero_state.mode == 3 ||
            (g_hero_state.state == 1 && g_hero_state.transition_progress < 0.7f)) {
            func_US2_L00_002C4560(34, 1);
            break;
        }
        start_equipped_item_animation();
    } else if (g_hero_state.object && (g_pad_state.buttons.word.pressed & 32))
        PlayMobySound(0, 0, g_hero_state.object);
    break;

    }
    case 53: {
    int action, frame_window;
    if (g_hero_state.attack_cooldown) break;
    if (!(g_hero_state.state < 2 || (g_hero_state.state == 4 && g_hero_state.grounded)))
        break;
    if (g_hero_state.mode != 1) {
        frame_window = g_hero_state.input_window;
        action = 9;
        action = action < frame_window ? 10 : frame_window;
        if (!PadPressedWithin(mask, action, &scratch.detach_age)) break;
        if (g_hero_state.object) {
            func_US2_L00_002C4560(31, 1);
            if (g_hero_state.object) PlayMobySound(0, 0, g_hero_state.object);
        }
    }
    break;
    }
    }

    if (g_hero_state.frame == previous_frame && D_001A7B08[0x26] && D_001A7390[3] == 54 &&
        g_hero_state.mode != 29 && g_hero_state.mode != 1 &&
        (g_hero_state.motion_flags & 0xffffffff00000000ULL) == 0) {
        math_fast_float_d(&D_L00_001A7CC4);
        if (D_L00_001A7CC4 &&
            (g_hero_state.state < 2 || g_hero_state.state == 12 ||
             ((g_hero_state.state == 2 || g_hero_state.state == 4) && g_hero_state.action_ready)) &&
            (g_pad_state.buttons.both & 0x800000008ULL) == 0x800000008ULL)
            func_US2_L00_002C4560(123, 1);
        if (g_pad_state.buttons.word.pressed & 8) D_L00_001A7CC4 = 30;
    }
    return g_hero_state.frame < previous_frame;
}
