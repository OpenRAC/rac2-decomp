#include "include_asm.h"

#include "common.h"
extern int D_L18_001B2348[] __attribute__((sda));
extern u8 *g_moby_l18_table;
extern u8 g_hero_position[];
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void moby_set_state(void *,int,int);
extern int flag_is_third_pending_set(void *);
extern int door_check_open_condition(u8 *,u8 *);
extern int door_check_close_condition(u8 *,u8 *);
#define W(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))

void func_PAL_L18_00401AE0(u8 *a) {
 u8 *s=*(u8 **)(a+0x68);
 switch(a[0x20]) {
 case 0:
  qcopy(s+0x40,a+0x10);
  W(s,0x6c)=(int)(F(s,0x60)/(F(s,0x64)*0.020000001f));
  vec_scale_to_length(s+0x50,s+0x30,F(s,0x60)/(float)W(s,0x6c));
  moby_set_state(a,1,-1);
  W(s,0x68)=0; W(s,0x74)=0;
  break;
 case 1:
  if(W(s,0x68)>=2) {
   FastVecSub(a+0x10,a+0x10,s+0x50);
   W(s,0x68)--;
  } else if(W(s,0x68)>0) {
   qcopy_nc(a+0x10,s+0x40); W(s,0x68)--;
  }
  if(!(D_L18_001B2348[0]&15)) {
   if(door_check_open_condition(a,W(s,0x70)!=-1?g_moby_l18_table+(W(s,0x70)<<8)+0x10:g_hero_position))
    moby_set_state(a,2,-1);
  }
  if(flag_is_third_pending_set(a)) { a[0xbe]&=0xfb; moby_set_state(a,2,-1); }
  break;
 case 2:
  if(W(s,0x68)<W(s,0x6c)) {
   FastVecAdd(a+0x10,a+0x10,s+0x50); W(s,0x68)++;
  }
  if(!(D_L18_001B2348[0]&15)) {
   if(door_check_close_condition(a,W(s,0x70)!=-1?g_moby_l18_table+(W(s,0x70)<<8)+0x10:g_hero_position))
    moby_set_state(a,1,-1);
  }
  if(flag_is_third_pending_set(a)) { a[0xbe]&=0xfb; moby_set_state(a,1,-1); }
  break;
 }
 if(*(u16 *)(a+0x96)<=0xfffe) ++*(u16 *)(a+0x96);
}
