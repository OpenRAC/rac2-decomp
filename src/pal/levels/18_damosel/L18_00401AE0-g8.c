#include "include_asm.h"

#include "common.h"
extern int g_frame_l18_counter[] __attribute__((sda));
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

/* Slides the object along a straight line in one of two directions, switching direction when a trigger fires or the hero's presence changes. (PAL: 50 Hz timings) */
void sliding_l18_door_update_pal(u8 *moby) {
 u8 *state=*(u8 **)(moby+0x68);
 switch(moby[0x20]) {
 case 0:
  qcopy(state+0x40,moby+0x10);
  W(state,0x6c)=(int)(F(state,0x60)/(F(state,0x64)*0.020000001f));
  vec_scale_to_length(state+0x50,state+0x30,F(state,0x60)/(float)W(state,0x6c));
  moby_set_state(moby,1,-1);
  W(state,0x68)=0; W(state,0x74)=0;
  break;
 case 1:
  if(W(state,0x68)>=2) {
   FastVecSub(moby+0x10,moby+0x10,state+0x50);
   W(state,0x68)--;
  } else if(W(state,0x68)>0) {
   qcopy_nc(moby+0x10,state+0x40); W(state,0x68)--;
  }
  if(!(g_frame_l18_counter[0]&15)) {
   if(door_check_open_condition(moby,W(state,0x70)!=-1?g_moby_l18_table+(W(state,0x70)<<8)+0x10:g_hero_position))
    moby_set_state(moby,2,-1);
  }
  if(flag_is_third_pending_set(moby)) { moby[0xbe]&=0xfb; moby_set_state(moby,2,-1); }
  break;
 case 2:
  if(W(state,0x68)<W(state,0x6c)) {
   FastVecAdd(moby+0x10,moby+0x10,state+0x50); W(state,0x68)++;
  }
  if(!(g_frame_l18_counter[0]&15)) {
   if(door_check_close_condition(moby,W(state,0x70)!=-1?g_moby_l18_table+(W(state,0x70)<<8)+0x10:g_hero_position))
    moby_set_state(moby,1,-1);
  }
  if(flag_is_third_pending_set(moby)) { moby[0xbe]&=0xfb; moby_set_state(moby,1,-1); }
  break;
 }
 if(*(u16 *)(moby+0x96)<=0xfffe) ++*(u16 *)(moby+0x96);
}
