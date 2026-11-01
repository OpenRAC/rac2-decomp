#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { u8 pad[0x88]; float z; u8 pad2[0x2b0]; int object; int state; } EHero;
extern EHero D_00189E20;
typedef struct { u8 pad[0x74]; u8 active; u8 pad2[0x13]; int object; } ESound;
extern u8 D_00188660[];
extern u8 *D_L08_001B2ACC __attribute__((sda));
extern float func_00282C48(float);
extern int func_00283CF0(float);
extern void func_002A7750(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern float func_00283180(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002AA150(float, float, float);
extern void func_002E59F8(int);
extern void func_002AD6F0(void *, void *, void *, void *);
#define E_I(p,o) (*(int *)((u8 *)(p)+(o)))
#define E_F(p,o) (*(float *)((u8 *)(p)+(o)))
typedef struct { u8 pad[0x60]; TI128 pos; TI128 rot; int index; float duration; float progress; u8 pad2[2]; u8 trigger; u8 side; int sound; } EPlatform;
typedef struct { u8 pad[0xf0]; float rx, ry, rz; } EMob;
void func_L08_003E5BB8(u8 *m)
{
    TI128 oldpos, oldrot, delta;
    EPlatform *p = *(EPlatform **)(m+0x68);
    float d1,d2,t;
    qcopy(&oldpos,m+0x10);
    qcopy(&oldrot,m+0xf0);
    switch(m[0x20]) {
    case 0:
        p->sound=-1;
        qcopy(&p->pos,m+0x10);
        qcopy(&p->rot,m+0xf0);
        if(E_F((u8 *)p,0x68)<E_F(D_L08_001B2ACC+p->index*128,0x38)) p->side=0; else p->side=1;
        p->progress=0;
        m[0xbc]=0;
        func_002A7750(m,1,-1);
        break;
    case 1:
        d1=func_00282C48(E_F((u8 *)p,0x68)-D_00189E20.z);
        d2=func_00282C48(E_F(D_L08_001B2ACC+p->index*128,0x38)-D_00189E20.z);
        if (((!p->trigger || func_00283CF0(p->progress)==p->side) && D_00189E20.object==(int)m && D_00189E20.state!=0) ||
            (p->progress<0.1f && d2<d1) || (p->progress>0.9f && d1<d2)) {
            m[0xbc]^=1;
            func_002A7750(m,2,-1);
        }
        break;
    case 2:
        if(((ESound *)(D_00188660+p->sound*0x70))->object!=(int)m || !((ESound *)(D_00188660+p->sound*0x70))->active)
            p->sound=func_002E5CF8(0,4,m);
        if(m[0xbc]) p->progress+=1.0f/p->duration;
        else p->progress-=1.0f/p->duration;
        if(p->progress>1.0f) p->progress=1.0f;
        else if(p->progress<0.0f) p->progress=0.0f;
        t=(1.0f-func_00283180(p->progress*3.141592741f))*0.5f;
        func_00282CF0(&delta,D_L08_001B2ACC+p->index*128+0x30,&p->pos);
        func_00282D30(&delta,&delta,t);
        func_00282CC0(m+0x10,&p->pos,&delta);
        ((EMob*)m)->rz=func_002AA150(E_F((u8 *)p,0x78),E_F(D_L08_001B2ACC+p->index*128,0x78),t);
        ((EMob*)m)->ry=func_002AA150(E_F((u8 *)p,0x74),E_F(D_L08_001B2ACC+p->index*128,0x74),t);
        ((EMob*)m)->rx=func_002AA150(E_F(p,0x70),E_F(D_L08_001B2ACC+p->index*128,0x70),t);
        if(m[0xbc] ? p->progress>=1.0f : p->progress<=0.0f) {
            int i=p->sound;
            if(i!=-1 && ((ESound *)(D_00188660+i*0x70))->object==(int)m && ((ESound *)(D_00188660+i*0x70))->active) func_002E59F8(i);
            p->sound=-1;
            if(*(short *)(m+0xaa)!=0xd49) func_002E5CF8(1,0,m);
            func_002A7750(m,3,-1);
        }
        break;
    case 3:
        if(D_00189E20.object!=(int)m) func_002A7750(m,1,-1);
        break;
    }
    if(m[0x20]<4) {
        func_00282CF0(&delta,m+0x10,&oldpos);
        func_002AD6F0((u8 *)p+0x20,&delta,&oldrot,m+0xf0);
    }
}


