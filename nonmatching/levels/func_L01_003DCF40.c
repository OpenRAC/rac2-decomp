/* Reconstruction retained 3 November 2026 (task v2225, tier opus-1: Claude Opus 5.5); not a linked match.
 * Profile: -O2 -G8 -ffunction-sections (place it in src/levels/01_oozla/L01_003DA740-g8.c).
 * Best check: 1100/1120 bytes, 0/1 places. Prologue, the whole initialization block
 * (both constant/store groups), the qcopy/qzero_nc section and the $gp address now match.
 * Remaining: the three -1 fallback chains (0x414/0x418/0x41C into 0x3F8). Retail
 * allocates first=a0, second=v1, third=v0, so three separate stores survive; here
 * global gives first=v1 (only v0 conflicts) and second=v0, so jump2 cross-jumps the
 * second/third `sw v0,0x3F8` (8 bytes per chain). Needs something that keeps the first
 * value out of v1 (e.g. a v1 preference on the second value). Everything after follows.
 * Store order is set by sched1 REG_DEAD weight: shared constants must die at the store
 * retail issues first (hence 0x182/0x183/0x29/0x30 written after 0x28, and 0x2C0/0x2CC/
 * 0x1C8/0x1C4 before 0x2D0/0x1C0/0x1CC). qzero_nc (not qzero) gives retail's fresh -1 loads.
 * Declarations: see below; D_L01_001B0900 needs the explicit SDATA GP view.
 */
extern s32 func_00283CF0(f32);
extern f32 func_002A78D8(f32,f32);
extern void func_L01_003377C8(void *);
extern void func_002B60B0(void *,f32,f32,f32,f32);
extern void func_002A7750(void *,s32,s32);
extern s32 func_002A7820(s32,s32);
extern void func_002A7470(void *,s32,s32,s32);
extern u8 *D_L01_001FE180[] NOT_SDA;
extern u8 D_L01_001B0900[] SDATA(D_L01_001B0900);
typedef int InitQuad __attribute__((mode(TI)));
void func_L01_003DCF40(u8 *obj) {
 u8 *p=*(u8 **)(obj+0x68);
 *(void **)(p+0x18)=p+0x1C0;
 p[0x48]=func_00283CF0(10.0f);
 p[0x4A]=func_00283CF0(9.6f);
 *(s32 *)(p+0x158)=5;
 *(u8 *)(p+0x127)=11;
 *(f32 *)(p+0x12C)=0.20000001788139343f;
 *(f32 *)(p+0x130)=0.10000000894069672f;
 *(f32 *)(p+0x134)=0.006111111491918564f;
 *(f32 *)(p+0x138)=0.010277777910232544f;
 *(f32 *)(p+0x13C)=0.011111111380159855f;
 *(f32 *)(p+0x14C)=0.4f;
 *(u8 *)(p+0x120)=0;
 *(u8 *)(p+0x121)=10;
 *(u8 *)(p+0x122)=10;
 *(u8 *)(p+0x126)=10;
 *(f32 *)(p+0x140)=0.5f;
 *(f32 *)(p+0x144)=0.5f;
 *(u8 *)(p+0x17C)=6;
 *(u8 *)(p+0x17D)=10;
 *(u8 *)(p+0x17E)=6;
 *(u8 *)(p+0x17F)=10;
 *(s16 *)(p+0x148)=0;
 *(u8 *)(p+0x28)=0;
 *(u8 *)(p+0x182)=6;
 *(u8 *)(p+0x183)=10;
 *(u8 *)(p+0x29)=1;
 *(f32 *)(p+0x30)=0.5f;
 *(InitQuad *)(p+0x3A0)=*(InitQuad *)(obj+0x10);
 *(s16 *)(p+0x3D8)=0;
 if(*(s32 *)(p+0x3C0)!=-1) func_L01_003377C8(D_L01_001FE180[*(s32 *)(p+0x3C0)]);
 if(*(s32 *)(p+0x3BC)!=-1) func_L01_003377C8(D_L01_001FE180[*(s32 *)(p+0x3BC)]);
 qcopy(p+0x2B0,obj+0x10);
 *(f32 *)(p+0x2C0)=0.3f;
 *(f32 *)(p+0x2CC)=5.0f;
 *(f32 *)(p+0x1C8)=0.2f;
 *(f32 *)(p+0x1C4)=0.1f;
 *(f32 *)(p+0x2D0)=5.0f;
 *(f32 *)(p+0x1C0)=0.3f;
 *(f32 *)(p+0x1CC)=0.2f;
 *(f32 *)(p+0x1D0)=0.8726646900177002f;
 *(f32 *)(p+0x1F0)=0.523598849773407f;
 *(f32 *)(p+0x1EC)=0.0055555556900799274f;
 *(s32 *)(p+0x1FC)=*(s32 *)(p+0x3BC);
 *(f32 *)(p+0x29C)=func_002A78D8(25.0f,35.0f)*0.01745329424738884f;
 *(s16 *)(p+0x2A2)=120;
 *(s16 *)(p+0x2A4)=180;
 func_002B60B0(obj,0.002222222276031971f,0.06666667014360428f,0.0021331803873181343f,0.19198624789714813f);
 *(f32 *)(p+0xF0)=*(f32 *)(obj+0x2C);
 *(f32 *)(p+0xE0)=*(f32 *)(p+0x30);
 *(void **)(p+0xC0)=D_L01_001B0900;
 *(s32 *)(obj+0xF4)=0;
 *(s32 *)(obj+0xF0)=0;
 qzero_nc(p+0x210);
 *(f32 *)(p+0x218)=1.0f;
 if(obj[0x21]!=255) {
   **(s32 **)(p+0x3FC)=0;
   **(s32 **)(p+0x400)=-1;
 }
 if(!p[0x3D0]) {
  if(p[0x3D1]) {
   if(*(s32 *)(p+0x414)!=-1) *(s32 *)(p+0x3F8)=*(s32 *)(p+0x414);
   else if(*(s32 *)(p+0x418)!=-1) *(s32 *)(p+0x3F8)=*(s32 *)(p+0x418);
   else *(s32 *)(p+0x3F8)=*(s32 *)(p+0x41C);
   if(p[0x3D2]) func_002A7750(obj,0,1);
   else func_002A7750(obj,1,3);
  } else {
   if(*(s32 *)(p+0x418)!=-1) *(s32 *)(p+0x3F8)=*(s32 *)(p+0x418);
   else if(*(s32 *)(p+0x414)!=-1) *(s32 *)(p+0x3F8)=*(s32 *)(p+0x414);
   else *(s32 *)(p+0x3F8)=*(s32 *)(p+0x41C);
   func_002A7750(obj,1,3);
  }
  if(*(s32 *)(p+0x408)!=-1) {
   if(obj[0x43]!=7) func_002A7470(obj,7,0,func_002A7820(2,10));
  } else if(obj[0x43]!=0) func_002A7470(obj,0,0,func_002A7820(2,10));
 } else {
  if(*(s32 *)(p+0x414)!=-1) *(s32 *)(p+0x3F8)=*(s32 *)(p+0x414);
  else if(*(s32 *)(p+0x418)!=-1) *(s32 *)(p+0x3F8)=*(s32 *)(p+0x418);
  else *(s32 *)(p+0x3F8)=*(s32 *)(p+0x41C);
  *(s32 *)(obj+0x98)=0;
  obj[0x31]=0;
  *(u16 *)(obj+0x34)|=1;
  *(f32 *)(obj+0x18)-=2.0f;
  func_002A7750(obj,0,1);
  if(obj[0x43]!=0) func_002A7470(obj,0,0,func_002A7820(2,10));
 }
}
