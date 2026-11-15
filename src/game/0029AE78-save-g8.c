#include "common.h"

/* Start a memory-card save. Adapted from RAC1 memcard_Save (GPL-3.0),
 * using RAC2's slot layout and the observed byte-sized entry field. */
extern char D_001393E0[];
extern char D_001A7360[] MACRO_ADDR;
extern int D_001A79F0 MACRO_ADDR;
extern int D_001A79F8 MACRO_ADDR;
extern int D_001A7BC0 MACRO_ADDR;
extern unsigned char D_001A7A0A MACRO_ADDR;
extern int D_001A7424 MACRO_ADDR;
extern unsigned char D_001A7BE8[] MACRO_ADDR;
extern char D_0018D278[], D_001A2BA8[], D_001A53A8[];
extern int D_00256138[], D_00256368[];
extern void func_001256D8(void *), func_00131A98(void *);
extern void func_002980D0(void), func_00297670(void *);
extern void *memcpy(void *, const void *, unsigned int);
extern int func_0029AF98(void *, int, int *);
/* Saves the game to the memory card slot: gathers the save data into a buffer and writes it. */
int func_0029B3E0(int slot, int flags) {
 unsigned char saved;
 func_001256D8(D_001A7360);
 func_00131A98(D_001A7360);
 func_002980D0();
 func_00297670(D_0018D278 + (D_001A79F0 << 11));
 {
  char *p = D_001393E0;
  int active = *(int *)(p + 0x148);
  int mask;
  if (active == -1 || *(short *)(p + active * 0xA0 + 0x18) < 0) return slot == 0;
  mask = *(int *)(p + 0x17C) | slot;
  *(int *)(p + 0x17C) = mask;
  if (mask == 0) goto done;
  if (slot == 0) D_001A7424 |= 0x200;
  if (*(int *)(p + 0x15C) >= 3) goto done;
  if (*(int *)(p + 0x164) >= 0) goto done;
  *(int *)(p + 0x150) = D_001A79F0;
  saved = 0;
  if (flags >= 0) {
   D_001A79F0 = flags;
   saved = D_001A7BE8[flags];
   if (saved == 0) D_001A7BE8[flags] = 1;
  }
 }
 {
  char *q = D_001393E0;
  char *names = q + 0x40;
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x34) = D_001A79F8;
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x30) = D_001A79F0;
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x3C) = D_001A7BC0;
  memcpy(names + *(short *)(q + 0x18) * 0x1C, D_001A7360, 8);
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x38) = D_001A7A0A;
  func_0029AF98(D_001A2BA8, 0, D_00256138);
  func_0029AF98(D_001A53A8, *(int *)(q + 0x150), D_00256368);
  if (flags >= 0) {
   D_001A7BE8[D_001A79F0] = saved;
   D_001A79F0 = *(int *)(q + 0x150);
  }
  if (*(int *)(q + 0x164) < 0) {
   *(int *)(q + 0x164) = 0xF;
   *(int *)(q + 0x168) = *(int *)(q + 0x148);
  }
 }
 done:
 { char *r = D_001393E0; return *(int *)(r + 0x164) == 0xF; }
}
