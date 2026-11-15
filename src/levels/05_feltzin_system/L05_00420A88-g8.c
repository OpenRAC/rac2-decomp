#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern int D_L05_001B1364 __attribute__((sda));
extern int D_L05_001B13F4 __attribute__((sda));
extern int D_L05_001B13D8 __attribute__((sda));
extern int D_L05_001B1350 __attribute__((sda));
extern int D_L05_00221D10[];
extern int D_L05_001B2048;
extern char *D_L05_001B251C;
extern char D_L05_001B1380[] SDATA(D_L05_001B1380);
extern char D_L05_001B1370[] SDATA(D_L05_001B1370);
extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(int);
extern char **func_L05_00379EB8(void);
extern int func_L00_004272A0(void);
extern void func_L05_0037B280(char *, int);
extern void func_L05_0037CEE0(char *, void *, float);
extern void func_L05_0037D608(char *, void *, float);
extern int func_00282948(void *);
extern void func_L05_00442828(void *, void *, int);
extern void func_L05_00445B58(void *, void *);
extern void func_L05_004222D8(void);
extern int func_0029B3E0(int, int);
extern void func_L00_003294F0(char *, int);
extern void func_L05_00379F48(int);
extern void func_002AD7B8(int);
extern void func_L05_00420788(char *, int);

/* Controls the first Feltzin mission: on the first frame it sets up the scene and points the
   nearby objects at a target, later it moves the camera and hands over to the reward code. */
void func_L05_00420A88(char *actor)
{
    Vector a;
    Vector b;
    Vector c;
    char *state = *(char **)(actor + 0x68);
    char **objects;
    int count;
    int secondCount;

    if (D_L05_001B1364 == 0) {
        D_L05_00221D10[11] = 0;
        D_L05_001B1364 = 1;
        music_Unpause();
        InitAllRegisteredEntries();
        SetPlayerStateField13(0);
        objects = GetLevelObjectList();
        count = GetLevelSavedValue();
        a.q = 0;
        a.f[0] = 487.0f;
        a.f[1] = 526.0f;
        a.f[2] = 531.0f;
        if (count > 0) {
            int remaining = count;
            do {
                switch (*(short *)(*objects + 0xAA)) {
                case 0x957 /* moby class 2391 */:
                case 0x97C /* moby class 2428 */:
                case 0xF76 /* moby class 3958 */:
                    SpawnEntryListObjectsWithFlag(*objects, 1);
                    func_L05_0037CEE0(*objects, &a, 64.0f);
                    func_L05_0037D608(*objects, &a, 64.0f);
                    break;
                }
                objects++;
            } while (--remaining != 0);
        }
    }
    if (D_L05_00221D10[4] != 0 || D_L05_001B2048 < 6)
        return;
    if (D_L05_00221D10[5] <= 0) {
        if (FastFloatHelperD(state + 0x58) == 0)
            return;
        *(int *)(state + 0x58) = 120;
        StartShipTransition(D_L05_001B1380, D_L05_001B1370, 200);
        a.q = 0;
        b.q = 0;
        c.q = 0;
        actor[0x20] = 3;
        a.f[0] = 593.5f;
        a.f[1] = 599.0f;
        a.f[2] = 566.0f;
        b.f[0] = 512.5f;
        b.f[1] = 530.0f;
        b.f[2] = 540.0f;
        c.f[0] = 438.0f;
        c.f[1] = 487.0f;
        c.f[2] = 535.0f;
        PointShipCameraAtTarget(&a, &c);
        objects = GetLevelObjectList();
        secondCount = GetLevelSavedValue();
        if (secondCount > 0) {
            int remaining = secondCount;
            do {
                switch (*(short *)(*objects + 0xAA)) {
                case 0x957 /* moby class 2391 */:
                case 0x97C /* moby class 2428 */:
                case 0xF76 /* moby class 3958 */:
                    SpawnEntryListObjectsWithFlag(*objects, 1);
                    func_L05_0037CEE0(*objects, &a, 10.0f);
                    func_L05_0037D608(*objects, &b, 20.0f);
                    break;
                }
                objects++;
            } while (--remaining != 0);
        }
    } else if (D_L05_001B13F4 != 0) {
        if (FastFloatHelperD(state + 0x58) != 0) {
            *(int *)(state + 0x58) = 25;
            D_L05_001B1350++;
            ClampAndSaveFeltzinMissionCounts();
            MemcardSave(0, -1);
            D_L05_001B1350--;
            SetObjectFlagBit(D_L05_001B251C + (*(int *)(state + 0x2C) << 8), 1);
            D_L05_001B13D8 = 0;
            D_L05_001B13F4 = 0;
            SetPlayerStateField18(1);
            MarkFlagAndAppendToList(6);
        }
    } else if (FastFloatHelperD(state + 0x58) != 0) {
        UpdateFeltzinMissionReward(actor, 0);
    }
}
