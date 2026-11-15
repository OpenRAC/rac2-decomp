#include "common.h"
extern float func_00283180(float), func_00283198(float);
extern float func_00283B98(float, float), func_00283BE0(float, float);
extern void func_00282CC0(void *, void *, void *), func_00282C88(void *);
extern void func_0027D330(int), func_L01_002B35E8(int), func_L00_002B9D60(void *, void *, int, int), func_002E5CF8(int, int, void *);
extern void func_00335438(void *, void *, int, int, int), func_00335370(void *), func_003353C8(void *);
extern void func_002A7470(void *, int, int, int), func_L00_002D2168(int, int, float);

extern unsigned char D_001A7A45;
extern int D_L01_001B1FA8;
typedef struct {
    char pad[0x80];
    float pos[4];
    float rot[4];
    char pad2[0x2214];
    unsigned char state;
    char pad3[10];
    unsigned char flag;
} TransitionPlayerState;
extern TransitionPlayerState D_00189E20;
/* Starts the hero arriving from a teleporter: places the hero in front of the moby, sets the camera and a sound, and moves the moby to its next state. */
void func_L01_00397110(unsigned char *moby) {
    float arrivePos[4], arriveRot[4], camPos[4], camRot[4];
    char *vars = *(char **)(moby + 0x68);
    arrivePos[0] = FastSinOrCosA(*(float *)(vars + 0x1C))*2.5f;
    arrivePos[1] = FastSinOrCosB(*(float *)(vars + 0x1C))*2.5f;
    arrivePos[2] = 0;
    FastVecAdd(arrivePos, arrivePos, vars + 0x10);
    ClearVector128(arriveRot);
    arriveRot[2] = FastAddRotations(*(float *)(vars + 0x1C), 3.1415929794311523f);
    FadeToBlack(10);
    if (gHeroState.state == 3) ResetHeroForAreaStart(0);
    ResetHeroPositionAndDirection(arrivePos, arriveRot, 0x6F, 0);
    PlayMobySound(0, 0, moby);
    camPos[0] = FastSinOrCosA(*(float *)(vars + 0x1C))*1.25f;
    camPos[1] = FastSinOrCosB(*(float *)(vars + 0x1C))*1.25f;
    camPos[2] = 0;
    camPos[0] += FastSinOrCosA(FastAddRotations(*(float *)(vars + 0x1C), 1.5707964897155762f))*4.0f;
    camPos[1] += FastSinOrCosB(FastAddRotations(*(float *)(vars + 0x1C), 1.5707964897155762f))*4.0f;
    FastVecAdd(camPos, camPos, vars + 0x10);
    camPos[2] += 1;
    ClearVector128(camRot);
    camRot[2] = fast_subtract_rotations(*(float *)(vars + 0x1C), 1.5707964897155762f);
    SetCamera5Pose(camPos, camRot, 1, 0, 0);
    CopyVectorToSelectedObject(camPos);
    SetCameraStateRotation(camRot);
    qcopy_nc(moby + 0x10, gHeroState.pos);
    qcopy_nc(moby + 0xF0, gHeroState.rot);
    if (moby[0x43] != 1) StartAnimationBlended(moby, 1, 0, 0);
    set_hero_animation(0x7B, 0, 0.0f);
    if (D_001A7A45) *(unsigned short *)(moby + 0x34) |= 0x8000;
    gHeroState.flag = 1;
    D_L01_001B1FA8 = 1;
    moby[0x20] = 2;
    *(int *)(vars + 0x6C) = 60;
}
