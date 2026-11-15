#include "common.h"

extern void func_L06_004576C8(char *);
extern void func_L06_00457920(char *);
extern void func_L06_004577B0(char *);
extern int func_002A9640(char *, int, int);
extern int func_002A8508(int, int);
extern void func_002A7750(char *, int, int);
extern int func_002B3868(char *);
extern void func_002A0488(char *, int, int, int);
extern int func_002E5CF8(int, int, char *);
extern int func_00282948(char *);
extern void func_002E5E58(int, int, int);
extern void func_002B0A18(int, int);
extern void func_L05_00424990(char *, int, int, int, int, int, int, int, int, int, int, float);
extern void func_L00_00326110(char *, int, float);
extern void func_0029F338(char *);
extern int D_L06_001B375C;
extern int D_L06_001B3758[] __attribute__((sda));
/* This word is written through GP in state 0 and absolutely in state 4. */
extern int D_L06_001B3758_gp SDATA(D_L06_001B3758);
extern int D_L06_001A903C;
/* 32-byte flag table, also scanned by func_002B0E90. */
extern unsigned char D_001A7A60[32] __attribute__((sda));
typedef struct {
    char pad[0x160];
    float scale;
    int pad164;
    int duration;
    int timer;
    char pad170[0x10];
    float speed;
    int pad184;
    int limit;
} EffectState;
extern EffectState D_L06_001B9700;

/* Runs a destructible machine: it waits until hit, then charges up and finally blows apart with a big effect. */
void func_L06_004573E8(unsigned char *obj)
{
    char *vars = *(char **)(obj + 0x68);
    switch (obj[0x20]) {
    case 0:
        SpawnRadialEmitters((char *)obj);
        D_L06_001B375C = 10;
        D_L06_001B3758_gp = 0;
        SetMobyState((char *)obj, 1, -1);
        break;
    case 1:
        if (FindOwnedEffectSlot((char *)obj, 0x4010000, 0) &&
            !CountMobysInGroupNotInState(*(int *)(vars + 0x64), -1) &&
            !CountMobysInGroupNotInState(*(int *)(vars + 0x68), -1) &&
            !CountMobysInGroupNotInState(*(int *)(vars + 0x6C), -1) &&
            !CountMobysInGroupNotInState(*(int *)(vars + 0x60), -1))
            SetMobyState((char *)obj, 3, -1);
        obj[0xA8] = 255;
        break;
    case 3:
        if (SetFirstPendingFlag((char *)obj)) {
            SpawnDebrisPieces((char *)obj);
            *(float *)(obj + 0x2C) *= .9f;
            set_moby_color((char *)obj, 255, 127, 127);
            *(unsigned short *)(obj + 0x34) |= 0x200;
            *(int *)(vars + 0x130) = 180;
            gCameraState_L06.speed = .02f;
            gCameraState_L06.limit = 180;
            gCameraState_L06.scale = .4f;
            gCameraState_L06.duration = 120;
            gCameraState_L06.timer = 0;
            PlayMobySound(0, 0, (char *)obj);
        }
        UpdateSpinningObjectRing((char *)obj);
        if (D_L06_001B375C < 127) ++D_L06_001B375C;
        if (FastFloatHelperD(vars + 0x130)) SetMobyState((char *)obj, 4, -1);
        break;
    case 4:
        if (SetFirstPendingFlag((char *)obj)) {
            PlayMobySound(1, 0, (char *)obj);
            if (!D_001A7A60[17]) {
                D_001A7A60[17] = 1;
                PlaySoundFromGlobalBank(1, 0, 0);
                SetEntryValueByIndex(0x1233, -1);
                D_L06_001A903C = 1;
            }
            SpawnShockwaveBurst((char *)obj + 0x10, 1, 25, 20, 20, 20, 45, 1, 1, 1, 1, 7);
            SpawnScaledBolts((char *)obj, 20, 0);
            D_L06_001B3758[0] = 1;
            gCameraState_L06.speed = .05f;
            gCameraState_L06.limit = 180;
            gCameraState_L06.scale = .05f;
            gCameraState_L06.duration = 120;
            gCameraState_L06.timer = 0;
            MarkMobySpawned((char *)obj);
        }
    }
}
