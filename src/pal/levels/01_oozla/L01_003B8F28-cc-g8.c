/* func_PAL_L01_003B8F28, the PAL copy of func_L01_003B53C8: the same C, where rename func_002B0ED8 becomes func_PAL_002B1A50; rename func_002A7470 becomes func_PAL_002A7E68; rename func_002AEC48 becomes func_PAL_L01_003BEB40; rename func_L01_003B4480 becomes func_PAL_L01_003B7FC0; lit 0.3f becomes 0.43200004f; rename func_PAL_L01_003BEB40 becomes func_002AEC48; rename func_L01_003BAFB0 becomes func_PAL_L01_003BEB40. */
#include "common.h"

float func_PAL_L01_003BEB40(void);

void func_L01_003B5290(u8 *arg0);

/* func_L01_003B57A8 is defined in L01_003835D8.c. */

#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
extern int D_001A79F0 MACRO_ADDR;
extern u8 D_001A7A60[] MACRO_ADDR;
extern float func_00282E48(void *,void *);
extern void func_PAL_002A7E68(void *,int,int,int);
extern void func_002A7750(void *,int,int);
#define P(p,o) (*(int **)((u8 *)(p)+(o)))
#define C(p,o) (*(u8 **)((u8 *)(p)+(o)))
typedef int OozlaQuad __attribute__((mode(TI)));
extern float D_L01_001B94C0[];
typedef struct { u8 pad[0x2290]; u8 *target; } OozlaHero;
extern OozlaHero D_00189E20;
extern float D_00189EA0[];
extern int D_L01_001B2088 MACRO_ADDR;
extern void func_002A93B0(void *);
extern int func_002B3BA8(void *,int,int,int,float,float);
extern float func_00282E80(void *,void *);
extern s32 func_002AB1F0(u8 *);
extern int func_PAL_002B1A50(void *,void *,int);
extern void func_L01_003B4BD8(void *);
extern float func_00283248(float,float);
extern float func_00283BE0(float,float);
extern void func_002AEC48(void *,void *,int,float,float);
extern int func_002A77E0(int);
extern void func_PAL_L01_003B7FC0(void *);
extern int func_002A8600(void *,int,int,int);
extern int func_002A86E8(void *,void *,int,int);
void func_PAL_L01_003B8F28(u8 *object)
{
    OozlaQuad saved[2];
    u8 *iterator;
    u8 *common;
    u8 *state = C(object,0x68);
    u8 *target, *detail;
    float angle, distance, best;
    if (object[0x31] && func_00282E48(object+0x10,D_L01_001B94C0) < 24.0f) {
        func_002A93B0(object);
        object[0x6F] = 22;
    }
    saved[0] = *(OozlaQuad *)(state+0x230);
    saved[1] = *(OozlaQuad *)(state+0x240);
    if (func_002B3BA8(object,I(state,0x398),0,0,F(state,0x388),0.5f) != 1 && ((int *)saved)[5] == 1) {
        target = ((u8 **)saved)[4];
        if (target && target[0x20] != 254 && target[0x20] != 253 && func_00282E80(object+0x10,target+0x10) < F(state,0x39C)) {
            *(OozlaQuad *)(state+0x230) = saved[0];
            *(OozlaQuad *)(state+0x240) = saved[1];
            target = C(state,0x240);
            if (target == D_00189E20.target) {
                qcopy(state+0x230, (u8 *)&D_00189E20+0xD0);
            } else {
                qcopy(state+0x230, target+0x10);
                detail = (u8 *)func_002AB1F0(target);
                if (detail) F(state,0x238) += F(detail,0x10);
            }
        }
    }
    common = C(object,0x68);
    if (func_PAL_002B1A50(object,common+0x60,0)) {
        if (F(common,0x20) <= 0.0f) I(common,0xDC) = -1;
        else I(common,0xDC) = I(common,0x14C);
        func_L01_003B4BD8(object);
        func_L01_003B5290(object);
        if (object[0x95] < 3) {
            common[0x7A] = 2;
            if (object[0x43] != 4) func_PAL_002A7E68(object,4,0,15);
            I(common,0x320) = 0;
            func_002A7750(object,1,1);
        }
    }
    if (object[0x31]) {
        u8 *goal = C(state,0x240);
        angle = func_00283248(F(goal,0x10)-F(object,0x10),F(goal,0x14)-F(object,0x14));
        F(state,0x2B8) = func_00283BE0(angle,F(object,0xF8));
        func_002AEC48(object,state+0x250,4,0.0432f,0.43200004f);
        if (F(object,0x18) <= func_PAL_L01_003BEB40()+0.3f && (object[0x95] >= 2 || func_002A77E0(9) == 0))
            func_PAL_L01_003B7FC0(object);
    }
    if (object[0x21] != 255 && *P(state,0x368) != D_L01_001B2088) {
        if (*P(state,0x36C) == -1 || *P(state,0x368) < D_L01_001B2088-10) {
            *P(state,0x36C) = -1;
            *P(state,0x370) = -1;
            best = 100000.0f;
            func_002A8600(&iterator,object[0x21],0,0);
            while (iterator) {
                if (*(short *)(iterator+0xAA) == *(short *)(object+0xAA)) {
                    distance = func_00282E80(iterator+0x10,D_00189EA0);
                    if (distance < best && iterator[0x95] == 3 && iterator[0x20] < 3) {
                        best = distance;
                        *P(state,0x370) = *P(state,0x36C);
                        *P(state,0x36C) = *(short *)(iterator+0xB2);
                    }
                }
                func_002A86E8(&iterator,iterator,0,0);
            }
            *P(state,0x368) = D_L01_001B2088;
        }
    }
}
