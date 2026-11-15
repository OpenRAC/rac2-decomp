#include "include_asm.h"
#include "common.h"

extern char *D_L01_001B255C __attribute__((sda));

extern u16 *D_L01_001FB020[];

/* Raises the measured flag on every record of the table the object's selector names. */
/* Sets a flag on every Mutant Muckdweller in this object's group. */
void func_L01_003DC838(s32 moby) {
    s32 mobyBase;
    s16 *member;
    s16 *groupList;

    if (*(u8 *)(moby + 0x21) == 0xFF)
        return;
    groupList = D_L01_001FB020[*(u8 *)(moby + 0x21)];
    if (groupList == 0)
        return;
    member = groupList;
    mobyBase = (s32)gMobyTable_L01;
    do {
        u32 offset = (*(u16 *)member & 0x7FFF) << 8;

        if (*(s8 *)(mobyBase + offset + 0x20) >= 0) {
            if (*(s16 *)(mobyBase + offset + 0xAA) == 0xB2B /* Mutant Muckdweller */)
                *(u16 *)(*(u32 *)(mobyBase + offset + 0x68) + 0x3DA) = 1;
        }
    } while (*member++ >= 0);
}

/* func_L01_00416A50 is defined in L01_003DA740.c (this unit has no $gp access for it). */

typedef unsigned int TI128 __attribute__((mode(TI)));

extern u8 *D_L01_001B264C __attribute__((sda));

extern char D_00189EA0[];

extern float func_00282E80(void *, void *);

extern float func_002A89A8(void *, int, float);

/* Picks the farthest of up to three points from the hero and gives its position and ground height. */
void func_L01_003DCE70(u8 *moby, u8 *out) {
    s32 *indexPtr = (s32 *)(*(u32 *)(moby + 0x68) + 0x3C4);
    TI128 point;
    int count = 3;
    f32 distance;

    *(f32 *)(out + 0xC) = 0.0f;
    while (--count >= 0) {
        s32 index = *indexPtr;

        if (index != -1) {
            u8 *base = D_L01_001B264C;

            qcopy_nc(&point, base + index * 128 + 0x30);
            distance = vec_distance_xy(&point, gHeroPosition);
            if (*(f32 *)(out + 0xC) < distance) {
                qcopy_nc(out, &point);
                *(f32 *)(out + 0xC) = distance;
            }
        }
        indexPtr++;
    }
    *(f32 *)(out + 0x8) = ProbeGroundHeightBelow(out, 0, 10.0f);
}

extern s32 func_002ACD38(void *);
extern f32 func_L01_003BAFB0(void);
extern f32 func_002A7940(void);
extern void func_002A7750(void *,s32,s32);
extern f32 func_002A7798(f32);
extern void func_002AEF28(void *,void *,void *,f32,f32,f32);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AD6F0(void *,void *,void *,void *);
extern f32 func_00283B98(f32,f32);
extern f32 func_00283198(f32);
extern s32 func_00283D38(u32,u32,f32);
extern f32 func_00282DB0(void *,void *);
extern f32 func_002AA898(void *,f32,void *,f32,f32,f32,s32);
extern void func_L01_00316C48(void *,void *,void *,void *,void *);
typedef struct {
 u8 pad0[0x80]; f32 position[4];
 u8 pad90[0x33C-0x90]; void *platform;
 u8 pad340[0xE]; s16 flag34E;
 u8 pad350[0x229C-0x350]; s32 mode;
} UpdateHero;
extern UpdateHero D_00189E20 NOT_SDA;
typedef int UpdateQuad __attribute__((mode(TI)));
extern f32 D_L01_001B1B28 __attribute__((sda));
extern f32 D_L01_001B1B2C __attribute__((sda));
extern f32 D_L01_001B1B30 __attribute__((sda));
extern f32 D_L01_001B1B34 __attribute__((sda));
extern f32 D_L01_001B1B38 __attribute__((sda));
extern f32 D_L01_001B1B3C __attribute__((sda));
extern f32 D_L01_001B1B40 __attribute__((sda));
extern f32 D_L01_001B1B44 __attribute__((sda));
extern f32 D_L01_001B1B48 __attribute__((sda));
extern f32 D_L01_001B1B4C __attribute__((sda));
extern f32 D_L01_001B1B50 __attribute__((sda));
extern f32 D_L01_001B1B54 __attribute__((sda));
extern f32 D_L01_001B1B58 __attribute__((sda));
extern f32 D_L01_001B1B5C __attribute__((sda));
extern f32 D_L01_001B1B60 __attribute__((sda));
extern f32 D_L01_001B1B64 __attribute__((sda));
typedef struct {
 u8 pad0[0x60];
 f32 field60;
 f32 field64;
 f32 field68;
 f32 field6C;
 u8 pad70[0x8];
 f32 field78;
 f32 field7C;
 f32 field80;
 f32 field84;
 u8 pad88[0x18];
 s32 fieldA0;
 u8 padA4[0x8];
 f32 fieldAC;
} State0041C970;
typedef struct {
 u8 pad0[0x10]; f32 position[4];
 u8 state; u8 slot; u8 pad22[2];
 struct ObjectClass0041C970 { u8 pad0[0x10]; s32 flags; } *classData;
 u8 pad28[4]; f32 field2C;
 u8 pad30; u8 field31; u8 pad32[2]; u16 flags34;
 u8 pad36[0xD]; u8 animation;
 u8 pad44[0x24]; State0041C970 *stateData;
 u8 pad6C[0xC]; u32 color;
 u8 pad7C[0x1C]; s32 collisionFlags;
 u8 pad9C[0x24]; f32 matrix[12]; f32 rotation[4];
} Object0041C970;
/* Tilting lift: initializes its height range, moves while the hero rides it,
 * and tilts toward the hero's offset projected on the object's axes. */
void func_L01_0041C970(Object0041C970 *obj) {
 f32 oldpos[4] __attribute__((aligned(16)));
 f32 oldrot[4] __attribute__((aligned(16)));
 f32 delta[4] __attribute__((aligned(16)));
 f32 local[4] __attribute__((aligned(16)));
 f32 oldstate[4] __attribute__((aligned(16)));
 f32 current[4] __attribute__((aligned(16)));
 f32 out[4] __attribute__((aligned(16)));
 State0041C970 *p;
 f32 height0, height1, height2, x, y, speed, scaledX;
 f32 timestep;
 s32 trigger;
 if(!IsObjectInSelectedZone(obj->position)) return;
 p=obj->stateData;
 qcopy(oldpos,obj->position);
 qcopy(oldrot,obj->rotation);
 switch(obj->state) {
 case 0:
  height0=GetWaterHeight();
  *(s32 *)((u8 *)p+0xAC)=0;
  if(height0>100.0f) {
   p->field78=RandomAngle();
   p->field7C=RandomAngle();
   p->field6C=obj->position[2]-height0;
   p->field60=p->field6C;
   p->field64=p->field6C-D_L01_001B1B28;
   p->field68=0;
   qcopy((u8 *)p+0x80,obj->rotation);
   qzero((u8 *)p+0x90);
   if(!p->fieldA0) SetMobyState(obj,2,-1);
   else SetMobyState(obj,1,-1);
  }
  break;
 case 1:
  height1=GetWaterHeight();
  trigger=0;
  if(gHeroState.mode==25 && p->field68<0.0f &&
     gHeroState.position[2]>obj->position[2]-0.2f &&
     obj->position[2]<height1+0.1f) trigger=1;
  if((gHeroState.platform==obj && !gHeroState.flag34E) || trigger) {
   if(trigger) obj->collisionFlags=0;
   else obj->collisionFlags=obj->classData->flags;
   x=EaseOutQuad((p->field6C-p->field64)/D_L01_001B1B28);
   timestep=0.01666666753590107f;
   p->field68=-(D_L01_001B1B2C*timestep)*x;
  } else {
   obj->collisionFlags=obj->classData->flags;
   x=EaseOutQuad((D_L01_001B1B28-(p->field6C-p->field64))/D_L01_001B1B28);
   timestep=0.01666666753590107f;
   p->field68=D_L01_001B1B30*(x*timestep);
  }
  p->field6C+=p->field68;
  obj->position[2]=height1+p->field6C;
  ScaleOwnerWordsByAngles(obj,(u8 *)p+0x78,(u8 *)p+0x7C,D_L01_001B1B3C,D_L01_001B1B40*0.0002908882452175021f,D_L01_001B1B44*0.0002908882452175021f);
  FastVecSub(delta,obj->position,oldpos);
  CombineTransformsAndStore((u8 *)p+0x20,delta,oldrot,obj->rotation);
  break;
 case 2:
  if(obj->field31) {
   p->fieldAC=FastAddRotations(p->fieldAC,0.05235988646745682f);
   obj->color=FastTweenColor(0xFFEEFC0E,0xF03B4004,FastSinOrCosB(p->fieldAC)*0.5f+0.5f);
  }
  height2=GetWaterHeight();
  if(!gHeroState.flag34E && gHeroState.platform==obj) {
   FastVecSub(local,gHeroState.position,obj->position);
   x=FastVecDot(local,obj->matrix);
   y=-D_L01_001B1B48 * FastVecDot(local,obj->matrix+4);
   scaledX=D_L01_001B1B4C*x;
   *(UpdateQuad *)oldstate=*(UpdateQuad *)((u8 *)p+0x80);
   *(UpdateQuad *)current=*(UpdateQuad *)(obj->position);
   ApproachWithVelocity((u8 *)p+0x80,y,(u8 *)p+0x90,D_L01_001B1B50,D_L01_001B1B54,D_L01_001B1B58,0);
   ApproachWithVelocity((u8 *)p+0x84,scaledX,(u8 *)p+0x94,D_L01_001B1B50,D_L01_001B1B54,D_L01_001B1B58,0);
   TransformOffsetByTwoMatrices(gHeroState.position,out,obj->position,oldstate,(u8 *)p+0x80);
  } else {
   ApproachWithVelocity((u8 *)p+0x80,0.0f,(u8 *)p+0x90,D_L01_001B1B5C,D_L01_001B1B60,D_L01_001B1B64,0);
   ApproachWithVelocity((u8 *)p+0x84,0.0f,(u8 *)p+0x94,D_L01_001B1B5C,D_L01_001B1B60,D_L01_001B1B64,0);
  }
  obj->position[2]=height2+p->field6C;
  ScaleOwnerWordsByAngles(obj,(u8 *)p+0x78,(u8 *)p+0x7C,D_L01_001B1B3C,D_L01_001B1B40*0.0002908882452175021f,D_L01_001B1B44*0.0002908882452175021f);
  obj->rotation[0]=FastAddRotations(p->field80,obj->rotation[0]);
  obj->rotation[1]=FastAddRotations(p->field84,obj->rotation[1]);
  FastVecSub(delta,obj->position,oldpos);
  CombineTransformsAndStore((u8 *)p+0x20,delta,oldrot,obj->rotation);
  break;
 }
}

extern s32 func_00283CF0(f32);
extern f32 func_002A78D8(f32, f32);
extern void func_L01_003377C8(void *);
extern void func_002B60B0(void *, f32, f32, f32, f32);
extern s32 func_002A7820(s32, s32);
extern void func_002A7470(void *, s32, s32, s32);
extern u8 *D_L01_001FE180[] NOT_SDA;
extern u8 D_L01_001B0900[] SDATA(D_L01_001B0900);

/* Sets up the Muckdweller when it appears: its speeds, timers and path points, and its first animation. */
void func_L01_003DCF40(u8 *obj) {
    u8 *vars = *(u8 **)(obj + 0x68);
    s32 idx;

    *(void **)(vars + 0x18) = vars + 0x1C0;
    vars[0x48] = FloatToInt(10.0f);
    vars[0x4A] = FloatToInt(9.6f);
    *(s32 *)(vars + 0x158) = 5;
    *(u8 *)(vars + 0x127) = 11;
    *(f32 *)(vars + 0x12C) = 0.20000001788139343f;
    *(f32 *)(vars + 0x130) = 0.10000000894069672f;
    *(f32 *)(vars + 0x134) = 0.006111111491918564f;
    *(f32 *)(vars + 0x138) = 0.010277777910232544f;
    *(f32 *)(vars + 0x13C) = 0.011111111380159855f;
    *(f32 *)(vars + 0x14C) = 0.4f;
    *(u8 *)(vars + 0x120) = 0;
    *(u8 *)(vars + 0x121) = 10;
    *(u8 *)(vars + 0x122) = 10;
    *(u8 *)(vars + 0x126) = 10;
    *(f32 *)(vars + 0x140) = 0.5f;
    *(f32 *)(vars + 0x144) = 0.5f;
    *(u8 *)(vars + 0x17C) = 6;
    *(u8 *)(vars + 0x17D) = 10;
    *(u8 *)(vars + 0x17E) = 6;
    *(u8 *)(vars + 0x17F) = 10;
    *(s16 *)(vars + 0x148) = 0;
    *(u8 *)(vars + 0x28) = 0;
    *(u8 *)(vars + 0x182) = 6;
    *(u8 *)(vars + 0x183) = 10;
    *(u8 *)(vars + 0x29) = 1;
    *(f32 *)(vars + 0x30) = 0.5f;
    *(TI128 *)(vars + 0x3A0) = *(TI128 *)(obj + 0x10);
    *(s16 *)(vars + 0x3D8) = 0;
    if (*(s32 *)(vars + 0x3C0) != -1) {
        ComputePathSegmentLengths_L01(D_L01_001FE180[*(s32 *)(vars + 0x3C0)]);
    }
    idx = *(s32 *)(vars + 0x3BC);
    if (idx != -1) {
        ComputePathSegmentLengths_L01(D_L01_001FE180[idx]);
    }
    qcopy(vars + 0x2B0, obj + 0x10);
    *(f32 *)(vars + 0x2C0) = 0.3f;
    *(f32 *)(vars + 0x2CC) = 5.0f;
    *(f32 *)(vars + 0x1C8) = 0.2f;
    *(f32 *)(vars + 0x1C4) = 0.1f;
    *(f32 *)(vars + 0x2D0) = 5.0f;
    *(f32 *)(vars + 0x1C0) = 0.3f;
    *(f32 *)(vars + 0x1CC) = 0.2f;
    *(f32 *)(vars + 0x1D0) = 0.8726646900177002f;
    *(f32 *)(vars + 0x1F0) = 0.523598849773407f;
    *(f32 *)(vars + 0x1EC) = 0.0055555556900799274f;
    *(s32 *)(vars + 0x1FC) = *(s32 *)(vars + 0x3BC);
    *(f32 *)(vars + 0x29C) = RandomSignedFloatRange(25.0f, 35.0f) * 0.01745329424738884f;
    *(s16 *)(vars + 0x2A2) = 120;
    *(s16 *)(vars + 0x2A4) = 180;
    SetControllerSpeedLimits(obj, 0.002222222276031971f, 0.06666667014360428f, 0.0021331803873181343f, 0.19198624789714813f);
    *(f32 *)(vars + 0xF0) = *(f32 *)(obj + 0x2C);
    *(f32 *)(vars + 0xE0) = *(f32 *)(vars + 0x30);
    *(void **)(vars + 0xC0) = D_L01_001B0900;
    *(s32 *)(obj + 0xF4) = 0;
    *(s32 *)(obj + 0xF0) = 0;
    qzero_nc(vars + 0x210);
    *(f32 *)(vars + 0x218) = 1.0f;
    if (obj[0x21] != 255) {
        **(s32 **)(vars + 0x3FC) = 0;
        **(s32 **)(vars + 0x400) = -1;
    }
    if (!vars[0x3D0]) {
        if (vars[0x3D1]) {
            if (*(s32 *)(vars + 0x414) != -1) *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x414);
            else if ((idx = *(s32 *)(vars + 0x418)) != -1) *(s32 *)(vars + 0x3F8) = idx;
            else *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x41C);
            if (vars[0x3D2]) {
                SetMobyState(obj, 0, 1);
            } else {
                SetMobyState(obj, 1, 3);
            }
        } else {
            if (*(s32 *)(vars + 0x418) != -1) *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x418);
            else if ((idx = *(s32 *)(vars + 0x414)) != -1) *(s32 *)(vars + 0x3F8) = idx;
            else *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x41C);
            SetMobyState(obj, 1, 3);
        }
        if (*(s32 *)(vars + 0x408) != -1) {
            if (obj[0x43] != 7) StartAnimationBlended(obj, 7, 0, RandomIntRange(2, 10));
        } else if (obj[0x43] != 0) {
            StartAnimationBlended(obj, 0, 0, RandomIntRange(2, 10));
        }
    } else {
        if (*(s32 *)(vars + 0x414) != -1) *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x414);
        else if ((idx = *(s32 *)(vars + 0x418)) != -1) *(s32 *)(vars + 0x3F8) = idx;
        else *(s32 *)(vars + 0x3F8) = *(s32 *)(vars + 0x41C);
        *(s32 *)(obj + 0x98) = 0;
        obj[0x31] = 0;
        *(u16 *)(obj + 0x34) |= 1;
        *(f32 *)(obj + 0x18) -= 2.0f;
        SetMobyState(obj, 0, 1);
        if (obj[0x43] != 0) StartAnimationBlended(obj, 0, 0, RandomIntRange(2, 10));
    }
}
