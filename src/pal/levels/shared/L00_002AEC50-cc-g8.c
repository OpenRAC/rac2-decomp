#include "names.h"
/* func_PAL_L00_002AEC50, the PAL copy of func_L00_002AED68: the same C. */
typedef struct SlotAED68 {
 unsigned char pad0[6];
 unsigned char flags[2];
 float opacity;
 unsigned char padc[12];
 int icon;
 unsigned char pad1c[4];
 unsigned char ids[2];
 unsigned char modes[2];
 float progress, scale, speed;
 short transition;
 unsigned char active, fading;
 int destroy;
 void *buffers[2];
} SlotAED68;
typedef struct PlayerAED68 {
 unsigned char pad0[0x40];
 unsigned char ids[2], modes[2];
 float progress;
} PlayerAED68;
typedef struct StateAED68 {
 char pad0[3116];
 int fc2c;
 char padc30[608];
 SlotAED68 *slots[2];
 int fe98;
 char pade9c[8];
 int fea4;
 char padea8[5096];
 PlayerAED68 *f2290;
 char pad2294[39];
 unsigned char f22bb;
 char pad22bc[3];
 unsigned char f22bf;
} StateAED68;
extern StateAED68 D_00189E20_26;
extern struct {
 char pad0[1508];
 float f5e4;
 char pad5e8[60];
 float f624;
 float f628;
 char pad62c[104];
 float f694;
 char pad698[60];
 float f6d4;
 float f6d8;
} D_L00_0025BE10;
extern int g_hero_item_anim_ids[2] __attribute__((sda));
extern unsigned char g_class_slot_indices[];
extern int g_sound_bank_table[];
typedef struct { char data[0x600]; } LargeBufferAED68;
typedef struct { char data[0x400]; } SmallBufferAED68;
extern LargeBufferAED68 g_item_large_anim_buffers[];
extern SmallBufferAED68 g_item_small_anim_buffers[];
extern float ApproachValue(float *,float,float);
extern void release_moby_animation_slot(void *,void *);
extern SlotAED68 *allocate_moby_animation_slot(void *,int);
extern void AdvanceAndDecodeAnimationFrames(void *,void *);
extern unsigned long math_l00_return_argument(int);
extern int hero_get_item_aim_adjustment(int,float *);
extern int hero_get_value_or_default(void *,int);
/* Fades the two on-screen hero item slots in and out, tracks the equipped item ids and modes, and
   advances their icon animations (PAL copy of update_hero_item_slot_animation_blends). */
void update_hero_item_slot_animation_blends_pal(void)
{
 int i,j,enabled,different,active; struct { short v; } transition; float amount;
 for(i=0;i<2;i++) {
  StateAED68 *g=&D_00189E20_26;
  SlotAED68 *t0=D_00189E20_26.slots[i];
  if(t0 && t0->destroy) {
   if(ApproachValue(&t0->opacity,0.0f,0.120000005f)==0.0f)
    release_moby_animation_slot(g->f2290,&D_00189E20_26.slots[i]);
  } else {
   enabled=0;
   if(g->f22bb && (i==0 || g->f22bb==2)) enabled=1;
   { StateAED68 *k=&D_00189E20_26;
   if(k->f22bf) {
    enabled=0;
    if(D_00189E20_26.slots[i]) D_00189E20_26.slots[i]->destroy=1;
   } }
   if(enabled) {
    StateAED68 *h=&D_00189E20_26;
    if(!D_00189E20_26.slots[i]) {
     D_00189E20_26.slots[i]=allocate_moby_animation_slot(h->f2290,g_hero_item_anim_ids[i]);
     D_00189E20_26.slots[i]->opacity=0.0f;
     D_00189E20_26.slots[i]->icon=g_sound_bank_table[g_class_slot_indices[i+1]];
    }
   } else {
    StateAED68 *h=&D_00189E20_26;
    if(!D_00189E20_26.slots[i]) continue;
    if(ApproachValue(&D_00189E20_26.slots[i]->opacity,0.0f,0.18f)==0.0f)
     release_moby_animation_slot(h->f2290,&D_00189E20_26.slots[i]);
   }
  }
  {
  StateAED68 *h=&D_00189E20_26;
  SlotAED68 *p=D_00189E20_26.slots[i]; if(!p) continue;
  different=h->f2290->modes[0]!=h->f2290->modes[1];
  if(h->fe98 && !h->fea4)
   ApproachValue(&p->opacity,0.0f,0.18f);
  else if(!p->destroy) ApproachValue(&p->opacity,1.0f,0.3f);
  transition.v=0;
  if(different && D_00189E20_26.fc2c &&
     math_l00_return_argument(p->modes[1])!=math_l00_return_argument(D_00189E20_26.f2290->modes[1]))
   transition.v=p->modes[0]!=p->modes[1];
  p->transition=transition.v;
  active=hero_get_item_aim_adjustment(g->f2290->modes[1],&amount);
  if(active || p->active) {
   if(amount!=0.0f) {
    g_hero_item_attach_records.f6d4=0.072000004f; g_hero_item_attach_records.f6d8=0.43200004f;
    g_hero_item_attach_records.f694=amount; g_hero_item_attach_records.f5e4=amount;
    g_hero_item_attach_records.f624=0.072000004f; g_hero_item_attach_records.f628=0.43200004f;
   }
   if(active && (!p->active || p->modes[1])) {
     if(p->modes[0]==p->modes[1] || p->progress>0.5f) { p->modes[0]=p->modes[1]; p->ids[0]=p->ids[1]; }
     p->progress=0.0f; p->speed=0.083333336f; p->modes[1]=0; p->ids[1]=0;
     p->scale=1.0f; p->active=1; p->fading=0;
   }
   if(!active) {
    if(!p->fading) {
     p->modes[1]=hero_get_value_or_default(g->f2290,g->f2290->modes[1]);
     p->ids[1]=0; p->fading=1; p->progress=0; p->scale=0;
    } else {
     p->progress+=0.120000005f; if(p->progress>1.0f) p->progress=1.0f;
     if(p->progress==1.0f) p->active=0;
    }
   } else p->scale=1.0f;
   { int k;
   for(k=0;k<2;k++) {
    if(p->modes[k]<23) { p->flags[k]=1; p->buffers[k]=&g_item_small_anim_buffers[i*2+k]; }
    else { p->flags[k]=0; p->buffers[k]=&g_item_large_anim_buffers[i*2+k]; }
   }
   }
   AdvanceAndDecodeAnimationFrames(g->f2290,p);
  } else {
   if(!p->transition) for(j=0;j<2;j++) {
    if(different && j!=1) continue;
    p->modes[j]=hero_get_value_or_default(D_00189E20_26.f2290,D_00189E20_26.f2290->modes[j]);
   }
   if(p->transition) {
    p->progress+=0.18f;
    if(p->progress>=1.0f) { p->modes[0]=p->modes[1]; p->ids[0]=p->ids[1]; p->transition=0; }
   } else {
    if(!different) {
     p->ids[0]=g->f2290->ids[0];
     p->ids[1]=g->f2290->ids[1];
     p->progress=g->f2290->progress;
    } else {
     p->ids[1]=g->f2290->ids[1];
     p->progress=g->f2290->progress;
    }
   }
   { int l;
   for(l=0;l<2;l++) {
    if(p->modes[l]<23) { p->flags[l]=1; p->buffers[l]=&g_item_small_anim_buffers[i*2+l]; }
    else { p->flags[l]=0; p->buffers[l]=&g_item_large_anim_buffers[i*2+l]; }
   }
   }
   AdvanceAndDecodeAnimationFrames(g->f2290,p);
  }
  }
 }
}
