#include "include_asm.h"
#include "names.h"

typedef int Copy128 __attribute__((mode(TI)));
typedef union { Copy128 q; float f[4]; } Vector16;
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char g_hero_position[];
extern void func_PAL_002A7650(char *, int, int);
extern int PlayMobySound(int, int,char*);
extern void matrix_mul_vec3(void *, void *, void *);
extern unsigned char *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void func_PAL_002B15D8(char *, int, float *, unsigned char, float, float, float, float);
extern void moby_mark_spawned(void *);

/* The func_L09_004050E0 burst with a particle spray (func_PAL_L00_003FB330) in place of the
   area hit, offset 1.0 up. func_PAL_L00_003FB330 returns a pointer; a void prototype puts the
   stack constant 1 ahead of the 20.0f. */
void func_PAL_L06_00448AB8(char *object)
{
    Vector16 position, offset, impulse;
    char *origin = object + 0x10;
    func_PAL_002A7650(object, 0, 3);
    PlayMobySound(1, 0, object);
    offset.q = 0;
    offset.f[2] = 1.0f;
    matrix_mul_vec3(&position, &offset, object + 0xC0);
    FastVecAdd(&position, &position, origin);
    func_PAL_L00_003FB330(origin, 0, 0, 0, 0, 10, 20, 0, 0.333f, 20.0f, 1, 0, 0, 0);
    FastVecSub(&impulse, origin, g_hero_position);
    impulse.f[2] = 0.0f;
    vec_scale_to_length(&impulse, &impulse, 0.120000005f);
    func_PAL_002B15D8(object, 0x1F, impulse.f, 255, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(object);
}
