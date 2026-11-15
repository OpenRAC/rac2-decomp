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
extern Obj_L00_0033BA68 *func_L00_0033BA68(char *, int, float);

/* Plays a footstep sound for one foot and, on some ground, spawns a dust puff at that foot. */
void func_L00_002A61C8(int kind, int side, int play_sound, int duration) {
    float point[4];
    float offset[4];
    float heading;
    int special;
    int ticks;
    if (play_sound) {
        special = 0;
        if (gHeroState.f1270) {
            int mode = gHeroState.f1298;
            if ((unsigned int)(mode - 19) < 2 || mode == 54)
                special = 1;
        }
        ticks = FloatToInt((float)((duration << 10) / 30));
        StartEffectFromWeights(kind, side, special, 0, (int)gHeroState.f2290, ticks);
    }
    if (gCurrentMapIndex == 7) {
        if (gHeroState.b149D == 0) goto effect;
    }
    if (gCurrentMapIndex != 19) return;
    if (gHeroState.b149D != 2) return;
effect:
    TransformMobyJointToWorld(gHeroState.f2290, side + 22, (char *)point);
    point[0] += FastSinOrCosA(gHeroState.f98) * 0.05f;
    point[1] += FastSinOrCosB(gHeroState.f98) * 0.05f;
    point[2] = ProbeGroundHeightBelow(point, 0, 0.5f) + 0.057f;
    heading = gHeroState.f98;
    if (gHeroState.f2294 == 0 || gHeroState.f229C == 4) {
        if (side == 0) {
            heading = FastAddRotations(heading, 0.436332345f);
            vec_scale_to_length(offset, gHeroState.v10, 0.037f);
            FastVecAdd(point, point, offset);
        } else {
            heading = FastAddRotations(heading, -0.436332345f);
            vec_scale_to_length(offset, gHeroState.v10, -0.037f);
            FastVecAdd(point, point, offset);
        }
    }
    SpawnGlowEffect((char *)point, !side, heading);
}
