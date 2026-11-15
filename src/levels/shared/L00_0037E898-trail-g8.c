#include "common.h"

/* Trail object spawners. The object's 0x68 work block and the fields below are measured
 * views; the 0xFF written to both the alpha byte and +0x32 is one constant in retail. */
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;

extern char *CreateMoby(int);
extern void moby_mark_spawned(void *);
extern void func_002A0F48(void *);
extern void euler_rotation_basis(void *, void *);
extern void moby_get_facing_direction(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void vec_clear_128(void *);
extern int slot_alloc_for_object(unsigned char *, unsigned int);
extern int part_alloc_effect_slot(void *, void *, float, float, float);

extern char *g_hero_moby[];
extern unsigned char D_00139591[];
extern int D_L00_001AEFA8 __attribute__((sda));
extern int D_L00_001AEF48 __attribute__((sda));

typedef struct {
    char pad00[0x58];
    int f58;
    char pad5C[224 - 0x5C];
} TrailEntry;
extern TrailEntry g_weapon_l00_table[];

typedef struct {
    Quadword velocity;
    Quadword basis[3];
    int f40, f44, handle;
    short f4C;
    signed char f4E;
    unsigned char f4F;
    int f50;
    int pad54;
    float f58;
    int pad5C;
    int f60, f64;
    void *owner;
    int pad6C;
    int f70;
} TrailWork;

typedef struct {
    char pad00[0x10];
    Quadword position;
    unsigned char state;
    char pad21[0xB];
    float scale;
    unsigned char alpha;
    char pad31;
    unsigned short drawMask;
    unsigned short flags;
    char pad36[0x32];
    TrailWork *work;
} TrailMoby;

/* Creates a Miniturret shot at the given position moving the given way, and turns it to face its direction. Returns null if it cannot be set up. */
char *miniturret_spawn_shot(Vector4 *position, Vector4 *velocity)
{
    Vector4 direction, forward, quaternion, axis;
    Vector4 rotation[3];
    char *object = CreateMoby(MOBY_CLASS_MINITURRET);
    TrailWork *work;
    float angle;
    if (object) {
        int initialState = 255;
        ((TrailMoby *)object)->scale *= 0.75f;
        ((TrailMoby *)object)->flags |= 0x100;
        work = ((TrailMoby *)object)->work;
        ((TrailMoby *)object)->drawMask = initialState;
        ((TrailMoby *)object)->state = 0;
        ((TrailMoby *)object)->alpha = initialState;
        qcopy(&((TrailMoby *)object)->position, position);
        qcopy(&work->velocity, velocity);
        euler_rotation_basis(object + 0xC0, g_hero_moby[0] + 0xF0);
        moby_get_facing_direction(object + 0x10, &direction);
        vec_scale_to_length(&forward, object + 0xE0, 1);
        FastVecCross(&axis, &forward, &direction);
        angle = FastVecDot(&forward, &direction) * 0.5f;
        FastVecScale(&quaternion, &axis, math_fast_sin_or_cos_b(angle));
        quaternion.f[3] = math_fast_sin_or_cos_a(angle);
        quaternion_to_rotation_basis(&quaternion, rotation);
        multiply_matrix3x3(object + 0xC0, rotation, object + 0xC0);
        work->owner = 0;
        work->f60 = (g_weapon_l00_table + D_00139591[0])->f58;
        work->f64 = 0;
        work->f50 = 0;
        work->f44 = 0;
        work->f4C = 1;
        work->f40 = D_L00_001AEF48;
        vec_clear_128(&work->basis[0]);
        *(float *)&work->basis[0] = 1;
        work->basis[2] = work->basis[0];
        work->basis[1] = work->basis[0];
        work->f58 = 0.026179943f;
        work->handle = slot_alloc_for_object((unsigned char *)object, 0);
        if (work->handle == -1) {
            moby_mark_spawned(object);
            return 0;
        }
        work->f4F = part_alloc_effect_slot(object, 0, 1, 1, 1);
        work->f4E = -1;
        work->f70 = 0;
        func_002A0F48(object);
    }
    return object;
}

/* Creates a Megaturret shot at the given position moving the given way, and turns it to face its direction. Returns null if it cannot be set up. */
char *megaturret_spawn_shot(void *owner, Vector4 *position, Vector4 *velocity)
{
    Vector4 direction, forward, quaternion, axis;
    Vector4 rotation[3];
    char *object = CreateMoby(MOBY_CLASS_MEGATURRET);
    TrailWork *work;
    float angle;
    if (object) {
        int initialState = 255;
        ((TrailMoby *)object)->flags |= 0x100;
        work = ((TrailMoby *)object)->work;
        ((TrailMoby *)object)->drawMask = initialState;
        ((TrailMoby *)object)->state = 0;
        ((TrailMoby *)object)->alpha = initialState;
        qcopy(&((TrailMoby *)object)->position, position);
        qcopy(&work->velocity, velocity);
        euler_rotation_basis(object + 0xC0, g_hero_moby[0] + 0xF0);
        moby_get_facing_direction(object + 0x10, &direction);
        vec_scale_to_length(&forward, object + 0xE0, 1);
        FastVecCross(&axis, &forward, &direction);
        angle = FastVecDot(&forward, &direction) * 0.5f;
        FastVecScale(&quaternion, &axis, math_fast_sin_or_cos_b(angle));
        quaternion.f[3] = math_fast_sin_or_cos_a(angle);
        quaternion_to_rotation_basis(&quaternion, rotation);
        multiply_matrix3x3(object + 0xC0, rotation, object + 0xC0);
        work->f64 = 0;
        work->f50 = 0;
        work->f44 = 0;
        work->f60 = 10;
        work->f4C = 1;
        work->f40 = D_L00_001AEFA8;
        vec_clear_128(&work->basis[0]);
        *(float *)&work->basis[0] = 1;
        work->basis[2] = work->basis[0];
        work->basis[1] = work->basis[0];
        work->f58 = 0.026179943f;
        work->owner = owner;
        work->handle = slot_alloc_for_object((unsigned char *)object, 0);
        if (work->handle == -1) {
            moby_mark_spawned(object);
            return 0;
        }
        work->f4F = part_alloc_effect_slot(object, 0, 1, 1, 1);
        work->f4E = -1;
        work->f70 = 0;
        func_002A0F48(object);
    }
    return object;
}

/* Fields of objects whose layouts are not identified yet. */
#define FIELD(type, p, off) (*(type *)((char *)(p) + (off)))

extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void moby_set_light_color(void *, int);
extern void func_002A05A8(char *);
extern float ApproachValue(float *, float, float);
extern int math_fast_float_d(int *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void *sheep_board_create_child(void *, void *, void *, unsigned int);
extern int PlayMobySound(int, int, char *);

extern char g_camera_l00_position[];
extern float D_L00_001AEDA0[2] __attribute__((sda));
extern int D_L00_001AEDA8[2] __attribute__((sda));
extern float D_L00_001AEDB0 __attribute__((sda));
extern float D_L00_001AEDB4 __attribute__((sda));
extern float D_L00_001AEDBC __attribute__((sda));
extern int D_L00_001AEDD0[2] __attribute__((sda));
extern Vector4 D_L00_001AEDC0 SDATA(D_L00_001AEDC0);
extern int g_frame_l00_counter;

/* Measured input fields; other fields are not yet identified. */
typedef struct {
    char pad[0x10C];
    float axis;
    char pad110[8];
    float negative, positive;
    char pad120[0x80];
    int buttons;
} PlayerControl;
extern PlayerControl D_00138500, g_pad_state;

typedef struct {
    Vector4 basis[2];
    Vector4 motion[2];
    int timers[2];
    char *objects[2];
} AttachmentWork;

/* The two returns give per-arm loads that jump2 cross-jumps into one lw. */
static inline int pad_buttons(int i)
{
    if (i)
        return g_pad_state.buttons;
    return D_00138500.buttons;
}

/* Updates two objects held in the owner's work area: places them from their basis
   vectors, scales and animates them. Then, for each, eases basis[i].z by the input
   axis (clamped to [-0.45, 0.35]), sets its alpha to 128 or pulses it depending on
   func_00282948 of a global counter, and when func_00282948 of its own counter is
   true, its alpha is 128 and a button in 0xE0 is down, sets that counter to 45 and
   calls func_L00_00384CA8 with a position and velocity taken from the object. The copy source is set before the loop: it gets no
   register and reload rematerializes it at the copy. */
/* Updates the two guns held by the owner: tilts them with the player's stick input, makes them glow, and fires a shot when a fire button is pressed. */
void twin_guns_update_and_fire(char *owner)
{
    AttachmentWork *work = FIELD(AttachmentWork *, owner, 0x68);
    Vector4 position, velocity;
    float scale, step, input, target, phase, period;
    int i, alpha;
    Vector4 *source;

    for (i = 0; i < 2; ++i) {
        matrix_mul_vec3(work->objects[i] + 0x10, &work->basis[i], g_camera_l00_position + 0x230);
        FastVecAdd(work->objects[i] + 0x10, work->objects[i] + 0x10, g_camera_l00_position);
        FIELD(float, work->objects[i], 0x2C) =
            FIELD(float, FIELD(char *, work->objects[i], 0x24), 0x24) * D_L00_001AEDA0[i];
        moby_set_light_color(work->objects[i], D_L00_001AEDA8[i]);
        func_002A05A8(work->objects[i]);
        func_002A0F48(work->objects[i]);
    }
    scale = D_L00_001AEDB0 * 0.016666668f;
    step = D_L00_001AEDBC * 0.00027777778f;
    source = &D_L00_001AEDC0;
    for (i = 0; i < 2; ++i) {
        if (i)
            input = g_pad_state.axis;
        else
            input = D_00138500.axis;
        if (input == 0.0f) {
            if (i)
                input = g_pad_state.positive - g_pad_state.negative;
            else
                input = D_00138500.positive - D_00138500.negative;
        }
        target = -input * scale;
        if (target != 0.0f)
            ApproachValue(&work->motion[i].f[2], target, step);
        else
            ApproachValue(&work->motion[i].f[2], 0.0f, step + step);
        work->basis[i].f[2] += work->motion[i].f[2];
        if (work->basis[i].f[2] > 0.35f) {
            work->basis[i].f[2] = 0.35f;
            if (work->motion[i].f[2] > 0.0f)
                work->motion[i].f[2] = 0.0f;
        } else if (work->basis[i].f[2] < -0.45f) {
            work->basis[i].f[2] = -0.45f;
            if (work->motion[i].f[2] < 0.0f)
                work->motion[i].f[2] = 0.0f;
        }
        if (math_fast_float_d(&D_L00_001AEDD0[i])) {
            FIELD(unsigned char, work->objects[i], 0x23) = 128;
        } else {
            phase = IntToFloat(g_frame_l00_counter % 60);
            period = IntToFloat(60);
            phase *= 6.2831855f;
            phase /= period;
            alpha = FloatToInt(math_fast_sin_or_cos_b(phase - 3.1415927f) * 10.0f) + 20;
            FIELD(unsigned char, work->objects[i], 0x23) = alpha;
        }
        if (math_fast_float_d(&work->timers[i])
            && FIELD(unsigned char, work->objects[i], 0x23) == 128
            && (pad_buttons(i) & 0xE0)) {
            work->timers[i] = 45;
            position.bits = source->bits;
            if (!i)
                position.f[1] -= 0.05f;
            matrix_mul_vec3(&position, &position, work->objects[i] + 0xC0);
            FastVecAdd(&position, &position, work->objects[i] + 0x10);
            vec_scale_to_length(&velocity, work->objects[i] + 0xC0, D_L00_001AEDB4 * 0.016666668f);
            sheep_board_create_child(work->objects[i], &position, &velocity, i);
            PlayMobySound(0, 0, work->objects[i]);
        }
    }
}
