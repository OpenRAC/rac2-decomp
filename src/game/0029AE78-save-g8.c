#include "common.h"

/* Start a memory-card save. Adapted from RAC1 memcard_Save (GPL-3.0),
 * using RAC2's slot layout and the observed byte-sized entry field. */
extern char g_memcard_state[];
extern char g_cd_clock_buffer[] MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern int g_player_bolts MACRO_ADDR;
extern int g_frame_counter_2 MACRO_ADDR;
extern unsigned char g_extras_unlocked_flag MACRO_ADDR;
extern int g_save_menu_flags MACRO_ADDR;
extern unsigned char g_map_unlocked_flags[] MACRO_ADDR;
extern char g_map_occlusion_data[], g_memcard_save_buffer[], g_memcard_slot_buffer[];
extern int g_save_record_layout_main[], g_save_record_layout_slot[];
extern int sceCdReadClock(void *);
extern void clock_to_local_time(void *);
extern void map_copy_band_colours(void), map_fill_buffer(void *);
extern void *memcpy(void *, const void *, unsigned int);
extern int save_pack_records(void *, int, int *);
int MemcardSave(int slot, int flags) {
 unsigned char saved;
 sceCdReadClock(g_cd_clock_buffer);
 clock_to_local_time(g_cd_clock_buffer);
 map_copy_band_colours();
 map_fill_buffer(g_map_occlusion_data + (g_current_map_index << 11));
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
   saved = g_map_unlocked_flags[flags];
   if (saved == 0) g_map_unlocked_flags[flags] = 1;
  }
 }
 {
  char *q = g_memcard_state;
  char *names = q + 0x40;
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x34) = g_player_bolts;
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x30) = g_current_map_index;
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x3C) = g_frame_counter_2;
  memcpy(names + *(short *)(q + 0x18) * 0x1C, g_cd_clock_buffer, 8);
  *(int *)(q + *(short *)(q + 0x18) * 0x1C + 0x38) = g_extras_unlocked_flag;
  save_pack_records(g_memcard_save_buffer, 0, g_save_record_layout_main);
  save_pack_records(g_memcard_slot_buffer, *(int *)(q + 0x150), g_save_record_layout_slot);
  if (flags >= 0) {
   g_map_unlocked_flags[g_current_map_index] = saved;
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
