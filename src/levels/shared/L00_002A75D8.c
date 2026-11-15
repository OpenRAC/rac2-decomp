#include "include_asm.h"
#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
typedef float f32;

typedef struct {
    u8 pad0[0x10];
    f32 m10[4];
    u8 pad1[0x80 - 0x20];
    f32 v80[4];
    u8 pad2[0x660 - 0x90];
    int f660;
    u8 pad3[0x6B0 - 0x664];
    f32 f6B0;
    u8 pad4[0x6BC - 0x6B4];
    short f6BC;
    u8 pad5[0x7A8 - 0x6BE];
    f32 f7A8;
    f32 f7AC;
    u8 pad6[0x2290 - 0x7B0];
    char *obj;
    int state;
} Owner_002A75D8;

extern Owner_002A75D8 D_00189E20;
extern void func_002AEE70(void *, void *, void *, float, float, float);
extern void func_00283410(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);

/* Updates the hero model for one special state. It tilts the model and copies a height value onto it, then moves the model by a small offset. */
void func_L00_002A75D8(void)
{
    Owner_002A75D8 *hero = &gHeroState;
    float offset[4];
    float matrix[16];

    if (hero->state == 0x7C)
        UpdateWrappedAngleOffset(hero->obj, &hero->f7A8, &hero->f7AC, 0.3f, 0.1163553f, -1.0f);
    if (hero->f6BC == 0)
        return;
    if (hero->f660 != 0)
        return;
    *(float *)(hero->obj + 0xF4) = hero->f6B0;
    *(TI128 *)offset = 0;
    offset[2] = 2.0f;
    euler_to_matrix(matrix, hero->obj + 0xF0);
    transform_vector(offset, offset, matrix);
    FastVecAdd(hero->obj + 0x10, hero->v80, offset);
}
