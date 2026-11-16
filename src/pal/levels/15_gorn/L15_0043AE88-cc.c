#include "names.h"
/* func_PAL_L15_0043AE88, the PAL copy of func_L15_004351E0: the same C, where rename func_002BDCE8 becomes func_PAL_002BE9A8; scale (func_002A7820(1, 10)); scale func_002A7820(40, 70). */
#include "common.h"

/* Measured prefixes with integer/float views of the same game records. */
extern float math_fast_sin_or_cos_b(float);
extern void gorn_path_mover_init(char *);
/* ---- shared declarations ---- */

/* Sets the level's four effect blocks up: the screen context first, then, when
   the level's own record says the object is idle, the four blocks of the
   effect data, each with its own size and colour. */
/* func_L15_00432A60 is in L15_00432A60-ribbon.c. */

extern float IntToFloat(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern void gorn_ship_init(char *);
extern void gorn_ship_spawn_damage_effects(void *);
extern int math_random_int_below(int);
extern void moby_mark_spawned(void *);
extern void euler_rotation_basis(void *, void *);
extern s32 g_gorn_ship_damage_joints[] SDATA(D_L15_001B1780);
extern s32 g_gorn_ship_part_joints[] SDATA(D_L15_001B17B0);
extern s32 PlayMobySound(s32 a, s32 b, void *c);
extern s32 math_random_int_below(s32 a);
extern f32 math_random_float_range(f32 a, f32 b);
extern void moby_transform_joint_to_world(void *obj, s32 a, void *out);
extern s32 FloatToInt(f32 a);
/* The particle helper has a different catalogue body in PAL. */
void gorn_ship_spawn_damage_effects(void *object);

typedef struct GornEffectCamera {
    char pad00[0x140];
    float position[4];
} GornEffectCamera;
extern GornEffectCamera g_hero_l15_state_floats;
extern unsigned char *g_particle_l15_byte_ptr;
extern void moby_transform_joint_to_world(void *, int, void *);
extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern unsigned char *part_spawn_spinning_spark_pal(float, float, float, float,
                                   void *, int, void *, int, int);
extern int math_random_int_range(int, int);
extern int FloatToInt(float);
extern float IntToFloat(int);

/* Spawns a puff of smoke particle at a joint of the Gorn ship, thrown away from the hero. (PAL: 50 Hz lifetimes) */
void gorn_part_spawn_smoke_pal(char *object, int joint, int unused, float radius) {
    float initial[4], point[4], velocity[4];
    float heading, speed, tilt, yaw;
    unsigned char *particle;
    unsigned char *data;

    moby_transform_joint_to_world(object, joint, initial);
    heading = mat_fast_helper_a(g_hero_l15_state_floats.position[0] - *(float *)(object + 0x10),
                            g_hero_l15_state_floats.position[1] - *(float *)(object + 0x14));
    point[0] = initial[0] + math_random_signed_float_range(0, radius);
    point[1] = initial[1] + math_random_signed_float_range(0, radius);
    point[2] = initial[2] + math_random_signed_float_range(0, radius);
    speed = math_random_float_range(radius * 0.010000001f,
                          radius * 0.020000001f);
    tilt = math_random_signed_float_range(0, 1.396263599395752f);
    yaw = FastAddRotations(heading, math_random_signed_float_range(0, 1.5707964897155762f));
    vec_build_spherical_offset(velocity, speed, yaw, tilt);
    particle = part_spawn_spinning_spark_pal(0, 1.0f, 1.01f, radius * 210000.0f,
                            point, -1, velocity, 0x307F7F7F, 0);
    if (particle != 0) {
        particle[3] = 0x48;
        *(short *)(particle + 0xA) = (((int)(math_random_int_range(40, 70)) * 5 + 2) / 6);
        particle[9] = FloatToInt(4.0f) + 0x60;
        data = particle + 0x20;
        *(float *)(data + 0x1C) = IntToFloat(((int)((math_random_int_range(1, 10))) * 5 + 2) / 6);
        *(int *)(data + 4) = 3;
        data[0xA] = 0x7F;
        data[0xB] = particle[0xA];
        particle[2] = *g_particle_l15_byte_ptr;
    }
}

void gorn_ship_init(char *object);

/* func_L15_00435E80 is in L15_00435E80.c. */

/* func_L15_004360D8 is in L15_004360D8.c. */

extern int PlayMobySound(int, int, void *);
/* The mover's own state decides whether the shot happens: the level's record
   must exist and be ready, and the mover's own counter must be idle.  The two
   shots take the slots after the counter, and the counter wraps at three. */
/* func_L15_004363C8 is in L15_004363C8-g8.c. */

/* Advance through the path points, pausing when an odd encoded action supplies
   a duration in seconds. The path has a 16-byte header and 16-byte points. */
void gorn_path_mover_init(char *a0);

/* func_L15_00438260 is in L15_00438260-g8.c. */

/* func_L15_00438518 is in L15_00438518-g8.c. */

extern int math_random_int_below(int);
/* The level's id lists: the number of groups, the table of the groups' lists (a pointer, read
   through $gp in a branch delay slot and as a bare lui/lw elsewhere: `sda` arrays of unknown size
   give that), the base of the 64-byte records of the first walk, the base of the 32-byte records
   of the second, and the table that maps a record's byte at +0x1D to a class. */
extern float math_fast_sin_or_cos_b(float);
extern void moby_mark_spawned(void *);
extern void euler_rotation_basis(void *, void *);

/* State 0 looks for the group of the level's id lists that holds the 64-byte record closest to
   the object (first walk, distances below 9999.0; the group index goes to the state's first word
   and the function ends when there is none), sets the object's aim from two random values
   (func_002A7878, func_002A7940) and the record list at state + 0x40, removes the object when the
   state's byte at +0x8A is zero, and otherwise walks the chosen group's 32-byte records
   (second walk): records of class 0xD34 and 0xD33 get their id written into the record list with
   the payload at state + 0x680 and state + 0x6A0 (func_L00_00323E48).  It then picks two random
   angular speeds (the second gets the sign opposite to the first) and goes to state 1, which
   keeps aiming and turns the two angles at +0x688 and +0x6A8.  Both walks keep the second
   `p != 0` guard before the `p[-1]` read and the second walk has a pointer variable of its own
   (one shared variable swaps two callee-saved registers).  Measured: a0 + 0xC0 and a0 + 0xF0
   formed in locals ahead of the second walk make loop.c hoist the two class constants out of it
   (two more saved registers); written at their use after the walk, as below, they stay in the
   loop.  The sign test is a store followed by a conditional store, which gives retail's
   `bc1f` with the first store in its slot and lets the constant 1 be shared by both stores. */
