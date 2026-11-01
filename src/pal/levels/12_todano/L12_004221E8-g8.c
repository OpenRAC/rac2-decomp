#include "include_asm.h"

#include "common.h"
typedef union {
    f32 f[4];
    u32 q __attribute__((mode(TI)));
} VecDDA8;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
typedef struct {
    u8 pad[0x38];
    f32 z;
    u8 pad3C[0x44];
} NodeDDA8;
extern NodeDDA8 *D_L12_001B2F8C;
extern NodeDDA8 *D_L12_001B2F8C_gp SDATA(D_L12_001B2F8C);
typedef struct {
    u8 pad[0x110];
    f32 direction[4];
    u8 pad120[0x21C];
    u8 *attached;
} HeroDDA8;
extern HeroDDA8 D_00189E20;
extern u8 D_00189EA0[];
extern s32 D_L12_001B29C8;
extern s32 D_L12_001B29C8_gp SDATA(D_L12_001B29C8);
extern f32 D_L12_001B1DE8 SDATA(D_L12_001B1DE8);
extern f32 D_L12_001B1DF8 SDATA(D_L12_001B1DF8);
extern f32 D_L12_001B1DE0 SDATA(D_L12_001B1DE0);
extern s32 D_L12_001B1DE4 SDATA(D_L12_001B1DE4);
extern s32 D_L12_001B1DF0 SDATA(D_L12_001B1DF0);
extern s32 D_L12_001B1DF4;
extern void func_PAL_L01_0031C9C0(void *, void *, f32, f32, f32, s32);
extern void func_L00_00410D18(void *);
extern s32 func_002ACBC8(void *, s32);
extern void func_002A7750(void *, s32, s32);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern f32 func_00282E80(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern f32 func_00282DB0(void *, void *);
extern f32 func_00282C48(f32);
extern void func_002AAC80(void *, f32, f32, f32, f32);
extern void func_00282F20(void *, void *, f32);
extern f32 func_00282E48(void *, void *);
extern s32 func_00282948(void *);
extern f32 func_00283CE0(s32);
extern s32 func_L01_0031BC68(s32, s32, f32);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Moves between the two node-relative endpoints and pauses before reversing. */
void func_PAL_L12_00423100(u8 *self)
{
    u8 *v = *(u8 **)(self + 0x68);
    f32 oldPos[4] __attribute__((aligned(16)));
    f32 oldRot[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    VecDDA8 motion;
    VecDDA8 temp;
    f32 work[4] __attribute__((aligned(16)));
    f32 speed, oldSpeed, angle;
    s32 *p, i;

    *(u32 *)(v + 0x70)|=2;
    qcopy(oldPos, self + 0x10);
    qcopy(oldRot, self + 0xF0);
    switch (self[0x20]) {
    case 0:
        *(u16 *)(self + 0x34)|=0x1000;
        *(u32 *)(v + 0xDC)|=1;
        self[0x20]=1;
        *(f32 *)(v + 0x140)=*(f32 *)(v + 0x13C)=D_L12_001B1DF8;
        break;
    case 1:
        {
            s32 delay;

            /* The compiler retains this short delay and pads its loop. */
            for (delay = 0; delay < 2; delay++) {}
        }
        func_PAL_L01_0031C9C0(self, v + 0x50, 1.5f, 1.5f, 0.1f, *(s32 *)(v + 0xEC));
        p=(s32 *)(v + 0xE0);
        for (i = 0; i < 2; i++, p++) {
            if (*p != -1)
                func_L00_00410D18(D_L12_001B2E9C_gp + (*p << 8));
        }
        if (*(s32 *)(v + 0xE8)!=-1 && func_002ACBC8(self + 0x10, *(s32 *)(v + 0xE8))) {
            *(s32 *)(v + 0x138)=50;
            func_002A7750(self, 3,-1);
            *(u16 *)(self + 0x34)&=0xEFFF;
            *(f32 *)(v + 0x130)=1.0f;
        }
        break;
    case 2:
        temp.q = 0;
        temp.f[0]=*(f32 *)(v + 0x130);
        motion.q=temp.q;
        func_00283098(&motion, &motion, &D_L12_001B2F8C[*(s32 *)(v + 0xE8)]);
        func_00282CC0(&motion, &motion,(u8 *)&D_L12_001B2F8C[*(s32 *)(v + 0xE8)]+0x30);
        speed=func_00282E80(self + 0x10, &motion);
        if (D_00189E20.attached!=self && D_L12_001B29C8%25==0) {
            func_00282CF0(&temp, self + 0x10, &motion);
            angle=func_00282DB0(&temp, D_00189E20.direction);
            if (func_00282C48(angle)<*(f32 *)(v + 0x134)*0.9f) {
                if (*(f32 *)(v + 0x13C)>3.0f) *(f32 *)(v + 0x13C)-=0.5f;
                if (*(f32 *)(v + 0x140)<9.0f) *(f32 *)(v + 0x140)+=0.5f;
            } else {
                if (*(f32 *)(v + 0x13C)<9.0f) *(f32 *)(v + 0x13C)+=0.5f;
                if (*(f32 *)(v + 0x140)>3.0f) *(f32 *)(v + 0x140)-=0.5f;
            }
        }
        oldSpeed=*(f32 *)(v + 0x134);
        func_002AAC80(v + 0x134, speed, *(f32 *)(v + 0x13C)*0.00040000002f, *(f32 *)(v + 0x140)*0.00040000002f, D_L12_001B1DE8*0.020000001f);
        func_00282CF0(delta, &motion, self + 0x10);
        delta[2]=0;
        func_00282F20(delta, delta, *(f32 *)(v + 0x134));
        qcopy(&temp, D_00189EA0);
        if (func_00282C48(temp.f[2]-D_L12_001B2F8C[*(s32 *)(v + 0xE8)].z)<2.5f)
            temp.f[2]=D_L12_001B2F8C_gp[*(s32 *)(v + 0xE8)].z;
        if (func_002ACBC8(&temp, *(s32 *)(v + 0xE8))) {
            func_00282CF0(work, &temp, self + 0x10);
            {
                s32 positive;

                if (func_00282DB0(work, delta) >= 0.0f)
                    positive = 1;
                else
                    positive = 0;
                if (positive == D_L12_001B1DE4 &&
                    func_00282E48(&temp, self + 0x10) < D_L12_001B1DE0) {
                    *(f32 *)(v + 0x134) = oldSpeed;
                    break;
                }
            }
        }
        func_00282CC0(self + 0x10, self + 0x10, delta);
        if (speed<0.01f) {
            *(s32 *)(v + 0x138)=50;
            *(f32 *)(v + 0x130)=-*(f32 *)(v + 0x130);
            func_002A7750(self, 3,-1);
        }
        break;
    case 3:
        if (func_00282948(v + 0x138)) func_002A7750(self, 2,-1);
        break;
    }
    if (self[0x31]) {
        angle=func_00283CE0(D_L12_001B29C8_gp%50);
        {
            f32 denominator = func_00283CE0(50);

            angle *= 6.2831855f;
            {
                s32 first = D_L12_001B1DF0;
                s32 second = D_L12_001B1DF4;

                angle /= denominator;
                *(s32 *)(self + 0x78) = func_L01_0031BC68(first, second, angle - 3.1415927f);
            }
        }
    }
    func_00282CF0(delta, self + 0x10, oldPos);
    func_002AD6F0(v + 0xA0, delta, oldRot, self + 0xF0);
}
