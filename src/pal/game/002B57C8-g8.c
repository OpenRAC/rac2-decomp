#include "include_asm.h"

extern void *D_0026CBB0[];
extern void *D_0026CBE0[];
extern int D_001A8BB0;
extern int D_001A8BB4;
extern int D_001A8BB8;
extern int D_0018C2EC __attribute__((nosda));
extern int D_001AA0F4 __attribute__((sda));
extern int D_001AA0F8 __attribute__((sda));
extern int D_001AA0FC __attribute__((sda));
extern char *D_001AA104 __attribute__((sda));
extern float D_001A8C7C;
extern float D_001B15A0;
extern int D_001B1694;
extern float D_001B90F0 __attribute__((nosda));
extern int D_001ABD80;
extern void func_PAL_002CB5D0(void);
extern void func_00285860(void);
extern void func_002F5EF8(void);
extern void func_PAL_002F66F8(void);
extern void func_0026FF08(int, int, float, float, float, float);
extern void func_0027AB40(void);
extern void func_PAL_002E8030(void);
extern void func_PAL_002F96D8(void);
extern void func_002DF380(void);
extern void func_PAL_00300300(void);
extern void func_PAL_00291A40(void);
extern void func_00282A28(void);
extern void func_PAL_002B5540(int);
extern int func_002857B0(void);
extern void func_PAL_002CAAF0(int);
extern void func_002858C0(int, int);
extern void func_002F5D40(int);
extern float func_002AA2E8(float *, float, float);
extern void func_PAL_002F6318(int);
extern void func_00288CB0(int, int);
extern void func_002E71B8(void);
extern void func_002E7090(int);
extern void func_PAL_002E7E00(void);
extern void func_PAL_002F90E8(int);
extern void func_002DF2E0(int, int);
extern void func_PAL_00300130(void);
extern void func_PAL_00291A20(void);

/* Applies a requested change of mode: D_001A8BB8 holds the requested mode (-2 when none) and
   D_001A8BB0 the current one. The first dispatch runs the handler of the mode being left and the
   second the handler of the mode being entered; unless that one holds the change (hold), the
   request becomes the current mode and is cleared. Both dispatches read the tables retail has in
   its data (ten code addresses each, one per mode, D_0026CBB0 and D_0026CBE0); `leaving` and
   `entering` only keep the labels alive. A handler reached through a table starts with no known
   values, so D_001A8BB8 is read again where retail reads it (the compare in the first handler of
   mode 3) without any qualifier on the global. */
void func_PAL_002B57D0(void)
{
    static void *leaving[12] = {&&L1_3, &&L1_4, &&L1_1, &&L1_2, &&L1_6, &&L1_5, &&L1_7, &&L1_8, &&L1_9, &&L1_0, &&L1_def, &&shared};
    static void *entering[11] = {&&L2_3, &&L2_0, &&L2_4, &&L2_1, &&L2_2, &&L2_6, &&L2_5, &&L2_7, &&L2_8, &&L2_9, &&L2_def};
    int mode = D_001A8BB0;
    int sel;
    int hold;
    D_001A8BB4 = mode;
    if (D_001A8BB8 == -2)
        return;
    if (D_001AA0F4 > 0) {
        D_001AA0F4--;
        return;
    }
    if (D_0018C2EC == 0)
        return;
    if ((unsigned)mode >= 10)
        goto L1_def;
    goto *D_0026CBB0[mode];
L1_3:
    if (D_001A8BB8 != 4 || D_001AA0F8 == 8)
        func_PAL_002CB5D0();
    goto E1;
L1_4:
    func_00285860();
    goto E1;
L1_1:
    func_002F5EF8();
    goto shared;
L1_2:
    func_PAL_002F66F8();
shared:
    D_001B90F0 = 0.62f;
    func_0026FF08(0, 3, 1.1243411f, 0.005f, 0.2f, 0.0f);
    func_0027AB40();
    goto E1;
L1_6:
    if (D_001AA0F8 != 4)
        func_PAL_002E8030();
    goto E1;
L1_5:
    func_PAL_002F96D8();
    goto E1;
L1_7:
    func_002DF380();
    goto E1;
L1_8:
    func_PAL_00300300();
    goto E1;
L1_9:
    func_PAL_00291A40();
    goto E1;
L1_def:
    func_00282A28();
L1_0:
E1:
    func_PAL_002B5540(10);
    hold = 0;
    sel = D_001A8BB8;
    if ((unsigned)sel >= 10)
        goto L2_def;
    goto *D_0026CBE0[sel];
L2_3:
    if (D_001A8BB4 != 4 || func_002857B0() == 8)
        func_PAL_002CAAF0(D_001AA0F8);
L2_0:
    hold = 0;
    goto E2;
L2_4:
    func_002858C0(D_001AA0F8, D_001AA0FC);
    goto E2;
L2_1:
    func_002F5D40(D_001AA0FC);
    hold = 0;
    goto E2;
L2_2:
    if ((unsigned)(D_001A8BB0 - 1) >= 2) {
        float f;
        func_002AA2E8(&D_001A8C7C, 1.4f, 0.120000005f);
        f = D_001A8C7C;
        D_001B15A0 = f;
        if (1.0f < f)
            D_001B15A0 = 1.0f;
        if (1.4f <= f) {
            hold = 0;
            D_001A8C7C = 1.0f;
            func_PAL_002F6318(D_001AA0F8);
        } else {
            hold = 1;
        }
    } else {
        func_PAL_002F6318(D_001AA0F8);
    }
    goto E2;
L2_6:
    if (D_001AA0F8 == 5) {
        func_00288CB0(D_001AA0FC, 1);
    } else if (D_001AA0F8 == 6) {
        func_002E71B8();
    } else {
        if (D_001A8BB4 == 3)
            func_002E7090(D_001AA0FC);
        else
            func_PAL_002E7E00();
        D_001B1694 = 1;
    }
    goto E2;
L2_5:
    func_PAL_002F90E8(D_001AA0F8);
    goto E2;
L2_7:
    {
        int fallback = D_001ABD80;
        func_002DF2E0(D_001AA0F8 ? D_001AA0F8 : fallback, D_001AA0FC);
    }
    goto E2;
L2_8:
    func_PAL_00300130();
    goto E2;
L2_9:
    func_PAL_00291A20();
    goto E2;
L2_def:
    func_00282A28();
E2:
    if (hold == 0) {
        int state;
        if (D_001AA104 != 0)
            *D_001AA104 = 1;
        state = D_001A8BB8;
        D_001A8BB8 = -2;
        D_001A8BB0 = state;
        D_001AA104 = 0;
    }
}

typedef struct {
    char pad0[0x10];
    float pos[4];                        
    char pad1[0xF8 - 0x20];
    float heading;                       
} Self_002B52A0;
typedef struct {
    char pad0[0x14];
    float f14, f18, f1C, f20, f24, f28, f2C, f30, f34;       
    unsigned flags38;                    
    char pad1[0x50 - 0x3C];
    float v50[4];                        
    float f60, f64;                      
    char pad3[0x80 - 0x68];
    int w80;                             
    char pad4[0x90 - 0x84];
    volatile float f90;  
    unsigned flags94;                    
    char pad5[0x9C - 0x98];
    int flags9C;                         
    float vel[4];                        
    float speed;                         
    float fB4;                           
    char pad7[0xC0 - 0xB8];
    short hC0, hC2;                      
    char pad8[0xCC - 0xC4];
    float fCC;                           
} Ctl_002B52A0;
extern float D_001AA108 __attribute__((sda));
extern float func_002AAA00(void *, float, void *, int, float, float, float);
extern float func_00283C80(float, float);
extern void func_00282C88(void *);
extern float func_00282E80(void *, void *);
extern float func_00282C10(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_002AC9F8(void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E20(void *);
extern void func_002AAC80(void *, float, float, float, float);

void func_PAL_002B5E58(Self_002B52A0 *self, Ctl_002B52A0 *ctl, void *target, float x)
{
    float local[4] __attribute__((aligned(16)));
    float local2[4] __attribute__((aligned(16)));
    float h, scale, dist, dot, len, len2, diff, g90;

    if (!(ctl->flags38 & 0x10))
        func_002AAA00(&self->heading, x, &ctl->fB4, 0, ctl->f14, ctl->f18, ctl->f1C);
    h = func_00283C80(self->heading, x);
    if (!(ctl->flags38 & 0x10) && ctl->f30 < h) {
        func_00282C88(local);
        if (h - ctl->f30 > ctl->fB4 * 25.0f)
            ctl->flags9C |= 2;
    } else {
        ctl->flags9C &= ~2;
        dist = func_00282E80(self->pos, target);
        ctl->fCC = dist;
        if (dist <= ctl->f34) {
            func_00282C88(local);
        } else {
            scale = func_00282C10(2.0f * (dist - ctl->f34) * ctl->f24);
            if (ctl->f28 < scale)
                scale = ctl->f28;
            h = x;
            if (ctl->w80 != 0) {
                x = func_00283B98(func_00283248(ctl->f60 - self->pos[0], ctl->f64 - self->pos[1]), 3.14159f);
                h = func_00283BE0(h, x);
                if (D_001AA108 < h)
                    h = D_001AA108;
                else if (h < -D_001AA108)
                    h = -D_001AA108;
                h = func_00283B98(h, x);
            }
            local[0] = func_00283180(h) * scale;
            local[1] = func_00283198(h) * scale;
            local[2] = 0;
        }
    }
    func_00282CF0(local2, local, ctl->vel);
    local2[2] = 0;
    dot = func_00282DB0(local, ctl->vel);
    if (0.0f < dot)
        func_002AC9F8(local2, ctl->f20);
    else
        func_002AC9F8(local2, ctl->f24);
    func_00282CC0(ctl->vel, ctl->vel, local2);
    len = func_00282E20(ctl->vel);
    ctl->speed = len;
    if (ctl->flags38 & 4)
        return;
    g90 = ctl->f90;
    if (g90 < self->pos[2]) {
        if (ctl->hC2 < 2) {
            if (self->pos[2] - g90 < 0.15f) {
                len2 = func_00282E20(ctl->v50);
                if (0.087266475f < func_00283248(ctl->v50[2], len2)) {
                    if (-func_00282DB0(ctl->vel, ctl->v50) < ctl->vel[2])
                        ctl->vel[2] = -func_00282DB0(ctl->vel, ctl->v50);
                }
            }
        }
        ctl->vel[2] = ctl->vel[2] - ctl->f2C;
        if (ctl->hC0 == 0)
            ctl->flags94 |= 0x20;
    } else {
        diff = g90 - self->pos[2];
        if (diff < ctl->vel[2])
            ctl->vel[2] = diff;
        else if (ctl->vel[2] < 0.0f)
            ctl->vel[2] = 0.0f;
        func_002AAC80(&ctl->vel[2], ctl->f90 - self->pos[2], 0.016f, 0.016f, 1.0f);
    }
}
