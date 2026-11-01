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
extern unsigned char *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void func_PAL_002B15D8(char *, int, float *, unsigned char, float, float, float, float);
extern void func_0029F338(void *);

/* The func_L09_004050E0 burst with a particle spray (func_PAL_L00_003FB330) in place of the
   area hit, offset 1.0 up. func_PAL_L00_003FB330 returns a pointer; a void prototype puts the
   stack constant 1 ahead of the 20.0f. */
void func_PAL_L06_00448AB8(char *object)
{
    Vector16 position, offset, impulse;
    char *origin = object + 0x10;
    func_PAL_002A7650(object, 0, 3);
    func_002E5CF8(1, 0, object);
    offset.q = 0;
    offset.f[2] = 1.0f;
    func_00283098(&position, &offset, object + 0xC0);
    func_00282CC0(&position, &position, origin);
    func_PAL_L00_003FB330(origin, 0, 0, 0, 0, 10, 20, 0, 0.333f, 20.0f, 1, 0, 0, 0);
    func_00282CF0(&impulse, origin, D_00189EA0);
    impulse.f[2] = 0.0f;
    func_00282F20(&impulse, &impulse, 0.120000005f);
    func_PAL_002B15D8(object, 0x1F, impulse.f, 255, 3.0f, 6.0f, 3.0f, 6.0f);
    func_0029F338(object);
}
