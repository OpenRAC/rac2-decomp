#include "include_asm.h"
#include "names.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;

extern void func_002FDBD8_6(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

extern int func_002A77E0_3(int x);


extern void func_31D8A0(void *, float, float);
extern void func_2E6CF0(void *, void *);
extern int func_2EDD48(void *);
extern void func_31A658(void *, int, int);
extern void part_emit_colored_burst(void);

/* Update step for an effect object: it keeps ticking a timer, registers its draw routine, and finishes the object when the timer runs out. */
void thief_weapon_update(char *self)
{
    char *vars = *(char **)(self + 0x68);

    if (*(unsigned char *)(self + 0x20) == 1) {
        func_31D8A0(vars, 1.0f, *(float *)(vars + 4));
        func_2E6CF0((void *)part_emit_colored_burst, self);
        if (func_2EDD48(vars + 8) != 0) {
            func_31A658(self, 0, -1);
        }
    }
}








/* Does nothing (an empty handler). */
void moby_l00_update_empty_4(void)
{
}




extern char g_camera_l00_position[];

extern void FastVecSub(char *, char *, char *);
extern float mat_fast_helper_a(float, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void part_spawn_burst(float *, float *, int, int, unsigned int, int,
                          float, float, float, float, float);

/* Fifteen times over: take the angle of the constant vector at D_L00_001B8DC0 and the point,
   build a direction from a random step and a random magnitude, jitter the point by a random
   small amount on each axis and hand the result to the spawn helper with 210000.0f, 500.0f,
   1.0f, 0.0f and 0.0f; the original game role is unknown. */
/* Sprays fifteen small sparks outward from a point. */
void part_l00_spawn_spark_spray_2(float *pos)
{
    float v[4];
    float dir[4];
    float out[4];
    float ang;
    float angle;
    float scale;
    float mag;
    float speed;
    int id;
    int i;

    FastVecSub((char *)v, g_camera_l00_position, (char *)pos);
    ang = mat_fast_helper_a(v[0], v[1]);

    for (i = 14; i >= 0; i--) {
        scale = math_random_float_range(0.5f, 1.0f);
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        math_random_float_range(0.05f, 0.2f);
        speed = 210000.0f;
        mag = math_random_float_range(0.0f, 1.396263599395752f);
        angle = FastAddRotations(ang, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(dir, scale * 0.01666666753590107f, angle, mag);
        out[0] = pos[0] + math_random_signed_float_range(0.0f, 0.1f);
        out[1] = pos[1] + math_random_signed_float_range(0.0f, 0.1f);
        out[2] = pos[2] + math_random_signed_float_range(0.0f, 0.1f);
        part_spawn_burst(out, dir, 30, 127, 0x007F7F7F, id,
                      math_random_float_range(0.05f, 0.2f) * speed, 500.0f, 1.0f, 0.0f, 0.0f);
    }
}




extern int func_2EDD48(void *);
extern void func_310440(void *);
extern void func_2E6EF8(void *, void *);
extern void spark_trail_draw_ribbon_wide(void);

/* Update step: when the timer runs out the object finishes, otherwise it registers its draw routine. */
void timed_draw_object_update(char *self)
{
    if (func_2EDD48(*(void **)(self + 0x68)) != 0) {
        func_310440(self);
    } else {
        func_2E6EF8((void *)spark_trail_draw_ribbon_wide, self);
    }
}


extern void moby_mark_spawned(void *);
extern int IsPointInCuboid(void *, int);
extern int coll_point_inside_region(void *, int);

/* The table of id lists (halfwords whose low 15 bits index the 32-byte records at the second
   pointer, the last one with its sign bit set) and the base of those records; both are read
   bare (`lui`/`lw`), the table's first read of each list in a branch delay slot, where the
   assembler gives it the $gp form. */
extern unsigned short **D_L00_001A9014 __attribute__((sda));
extern unsigned char *D_L00_001B2514 __attribute__((sda));

/* Applies OP to the flag byte at +0x1E of every record of the 14 id lists named by the first 14
   words of the object's state (-1: no list). */
#define MARK_LISTS(op)                                                                  \
    for (i = 0; i < 14; i++) {                                                          \
        id = *(int *)(priv + (i << 2));                                                 \
        if (id != -1) {                                                                 \
            for (p = D_L00_001A9014[id];                                                \
                 p != 0 && ((short)p[-1] >= 0 || p == D_L00_001A9014[id]); p++) {       \
                e = D_L00_001B2514 + ((*p & 0x7FFF) << 5);                              \
                if (e == 0)                                                             \
                    break;                                                              \
                e[0x1E] op;                                                             \
            }                                                                           \
        }                                                                               \
    }

/* A three-state switch on the object's state byte (+0x20) over its private state (+0x68), whose
   words at +0x38 and +0x3C are two optional trigger ids (-1: none) tested against the resident
   D_L00_001B8DC0 by func_002ACBC8 and func_L00_00329520. State 0: with no trigger at all it
   hands the object to func_0029F338 and returns; otherwise it stamps +0x30 with 0xFF and moves to
   state 1. State 1: once a trigger holds it sets bit 2 of the flag byte of every listed record
   (MARK_LISTS) and moves to state 2. State 2: while a trigger holds the bit is set again; when
   none does it is cleared and the object goes back to state 1. Then the halfword counter at
   +0x96 counts up. The state-2 test is written as "no trigger holds": that is retail's block
   order (clearing loop first, setting loop last), which also keeps the two `sb` of the state from
   being cross-jumped into one. */
/* Turns a group of linked records on and off depending on whether one of two triggers is active. */
void trigger_linked_records_update(unsigned char *self)
{
    unsigned char *priv = *(unsigned char **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;
    int id;
    int i;

    switch (self[0x20]) {
    case 0:
        if (*(int *)(priv + 0x38) == -1 && *(int *)(priv + 0x3C) == -1) {
            moby_mark_spawned(self);
            return;
        }
        self[0x30] = 0xFF;
        self[0x20] = 1;
        break;
    case 1:
        if ((*(int *)(priv + 0x38) != -1 && IsPointInCuboid(g_camera_l00_position, *(int *)(priv + 0x38))) ||
            (*(int *)(priv + 0x3C) != -1 && coll_point_inside_region(g_camera_l00_position, *(int *)(priv + 0x3C)))) {
            MARK_LISTS(|= 4)
            self[0x20] = 2;
        }
        break;
    case 2:
        if ((*(int *)(priv + 0x38) == -1 || IsPointInCuboid(g_camera_l00_position, *(int *)(priv + 0x38)) == 0) &&
            (*(int *)(priv + 0x3C) == -1 || coll_point_inside_region(g_camera_l00_position, *(int *)(priv + 0x3C)) == 0)) {
            MARK_LISTS(&= 0xFB)
            self[0x20] = 1;
        } else {
            MARK_LISTS(|= 4)
        }
        break;
    }
    *(unsigned short *)(self + 0x96) += 1;
}


extern int bouncer_spawn_debris_object(int, int, int);

/* Spawns a piece of debris and remembers which object launched it. */
int bouncer_spawn_debris(int owner, int position, int velocity)
{
    int debris = bouncer_spawn_debris_object(position, velocity, *(short *)(owner + 0xAA) == 0xE9E /* Heavy Bouncer */);

    if (debris != 0) {
        *(int *)(debris + 0xB8) = owner;
    }
    return debris;
}

extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void vec_random_direction(char *, float, float);
extern char *SpawnSpinningSparkParticle(float, float, float, float, char *, int, char *,
                     unsigned int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_spawn_template_effect(void *, void *, void *, void *);
extern char ref_L00_003FE310_00[];

/* Twenty rounds that spawn a particle at the second argument: each round draws a radius
   (70000..150000) and a byte (10..127), builds a three-float direction on the stack and
   fills the new record's short and byte fields; the level's own data address is then
   handed to the vector routine with the third argument and a scale of 1.5, and to the
   level-object starter with the second argument. */
/* Throws out twenty glowing sparks from a point as a muzzle burst. */
void part_spawn_muzzle_spark_burst(void *shooter, void *position, void *direction)
{
    char local[16];
    float radius;
    int i;
    unsigned int shade;
    unsigned int shadeMid;
    unsigned int shadeHigh;
    char *particle;

    for (i = 19; i >= 0; i--) {
        func_002A77E0_3(2);
        func_002A77E0_3(2);
        radius = math_random_float_range(70000.0f, 150000.0f);
        shade = math_random_int_range(10, 127);
        shadeMid = (shade << 8) | 0x7f000000U;
        shadeHigh = (shade << 16) | shadeMid;
        shade = shadeHigh | shade;
        vec_random_direction(local, 1.6666668670950457453728e-05f,
                6.6666672937572002410889e-03f);
        particle = SpawnSpinningSparkParticle(0.3f, 1.0f, 1.01f, radius, position, 0, local, shade, 1);
        if (particle != 0) {
            char *extra = particle + 32;

            *(short *)(particle + 10) = 120;
            *(int *)(extra + 4) = 2;
            *(char *)(extra + 10) = 127;
            *(char *)(extra + 11) = *(unsigned char *)(particle + 10);
        }
    }
    vec_scale_to_length(ref_L00_003FE310_00, direction, 1.5f);
    moby_spawn_template_effect(ref_L00_003FE310_00, position, 0, 0);
}

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
/* Draws the object's attached effect when its flag is set. */
void moby_draw_attached_effect(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_6(1.0f, context, context->vector_10, 0);
    }
}











/* takes the float array at +104 and writes four values returned by a call with argument 255, then four float constants (-1.0, -2.25, 1.25, 2.5) at +16..+28, a descending count 255/191/127/63 into the ints at +44..+32 and 2.5/3.0 pairs at +48..+60 */
/* Sets the starting values of a glowing effect: four random phases, fixed sizes and fading brightness steps. */
void glow_effect_init_vars(char *self)
{
    float *vars = *(float **)(self + 104);
    float *writePtr = vars;
    int *intPtr;
    int value;
    int i;
    int j;

    for (i = 3; i >= 0; i--)
    {
        *writePtr = (float)func_002A77E0_3(255);
        writePtr++;
    }

    vars[4] = -1.0000000000000000000000e+00f;
    vars[5] = -2.2500000000000000000000e+00f;
    vars[6] = 1.2500000000000000000000e+00f;
    vars[7] = 2.5000000000000000000000e+00f;

    j = 3;
    intPtr = (int *)(vars + 11);
    value = 255;
    for (; j >= 0; j--)
    {
        *intPtr = value;
        intPtr--;
        value -= 64;
    }

    vars[12] = 2.5000000000000000000000e+00f;
    vars[13] = 3.0000000000000000000000e+00f;
    vars[15] = 2.5000000000000000000000e+00f;
    vars[14] = 3.0000000000000000000000e+00f;
}

