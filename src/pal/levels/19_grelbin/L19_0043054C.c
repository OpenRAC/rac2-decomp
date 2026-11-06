#include "include_asm.h"
/* func_PAL_L19_0043054C, the PAL copy of func_L19_0042A9A0: the same C, where the 10-tick blends
 * become 8, 120 becomes 100, the two random timers take the (x * 5 + 2) / 6 scale, blend is set
 * beside rate in both paths (retail loads 0.3f in each), and both final arguments are multiplied
 * by 1.44f. */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { u8 prefix[0x30]; int field30,field34,field38,field3c,field40,field44; } L19UtilityQueueView;
extern int D_L19_001B2508[] __attribute__((sda));
extern int D_L19_001B2724[4] __attribute__((sda));
extern int D_L19_001A8F00 __attribute__((sda));
extern u8 *D_L19_001B2A1C __attribute__((sda));
extern u8 D_001A7A40[] __attribute__((sda));
extern u32 D_00139800;
extern L19UtilityQueueView D_L19_001BFC40;
typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; Quadword q[0x260]; } Hero;
extern u8 D_00189E20[];
extern void func_L19_0042A8B8(void);
extern int func_L19_0042A860(void);
extern void func_0029F338(void *);
extern void func_002A7750(u8 *,u8,int);
extern void func_L01_003128C0(char *);
extern int func_L01_003245E0(u8 *,int,float);
extern void func_L01_003246D0(u8 *);
extern int func_00288AA0(u8 *,int);
extern int func_00288BE8(L19UtilityQueueView *);
extern int func_002F5D10(void);
extern int func_00282978(void *);
extern int func_00282948(void *);
extern float func_002A7878(float,float);
extern int func_00283CF0(float);
extern void func_PAL_002A7E68(u8 *,int,int,int);
extern float func_00282E80(void *,void *);
extern float func_00283248(float,float);
extern float func_00283C80(float,float);
extern float func_00282DF0(void *);
extern float func_00283B98(float,float);
extern void func_002AF000(float *,float,float,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern float func_00283BE0(float,float);
extern float func_00282E20(void *);
extern void func_002AEC48(void *,void *,int,float,float);

void func_PAL_L19_0043054C(u8 *object)
{
    Vector target, origin, direction;
    u8 *state = *(u8 **)(object + 0x68);
    float rate, yaw, pitch, rotation, radians;
    int aiming;
    float blend;

    func_L19_0042A8B8();
    if (D_L19_001B2508[0] == 5) func_L19_0042A860();
    switch (object[0x20]) {
    case 0:
        func_L19_0042A860();
        if (D_00139800 & 0x4000000) {
            if (*(int *)(state+0x124) != -1)
                func_0029F338(D_L19_001B2A1C + *(int *)(state+0x124)*0x100);
            *(int *)(state+0x124) = -1;
            func_0029F338(object);
            return;
        }
        if (D_00139800 & 0x1000000) {
            func_0029F338(object);
            return;
        }
        func_002A7750(object,1,-1);
        func_L01_003128C0((char *)object);
        break;
    case 1:
        if (func_L01_003245E0(object,10,2.5f)) {
            func_L01_003246D0(object);
            if (func_00288AA0((u8 *)&D_L19_001BFC40,0x98)) {
                func_00288BE8(&D_L19_001BFC40);
                func_002A7750(object,2,-1);
            }
        }
        break;
    case 2:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00 == 2) {
            object[0x31]=0;
            *(u16 *)(object+0x34) |= 1;
        }
        if (!func_002F5D10()) {
            D_L19_001B2724[1] = 0;
            object[0x31] = 1;
            *(u16 *)(object+0x34) &= 0xfffe;
            func_0029F338(object);
            return;
        }
        break;
    }
    if (object[0x20]) {
        if (object[0x43] == 1 && func_00282978(state+0x11e)) {
            *(short *)(state+0x11e) = func_00283CF0((func_002A7878(1200.0f,2400.0f) * 5.0f + 2.0f) * 0.16666667f);
            if (object[0x43] != 2) func_PAL_002A7E68(object,2,0,8);
        } else if (object[0x60] & 2) {
            if (object[0x43] != 1) func_PAL_002A7E68(object,1,0,8);
        }
    }
    aiming = 0;
    rate = 0.02f;
    blend = 0.3f;
    if (object[0x43] == 1) {
        aiming = 1;
        if (func_00282E80(object+0x10,&((Hero *)D_00189E20)->q[8]) < 8.0f &&
            func_00283C80(*(float *)(object+0xf8),
                func_00283248(((Hero *)D_00189E20)->f[0xe0 / 4]-*(float *)(object+0x10),
                             ((Hero *)D_00189E20)->f[0xe4 / 4]-*(float *)(object+0x14))) < 1.5707965f) {
            if (func_00282DF0(&((Hero *)D_00189E20)->q[0x110 / 16])>0.01f) *(int *)(state+0x114)=100;
            else func_00282948(state+0x114);
        } else if (*(int *)(state+0x114)) {
            *(int *)(state+0x114)=0;
            qcopy(state+0x100, &((Hero *)D_00189E20)->q[0xe0 / 16]);
        }
        if (func_00282948(state+0x118)) {
            radians=0.017453294f;
            *(int *)(state+0x118)=func_00283CF0((func_002A7878(180.0f,300.0f) * 5.0f + 2.0f) * 0.16666667f);
            rotation=func_00283B98(*(float *)(object+0xf8),func_002A7878(-90.0f,90.0f)*radians);
            func_002AF000((float *)(state+0x100),6.0f,rotation,func_002A7878(0.0f,30.0f)*radians);
            func_00282CC0(state+0x100,state+0x100,object+0x10);
        }
        if (*(int *)(state+0x114)) {
            qcopy(&target, &((Hero *)D_00189E20)->q[0xe0 / 16]);
            rate=0.04f;
            blend=0.3f;
        } else qcopy(&target, state+0x100);
    }
    if (aiming) {
        qcopy(&origin, object+0x10);
        origin.f[2]+=2.0f;
        func_00282CF0(&direction,&target,&origin);
        yaw=func_00283BE0(func_00283248(direction.f[0],direction.f[1]),*(float *)(object+0xf8));
        pitch=-func_00283248(func_00282E20(&direction),direction.f[2]);
        if (yaw>1.5707965f) yaw=1.5707965f;
        else if (yaw< -1.5707965f) yaw= -1.5707965f;
        if (pitch>0.52359885f) pitch=0.52359885f;
        else if (pitch< -0.52359885f) pitch= -0.52359885f;
        *(float *)(state+0x64)=pitch;
        *(float *)(state+0x68)=yaw*0.6f;
        *(float *)(state+0xe8)=yaw*0.4f;
    }
    if (D_001A7A40[0]) *(float *)(state+0x70)=1.9f;
    func_002AEC48(object,state,0,rate*1.44f,blend*1.44f);
    func_002AEC48(object,state+0x80,1,rate*1.44f,blend*1.44f);
}
