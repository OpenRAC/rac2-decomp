#include "include_asm.h"
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
extern int D_L00_001A7D00[2] __attribute__((sda));
extern unsigned char D_L00_001DA860[];
extern int D_L00_001D9F00[];
typedef struct { char data[0x600]; } LargeBufferAED68;
typedef struct { char data[0x400]; } SmallBufferAED68;
extern LargeBufferAED68 D_L00_001B5C00[];
extern SmallBufferAED68 D_L00_001B3400[];
extern float func_002AA2E8(float *,float,float);
extern void func_L00_00310C88(void *,void *);
extern SlotAED68 *func_L00_00310BC8(void *,int);
extern void func_L00_00310D30(void *,void *);
extern int func_L00_002A4EF0(int);
extern int func_L00_002ADFE8(int,float *);
extern int func_L00_002ADFD0(void *,int);
void func_L00_002AED68(void)
{
 int i,j,enabled,different,active; struct { short v; } transition; float amount;
 for(i=0;i<2;i++) {
  StateAED68 *g=&D_00189E20_26;
  SlotAED68 *t0=D_00189E20_26.slots[i];
  if(t0 && t0->destroy) {
   if(func_002AA2E8(&t0->opacity,0.0f,0.1f)==0.0f)
    func_L00_00310C88(g->f2290,&D_00189E20_26.slots[i]);
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
     D_00189E20_26.slots[i]=func_L00_00310BC8(h->f2290,D_L00_001A7D00[i]);
     D_00189E20_26.slots[i]->opacity=0.0f;
     D_00189E20_26.slots[i]->icon=D_L00_001D9F00[D_L00_001DA860[i+1]];
    }
   } else {
    StateAED68 *h=&D_00189E20_26;
    if(!D_00189E20_26.slots[i]) continue;
    if(func_002AA2E8(&D_00189E20_26.slots[i]->opacity,0.0f,0.15f)==0.0f)
     func_L00_00310C88(h->f2290,&D_00189E20_26.slots[i]);
   }
  }
  {
  StateAED68 *h=&D_00189E20_26;
  SlotAED68 *p=D_00189E20_26.slots[i]; if(!p) continue;
  different=h->f2290->modes[0]!=h->f2290->modes[1];
  if(h->fe98 && !h->fea4)
   func_002AA2E8(&p->opacity,0.0f,0.15f);
  else if(!p->destroy) func_002AA2E8(&p->opacity,1.0f,0.25f);
  transition.v=0;
  if(different && D_00189E20_26.fc2c &&
     func_L00_002A4EF0(p->modes[1])!=func_L00_002A4EF0(D_00189E20_26.f2290->modes[1]))
   transition.v=p->modes[0]!=p->modes[1];
  p->transition=transition.v;
  active=func_L00_002ADFE8(g->f2290->modes[1],&amount);
  if(active || p->active) {
   if(amount!=0.0f) {
    D_L00_0025BE10.f6d4=0.05f; D_L00_0025BE10.f6d8=0.3f;
    D_L00_0025BE10.f694=amount; D_L00_0025BE10.f5e4=amount;
    D_L00_0025BE10.f624=0.05f; D_L00_0025BE10.f628=0.3f;
   }
   if(active && (!p->active || p->modes[1])) {
     if(p->modes[0]==p->modes[1] || p->progress>0.5f) { p->modes[0]=p->modes[1]; p->ids[0]=p->ids[1]; }
     p->progress=0.0f; p->speed=0.06666667f; p->modes[1]=0; p->ids[1]=0;
     p->scale=1.0f; p->active=1; p->fading=0;
   }
   if(!active) {
    if(!p->fading) {
     p->modes[1]=func_L00_002ADFD0(g->f2290,g->f2290->modes[1]);
     p->ids[1]=0; p->fading=1; p->progress=0; p->scale=0;
    } else {
     p->progress+=0.1f; if(p->progress>1.0f) p->progress=1.0f;
     if(p->progress==1.0f) p->active=0;
    }
   } else p->scale=1.0f;
   { int k;
   for(k=0;k<2;k++) {
    if(p->modes[k]<23) { p->flags[k]=1; p->buffers[k]=&D_L00_001B3400[i*2+k]; }
    else { p->flags[k]=0; p->buffers[k]=&D_L00_001B5C00[i*2+k]; }
   }
   }
   func_L00_00310D30(g->f2290,p);
  } else {
   if(!p->transition) for(j=0;j<2;j++) {
    if(different && j!=1) continue;
    p->modes[j]=func_L00_002ADFD0(D_00189E20_26.f2290,D_00189E20_26.f2290->modes[j]);
   }
   if(p->transition) {
    p->progress+=0.15f;
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
    if(p->modes[l]<23) { p->flags[l]=1; p->buffers[l]=&D_L00_001B3400[i*2+l]; }
    else { p->flags[l]=0; p->buffers[l]=&D_L00_001B5C00[i*2+l]; }
   }
   }
   func_L00_00310D30(g->f2290,p);
  }
  }
 }
}
