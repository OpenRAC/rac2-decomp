#include "include_asm.h"
#include "names.h"

typedef int OrbitQuad __attribute__((mode(TI)));
typedef union { OrbitQuad q; float v[4]; } OrbitVector;

extern char g_hero_state[] __attribute__((nosda));
extern float IntToFloat(int value);
extern float math_fast_sin_or_cos_a(float angle);
extern float math_fast_sin_or_cos_b(float angle);
extern void vec_scale_to_length(void *out, void *vector, float scale);
extern void FastVecAdd(void *out, void *left, void *right);

/* Works out where a Synthenoid should hover as it circles around the player. */
void synthenoid_compute_orbit_point(void *unused, char *vars)
{
    OrbitVector offset;
    float scale = 1.2f;
    float angle = IntToFloat(*(int *)(vars + 0x38));
    char *hero;
    char *axis0, *axis1, *axis2;
    float wave;
    wave = IntToFloat(3);
    wave = 3.1415927f / wave;
    angle *= wave;
    hero = g_hero_state;
    axis0 = *(char **)(hero + 0x2290) + 0xd0;
    wave = math_fast_sin_or_cos_a(angle);
    vec_scale_to_length(&offset, axis0, wave * scale);
    FastVecAdd(vars, &offset, hero + 0x80);
    axis1 = *(char **)(hero + 0x2290) + 0xe0;
    wave = math_fast_sin_or_cos_b(angle);
    vec_scale_to_length(&offset, axis1, wave * scale + 2.2f);
    FastVecAdd(vars, vars, &offset);
    axis2 = *(char **)(hero + 0x2290) + 0xc0;
    wave = math_fast_sin_or_cos_b(angle);
    vec_scale_to_length(&offset, axis2, wave + wave);
    FastVecAdd(vars, vars, &offset);
}
