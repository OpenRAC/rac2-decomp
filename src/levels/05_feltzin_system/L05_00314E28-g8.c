#include "include_asm.h"
#include "common.h"

/* Built with -G8: the three small-data globals are reached through $gp in retail,
   the rest of the file's symbols are addressed absolutely. */

extern int D_L05_00221D10[];

extern unsigned char D_L05_001B2000;

extern unsigned char D_L05_001B2001;

extern unsigned char D_L05_001B2002;

extern float D_L05_001B2004;

extern float D_L05_001B2008;

extern float D_L05_001B200C;

extern float D_L05_001B2010;

extern int D_L05_001B2014;

extern unsigned char D_L05_001B3558;

extern unsigned char D_L05_001B3559;

extern unsigned char D_L05_001B355A;

extern float D_L05_001B355C;

extern float D_L05_001B3560;

extern float D_L05_001B3564;

extern float D_L05_001B3568;

extern int D_L05_001B356C;

extern int D_L05_001B1360 __attribute__((sda));

extern int D_L05_001B1364 __attribute__((sda));

extern int D_L05_001B13E8 __attribute__((sda));

extern int D_L05_001B13B0 __attribute__((sda));

extern int D_L05_001B13B4 __attribute__((sda));

extern int D_L05_001B13B8 __attribute__((sda));

extern int D_L05_001B13F0 __attribute__((sda));

extern unsigned char D_L05_001B4568 __attribute__((sda));

extern void func_379F28(int a0);

extern void func_37D6E8(void);

extern void func_379F68(void);

extern void func_37B210(void);

extern void func_379F18(int a0);

extern int func_442860(void);

extern void func_445A98(void);

extern void func_328870(int a0);

extern int D_L05_001B1350 __attribute__((sda));

extern char *func_002A9640(char *a0, char *a1, int a2);

extern void func_002AB8C0(char *a0, char *a1);

extern void func_002AB800(char *a0, char *a1);

extern int func_002E5DA0(int a0, int a1, char *a2, int a3);

extern int func_002A77E0(int kind);

extern float func_002A7878(float a, float b);

extern void func_L05_00398F18(void *a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
                              float f8);

extern void func_L05_00424990(void *a0, void *a1, int a2, int a3, int a4, int a5, int a6, int a7,
                              int a8, int a9, int a10, float f12);

extern void func_L05_00421908(char *a0, int a1, int a2);

extern int func_L05_0037BBB8(char *a0);

extern void func_L05_0037BE98(char *a0);

extern void func_L05_0037AE40(char *a0);

/* Same reset, plus the shutdown of the two cached records. */
void func_L05_0041FD48(void)
{
    char *p;
    int one = 1;

    func_37B210();
    func_379F18(1);
    p = (char *)D_L05_00221D10;
    *(int *)(p + 0x28) = 100;
    *(float *)(p + 0x30) = 8.0f;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0xC) = 0;
    D_L05_001B1364 = 0;
    *(int *)(p + 0x14) = 0;
    *(int *)(p + 0x2C) = one;
    D_L05_001B13F0 = 0;
    func_379F28(0);
    if (func_442860() != 0) {
        *(int *)(p + 0x2C) = 0;
        *(unsigned char *)(D_L05_001B13B0 + 0x20) = one;
    }
    func_37D6E8();
    func_379F68();
    func_445A98();
    if (D_L05_001B13B4 != 0) {
        func_328870(D_L05_001B13B4);
        D_L05_001B13B4 = 0;
    }
    if (D_L05_001B13B8 != 0) {
        func_328870(D_L05_001B13B8);
        D_L05_001B13B8 = 0;
    }
    D_L05_001B2000 = D_L05_001B3558;
    D_L05_001B2001 = D_L05_001B3559;
    D_L05_001B2002 = D_L05_001B355A;
    D_L05_001B2008 = D_L05_001B3560;
    D_L05_001B2010 = D_L05_001B3568;
    D_L05_001B2004 = D_L05_001B355C;
    D_L05_001B200C = D_L05_001B3564;
    D_L05_001B2014 = D_L05_001B356C;
}

/* The moby's death timer: it ticks the stored time down and, once it reaches zero,
   fires the object's effect and takes the moby down, which it reports. */
int func_L05_0041FFF8(char *obj, int flag)
{
    char *attached;
    float *health;
    char *hitSource;
    char *vars;
    float burstPos[3];
    int ret = 0;

    hitSource = FindOwnedEffectSlot(obj, (char *)0x230000, 0);
    *(unsigned char *)(obj + 0xA8) = 0xFF;
    vars = *(char **)(obj + 0x68);
    attached = *(char **)(vars + 0x10);
    health = *(float **)(vars + 0x0);
    if (attached != 0) {
        UpdateColorFade(obj, attached);
    }
    if (hitSource != 0) {
        if (attached != 0) {
            *(unsigned char *)(attached + 7) = 0xFF;
            StartColorFade(obj, attached);
        }
        *health = *health - *(float *)(hitSource + 0x2C);
        if (*(short *)(obj + 0xAA) != 0xB73) {
            PlaySoundFromClassBank(0xD, 0, obj, 0xFBF);
            if (RandomIntBelow(3) == 0) {
                if (*(short *)(obj + 0xAA) == 0x10F5) {
                    PlaySoundFromClassBank(1, 0, obj, 0x10F5);
                } else {
                    PlaySoundFromClassBank(0xB, 0, obj, 0xFBF);
                }
            }
        }
        if (*health <= 0.0f) {
            *health = 0.0f;
            if (*(short *)(obj + 0xAA) == 0x10F5) {
                func_L05_00398F18(obj + 0x10, 0, 0x19, 0, 0, 0x1E, 0, 1, 0.8f);
            } else if (*(short *)(obj + 0xAA) == 0x111A) {
                func_L05_00398F18(obj + 0x10, 0, 0xF, 0, 0, 0x1E, 0, 0, 2.0f);
                burstPos[0] = *(float *)(obj + 0x10) + RandomFloatRange(1.5f, -1.5f);
                burstPos[1] = *(float *)(obj + 0x14) + RandomFloatRange(1.5f, -1.5f);
                burstPos[2] = *(float *)(obj + 0x18) + RandomFloatRange(1.5f, -1.5f);
                func_L05_00398F18(burstPos, 0, 0xF, 0, 0, 0x1E, 0, 0, 2.0f);
                burstPos[0] = *(float *)(obj + 0x10) + RandomFloatRange(1.5f, -1.5f);
                burstPos[1] = *(float *)(obj + 0x14) + RandomFloatRange(1.5f, -1.5f);
                burstPos[2] = *(float *)(obj + 0x18) + RandomFloatRange(1.5f, -1.5f);
                func_L05_00398F18(burstPos, 0, 0xF, 0, 0, 0x1E, 0, 0, 2.0f);
            } else {
                SpawnShockwaveBurst(obj + 0x10, 0, 0x32, 0x1E, 0x1E, 0x1E, 0x28, 1, 1, 0, 0, 0.75f);
            }
            if (D_L05_001B1350 == 0) {
                func_L05_00421908(obj, 1, 5);
            } else {
                func_L05_00421908(obj, 0, 5);
            }
            if (IsObjectInUse(obj)) {
                ReleaseObjectFromGroup(obj);
            }
            if (flag == 0) {
                ResetObjectActionState(obj);
            }
            ret = 1;
        }
    }
    return ret;
}

/* Resets the shared spawn table and copies the mode record into the live one. */
void func_L05_0041FC60(void)
{
    char *p = (char *)D_L05_00221D10;

    D_L05_001B1364 = 0;
    D_L05_001B1360 = -2;
    D_L05_001B13E8 = 1;
    *(int *)(p + 0x2C) = 1;
    *(int *)(p + 0x28) = 100;
    *(int *)(p + 0x14) = 0;
    *(float *)(p + 0x30) = 8.0f;
    func_379F28(0);
    func_37D6E8();
    func_379F68();
    D_L05_001B2000 = D_L05_001B3558;
    D_L05_001B2001 = D_L05_001B3559;
    D_L05_001B2002 = D_L05_001B355A;
    D_L05_001B2008 = D_L05_001B3560;
    D_L05_001B2010 = D_L05_001B3568;
    D_L05_001B2004 = D_L05_001B355C;
    D_L05_001B200C = D_L05_001B3564;
    D_L05_001B2014 = D_L05_001B356C;
}

typedef struct { int words[10]; } SpawnEntry;
extern SpawnEntry D_L05_002A1800[];
extern int func_37AAC8(int a0);

/* Resets the shared spawn table, frees the two cached records and copies the mode record into the live one. */
void func_L05_0041FE98(void)
{
    char *p;
    int i;

    func_37B210();
    func_379F18(1);
    p = (char *)D_L05_00221D10;
    D_L05_001B1360 = -2;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0xC) = 0;
    D_L05_001B13E8 = 1;
    *(int *)(p + 0x2C) = 1;
    *(int *)(p + 0x28) = 100;
    D_L05_001B1364 = 0;
    *(int *)(p + 0x14) = 0;
    i = func_37AAC8(6);
    D_L05_001B13F0 = 0;
    D_L05_002A1800[i].words[5] = D_L05_002A1800[i].words[4];
    func_37D6E8();
    func_379F68();
    func_445A98();
    *(float *)(p + 0x30) = 8.0f;
    func_379F28(0);
    if (D_L05_001B13B4 != 0) {
        func_328870(D_L05_001B13B4);
        D_L05_001B13B4 = 0;
    }
    if (D_L05_001B13B8 != 0) {
        func_328870(D_L05_001B13B8);
        D_L05_001B13B8 = 0;
    }
    D_L05_001B2000 = D_L05_001B3558;
    D_L05_001B2001 = D_L05_001B3559;
    D_L05_001B2002 = D_L05_001B355A;
    D_L05_001B2008 = D_L05_001B3560;
    D_L05_001B2010 = D_L05_001B3568;
    D_L05_001B2004 = D_L05_001B355C;
    D_L05_001B200C = D_L05_001B3564;
    D_L05_001B2014 = D_L05_001B356C;
}
