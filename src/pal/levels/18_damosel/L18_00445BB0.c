#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L18_00445BB0);


#include "common.h"
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern s32 func_002E59B0(void *, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern void *func_002A9640(void *, s32, s32);
extern float func_PAL_002AA108(void *, void *);
extern void func_002A7750(void *, int, int);
extern int func_00283CF0(float);
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern void func_0029F338(void *);
extern void func_L00_00426478(void *);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern void func_PAL_002A7650(void *, int, int);
extern char D_00188660[], D_00189EA0[];
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern char D_00188660[];
extern int func_002E59B0(void *,int),func_002E5CF8(int,int,void *);
extern void func_002E59F8(int);
extern s32 func_002E59B0(void *, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern void *func_002A9640(void *, s32, s32);
extern float func_PAL_002AA108(void *, void *);
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } DamoselSoundAnchor;
extern char D_00188660[];
extern char D_00189EA0[];
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_002AFEB8(void *, void *, void *, void *, float);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern void func_PAL_002A7650(void *, int, int), func_0029F338(void *);
extern void func_L00_00426478(void *);

void func_PAL_L18_00446940(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    char *hit;
    char *owner;
    int excluded;
    float zero, damage;
    float direction[4];
    switch (object[0x20]) {
    case 0:
        *(int *)(state + 0x100) = -1;
        *(unsigned short *)(object + 0x34) |= 0x1000;
        state[0x48] = func_00283CF0(15.0f);
        state[0x4a] = func_00283CF0(6.0f);
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_002B3868(object)) {
            if (*(int *)(state + 0x100) != -1 && ((DamoselSoundAnchor *)(D_00188660 + *(int *)(state + 0x100) * 112))->owner == object && ((DamoselSoundAnchor *)(D_00188660 + *(int *)(state + 0x100) * 112))->active)
                func_002E59F8(*(int *)(state + 0x100));
            *(int *)(state + 0x100) = -1;
        }
        hit = func_002A9640(object, 0x10000, 0);
        if (!hit) goto intact;
        owner = *(char **)(hit + 0x20);
        excluded = 0;
        if (owner && (*(short *)(owner + 0xaa) == 0xb69 || *(short *)(owner + 0xaa) == 0xf9e)) excluded = 1;
        if (excluded) break;
        zero = 0.0f;
        damage = func_PAL_002AA108(object, hit);
        object[0xa8] = 255;
        *(float *)(state + 0x20) -= damage;
        if (*(float *)(state + 0x20) <= zero) {
            func_PAL_002AC718(object, object + 0x10, 0, zero, zero, 10, 3, 9,
                         4.0f, 2.0f, 9.0f, zero, -1, 15.0f, 1, 1, -1, 0, 0x810001);
            func_002E5CF8(0, 0, object);
            func_00282CF0(direction, (float *)(object + 0x10), (float *)D_00189EA0);
            func_002AFEB8(object, direction, direction, 0, zero);
            func_00282F20((char *)direction, (char *)direction, 0.120000005f);
            func_PAL_002B15D8(object, 0x1fff, direction, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            func_PAL_002A7650(object, 0, 3);
            func_0029F338(object);
        }
        break;
intact:
        func_L00_00426478(object);
        break;
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L18_0044C9C0);
