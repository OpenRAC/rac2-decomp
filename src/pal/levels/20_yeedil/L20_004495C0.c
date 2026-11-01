#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 v;
    struct { f32 x, y, z, w; } f;
} L20_V4;
extern float func_002A7878(float, float);
extern void func_002833F0(TI128 *, TI128 *);
extern void func_00283738(TI128 *, TI128 *, char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00283098(char *, char *, char *);
extern void func_00282D30(char *, char *, float);

void func_PAL_L20_004495C0(char *arg0, char *arg1, char *arg2, float *arg3) {
    char *state = *(char **)(arg0 + 0x68);
    L20_V4 v1;
    L20_V4 v2;
    L20_V4 v3;
    struct {
        TI128 angles;
        L20_V4 adjustment;
        TI128 basis[3];
    } transform;
    f32 r;

    v1.v = 0;
    v1.f.x = 5.0f;
    v3.v = 0;
    v1.f.z = 5.5f;
    r = func_002A7878(-1.0f, 1.0f);
    v3.f.y = r;
    transform.adjustment.v = 0;
    v2.v = v3.v;
    transform.adjustment.f.z = *(float *)(state + 0x298) * 0.5f;
    transform.angles = transform.adjustment.v;
    func_002833F0(transform.basis, &transform.angles);
    func_00283738(transform.basis, transform.basis, arg0 + 0xC0);
    func_00282CC0((char *)&v1, (char *)&v1, (char *)&v2);
    func_00283098((char *)&v1, (char *)&v1, (char *)&transform.basis);
    func_00282CC0(arg1, (char *)&v1, arg0 + 0x10);
    r = func_002A7878(5.0f, 10.0f);
    v2.f.x = r;
    r = func_002A7878(4.0f, 6.0f);
    v2.f.z = r;
    func_00283098((char *)&v3, (char *)&v2, (char *)&transform.basis);
    func_00282D30(arg2, (char *)&v3, 0.019867549f);
    *arg3 = *arg3 * v2.f.y;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L20_00449750);

INCLUDE_ASM("asm/pal/levels", func_PAL_L20_004497B8);

INCLUDE_ASM("asm/pal/levels", func_PAL_L20_00449870);


INCLUDE_ASM("asm/pal/levels", func_PAL_L20_00449B08);
