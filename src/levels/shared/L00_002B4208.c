#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef float f32;
typedef int V4 __attribute__((mode(TI)));

typedef struct {
    u8 pad0[0x98];
    f32 yaw;
    u8 pad1[0x1B4 - 0x9C];
    f32 speed;
    u8 pad2[0x324 - 0x1B8];
    f32 f324;
    u8 pad3[0x22C3 - 0x328];
    u8 flag;
} Owner_002B4208;

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vec4;
extern Owner_002B4208 D_00189E20;
extern V4 D_00189F10;
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_002830C0(void *, void *, void *);
extern void func_002AF000(void *, float, float, float);
/* Works out the direction the hero is pushed in from an angle and the hero speed, and saves it. */
void func_L00_002B4208(float angle)
{
    Vec4 result;
    float direction[4];
    float useAngle;
    float length;
    float zero;
    Owner_002B4208 *hero = &gHeroState;
    useAngle = hero->yaw;
    if (angle <= 3.1415927f)
        useAngle = angle;
    length = hero->speed;
    if (hero->flag != 0) {
        zero = 0.0f;
        direction[0] = FastSinOrCosA(zero) * length;
        direction[1] = FastSinOrCosB(zero) * length;
        direction[2] = zero;
        transform_vector(direction, direction, hero);
        *(V4 *)&result = *(V4 *)direction;
    } else {
        BuildSphericalOffset(&result, length, useAngle, hero->f324);
    }
    D_00189F10 = *(V4 *)&result;
}
