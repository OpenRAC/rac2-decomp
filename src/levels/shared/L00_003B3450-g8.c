#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } UpdateVector;
typedef struct UpdateContext {
    int field0;
    short timer4, timer6, timer8, timerA;
    float rotC, rot10;
    int timer14;
    char pad18[8];
    UpdateVector saved, velocity;
} UpdateContext;
typedef struct UpdateObject {
    char pad0[0x10];
    UpdateVector position;
    unsigned char state;
    char pad21[0x34-0x21];
    unsigned short flags;
    char pad36[0x68-0x36];
    UpdateContext *context;
    char pad6C[0xAA-0x6C];
    short classId;
    char padAC[0xF0-0xAC];
    float rotX, rotY;
} UpdateObject;
typedef struct HeroView {
char pad0[4640];
UpdateObject * field1220;
char pad1224[4204];
unsigned char * field2290;
char pad2294[32];
unsigned char field22b4;
unsigned char field22b5;
char pad22b6[9];
unsigned char field22bf;
} HeroView;
extern HeroView D_00189E20;
extern float D_L00_001AF8C4 __attribute__((sda));
extern int D_L00_001AF8DC __attribute__((sda));
extern int D_L00_001AF8E0 __attribute__((sda));
extern int D_L00_001AF8EC __attribute__((sda));
extern unsigned short D_L00_001AF8CC __attribute__((sda));
extern float D_L00_001AF8E4 __attribute__((sda));
extern float D_L00_001AF8E8 __attribute__((sda));
extern float D_L00_001A8F20[4] MACRO_ADDR;
extern Quad D_L00_001BF230;
extern void func_00282CC0(void *,void *,void *),func_002B00D8(void *,void *,void *,float);
extern float func_00283B98(float,float),func_00282DB0(void *,void *),func_00283CE0(int);
extern int func_00282978(short *),func_00282948(int *);
extern void func_00282D08(void *,void *,void *,float),ref_L00_003B3450_00(void (*)(void *),void *);
extern int func_00277258(void *,int,void *,float);
extern void func_0029F338(void *);
extern void func_L00_003B39D0(void *),func_L00_003B4E88(void *),func_L00_003B4EF8(void *),func_L00_003B4198(void *),func_L00_003B3E78(void *),func_L00_003B4018(void *),func_L00_003B3C40(void *),func_L00_003B3AF8(void *);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
void func_L00_003B3450(UpdateObject *object)
{
    Quad previous;
    UpdateContext *ctx=object->context;
    UpdateObject *hero_object=D_00189E20.field1220;
    float fraction;
    if((!hero_object || hero_object->classId!=0xC0) && !object->state) { func_0029F338(object); return; }
    if(D_00189E20.field22b4 && !object->state) { func_0029F338(object); return; }
    if((D_00189E20.field22b5 || D_00189E20.field22bf) && !object->state) object->flags|=0x41;
    else object->flags&=~0x41;
    switch(object->state) {
    case 1:
        qcopy(&previous,&object->position);
        func_00282CC0(&object->position,&object->position,&ctx->velocity);
        func_002B00D8(&object->position,&ctx->velocity,&ctx->velocity,D_L00_001AF8C4*0.00027777778f);
        object->rotX=func_00283B98(object->rotX,ctx->rotC);
        object->rotY=func_00283B98(object->rotY,ctx->rot10);
        func_L00_003B39D0(object);
        if(func_00282978(&ctx->timer4)) { func_0029F338(object); return; }
        if(object->position.f[0]<2.0f || object->position.f[0]>1021.0f || object->position.f[1]<2.0f || object->position.f[1]>1021.0f || object->position.f[2]<2.0f || object->position.f[2]>1021.0f) { func_0029F338(object); return; }
        if(func_00282DB0((char *)&D_00189E20+0x2C0,&ctx->velocity)>0.0f && func_00282978(&ctx->timer6)) {
            object->state=2;
            {
                unsigned short duration = D_L00_001AF8CC;
                unsigned short transition = *(unsigned short *)&D_L00_001AF8DC;
                ctx->timer8 = duration;
                ctx->timerA = transition;
            }
            qcopy(&ctx->saved,&ctx->velocity);
            func_L00_003B4E88(object);
        }
        return;
    case 2: {
        float duration;
        fraction=func_00283CE0(ctx->timerA);
        duration=func_00283CE0(D_L00_001AF8DC);
        fraction/=duration;
        func_00282D08(&ctx->velocity,D_L00_001A8F20,&ctx->saved,fraction);
        func_00282CC0(&object->position,&object->position,&ctx->velocity);
        object->rotX=func_00283B98(object->rotX,ctx->rotC);
        object->rotY=func_00283B98(object->rotY,ctx->rot10);
        func_L00_003B4EF8(object);
        ref_L00_003B3450_00(func_L00_003B4198,object);
        if(func_00277258(&object->position,0,D_00189E20.field2290,0.25f)) qcopy(&object->position,&D_L00_001BF230);
        if(object->position.f[0]<2.0f || object->position.f[0]>1021.0f || object->position.f[1]<2.0f || object->position.f[1]>1021.0f || object->position.f[2]<2.0f || object->position.f[2]>1021.0f) {
        func_0029F338(object);return;
        }
        if(func_00282978(&ctx->timerA) && !D_L00_001AF8EC) {
            object->state=3;ctx->timer14=D_L00_001AF8E0;
            D_L00_001AF8EC=(int)object;func_L00_003B3E78(object);
        }
        return;
    }
    case 3:
        object->rotX=func_00283B98(object->rotX,ctx->rotC);
        object->rotY=func_00283B98(object->rotY,ctx->rot10);
        func_L00_003B4EF8(object);func_L00_003B4018(object);
        if(ctx->timer8>=60) func_L00_003B3C40(object);
        ref_L00_003B3450_00(func_L00_003B4198,object);
        func_00282948(&ctx->timer14);
        if(ctx->timer14) {
            fraction=func_00283CE0(ctx->timer14);fraction/=func_00283CE0(D_L00_001AF8E0);
            if(func_00277258(&object->position,2,D_00189E20.field2290,D_L00_001AF8E8+(D_L00_001AF8E4-D_L00_001AF8E8)*fraction)) qcopy(&object->position,&D_L00_001BF230);
        }
        func_L00_003B3AF8(object);
        if(func_00282978(&ctx->timer8)) {
            qzero_nc(&previous);
            func_002ABBB8(object,&previous,&object->position,0.0f,0.0f,5,2,4,4.0f,2.0f,9.0f,1.0f,-1,15.0f,1,5,-1,0,0x810001);
            D_L00_001AF8EC=0;object->state=90;
        }
        return;
    case 90:
        func_0029F338(object);
    }
}
