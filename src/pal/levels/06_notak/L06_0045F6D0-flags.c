#include "include_asm.h"

#include "common.h"
extern void func_002A7750(char *, int, int);
extern void func_0029F338(char *);
extern void func_00282D30(char *, char *, float);
extern int func_002A9640(char *, int, int);
extern void func_PAL_L06_0045CD20(char *, int, void *, int, float, float, float, float);
extern void func_002E5CF8(int, int, char *);
extern void func_PAL_L00_003281C0(char *, int, float);

void func_PAL_L06_004610E0(unsigned char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        *(unsigned short *)(a0 + 0x34) |= 0x800;
        func_002A7750((char *)a0, 1, -1);
        break;
    case 1:
        if (func_002A9640((char *)a0, 0x4010000, 0) != 0) {
            if (*(int *)o == 0) {
                func_002A7750((char *)a0, 2, -1);
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2: {
        char tmp[16];

        func_00282D30(tmp, (char *)(a0 + 0xD0), -0.040000003f);
        func_PAL_L06_0045CD20((char *)a0, 3, tmp, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_002E5CF8(0, 0, (char *)a0);
        func_PAL_L00_003281C0((char *)a0, 1, 0.0f);
        func_0029F338((char *)a0);
        break;
    }
    }
}

extern void func_PAL_002AC718(void *, void *, int, int, int, int, int, int, int, int, int, int,
                          float, float, float, float, float, float, float);
extern void func_002A7A00(float *, float, float);
extern float func_00282C48(float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern char *func_PAL_002735D0(char *, int, int, int, char *, char *, float *, int, float, float);
extern void func_PAL_L06_00461470(unsigned char *);

/* Looks up the object bound to the given flags; unless the hit object's own field says
   0xFE5, it starts a smoke emitter, spawns one particle with the level's own callback
   and six more in a loop, then clears the object's byte at 0xA8. */
void func_PAL_L06_00461210(char *a0)
{
    char *hit;
    char *p;
    float local[3];
    int i;

    hit = (char *)func_002A9640(a0, 0x4010001, 0);
    if (hit != 0 && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        func_002E5CF8(0, 0, a0);
        func_PAL_002AC718(a0, a0 + 0x10, 0, 10, 3, 9, -1, 1, 1, -1, 0, 0x810001,
                      0.0f, 0.0f, 4.0f, 2.0f, 9.0f, 0.0f, 15.0f);
        func_002A7A00(local, 0.040000003f, 0.080000006f);
        local[2] = func_00282C48(local[2]);
        p = func_PAL_002735D0(a0, 1, *(short *)(a0 + 0xAA), 6, a0 + 0x10, a0 + 0xF0,
                          local, 1, func_002A78D8(20.0f, 45.0f), 15.0f);
        if (p != 0) {
            *(void (**)(void))(p + 0x64) = (void (*)(void))func_PAL_L06_00461470;
        }
        for (i = 0; i < 6; i++) {
            func_002A7A00(local, 0.120000005f, 0.24000001f);
            local[2] = func_00282C48(local[2]);
            func_PAL_002735D0(a0, 2, *(short *)(a0 + 0xAA), i, a0 + 0x10, a0 + 0xF0,
                          local, 0xFF, func_002A78D8(20.0f, 45.0f),
                          func_002A7878(15.0f, 25.0f));
        }
        func_002E5CF8(1, 0, a0);
        func_PAL_L00_003281C0(a0, 1, 0.0f);
        func_0029F338(a0);
    }
    *(unsigned char *)(a0 + 0xA8) = 0xFF;
}
