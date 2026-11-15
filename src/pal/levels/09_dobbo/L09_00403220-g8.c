#include "include_asm.h"

#include "common.h"
extern unsigned char *moby_get_private_value_0(unsigned char *);
extern void moby_set_state(unsigned char *, int, int);
extern int FloatToInt(float);
extern int track_count_entries(unsigned char *);
extern void moby_mark_spawned(unsigned char *);
extern void path_measure_start_followers(unsigned char *);
extern int PlayMobySound(void *, int, unsigned char *);
extern unsigned char *D_L09_001B11B4 __attribute__((sda));
extern unsigned char *D_L09_001FE6C0[];
extern unsigned char g_sound_state[];

/* Initializes the record channels and selects its initial track state. */
void func_PAL_L09_00403220(unsigned char *obj) {
 unsigned char *s = *(unsigned char **)(obj+0x68);
 moby_get_private_value_0(obj)[14] = 1;
 s[0x170]=2; *(int *)(s+0x1A8)=2; s[0x171]=1; s[0x172]=1; s[0x176]=1; s[0x177]=1;
 *(float *)(s+0x17C)=0.020000001f; *(float *)(s+0x180)=0.020000001f;
 *(float *)(s+0x184)=0.006f; *(float *)(s+0x188)=0.012f;
 *(float *)(s+0x18C)=0.006f; *(float *)(s+0x190)=1.0f;
 *(float *)(s+0x194)=-0.25f; *(float *)(s+0x19C)=0.4f;

 s[0x1CC]=7; s[0x1CD]=12; s[0x1CE]=3; s[0x1CF]=5;
 s[0x1D2]=10; s[0x1D3]=17; s[0x1D6]=1; s[0x441]=0;
 if (*(short *)(s+0x3D6)==1) {
  *(int *)(obj+0x98)=0; obj[0x30]=255;
  *(unsigned short *)(obj+0x34)=(*(unsigned short *)(obj+0x34)|0x41)&0xEFFF;
  moby_set_state(obj,5,-1);
  s[0x48]=FloatToInt(17.0f); s[0x4A]=FloatToInt(6.0f);
  *(short *)(s+0x424)=track_count_entries(obj);
 } else {
  if (*(int *)(s+0x314)==-1 || !*(int *)D_L09_001FE6C0[*(int *)(s+0x314)] || *(int *)(s+0x318)==-1 || !*(int *)D_L09_001FE6C0[*(int *)(s+0x318)]) {moby_mark_spawned(obj);return;}
  s[0x28]=3;
  qcopy_nc(obj+0x10,D_L09_001FE6C0[*(int *)(s+0x314)]+0x10);
  qcopy_nc(s+0x390,D_L09_001FE6C0[*(int *)(s+0x318)]+0x10);
  path_measure_start_followers(obj);
  *(short *)(s+0x328)=1; *(float *)(s+0x43C)=-1.0f;
  *(float *)(s+0x380)=*(float *)(s+0x3B4)=*(float *)(s+0x3B8)=
  *(float *)(s+0x3BC)=*(float *)(s+0x3A0)=*(float *)(s+0x3A4)=*(float *)(s+0x3A8)=0.0f;
  *(int *)(s+0x42C)=0;
  *(float *)(s+0x3CC)=*(float *)(s+0x3C8)=*(float *)(s+0x3C4)=*(float *)(s+0x3C0)=*(float *)(s+0x384)=0.0f;
  *(float *)(s+0x3D0)=*(float *)(obj+0xF8); *(short *)(s+0x3D4)=0; *(int *)(s+0x3AC)=0;
  *(float *)(s+0x3E8)=*(float *)(s+0x3E4)=*(float *)(s+0x3D8)=0.0f;
  moby_set_state(obj,1,-1);
  {unsigned char *r=g_sound_state+*(int *)(s+0x3F0)*0x70;
   if (*(unsigned char **)(r+0x88)!=obj || !r[0x74]) *(int *)(s+0x3F0)=PlayMobySound(D_L09_001B11B4,4,obj);
  }
 }
}
