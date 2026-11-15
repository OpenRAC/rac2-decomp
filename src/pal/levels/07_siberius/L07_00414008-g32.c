#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void copy_matrix_rotation(void *,void *);
extern u8 *CreateMoby(s32);
extern void moby_init_child_from_parent(void *,void *);
extern void euler_rotation_basis(void *,void *);
extern void transform_vector(void *,void *,void *);
extern void multiply_matrix3x3(void *,void *,void *);
extern void func_002A0F48(void *);
extern void FastVecSub(void *,void *,void *);
extern void mat_get_euler_angles(void *,void *);
extern void mat_combine_and_store(void *,void *,void *,void *);
extern f32 ApproachValue(void *,f32,f32);
extern void snd_stop_voice(s32);
extern u8 g_sound_state[];
typedef struct { f32 v[4]; } Vec;
extern Vec D_L07_001B1790[2] __attribute__((sda));
extern Vec D_L07_001B17B0[2] __attribute__((sda));
typedef struct {u8 pad[0x108];u8 *children[2];f32 angles[2];} State;

void func_PAL_L07_00414008(u8 *obj)
{
 f32 mat[16],oldpos[4],oldrot[4],delta[4],rot[4];
 u8 *p=*(u8 **)(obj+0x68),*child,*state,*sound;
 s32 i,id,index;
 u8 *attachment;
 u8 *createdState;
 State *ps=(State *)p;
 copy_matrix_rotation(mat,obj+0xc0);
 qcopy(mat+12,obj+0x10);
 mat[15]=1.0f;
 for(i=0;i<2;i++) {
  child=ps->children[i];
  if(child==0) {
   child=CreateMoby(i?0x11e2:0x11e1);
   if(child) {
    moby_init_child_from_parent(child,obj);
    *(u16 *)(child+0x34)|=0x120;
    createdState=*(u8 **)(child+0x68);
    *(u8 **)(createdState+8)=createdState+0x20;
    *(u32 *)(createdState+0x5c)|=2;
    euler_rotation_basis(child+0xc0,child+0xf0);
   }
   ps->children[i]=child;
   ps->angles[i]=i?1.2f:-1.2f;
  } else {
   qcopy_nc(oldpos,child+0x10);
   qcopy_nc(oldrot,child+0xf0);
   transform_vector(child+0x10,&D_L07_001B1790[i],mat);
   qzero_nc(rot);
   rot[1]=ps->angles[i];
   euler_rotation_basis(child+0xc0,rot);
   multiply_matrix3x3(child+0xc0,mat,child+0xc0);
   func_002A0F48(child);
   state=*(u8 **)(child+0x68);
   FastVecSub(delta,child+0x10,oldpos);
   mat_get_euler_angles(child+0xc0,child+0xf0);
   mat_combine_and_store(state+0x20,delta,oldrot,child+0xf0);
  }
 }
 attachment=*(u8 **)(p+0x16c0);
 if(attachment==0) {
  attachment=CreateMoby(0xd3b);
  if(attachment) {
   moby_init_child_from_parent(attachment,obj);
   *(f32 *)(attachment+0x2c)=*(f32 *)(*(u8 **)(attachment+0x24)+0x24)*1.1f;
   *(u16 *)(attachment+0x34)=(*(u16 *)(attachment+0x34)&0xffdf)|0x102;
   *(u8 **)(p+0x16c0)=attachment;
  }
 } else if((*(u16 *)(attachment+0x34)^1)&1) {
  if(*(f32 *)(p+0x16c8)!=0.0f) {
   ApproachValue(p+0x16c4,*(f32 *)(p+0x16c8),0.040000003f);
   if(*(f32 *)(p+0x16c4)>=*(f32 *)(p+0x16c8)) {
    id=*(s32 *)(p+0x16cc);
    if(id!=-1) {
     sound=g_sound_state+id*0x70;
     if(*(u8 **)(sound+0x88)==obj && sound[0x74]) snd_stop_voice(id);
    }
    *(s32 *)(p+0x16cc)=-1;
    attachment[0x31]=0;
    *(u16 *)(attachment+0x34)|=1;
   }
  }
  index=*(s16 *)(obj+0xaa)!=0x11d9;
  qcopy(attachment+0x10,&D_L07_001B17B0[index]);
  *(f32 *)(attachment+0x18)+=*(f32 *)(p+0x16c4);
  transform_vector(attachment+0x10,attachment+0x10,mat);
  *(TI128 *)oldpos=0;
  oldpos[2]=1.5707964f;
  euler_rotation_basis(attachment+0xc0,oldpos);
  multiply_matrix3x3(attachment+0xc0,mat,attachment+0xc0);
  func_002A0F48(attachment);
 }
}
