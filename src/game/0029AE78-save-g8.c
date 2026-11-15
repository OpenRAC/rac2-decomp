#include "common.h"

/* Start a memory-card save. Adapted from RAC1 memcard_Save (GPL-3.0),
 * using RAC2's slot layout and the observed byte-sized entry field. */
extern char g_memcard_state[];
extern char D_001A7360[] MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern int g_player_bolts MACRO_ADDR;
extern int D_001A7BC0 MACRO_ADDR;
extern unsigned char D_001A7A0A MACRO_ADDR;
extern int g_save_menu_flags MACRO_ADDR;
extern unsigned char D_001A7BE8[] MACRO_ADDR;
extern char D_0018D278[], D_001A2BA8[], D_001A53A8[];
extern int D_00256138[], D_00256368[];
extern void sceCdReadClock(void *), clock_to_local_time(void *);
extern void map_copy_band_colours(void), map_fill_buffer(void *);
extern void *memcpy(void *, const void *, unsigned int);
extern int save_pack_records(void *, int, int *);
int MemcardSave(int slot, int flags) {
 unsigned char saved;
 sceCdReadClock(D_001A7360);
 clock_to_local_time(D_001A7360);
 map_copy_band_colours();
 map_fill_buffer(D_0018D278 + (g_current_map_index << 11));
 {
  char *p = g_memcard_state;
  int active = *(int *)(p + 0x148);
  int mask;
  if (active == -1 || *(short *)(p + active * 0xA0 + 0x18) < 0) return slot == 0;
  mask = *(int *)(p + 0x17C) | slot;
  *(int *)(p + 0x17C) = mask;
  if (mask == 0) goto done;
  if (slot == 0) g_save_menu_flags |= 0x200;
  if (*(int *)(p + 0x15C) >= 3) goto done;
  if (*(int *)(p + 0x164) >= 0) goto done;
  *(int *)(p + 0x150) = g_current_map_index;
  saved = 0;
  if (flags >= 0) {
   g_current_map_index = flags;
   saved = D_001A7BE8[flags];
   if (saved == 0) D_001A7BE8[flags] = 1;
  }
 }
 {
  char *q = g_memcard_state;
  char *names = q + 0x40;
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x34) = g_player_bolts;
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x30) = g_current_map_index;
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x3C) = D_001A7BC0;
  memcpy(names + *(short *)(q + 0x18) * 0x1C, D_001A7360, 8);
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x38) = D_001A7A0A;
  save_pack_records(D_001A2BA8, 0, D_00256138);
  save_pack_records(D_001A53A8, *(int *)(q + 0x150), D_00256368);
  if (flags >= 0) {
   D_001A7BE8[g_current_map_index] = saved;
   g_current_map_index = *(int *)(q + 0x150);
  }
  if (*(int *)(q + 0x164) < 0) {
   *(int *)(q + 0x164) = 0xF;
   *(int *)(q + 0x168) = *(int *)(q + 0x148);
  }
 }
 done:
 { char *r = g_memcard_state; return *(int *)(r + 0x164) == 0xF; }
}
