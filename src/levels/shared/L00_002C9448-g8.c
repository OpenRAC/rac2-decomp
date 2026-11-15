#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
/* Fields used here are a prefix of the resident hero state, not its total size. */
typedef struct {
    unsigned char pad_000[128];
    float position[4];
    unsigned char pad_090[8];
    float heading;
    unsigned char pad_09C[284];
    int frame;
    unsigned char pad_1BC[74];
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

/* The retail helper consumes a button mask, a history window and optional age output. */
extern int func_L00_0032EF10(u32, int, int *);
extern int func_L00_002B3248(unsigned char *);
/* Matched helper definition takes no parameters. */
extern void func_L00_002BA508(void);
extern int func_00283CF0(float);
extern void func_L00_002C42E0(int, int);
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
int func_L00_002C9448(void)
{
    struct {
        Quadword point;
        int input_age, action_age, detach_age;
    } scratch;
    int previous_frame, state;
    u32 mask;


    if (gHeroState.special_control) {
        if (gHeroState.action != 10)
            return 0;
        if (gHeroState.special_ready != 1)
            return 0;
    }
    if (gHeroState.disabled) return 0;
    if (!gHeroState.object) return 0;
    if (gHeroState.input_locked) return 0;
    if (gHeroState.control_mode != 2) return 0;

    previous_frame = gHeroState.frame;
    mask = gHeroState.buttons;
    state = gHeroState.action;
    switch (state) {
    case 10: {
    int action, difference;
    int buffered_window;
    char *object;
    AnimationRange *range;
    float threshold, movement;
    if (gHeroState.action_locked) break;
    if (gHeroState.state < 2 || (gHeroState.state == 4 && gHeroState.grounded)) {
        if (PadPressedWithin(mask, 10, &scratch.input_age)) {
            object = gHeroState.object;
            if (!object) goto clear_action;
            if (!IsMobyClass71((unsigned char *)object) || *(unsigned char *)(object + 0x20))
                goto clear_action;
            if ((gPadState.buttons.word.held & 8) ||
                ((gHeroState.mode == 1 || gHeroState.mode == 29) && gHeroState.frame >= 21)) {
                if ((gHeroState.mode == 1 || gHeroState.mode == 29) && gHeroState.frame >= 21)
                    SetupHeroAttachedObjectTransform();
                else
                    SetHeroAction_L00(21, 1);
            } else {
                SetHeroAction_L00(19, 1);
            }
            goto clear_action;
        }
        goto clear_action;
    }
    if (gHeroState.mode == 7 || gHeroState.mode == 9 || gHeroState.mode == 137 ||
        gHeroState.mode == 8 || gHeroState.mode == 6 ||
        (gHeroState.mode == 14 && gHeroState.animation_frame > 32.0f))
        goto buffered_attack;
    if ((gHeroState.mode == 11 && gHeroState.attack_mode != 3 && gHeroState.animation_frame > 18.0f) ||
        (gHeroState.mode == 11 && gHeroState.attack_mode == 3 && gHeroState.animation_frame > 20.0f))
        goto buffered_attack;
    if (gHeroState.mode == 44 || gHeroState.mode == 17)
        goto buffered_attack;
    goto ranged_attack;

buffered_attack:
    if (gHeroState.frame < 11) goto ranged_attack;
    buffered_window = 14;
    if (gHeroState.mode == 11 || gHeroState.mode == 14)
        buffered_window = 18;
    if (!PadPressedWithin(mask, buffered_window, 0)) goto clear_action;
    if ((!gHeroState.fast_attack && gHeroState.movement > 0.1f) ||
        (gHeroState.fast_attack && gHeroState.movement > 0.57f) ||
        (gHeroState.mode == 8 && gHeroState.movement > 0.57f)) {
        if (gHeroState.attack_blocked || gHeroState.attack_pending) goto clear_action;
        SetHeroAction_L00(20, 1);
    } else {
        SetHeroAction_L00(19, 1);
    }
    goto clear_action;

ranged_attack:
    if (gHeroState.state == 6) {
        range = &D_L00_0025D990[gHeroState.animation_index];
        if (gHeroState.mode == 21 && gHeroState.frame >= 31) {
            if (gHeroState.input_locked) goto check_attack_delay;
            if (gHeroState.attack_delay) goto clear_action;
            if ((float)range->trigger_frame <= gHeroState.animation_frame && (gPadState.buttons.word.held & 8) &&
                PadPressedWithin(mask, 15, 0)) {
                SetHeroAction_L00(21, 1);
                break;
            }
        }
check_attack_delay:
        if (!gHeroState.attack_delay) {
            if (!gHeroState.input_locked) {
                float frame = gHeroState.animation_frame;
                if (!((float)range->trigger_frame <= frame)) goto clear_action;
                difference = (FloatToInt(frame) - range->first_frame) * 2;
                action = difference > 0 ? difference : 1;
                action = action < 16 ? action : 15;
                if (PadPressedWithin(mask, action, 0)) {
                    if (gPadState.buttons.word.held & 8) {
                        SetHeroAction_L00(21, 1);
                        goto clear_action;
                    }
                    SetHeroAction_L00(19, 1);
                }
            }
        }
    }
clear_action:
    gHeroState.attack_pending = 0;
    break;

    }
    case 22:
    case 65:
    if (gHeroState.mode == 1 || gHeroState.mode == 29) break;
    if (!(gHeroState.state < 2 || gHeroState.state == 12 ||
          (gHeroState.state == 4 && gHeroState.grounded))) break;
    if (gHeroState.pending_action && gHeroState.pending_action != 22 && gHeroState.pending_action != 65)
        break;
    if (!(gPadState.buttons.word.held & 32) || gHeroState.input_window < 23) break;
    if (get_ammo(state)) {
        SetHeroAction_L00(131, 1);
        break;
    }
    if (gPadState.buttons.word.pressed & 32) {
        EffectDefinition *effect = &gWeaponTable_L00[gItemSlotToRecord[state]];
        PlaySoundFromClassBank(0, 0, gHeroState.owner, effect->sound);
    }
    break;

    case 46: {
    char *target;
    float direction;
    if (!(gPadState.buttons.word.pressed & mask)) break;
    if (gHeroState.aim_target) {
        gHeroState.aim_target = 0;
        break;
    }
    target = SelectBestEligibleTarget(&gHeroState, 21, 0, 20.0f, gHeroState.heading,
                              0.5235988497734069824f, 0.6981317996978759766f);
    gHeroState.aim_target = target;
    if (target) {
        qcopy(&scratch.point, target + 16);
        ((float *)&scratch.point)[2] += 0.5f;
        if (CollLine(&scratch.point, (char *)&gHeroState + 0xE0, 2, target, 0))
            gHeroState.aim_target = 0;
        else {
            char *aim_target = gHeroState.aim_target;
            direction = FastMatrixHelperA(gHeroState.position[0] - *(float *)(aim_target + 16),
                                     gHeroState.position[1] - *(float *)(aim_target + 20));
            gHeroState.target_angle = fast_subtract_rotations(*(float *)(gHeroState.aim_target + 0xF8), direction);
        }
    }
    break;

    }
    case 13: {
    int action;
    FindSwingshotNodeInFront();
    FindActiveSwingshotNode();
    FindBlueSwingshotTarget();
    action = gHeroState.extended_range ? 8 : 5;
    if (gHeroState.mode == 40) action = 11;
    if (gHeroState.mode == 39 && (gHeroState.alternate_target_ready || gHeroState.nearby_ready)) {
        if (PadPressedWithin(mask, action, 0) ||
            ((gPadState.buttons.word.held & mask) && gHeroState.input_window >= 16)) {
            SetHeroAction_L00(40, 1);
            break;
        }
    }
    if (!(gHeroState.state < 2 || gHeroState.state == 12 || gHeroState.state == 4 ||
          gHeroState.state == 2 || gHeroState.state == 30 || gHeroState.state == 5 ||
          (gHeroState.mode == 40 && gHeroState.frame >= 6) || gHeroState.mode == 29))
        break;
    if (!PadPressedWithin(mask, action, 0) &&
        (!(gPadState.buttons.word.held & mask) || gHeroState.input_window < 16)) break;
    if (gHeroState.alternate_target_ready) {
        if (gHeroState.nearby_ready) {
            if (gHeroState.alternate_distance < gHeroState.nearby_distance) gHeroState.nearby_ready = 0;
            else gHeroState.alternate_target_ready = 0;
        }
        if (gHeroState.alternate_target_ready && !gHeroState.control_lock && gHeroState.mode != 43) {
            SetHeroAction_L00(43, 1);
            break;
        }
    }
    if (gHeroState.nearby_ready && !gHeroState.control_lock) {
        SetHeroAction_L00(35, 1);
        break;
    }
    if (gHeroState.second_target_ready) {
        SetHeroAction_L00(138, 1);
        break;
    }
    break;

    }
    case 12:
    case 15:
    case 17:
    case 31: {
    int action, frame_window;
    if (!((gHeroState.state == 0 && gHeroState.mode != 29) || gHeroState.state == 1 ||
          gHeroState.state == 12 || gHeroState.state == 5 || gHeroState.state == 15 ||
          (gHeroState.state == 4 && gHeroState.alternate_ready) ||
          (gHeroState.mode == 34 && gHeroState.animation_frame > 55.0f))) break;
    if (gHeroState.changing_weapon) break;
    frame_window = gHeroState.input_window;
    action = 7;
    if (frame_window < action) action = frame_window;
    if (!PadPressedWithin(mask, action, &scratch.action_age) && !(gPadState.buttons.word.held & 32)) break;
    if (frame_window < 23) break;
    if (get_ammo(-1)) {
        if (gHeroState.state == 12 || gHeroState.state == 0 || gHeroState.mode == 3 ||
            (gHeroState.state == 1 && gHeroState.transition_progress < 0.7f)) {
            SetHeroAction_L00(34, 1);
            break;
        }
        start_equipped_item_animation();
    } else if (gHeroState.object && (gPadState.buttons.word.pressed & 32))
        PlayMobySound(0, 0, gHeroState.object);
    break;

    }
    case 53: {
    int action, frame_window;
    if (!(gHeroState.state < 2 || (gHeroState.state == 4 && gHeroState.grounded)))
        break;
    if (gHeroState.mode != 1) {
        frame_window = gHeroState.input_window;
        action = 9;
        action = action < frame_window ? 10 : frame_window;
        if (!PadPressedWithin(mask, action, &scratch.detach_age)) break;
        if (gHeroState.object) {
            SetHeroAction_L00(31, 1);
            if (gHeroState.object) PlayMobySound(0, 0, gHeroState.object);
        }
    }
    break;
    }
    }

    if (gHeroState.frame == previous_frame && D_001A7B08[0x26] && D_001A7390[3] == 54 &&
        gHeroState.mode != 29 && gHeroState.mode != 1 &&
        (gHeroState.motion_flags & 0xffffffff00000000ULL) == 0) {
        FastFloatHelperD(&D_L00_001A7CC4);
        if (D_L00_001A7CC4 &&
            (gHeroState.state < 2 || gHeroState.state == 12 ||
             ((gHeroState.state == 2 || gHeroState.state == 4) && gHeroState.action_ready)) &&
            (gPadState.buttons.both & 0x800000008ULL) == 0x800000008ULL)
            SetHeroAction_L00(123, 1);
        if (gPadState.buttons.word.pressed & 8) D_L00_001A7CC4 = 30;
    }
    return gHeroState.frame < previous_frame;
}
