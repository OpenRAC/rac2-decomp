#include "include_asm.h"
#include "names.h"

extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float FastVecLength(float *);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern void ref_L03_003C4240_00(unsigned char *, float);
extern void ref_L03_003C4240_01(unsigned char *, void *, int, float, float, float);
extern int ref_L03_003C4240_02(void *, void *, void *);
extern void ref_L03_003C4240_03(void *, void *);
extern float ref_L03_003C4240_04 __attribute__((sda));
extern float ref_L03_003C4240_05 __attribute__((sda));

/* Turns the object with its state: it stops when the state has no time left, otherwise it
   spreads the turn over the frame and lets the state and the object react to it. */
void moby_turn_toward_move_direction_pal(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *target;
    float value;
    float length;

    value = FastVecLength((float *)(state + 0x1B0));
    if (value <= 0.0f)
        return;
    length = FastVecLength((float *)(state + 0x1B0));
    if (length > 0.020000001f) {
        value = mat_fast_helper_a(*(float *)(state + 0x1B0), *(float *)(state + 0x1B4));
        value = FastAddRotations(value, 3.14159274f);
        ref_L03_003C4240_00(object, value);
    }
    ref_L03_003C4240_01(object, object + 0x10, 0x10, *(float *)(object + 0xF8),
                        ref_L03_003C4240_05 * 0.020000001f,
                        ref_L03_003C4240_04 * 0.00040000002f);
    ref_L03_003C4240_02(*(void **)(state + 0x220), object + 0x10, state + 0x368);
    target = *(unsigned char **)(state + 0x194);
    if (target != 0) {
        if (*(short *)(target + 0xAA) == 0x940 /* moby class 2368 */ || *(short *)(target + 0xAA) == 0x93C /* moby class 2364 */ ||
            *(short *)(target + 0xAA) == 0x964 /* moby class 2404 */)
            ref_L03_003C4240_03(*(unsigned char **)(state + 0x194), object + 0x10);
    }
}

#include "common.h"
extern char *moby_get_private_value_2(u8 *);
extern float math_fabs(float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_clamp_length(float *, float);
extern float g_moby_l03_push_scale __attribute__((sda));
extern float g_moby_push_clamp __attribute__((sda));

/* Pushes the object toward a target point by adding a scaled offset to its drift velocity. (PAL: 50 Hz scaling) */
void moby_push_toward_target_pal(u8 *object, void *target)
{
    float delta[4];
    u8 *state;
    u8 *attachment;
    if (object[0x20] != 4 && object[0x20] != 2)
        return;
    state = *(u8 **)(object + 0x68);
    if (*(u8 **)(state + 0x198) != 0) {
        attachment = (u8 *)moby_get_private_value_2(*(u8 **)(state + 0x198));
        if (attachment != 0 && 0.002f < math_fabs(*(float *)(attachment + 0x18)))
            return;
    }
    FastVecSub(delta, object + 0x10, target);
    delta[2] = 0.0f;
    vec_scale_to_length(delta, delta, (g_moby_l03_push_scale + g_moby_l03_push_scale) * 0.00040000002f);
    FastVecAdd(state + 0x1B0, state + 0x1B0, delta);
    vec_clamp_length((float *)(state + 0x1B0), g_moby_push_clamp * 0.020000001f);
}

extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern void gfx_add_draw_callback_first(void *, void *);
extern void part_spawn_at_attachment_points(unsigned char *);
extern void *ref_L03_003C4578_00[];
extern int ref_L03_003C4578_01 __attribute__((sda));
extern int ref_L03_003C4578_02[3] __attribute__((sda));
extern float ref_L03_003C4578_03 __attribute__((sda));
extern int ref_L03_003C4578_04 __attribute__((sda));
extern int ref_L03_003C4578_05[3] __attribute__((sda));
extern float ref_L03_003C4578_06 __attribute__((sda));
extern float ref_L03_003C4578_07 __attribute__((sda));
extern int ref_L03_003C4578_08 __attribute__((sda));
extern int ref_L03_003C4578_09[3] __attribute__((sda));
extern int ref_L03_003C4578_10 __attribute__((sda));
extern int ref_L03_003C4578_11[3] __attribute__((sda));
extern int ref_L03_003C4578_12 __attribute__((sda));
extern int ref_L03_003C4578_13[3] __attribute__((sda));
extern int ref_L03_003C4578_14 __attribute__((sda));
extern int ref_L03_003C4578_15[3] __attribute__((sda));
extern int ref_L03_003C4578_16 __attribute__((sda));
extern int ref_L03_003C4578_17[3] __attribute__((sda));
extern float ref_L03_003C4578_18 __attribute__((sda));
extern int ref_L03_003C4578_19;
extern unsigned short *ref_L03_003C4578_20[];
extern int ref_L03_003C4578_21 __attribute__((sda));
extern unsigned char *ref_L03_003C4578_22[3] __attribute__((sda));
typedef struct {
    unsigned char pad0[0x35C];
    float phase;
    unsigned char pad1[0x378 - 0x360];
    int stamp;
} L03State;
typedef struct {
    unsigned char pad0[0x21];
    unsigned char group;
    unsigned char pad1[0x31 - 0x22];
    unsigned char live;
    unsigned char pad2[0x68 - 0x32];
    L03State *state;
    unsigned char pad3[0x78 - 0x6C];
    int tint;
    unsigned char pad4[0x95 - 0x7C];
    unsigned char kind;
} L03Obj;

/* Per object kind (object->kind: 1 and 7, 8, 2..6, else) it picks a pair of ids and a scale, turns
   the object's phase (the float at 0x35C of its state) by that scale, stores the result of
   func_00283D38 on the pair in object->tint, and, when the state's stamp is not the frame counter,
   stamps the counter into the state of every entity of its group and registers
   func_L03_003C4800 for the object with func_L00_002E6CF0. The kind selects its arm through the
   level's jump table; `cases` only keeps the labels alive, and the labels are named after the
   kind that reaches them. */
void moby_pulse_tint_pal(L03Obj *object) {
    static void *cases[9] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c1, &&c8};
    L03State *state = object->state;
    int pair[2];
    float scale;
    float angle;
    float wave;
    unsigned short *id_list;
    L03Obj *other;
    unsigned int kind;

    if (object->live != 0) {
        kind = object->kind;
        if (kind < 9)
            goto *ref_L03_003C4578_00[kind];
        goto c0;
c1:
        pair[0] = ref_L03_003C4578_01;
        pair[1] = ref_L03_003C4578_02[0];
        scale = ref_L03_003C4578_03 * 0.0003490659f;
        goto join;
c8:
        pair[0] = ref_L03_003C4578_04;
        pair[1] = ref_L03_003C4578_05[0];
        scale = ref_L03_003C4578_06 * 0.0003490659f;
        goto join;
c2:
        pair[0] = ref_L03_003C4578_04;
        pair[1] = ref_L03_003C4578_05[0];
        scale = ref_L03_003C4578_07 * 0.0003490659f;
        goto join;
c3:
        pair[0] = ref_L03_003C4578_08;
        pair[1] = ref_L03_003C4578_09[0];
        scale = ref_L03_003C4578_07 * 0.0003490659f;
        goto join;
c4:
        pair[0] = ref_L03_003C4578_10;
        pair[1] = ref_L03_003C4578_11[0];
        scale = ref_L03_003C4578_07 * 0.0003490659f;
        goto join;
c5:
        pair[0] = ref_L03_003C4578_12;
        pair[1] = ref_L03_003C4578_13[0];
        scale = ref_L03_003C4578_07 * 0.0003490659f;
        goto join;
c6:
        pair[0] = ref_L03_003C4578_14;
        pair[1] = ref_L03_003C4578_15[0];
        scale = ref_L03_003C4578_07 * 0.0003490659f;
        goto join;
c0:
        pair[0] = ref_L03_003C4578_16;
        pair[1] = ref_L03_003C4578_17[0];
        scale = ref_L03_003C4578_18 * 0.0003490659f;
join:
        angle = FastAddRotations(state->phase, scale);
        state->phase = angle;
        wave = math_fast_sin_or_cos_b(angle);
        object->tint = FastTweenColor(pair[0], pair[1], wave * 0.5f + 0.5f);
        if (state->stamp != ref_L03_003C4578_19) {
            for (id_list = ref_L03_003C4578_20[object->group];
                 object->group != 0xFF && object->group <= ref_L03_003C4578_21 && id_list != 0 &&
                 ((id_list != 0 && (short)id_list[-1] >= 0) || id_list == ref_L03_003C4578_20[object->group]);
                 id_list++) {
                other = (L03Obj *)(ref_L03_003C4578_22[0] + ((*id_list & 0x7FFF) << 8));
                if (other == 0)
                    break;
                other->state->stamp = ref_L03_003C4578_19;
            }
            gfx_add_draw_callback_first(part_spawn_at_attachment_points, object);
        }
    }
}
