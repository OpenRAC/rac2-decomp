/* functional: medium. From the near-miss draft nonmatching/levels/func_L11_00453358.c, read in full against retail
 * (level 11, 1131 instructions, jump table 0x2BBD50: stages 3,4,7..14, 5 and 6 fall to the common tail). Changes from
 * the draft: its ten dead `dist` stores in stage 9 are gone; 0x441A38 in level 11 is func_L02_003FC248 (the draft said
 * func_L11_00441A38); the player block D_00189E20 (+0x80 position, +0x249C object) written as byte offsets; callee
 * prototypes declared here. Calls, arguments, stores and compares are retail's, in its order and compare sense. */
/* func_L11_00453358: level 11 (joba) creature update: faces its target (pv+0x1C4 or the player), then a stage
 * machine on self[0x20]: 3 wake, 4 return, 7 path follow (D_L11_001FF580 paths), 8 approach, 9 grab anim, 10 hold,
 * 11 carry/drop toward the player, 12 release, 13 fall with collision, 14 spin away and die; then orbit clamp around
 * the target, spin damping of pv+0x1B0..0x1B8 into self+0xF0, ground clamp with dust particles, and the sound/update
 * tail (func_002A8C28, func_L11_00454AE0). */
#include "common.h"

typedef float V4[4] __attribute__((aligned(16)));

extern int D_L11_001A8FF4 __attribute__((sda));
extern float D_L11_001B1D40;
extern float D_L11_001B1D44;
extern float D_L11_001B1D48;
extern u8 *D_L11_001FF580[];
extern u8 D_00189E20[];

extern void func_L11_00454508(u8 *);
extern float func_00283248(float, float);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern float *func_L11_004417E8(s32);
extern int func_L11_00441808(void *, void *);
extern int func_002B3868(void *);
extern int func_002B3890(void *);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_L01_00321178(void *, void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_00282C48(float);
extern void func_002A677C(void *);
extern void func_L02_00333438(void *, void *);
extern int func_002B4FF0(void *, void *, float);
extern void func_002AA548(void *, void *, float, float, float, float);
extern int func_002A8C28(void *, void *, int, float, float, float, int, int, int);
extern int func_002A8D70(void *, int, int, float, float, float, int, int, int);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00277258(void *, int, void *, float);
extern void func_L02_003FC248(void *, s32, s32);
extern void func_L11_00454DD8(void *);
extern void func_002AB6D8(void *, void *);
extern int func_L07_00321D68(void *, void *);
extern void func_002B4090(void *, void *, float, float, float);
extern void func_002833F0(void *, void *);
extern float func_002AA150(float, float, float);
extern float func_00283B98(float, float);
extern void func_002A7A00(void *, float, float);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern void func_L11_00454AE0(void *);

#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

void func_L11_00453358(u8 *self)
{
    V4 v00;
    V4 v10;
    V4 v20;
    V4 v30;
    V4 m[3];
    u8 *pv;
    float *target;
    u8 *pos;
    float dist;
    u8 *player = D_00189E20 + 0x80;

    pv = *(u8 **)(self + 0x68);
    if (self[0x20] == 1)
        return;
    if (S16(pv, 0x1FC) != 0 && D_L11_001A8FF4 == 0 && self[0x20] != 14 && self[0x20] != 13)
        return;
    func_L11_00454508(self);
    if (*(u8 **)(pv + 0x1C4) != 0) {
        qcopy(v00, *(u8 **)(pv + 0x1C4) + 0x10);
        func_00283248(F(*(u8 **)(pv + 0x1C4), 0x10) - F(self, 0x10), F(*(u8 **)(pv + 0x1C4), 0x14) - F(self, 0x14));
    } else {
        qcopy(v00, player);
        func_00283248(F(D_00189E20, 0x80) - F(self, 0x10), F(D_00189E20, 0x84) - F(self, 0x14));
    }
    pos = self + 0x10;
    dist = func_00282E48(pos, v00);
    if (self[0x20] == 1)
        return;
    if (S16(pv, 0x1FC) != 0 && D_L11_001A8FF4 == 0)
        return;
    target = 0;
    if (S32(self, 0xB8) != 0)
        target = func_L11_004417E8(S32(self, 0xB8));

    switch (self[0x20]) {
    case 3:
        if (func_002B3868(self) != 0) {
            func_002B60B0(self, 0.027777778f, 1.6666667f, 0.001163553f, 0.10471977f);
            self[0xBC] = 0;
            U16(self, 0x96) = 0;
        }
        if (self[0xBC] == 0 && S16(pv, 0x1EE) < U16(self, 0x96)) {
            self[0xBC] = 1;
            break;
        }
        if (self[0xBC] == 1) {
            if (func_L11_00441808((void *)S32(self, 0xB8), pos) != 0)
                func_002A7750(self, 7, 3);
            func_L01_00321178(self, func_L11_004417E8(S32(self, 0xB8)));
        }
        break;
    case 4:
        if (func_002B3868(self) != 0)
            U16(self, 0x96) = 0;
        if (U16(self, 0x96) < 26)
            break;
        if (self[0x43] != 0)
            func_002A7470(self, 0, 0, 5);
        func_002A7750(self, 8, 3);
        break;
    case 7: {
        u8 *path;
        u8 *p;
        s32 i;
        s32 best;
        float d;
        float lim;

        if (S16(pv, 0x1FC) != 0)
            path = D_L11_001FF580[S32(pv, 0x1E0)];
        else
            path = D_L11_001FF580[S32(pv, 0x1C0)];
        if (func_002B3868(self) != 0) {
            p = path + 0x10;
            best = 0;
            func_002B60B0(self, 0.027777778f, 3.3333335f, 0.001163553f, 0.10471977f);
            F(pv, 0x1C8) = func_002A7878(1.0f, 3.0f);
            d = func_00282E48(pos, p);
            for (i = 0; i < S32(path, 0) - 1; i++, p += 0x10) {
                float e = func_00282E48(pos, p);
                if (e < d) {
                    d = e;
                    best = i;
                }
            }
            S32(pv, 0x1D4) = best;
            S16(pv, 0x1E8) = func_002A77E0(2);
        } else {
            qcopy(v10, path + 0x10 + (S32(pv, 0x1D4) << 4));
            if (S16(pv, 0x1FC) != 0) {
                func_00282CF0(v30, v10, target);
                v30[2] = 0.0f;
                func_00282F20(v30, v30, 15.0f - F(pv, 0x1C8));
                v10[0] = target[0] + v30[0];
                v10[1] = target[1] + v30[1];
            } else {
                v10[2] = F(pv, 0x1C8) + target[2];
            }
            func_00282CF0(v20, v10, pos);
            lim = 2.0f;
            func_00282F20(v20, v20, F(pv, 0x1D8));
            func_00282CC0(pos, pos, v20);
            if (S16(pv, 0x1FC) != 0)
                lim = 4.0f;
            if (S16(pv, 0x1E8) != 0) {
                if (func_00282E48(pos, v10) < lim)
                    S32(pv, 0x1D4) -= 1;
                if (S32(pv, 0x1D4) < 0)
                    S32(pv, 0x1D4) = S32(path, 0) - 1;
            } else {
                if (func_00282E48(pos, v10) < lim)
                    S32(pv, 0x1D4) += 1;
                if (!(S32(pv, 0x1D4) < S32(path, 0)))
                    S32(pv, 0x1D4) = 0;
            }
            if (!(S32(pv, 0x1D4) < S32(path, 0) - 6) && 0.10000001f <= F(pv, 0x1D8))
                F(pv, 0x1D8) = F(pv, 0x1D8) - 0.0025f;
            func_002A677C(self);
            if (S16(pv, 0x1FC) != 0) {
                func_L02_00333438(self, v10);
            } else {
                func_002B4FF0(self, v10, F(pv, 0x1D0));
                func_002AA548(self + 0x18, pv + 0x108, F(pv, 0x1C8), 0.00055555557f, 0.00055555557f, 0.16666667f);
            }
        }
        if (S16(pv, 0x1EC) != 0)
            func_002A7750(self, 8, 3);
        break;
    }
    case 8: {
        s32 flag;

        if (func_002B3868(self) != 0)
            func_002B60B0(self, 0.011111111f, 1.3333334f, 0.001163553f, 0.10471977f);
        flag = 0;
        if (S16(pv, 0x1FC) != 0) {
            if (4.0f < dist) {
                func_00282CF0(v10, v00, pos);
                func_00282F20(v10, v10, 10.0f);
                func_00282CC0(v10, v10, pos);
                func_L02_00333438(self, v10);
            } else {
                func_L02_00333438(self, v00);
            }
            flag = dist < 4.0f;
        } else {
            float z = target[2] + 0.5f;
            func_002AA548(self + 0x18, pv + 0x108, z, 0.0055555557f, 0.027777778f, 0.16666667f);
            func_002B4FF0(self, v00, F(pv, 0x1D0));
            if (func_00282C48(F(self, 0x18) - z) < 0.1f && func_00282E80(pos, player) < 2.0f)
                flag = 1;
        }
        if (flag) {
            U16(self, 0x96) = 0;
            func_002A7750(self, 10, -1);
        }
        func_002A8C28(self, pos, 1, 0.3f, (float)pv[0x34], 1.0f, 0, 1, 0);
        break;
    }
    case 9:
        if (func_002B3868(self) != 0 && self[0x43] != 2)
            func_002A7470(self, 2, 0, 3);
        if (self[0x60] & 2) {
            if (self[0x43] != 3)
                func_002A7470(self, 3, 0, 5);
            func_002A7750(self, 11, -1);
        }
        break;
    case 11: {
        s32 k;
        float lim;

        if (func_002B3890(self) != 0) {
            func_002B60B0(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
            U16(self, 0x96) = 0;
        }
        F(self, 0x48) = 1.75f;
        for (k = 0; k < 4; k++)
            func_002A8D70(self, k, 1, 0.5f, (float)pv[0x34], 1.0f, 0, 1, 0);
        lim = 1.8f;
        if (lim <= func_00282E48(pos, player)) {
            qcopy(v10, v00);
        } else if (func_00282E48(pos, player) < lim) {
            func_00282CF0(v10, pos, v00);
            func_00282F20(v10, v10, 2.0f);
            func_00282CC0(v10, v10, pos);
        } else {
            qcopy(v10, pos);
        }
        if (S16(pv, 0x1FC) != 0) {
            func_L02_00333438(self, v10);
        } else {
            func_002AA548(self + 0x18, pv + 0x108, target[2] + 0.5f, 0.0055555557f, 0.027777778f, 0.16666667f);
            func_L01_00321178(self, v10);
        }
        if (*(u8 **)(D_00189E20 + 0x249C) == self) {
            func_002A7750(self, 12, -1);
            if (self[0x43] != 4)
                func_002A7470(self, 4, 0, 5);
            F(self, 0x48) = 1.0f;
        }
        if (4.0f < func_00282E48(pos, player) && !(U16(self, 0x96) < 121)) {
            if (self[0x43] != 5)
                func_002A7470(self, 5, 0, 15);
            func_002A7750(self, 4, -1);
            F(self, 0x48) = 1.0f;
        }
        break;
    }
    case 12:
        if (!(self[0x60] & 2))
            break;
        if (self[0x43] != 0)
            func_002A7470(self, 0, 0, 15);
        func_002A7750(self, 8, -1);
        break;
    case 10:
        if (!(U16(self, 0x96) < 15)) {
            func_002A7750(self, 9, -1);
            if (self[0x43] != 2)
                func_002A7470(self, 2, 0, 2);
            F(self, 0x48) = 1.0f;
        }
        qcopy(v10, pos);
        if (dist < 1.0f)
            func_002A8C28(self, v10, 1, 0.3f, (float)pv[0x34], 1.0f, 0, 1, 0);
        break;
    case 13:
        qcopy(v10, pos);
        F(pv, 0x108) = F(pv, 0x108) - F(pv, 0x8C);
        func_00282CC0(pos, pos, pv + 0x100);
        if (func_002761F8(v10, pos, 0, self, 0) == 0 && func_00277258(pos, 4, self, 0.3f) == 0 &&
            func_002A77E0(30) != 0)
            break;
        func_002A8C28(self, pos, 0x10000, 0.5f, (float)pv[0x34], 1.0f, 0, 1, 0);
        if (0.0f < F(pv, 0x20)) {
            func_002A7750(self, 8, 3);
            if (self[0x43] != 0)
                func_002A7470(self, 0, 0, 5);
        } else if (S16(pv, 0x1FC) != 0 && func_002A77E0(2) == 0) {
            func_002A7750(self, 14, -1);
        } else {
            func_L02_003FC248(self, 0, 1);
            func_L11_00454DD8(self);
        }
        break;
    case 14: {
        s32 j;
        float *t;

        if (func_002B3868(self) != 0) {
            t = func_L11_004417E8(S32(self, 0xB8));
            func_00282CF0(pv + 0x100, t, pos);
            F(pv, 0x108) = 0.0f;
            func_00282F20(pv + 0x100, pv + 0x100, func_002A7878(3.0f, 5.0f) * 0.016666668f);
            S16(pv, 0x1FC) = 0;
            for (j = 0; j < 3; j++) {
                ((float *)(pv + 0x1B0))[j] = func_002A7878(240.0f, 720.0f) * 0.00029088825f;
                qcopy(m[j], self + 0xC0 + j * 0x10);
            }
            func_002AB6D8(m, self + 0xF0);
            U16(self, 0x34) &= 0xEFFF;
        }
        F(pv, 0x108) = F(pv, 0x108) - F(pv, 0x8C);
        func_L07_00321D68(self, pv + 0x100);
        func_00282D30(pv + 0x1B0, pv + 0x1B0, 0.98f);
        qzero(v20);
        v20[2] = F(pv, 0x30);
        qcopy(v10, v20);
        func_002B4090(self, v10, F(pv, 0x1B0), F(pv, 0x1B4), F(pv, 0x1B8));
        func_002833F0(self + 0xC0, self + 0xF0);
        t = func_L11_004417E8(S32(self, 0xB8));
        if (F(self, 0x18) < t[2] + 5.0f || func_002A77E0(450) == 0 || !(U16(self, 0x96) < 301)) {
            func_L02_003FC248(self, 0, -1);
            func_L11_00454DD8(self);
        }
        break;
    }
    }

    if (S16(pv, 0x1FC) != 0 && self[0x95] != 4) {
        float z = F(self, 0x18);
        func_00282CF0(v10, pos, target);
        v10[2] = 0.0f;
        func_00282F20(v10, v10, 14.3f);
        func_00282CC0(pos, v10, target);
        F(self, 0x18) = z;
    }
    if (self[0x20] != 14) {
        F(pv, 0x1B0) = func_002AA150(F(pv, 0x1B0), D_L11_001B1D40 * 0.00029088825f, 0.0625f);
        F(pv, 0x1B4) = func_002AA150(F(pv, 0x1B4), D_L11_001B1D44 * 0.00029088825f, 0.0625f);
        F(pv, 0x1B8) = func_002AA150(F(pv, 0x1B8), D_L11_001B1D48 * 0.00029088825f, 0.0625f);
        F(self, 0xF0) = func_00283B98(F(self, 0xF0), F(pv, 0x1B0));
        F(self, 0xF4) = func_00283B98(F(self, 0xF4), F(pv, 0x1B4));
        F(self, 0xF8) = func_00283B98(F(self, 0xF8), F(pv, 0x1B8));
    }
    if (target != 0 && S16(pv, 0x1FC) == 0 && F(self, 0x18) <= target[2] + 0.4f) {
        if (self[0x31] == 0) {
            F(pv, 0x108) = 0.016666668f;
            F(self, 0x18) = target[2] + 0.3f;
        } else if (func_00277258(pos, 6, 0, 0.3f) != 0) {
            float s;
            s32 n;

            F(pv, 0x108) = 0.016666668f;
            F(self, 0x18) = target[2] + 0.3f;
            v10[0] = F(self, 0x10) + func_002A7878(-0.01f, 0.01f);
            v10[1] = F(self, 0x14) + func_002A7878(-0.01f, 0.01f);
            v10[2] = F(self, 0x18) - 0.3f;
            s = func_002A7878(0.3f, 0.8f);
            n = func_002A77E0(2);
            if (n == 0)
                n = -1;
            func_002A7A00(v20, 0.0008333334f, 0.050000004f);
            v20[2] = func_002A7878(1.0f, 5.0f) * 0.016666668f;
            func_002C2210(v10, 60, s * 0.1f, s, 0x7F007F7F, 0, n, v20, 0, 0.002f);
        }
    }
    func_002A8C28(self, pos, 0x4000000, 0.8f, 5.0f, 1.0f, 0, 1, 0);
    func_L11_00454AE0(self);
}
