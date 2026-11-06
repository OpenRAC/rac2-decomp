/* func_PAL_L01_004221D8, the PAL copy of func_L01_0041C970: the same C, with 50 Hz timestep and angle constants. */
#include "common.h"

extern s32 func_002ACD38(void *);
extern f32 func_PAL_L01_003BEB40(void);
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
void func_PAL_L01_004221D8(Object0041C970 *obj) {
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
 if(!func_002ACD38(obj->position)) return;
 p=obj->stateData;
 qcopy(oldpos,obj->position);
 qcopy(oldrot,obj->rotation);
 switch(obj->state) {
 case 0:
  height0=func_PAL_L01_003BEB40();
  *(s32 *)((u8 *)p+0xAC)=0;
  if(height0>100.0f) {
   p->field78=func_002A7940();
   p->field7C=func_002A7940();
   p->field6C=obj->position[2]-height0;
   p->field60=p->field6C;
   p->field64=p->field6C-D_L01_001B1B28;
   p->field68=0;
   qcopy((u8 *)p+0x80,obj->rotation);
   qzero((u8 *)p+0x90);
   if(!p->fieldA0) func_002A7750(obj,2,-1);
   else func_002A7750(obj,1,-1);
  }
  break;
 case 1:
  height1=func_PAL_L01_003BEB40();
  trigger=0;
  if(D_00189E20.mode==25 && p->field68<0.0f &&
     D_00189E20.position[2]>obj->position[2]-0.2f &&
     obj->position[2]<height1+0.1f) trigger=1;
  if((D_00189E20.platform==obj && !D_00189E20.flag34E) || trigger) {
   if(trigger) obj->collisionFlags=0;
   else obj->collisionFlags=obj->classData->flags;
   x=func_002A7798((p->field6C-p->field64)/D_L01_001B1B28);
   timestep=0.020000001f;
   p->field68=-(D_L01_001B1B2C*timestep)*x;
  } else {
   obj->collisionFlags=obj->classData->flags;
   x=func_002A7798((D_L01_001B1B28-(p->field6C-p->field64))/D_L01_001B1B28);
   timestep=0.020000001f;
   p->field68=D_L01_001B1B30*(x*timestep);
  }
  p->field6C+=p->field68;
  obj->position[2]=height1+p->field6C;
  func_002AEF28(obj,(u8 *)p+0x78,(u8 *)p+0x7C,D_L01_001B1B3C,D_L01_001B1B40*0.0003490659f,D_L01_001B1B44*0.0003490659f);
  func_00282CF0(delta,obj->position,oldpos);
  func_002AD6F0((u8 *)p+0x20,delta,oldrot,obj->rotation);
  break;
 case 2:
  if(obj->field31) {
   p->fieldAC=func_00283B98(p->fieldAC,0.062831864f);
   obj->color=func_00283D38(0xFFEEFC0E,0xF03B4004,func_00283198(p->fieldAC)*0.5f+0.5f);
  }
  height2=func_PAL_L01_003BEB40();
  if(!D_00189E20.flag34E && D_00189E20.platform==obj) {
   func_00282CF0(local,D_00189E20.position,obj->position);
   x=func_00282DB0(local,obj->matrix);
   y=-D_L01_001B1B48 * func_00282DB0(local,obj->matrix+4);
   scaledX=D_L01_001B1B4C*x;
   *(UpdateQuad *)oldstate=*(UpdateQuad *)((u8 *)p+0x80);
   *(UpdateQuad *)current=*(UpdateQuad *)(obj->position);
   func_002AA898((u8 *)p+0x80,y,(u8 *)p+0x90,D_L01_001B1B50*1.44f,D_L01_001B1B54*1.44f,D_L01_001B1B58*1.2f,0);
   func_002AA898((u8 *)p+0x84,scaledX,(u8 *)p+0x94,D_L01_001B1B50*1.44f,D_L01_001B1B54*1.44f,D_L01_001B1B58*1.2f,0);
   func_L01_00316C48(D_00189E20.position,out,obj->position,oldstate,(u8 *)p+0x80);
  } else {
   func_002AA898((u8 *)p+0x80,0.0f,(u8 *)p+0x90,D_L01_001B1B5C*1.44f,D_L01_001B1B60*1.44f,D_L01_001B1B64*1.2f,0);
   func_002AA898((u8 *)p+0x84,0.0f,(u8 *)p+0x94,D_L01_001B1B5C*1.44f,D_L01_001B1B60*1.44f,D_L01_001B1B64*1.2f,0);
  }
  obj->position[2]=height2+p->field6C;
  func_002AEF28(obj,(u8 *)p+0x78,(u8 *)p+0x7C,D_L01_001B1B3C,D_L01_001B1B40*0.0003490659f,D_L01_001B1B44*0.0003490659f);
  obj->rotation[0]=func_00283B98(p->field80,obj->rotation[0]);
  obj->rotation[1]=func_00283B98(p->field84,obj->rotation[1]);
  func_00282CF0(delta,obj->position,oldpos);
  func_002AD6F0((u8 *)p+0x20,delta,oldrot,obj->rotation);
  break;
 }
}
