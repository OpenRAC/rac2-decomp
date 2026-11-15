#include "names.h"
/* func_PAL_L23_0041B350, the PAL copy of func_L23_00416388: the same C, where the hero
 * state written in state 4 becomes 8, the three frame counts are scaled to 50 Hz and the
 * age limit 40 becomes 33. Level 23 boss state update: a 21-way state switch, shared
 * cleanup and the attached-object tables. "Boss" is inferred from its behaviour. It reads
 * $gp data (hence -G8) and has its own jump table and constants, so it lives in a unit of
 * its own.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct {
    char prefix[0x18]; u8 enabled, count, kind;
    char reserved[0x65]; u8 payload[1];
} DispatchContext;
typedef struct LvlSlotNode { char prefix[0x1c]; struct LvlSlotNode *next; } LvlSlotNode;
typedef struct LvlSlotCtx { char prefix[0x50]; LvlSlotNode *head; } LvlSlotCtx;
extern unsigned char g_hero_state[];
extern char g_hero_position[];
/* A partial resident view; the external byte array keeps its unknown full extent. */
typedef struct {
    u8 prefix[0x80];
    float position[4];
    u8 middle0[0x150];
    short state1e0;
    u8 middle1[0x168e];
    struct LvlSlotNode *slotList;
    u8 middle2[8];
    int slotCount;
    u8 middle3[0xa10];
    char *player;
    int field2294;
} ResidentHeroView;
extern u8 *D_L23_00259560[];
extern float D_L23_001B36A0[] __attribute__((sda));
extern float D_L23_001B36A4[] __attribute__((sda));
extern int D_L23_001B36AC[] __attribute__((sda));
extern int D_L23_001B3710[] __attribute__((sda));
extern int D_L23_001B3714[] __attribute__((sda));
extern int D_L23_001B3718[] __attribute__((sda));
extern float D_L23_001B36C0[4] __attribute__((sda));
extern float D_L23_001B36D0[4] __attribute__((sda));
extern float D_L23_001B3760[4] __attribute__((sda));
extern float D_L23_001B3770[4] __attribute__((sda));
extern float D_L23_001B3860[4] __attribute__((sda));
extern float D_L23_001B3880[4] __attribute__((sda));
extern float g_camera_l23_position[];
extern Quad D_L23_001BA870[] NOT_SDA;
extern Quad D_L23_001C87C0 NOT_SDA;
extern Quad D_L23_001C87D0 NOT_SDA;
extern float D_L23_001B13D8 __attribute__((sda));
extern float D_L23_001B13DC __attribute__((sda));
extern float D_L23_001B13E0 __attribute__((sda));
extern int D_L23_001B13E4 __attribute__((sda));
extern int D_L23_001B13EC __attribute__((sda));
extern int D_L23_001B140C __attribute__((sda));
extern float D_L23_001B1410 __attribute__((sda));
extern float D_L23_001B1420 __attribute__((sda));
extern int D_L23_001B1424 __attribute__((sda));
extern int D_L23_001B1428 __attribute__((sda));
extern int D_L23_001B142C __attribute__((sda));
extern int D_L23_001B1430 __attribute__((sda));
extern u8 *g_mothership_boss_moby __attribute__((sda));
extern float D_L23_001B1488 __attribute__((sda));
extern float D_L23_001B148C __attribute__((sda));
extern float D_L23_001B1494 __attribute__((sda));
extern float D_L23_001B1498 __attribute__((sda));
extern float D_L23_001B14C4 __attribute__((sda));
extern float D_L23_001B14C8 __attribute__((sda));
extern float D_L23_001B14CC __attribute__((sda));
extern float D_L23_001B14D0 __attribute__((sda));
extern float D_L23_001B14D4 __attribute__((sda));
extern int D_L23_001B14D8 __attribute__((sda));
extern float D_L23_001B14E0 __attribute__((sda));
extern float D_L23_001B14E4 __attribute__((sda));
extern int D_L23_001B14EC __attribute__((sda));
extern int D_L23_001B14F8 __attribute__((sda));
extern float D_L23_001B1500 __attribute__((sda));
extern int D_L23_001B15BC __attribute__((sda));
extern float D_L23_001B1600 __attribute__((sda));
extern float D_L23_001B1604 __attribute__((sda));
extern float D_L23_001B1634 __attribute__((sda));
extern int D_L23_001B1638 __attribute__((sda));
extern int D_L23_001B1648 __attribute__((sda));
extern int D_L23_001B164C __attribute__((sda));
extern float D_L23_001B168C __attribute__((sda));
extern int D_L23_001B1694 __attribute__((sda));
extern float D_L23_001B36FC __attribute__((sda));
extern int D_L23_001B3758[] __attribute__((sda));
extern int D_L23_001B3780 __attribute__((sda));

extern int math_fast_float_d(char *);
extern void FastVecScale(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern void FastVecSub(char *, char *, char *);
extern float FastVecLength(char *);
extern float fast_vec_dist(char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern float gravity_get_center_distance(char *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void moby_transform_joint_point(char *, int, char *);
extern void AttachManipulator(u8 *, unsigned int, u8 *);
extern void moby_set_state(u8 *, int, int);
extern float math_random_float_range(float, float);
extern int flag_set_first_pending(u8 *);
extern void mat_get_euler_angles(float *, float *);
extern int PlayMobySound(int, int, char *);
extern void snd_stop_voice(int);
extern int moby_dispatch_action_by_kind(void *, DispatchContext *);
extern void func_PAL_L00_002AF6C0(void);
extern void release_moby_animation_slot(LvlSlotCtx *, LvlSlotNode **);
extern void moby_store_position_private(u8 *, void *);
extern int player_slot_has_object(unsigned int);
extern int charged_shot_get_for_owner(int);
extern void charged_shot_release(int, int);
extern int queue_copy_record_by_index(unsigned int);
extern int moby_check_target_point_from_offset(char *, void *);
extern void func_PAL_L23_004207B8(char *);
extern void mothership_project_point_onto_surface(char *, float);
extern void mothership_update_gun_pick_target(char *);
extern void mothership_tick_timers(char *);
extern void mothership_relatch_first_measure(char *, float *);
extern void mothership_relatch_second_measure(char *, float *);
extern void mothership_mark_held(char *);
extern void mothership_set_timer_value(float);
extern void mothership_disable_part_flags(char *);
extern void mothership_free_effect_handles(void);
extern void func_PAL_L23_004206A8(char *);
extern void mothership_clear_measure_flags(char *);
extern void func_PAL_L23_00420578(char *);
extern void mothership_release_effect_handles(char *);
/* Action-helper inputs were checked against retail. Their discarded result
   declarations remain hypotheses where no deliberate result bank is observable. */
extern void func_PAL_L23_0041C820(u8 *);
extern void func_PAL_L23_0041D1A8(char *);
extern void func_PAL_L23_0041D738(char *, float);
extern void func_PAL_L23_0041EDC8(char *);
extern int func_PAL_L23_0041F0D8(char *, char *);
extern int func_PAL_L23_0041F458(char *, char *);
extern void func_PAL_L23_0041F840(char *);
extern void boss_drift_along_path(char *);
extern void func_PAL_L23_004211C8(char *);
extern void boss_update_effect_pools(char *);
extern void func_PAL_L23_004225D0(char *);
extern void object_copy_vector_to_selected(char *);
extern void cam_set_state_rotation(char *);
extern void SetCamera5Pose(char *, char *, int, int, void *);
extern char *func_PAL_L00_003FB330(char *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void FadeToBlack(int);
extern void moby_copy_joint_transform_to_object(u8 *, char *, int, int);
extern void func_PAL_L00_002B9CD8(char *, char *, int, int);
extern int func_PAL_L22_002C99C8(int, int);
extern char *effect_create_attached(char *, char *);
extern void build_axis_rotation_quaternion(char *, int, float);

/* Measured accesses to the boss's private state, not a claim about its complete type:
   each one is a member of the state structure. */
typedef struct { int value; } StateInt;
typedef struct { float value; } StateFloat;
typedef struct { u8 value; } StateByte;
typedef struct { char *value; } StatePointer;
/* The five attached objects listed at state + 0x358. */
typedef struct { char *entry[5]; } LinkTable;
#define S32(o) (((StateInt *)(state + (o)))->value)
#define SF(o) (((StateFloat *)(state + (o)))->value)
#define SB(o) (((StateByte *)(state + (o)))->value)
#define SP(o) (((StatePointer *)(state + (o)))->value)
#define FLAGS(p) (*(unsigned short *)((p) + 0x34))
#define AGE (*(unsigned short *)(object + 0x96))

void func_PAL_L23_0041B350(u8 *object)
{
    char direction[16] __attribute__((aligned(16)));
    float jointMatrix[16] __attribute__((aligned(16)));
    char jointOffset[16] __attribute__((aligned(16)));
    char blendedPosition[16] __attribute__((aligned(16)));
    char localPosition[16] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    char *jointPosition;
    char *enemy;
    float height, distance;
    unsigned int mode;
    int wasActive;

    func_PAL_L23_0041C820(object);
    if (D_L23_001B1424 > 200)
        return;
    D_L23_001B1410 = 0.0f;
    math_fast_float_d((char *)D_L23_001B3714);
    wasActive = S32(0x604);
    D_L23_001B13EC = wasActive != 0;
    if (!wasActive && S32(0x60c) != -1)
        D_L23_001B1430 = 1;
    else
        D_L23_001B1430 = 0;
    if (!g_mothership_boss_moby)
        return;
    func_PAL_L23_004207B8((char *)object);
    S32(0x604) = 0;
    FastVecScale((char *)D_L23_001B36C0, (((ResidentHeroView *)g_hero_state)->player) + 0xe0, D_L23_001B1488);
    FastVecAdd((char *)D_L23_001B36C0, (char *)D_L23_001B36C0, ((char *)((ResidentHeroView *)g_hero_state)->position));
    FastVecScale((char *)D_L23_001B36D0, (((ResidentHeroView *)g_hero_state)->player) + 0xe0, D_L23_001B148C);
    FastVecAdd((char *)D_L23_001B36D0, (char *)D_L23_001B36D0, ((char *)((ResidentHeroView *)g_hero_state)->position));
    qcopy(state+(0x3f0),((char *)((ResidentHeroView *)g_hero_state)->position));
    mothership_project_point_onto_surface(state + 0x3f0, 0.0f);
    qcopy(state+(0x3e0),object + 0x10);
    mothership_project_point_onto_surface(state + 0x3e0, 0.0f);
    {
        float playerHeight = gravity_get_center_distance(((char *)((ResidentHeroView *)g_hero_state)->position)) - D_L23_001B36A4[0];
        SF(0x5c0) = playerHeight;
        D_L23_001B3710[0] = SF(0x588) < playerHeight;
    }
    FastVecSub(direction, state + 0x3f0, state + 0x3e0);
    SF(0x5b8) = FastVecLength(direction);
    mothership_update_gun_pick_target((char *)object);
    SF(0x5bc) = fast_vec_dist(((char *)object + 0x10), ((char *)((ResidentHeroView *)g_hero_state)->position));
    moby_transform_joint_to_world((char *)object, 0x2a, jointOffset);
    moby_transform_joint_point((char *)object, 0x27, (char *)jointMatrix);
    FastVecScale((char *)D_L23_001B3860, (char *)jointMatrix, D_L23_001B1600);
    FastVecAdd((char *)D_L23_001B3860, (char *)D_L23_001B3860, jointOffset);
    jointPosition = (char *)jointMatrix + 0x30;
    FastVecSub(blendedPosition, (char *)D_L23_001B36C0, jointPosition);
    vec_scale_to_length(blendedPosition, blendedPosition, D_L23_001B1604);
    FastVecAdd((char *)D_L23_001B3880, jointPosition, blendedPosition);
    SB(0x404) = 0;
    if (SF(0x5bc) < D_L23_001B1634)
        SB(0x404) = !CollLine(D_L23_001B3880, D_L23_001B36C0, 0x10, (((ResidentHeroView *)g_hero_state)->player), 0);
    if (!(D_L23_001B1648 / 2 < D_L23_001B36AC[0])) {
        math_fast_float_d((char *)&D_L23_001B142C);
        if (object[0x20] == 7 &&
            (!SB(0x404) || !object[0x31] || D_L23_001B14E0 + 40.0f < SF(0x5bc)) &&
            !D_L23_001B142C && !S32(0x590)) {
            D_L23_001B142C = D_L23_001B1428;
            moby_set_state(D_L23_00259560[D_L23_001B164C], 6, 0);
            D_L23_001B164C = (D_L23_001B164C + 1) % 25;
        }
    }
    SB(0x405) = 0;
    mode = object[0x20];
    if (mode != 4 && (SF(0x5bc) < D_L23_001B1634 || mode == 16) &&
        (SF(0x5b8) >= D_L23_001B168C || SF(0x5c0) <= SF(0x588)))
        SB(0x405) = moby_check_target_point_from_offset((char *)object, g_hero_position);
    mode = object[0x20];
    switch (mode) {
    case 0: goto state_default;
    case 4: goto state4;
    case 2: goto state2;
    case 3: goto state3;
    case 1: goto state1;
    case 7: goto state7;
    case 8: goto state8;
    case 9: goto state9;
    case 10: goto state10;
    case 11: goto state11;
    case 13: goto state13;
    case 14: goto state14;
    case 15: goto state15;
    case 12: goto state12;
    case 19: goto state19;
    case 5: goto state5;
    case 6: goto state6;
    case 16: goto state16;
    case 20: goto state20;
    default: goto state_default;
    }
state4:
    mothership_disable_part_flags((char *)object);
    ((ResidentHeroView *)g_hero_state)->state1e0 = 8;
    if (flag_set_first_pending(object)) {
        mothership_free_effect_handles();
        FadeToBlack(D_L23_001B13E4);
    } else {
        char transform[64] __attribute__((aligned(16)));
        char secondPosition[16] __attribute__((aligned(16)));
        char thirdPosition[16] __attribute__((aligned(16)));

        if (D_L23_001B13E4 / 2 < AGE) {
            func_PAL_L23_004225D0((char *)object);
        } else if (AGE == D_L23_001B13E4 / 2 - 4) {
            FadeToBlack(1);
            qcopy(transform+0x00,&D_L23_001BA870[0]);
            qcopy(transform+0x10,&D_L23_001BA870[1]);
            qcopy(transform+0x20,&D_L23_001BA870[2]);
            qzero_nc(transform + 0x30);
            mat_get_euler_angles((float *)transform, (float *)localPosition);
            SetCamera5Pose((char *)g_camera_l23_position, localPosition, 1, 0, 0);
        } else if (D_L23_001B13E4 / 2 - 4 < AGE) {
            FadeToBlack(1);
            qcopy((transform + 0x00) ,(object + 0xc0));
            qcopy((transform + 0x10) ,(object + 0xd0));
            qcopy((transform + 0x20) ,(object + 0xe0));
            qzero_nc(transform + 0x30);
            mat_get_euler_angles((float *)transform, (float *)localPosition);
            FastVecScale(secondPosition, (char *)object + 0xc0, -D_L23_001B13E0);
            FastVecAdd(secondPosition, secondPosition, ((char *)object + 0x10));
            mothership_project_point_onto_surface(secondPosition, 0.0f);
            func_PAL_L00_002B9CD8(secondPosition, localPosition, 0x6f, 0);
            cam_set_state_rotation(localPosition);
            FastVecScale(thirdPosition, (char *)object + 0xc0, -D_L23_001B13D8);
            FastVecAdd(thirdPosition, thirdPosition, ((char *)object + 0x10));
            mothership_project_point_onto_surface(thirdPosition, D_L23_001B13DC);
            object_copy_vector_to_selected(thirdPosition);
            qzero(&D_L23_001C87D0);
            qzero(&D_L23_001C87C0);
        } else {
            FadeToBlack(1);
        }
    }
    ++AGE;
    return;
state2:
    if (flag_set_first_pending(object)) {
        mothership_relatch_first_measure((char *)object, &D_L23_001B1498);
        mothership_relatch_second_measure((char *)object, &D_L23_001B14D0);
        if (!SB(0x4b1))
            AttachManipulator(object, 0x27, (u8 *)state + 0x4b0);
        SF(0x578) = 1.4726215600967407f;
        build_axis_rotation_quaternion(state + 0x4c0, 1, 1.4726215600967407f);
    }
    goto state_default;
state3:
    qcopy(state+(0x3d0),D_L23_001B3760);
    SP(0x400) = state + 0x3d0;
    func_PAL_L23_0041D738((char *)object, SF(0x588));
    mothership_release_effect_handles((char *)object);
    moby_set_state(object, 7, 1);
    goto state_default;
state1:
    mothership_mark_held((char *)object);
    if (flag_set_first_pending(object)) {
        SP(0x400) = (char *)D_L23_001B3760;
        mothership_relatch_first_measure((char *)object, &D_L23_001B1498);
        mothership_relatch_second_measure((char *)object, &D_L23_001B14C4);
    }
    if (fast_vec_dist(state + 0x3e0, (char *)D_L23_001B3760) < 10.0f)
        moby_set_state(object, 3, 0);
    else
        func_PAL_L23_0041D738((char *)object, SF(0x588));
    goto state_default;
state7:
    mothership_mark_held((char *)object);
    math_fast_float_d(state + 0x608);
    if (flag_set_first_pending(object)) {
        mothership_relatch_first_measure((char *)object, &D_L23_001B1494);
        mothership_relatch_second_measure((char *)object, &D_L23_001B14C4);
        mothership_set_timer_value(D_L23_001B14E0 + math_random_float_range(5.0f, 45.0f));
    }
    if (S32(0x60c) == -1) {
        moby_set_state(object, 6, 1);
        goto state_default;
    }
    if (!(D_L23_001B1648 / 2 < D_L23_001B36AC[0]) && !S32(0x608)) {
        if (D_L23_001B3758[0] % 3 == 2)
            mothership_set_timer_value(D_L23_001B14E0);
        else
            mothership_set_timer_value(D_L23_001B14E0 + math_random_float_range(25.0f, 55.0f));
        moby_set_state(object, 8, 1);
        ++D_L23_001B3758[0];
    } else {
        boss_drift_along_path((char *)object);
        if (AGE % 480 == 0) {
            if (D_L23_001B36AC[0] < 4)
                mothership_set_timer_value(D_L23_001B14E0 + 60.0f);
            else
                mothership_set_timer_value(D_L23_001B14E0 + math_random_float_range(-4.0f, 80.0f));
        }
    }
    goto state_default;
state8:
    mothership_mark_held((char *)object);
    flag_set_first_pending(object);
    if (D_L23_001B14E4 - 6.0f <= SF(0x5b8) && SF(0x5b8) <= D_L23_001B14E4 + 6.0f)
        moby_set_state(object, 9, 1);
    else
        boss_drift_along_path((char *)object);
    goto state_default;
state9:
    if (flag_set_first_pending(object)) {
        boss_drift_along_path((char *)object);
        mothership_relatch_second_measure((char *)object, &D_L23_001B14C8);
        S32(0x598) = ((s32)D_L23_001B14EC * 5 + 2) / 6;
        PlayMobySound(6, 0, (char *)object);
    } else if (S32(0x5d8)) {
        if (S32(0x598) <= 0) {
            moby_set_state(object, 10, 1);
        } else {
            if (S32(0x598) == ((s32)D_L23_001B14EC * 5 + 2) / 6) {
                int next;
                int i;
                PlayMobySound(0, 0, (char *)object);
                next = D_L23_001B164C;
                for (i = 0; i < 4; ++i) {
                    char jointVector[16] __attribute__((aligned(16)));
                    float matrix[16] __attribute__((aligned(16)));
                    char thirdPosition[16] __attribute__((aligned(16)));
                    char extraPosition[16] __attribute__((aligned(16)));

                    enemy = (char *)D_L23_00259560[next];
                    moby_set_state((u8 *)enemy, 2, 0);
                    next = (next + 1) % 25;
                    moby_transform_joint_to_world((char *)object, i + 30, jointVector);
                    moby_transform_joint_point((char *)object, i + 30, (char *)matrix);
                    FastVecScale(localPosition, (char *)matrix + 0x20, -16.0f);
                    qcopy_nc(extraPosition, jointVector);
                    mothership_project_point_onto_surface(extraPosition, 0.0f);
                    FastVecSub(thirdPosition, extraPosition, state + 0x3e0);
                    FastVecScale(thirdPosition, thirdPosition, D_L23_001B1420);
                    FastVecAdd(localPosition, localPosition, thirdPosition);
                    FastVecAdd(jointVector, state + 0x3e0, localPosition);
                    mothership_project_point_onto_surface(jointVector, 0.0f);
                    qcopy((enemy + 0xc0) ,(object + 0xc0));
                    qcopy((enemy + 0xd0) ,(object + 0xd0));
                    qcopy((enemy + 0xe0) ,(object + 0xe0));
                    qcopy((enemy + 0x10) ,jointVector);
                }
            }
            math_fast_float_d(state + 0x598);
        }
    }
    goto state_default;
state10:
    if (S32(0x60c) == -1)
        mothership_mark_held((char *)object);
    if (flag_set_first_pending(object))
        mothership_relatch_second_measure((char *)object, &D_L23_001B14C4);
    if (SF(0x588) > D_L23_001B14CC) {
        int enable;
        int i;
        char **children;
        char **links;
        S32(0x598) = 0;
        S32(0x590) = 4;
        moby_set_state(object, 11, 1);
        enable = D_L23_001B14D8;
        links = (char **)(state + 0x358);
        children = (char **)(state + 0x36c);
        for (i = 0; i < 5; ++i) {
            if (*children) {
                qcopy_nc(*children + 0xc0, *links + 0xc0);
                qcopy_nc(*children + 0xd0, *links + 0xd0);
                qcopy_nc(*children + 0xe0, *links + 0xe0);
                qcopy_nc(*children + 0x10, *links + 0x10);
                FLAGS(*children) &= 0xbff9;
                *(int *)(*children + 0x98) = *(int *)(*(char **)(*children + 0x24) + 0x10);
                if (enable)
                    FLAGS(*children) &= 0xffbe;
            }
            ++links;
            ++children;
        }
    }
    goto state_default;
state11:
    if (flag_set_first_pending(object))
        mothership_set_timer_value(D_L23_001B14E0);
    if (S32(0x60c) == -1)
        mothership_mark_held((char *)object);
    if (S32(0x5d8) && !S32(0x598) && !S32(0x590)) {
        int i;
        char **children = (char **)(state + 0x36c);
        for (i = 0; i < 5; ++i, ++children) {
            if (*children) {
                *(int *)(*children + 0x98) = 0;
                FLAGS(*children) |= 0x41;
            }
        }
        S32(0x608) = D_L23_001B1638;
        if (object[0x31] && SB(0x404)) {
            moby_set_state(object, 13, 2);
            D_L23_001B15BC = PlayMobySound(8, 4, (char *)object);
            D_L23_001B140C = 0;
        } else {
            moby_set_state(object, 7, 1);
        }
    } else if (S32(0x590) && !S32(0x598)) {
        func_PAL_L23_0041D1A8((char *)object);
    }
    boss_drift_along_path((char *)object);
    goto state_default;
state13:
    mothership_mark_held((char *)object);
    if (AGE)
        moby_set_state(object, 14, 2);
    boss_drift_along_path((char *)object);
    goto state_default;
state14:
    mothership_mark_held((char *)object);
    if (AGE >= 33)
        moby_set_state(object, 15, 2);
    boss_drift_along_path((char *)object);
    goto state_default;
state15:
    mothership_mark_held((char *)object);
    flag_set_first_pending(object);
    if (AGE >= 33) {
        if (D_L23_001B15BC != -1) {
            snd_stop_voice(D_L23_001B15BC);
            D_L23_001B15BC = -1;
        }
        moby_set_state(object, 7, 1);
    }
    goto state_default;
state12:
    if (!S32(0x598) && !S32(0x590)) {
        moby_set_state(object, 16, 2);
        S32(0x608) = D_L23_001B1638;
    } else if (S32(0x590) && !S32(0x598)) {
        func_PAL_L23_0041D1A8((char *)object);
    }
    goto state_default;
state19:
    if (flag_set_first_pending(object)) {
        mothership_relatch_second_measure((char *)object, &D_L23_001B14D4);
    } else if (AGE > ((s32)D_L23_001B14F8 * 5 + 2) / 6) {
        moby_set_state(object, 7, 0);
    }
    if (SF(0x588) > D_L23_001B36A0[0])
        boss_drift_along_path((char *)object);
    goto state_default;
state5:
    if (flag_set_first_pending(object)) {
        SP(0x400) = (char *)D_L23_001B3770;
        mothership_relatch_first_measure((char *)object, &D_L23_001B1494);
    } else if (fast_vec_dist(state + 0x3e0, (char *)D_L23_001B3770) > 1.0f) {
        func_PAL_L23_0041D738((char *)object, SF(0x588));
    } else {
        moby_set_state(object, 17, 2);
    }
    goto state_default;
state6:
    mothership_mark_held((char *)object);
    if (flag_set_first_pending(object)) {
        SP(0x400) = (char *)D_L23_001B3760;
        mothership_relatch_first_measure((char *)object, &D_L23_001B1494);
        mothership_relatch_second_measure((char *)object, &D_L23_001B14C4);
    } else if (fast_vec_dist(state + 0x3e0, (char *)D_L23_001B3760) > 1.0f) {
        func_PAL_L23_0041D738((char *)object, SF(0x588));
    } else {
        moby_set_state(object, 16, 2);
    }
    goto state_default;
state16:
    if (flag_set_first_pending(object))
        mothership_relatch_second_measure((char *)object, &D_L23_001B14D0);
    if (D_L23_001B1500 + D_L23_001B1500 * 0.6200000047683716f < SF(0x5b8)) {
        mothership_release_effect_handles((char *)object);
        if (!S32(0x5b0)) {
            math_fast_float_d(state + 0x608);
            if (!(D_L23_001B1648 / 2 < D_L23_001B36AC[0]) && !S32(0x608)) {
                moby_set_state(object, 12, 2);
                S32(0x598) = 0;
                S32(0x590) = 4;
            }
        }
    } else if (!D_L23_001B3780) {
        if (*(float *)(*(char **)(SP(0x610) + 0x68) + 0x20) < D_L23_001B36FC ||
            SF(0x5b8) < D_L23_001B1500 * 0.5f) {
            func_PAL_L23_0041F840((char *)object);
            D_L23_001B3780 = 1;
        } else {
            math_fast_float_d(state + 0x608);
            if (!(D_L23_001B1648 / 2 < D_L23_001B36AC[0]) && !S32(0x608)) {
                moby_set_state(object, 12, 2);
                S32(0x598) = 0;
                S32(0x590) = 4;
            }
        }
    } else {
        func_PAL_L23_0041F840((char *)object);
    }
    goto state_default;
state20:
    mothership_release_effect_handles((char *)object);
    if (moby_dispatch_action_by_kind(object, (DispatchContext *)(state + 0x140)) & 1) {
        moby_set_state(object, 4, 0);
        ((ResidentHeroView *)g_hero_state)->field2294 = 0;
        func_PAL_L00_002AF6C0();
        release_moby_animation_slot((LvlSlotCtx *)(((ResidentHeroView *)g_hero_state)->player), &((ResidentHeroView *)g_hero_state)->slotList);
        ((ResidentHeroView *)g_hero_state)->slotCount = 0;
        func_PAL_L22_002C99C8(0, 1);
        D_L23_001B1694 = 0;
        return;
    }
state_default:
    S32(0x5a8) = 0;
    {
        int i;
        for (i = 0; i < 5; ++i) {
            char *child = SP(0x36c + i * 4);
            if (child && !*(unsigned short *)(child + 0x7c))
                *(unsigned short *)(child + 0x7c) = 0x3ff;
        }
    }
    boss_update_effect_pools((char *)object);
    mothership_tick_timers((char *)object);
    {
        int i;
        LinkTable *links = (LinkTable *)(state + 0x358);
        for (i = 0; i < 5; ++i) {
            if (links->entry[i]) {
                moby_copy_joint_transform_to_object(object, links->entry[i], i + 1, 0);
                FLAGS(links->entry[i]) &= 0xfff9;
                FLAGS(links->entry[i]) |= 0x4000;
            }
        }
    }
    if (SP(0x610)) {
        moby_copy_joint_transform_to_object(object, SP(0x610), 0x22, 0);
        FLAGS(SP(0x610)) &= 0xfff9;
        FLAGS(SP(0x610)) |= 0x800;
        if (S32(0x60c) == -1 && (object[0x20] == 16 || object[0x20] == 12))
            FLAGS(SP(0x610)) |= 0x4000;
        else
            FLAGS(SP(0x610)) &= 0xbfff;
    } else {
        FLAGS(object) |= 0x4000;
    }
    if (SP(0x614)) {
        moby_copy_joint_transform_to_object(object, SP(0x614), 0x22, 0);
        FLAGS(SP(0x614)) &= 0xfff9;
        FLAGS(SP(0x614)) &= 0xbfff;
        FLAGS(SP(0x614)) |= 0x100;
    }
    func_PAL_L23_0041EDC8((char *)object);
    qcopy(localPosition ,D_L23_001B36C0);
    func_PAL_L23_0041F0D8((char *)object, localPosition);
    func_PAL_L23_0041F458((char *)object, localPosition);
    func_PAL_L23_004211C8((char *)object);
    if (!SP(0x40c))
        SP(0x40c) = effect_create_attached((char *)object, ((char *)object + 0x10));
    else
        moby_store_position_private((u8 *)SP(0x40c), ((char *)object + 0x10));
    func_PAL_L23_004206A8((char *)object);
    if (D_L23_001B1410 != 0.0f)
        func_PAL_L23_00420578((char *)object);
    else
        mothership_clear_measure_flags((char *)object);
    if (player_slot_has_object((unsigned int)(((ResidentHeroView *)g_hero_state)->player)) && D_L23_001B3780 &&
        (object[0x20] == 16 || object[0x20] == 12) && D_L23_001B1500 < SF(0x5bc)) {
        char *attachment = (char *)charged_shot_get_for_owner((int)(((ResidentHeroView *)g_hero_state)->player)) + 0x10;
        height = gravity_get_center_distance(attachment) - D_L23_001B36A4[0];
        distance = fast_vec_dist(attachment, (char *)D_L23_001B3760);
        if (distance < D_L23_001B1500 * 0.6f && height < D_L23_001B14D0 - 2.0f) {
            func_PAL_L00_003FB330(attachment, 0, 15, 10, 15, 15, 15, 1, 2.0f, 20.0f, 0, 0, 0, 0);
            charged_shot_release((int)(((ResidentHeroView *)g_hero_state)->player), 1);
        }
    }
    math_fast_float_d((char *)&D_L23_001B3718[0]);
    if (D_L23_001B3718[0])
        queue_copy_record_by_index(0x2b);
}
