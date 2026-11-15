#include "common.h"
extern unsigned char D_0019B4A8[];
extern struct { char pad[0x464]; u8 state[0]; } D_L19_0021EA30;
extern int g_current_map_index SDATA(D_001A79F0);
extern int D_L19_001B1DE0 __attribute__((sda));
extern char D_L19_001BFEC0[];
extern void moby_mark_spawned(void *);
extern int moby_is_in_selected_zone(void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern int CollLine(void *, void *, int, void *, void *);
extern void mat_align_to_dir(void *, void *, void *), moby_set_state(void *, int, int), EmitGrelbinGlowSprites(void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern float moby_update_aim_target_strength(void *, void *), IntToFloat(int);
extern int FloatToInt(float);
extern void gfx_start_color_fade(void *, void *), anim_start_immediate(void *, int, int), gfx_update_color_fade(void *, void *);
extern int math_random_int_range(int,int);
extern int PlayMobySound(int,int,void *);
extern void part_spawn_masked_debris(void *, int, void *, float, float, float, float, int);
extern char *CreateMoby(int);
extern void func_002A0F48(void *), hero_copy_field_to_moby(void *);
/* Remove the object when its persistence state says so; otherwise apply hit damage
 * and spawn object kind 0x1266 when health runs out. */
/* A breakable object. It flashes when hit, and when its health runs out it bursts and drops a pickup (moby class 4710). */
void UpdateBreakablePickupSpawner(char *moby)
{
 char *vars, *hitInfo, *dropMoby;
 float *health; char *color;
 float scratchA[4] __attribute__((aligned(16))), scratchB[4] __attribute__((aligned(16)));
 float damage;
 if (*(u8 *)(moby+0xb0)!=255) {
  unsigned short id=*(unsigned short *)(moby+0xb2);
  int savedCount;
  if (D_L19_0021EA30.state[(short)id] || (savedCount=D_0019B4A8[((short)id>>1)+(g_current_map_index<<10)], (id&1) ? ((savedCount>>4)&7) : (savedCount&7))) {moby_mark_spawned(moby);return;}
 }
 if (!moby_is_in_selected_zone(moby+0x10)) return;
 vars=*(char **)(moby+0x68);
 if (!*(u8 *)(moby+0x20)) {
  *(int *)(moby+0x78)=D_L19_001B1DE0;
  *(float *)(moby+0x18)=coll_probe_ground_height_below(moby+0x10,0,0.5f)-0.1f;
  *(u8 *)(moby+0x31)=1; *(u16 *)(moby+0x34)|=0x100; *(int *)(moby+0x48)=0;
  qcopy(scratchA,moby+0x10); qcopy(scratchB,moby+0x10); scratchA[2]+=1; scratchB[2]-=10;
  CollLine(scratchA,scratchB,2,moby,0);
  mat_align_to_dir(moby+0xc0,D_L19_001BFEC0,0); moby_set_state(moby,1,0);
 }
 if (*(u8 *)(moby+0x31)) EmitGrelbinGlowSprites(moby);
 if (*(u8 *)(moby+0x20)!=1) return;
 hitInfo=part_find_owned_effect_slot(moby,0x230000,0);
 health=(float *)(vars+0x20);color=vars+0x50;
 damage=moby_update_aim_target_strength(moby,hitInfo);
 if(damage>0) {
  *health-=damage;
  *(u8 *)(color+7)=255; *(u8 *)(color+8)=255; *(u8 *)(color+9)=255;
  gfx_start_color_fade(moby,color);
  anim_start_immediate(moby,0,FloatToInt(IntToFloat(*(short *)(vars+0x24))-*health)<8 ? FloatToInt(IntToFloat(*(short *)(vars+0x24))-*health):7);
  {int soundIndex=math_random_int_range(0,2); if(*health>0)PlayMobySound(soundIndex,0,moby);}
 }
 *(u8 *)(moby+0xa8)=255;gfx_update_color_fade(moby,color);
 if(*health<=0) {
  qzero(scratchA); scratchA[2]=1.0f/6.0f;
  if(hitInfo)qcopy(scratchB,hitInfo);else {qcopy(scratchB,moby+0x10); scratchB[2]+=2;}
  qzero(scratchA);scratchA[2]=0.15f;
  part_spawn_masked_debris(moby,15,scratchA,3,6,3,6,255);
  dropMoby=CreateMoby(0x1266 /* moby class 4710 */);
  if(dropMoby) {
   *(u8 *)(dropMoby+0x23)=0x50;*(u16 *)(dropMoby+0x34)|=0x800;
   *(float *)(dropMoby+0x2c)=*(float *)(*(char **)(dropMoby+0x24)+0x24)*0.65f;
   *(u8 *)(dropMoby+0x30)=255;*(u16 *)(dropMoby+0x32)=255;*(u8 *)(dropMoby+0x31)=1;*(u8 *)(dropMoby+0x20)=0;*(u8 *)(dropMoby+0xbc)=0;
   qcopy(dropMoby+0x10,moby+0x10);func_002A0F48(dropMoby);hero_copy_field_to_moby(dropMoby);PlayMobySound(3,0,moby);*(char **)(*(char **)(dropMoby+0x68)+4)=moby;
  }
  *(u8 *)(moby+0x20)=2;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xefff;*(int *)(moby+0x98)=0;
 }
}
