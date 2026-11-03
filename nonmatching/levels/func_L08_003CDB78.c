/* 2 November 2026: retained nonmatching C; no linked matching credit.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * USA v1.01 check: 1044/1056 bytes, 0/3 placements.
 * Full collision-resolver C replaces the old screen. All three fallback probes, global contact
 * adjustment, the hero and level-specific response branches, and the truthful int/float callee
 * results are retained. Two complete vectors fit the measured 0xA0 frame. Direct contact
 * symbols improve 1036 to 1044 bytes; ordinary TI copies tie. Hero high-half/base lifetime,
 * saved pointer allocation and call/store scheduling remain. Reopen on measured hero/contact
 * pointer lifetimes. No linked or native-runtime validation.
 */
#include "common.h"
typedef int ContactQuad __attribute__((mode(TI)));
typedef union { ContactQuad q; float f[4]; } ContactVector;
extern char D_00189E20[];
extern char D_L08_001BFF60[], D_L08_001A8F20[];
extern char *D_L08_001B29DC __attribute__((sda));
extern float D_L08_001AFFF4 __attribute__((sda)), D_L08_001AFFF0 __attribute__((sda));
extern float D_L08_001AFFEC __attribute__((sda));
extern float D_L08_001B0118 __attribute__((sda)), D_L08_001B0120 __attribute__((sda));
extern float D_L08_001B3410 MACRO_ADDR, D_L08_001B3414 MACRO_ADDR;
extern float D_L08_001B2094 MACRO_ADDR, D_L08_001B2098 MACRO_ADDR;
extern int D_001A79F0;
extern void func_00282F20(void *,void *,float),func_00282CC0(void *,void *,void *);
extern int func_00277258(void *,int,float,void *);
extern void func_0029FCC0(void *,int,void *);
extern int func_002761F8(void *,void *,int,void *,void *);
extern float func_00282E48(void *,void *);
extern void func_00282CF0(void *,void *,void *),func_00283028(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_002ABBB8(void *,void *,void *,int,int,int,int,int,int,int,int,int,
                         float,float,float,float,float,float,float);
extern int func_002E5DA0(int,int,void *,int),func_00278E78(void);
extern int func_L08_002D2ED8(int,int);
extern void func_002A7470(void *,int,int,int),func_002A7750(void *,int,int);
extern void func_L08_003CDB38(void *),func_L00_002D2168(int,int,float);

/* Resolve the movement probes and update the D_L08_001BFF60 response. */
int func_L08_003CDB78(char *object, void *previous)
{
    ContactVector temporary, point;
    char *state=*(char **)(object+0x68);
    int hit;
    float whole,part,drop;
    char *hero=D_00189E20;

    func_00282F20(&temporary,object+0xC0,D_L08_001AFFF4);
    func_00282CC0(&point,&temporary,object+0x10);
    func_00282F20(&temporary,object+0xE0,D_L08_001AFFF0);
    func_00282CC0(&point,&point,&temporary);
    hit=func_00277258(&point,0,D_L08_001AFFEC,*(void **)(hero+0x2290));
    if (!hit) {
        func_0029FCC0(object,1,&temporary);
        hit=func_002761F8(&point,&temporary,0x10,*(void **)(hero+0x2290),0);
        if (!hit) {
            func_0029FCC0(object,4,&temporary);
            hit=func_002761F8(&point,&temporary,0x10,*(void **)(hero+0x2290),0);
            if (!hit) {
                point.q=*(ContactQuad *)previous;
                temporary.q=*(ContactQuad *)state;
                hit=func_002761F8(previous,state,0x10,*(void **)(hero+0x2290),0);
                if (!hit) return hit;
                whole=func_00282E48(&point,&temporary);
                part=func_00282E48(&point,D_L08_001BFF60);
                func_00282CF0(D_L08_001BFF60+0x10,&point,&temporary);
                func_00282F20(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,whole-part);
                func_00282CC0(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,&point);
            }
        }
    }
    if (hit) {
        func_002ABBB8(object,D_L08_001A8F20,D_L08_001BFF60,3,3,3,-1,0,3,-1,7,0x810001,
                     0.0f,0.0f,0.0f,0.0f,9.0f,0.8f,0.0f);
        if (!*(int *)(state+0xB0)) {
            func_002E5DA0(4,0,object,0x988);
            *(int *)(state+0xB0)=15;
        }
        func_00282CF0(&point,state,&point);
        func_00282CC0(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,&point);
        if (D_001A79F0!=9 && func_00278E78()==1) {
            D_L08_001B2094=D_L08_001B3410;
            D_L08_001B2098=D_L08_001B3414;
            *(int *)(state+0x50)=0;
            func_L08_002D2ED8(0,1);
            if ((unsigned char)object[0x43]) func_002A7470(object,0,0,10);
            if (*(int *)(state+0x6C)>0)
                *(ContactQuad *)state=*(ContactQuad *)(D_L08_001B29DC+(*(int *)(state+0x6C)<<8)+0x10);
            func_L08_003CDB38(object);
            func_002A7750(object,1,-1);
            *(int *)(hero+0x24CC)=1;
        } else {
            char *velocity=state+0x20;
            *(ContactQuad *)state=*(ContactQuad *)(D_L08_001BFF60+0x10);
            func_00283028(velocity,velocity,D_L08_001BFF60+0x20);
            func_00282D30(velocity,velocity,D_L08_001B0118);
            drop=D_L08_001B0120*0.00027777778450399637f;
            *(float *)(state+0x28)-=drop;
            if ((unsigned char)object[0x20]!=9) {
                if (*(float *)(state+0x28)>0.0f) *(float *)(state+0x28)=-drop;
                func_L00_002D2168(0x80,0,15.0f);
                func_002A7750(object,9,-1);
            }
            func_00282CC0(object+0x10,object+0x10,velocity);
        }
    }
    return hit;
}
