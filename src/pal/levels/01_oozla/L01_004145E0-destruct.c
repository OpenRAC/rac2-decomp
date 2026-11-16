#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } EffectVector;
extern int g_oozla_intro_timer MACRO_ADDR;
extern int g_breakable_count MACRO_ADDR;
extern int g_breakable_active_limit[] NOT_SDA;
extern float D_L01_001B2090_gp[] SDATA(D_L01_001B2090);
extern float D_L01_001B208C_gp[] SDATA(D_L01_001B208C);
extern float D_L01_001B1640_gp[] SDATA(D_L01_001B1640);
extern float g_breakable_effect_offset_y_alt[] NOT_SDA;
extern float g_breakable_offset_z[] NOT_SDA;
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void FastVecScale(void *, void *, float);
extern void func_PAL_002B15D8(void *, int, float *, unsigned char, float, float, float, float);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void part_l01_spawn_spark_burst_pal(float *, float *, int, int, int, float, float, float);
extern void part_spawn_scaled_bolts_pal(void *, int, float);
extern int PlayMobySound(int, int, void *);
extern int flag_set_first_pending(void *);
extern int math_fast_float_d(int *);
extern void moby_mark_spawned(void *);
typedef struct { int blocked, timer; } DestructionState;
typedef struct {
    unsigned char pad00[0x20];
    unsigned char state;             
    unsigned char pad21[0x10];
    unsigned char visible;           
    unsigned char pad32[2];
    unsigned short flags;            
    unsigned char pad36[0x32];
    DestructionState *vars;          
    unsigned char pad6C[0x2C];
    int collision_disable;           
    unsigned char pad9C[0xC];
    unsigned char hit_slot;          
    unsigned char padA9[0x17];
    float rot_row0[4];               
    float rot_row1[4];               
} DestructionMoby;

/* Counts itself in D_L01_001AEC38 until a hit (func_002A9640, mask 0x4010000)
   arrives while not blocked; then spawns its debris and sparks, plays its sound 0,
   and once func_002B3868 reports done hides itself, counts in D_L01_001B3468
   for 120 frames and deletes itself. */
void func_PAL_L01_00414BD8(DestructionMoby *object)
{
    float velocity[4] __attribute__((aligned(16)));
    EffectVector tilt;
    float position[4] __attribute__((aligned(16)));
    DestructionState *state = object->vars;

    switch (object->state) {
    case 0:
        g_oozla_intro_timer++;
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(object, 0x4010000, 0) && !state->blocked) {
            g_oozla_intro_timer--;
            moby_set_state(object, 2, -1);
        }
        object->hit_slot = 255;
        break;
    case 2:
        FastVecScale(velocity, object->rot_row1, -0.080000006f);
        if (object->visible && D_L01_001B2090_gp[0] < 0.9f && D_L01_001B208C_gp[0] < 0.9f &&
            g_breakable_count < g_breakable_active_limit[0]) {
            func_PAL_002B15D8(object, 0x3F, velocity, 255, 1.0f, 3.0f, 2.0f, 5.0f);
            tilt.q = 0;
            tilt.f[1] = -0.018000001f;
            vec_local_offset_to_world(object, position, D_L01_001B1640_gp[0], g_breakable_effect_offset_y_alt[0], g_breakable_offset_z[0]);
            matrix_mul_vec3(tilt.f, tilt.f, object->rot_row0);
            part_l01_spawn_spark_burst_pal(position, tilt.f, 10, 0x3F7FFF3F, 0, 0.008f, 1.0f, 1.0299999713897705f);
        } else
            func_PAL_002B15D8(object, 2, velocity, 255, 1.0f, 3.0f, 2.0f, 5.0f);
        part_spawn_scaled_bolts_pal(object, 1, 0.0f);
        PlayMobySound(0, 0, object);
        moby_set_state(object, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(object)) {
            object->visible = 0;
            object->collision_disable = 0;
            object->flags |= 1;
            state->timer = 100;
            g_breakable_count++;
        }
        if (math_fast_float_d(&state->timer)) {
            g_breakable_count--;
            moby_mark_spawned(object);
        }
        break;
    }
}
