#include "include_asm.h"

#include "common.h"
typedef struct GrelbinMoby {
    u8 pad0[0x10];
    float position[4];
    u8 state;
    u8 pad21[0x2];
    u8 opacity;
    u8 pad24[0x4];
    struct GrelbinMoby * next;
    u8 pad2C[0x4];
    u8 drawDistance;
    u8 b31;
    u16 group;
    u16 flags;
    u8 pad36[0xD];
    u8 animation;
    u8 pad44[0x4];
    float f48;
    u8 pad4C[0x1C];
    void * pvars;
    u8 pad6C[0x29];
    u8 b95;
    u16 timer;
    int w98;
    u8 pad9C[0xC];
    u8 bA8;
    u8 padA9[0x1];
    s16 classId;
    u8 padAC[0x6];
    u16 uid;
    u8 padB4[0x8];
    u8 bBC;
    u8 padBD[0x3];
    float transform[4][4];
} GrelbinMoby;
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
extern int D_001A79F0 __attribute__((sda));
extern u8 D_00189EA0[];
typedef struct { u8 pad0[0x464]; u8 active[0]; } GrelbinEntityFlags;
extern GrelbinEntityFlags D_L19_0021EA30;
extern GrelbinMoby *D_L19_001B2A1C __attribute__((sda));
extern void func_002A7750(GrelbinMoby *,int,int);
extern void func_0029F338(GrelbinMoby *);
extern void *func_002A9640(GrelbinMoby *,int,int);
extern GrelbinMoby *func_0029EFD0(int);
extern void func_002B37E8(void *,void *);
extern int func_002761F8(void *,void *,int,void *,int);
extern u8 D_L19_001BFEC0[];
extern void func_002B0408(void *,void *,int);
extern void func_002B60B0(void *,float,float,float,float);
extern u8 D_0019B4A8[];
extern void func_PAL_002A7650(void *,int,int);
extern void func_002A0F48(void *);
extern void func_002AB650(void *);
extern void func_PAL_002A7E68(void *,int,int,int);
extern void func_PAL_002AC3C0(void *,void *);
extern int func_00282978(void *);
extern float func_PAL_002AA108(void *,void *);
extern void func_PAL_002AC290(void *,void *);
extern int D_L19_001B1D20 MACRO_ADDR;
typedef struct {
    u8 pad0[0x80];
    float position[4];
    u8 pad90[0x40];
    float previousPosition[4];
    u8 padE0[0x21B0];
    GrelbinMoby *object;
    int mode;
} GrelbinPlayer;
extern GrelbinPlayer D_00189E20;
extern GrelbinMoby *D_L19_001B2A28 MACRO_ADDR;
extern int func_002B3BA8(void *,int,float,int,float,int);
extern float func_00282E80(void *,void *);
typedef struct {
    u8 pad0[0x20];
    float health;
    s16 healthSet;
    u8 pad26[0x8];
    u8 phase;
    u8 pad2F[0x1];
    float range;
    u8 pad34[0x1C];
    int w50;
    float f54;
    float f58;
    float f5C;
    float f60;
    u8 pad64[0x1C];
    float f80;
    float f84;
    int flags;
    u8 pad8C[0xB4];
    u8 damageState[7];
    u8 damageTimer;
    u8 pad148[0x8];
    u8 b150;
    u8 pad151[0x5];
    u8 b156;
    u8 pad157[0x19];
    float f170;
    float f174;
    u8 pad178[0x4];
    float f17C;
    u8 pad180[0x8];
    int w188;
    u8 pad18C[0x2B];
    u8 b1B7;
    u8 pad1B8[0x30];
    float damageScale;
    u8 pad1EC[0x4];
    float targetPosition[4];
    GrelbinMoby *target;
    int targetSet;
    u8 pad208[0x8];
    int w210;
    float f214;
    u8 pad218[0x10];
    float f228;
    int w22C;
    float f230;
    float f234;
    float f238;
    u8 pad23C[0x94];
    float height;
    u8 pad2D4[0x4];
    float previousHeight;
    int sourceIndex;
    u8 pad2E0[0x10];
    GrelbinMoby *source;
    int w2F4;
    int w2F8;
    int w2FC;
    u8 pad300[0x4];
    int w304;
} GrelbinUpdateState;

int func_PAL_L19_0041C498(GrelbinMoby *obj)
{
    GrelbinUpdateState *state=obj->pvars;
    void *other;
    GrelbinMoby *spawn;
    u8 *data;
    int i;
    float top[4] __attribute__((aligned(16)));
    float bottom[4] __attribute__((aligned(16)));
    if (obj->state==0) {
        obj->w98=0;
        obj->flags=(obj->flags|1)&0xEFFF;
        state->w304=0;
        if (state->sourceIndex!=-1) state->source=D_L19_001B2A1C+state->sourceIndex;
        else {
            state->source=func_0029EFD0(0x1178);
            if (!state->source) {
        success:
            return 1;
            }
            func_002B37E8(state->source,obj);
            state->source->group=obj->group;
            state->source->drawDistance=obj->drawDistance;
            state->source->flags|=0x100;
            qcopy(top,obj->position); qcopy(bottom,obj->position);
            top[2]+=1.f; bottom[2]-=10.f;
            func_002761F8(top,bottom,2,obj,0);
            func_002B0408(state->source->transform,D_L19_001BFEC0,0);
        }
        {
        float half=0.5f;
        float one=1.f;
        state->height=state->previousHeight=obj->position[2];
        { u16 distance=90; obj->group=distance; obj->drawDistance=distance; }
        state->f228=0.1f; state->w22C=0; state->f230=one; state->f234=0.1f;
        state->f170=half;state->f174=half;state->b1B7=1;
        state->f238=0.1f; state->b150=12; state->w188=3; state->b156=5;
        state->f17C=0.15f; state->range=16.f; state->phase=1;
        if (!state->healthSet) {state->health=one;state->healthSet=1;}
        }
        state->w50=0;state->f84=0.5f;state->f54=0.2f;state->f5C=state->f58=0.75f;
        state->f60=1.5707965f;state->f80=0.52359885f;
        func_002B60B0(obj,0.0048f,0.120000005f,0.010053098f,1.0053098f);
        state->flags|=2;
        func_002A7750(obj,1,0);
        if(obj->animation!=7) func_PAL_002A7E68(obj,7,0,0);
    {
        u16 id=obj->uid;
        int value;
        if (D_L19_0021EA30.active[(s16)id]) goto replace;
        value=D_0019B4A8[((s16)id>>1)+(D_001A79F0<<10)];
        if ((id&1) ? ((value>>4)&7) : (value&7)) {
        replace:
        {
            GrelbinMoby *replacement;
            replacement=func_0029EFD0(0x1208);
            if (!replacement) goto success;
            func_002B37E8(replacement,state->source);
            replacement->group=obj->group;replacement->drawDistance=obj->drawDistance;
            { float (*src)[4]=state->source->transform;
            for(i=0;i<4;i++) qcopy(replacement->transform[i],src[i]); }
            func_0029F338(state->source);
            state->source=replacement;
            goto success;
        }
        }
    }
    }
    if(state->phase==2) {
        u16 id;
        u8 *count;
        func_PAL_002A7650(obj,0,3);
        spawn=func_0029EFD0(0x1266);
        if(!spawn) goto success;
        id=obj->uid;
        if(id&1) { count=((s16)id>>1)+(D_001A79F0<<10)+D_0019B4A8; if(((*count>>4)&7)!=7) *count+=16;}
        else { count=((s16)id>>1)+(D_001A79F0<<10)+D_0019B4A8; if((*count&7)!=7) *count+=1;}
        spawn->opacity=80;spawn->flags|=0x800;spawn->drawDistance=255;spawn->group=255;
        spawn->state=0;spawn->bBC=0;spawn->b31=1;
        qcopy(spawn->position,state->source->position);
        spawn->position[2]+=1.f;func_002A0F48(spawn);func_002AB650(spawn);
        data=spawn->pvars;F(data,0)=0.1f;
        func_PAL_002A7E68(spawn,1,0,20);
        { float duration=F(data,0); spawn->state=2;spawn->f48=duration+duration; }
        goto success;
    }
    func_PAL_002AC3C0(obj,&state->damageState);
    {
    other=func_002A9640(obj,0x10000,0);
    if(!func_00282978((u8 *)state+0x26)) other=0;
    if(other) {
        float damage=F(other,0x2C);
        if(state->damageScale!=0.f) {
            GrelbinMoby *source=*(GrelbinMoby **)(other+0x20);
            if(source && obj->classId==source->classId) F(other,0x2C)=damage*state->damageScale;
        }
        {
            float damage=func_PAL_002AA108(obj,other);
            obj->bA8=255;state->damageTimer=200;
            state->health-=damage;
        }
        func_PAL_002AC290(obj,&state->damageState);
        if(state->health<=0.f) {
            GrelbinMoby *target;
            if(obj->animation!=5) func_PAL_002A7E68(obj,5,0,17);
            func_002A7750(obj,12,3);
            target=state->target;
            if(target && target->classId==0x10D0) {
                D_L19_001B1D20=D_L19_001B1D20-1;
                func_0029F338(target);
                state->target=D_00189E20.object;
                state->targetSet=1;qcopy(state->targetPosition,D_00189E20.previousPosition);
            }
        }
        obj->bA8=255;
    }
    }
    if(obj->state!=11) {
    state->w2FC=func_002B3BA8(obj,state->w210,36.f,0,10.f,0);
    if(obj->b95) {
        state->w2F8=func_002B3BA8(obj,state->w2F4,state->f214*1.5f,0,0.f,0);
        if(state->w2F4==-1) {
            if(func_00282E80(obj->position,D_00189EA0)<32.f) state->w2F8=1;
            else state->w2F8=0;
        }
    }
    if(D_00189E20.mode==49) qcopy(state->targetPosition,D_00189E20.position);
    other=D_L19_001B2A28;
    while(other) {
        if(((GrelbinMoby *)other)->classId==0x10D0 && obj->state!=4 && obj->state!=9 && obj->state!=8 && state->health>0.f) {
            if(obj->state==7 && obj->timer>=16) break;
            if(func_00282E80(obj->position,((GrelbinMoby *)other)->position)<16.f && func_00282E80(obj->position,((GrelbinMoby *)other)->position)>15.f && ((GrelbinMoby *)other)->b95 && I(((GrelbinMoby *)other)->pvars,0x254)) {
                state->target=other;state->targetSet=1;qcopy(state->targetPosition,((GrelbinMoby *)other)->position);break;
            }
        }
        other=((GrelbinMoby *)other)->next;
    }
    }
    {
    GrelbinMoby *target=state->target;
    if(target && target->classId==0x10D0 && func_00282E80(obj->position,target->position)<16.f && func_00282E80(obj->position,state->target->position)>15.f && obj->state!=11 && obj->b95) {
        state->height=state->previousHeight;
        if(obj->animation!=6) func_PAL_002A7E68(obj,6,0,16);
        func_002A7750(obj,11,-1);
        state->target->state=23;state->target->b95=4;
        func_PAL_002A7E68(state->target,6,0,12);
    }
    }
    return 0;
}
