#include "include_asm.h"

#include "common.h"
typedef int Copy128 __attribute__((mode(TI)));
typedef union { Copy128 q; float f[4]; } Vector16;
extern void func_002AB6D8(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern char D_00189EA0[];
extern int D_L02_001A8FF0 __attribute__((sda));
extern void func_PAL_002A7650(char *, int, int);
extern int func_002E5CF8(int, int, char *);
extern void func_00283098(void *, void *, void *);
extern unsigned char *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void func_002AFEB8(char *, void *, void *, float, void *);
extern int func_002A77E0(int);
extern void func_PAL_002B15D8(char *, int, float *, unsigned char, float, float, float, float);
extern void func_0029F338(void *);

/* Spawn the destruction burst and ground impulse, then remove the object. */
void func_PAL_L02_003D2A10(char *object)
{
    Vector16 position, offset;
    float impulse[4];
    char *origin;
    int colour;

    if (*(short *)(*(char **)(object + 0x68) + 0x338) != 0)
        func_002AB6D8(object + 0xC0, object + 0xF0);
    origin = object + 0x10;
    func_PAL_002A7650(object, 0, 3);
    func_002E5CF8(1, 0, object);
    offset.q = 0;
    offset.f[2] = 1.0f;
    func_00283098(&position, &offset, object + 0xC0);
    func_00282CC0(&position, &position, origin);
    func_PAL_L00_003FB330(origin, 0, 0, 0, 0, 10, 20, 0, 0.333f, 20.0f, 1, 0, 0, 0);
    func_00282CF0(&impulse, origin, D_00189EA0);
    func_002AFEB8(object, &impulse, &impulse, 0.0f, 0);
    func_00282F20(&impulse, &impulse, 0.120000005f);
    if (D_L02_001A8FF0)
        colour = func_002A77E0(255);
    else
        colour = 255;
    func_PAL_002B15D8(object, colour & 0x1F, impulse, 255, 3.0f, 6.0f, 3.0f, 6.0f);
    func_0029F338(object);
}

