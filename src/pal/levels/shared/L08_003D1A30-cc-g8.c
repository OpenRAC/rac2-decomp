/* func_PAL_L08_003D1A30, the PAL copy of func_L08_003CDB78: the same C, where rename func_002ABBB8 becomes func_PAL_002AC718; rename func_L08_002D2ED8 becomes func_PAL_L08_002D3078; rename func_002A7470 becomes func_PAL_002A7E68; rename func_L00_002D2168 becomes func_PAL_L00_002D2668. */
#include "common.h"
typedef int ContactQuad __attribute__((mode(TI)));
typedef union { ContactQuad q; float f[4]; } ContactVector;
typedef struct { char pad[0x2290]; void *collision; char gap[0x24CC-0x2294]; int contact; } ContactHero;
extern ContactHero D_00189E20;
extern char D_L08_001BFF60[], D_L08_001A8F20[] MACRO_ADDR;
typedef struct { char pad[0x10]; ContactQuad position; char tail[0xE0]; } ContactEntry;
extern ContactEntry *D_L08_001B29DC __attribute__((sda));
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
extern void func_PAL_002AC718(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern int func_002E5DA0(int,int,void *,int),func_00278E78(void);
extern int func_PAL_L08_002D3078(int,int);
extern void func_PAL_002A7E68(void *,int,int,int),func_002A7750(void *,int,int);
extern void func_L08_003CDB38(void *),func_PAL_L00_002D2668(int,int,float);

/* Resolve the movement probes and update the D_L08_001BFF60 response. */
int func_PAL_L08_003D1A30(char *object, void *previous)
{
    ContactVector temporary, point;
    char *state=*(char **)(object+0x68);
    int hit,index,result;
    float whole,part,drop;
    ContactHero *hero=&D_00189E20;

    func_00282F20(&temporary,object+0xC0,D_L08_001AFFF4);
    func_00282CC0(&point,&temporary,object+0x10);
    func_00282F20(&temporary,object+0xE0,D_L08_001AFFF0);
    func_00282CC0(&point,&point,&temporary);
    hit=func_00277258(&point,0,D_L08_001AFFEC,hero->collision);
    if (!hit) {
        func_0029FCC0(object,1,&temporary);
        hit=func_002761F8(&point,&temporary,0x10,hero->collision,0);
        if (!hit) {
            func_0029FCC0(object,4,&temporary);
            hit=func_002761F8(&point,&temporary,0x10,hero->collision,0);
            if (!hit) {
                qcopy(&point,previous);
                qcopy(&temporary,state);
                hit=func_002761F8(previous,state,0x10,hero->collision,0);
            }
        }
        if (hit) {
            whole=func_00282E48(&point,&temporary);
            part=func_00282E48(&point,D_L08_001BFF60);
            func_00282CF0(D_L08_001BFF60+0x10,&point,&temporary);
            func_00282F20(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,whole-part);
            func_00282CC0(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,&point);
        }
    }
    if (hit) {
        func_PAL_002AC718(object,D_L08_001A8F20,D_L08_001BFF60,0.0f,0.0f,3,3,3,0.0f,0.0f,9.0f,0.8f,-1,0.0f,0,3,-1,7,0x810001);
        if (!*(int *)(state+0xB0)) {
            func_002E5DA0(4,0,object,0x988);
            *(int *)(state+0xB0)=12;
        }
        func_00282CF0(&point,state,&point);
        func_00282CC0(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,&point);
        if (D_001A79F0!=9 && (result=func_00278E78())==1) {
            D_L08_001B2094=D_L08_001B3410;
            D_L08_001B2098=D_L08_001B3414;
            *(int *)(state+0x50)=0;
            func_PAL_L08_002D3078(0,1);
            if (*(unsigned char *)(object+0x43)) func_PAL_002A7E68(object,0,0,10);
            index=*(int *)(state+0x6C);
            if (index>0) {
                qcopy(state,&D_L08_001B29DC[index].position);
                func_L08_003CDB38(object);
            }
            func_002A7750(object,1,-1);
            D_00189E20.contact=result;
        } else {
            qcopy(state,D_L08_001BFF60+0x10);
            func_00283028(state+0x20,state+0x20,D_L08_001BFF60+0x20);
            func_00282D30(state+0x20,state+0x20,D_L08_001B0118);
            drop=D_L08_001B0120*0.00040000002f;
            *(float *)(state+0x28)-=drop;
            if (*(unsigned char *)(object+0x20)!=9) {
                if (*(float *)(state+0x28)>0.0f) *(float *)(state+0x28)=-drop;
                func_PAL_L00_002D2668(0x80,0,12.0f);
                func_002A7750(object,9,-1);
            }
            func_00282CC0(object+0x10,object+0x10,state+0x20);
        }
    }
    return hit;
}
