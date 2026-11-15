#include "common.h"
extern unsigned char *func_002AB1F0(unsigned char *);
extern void func_002A7750(unsigned char *, int, int);
extern int func_00283CF0(float);
extern int func_L09_003FE620(unsigned char *);
extern void func_0029F338(unsigned char *);
extern void func_L09_003FDA38(unsigned char *);
extern int func_002E5CF8(void *, int, unsigned char *);
extern unsigned char *D_L09_001B11B4 __attribute__((sda));
extern unsigned char *D_L09_001FE6C0[];
extern unsigned char D_00188660[];
/* Initializes the record channels and selects its initial track state. */
/* Sets up the moby's starting values, then either prepares it as a parent object or starts it at the first point of its path. */
void func_L09_003FE670(unsigned char *moby) {
 unsigned char *vars = *(unsigned char **)(moby+0x68);
 GetMobyPrivateValue0(moby)[14] = 1;
 vars[0x170]=2; *(int *)(vars+0x1A8)=2; vars[0x171]=1; vars[0x172]=1; vars[0x176]=1; vars[0x177]=1;
 *(float *)(vars+0x17C)=0.016666668f; *(float *)(vars+0x180)=0.016666668f;
 *(float *)(vars+0x184)=0.004166667f; *(float *)(vars+0x188)=0.008333334f;
 *(float *)(vars+0x18C)=0.004166667f; *(float *)(vars+0x190)=1.0f;
 *(float *)(vars+0x194)=-0.25f; *(float *)(vars+0x19C)=0.4f;

 vars[0x1CC]=7; vars[0x1CD]=12; vars[0x1CE]=3; vars[0x1CF]=5;
 vars[0x1D2]=10; vars[0x1D3]=17; vars[0x1D6]=1; vars[0x441]=0;
 if (*(short *)(vars+0x3D6)==1) {
  *(int *)(moby+0x98)=0; moby[0x30]=255;
  *(unsigned short *)(moby+0x34)=(*(unsigned short *)(moby+0x34)|0x41)&0xEFFF;
  SetMobyState(moby,5,-1);
  vars[0x48]=FloatToInt(17.0f); vars[0x4A]=FloatToInt(6.0f);
  *(short *)(vars+0x424)=CountTrackEntries(moby);
 } else {
  if (*(int *)(vars+0x314)==-1 || !*(int *)D_L09_001FE6C0[*(int *)(vars+0x314)] || *(int *)(vars+0x318)==-1 || !*(int *)D_L09_001FE6C0[*(int *)(vars+0x318)]) {MarkMobySpawned(moby);return;}
  vars[0x28]=3;
  qcopy_nc(moby+0x10,D_L09_001FE6C0[*(int *)(vars+0x314)]+0x10);
  qcopy_nc(vars+0x390,D_L09_001FE6C0[*(int *)(vars+0x318)]+0x10);
  MeasurePathsAndStartFollowers(moby);
  *(short *)(vars+0x328)=1; *(float *)(vars+0x43C)=-1.0f;
  *(float *)(vars+0x380)=*(float *)(vars+0x3B4)=*(float *)(vars+0x3B8)=
  *(float *)(vars+0x3BC)=*(float *)(vars+0x3A0)=*(float *)(vars+0x3A4)=*(float *)(vars+0x3A8)=0.0f;
  *(int *)(vars+0x42C)=0;
  *(float *)(vars+0x3CC)=*(float *)(vars+0x3C8)=*(float *)(vars+0x3C4)=*(float *)(vars+0x3C0)=*(float *)(vars+0x384)=0.0f;
  *(float *)(vars+0x3D0)=*(float *)(moby+0xF8); *(short *)(vars+0x3D4)=0; *(int *)(vars+0x3AC)=0;
  *(float *)(vars+0x3E8)=*(float *)(vars+0x3E4)=*(float *)(vars+0x3D8)=0.0f;
  SetMobyState(moby,1,-1);
  {unsigned char *soundEntry=gSoundState+*(int *)(vars+0x3F0)*0x70;
   if (*(unsigned char **)(soundEntry+0x88)!=moby || !soundEntry[0x74]) *(int *)(vars+0x3F0)=PlayMobySound(D_L09_001B11B4,4,moby);
  }
 }
}
