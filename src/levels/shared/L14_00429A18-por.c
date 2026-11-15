/* func_L14_00429A18: the func_L07_003E7240 launch burst without the flag and timer reset
 * (state block at +0x300). SpawnExplosion returns a pointer: with a void prototype the
 * constant 1 for the stack argument is scheduled ahead of the 20.0f. */
#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_00325D30(char *, char *);

extern void func_002A6C58(char *, int, int);

extern void func_00283098(TI128 *, TI128 *, char *);

extern void func_00282CC0(TI128 *, TI128 *, char *);

extern unsigned char *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int,
                                    int, int, void *);

extern void func_002E5CF8(int, int, char *);

extern void func_00282F20(TI128 *, TI128 *, float);

extern void func_002B0A68(char *, int, TI128 *, float, float, float, float, int);


void func_L14_00429A18(char *arg)
{
    char *o;
    TI128 v[1];
    TI128 w;

    o = *(char **)(arg + 0x68);
    func_00325D30(arg, o + 0x300);
    SetDeathBits(arg, 0, 3);
    v[0] = 0;
    ((float *)v)[2] = 0.75f;
    matrix_mul_vec3(v, v, arg + 0xC0);
    FastVecAdd(v, v, arg + 0x10);
    SpawnExplosion(v, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f, 1, 0, 0, 0);
    PlayMobySound(6, 0, arg);
    vec_scale_to_length(&w, o + 0x1C0, 0.05000000447034836f);
    func_002B0A68(arg, 1016, &w, 3.0f, 6.0f, 3.0f, 6.0f, 255);
}
