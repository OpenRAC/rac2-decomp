#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));
typedef union { Vector128 bits; float f[4]; } __attribute__((aligned(16))) BeamVector;
typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { float vertices[4][4]; unsigned int colors[4]; float uv[4][2]; u64 registers[4]; } __attribute__((aligned(16))) BeamQuad;

extern char *CreateMoby(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void SpawnBurstEffects(char *, char *);
extern char D_L00_001B8C80[];
typedef struct SpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra;
} SpawnState;
typedef struct SpawnObject {
    char pad00[0x10];
    float position[4];
    char status;
    char pad21[0xf];
    unsigned char alpha;
    char pad31;
    short color;
    char pad34[0x34];
    SpawnState *state;
    char pad6c[0x54];
    float forward[4], right[4], up[4];
} SpawnObject;


#include "include_asm.h"

extern int func_00282978_5(char *handle);

extern void func_0029F338_2(char *object);

#ifndef RAC2_T_NODE16_F23626AD8
#define RAC2_T_NODE16_F23626AD8
typedef struct Node16_F23626ad8 Node16_F23626ad8;
#endif

#ifndef RAC2_T_NODE104_F23626AD8
#define RAC2_T_NODE104_F23626AD8
typedef struct Node104_F23626ad8 Node104_F23626ad8;
#endif

#ifndef RAC2_T_NODE24_F23626AD8
#define RAC2_T_NODE24_F23626AD8
typedef struct Node24_F23626ad8 Node24_F23626ad8;
#endif

struct Node16_F23626ad8 {
    short h0;
    unsigned char pad2[2];
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
};

struct Node104_F23626ad8 {
    unsigned char pad0[16];
    Node16_F23626ad8 *p16;
};

struct Node24_F23626ad8 {
    unsigned char pad0[52];
    unsigned short h52;
    unsigned char pad54[50];
    Node104_F23626ad8 *p104;
};

#ifndef RAC2_T_OBJ_F23626AD8
#define RAC2_T_OBJ_F23626AD8
typedef struct Obj_F23626ad8 {
    unsigned char pad0[4];
    union {
        int f4;
        struct {
            unsigned char b4;
            unsigned char b5;
            short h6;
        } b;
    } u;
    unsigned char pad8[16];
    Node24_F23626ad8 *f24;
} Obj_F23626ad8;
#endif

extern void set_moby_color(Node24_F23626ad8 *a, unsigned char b, unsigned char c, unsigned char d);

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

extern void cam_compute_view_direction(char *a0, void *a1, int a2);

extern void FastVecScale(void *a0, void *a1, float f12);

extern void lightning_arcs_update_owned(char *a0);

extern char ref_L00_004117B8_00[];

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

/* func_L00_004096B0 is defined in L00_004096B0-sweep-g8.c. */

/* func_L00_00409E48 is defined in L00_004096B0-g8.c. */

/* func_L00_0040A4A8 is defined in L00_0040A4A8.c. */


/* func_L00_0040B098 is defined in L00_0040B098.c. */

/* func_L00_0040B2C0 is defined in L00_0040B2C0-flags-g8.c. */




/* func_L00_0040BA30 is defined in L00_0040BA30-g8.c. */

/* func_L00_0040C7D8 is defined in L00_0040C7D8-g8.c. */

/* func_L00_0040CCA0 is in L00_0040CCA0.c. */

/* func_L00_0040D058 is defined in L00_0040D058-ribbon.c. */

/* Creates a glowing flare effect facing the camera at a position, with the given size and colour. It also gives the camera a small shake when the flare is close. */
char *flare_spawn(float size, char *position, int trigger, int kind, int red, int green, int blue, int enabled, int flags, int extra, int control)
{
    Vector128 direction[1], up[1], sphere[1], difference[1];
    char *object = CreateMoby(0xf6d /* moby class 3949 */);
    SpawnState *state;
    SpawnObject *moby_view;
    char *camera;
    float angle;
    if (object != 0) {
        moby_view = (SpawnObject *)object;
        state = moby_view->state;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        camera = D_L00_001B8C80 + 0x140;
        FastVecSub(direction, camera, object + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        FastVecCross(object + 0xd0, object + 0xc0, up);
        vec_scale_to_length(object + 0xd0, object + 0xd0, 1.0f);
        FastVecCross(object + 0xe0, object + 0xd0, object + 0xc0);
        moby_view->forward[3] = moby_view->right[3] = moby_view->up[3] = 0.0f;
        /* Both countdowns start together. */
        state->timer = state->life = 60;
        state->outer = size + size;
        state->inner = size*4.0f;
        state->kind = kind;
        state->red = red;
        state->green = green;
        state->blue = blue;
        state->enabled = enabled;
        state->extra = extra;
        state->control = control;
        state->flags = flags;
        state->size = size;
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (fast_vec_dist(position, camera) < 48.0f && trigger != 0) {
                char *manager = camera - 0x140;
                *(int *)(manager + 0x16c) = 0;
                *(volatile float *)(manager + 0x160) = 0.075f;
                *(volatile int *)(manager + 0x168) = 40;
            }
            if (state->flags != 0) {
                FastVecSub(difference, object + 0x10, D_L00_001B8C80 + 0x140);
                vec_scale_to_length(difference, difference, 1.0f);
                angle = math_fast_angle_helper(FastVecDot(difference, D_L00_001B8C80 + 0x370));
                if (1.5707963705f - angle < 0.4537856579f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        SpawnBurstEffects(object, (char *)up);
    }
    return object;
}


/* Tests the handle cached in the object and, while the handle reports itself already released, drops the next sub-handle, otherwise runs the object's destroy helper. */
/* Per-frame update for the flare effect (moby class 3949): waits for its handle to be released, then removes the object. */
void flare_update(char *object)
{
    char *handle = *(char **)(object + 104);

    if (func_00282978_5(handle) == 0)
        func_00282978_5(handle + 4);
    else
        func_0029F338_2(object);
}

/* func_L00_0040DF58 is in L00_0040DF58-g8.c. */

/* func_L00_0040F6A0 is in L00_0040F6A0-g16.c. */

/* func_L00_00410178 is defined in L00_00410178.c. */



/* func_L00_00410690 is defined in L00_00410690-g64.c. */

/* Reads the halfword at +0x1A of the object's node and grades it: 4 at or above 90, 3 above 60,
   2 above 30, else 1. The two lower bounds stay in variables, which is what keeps them in
   registers instead of an immediate compare. */
/* Turns the object's charge level into a grade from 1 (low) to 4 (full). */
int weapon_get_charge_grade(char *object)
{
    int value = *(short *)(*(int *)(object + 0x68) + 0x1A);
    int upper = 0x3C;
    int lower = 0x1E;
    int result = 1;

    if (value >= 0x5A)
        result = 4;
    else if (upper < value)
        result = 3;
    else if (lower < value)
        result = 2;
    return result;
}

/* func_L00_00410888 is defined in L00_00410888-g8.c. */

/* Does nothing. Several object classes use it as an empty update. */
void moby_update_empty_alt(void)
{
}

/* func_L00_00410D20 is defined in L00_00410D20.c. */

/* Calls a helper with a referenced node and three identity bytes of the object, then copies those bytes into a linked record when a node flag bit is set and the record exists with a non-zero leading short. */
/* Applies the slot's colour to its target, and copies it into the target's linked record when that record allows it. */
void target_apply_slot_color(Obj_F23626ad8 *slot)
{
    Node24_F23626ad8 *target;
    Node16_F23626ad8 *record;
    int value;

    set_moby_color(slot->f24, slot->u.b.b4, slot->u.b.b5, slot->u.b.h6);
    target = slot->f24;
    if ((target->h52 & 0x20) == 0)
        return;
    record = ((Node104_F23626ad8 *)target->p104)->p16;
    if (record == 0)
        return;
    if (record->h0 == 0)
        return;
    record->b4 = slot->u.b.b4;
    record->b5 = slot->u.f4 >> 8;
    value = slot->u.b.h6;
    record->b6 = value;
}



/* func_L00_004115E8 is defined in L00_004096B0-g8.c. */

/* Walks the thirty records of the level's block and, for every record whose +0x18 pointer is
   set, folds it into a sixteen-byte buffer: the record's own transform, then the scale of its
   +0x0C word, then its first three words added to the buffer. The block's address differs
   from level to level, so it takes a per-level name. */
/* Updates the positions of the 30 tracked targets, then redraws the lightning arcs of this object. */
void tracked_target_offsets_update(char *moby)
{
    char *slot = ref_L00_004117B8_00;
    char *owner = moby;
    char *target;
    float offset[4];
    int i;

    for (i = 0x1D; i >= 0; i--) {
        if (*(char **)(slot + 0x18) != 0) {
            target = *(char **)(slot + 0x18);
            cam_compute_view_direction(target + 0x10, offset, 1);
            target = *(char **)(slot + 0x18);
            FastVecScale(offset, offset, *(float *)(target + 0xC) * 0.0008300250046886504f);
            target = *(char **)(slot + 0x18);
            offset[0] += *(float *)(target + 0) * 0.0009764999849721789f;
            offset[1] += *(float *)(target + 4) * 0.0009764999849721789f;
            offset[2] += *(float *)(target + 8) * 0.0009764999849721789f;
        }
        slot = slot + 0x30;
    }
    lightning_arcs_update_owned(owner);
}


extern char D_L00_00256BC0[];
extern char *moby_get_private_value_0(char *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float), IntToFloat(int);
extern void FastVecAdd(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern int math_fast_float_d(void *);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern void part_emit_spark_particle_pairs(void *, int, int);
/* Moves each of this object's 48 flying pieces toward its target. When a piece arrives it hits the target with damage and sparks, and the piece is freed. */
void tumbling_pieces_update(char *moby)
{
    Vector128 offset_vec[1];
    char hit_event[48];
    char *record, *active_record, *link_data, *current_pos, *start_pos;
    int i;
    float fraction, amount;
    for (i = 0; i < 48; i++) {
        record = D_L00_00256BC0 + i * 0xd0;
        if (*(char **)(record + 0xac) != moby) continue;
        current_pos = record + 0x20;
        qcopy(current_pos, record + 0x40);
        if (*(char **)(record + 0xb4)) {
            link_data = moby_get_private_value_0(*(char **)(record + 0xb4));
            if (link_data) {
                cam_compute_view_direction(*(char **)(record + 0xb4) + 0x10, offset_vec, 1);
                FastVecScale(offset_vec, offset_vec, *(float *)(link_data + 0x10));
                FastVecAdd(offset_vec, offset_vec, *(char **)(record + 0xb4) + 0x10);
                FastVecAdd(current_pos, offset_vec, current_pos);
            } else qcopy(current_pos, *(char **)(record + 0xb4) + 0x10);
        }
        if (*(int *)(record + 0xb8)) {
            *(float *)(record + 96) = FastAddRotations(*(float *)(record + 96), *(float *)(record + 108) * 100.0f);
            *(float *)(record + 100) = FastAddRotations(*(float *)(record + 100), *(float *)(record + 112) * 100.0f);
            *(float *)(record + 104) = FastAddRotations(*(float *)(record + 104), *(float *)(record + 116) * 100.0f);
            *(float *)(record + 132) = FastAddRotations(*(float *)(record + 132), *(float *)(record + 144) * 100.0f);
            *(float *)(record + 136) = FastAddRotations(*(float *)(record + 136), *(float *)(record + 148) * 100.0f);
            *(float *)(record + 140) = FastAddRotations(*(float *)(record + 140), *(float *)(record + 152) * 100.0f);
        } else {
            *(float *)(record + 96) = FastAddRotations(*(float *)(record + 96), *(float *)(record + 108));
            *(float *)(record + 100) = FastAddRotations(*(float *)(record + 100), *(float *)(record + 112));
            *(float *)(record + 104) = FastAddRotations(*(float *)(record + 104), *(float *)(record + 116));
            *(float *)(record + 132) = FastAddRotations(*(float *)(record + 132), *(float *)(record + 144));
            *(float *)(record + 136) = FastAddRotations(*(float *)(record + 136), *(float *)(record + 148));
            *(float *)(record + 140) = FastAddRotations(*(float *)(record + 140), *(float *)(record + 152));
        }
        *(float *)(record + 0) = math_fast_sin_or_cos_a(*(float *)(record + 96)) * *(float *)(record + 120);
        *(float *)(record + 4) = math_fast_sin_or_cos_b(*(float *)(record + 100)) * *(float *)(record + 124);
        *(float *)(record + 8) = -math_fast_sin_or_cos_b(*(float *)(record + 104)) * *(float *)(record + 128);
        *(float *)(record + 16) = math_fast_sin_or_cos_a(*(float *)(record + 132)) * *(float *)(record + 156);
        *(float *)(record + 20) = math_fast_sin_or_cos_b(*(float *)(record + 136)) * *(float *)(record + 160);
        *(float *)(record + 24) = -math_fast_sin_or_cos_b(*(float *)(record + 140)) * *(float *)(record + 164);
        qcopy(record + 0x30, record + 0x50);
        if (*(char **)(record + 0xb0)) {
            link_data = moby_get_private_value_0(*(char **)(record + 0xb0));
            if (link_data) {
                cam_compute_view_direction(*(char **)(record + 0xb0) + 0x10, offset_vec, 1);
                FastVecScale(offset_vec, offset_vec, *(float *)(link_data + 0x10));
                FastVecAdd(offset_vec, offset_vec, *(char **)(record + 0xb0) + 0x10);
                FastVecAdd(record + 0x30, offset_vec, record + 0x30);
            } else qcopy(record + 0x30, *(char **)(record + 0xb0) + 0x10);
        }
        current_pos = record + 0x30;
        active_record = record;
        fraction = IntToFloat(*(int *)(active_record + 0xb8));
        fraction /= IntToFloat(*(int *)(active_record + 0xbc));
        start_pos = active_record + 0x20;
        lerp_vector(current_pos, start_pos, current_pos, 1.0f - fraction);
        if (!math_fast_float_d(active_record + 0xb8)) continue;
        if (*(int *)(*(char **)(active_record + 0xb0) + 0x98) && !*(int *)(active_record + 0xc0) && *(int *)(active_record + 0xc4)) {
            FastVecSub(offset_vec, current_pos, start_pos);
            vec_scale_to_length(offset_vec, offset_vec, 0.033333335f);
            amount = *(float *)(active_record + 0xc8);
            *(int *)(moby + 0xb8) = *(int *)(*(char **)(active_record + 0xcc) + 0x20);
            make_hit_descriptor(hit_event, moby, 0x210000, offset_vec, amount);
            hit_event[0x18] = 5;
            hit_event[0x19] = 3;
            *(short *)(hit_event + 0x1a) = *(short *)(moby + 0xaa);
            QueueMobyImpact(*(char **)(active_record + 0xb0), hit_event);
            *(int *)(active_record + 0xc0) = 1;
            part_emit_spark_particle_pairs(current_pos, 10, 1);
        }
        if (math_fast_float_d(active_record + 0xa8)) *(int *)(active_record + 0xac) = 0;
    }
}


/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void effect_reset_record(char *record)
{
    *(long long *)(record + 112) = 0LL;
    *(int *)(record + 80) = 0;
    *(int *)(record + 84) = 0;
    *(float *)(record + 88) = 1.0f;
    *(int *)(record + 92) = 0;
    *(int *)(record + 96) = 0;
    *(float *)(record + 100) = 1.0f;
    *(float *)(record + 104) = 1.0f;
    *(float *)(record + 108) = 1.0f;
    *(float *)(record + 8) = -1.0f;
    *(float *)(record + 24) = 1.0f;
    *(float *)(record + 40) = -1.0f;
    *(float *)(record + 56) = 1.0f;
    *(float *)(record + 4) = -1.0f;
    *(float *)(record + 36) = 1.0f;
    *(float *)(record + 52) = 1.0f;
    *(int *)(record + 0) = 0;
    *(int *)(record + 16) = 0;
    *(int *)(record + 32) = 0;
    *(int *)(record + 48) = 0;
    *(float *)(record + 12) = 1.0f;
    *(float *)(record + 28) = 1.0f;
    *(float *)(record + 44) = 1.0f;
    *(long long *)(record + 128) = 280993940374112LL;
    *(float *)(record + 20) = -1.0f;
    *(float *)(record + 60) = 1.0f;
}

/* func_L00_00412110 is defined in L00_00412110.c. */

/* func_L00_00412230 is defined in x-qcopy.c. */

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
/* Works out the next point of a curve from the two points before it. */
void curve_extend_from_two_points(Vec16_Fc936841d *points, int index)
{
    char delta[16];

    func_00282CF0_9(delta, (char *)&points[index - 2], (char *)&points[index - 3]);
    func_00282CC0_15((char *)&points[index - 1], (char *)&points[index - 2], delta);
}

/* func_L00_00412470 is defined in L00_00412470.c. */
