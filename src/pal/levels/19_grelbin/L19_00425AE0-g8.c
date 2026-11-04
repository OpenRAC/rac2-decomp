/* func_PAL_L19_00425AE0, the PAL copy of func_L19_004203F0: the same C, where func_L19_00423270
   becomes func_PAL_L19_004289C0; func_002A96A0 becomes func_PAL_002AA108; func_002AB800 becomes
   func_PAL_002AC290; func_002AB8C0 becomes func_PAL_002AC3C0; 1.0f / 6.0f becomes 0.20000002f;
   0.15f becomes 0.18f; func_002B0A68 becomes func_PAL_002B15D8. */
#include "common.h"
extern unsigned char D_0019B4A8[];
extern struct { char pad[0x464]; u8 state[0]; } D_L19_0021EA30;
extern int D_001A79F0 SDATA(D_001A79F0);
extern int D_L19_001B1DE0 __attribute__((sda));
extern char D_L19_001BFEC0[];
extern void func_0029F338(void *);
extern int func_002ACD38(void *);
extern float func_002A89A8(void *, int, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_002B0408(void *, void *, void *), func_002A7750(void *, int, int), func_PAL_L19_004289C0(void *);
extern void *func_002A9640(void *, int, int);
extern float func_PAL_002AA108(void *, void *), func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_PAL_002AC290(void *, void *), func_002A7398(void *, int, int), func_PAL_002AC3C0(void *, void *);
extern int func_002A7820(int,int);
extern int func_002E5CF8(int,int,void *);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern char *func_0029EFD0(int);
extern void func_002A0F48(void *), func_002AB650(void *);
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
  if (D_L19_0021EA30.state[(short)id] || (v=D_0019B4A8[((short)id>>1)+(D_001A79F0<<10)], (id&1) ? ((v>>4)&7) : (v&7))) {func_0029F338(o);return;}
 }
 if (!func_002ACD38(o+0x10)) return;
 d=*(char **)(o+0x68);
 if (!*(u8 *)(o+0x20)) {
  *(int *)(o+0x78)=D_L19_001B1DE0;
  *(float *)(o+0x18)=func_002A89A8(o+0x10,0,0.5f)-0.1f;
  *(u8 *)(o+0x31)=1; *(u16 *)(o+0x34)|=0x100; *(int *)(o+0x48)=0;
  qcopy(a,o+0x10); qcopy(b,o+0x10); a[2]+=1; b[2]-=10;
  func_002761F8(a,b,2,o,0);
  func_002B0408(o+0xc0,D_L19_001BFEC0,0); func_002A7750(o,1,0);
 }
 if (*(u8 *)(o+0x31)) func_PAL_L19_004289C0(o);
 if (*(u8 *)(o+0x20)!=1) return;
 hit=func_002A9640(o,0x230000,0);
 health=(float *)(d+0x20);color=d+0x50;
 damage=func_PAL_002AA108(o,hit);
 if(damage>0) {
  *health-=damage;
  *(u8 *)(color+7)=255; *(u8 *)(color+8)=255; *(u8 *)(color+9)=255;
  func_PAL_002AC290(o,color);
  func_002A7398(o,0,func_00283CF0(func_00283CE0(*(short *)(d+0x24))-*health)<8 ? func_00283CF0(func_00283CE0(*(short *)(d+0x24))-*health):7);
  {int s=func_002A7820(0,2); if(*health>0)func_002E5CF8(s,0,o);}
 }
 *(u8 *)(o+0xa8)=255;func_PAL_002AC3C0(o,color);
 if(*health<=0) {
  qzero(a); a[2]=0.20000002f;
  if(hit)qcopy(b,hit);else {qcopy(b,o+0x10); b[2]+=2;}
  qzero(a);a[2]=0.18f;
  func_PAL_002B15D8(o,15,a,3,6,3,6,255);
  n=func_0029EFD0(0x1266);
  if(n) {
   *(u8 *)(n+0x23)=0x50;*(u16 *)(n+0x34)|=0x800;
   *(float *)(n+0x2c)=*(float *)(*(char **)(n+0x24)+0x24)*0.65f;
   *(u8 *)(n+0x30)=255;*(u16 *)(n+0x32)=255;*(u8 *)(n+0x31)=1;*(u8 *)(n+0x20)=0;*(u8 *)(n+0xbc)=0;
   qcopy(n+0x10,o+0x10);func_002A0F48(n);func_002AB650(n);func_002E5CF8(3,0,o);*(char **)(*(char **)(n+0x68)+4)=o;
  }
  *(u8 *)(o+0x20)=2;*(u16 *)(o+0x34)=(*(u16 *)(o+0x34)|0x41)&0xefff;*(int *)(o+0x98)=0;
 }
}
