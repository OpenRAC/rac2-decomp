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
extern HeroActionState D_00189E20;
typedef union {
    struct { u32 held, pressed; } word;
    u64 both;
} ButtonPair;
typedef struct {
    unsigned char prefix[0x1A0];
    ButtonPair buttons;
} InputState;
extern InputState D_00138180;
extern unsigned char D_00139568[];
extern u8 D_001A7B08[0x40] __attribute__((sda));
extern unsigned int D_001A7390[] __attribute__((sda));
extern int D_L00_001A7CC4 __attribute__((sda));
typedef struct { char pad[12]; int first_frame, trigger_frame; char rest[24]; } AnimationRange;
extern AnimationRange D_L00_0025D990[];
typedef struct { char pad[20]; int sound; char rest[200]; } EffectDefinition;
extern EffectDefinition D_L00_00262570[];
extern int func_L00_0032EF10(u32, int, int *);
extern int func_L00_002B3248(unsigned char *);
extern void func_L00_002BA508(void);
extern int func_00283CF0(float);
extern void func_US2_L00_002C4560(int, int);
extern int func_L00_002D4040(int);
extern int func_002E5DA0(int, int, char *, int);
extern char *func_L00_002AE888(void *, int, int, float, float, float, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern void func_L00_002C3BB0(void);
extern int func_L00_002C3E18(void);
extern int func_L00_002C40C0(void);
extern void func_L00_002AF568(void);
extern int func_002E5CF8(int, int, char *);
extern int func_00282948(int *);

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


    if (D_00189E20.special_control) {
        if (D_00189E20.action != 10)
            return 0;
        if (D_00189E20.special_ready != 1)
            return 0;
    }
    if (D_00189E20.disabled) return 0;
    if (!D_00189E20.object) return 0;
    if (D_00189E20.input_locked) return 0;
    if (D_00189E20.control_mode != 2) return 0;

    previous_frame = D_00189E20.frame;
    mask = D_00189E20.buttons;
    state = D_00189E20.action;
    switch (state) {
    case 10: {
    int action, difference;
    int buffered_window;
    char *object;
    AnimationRange *range;
    float threshold, movement;
    if (D_00189E20.action_locked) break;
    if (D_00189E20.attack_cooldown == 0 && (D_00189E20.state < 2 || (D_00189E20.state == 4 && D_00189E20.grounded))) {
        if (func_L00_0032EF10(mask, 10, &scratch.input_age)) {
            object = D_00189E20.object;
            if (!object) goto clear_action;
            if (!func_L00_002B3248((unsigned char *)object) || *(unsigned char *)(object + 0x20))
                goto clear_action;
            if ((D_00138180.buttons.word.held & 8) ||
                ((D_00189E20.mode == 1 || D_00189E20.mode == 29) && D_00189E20.frame >= 21)) {
                if ((D_00189E20.mode == 1 || D_00189E20.mode == 29) && D_00189E20.frame >= 21)
                    func_L00_002BA508();
                else
                    func_US2_L00_002C4560(21, 1);
            } else {
                func_US2_L00_002C4560(19, 1);
            }
            goto clear_action;
        }
        goto clear_action;
    }
    if (D_00189E20.mode == 7 || D_00189E20.mode == 9 || D_00189E20.mode == 137 ||
        D_00189E20.mode == 8 || D_00189E20.mode == 6 ||
        (D_00189E20.mode == 14 && D_00189E20.animation_frame > 32.0f))
        goto buffered_attack;
    if ((D_00189E20.mode == 11 && D_00189E20.attack_mode != 3 && D_00189E20.animation_frame > 18.0f) ||
        (D_00189E20.mode == 11 && D_00189E20.attack_mode == 3 && D_00189E20.animation_frame > 20.0f))
        goto buffered_attack;
    if (D_00189E20.mode == 44 || D_00189E20.mode == 17)
        goto buffered_attack;
    goto ranged_attack;

buffered_attack:
    if (D_00189E20.frame < 11) goto ranged_attack;
    buffered_window = 14;
    if (D_00189E20.mode == 11 || D_00189E20.mode == 14)
        buffered_window = 18;
    if (!func_L00_0032EF10(mask, buffered_window, 0)) goto clear_action;
    if ((!D_00189E20.fast_attack && D_00189E20.movement > 0.1f) ||
        (D_00189E20.fast_attack && D_00189E20.movement > 0.57f) ||
        (D_00189E20.mode == 8 && D_00189E20.movement > 0.57f)) {
        if (D_00189E20.attack_blocked || D_00189E20.attack_pending) goto clear_action;
        func_US2_L00_002C4560(20, 1);
    } else {
        func_US2_L00_002C4560(19, 1);
    }
    goto clear_action;

ranged_attack:
    if (D_00189E20.state == 6) {
        range = &D_L00_0025D990[D_00189E20.animation_index];
        if (D_00189E20.mode == 21 && D_00189E20.frame >= 31) {
            if (D_00189E20.input_locked) goto check_attack_delay;
            if (D_00189E20.attack_delay) goto clear_action;
            if ((float)range->trigger_frame <= D_00189E20.animation_frame && (D_00138180.buttons.word.held & 8) &&
                func_L00_0032EF10(mask, 15, 0)) {
                func_US2_L00_002C4560(21, 1);
                break;
            }
        }
check_attack_delay:
        if (!D_00189E20.attack_delay) {
            if (!D_00189E20.input_locked) {
                float frame = D_00189E20.animation_frame;
                if (!((float)range->trigger_frame <= frame)) goto clear_action;
                difference = (func_00283CF0(frame) - range->first_frame) * 2;
                action = difference > 0 ? difference : 1;
                action = action < 16 ? action : 15;
                if (func_L00_0032EF10(mask, action, 0)) {
                    if (D_00138180.buttons.word.held & 8) {
                        func_US2_L00_002C4560(21, 1);
                        goto clear_action;
                    }
                    func_US2_L00_002C4560(19, 1);
                }
            }
        }
    }
clear_action:
    D_00189E20.attack_pending = 0;
    break;

    }
    case 22:
    case 65:
    if (D_00189E20.mode == 1 || D_00189E20.mode == 29) break;
    if (!(D_00189E20.state < 2 || D_00189E20.state == 12 ||
          (D_00189E20.state == 4 && D_00189E20.grounded))) break;
    if (D_00189E20.pending_action && D_00189E20.pending_action != 22 && D_00189E20.pending_action != 65)
        break;
    if (!(D_00138180.buttons.word.held & 32) || D_00189E20.input_window < 23) break;
    if (func_L00_002D4040(state)) {
        func_US2_L00_002C4560(131, 1);
        break;
    }
    if (D_00138180.buttons.word.pressed & 32) {
        EffectDefinition *effect = &D_L00_00262570[D_00139568[state]];
        func_002E5DA0(0, 0, D_00189E20.owner, effect->sound);
    }
    break;

    case 46: {
    char *target;
    float direction;
    if (!(D_00138180.buttons.word.pressed & mask)) break;
    if (D_00189E20.aim_target) {
        D_00189E20.aim_target = 0;
        break;
    }
    target = func_L00_002AE888(&D_00189E20, 21, 0, 20.0f, D_00189E20.heading,
                              0.5235988497734069824f, 0.6981317996978759766f);
    D_00189E20.aim_target = target;
    if (target) {
        qcopy(&scratch.point, target + 16);
        ((float *)&scratch.point)[2] += 0.5f;
        if (func_002761F8(&scratch.point, (char *)&D_00189E20 + 0xE0, 2, target, 0))
            D_00189E20.aim_target = 0;
        else {
            char *aim_target = D_00189E20.aim_target;
            direction = func_00283248(D_00189E20.position[0] - *(float *)(aim_target + 16),
                                     D_00189E20.position[1] - *(float *)(aim_target + 20));
            D_00189E20.target_angle = func_00283BE0(*(float *)(D_00189E20.aim_target + 0xF8), direction);
        }
    }
    break;

    }
    case 13: {
    int action;
    func_L00_002C3BB0();
    func_L00_002C3E18();
    func_L00_002C40C0();
    action = D_00189E20.extended_range ? 8 : 5;
    if (D_00189E20.mode == 40) action = 11;
    if (D_00189E20.mode == 39 && (D_00189E20.alternate_target_ready || D_00189E20.nearby_ready)) {
        if (func_L00_0032EF10(mask, action, 0) ||
            ((D_00138180.buttons.word.held & mask) && D_00189E20.input_window >= 16)) {
            func_US2_L00_002C4560(40, 1);
            break;
        }
    }
    if (!(D_00189E20.state < 2 || D_00189E20.state == 12 || D_00189E20.state == 4 ||
          D_00189E20.state == 2 || D_00189E20.state == 30 || D_00189E20.state == 5 ||
          (D_00189E20.mode == 40 && D_00189E20.frame >= 6) || D_00189E20.mode == 29))
        break;
    if (!func_L00_0032EF10(mask, action, 0) &&
        (!(D_00138180.buttons.word.held & mask) || D_00189E20.input_window < 16)) break;
    if (D_00189E20.alternate_target_ready) {
        if (D_00189E20.nearby_ready) {
            if (D_00189E20.alternate_distance < D_00189E20.nearby_distance) D_00189E20.nearby_ready = 0;
            else D_00189E20.alternate_target_ready = 0;
        }
        if (D_00189E20.alternate_target_ready && !D_00189E20.control_lock && D_00189E20.mode != 43) {
            func_US2_L00_002C4560(43, 1);
            break;
        }
    }
    if (D_00189E20.nearby_ready && !D_00189E20.control_lock) {
        func_US2_L00_002C4560(35, 1);
        break;
    }
    if (D_00189E20.second_target_ready) {
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
    if (!((D_00189E20.state == 0 && D_00189E20.mode != 29) || D_00189E20.state == 1 ||
          D_00189E20.state == 12 || D_00189E20.state == 5 || D_00189E20.state == 15 ||
          (D_00189E20.state == 4 && D_00189E20.alternate_ready) ||
          (D_00189E20.mode == 34 && D_00189E20.animation_frame > 55.0f))) break;
    if (D_00189E20.changing_weapon) break;
    if (D_00189E20.attack_cooldown) break;
    frame_window = D_00189E20.input_window;
    action = 7;
    if (frame_window < action) action = frame_window;
    if (!func_L00_0032EF10(mask, action, &scratch.action_age) && !(D_00138180.buttons.word.held & 32)) break;
    if (frame_window < 23) break;
    if (func_L00_002D4040(-1)) {
        if (D_00189E20.state == 12 || D_00189E20.state == 0 || D_00189E20.mode == 3 ||
            (D_00189E20.state == 1 && D_00189E20.transition_progress < 0.7f)) {
            func_US2_L00_002C4560(34, 1);
            break;
        }
        func_L00_002AF568();
    } else if (D_00189E20.object && (D_00138180.buttons.word.pressed & 32))
        func_002E5CF8(0, 0, D_00189E20.object);
    break;

    }
    case 53: {
    int action, frame_window;
    if (D_00189E20.attack_cooldown) break;
    if (!(D_00189E20.state < 2 || (D_00189E20.state == 4 && D_00189E20.grounded)))
        break;
    if (D_00189E20.mode != 1) {
        frame_window = D_00189E20.input_window;
        action = 9;
        action = action < frame_window ? 10 : frame_window;
        if (!func_L00_0032EF10(mask, action, &scratch.detach_age)) break;
        if (D_00189E20.object) {
            func_US2_L00_002C4560(31, 1);
            if (D_00189E20.object) func_002E5CF8(0, 0, D_00189E20.object);
        }
    }
    break;
    }
    }

    if (D_00189E20.frame == previous_frame && D_001A7B08[0x26] && D_001A7390[3] == 54 &&
        D_00189E20.mode != 29 && D_00189E20.mode != 1 &&
        (D_00189E20.motion_flags & 0xffffffff00000000ULL) == 0) {
        func_00282948(&D_L00_001A7CC4);
        if (D_L00_001A7CC4 &&
            (D_00189E20.state < 2 || D_00189E20.state == 12 ||
             ((D_00189E20.state == 2 || D_00189E20.state == 4) && D_00189E20.action_ready)) &&
            (D_00138180.buttons.both & 0x800000008ULL) == 0x800000008ULL)
            func_US2_L00_002C4560(123, 1);
        if (D_00138180.buttons.word.pressed & 8) D_L00_001A7CC4 = 30;
    }
    return D_00189E20.frame < previous_frame;
}
