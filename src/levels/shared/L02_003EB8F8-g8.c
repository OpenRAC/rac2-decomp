#include "common.h"
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
struct LiftHero { char pad0[0x80]; float pos[4]; char pad1[0x28c]; float f31c; char pad2[0x1c]; char *standing; int active; };
extern char D_00189E20[];
#define HERO ((struct LiftHero *)D_00189E20)
extern char D_00188660[], D_L02_001BA500[];
extern void ref_L02_003EB8F8_02(void *);
extern void ref_L02_003EB8F8_03(void *, int, int);
extern float ref_L02_003EB8F8_04(float);
extern float ref_L02_003EB8F8_05(void *, void *);
extern void ref_L02_003EB8F8_06(void *, void *, void *);
extern void ref_L02_003EB8F8_07(void *, void *, void *);
extern int ref_L02_003EB8F8_08(void *, int);
extern void ref_L02_003EB8F8_09(void *, void *, float, float, float, float);
extern int ref_L02_003EB8F8_10(int, int, void *);
extern void ref_L02_003EB8F8_11(int);
extern void ref_L02_003EB8F8_12(void *, void *, void *, void *);
struct LiftData {
    char pad0[0x60];
    int waypoint;
    char pad64[4];
    int direction;
    float velocity;
    float origin[4];
    int sound;
    int latched;
};
struct LiftPoint { char pad0[0x38]; float z; char pad3c[0x44]; };
struct LiftMoby {
    char pad0[0x10]; float pos[4];
    unsigned char state; char pad21[0x47];
    struct LiftData *data;
    char pad6c[0x3e]; short kind;
    char padac[0x44]; float rotation[4];
};
extern struct LiftPoint *ref_L02_003EB8F8_00 __attribute__((sda));
extern struct LiftPoint *ref_L02_003EB8F8_01 MACRO_ADDR;
void func_L02_003EB8F8(struct LiftMoby *obj) {
    struct LiftData *data = obj->data;
    int oldpos[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float target, speed;
    float endpoint;
    float *d;
    struct LiftHero *h, *h2;
    qcopy(oldpos,obj->pos);
    switch (obj->state) {
    case 0:
        if (!data) { ref_L02_003EB8F8_02(obj); return; }
        qcopy((char *)data+0x70,obj->pos);
        ref_L02_003EB8F8_03(obj,1,-1);
        break;
    case 1:
        target = data->direction ? ref_L02_003EB8F8_00[data->waypoint].z : data->origin[2];
        if (ref_L02_003EB8F8_04(target-obj->pos[2]) < 2.0f) {
            endpoint = ref_L02_003EB8F8_01[data->waypoint].z;
            
            if (HERO->standing==obj && HERO->active) {
                if (!data->latched) data->direction=(data->direction+1)&1;
                data->latched=1;
            } else {
                if (HERO->standing!=obj || HERO->f31c>0.2f) data->latched=0;
                if (data->direction) {
                        if (ref_L02_003EB8F8_04(HERO->pos[2]-data->origin[2])<4.0f && ref_L02_003EB8F8_05(HERO->pos,obj->pos)<24.0f) data->direction=0;
                    } else {
                        if (ref_L02_003EB8F8_04(HERO->pos[2]-endpoint)<4.0f && ref_L02_003EB8F8_05(HERO->pos,obj->pos)<24.0f) data->direction=1;
                    }
            }
        }
        speed=0.003888889f;
        d=delta;
        if (data->direction) {
            if (HERO->pos[2]<obj->pos[2]-1.0f || F(D_L02_001BA500,8)<obj->pos[2]) {
                ref_L02_003EB8F8_06(d,D_L02_001BA500,(char *)&ref_L02_003EB8F8_01[data->waypoint]+0x30);
                ref_L02_003EB8F8_07(d,d,(char *)&ref_L02_003EB8F8_01[data->waypoint]+0x40);
                if (ref_L02_003EB8F8_08(HERO->pos,data->waypoint) || (ref_L02_003EB8F8_04(delta[0])<1.0f && ref_L02_003EB8F8_04(delta[1])<1.0f)) {
                    if (obj->kind==0xbf5) target+=5.0f; else target+=3.0f;
                }
                speed+=speed;
            } else target+=0.15f;
        }
        ref_L02_003EB8F8_09(&obj->pos[2],(char *)data+0x6c,target,0.0019444445f,speed,0.5f);
        if (ref_L02_003EB8F8_04(obj->pos[2]-target)<=data->velocity) {
            obj->pos[2]=target;
            if (data->velocity!=0.0f) data->velocity=0.0f;
        }
        break;
    }
    if (ref_L02_003EB8F8_04(data->velocity)>0.01f) {
        char *e=D_00188660+data->sound*0x70;
        if (P(e,0x88)!=obj || !*(unsigned char *)(e+0x74)) data->sound=ref_L02_003EB8F8_10(0,4,obj);
    } else {
        if (data->sound!=-1) {
            char *e=D_00188660+data->sound*0x70;
            if (P(e,0x88)==obj && *(unsigned char *)(e+0x74)) ref_L02_003EB8F8_11(data->sound);
        }
        data->sound=-1;
    }
    ref_L02_003EB8F8_06(delta,obj->pos,oldpos);
    ref_L02_003EB8F8_12((char *)data+0x20,delta,obj->rotation,obj->rotation);
}
