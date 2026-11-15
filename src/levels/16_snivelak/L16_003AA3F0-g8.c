#include "common.h"
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vector;
typedef Vector Row[4];
typedef struct {
    int index;
    char pad4[0xe];
    short lifetime;
    int pad14;
    u8 selected[8];
    Vector positions[32], velocities[32];
    Vector branches[4][4], branchVelocities[4][4];
    int duration;
    char pad624[0x2c];
    float rotation[3];
} Beam;
typedef struct {
    char pad0[0x10];
    Vector position;
    char pad20[0x48];
    Beam *vars;
} BeamMoby;
extern int g_current_map_index;
extern int D_L16_001AF884 __attribute__((sda)), D_L16_001AF888 __attribute__((sda));
extern float D_L16_001AF908 __attribute__((sda)), D_L16_001AF90C __attribute__((sda)), D_L16_001AF920 __attribute__((sda));
extern int D_L16_001AF914 __attribute__((sda)), D_L16_001AF918 __attribute__((sda));
extern int D_L16_001AF928 __attribute__((sda)), D_L16_001AF92C __attribute__((sda));
extern char *D_L16_001B2C0C __attribute__((sda));
extern float D_L16_001B9B00[4];
extern int math_random_int_range(int,int);
extern float math_random_float_range(float,float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void vec_random_direction(void *,float,float);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern float vec_distance_xy(void *,void *);
extern float math_random_angle(void);
extern void euler_to_matrix(void *,void *);
extern void transform_vector(void *,void *,void *);
extern int math_random_int_below(int);
extern void *part_spawn_trail(void *,void *,void *,int,int,int,int,int,int);

/* The second particle loop draws this coin and never reads it. The test still has to be there at
   gcse: it splits the block, so the call's &jitter takes the reaching register as in the first loop. */
static inline void flipCoin(int *heads)
{
    if (math_random_int_below(2))
        *heads = 1;
    else
        *heads = 0;
}

/* Builds a new random lightning beam with branches and spawns sparks along it. */
void start_vendor_beam_pulse(BeamMoby *object)
{
    Beam *beam = object->vars;
    Vector positions[32], velocities[32], scratch, jitter;
    Vector transform[4];
    const float frameTime = 0.01666666753590107f;
    float half;
    float timeStep;
    float unit;
    float spread;
    int i, smoothIndex, branchIndex, particleIndex, j, k;
    int selected;
    object->position.w = 1.0f;
    beam->lifetime = math_random_int_range(D_L16_001AF884, D_L16_001AF888);
    beam->duration = beam->lifetime;
    if (g_current_map_index == 0xd5 || g_current_map_index == 16)
        spread = math_random_float_range(40.0f, 45.0f);
    else spread = math_random_float_range(4.0f, 8.0f);
    half = 0.5f;
    timeStep = frameTime;
    unit = 1.0f;
    for (i = 0; i < 32; i++) {
        float height = IntToFloat(i);
        float last = IntToFloat(31);
        height = height / last;
        height = (half - height) * spread;
        if ((unsigned)(i - 3) >= 26) {
            vec_clear_128(&positions[i]);
            vec_clear_128(&velocities[i]);
        } else {
            vec_random_direction(&positions[i], 0.0f, D_L16_001AF908);
            if (g_current_map_index == 16 || g_current_map_index == 0xd5)
                vec_random_direction(&velocities[i], 0.0f, 0.20000001788139343f);
            else vec_random_direction(&velocities[i], 0.0f, D_L16_001AF90C * timeStep);
        }
        {
            float y = positions[i].y;
            positions[i].w = unit;
            positions[i].y = y + height;
        }
    }
    for (smoothIndex = 0; smoothIndex < 32; smoothIndex++) {
        if (smoothIndex == 0 || smoothIndex == 31) {
            qcopy(&beam->positions[smoothIndex], &positions[smoothIndex]);
            qcopy(&beam->velocities[smoothIndex], &velocities[smoothIndex]);
        } else {
            FastVecAdd(&scratch, &positions[smoothIndex-1], &positions[smoothIndex]);
            FastVecAdd(&scratch, &scratch, &positions[smoothIndex+1]);
            FastVecScale(&beam->positions[smoothIndex], &scratch, 0.333f);
            FastVecAdd(&scratch, &velocities[smoothIndex-1], &velocities[smoothIndex]);
            FastVecAdd(&scratch, &scratch, &velocities[smoothIndex+1]);
            FastVecScale(&beam->velocities[smoothIndex], &scratch, 0.333f);
        }
    }
    for (branchIndex = 0; branchIndex < 4; branchIndex++) {
        if (g_current_map_index == 0xd5 || g_current_map_index == 16)
            vec_random_direction(&scratch, 1.0f, 1.0f);
        else vec_random_direction(&scratch, D_L16_001AF908, D_L16_001AF908);
        selected = FloatToInt(math_random_float_range((float)branchIndex * 6.0f, (float)(branchIndex + 1) * 6.0f)) + 4;
        beam->selected[branchIndex] = selected;
        qcopy(&beam->branches[0][branchIndex], &beam->positions[selected]);
        qcopy(&beam->branchVelocities[0][branchIndex], &beam->velocities[selected]);
        {
            int velOffset = (int)&((Beam *)0)->branchVelocities[0][branchIndex];
            int curOffset = (int)&((Beam *)0)->branches[0][branchIndex];
            for (j = 1; j < 4; j++) {
                Beam *column = (Beam *)(branchIndex * 16);
                column = (Beam *)((int)column + (int)beam);
                vec_random_direction(&jitter, 0.1f, 0.1f);
                if (g_current_map_index == 0xd5 || g_current_map_index == 16)
                    vec_random_direction(((Row *)((char *)beam + velOffset))[j], 0.0f, 0.20000001788139343f);
                else vec_random_direction(((Row *)((char *)beam + velOffset))[j], 0.0f, D_L16_001AF90C * frameTime);
                FastVecAdd(((Row *)((char *)beam + curOffset))[j], column->branches[j-1], &scratch);
                FastVecAdd(((Row *)((char *)beam + curOffset))[j], ((Row *)((char *)beam + curOffset))[j], &jitter);
            }
        }
    }
    if (vec_distance_xy(&object->position, D_L16_001B9B00) >= 4.0f) {
        char *definition = (char *)(beam->index * 128 + (int)D_L16_001B2C0C);
        beam->rotation[2] = *(float *)(definition + 0x78);
        beam->rotation[1] = *(float *)(definition + 0x74);
        beam->rotation[0] = math_random_angle();
        euler_to_matrix(transform, beam->rotation);
        qcopy(&transform[3], &object->position);
        for (particleIndex = 0; particleIndex < 32; particleIndex += 8) {
            int color, duration;
            transform_vector(&scratch, &beam->positions[particleIndex], transform);
            qcopy(&jitter, &beam->velocities[particleIndex]);
            jitter.w = D_L16_001AF920;
            color = math_random_int_below(2) ? D_L16_001AF928 : D_L16_001AF92C;
            duration = math_random_int_below(10);
            part_spawn_trail(&scratch, &jitter, &jitter, D_L16_001AF914, D_L16_001AF918, particleIndex >> 1, 15, duration + 20, color);
        }
        for (k = 0; k < 2; k++) {
            int duration, heads;
            transform_vector(&scratch, &beam->branches[3][k], transform);
            qcopy(&jitter, &beam->branchVelocities[3][k]);
            jitter.w = D_L16_001AF920;
            flipCoin(&heads);
            duration = math_random_int_below(10);
            part_spawn_trail(&scratch, &jitter, &jitter, D_L16_001AF914, D_L16_001AF918, beam->selected[k] >> 1, 15, duration + 20, D_L16_001AF92C);
        }
    }
}
