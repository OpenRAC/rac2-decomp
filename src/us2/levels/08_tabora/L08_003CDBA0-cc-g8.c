/* func_US2_L08_003CDBA0, the USA v2.00 copy of func_L08_003CC750: the same C, where rename func_002B0A18 becomes func_US2_002B1880. */
#include "common.h"
#define F(p,T,o) (*(T *)((char *)(p)+(o)))
typedef struct { char pad[0x2294]; int mode; int unused; int action; } Globals;
extern Globals D_00189E20;
typedef struct { char pad0[0x24]; char *descriptor; char pad1[4]; float scale; } ObjectView;
extern char D_00189EA0[], D_0019B2E8[], D_0019B4A8[];
extern u8 D_L08_001B2840[] MACRO_ADDR;
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021DE80, D_L08_0021EAF0;
extern int D_001A79F0;
extern u16 D_001A7A1A;
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_L08_001A903C __attribute__((sda));
extern float D_L08_001AFED0 __attribute__((sda)), D_L08_001AFED4 __attribute__((sda)), D_L08_001AFED8 __attribute__((sda));
extern float D_L08_001AFEDC __attribute__((sda)), D_L08_001AFEE4 __attribute__((sda)), D_L08_001AFEE8 __attribute__((sda));
extern void func_002A7750(void *,int,int), func_002A7470(void *,int,int,int);
extern void func_L08_003CC4B8(void *);
extern float func_00282E80(void *,void *), func_00282E20(void *);
extern void func_00282CF0(void *,void *,void *), func_00282FB8(void *,void *,float), func_00282CC0(void *,void *,void *);
extern int func_002E5DA0(int,int,void *,int);
extern int func_002E5E58(int, int, void *);
extern void func_0029F338(void *), func_US2_002B1880(int, int);
extern int func_L08_00435938(void);
void func_US2_L08_003CDBA0(char *object) {
    char *state;
    float vector[4] __attribute__((aligned(16)));
    float distance, speed, threshold;
    F(object,u16,0x96)++;
    state = F(object,char *,0x68);
    switch (F(object,u8,0x20)) {
    case 0:
        F(object,u8,0x23) = 0x50;
        F(object,u16,0x34) |= 0x800;
        func_002A7750(object,1,-1);
        if (F(object,u8,0x43)) func_002A7470(object,0,0,0);
        break;
    case 1:
        if (func_00282E80(object+0x10,D_00189EA0) < D_L08_001AFED0) {
            F(state,float,0) = D_L08_001AFEE4;
            if (F(object,u8,0x43) != 1) func_002A7470(object,1,0,0x14);
            F(object,float,0x48) = F(state,float,0) + F(state,float,0);
            func_002A7750(object,2,-1);
        }
        if (F(object,u8,0x31)) func_L08_003CC4B8(object);
        break;
    case 2:
        F(state,float,0) += (1.0f - F(state,float,0)) * D_L08_001AFEDC;
        F(object,float,0x48) = F(state,float,0) + F(state,float,0);
        func_00282CF0(vector,D_00189EA0,object+0x10);
        vector[2] += 0.6f;
        distance = func_00282E20(vector);
        threshold = 0.12f;
        if (F(object,u16,0x96) < 180) {
            if (F(D_00189EA0,int,0x2214) != 0x31)
                speed = D_L08_001AFED4 * (F(state,float,0) * 0.016666668f);
            else {
                speed = D_L08_001AFED8 * (F(state,float,0) * 0.016666668f);
                threshold = 0.8f;
            }
        } else speed = F(state,float,0) + F(state,float,0);
        func_00282FB8(vector,vector,speed);
        func_00282CC0(object+0x10,object+0x10,vector);
        if (((ObjectView *)object)->scale > 0.1f || distance < threshold || distance < speed)
            ((ObjectView *)object)->scale -= D_L08_001AFEE8 * F(((ObjectView *)object)->descriptor,float,0x24);
        if ((distance < speed && ((ObjectView *)object)->scale < F(((ObjectView *)object)->descriptor,float,0x24)*0.01f) ||
            D_00189E20.action == 0x14 || D_00189E20.action == 0x19 ||
            D_00189E20.mode == 0x39 || D_00189E20.mode == 0x6F) {
            func_002E5DA0(3,0,object,0x96A);
            D_001A7A1A++;
            if (F(state,char *,4)) {
                D_L08_0021DE80.flags[F(F(state,char *,4),short,0xB2)] = F(F(state,char *,4),u8,0xB0)+2;
                if (F(F(state,char *,4),u8,0xB0) == 0xFF ||
                    (!(D_L08_001B2840[F(F(state,char *,4),u8,0xB0)] & 0x80) &&
                     (F(D_0019B2E8,u8,F(F(state,char *,4),u8,0xB0)+(D_001A79F0<<4)) & 0x80)))
                    D_L08_0021EAF0.flags[F(F(state,char *,4),short,0xB2)] = F(F(state,char *,4),u8,0xB0)+2;
                {
                    u16 index = F(F(state,char *,4),u16,0xB2);
                    if (index & 1) {
                        u8 *bits = (u8 *)D_0019B4A8 + (((short)index >> 1) + (D_001A79F0 << 10));
                        if (((*bits >> 4) & 7) != 7) *bits += 0x10;
                    } else {
                        u8 *bits = (u8 *)D_0019B4A8 + (((short)index >> 1) + (D_001A79F0 << 10));
                        if ((*bits & 7) != 7) ++*bits;
                    }
                }
            }
            func_0029F338(object);
            if (!func_L08_00435938() && !D_001A7A60[5]) {
                D_001A7A60[5] = 1;
                func_002E5E58(1,0,0);
                func_US2_002B1880(0x1233,-1);
                D_L08_001A903C = 1;
            }
        } else func_L08_003CC4B8(object);
        break;
    }
}
