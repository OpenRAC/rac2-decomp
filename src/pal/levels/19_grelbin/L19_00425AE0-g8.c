#include "names.h"
/* func_PAL_L19_00425AE0, the PAL copy of func_L19_004203F0: the same C, where func_L19_00423270
   becomes func_PAL_L19_004289C0; func_002A96A0 becomes func_PAL_002AA108; func_002AB800 becomes
   func_PAL_002AC290; func_002AB8C0 becomes func_PAL_002AC3C0; 1.0f / 6.0f becomes 0.20000002f;
   0.15f becomes 0.18f; func_002B0A68 becomes func_PAL_002B15D8. */
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
extern void mat_align_to_dir(void *, void *, void *), moby_set_state(void *, int, int), func_PAL_L19_004289C0(void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern float func_PAL_002AA108(void *, void *), IntToFloat(int);
extern int FloatToInt(float);
extern void func_PAL_002AC290(void *, void *), anim_start_immediate(void *, int, int), func_PAL_002AC3C0(void *, void *);
extern int math_random_int_range(int,int);
extern int PlayMobySound(int,int,void *);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern char *CreateMoby(int);
extern void func_002A0F48(void *), hero_copy_field_to_moby(void *);
/* Remove the object when its persistence state says so; otherwise apply hit damage
 * and spawn object kind 0x1266 when health runs out. */
void func_PAL_L19_00425AE0(char *o)
{
 char *d, *hit, *n;
 float *health; char *color;
 float a[4] __attribute__((aligned(16))), b[4] __attribute__((aligned(16)));
 float damage;
 if (*(u8 *)(o+0xb0)!=255) {
  unsigned short id=*(unsigned short *)(o+0xb2);
  int v;
  if (D_L19_0021EA30.state[(short)id] || (v=D_0019B4A8[((short)id>>1)+(g_current_map_index<<10)], (id&1) ? ((v>>4)&7) : (v&7))) {moby_mark_spawned(o);return;}
 }
 if (!moby_is_in_selected_zone(o+0x10)) return;
 d=*(char **)(o+0x68);
 if (!*(u8 *)(o+0x20)) {
  *(int *)(o+0x78)=D_L19_001B1DE0;
  *(float *)(o+0x18)=coll_probe_ground_height_below(o+0x10,0,0.5f)-0.1f;
  *(u8 *)(o+0x31)=1; *(u16 *)(o+0x34)|=0x100; *(int *)(o+0x48)=0;
  qcopy(a,o+0x10); qcopy(b,o+0x10); a[2]+=1; b[2]-=10;
  CollLine(a,b,2,o,0);
  mat_align_to_dir(o+0xc0,D_L19_001BFEC0,0); moby_set_state(o,1,0);
 }
 if (*(u8 *)(o+0x31)) func_PAL_L19_004289C0(o);
 if (*(u8 *)(o+0x20)!=1) return;
 hit=part_find_owned_effect_slot(o,0x230000,0);
 health=(float *)(d+0x20);color=d+0x50;
 damage=func_PAL_002AA108(o,hit);
 if(damage>0) {
  *health-=damage;
  *(u8 *)(color+7)=255; *(u8 *)(color+8)=255; *(u8 *)(color+9)=255;
  func_PAL_002AC290(o,color);
  anim_start_immediate(o,0,FloatToInt(IntToFloat(*(short *)(d+0x24))-*health)<8 ? FloatToInt(IntToFloat(*(short *)(d+0x24))-*health):7);
  {int s=math_random_int_range(0,2); if(*health>0)PlayMobySound(s,0,o);}
 }
 *(u8 *)(o+0xa8)=255;func_PAL_002AC3C0(o,color);
 if(*health<=0) {
  qzero(a); a[2]=0.20000002f;
  if(hit)qcopy(b,hit);else {qcopy(b,o+0x10); b[2]+=2;}
  qzero(a);a[2]=0.18f;
  func_PAL_002B15D8(o,15,a,3,6,3,6,255);
  n=CreateMoby(0x1266);
  if(n) {
   *(u8 *)(n+0x23)=0x50;*(u16 *)(n+0x34)|=0x800;
   *(float *)(n+0x2c)=*(float *)(*(char **)(n+0x24)+0x24)*0.65f;
   *(u8 *)(n+0x30)=255;*(u16 *)(n+0x32)=255;*(u8 *)(n+0x31)=1;*(u8 *)(n+0x20)=0;*(u8 *)(n+0xbc)=0;
   qcopy(n+0x10,o+0x10);func_002A0F48(n);hero_copy_field_to_moby(n);PlayMobySound(3,0,o);*(char **)(*(char **)(n+0x68)+4)=o;
  }
  *(u8 *)(o+0x20)=2;*(u16 *)(o+0x34)=(*(u16 *)(o+0x34)|0x41)&0xefff;*(int *)(o+0x98)=0;
 }
}
