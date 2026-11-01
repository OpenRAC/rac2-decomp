#include "include_asm.h"

#include "common.h"
extern int func_002A77E0(int);
extern void func_0029F338(char *);
extern void func_002A7750(char *, int, int);
extern float D_L00_001B19D0;
extern char D_L00_001B8FF0[];
extern int func_PAL_00273A10(char *);
extern int func_00282C30(int);
extern float func_00282C48(float);
extern float func_00282DB0(char *, char *);
extern int func_00283D38(unsigned int, int, float);
extern void func_002A0488(char *, int, int, int);

/* Fades the glow object in and out: opens it when its trigger fires, retires it after two ticks of its counter, and keeps its colour pulsing. */
void func_PAL_L00_0039E608(char *obj)
{
    char *rig = *(char **)(obj + 0x68);
    float shade;
    unsigned int base;
    int color, green, blue;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        if (func_PAL_00273A10(obj) != 0 || (D_L00_001B19D0 > 0.8f && func_002A77E0(10) == 0)) {
            func_002A7750(obj, 1, -1);
            *(u16 *)(obj + 0x34) |= 0x2800;
        }
        break;
    case 1:
        func_PAL_00273A10(obj);
        if (*(u8 *)(obj + 0x23) < 2) {
            func_0029F338(obj);
            return;
        }
        *(u8 *)(obj + 0x23) -= 2;
        break;
    }
    shade = func_00282C48(func_00282DB0(obj + 0xC0, D_L00_001B8FF0));
    shade = shade * (shade * shade * shade * shade);
    if (*(u16 *)(obj + 0x96) != 0) {
        shade = (float)(10 - func_00282C30(*(u16 *)(obj + 0x96) - 10)) * 0.1f;
        *(u16 *)(obj + 0x96) = *(u16 *)(obj + 0x96) - 1;
    } else if (func_002A77E0(0x2D) == 0) {
        *(u16 *)(obj + 0x96) = 0x14;
    }
    base = *(unsigned int *)(rig + 0x50);
    if ((base >> 24) != 0)
        shade = shade * 0.8f;
    color = func_00283D38(base, -1, shade);
    blue = (color >> 16) & 0xFF;
    green = (color >> 8) & 0xFF;
    func_002A0488(obj, color & 0xFF, green, blue);
}
