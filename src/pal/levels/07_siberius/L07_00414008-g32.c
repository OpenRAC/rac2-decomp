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
extern Vec g_ship_attach_offsets_left[2] __attribute__((sda));
extern Vec g_ship_attach_offsets_right[2] __attribute__((sda));
typedef struct {u8 pad[0x108];u8 *children[2];f32 angles[2];} State;

/* Creates the two side parts and the top attachment of a Siberius ship and keeps them attached to its body every frame. */
void ship_update_attached_parts_pal(u8 *moby)
{
 f32 matrix[16],old_position[4],old_rotation[4],delta[4],rotation[4];
 u8 *vars=*(u8 **)(moby+0x68),*child,*child_vars,*sound_slot;
 s32 i,sound_id,side_index;
 u8 *attachment;
 u8 *created_vars;
 State *ship_state=(State *)vars;
 copy_matrix_rotation(matrix,moby+0xc0);
 qcopy(matrix+12,moby+0x10);
 matrix[15]=1.0f;
 for(i=0;i<2;i++) {
  child=ship_state->children[i];
  if(child==0) {
   child=CreateMoby(i?0x11e2:0x11e1);
   if(child) {
    moby_init_child_from_parent(child,moby);
    *(u16 *)(child+0x34)|=0x120;
    created_vars=*(u8 **)(child+0x68);
    *(u8 **)(created_vars+8)=created_vars+0x20;
    *(u32 *)(created_vars+0x5c)|=2;
    euler_rotation_basis(child+0xc0,child+0xf0);
   }
   ship_state->children[i]=child;
   ship_state->angles[i]=i?1.2f:-1.2f;
  } else {
   qcopy_nc(old_position,child+0x10);
   qcopy_nc(old_rotation,child+0xf0);
   transform_vector(child+0x10,&g_ship_attach_offsets_left[i],matrix);
   qzero_nc(rotation);
   rotation[1]=ship_state->angles[i];
   euler_rotation_basis(child+0xc0,rotation);
   multiply_matrix3x3(child+0xc0,matrix,child+0xc0);
   func_002A0F48(child);
   child_vars=*(u8 **)(child+0x68);
   FastVecSub(delta,child+0x10,old_position);
   mat_get_euler_angles(child+0xc0,child+0xf0);
   mat_combine_and_store(child_vars+0x20,delta,old_rotation,child+0xf0);
  }
 }
 attachment=*(u8 **)(vars+0x16c0);
 if(attachment==0) {
  attachment=CreateMoby(0xd3b);
  if(attachment) {
   moby_init_child_from_parent(attachment,moby);
   *(f32 *)(attachment+0x2c)=*(f32 *)(*(u8 **)(attachment+0x24)+0x24)*1.1f;
   *(u16 *)(attachment+0x34)=(*(u16 *)(attachment+0x34)&0xffdf)|0x102;
   *(u8 **)(vars+0x16c0)=attachment;
  }
 } else if((*(u16 *)(attachment+0x34)^1)&1) {
  if(*(f32 *)(vars+0x16c8)!=0.0f) {
   ApproachValue(vars+0x16c4,*(f32 *)(vars+0x16c8),0.040000003f);
   if(*(f32 *)(vars+0x16c4)>=*(f32 *)(vars+0x16c8)) {
    sound_id=*(s32 *)(vars+0x16cc);
    if(sound_id!=-1) {
     sound_slot=g_sound_state+sound_id*0x70;
     if(*(u8 **)(sound_slot+0x88)==moby && sound_slot[0x74]) snd_stop_voice(sound_id);
    }
    *(s32 *)(vars+0x16cc)=-1;
    attachment[0x31]=0;
    *(u16 *)(attachment+0x34)|=1;
   }
  }
  side_index=*(s16 *)(moby+0xaa)!=0x11d9;
  qcopy(attachment+0x10,&g_ship_attach_offsets_right[side_index]);
  *(f32 *)(attachment+0x18)+=*(f32 *)(vars+0x16c4);
  transform_vector(attachment+0x10,attachment+0x10,matrix);
  *(TI128 *)old_position=0;
  old_position[2]=1.5707964f;
  euler_rotation_basis(attachment+0xc0,old_position);
  multiply_matrix3x3(attachment+0xc0,matrix,attachment+0xc0);
  func_002A0F48(attachment);
 }
}
