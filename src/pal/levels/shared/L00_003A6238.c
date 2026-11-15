#include "include_asm.h"





#include "common.h"
extern int vec_fast_helper_a(void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_below(int);
extern char *func_PAL_002BE9A8(float, void *, float, float, int, void *, float, unsigned int, int);
extern int FloatToInt(float);

/* func_L00_003A2C60 is defined in L00_003A2C60-g8.c. */

/* func_L00_003A2EE0 is defined in L00_003A2EE0-g8.c. */



/* Emit layered sparks while the object's effect timer remains active. */
void func_PAL_L00_003A77D8(char *moby)
{
    float position[4], offset[4], velocity[4];
    int count, rotation;
    int style;
    int firstStyle;
    int firstKind, firstAlpha, secondKind, secondAlpha;
    float size;
    if (!*(unsigned char *)(moby + 0xBC))
        return;
    vec_fast_helper_a(moby + 0xBC);
    firstStyle = 7;
    firstKind = 2;
    firstAlpha = 127;
    FastVecScale(position, moby + 0xD0, 0.1f);
    FastVecAdd(position, position, moby + 0x10);
    FastVecScale(offset, moby + 0xC0, 0.275f);
    FastVecAdd(position, position, offset);
    FastVecScale(velocity, moby + 0xD0, 0.120000005f);
    for (count = 3; count >= 0; count--) {
        char *particle;
        rotation = math_random_int_below(16);
        if (math_random_int_below(2))
            rotation = -rotation;
        particle = func_PAL_002BE9A8(0.04f, position, 1.0f, 0.9f, rotation, velocity, 52500.0f, 0x7F204080, 0);
        if (particle) {
            char *sub;
            sub = particle + 0x20;
            *(short *)(particle + 10) = firstStyle;
            *(unsigned char *)(particle + 9) = ((*(short *)(moby + 0x32) >> 5) << 4) + FloatToInt(4.0f);
            *(int *)(sub + 4) = firstKind;
            *(unsigned char *)(sub + 10) = firstAlpha;
            *(unsigned char *)(sub + 11) = *(unsigned char *)(particle + 10);
        }
    }
    rotation = 16;
    style = 2;
    size = 15750.0009765625f;
    secondKind = 2;
    secondAlpha = 127;
    for (count = 2; count >= 0; count--) {
        char *particle = func_PAL_002BE9A8(0.02f, position, 1.0f, 1.0f, rotation, velocity, size, 0x7FFFFFFF, 0);
        if (particle) {
            char *sub;
            int brightness;
            sub = particle + 0x20;
            brightness = ((*(short *)(moby + 0x32) >> 5) << 4) + FloatToInt(4.0f);
            *(short *)(particle + 10) = style;
            *(unsigned char *)(particle + 9) = brightness;
            *(unsigned char *)(particle + 8) = math_random_int_below(255);
            *(int *)(sub + 4) = secondKind;
            *(unsigned char *)(sub + 10) = secondAlpha;
            *(unsigned char *)(sub + 11) = *(unsigned char *)(particle + 10);
        }
        rotation = -rotation;
        style <<= 1;
        size -= 3150.0f;
    }
}




extern char D_L00_001A8F20[] __attribute__((sda));
extern void func_0029FCC0_1(int a, int b, void *c);
extern void *projectile_spawn_targeted(int a, void *b, int c, char *d, float e, float f, float g, float h);

/* Runs one helper over the object and a stack buffer, then builds a second call from the object's field 104 sub-object - its field 24 as a float, the constants 2.0f/5.0f/0.6f and a bound data address - and stores the object into field 184 of the returned pointer when it is non-null. */
void func_PAL_L00_003A8978(int a0)
{
    int buf[4];
    int s0;
    int v;

    s0 = *(int *)(a0 + 104);
    func_0029FCC0_1(a0, 0, buf);
    v = projectile_spawn_targeted(a0, buf, *(int *)(s0 + 16), D_L00_001A8F20, *(float *)(s0 + 24), 2.0f, 5.0f, 0.6f);
    if (v != 0) {
        *(int *)(v + 184) = a0;
    }
}


typedef struct {
    unsigned char pad_000[0x18];
    int object_18;
    unsigned char pad_01C[4];
    float vector_20[4];
} L00AimState;
typedef struct {
    unsigned char pad_000[0x70];
    float value_70;
    unsigned char pad_074[0x6C];
} L00AimEntry;
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *,void *,int,void *,void *);
extern float fast_vec_dist(void *, void *);
extern char *func_PAL_L00_00400968(char *, char *, char *, int);
extern void QueueMobyImpact(int, void *);
extern int func_PAL_0032F0B8(int, int, char *);
extern int g_hero_moby;
extern unsigned char D_00139582;
extern L00AimState g_collision_result;
extern L00AimEntry g_weapon_l00_table[];

int func_PAL_L00_003A9468(char *a0, char *a1, char *a2, char *a3)
{
    char local[16];
    float distance;
    float saved;
    int ret;

    FastVecSub(a3, a2, a1);
    vec_scale_to_length(a3, a3, 1.5f);
    *(float *)(a3 + 0xC) = 5627.9248046875f;
    if (CollLine(a1, a2, 0x10, g_hero_moby, 0) != 0) {
        FastVecSub(local, a2, a1);
        vec_scale_to_length(local, local, 1.0f);
        FastVecSub(local, (char *)g_collision_result.vector_20, a1);
        func_PAL_L00_00400968(a1, local, (char *)g_collision_result.vector_20, 1);
        if (g_collision_result.object_18 != 0) {
            saved = (g_weapon_l00_table + D_00139582)->value_70;
            distance = fast_vec_dist((char *)g_collision_result.vector_20, a1);
            if (distance < 10.0f) {
                *(float *)(a3 + 0x1C) = saved;
            } else if (distance < 14.0f) {
                *(float *)(a3 + 0x1C) = saved * 0.75f;
            } else if (distance < 20.0f) {
                *(float *)(a3 + 0x1C) = saved * 0.5f;
            } else {
                *(float *)(a3 + 0x1C) = saved * 0.125f;
            }
            QueueMobyImpact(g_collision_result.object_18, a3);
            func_PAL_0032F0B8(g_collision_result.object_18, 26, a0);
        }
        ret = g_collision_result.object_18;
    } else {
    FastVecSub(local, a2, a1);
    func_PAL_L00_00400968(a1, local, a2, 0);
    ret = 0;
    }
    return ret;
}


