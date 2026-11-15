#include "include_asm.h"
#include "names.h"

typedef int OrbitQuad __attribute__((mode(TI)));
typedef union { OrbitQuad q; float v[4]; } OrbitVector;

extern char D_00189E20[] __attribute__((nosda));
extern float func_00283CE0(int value);
extern float func_00283180(float angle);
extern float func_00283198(float angle);
extern void func_00282F20(void *out, void *vector, float scale);
extern void func_00282CC0(void *out, void *left, void *right);

/* Works out where a Synthenoid should hover as it circles around the player. */
void func_L00_003EB7C0(void *unused, char *vars)
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
    hero = gHeroState;
    axis0 = *(char **)(hero + 0x2290) + 0xd0;
    wave = FastSinOrCosA(angle);
    vec_scale_to_length(&offset, axis0, wave * scale);
    FastVecAdd(vars, &offset, hero + 0x80);
    axis1 = *(char **)(hero + 0x2290) + 0xe0;
    wave = FastSinOrCosB(angle);
    vec_scale_to_length(&offset, axis1, wave * scale + 2.2f);
    FastVecAdd(vars, vars, &offset);
    axis2 = *(char **)(hero + 0x2290) + 0xc0;
    wave = FastSinOrCosB(angle);
    vec_scale_to_length(&offset, axis2, wave + wave);
    FastVecAdd(vars, vars, &offset);
}
