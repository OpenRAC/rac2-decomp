#include "include_asm.h"
#include "names.h"
typedef int Copy128 __attribute__((mode(TI)));
typedef union { Copy128 q; float f[4]; } Vector16;

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern char D_00189EA0[];
extern void func_002A6C58(char *, int, int);
extern int func_002E5CF8(int, int,char*);
extern void func_00283098(void *, void *, void *);
extern unsigned char *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void func_002B0A68(char *, int, float *, unsigned char, float, float, float, float);
extern void func_0029F338(void *);

/* The func_L09_004050E0 burst with a particle spray (func_0032C700) in place of the
   area hit, offset 1.0 up. func_0032C700 returns a pointer; a void prototype puts the
   stack constant 1 ahead of the 20.0f. */
/* Blows the object up: sprays particles, pushes the hero away, then removes the object. */
void func_L06_00443F30(char *object)
{
    Vector16 position, offset, impulse;
    char *origin = object + 0x10;
    SetDeathBits(object, 0, 3);
    PlayMobySound(1, 0, object);
    offset.q = 0;
    offset.f[2] = 1.0f;
    matrix_mul_vec3(&position, &offset, object + 0xC0);
    FastVecAdd(&position, &position, origin);
    SpawnExplosion(origin, 0, 0, 0, 0, 10, 20, 0, 0.333f, 20.0f, 1, 0, 0, 0);
    FastVecSub(&impulse, origin, gHeroPosition);
    impulse.f[2] = 0.0f;
    vec_scale_to_length(&impulse, &impulse, 0.10000001f);
    SpawnDebrisForMaskedParts(object, 0x1F, impulse.f, 255, 3.0f, 6.0f, 3.0f, 6.0f);
    MarkMobySpawned(object);
}
