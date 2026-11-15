#include "common.h"

typedef int Copy128 __attribute__((mode(TI)));
typedef union { Copy128 q; float f[4]; } Vector16;

extern void func_002AB6D8(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern char D_00189EA0[];
extern int D_L02_001A8FF0 __attribute__((sda));
extern void func_002A6C58(char *, int, int);
extern int func_002E5CF8(int, int, char *);
extern void func_00283098(void *, void *, void *);
extern unsigned char *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void func_002AFEB8(char *, void *, void *, float, void *);
extern int func_002A77E0(int);
extern void func_002B0A68(char *, int, float *, unsigned char, float, float, float, float);
extern void func_0029F338(void *);

/* Spawn the destruction burst and ground impulse, then remove the object. */
void func_L02_003CEA28(char *object)
{
    Vector16 position, offset;
    float impulse[4];
    char *origin;
    int colour;

    if (*(short *)(*(char **)(object + 0x68) + 0x338) != 0)
        GetEulerAnglesFromMatrix(object + 0xC0, object + 0xF0);
    origin = object + 0x10;
    SetDeathBits(object, 0, 3);
    PlayMobySound(1, 0, object);
    offset.q = 0;
    offset.f[2] = 1.0f;
    matrix_mul_vec3(&position, &offset, object + 0xC0);
    FastVecAdd(&position, &position, origin);
    SpawnExplosion(origin, 0, 0, 0, 0, 10, 20, 0, 0.333f, 20.0f, 1, 0, 0, 0);
    FastVecSub(&impulse, origin, gHeroPosition);
    TransformAndSetHeight(object, &impulse, &impulse, 0.0f, 0);
    vec_scale_to_length(&impulse, &impulse, 0.10000001f);
    if (D_L02_001A8FF0)
        colour = RandomIntBelow(255);
    else
        colour = 255;
    SpawnDebrisForMaskedParts(object, colour & 0x1F, impulse, 255, 3.0f, 6.0f, 3.0f, 6.0f);
    MarkMobySpawned(object);
}
