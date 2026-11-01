#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[0x10];
    float v10[4];
    unsigned char pad20[0x98 - 0x20];
    float f98;
    unsigned char pad9C[0x1270 - 0x9C];
    int f1270;
    unsigned char pad1274[0x1298 - 0x1274];
    int f1298;
    unsigned char pad129C[0x149D - 0x129C];
    unsigned char b149D;
    unsigned char pad149E[0x2290 - 0x149E];
    void *f2290;
    int f2294;
    int f2298;
    int f229C;
} Hero_L00_002A61C8;
extern Hero_L00_002A61C8 D_00189E20;
extern int D_001A79F0 MACRO_ADDR;
extern int func_00283CF0(float);
extern int func_L00_0035F6D8(int, int, int, int, int, int);
extern void func_0029FCC0(char *, int, char *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002A89A8(void *, int, float);
extern float func_00283B98(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
typedef struct Obj_L00_0033BA68 Obj_L00_0033BA68;
extern Obj_L00_0033BA68 *func_PAL_L00_0033DE50(char *, int, float);

void func_PAL_L00_002A6058(int kind, int side, int play_sound, int duration) {
    float point[4];
    float offset[4];
    float heading;
    int special;
    int ticks;
    if (play_sound) {
        special = 0;
        if (D_00189E20.f1270) {
            int mode = D_00189E20.f1298;
            if ((unsigned int)(mode - 19) < 2 || mode == 54)
                special = 1;
        }
        ticks = func_00283CF0((float)((duration << 10) / 30));
        func_L00_0035F6D8(kind, side, special, 0, (int)D_00189E20.f2290, ticks);
    }
    if (D_001A79F0 == 7) {
        if (D_00189E20.b149D == 0) goto effect;
    }
    if (D_001A79F0 != 19) return;
    if (D_00189E20.b149D != 2) return;
effect:
    func_0029FCC0(D_00189E20.f2290, side + 22, (char *)point);
    point[0] += func_00283180(D_00189E20.f98) * 0.05f;
    point[1] += func_00283198(D_00189E20.f98) * 0.05f;
    point[2] = func_002A89A8(point, 0, 0.5f) + 0.057f;
    heading = D_00189E20.f98;
    if (D_00189E20.f2294 == 0 || D_00189E20.f229C == 4) {
        if (side == 0) {
            heading = func_00283B98(heading, 0.436332345f);
            func_00282F20(offset, D_00189E20.v10, 0.037f);
            func_00282CC0(point, point, offset);
        } else {
            heading = func_00283B98(heading, -0.436332345f);
            func_00282F20(offset, D_00189E20.v10, -0.037f);
            func_00282CC0(point, point, offset);
        }
    }
    func_PAL_L00_0033DE50((char *)point, !side, heading);
}
