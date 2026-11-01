#include "include_asm.h"

#include "common.h"
typedef int Vector __attribute__((mode(TI)));
typedef struct {
    unsigned char type;
    unsigned char active;
    unsigned char pad2;
    unsigned char enabled;
    unsigned char pad4[8];
    float fade;
    Vector a;
    Vector b;
    Vector c;
} Effect5518;
typedef struct {
    unsigned char pad[0xEC0];
    Effect5518 effects[7];
    unsigned char pad1080[0x100];
    int counter;
    unsigned char pad1184[0x2290 - 0x1184];
    unsigned char *moby;
} Hero5518;
extern Hero5518 D_00189E20;
typedef struct {
    unsigned char pad[0x274];
    float pitch;
    float yaw;
    unsigned char pad27c[0x8A4 - 0x27C];
    float out_pitch;
    float out_yaw;
} Control5518;
extern Control5518 D_L00_0025BE10;
extern Vector D_L00_0025DD90[7];
extern Vector D_L00_0025DE00[7];
extern Vector D_L00_0025DE70[7];
extern int D_L00_001A7E40[7] SDATA(D_L00_001A7E40);
extern float D_L00_001A7E10[12] SDATA(D_L00_001A7E10);
extern void func_PAL_L00_002A5310(void);
extern void func_0029F9F0(char *, char *);
extern void func_0029F978(unsigned char *, unsigned int, unsigned char *);

/* Clamp control rotations and initialize, fade or retire the hero effects. */
void func_PAL_L00_002A53A8(void)
{
    D_L00_0025BE10.out_yaw = D_L00_0025BE10.yaw * 0.25f;
    if (D_L00_0025BE10.out_yaw > 0.148353f)
        D_L00_0025BE10.out_yaw = 0.148353f;
    else if (D_L00_0025BE10.out_yaw < -0.148353f)
        D_L00_0025BE10.out_yaw = -0.148353f;
    D_L00_0025BE10.out_pitch = D_L00_0025BE10.pitch * 0.35714287f;
    if (D_L00_0025BE10.out_pitch > 0.296706f)
        D_L00_0025BE10.out_pitch = 0.296706f;
    if (D_L00_0025BE10.out_pitch < -0.17453295f)
        D_L00_0025BE10.out_pitch = -0.17453295f;
    if ((unsigned int)(*(unsigned char *)((char *)D_00189E20.moby + 0x43) - 1) < 2) {
        if (D_L00_0025BE10.out_yaw > 0.03490659f)
            D_L00_0025BE10.out_yaw = 0.03490659f;
        if (D_L00_0025BE10.out_yaw < -0.03490659f)
            D_L00_0025BE10.out_yaw = -0.03490659f;
        if (D_L00_0025BE10.out_pitch > 0.122173056f)
            D_L00_0025BE10.out_pitch = 0.122173056f;
        if (D_L00_0025BE10.out_pitch < -0.122173056f)
            D_L00_0025BE10.out_pitch = -0.122173056f;
    }
    func_PAL_L00_002A5310();
    if (D_00189E20.counter == 0)
        return;
    D_00189E20.counter += 1;
    if (D_00189E20.counter >= 12)
        D_00189E20.counter = 0;
    if (D_00189E20.counter == 0) {
        int i;
        for (i = 0; i < 7; i++) {
            if (D_00189E20.effects[i].active)
                func_0029F9F0((char *)D_00189E20.moby, (char *)&D_00189E20.effects[i]);
        }
        return;
    }
    {
        int i;
        for (i = 0; i < 7; i++) {
            if (!D_00189E20.effects[i].active) {
                func_0029F978(D_00189E20.moby, D_L00_001A7E40[i],
                             (unsigned char *)&D_00189E20.effects[i]);
                D_00189E20.effects[i].enabled = 1;
                qcopy(&D_00189E20.effects[i].a, D_L00_0025DD90 + i);
                qcopy(&D_00189E20.effects[i].b, D_L00_0025DE00 + i);
                qcopy(&D_00189E20.effects[i].c, D_L00_0025DE70 + i);
            }
        }
    }
    {
        int i;
        for (i = 0; i < 7; i++)
            D_00189E20.effects[i].fade = D_L00_001A7E10[D_00189E20.counter];
    }
}
