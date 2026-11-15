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
extern void func_002B0408(void *, void *, void *), func_002A7750(void *, int, int), func_L19_00423270(void *);
extern void *func_002A9640(void *, int, int);
extern float func_002A96A0(void *, void *), func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_002AB800(void *, void *), func_002A7398(void *, int, int), func_002AB8C0(void *, void *);
extern int func_002A7820(int,int);
extern int func_002E5CF8(int,int,void *);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern char *func_0029EFD0(int);
extern void func_002A0F48(void *), func_002AB650(void *);
/* Remove the object when its persistence state says so; otherwise apply hit damage
 * and spawn object kind 0x1266 when health runs out. */
/* A breakable object. It flashes when hit, and when its health runs out it bursts and drops a pickup (moby class 4710). */
void func_L19_004203F0(char *moby)
{
 char *vars, *hitInfo, *dropMoby;
 float *health; char *color;
 float scratchA[4] __attribute__((aligned(16))), scratchB[4] __attribute__((aligned(16)));
 float damage;
 if (*(u8 *)(moby+0xb0)!=255) {
  unsigned short id=*(unsigned short *)(moby+0xb2);
  int savedCount;
  if (D_L19_0021EA30.state[(short)id] || (savedCount=D_0019B4A8[((short)id>>1)+(gCurrentMapIndex<<10)], (id&1) ? ((savedCount>>4)&7) : (savedCount&7))) {MarkMobySpawned(moby);return;}
 }
 if (!IsObjectInSelectedZone(moby+0x10)) return;
 vars=*(char **)(moby+0x68);
 if (!*(u8 *)(moby+0x20)) {
  *(int *)(moby+0x78)=D_L19_001B1DE0;
  *(float *)(moby+0x18)=ProbeGroundHeightBelow(moby+0x10,0,0.5f)-0.1f;
  *(u8 *)(moby+0x31)=1; *(u16 *)(moby+0x34)|=0x100; *(int *)(moby+0x48)=0;
  qcopy(scratchA,moby+0x10); qcopy(scratchB,moby+0x10); scratchA[2]+=1; scratchB[2]-=10;
  CollLine(scratchA,scratchB,2,moby,0);
  AlignRotationToDirection(moby+0xc0,D_L19_001BFEC0,0); SetMobyState(moby,1,0);
 }
 if (*(u8 *)(moby+0x31)) EmitGrelbinGlowSprites(moby);
 if (*(u8 *)(moby+0x20)!=1) return;
 hitInfo=FindOwnedEffectSlot(moby,0x230000,0);
 health=(float *)(vars+0x20);color=vars+0x50;
 damage=UpdateAimTargetStrength(moby,hitInfo);
 if(damage>0) {
  *health-=damage;
  *(u8 *)(color+7)=255; *(u8 *)(color+8)=255; *(u8 *)(color+9)=255;
  StartColorFade(moby,color);
  StartAnimationImmediate(moby,0,FloatToInt(IntToFloat(*(short *)(vars+0x24))-*health)<8 ? FloatToInt(IntToFloat(*(short *)(vars+0x24))-*health):7);
  {int soundIndex=RandomIntRange(0,2); if(*health>0)PlayMobySound(soundIndex,0,moby);}
 }
 *(u8 *)(moby+0xa8)=255;UpdateColorFade(moby,color);
 if(*health<=0) {
  qzero(scratchA); scratchA[2]=1.0f/6.0f;
  if(hitInfo)qcopy(scratchB,hitInfo);else {qcopy(scratchB,moby+0x10); scratchB[2]+=2;}
  qzero(scratchA);scratchA[2]=0.15f;
  SpawnDebrisForMaskedParts(moby,15,scratchA,3,6,3,6,255);
  dropMoby=CreateMoby(0x1266 /* moby class 4710 */);
  if(dropMoby) {
   *(u8 *)(dropMoby+0x23)=0x50;*(u16 *)(dropMoby+0x34)|=0x800;
   *(float *)(dropMoby+0x2c)=*(float *)(*(char **)(dropMoby+0x24)+0x24)*0.65f;
   *(u8 *)(dropMoby+0x30)=255;*(u16 *)(dropMoby+0x32)=255;*(u8 *)(dropMoby+0x31)=1;*(u8 *)(dropMoby+0x20)=0;*(u8 *)(dropMoby+0xbc)=0;
   qcopy(dropMoby+0x10,moby+0x10);func_002A0F48(dropMoby);CopyHeroField38ToMoby(dropMoby);PlayMobySound(3,0,moby);*(char **)(*(char **)(dropMoby+0x68)+4)=moby;
  }
  *(u8 *)(moby+0x20)=2;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xefff;*(int *)(moby+0x98)=0;
 }
}
