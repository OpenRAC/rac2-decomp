/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* GPT-6.1 Sol low worker, 28 October 2026, pinned upstream game compiler.
   180/184 bytes, 0/2 places. Explicit nested mode tests preserve retail
   equality branches; typed entry gives exact table-lookup instruction sequence.
   Reused low base differs: retail keeps high half and rematerializes low halves.
   Cached pointer gives 176 bytes, switch gives 168, sda base gives 176. Default -G0.
   Not linked or counted. */

extern char D_00189E20[];
extern unsigned char D_00139568[];
extern char D_L22_002645F0[];
extern int func_L00_002ADEA0(int);
typedef struct {
 char pad0[0x1492]; unsigned char unlocked;
 char pad1493[0x22B4-0x1493]; unsigned char mode;
 char pad22B5[5]; unsigned char ready;
 char pad22BB[0x24CC-0x22BB]; int progress;
 char pad24D0[0x24EC-0x24D0]; short timer;
} ShopState;
#define SHOP ((ShopState *)D_00189E20)
int func_L22_002A8CE0(int a0) {
 unsigned char mode = SHOP->mode;
 if (mode == 1) return 0;
 else if (mode == 2) return 0;
 else {
 ShopState *p = (ShopState *)D_00189E20;
 if (a0 && p->ready && !p->timer) {
   int index = func_L00_002ADEA0(0);
   typedef struct { char pad[0x28]; int value; char tail[0xE0-0x2C]; } Entry;
   return ((Entry *)D_L22_002645F0)[D_00139568[index]].value;
 } else if (SHOP->progress != 1) return SHOP->unlocked ? 0x67 : 0;
 else return 0x51;
 }
}
#undef SHOP
