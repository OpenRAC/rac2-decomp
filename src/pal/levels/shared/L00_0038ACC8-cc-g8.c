/* func_PAL_L00_0038ACC8, the PAL copy of func_L00_00387CA8: the same C, where wrap D_L00_001AEF48 (((int)({e}) * 5 + 2) / 6). */
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
extern unsigned char g_miniturret_weapon_index[];
extern int g_miniturret_shot_value __attribute__((sda));

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

/* Creates a Miniturret shot at the given position moving the given way, and turns it to face its direction. Returns null if it cannot be set up (PAL: 50 Hz shot timer). */
char *miniturret_spawn_shot_pal(Vector4 *position, Vector4 *velocity)
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
        work->f60 = (g_weapon_l00_table + g_miniturret_weapon_index[0])->f58;
        work->f64 = 0;
        work->f50 = 0;
        work->f44 = 0;
        work->f4C = 1;
        work->f40 = (((int)(g_miniturret_shot_value) * 5 + 2) / 6);
        vec_clear_128(&work->basis[0]);
        *(float *)&work->basis[0] = 1;
        work->basis[2] = work->basis[0];
        work->basis[1] = work->basis[0];
        work->f58 = 0.031415932f;
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
extern Vector4 g_twin_guns_source_vector SDATA(D_L00_001AEDC0);
/* Measured input fields; other fields are not yet identified. */
typedef struct {
    char pad[0x10C];
    float axis;
    char pad110[8];
    float negative, positive;
    char pad120[0x80];
    int buttons;
} PlayerControl;
extern PlayerControl g_pad_device_state, g_pad_state;

/* The two returns give per-arm loads that jump2 cross-jumps into one lw. */

/* Updates two objects held in the owner's work area: places them from their basis
   vectors, scales and animates them. Then, for each, eases basis[i].z by the input
   axis (clamped to [-0.45, 0.35]), sets its alpha to 128 or pulses it depending on
   func_00282948 of a global counter, and when func_00282948 of its own counter is
   true, its alpha is 128 and a button in 0xE0 is down, sets that counter to 45 and
   calls func_L00_00384CA8 with a position and velocity taken from the object. The copy source is set before the loop: it gets no
   register and reload rematerializes it at the copy. */
