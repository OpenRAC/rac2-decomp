#include "include_asm.h"

typedef int Copy128 __attribute__((mode(TI)));
typedef union { Copy128 q; float f[4]; } Vector16;
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern char D_00189EA0[];
extern void func_PAL_002A7650(char *, int, int);
extern int func_002E5CF8(int, int,char*);
extern void func_00283098(void *, void *, void *);
extern void func_PAL_002AD288(char *, void *, int,float, float);
extern void func_PAL_002B15D8(char *, int, float *,unsigned char,float, float,float, float);
extern void func_0029F338(void *);

void func_PAL_L09_0040A050(char *object)
{
    Vector16 position, offset, impulse;
    char *origin = object + 0x10;
    float zero;
    func_PAL_002A7650(object, 0, 3);
    zero = 0.0f;
    func_002E5CF8(1, 0, object);
    offset.q = 0;
    offset.f[2] = 0.75f;
    func_00283098(&position, &offset, object + 0xC0);
    func_00282CC0(&position, &position, origin);
    func_PAL_002AD288(object, &position, -1, 0.333f, zero);
    func_00282CF0(&impulse, origin, D_00189EA0);
    impulse.f[2] = zero;
    func_00282F20(&impulse, &impulse, 0.120000005f);
    func_PAL_002B15D8(object, 0x1F, impulse.f, 255, 3.0f, 6.0f, 3.0f, 6.0f);
    func_0029F338(object);
}
