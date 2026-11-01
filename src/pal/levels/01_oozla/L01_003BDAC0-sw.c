#include "include_asm.h"

#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float v[4]; } Vector;
struct Rac2Native_5f824a0e369ccf7b_src_record;
typedef struct {
    float f0;
    float f4;
    float f8;
    float f12;
    float f16;
    float f20;
    unsigned char f24;
    unsigned char f25;
    short f26;
    unsigned char f28;
    unsigned char f29;
    unsigned char f30;
    unsigned char f31;
    unsigned char pad32[16];
    short f48;
    short f50;
    int f52;
    int f56;
    int f60;
} PoolRecord64;
typedef struct {
    unsigned char prefix[0x80];
    Vector position;
    unsigned char pad90[0x50];
    Vector eye;
    unsigned char padF0[0x24C];
    char *interaction;
    int active;
} HeroView;
extern HeroView D_00189E20;
extern unsigned char D_0019B2E8[];
extern int D_001A79F0 MACRO_ADDR;
extern char *D_L01_001FE180[];
extern char *D_L01_001B255C __attribute__((sda));
extern float D_L01_001AFE18[] __attribute__((sda));
extern float D_L01_002A48B0[], D_L01_002A45D0[];
extern struct Rac2Native_5f824a0e369ccf7b_src_record D_L01_00297300;
extern struct Rac2Native_5f824a0e369ccf7b_src_record D_L01_00297380;
extern struct Rac2Native_5f824a0e369ccf7b_src_record D_L01_00297400;
extern float func_PAL_L01_003BEB40(void);
extern int func_001163B0(void);
extern void func_PAL_002A7E68(unsigned char *, int, int, int);
extern void func_002A7750(unsigned char *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00282E20(void *);
extern float func_00282DF0(void *);
extern float func_00283248(float, float);
extern float func_00283180(float), func_00283198(float);
extern float func_00283BE0(float, float), func_00283C80(float, float);
extern int func_00283CF0(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_0029FCC0(char *, int, char *);
extern void *func_002A9640(void *, unsigned int, int);
extern float func_002AA150(float, float, float);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA548(float *, float *, float, float, float, float);
extern float func_002AAA00(float *, float, float *, int, float, float, float);
extern void func_002AAC80(void *, float, float, float, float);
extern void func_002AC9F8(float *, float), func_002ACB48(float *, float);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_002AEC48(void *, void *, int, float, float);
extern void func_002AEF28(float *, float *, float *, float, float, float);
extern void func_PAL_002B14F8(void *, float *, float, int, int);
extern char *func_002C19D8(void *, float, float, void *, int);
extern void func_002C9828(void *, int, void *, void *, int, float);
extern int func_L00_002D6998(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern void func_L00_002D6B70(int);
extern PoolRecord64 *func_PAL_L00_002D7850(int);
extern void func_L00_002D7140(unsigned char *);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
typedef struct {
    unsigned char pad00[0x34];
    unsigned short f34;
    unsigned char pad36[0x62];
    int f98;
} ObjectView;

void func_PAL_L01_003BDAC0(unsigned char *object)
{
    Vector old_position, old_rotation, direction, target, velocity;
    char *context = P(object, 0x68);
    char *outbound = D_L01_001FE180[I(context, 0x290)];
    char *inbound = D_L01_001FE180[I(context, 0x294)];
    char *hit, *child, *other;
    float surface;
    int i, index;
    unsigned char animation;
    qcopy(&old_position, object+0x10);
    qcopy(&old_rotation, object+0xF0);
    surface = func_PAL_L01_003BEB40();
    if (object[0x20] > 1) F(object, 0x18) = F(context, 0x2A8);
    switch (object[0x20]) {
    case 0:
        if (surface > 0.0f) {
            F(context, 0x2B4) = 1.0f / func_00282E48(outbound + 0x10, outbound + 0x20);
            F(context, 0x2B8) = 1.0f / func_00282E48(inbound + 0x10, inbound + 0x20);
            I(context, 0x2F0) = -1;
            qcopy(object+0x10, outbound+0x10);
            F(object, 0xF8) = func_00283248(F(outbound, 0x20) - F(object, 0x10), F(outbound, 0x24) - F(object, 0x14));
            F(context, 0x2D4) = F(object, 0x18);
            I(context, 0x2AC) = 0;
            animation = object[0x43];
            if (animation != (func_001163B0() & 1)) {
                index = func_001163B0() & 1;
                func_PAL_002A7E68(object, index, 0, func_002A7820(10, 20));
            }
            I(context, 0x8C) |= 0x10;
            if (I(context, 0x2D8) != 0) {
                object[0x31] = 0;
                ((ObjectView *)object)->f98 = 0;
                ((ObjectView *)object)->f34 |= 1;
                func_002A7750(object, 1, -1);
            } else {
                func_002A7750(object, 2, -1);
            }
        }
        break;
    case 1: {
        int i, index, ready, bank;
        object[0x31] = 0;
        ((ObjectView *)object)->f98 = 0;
        ((ObjectView *)object)->f34 |= 1;
        bank = D_001A79F0*16;
        ready = 1;
        for (i = 0; i < 5; ++i) {
            index = I(context, 0x2DC + 4*i);
            if (index != -1 && !(D_0019B2E8[index + bank] & 0x80)) ready = 0;
        }
        if (ready) {
            object[0x31] = 1;
            ((ObjectView *)object)->f34 &= ~1;
            ((ObjectView *)object)->f98 = I(P(object, 0x24), 0x10);
            func_002A7750(object, 2, -1);
        }
        break;
    }
    case 2: {
        float rate, yaw;
        int i;
        hit = func_002A9640(object, 0x10000, 0);
        if (hit && (!P(hit, 0x20) || H(P(hit, 0x20), 0xAA) != 0xCE7)) {
            if (D_00189E20.interaction == (char *)object && D_00189E20.active) func_L00_002D6998(&D_L01_00297300);
            if (object[0x43] != 2) func_PAL_002A7E68(object, 2, 5, 3);
            func_002A7750(object, 3, -1);
        } else {
            rate = func_00282E80(object + 0x10, &D_00189E20.position);
            if (rate < 10.0f) {
                if (object[0x43]) func_PAL_002A7E68(object, 0, 0, func_002A7820(10, 20));
                func_0029FCC0(object, 0, (char *)&direction);
                func_00282CF0(&direction, &D_00189E20.eye, &direction);
                yaw = func_00283248(direction.v[0], direction.v[1]);
                yaw = func_00283BE0(yaw, F(object, 0xF8));
                rate = -func_00283248(func_00282E20(&direction), direction.v[2]);
                if (yaw > 2.2689283f) yaw = 2.2689283f;
                else if (yaw < -2.2689283f) yaw = -2.2689283f;
                if (rate > 0.52359885f) rate = 0.52359885f;
                else if (rate < -0.52359885f) rate = -0.52359885f;
                F(context, 0xF4) = rate;
                for (i = 0; i < 3; ++i) F(context, 0xF0 + i*0x80) = yaw * 0.33333334f;
            } else if ((object[0x60] & 2) && !func_002A77E0(1)) {
                if (object[0x42] == 0 && !func_002A77E0(2)) {
                    if (object[0x43] != 1) func_PAL_002A7E68(object, 1, 0, 10);
                } else if (object[0x42] == 1 && object[0x43] != 0) {
                    func_PAL_002A7E68(object, 0, 0, 10);
                }
                F(object, 0x48) = func_002A7878(0.8f, 1.2f);
            }
            if (D_00189E20.interaction == (char *)object && D_00189E20.active) {
                func_L00_002D6998(&D_L01_00297300);
                if (object[0x43] != 2) func_PAL_002A7E68(object, 2, 5, 3);
                func_002A7750(object, 3, -1);
            }
        }
        object[0xA8] = 0xFF;
        break;
    }
    case 3:
        if (object[0x60] & 2) {
            if (D_00189E20.interaction == (char *)object && D_00189E20.active) I(context, 0x2F0) = func_L00_002D6998(&D_L01_00297380);
            if (object[0x43] != 3) func_PAL_002A7E68(object, 3, 0, 6);
            F(context, 0x2CC) = F(context, 0x2D0) = 10.0f;
            func_002A7750(object, 4, -1);
            object[0xA8] = 0xFF;
        }
        break;
    case 4: {
        float rate, lookahead;
        float *point;
        int i, index;
        i = func_00283CF0(F(context, 0x2B0));
        point = (float *)outbound;
        point += i*4;
        if (point[7] > 0.0f) {
            i = func_00283CF0(F(context, 0x2B0));
            point = (float *)outbound;
            point += i*4;
            F(context, 0x2CC) = point[7];
        }
        func_002AA2E8((float *)(context + 0x2D0), F(context, 0x2CC), 0.40000004f);
        {
            float rate = F(context, 0x2B4);
            func_002AA548((float *)(context+0x2B0), (float *)(context+0x2BC), (float)(I(outbound, 0)-1), rate*0.0072000003f, rate*0.0024f, F(context, 0x2D0)*(rate*0.020000001f));
        }
        func_002C9828(outbound, 0, object+0x10, &direction, 0, F(context, 0x2B0));
        F(object, 0xF8) = func_002AA150(F(object, 0xF8), direction.v[2], 0.5f);
        lookahead = F(context, 0x2B0)+6.0f;
        qzero_nc(&target);
        if (lookahead < (float)(I(outbound, 0)-1)) {
            float yaw;
            qcopy(&target, object+0x10);
            qcopy(&velocity, object+0xF0);
            func_002C9828(outbound, 0, &target, &velocity, 0, lookahead);
            func_00282CF0(&target, &target, object+0x10);
            yaw = func_00283248(target.v[0], target.v[1]);
            yaw = func_00283BE0(yaw, F(object, 0xF8));
            F(context, 0xF0) = yaw; F(context, 0xF8) = yaw*0.5f;
            F(context, 0x174) = yaw*0.33333334f; F(context, 0x1F4) = -yaw*0.5f;
        }
        target.v[0] = func_00283180(F(object, 0xF8))*10.0f;
        target.v[1] = func_00283198(F(object, 0xF8))*10.0f;
        target.v[2] = 0.0f;
        func_00282CC0(&target, &target, object+0x10);
        target.v[3] = 12345.0f;
        if (!func_002A77E0(4)) {
            qcopy(&velocity, object+0x10);
            func_002ACB48(velocity.v, 0.05f);
            velocity.v[2] = surface;
            rate = func_002A7878(2.0f, 3.0f);
            i = func_002A77E0(6);
            child = func_002C19D8(&velocity, rate, 15600.001f, D_L01_001AFE18, ((u32)(i+20)<<24)|0x5060U);
            if (child) child[9] = func_00283CF0(16.0f)+32;
        }
        if ((float)(I(outbound, 0)-1) <= F(context, 0x2B0)) {
            func_L00_002D6B70(I(context, 0x2F0));
            I(context, 0x2F0) = -1;
            if (D_00189E20.interaction == (char *)object && D_00189E20.active) func_L00_002D6998(&D_L01_00297400);
            if (object[0x43] != 6) func_PAL_002A7E68(object, 6, 0, 10);
            U(object, 0x96) = 0;
            object[0x20] = 5;
            I(context, 0x2C0) = 17;
            F(context, 0x2B0) = 0.0f;
        }
        if ((I(context, 0x298) == -1 && target.v[3] != 12345.0f) ||
            D_00189E20.interaction != (char *)object || !D_00189E20.active) {
            if (P(context, 0x2AC)) { func_L00_002D7140(P(context, 0x2AC)); P(context, 0x2AC) = 0; }
            break;
        }
        index = I(context, 0x298);
        if (index != -1) {
            other = D_L01_001B255C + index*0x100;
            if (func_00282E80(object+0x10, other+0x10) < F(context, 0x29C)) {
                qcopy(&target, other+0x10);
                target.v[3] = 12345.0f;
            }
        }
        if (target.v[3] == 12345.0f) {
            if (!P(context, 0x2AC)) {
                P(context, 0x2AC) = (char *)func_PAL_L00_002D7850(5);
                if (!P(context, 0x2AC)) break;
            }
            child = P(context, 0x2AC);
            func_00282CF0(child+0x20, &target, &D_00189E20.position);
            ((PoolRecord64 *)child)->f31 = 1;
            ((PoolRecord64 *)child)->f52 = 3;
        }
        break;
    }
    case 5:
    case 7: {
        float rate, yaw;
        func_0029FCC0(object, 0, (char *)&target);
        if (object[0x20] == 5) {
            qcopy(&direction, inbound+0x10);
            direction.v[2] -= 1.5f;
        } else {
            qcopy(&direction, outbound+0x10);
        }
        if (object[0x20] == 5)
            yaw = func_00283248(F(inbound, 0x20)-direction.v[0], F(inbound, 0x24)-direction.v[1]);
        else
            yaw = func_00283248(F(outbound, 0x20)-direction.v[0], F(outbound, 0x24)-direction.v[1]);
        func_00282CF0(&velocity, &direction, object+0x10);
        rate = func_00282DF0(&velocity);
        func_002AAC80(context+0x2C4, rate, 0.0024f, 0.0024f, 0.120000005f);
        func_002AC9F8(velocity.v, F(context, 0x2C4));
        func_00282CC0(object+0x10, object+0x10, &velocity);
        if (object[0x20] == 5) F(object, 0x18) = F(outbound, 0x18) + D_L01_002A48B0[U(object, 0x96)];
        else F(object, 0x18) = F(outbound, 0x18) + D_L01_002A45D0[U(object, 0x96)];
        if (U(object, 0x96) < 180) {
            U(object, 0x96)++;
            if (!func_002A77E0(8)) {
                func_002ACB48(target.v, 0.01f);
                target.v[2] = surface;
                rate = func_002A7878(0.02f, 0.1f); i = func_002A77E0(6);
                func_002C19D8(&target, rate, 9.6e+03f, D_L01_001AFE18, ((u32)(i+20)<<24)|0x5060U);
            }
        } else {
            if (object[0x43]) func_PAL_002A7E68(object, 0, 0, 10);
            func_002AAA00((float *)(object+0xF8), yaw, (float *)(context+0x2C8), 0, 0.0005585055f, 0.00048869225f, 0.031415932f);
            if (func_00283C80(F(object, 0xF8), yaw) < 0.001f) {
                object[0xA8] = 0xFF; object[0x20] = object[0x20] == 5 ? 6 : 2;
                F(context, 0x2B0) = 0.0f;
            }
        }
        if (surface < target.v[2] && !func_002A77E0(6)) {
            qcopy(&target, object+0x10);
            func_002ACB48(target.v, 0.5f); target.v[2] = surface;
            rate = func_002A7878(2.0f, 3.0f); i = func_002A77E0(6);
            child = func_002C19D8(&target, rate, 15600.001f, D_L01_001AFE18, ((u32)(i+20)<<24)|0x5060U);
            if (child) child[9] = func_00283CF0(16.0f)+32;
        }
        if (P(context, 0x2AC)) { func_L00_002D7140(P(context, 0x2AC)); P(context, 0x2AC) = 0; }
        break;
    }
    case 6: {
        float rate;
        rate = F(context, 0x2B8)*0.0032000002f;
        func_002AA548((float *)(context+0x2B0), (float *)(context+0x2BC), (float)(I(inbound, 0)-1), rate, rate, F(context, 0x2B8)*0.20000002f);
        func_002C9828(inbound, 0, object+0x10, object+0xF0, 0, F(context, 0x2B0));
        F(object, 0x18) -= 1.5f;
        if ((float)(I(inbound, 0)-1) <= F(context, 0x2B0)) {
            U(object, 0x96) = 0;
            if (object[0x43] != 7) func_PAL_002A7E68(object, 7, 0, 10);
            object[0x20] = 7; F(context, 0x2B0) = 0.0f;
        }
        break;
    }
    }
    if (object[0x20] > 1) {
        float rate;
        F(context, 0x2A8) = F(object, 0x18);
        F(object, 0x18) = F(object, 0x18) - F(context, 0x2D4) + surface;
        func_002AEF28((float *)object, (float *)(context+0x2A0), (float *)(context+0x2A4), 0.03490659f, 0.05f, 0.01f);
        for (i = 0; i < 3; ++i) func_002AEC48(object, context+0x90+i*0x80, i, 0.028800001f, 0.43200004f);
        if (object[0x20] != 6 && object[0x20] != 0 && !func_002A77E0(49)) {
            rate = func_002A7878(3.0f, 5.0f); i = func_002A77E0(6);
            child = func_002C19D8(object+0x10, rate, 15600.001f, D_L01_001AFE18, ((u32)(i+20)<<24)|0x5060U);
            if (child) child[9] = func_00283CF0(16.0f)+32;
        }
        func_00282CF0(&direction, object+0x10, &old_position);
        if (surface-0.2f < F(object, 0x18)) func_002AD6F0(context+0x50, &direction, object+0xF0, object+0xF0);
    }
    func_PAL_002B14F8(object, (float *)(context+0x300), 2.5f, 4, 1);
}
