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
    u8 aiMode;
    u16 timer;
    int w98;
    u8 pad9C[0xC];
    u8 hitFlash;
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
extern void func_00318240(GrelbinMoby *,int,int);
extern void func_0030DFE8(GrelbinMoby *);
extern void *func_0031A8C8(GrelbinMoby *,int,int);
extern GrelbinMoby *func_0030DC80(int);
extern void func_00326780(void *,void *);
extern int func_002DBF58(void *,void *,int,void *,int);
extern u8 D_L19_001BFEC0[];
extern void func_00323098(void *,void *,int);
extern void func_003299C8(void *,float,float,float,float);
extern u8 D_0019B4A8[];
extern void func_00317748(void *,int,int);
extern void func_00310760(void *);
extern void func_0031CA60(void *);
extern void func_00317F60(void *,int,int,int);
extern void func_0031CDC8(void *,void *);
extern int func_002EB5C0(void *);
extern float func_0031A928(void *,void *);
extern void func_0031CD08(void *,void *);
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
extern int func_00326D70(void *,int,float,int,float,int);
extern float func_002EBB00(void *,void *);
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
/* Sets up the Leviathan's helper object on its first frame, takes hit damage, and watches for a Y.E.T.I. to grab. Returns 1 when the object should be removed. */
int func_L19_004170D8(GrelbinMoby *moby)
{
    GrelbinUpdateState *vars=moby->pvars;
    void *otherMoby;
    GrelbinMoby *spawn;
    u8 *effectVars;
    int i;
    float top[4] __attribute__((aligned(16)));
    float bottom[4] __attribute__((aligned(16)));
    if (moby->state==0) {
        moby->w98=0;
        moby->flags=(moby->flags|1)&0xEFFF;
        vars->w304=0;
        if (vars->sourceIndex!=-1) vars->source=gMobyArray_L19+vars->sourceIndex;
        else {
            vars->source=func_0030DC80(0x1178 /* moby class 4472 */);
            if (!vars->source) {
        success:
            return 1;
            }
            func_00326780(vars->source,moby);
            vars->source->group=moby->group;
            vars->source->drawDistance=moby->drawDistance;
            vars->source->flags|=0x100;
            qcopy(top,moby->position); qcopy(bottom,moby->position);
            top[2]+=1.f; bottom[2]-=10.f;
            func_002DBF58(top,bottom,2,moby,0);
            func_00323098(vars->source->transform,D_L19_001BFEC0,0);
        }
        {
        float half=0.5f;
        float one=1.f;
        vars->height=vars->previousHeight=moby->position[2];
        { u16 distance=90; moby->group=distance; moby->drawDistance=distance; }
        vars->f228=0.1f; vars->w22C=0; vars->f230=one; vars->f234=0.1f;
        vars->f170=half;vars->f174=half;vars->b1B7=1;
        vars->f238=0.1f; vars->b150=12; vars->w188=3; vars->b156=5;
        vars->f17C=0.15f; vars->range=16.f; vars->phase=1;
        if (!vars->healthSet) {vars->health=one;vars->healthSet=1;}
        }
        vars->w50=0;vars->f84=0.5f;vars->f54=0.2f;vars->f5C=vars->f58=0.75f;
        vars->f60=1.5707965f;vars->f80=0.52359885f;
        func_003299C8(moby,0.0033333334f,0.10000001f,0.006981318f,0.8377582f);
        vars->flags|=2;
        func_00318240(moby,1,0);
        if(moby->animation!=7) func_00317F60(moby,7,0,0);
    {
        u16 id=moby->uid;
        int value;
        if (D_L19_0021EA30.active[(s16)id]) goto replace;
        value=D_0019B4A8[((s16)id>>1)+(gCurrentMapIndex<<10)];
        if ((id&1) ? ((value>>4)&7) : (value&7)) {
        replace:
        {
            GrelbinMoby *replacement;
            replacement=func_0030DC80(0x1208 /* moby class 4616 */);
            if (!replacement) goto success;
            func_00326780(replacement,vars->source);
            replacement->group=moby->group;replacement->drawDistance=moby->drawDistance;
            { float (*src)[4]=vars->source->transform;
            for(i=0;i<4;i++) qcopy(replacement->transform[i],src[i]); }
            func_0030DFE8(vars->source);
            vars->source=replacement;
            goto success;
        }
        }
    }
    }
    if(vars->phase==2) {
        u16 id;
        u8 *count;
        func_00317748(moby,0,3);
        spawn=func_0030DC80(0x1266 /* moby class 4710 */);
        if(!spawn) goto success;
        id=moby->uid;
        if(id&1) { count=((s16)id>>1)+(gCurrentMapIndex<<10)+D_0019B4A8; if(((*count>>4)&7)!=7) *count+=16;}
        else { count=((s16)id>>1)+(gCurrentMapIndex<<10)+D_0019B4A8; if((*count&7)!=7) *count+=1;}
        spawn->opacity=80;spawn->flags|=0x800;spawn->drawDistance=255;spawn->group=255;
        spawn->state=0;spawn->bBC=0;spawn->b31=1;
        qcopy(spawn->position,vars->source->position);
        spawn->position[2]+=1.f;func_00310760(spawn);func_0031CA60(spawn);
        effectVars=spawn->pvars;F(effectVars,0)=0.1f;
        func_00317F60(spawn,1,0,20);
        { float duration=F(effectVars,0); spawn->state=2;spawn->f48=duration+duration; }
        goto success;
    }
    func_0031CDC8(moby,&vars->damageState);
    {
    otherMoby=func_0031A8C8(moby,0x10000,0);
    if(!func_002EB5C0((u8 *)vars+0x26)) otherMoby=0;
    if(otherMoby) {
        float damage=F(otherMoby,0x2C);
        if(vars->damageScale!=0.f) {
            GrelbinMoby *source=*(GrelbinMoby **)(otherMoby+0x20);
            if(source && moby->classId==source->classId) F(otherMoby,0x2C)=damage*vars->damageScale;
        }
        {
            float damage=func_0031A928(moby,otherMoby);
            moby->hitFlash=255;vars->damageTimer=200;
            vars->health-=damage;
        }
        func_0031CD08(moby,&vars->damageState);
        if(vars->health<=0.f) {
            GrelbinMoby *target;
            if(moby->animation!=5) func_00317F60(moby,5,0,20);
            func_00318240(moby,12,3);
            target=vars->target;
            if(target && target->classId==0x10D0 /* Y.E.T.I. */) {
                gActiveYetiCount=gActiveYetiCount-1;
                func_0030DFE8(target);
                vars->target=gHeroState.object;
                vars->targetSet=1;qcopy(vars->targetPosition,gHeroState.previousPosition);
            }
        }
        moby->hitFlash=255;
    }
    }
    if(moby->state!=11) {
    vars->w2FC=func_00326D70(moby,vars->w210,36.f,0,10.f,0);
    if(moby->aiMode) {
        vars->w2F8=func_00326D70(moby,vars->w2F4,vars->f214*1.5f,0,0.f,0);
        if(vars->w2F4==-1) {
            if(func_002EBB00(moby->position,gHeroPosition)<32.f) vars->w2F8=1;
            else vars->w2F8=0;
        }
    }
    if(gHeroState.mode==49) qcopy(vars->targetPosition,gHeroState.position);
    otherMoby=D_L19_001B2A28;
    while(otherMoby) {
        if(((GrelbinMoby *)otherMoby)->classId==0x10D0 /* Y.E.T.I. */ && moby->state!=4 && moby->state!=9 && moby->state!=8 && vars->health>0.f) {
            if(moby->state==7 && moby->timer>=16) break;
            if(func_002EBB00(moby->position,((GrelbinMoby *)otherMoby)->position)<16.f && func_002EBB00(moby->position,((GrelbinMoby *)otherMoby)->position)>15.f && ((GrelbinMoby *)otherMoby)->aiMode && I(((GrelbinMoby *)otherMoby)->pvars,0x254)) {
                vars->target=otherMoby;vars->targetSet=1;qcopy(vars->targetPosition,((GrelbinMoby *)otherMoby)->position);break;
            }
        }
        otherMoby=((GrelbinMoby *)otherMoby)->next;
    }
    }
    {
    GrelbinMoby *target=vars->target;
    if(target && target->classId==0x10D0 /* Y.E.T.I. */ && func_002EBB00(moby->position,target->position)<16.f && func_002EBB00(moby->position,vars->target->position)>15.f && moby->state!=11 && moby->aiMode) {
        vars->height=vars->previousHeight;
        if(moby->animation!=6) func_00317F60(moby,6,0,19);
        func_00318240(moby,11,-1);
        vars->target->state=23;vars->target->aiMode=4;
        func_00317F60(vars->target,6,0,15);
    }
    }
    return 0;
}
