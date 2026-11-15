#include "common.h"

/* func_L01_0040F958, in a unit of its own: retail reaches its globals with
   assembler macro loads (-mno-split-addresses), $gp-relative where they sit in
   a delay slot or are small-data views (SDATA), absolute elsewhere. */

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } EffectVector;

extern int D_L01_001AEC38 MACRO_ADDR;
extern int D_L01_001B3468 MACRO_ADDR;
extern int D_L01_001B15E0[] NOT_SDA;
extern float D_L01_001B2090_gp[] SDATA(D_L01_001B2090);
extern float D_L01_001B208C_gp[] SDATA(D_L01_001B208C);
extern float D_L01_001B1640_gp[] SDATA(D_L01_001B1640);
extern float D_L01_001B1644[] NOT_SDA;
extern float D_L01_001B1648[] NOT_SDA;

extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void FastVecScale(void *, void *, float);
extern void part_spawn_masked_debris(void *, int, float *, unsigned char, float, float, float, float);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void part_l01_spawn_spark_burst(float *, float *, int, int, int, float, float, float);
extern void part_spawn_scaled_bolts(void *, int, float);
extern int PlayMobySound(int, int, void *);
extern int flag_set_first_pending(void *);
extern int math_fast_float_d(int *);
extern void moby_mark_spawned(void *);

typedef struct { int blocked, timer; } DestructionState;

/* The moby fields this function touches. Struct (not cast) accesses matter:
   GCC only lets a global's load pass a store through a varying address when
   that store is a structure field. */
typedef struct {
    unsigned char pad00[0x20];
    unsigned char state;            /* 0x20 */
    unsigned char pad21[0x10];
    unsigned char visible;          /* 0x31 */
    unsigned char pad32[2];
    unsigned short flags;           /* 0x34 */
    unsigned char pad36[0x32];
    DestructionState *vars;         /* 0x68 */
    unsigned char pad6C[0x2C];
    int collision_disable;          /* 0x98 */
    unsigned char pad9C[0xC];
    unsigned char hit_slot;         /* 0xA8 */
    unsigned char padA9[0x17];
    float rot_row0[4];              /* 0xC0 */
    float rot_row1[4];              /* 0xD0 */
} DestructionMoby;

/* Counts itself in D_L01_001AEC38 until a hit (func_002A9640, mask 0x4010000)
   arrives while not blocked; then spawns its debris and sparks, plays its sound 0,
   and once func_002B3868 reports done hides itself, counts in D_L01_001B3468
   for 120 frames and deletes itself. */
/* Breakable object. When something hits it, it breaks into pieces, hides, and removes itself after a short wait. */
void breakable_l01_object_update_2(DestructionMoby *object)
{
    float velocity[4] __attribute__((aligned(16)));
    EffectVector tilt;
    float position[4] __attribute__((aligned(16)));
    DestructionState *state = object->vars;

    switch (object->state) {
    case 0:
        D_L01_001AEC38++;
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(object, 0x4010000, 0) && !state->blocked) {
            D_L01_001AEC38--;
            moby_set_state(object, 2, -1);
        }
        object->hit_slot = 255;
        break;
    case 2:
        FastVecScale(velocity, object->rot_row1, -0.06666667014360428f);
        if (object->visible && D_L01_001B2090_gp[0] < 0.9f && D_L01_001B208C_gp[0] < 0.9f &&
            D_L01_001B3468 < D_L01_001B15E0[0]) {
            part_spawn_masked_debris(object, 0x3F, velocity, 255, 1.0f, 3.0f, 2.0f, 5.0f);
            tilt.q = 0;
            tilt.f[1] = -0.015000000596046448f;
            vec_local_offset_to_world(object, position, D_L01_001B1640_gp[0], D_L01_001B1644[0], D_L01_001B1648[0]);
            matrix_mul_vec3(tilt.f, tilt.f, object->rot_row0);
            part_l01_spawn_spark_burst(position, tilt.f, 10, 0x3F7FFF3F, 0, 0.0066666672937572f, 1.0f, 1.0299999713897705f);
        } else
            part_spawn_masked_debris(object, 2, velocity, 255, 1.0f, 3.0f, 2.0f, 5.0f);
        part_spawn_scaled_bolts(object, 1, 0.0f);
        PlayMobySound(0, 0, object);
        moby_set_state(object, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(object)) {
            object->visible = 0;
            object->collision_disable = 0;
            object->flags |= 1;
            state->timer = 120;
            D_L01_001B3468++;
        }
        if (math_fast_float_d(&state->timer)) {
            D_L01_001B3468--;
            moby_mark_spawned(object);
        }
        break;
    }
}
