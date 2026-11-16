#include "include_asm.h"

#include "common.h"
extern int g_mission_menu_depth __attribute__((sda)), g_mission_select_enabled __attribute__((sda)), g_mission_menu_result __attribute__((sda));
extern int g_mission_menu_flag __attribute__((sda));
extern int g_mission_menu_ids[4] __attribute__((sda));
extern int g_notice_owner MACRO_ADDR;
extern char *g_resident_data_base MACRO_ADDR;
extern char *D_001A8CFC_gp SDATA(D_001A8CFC);
typedef struct { char pad[0x1C0]; int flags; int pad2[2]; int state; } MenuInput;
extern MenuInput g_pad_state;
extern void menu_update_mission_select_enable_pal(void), RefreshMissionMenuItems_pal(void);
extern void circle_menu_position_label_pal(void *), circle_menu_set_enabled_pal(void *, int), circle_menu_set_selection_pal(void *, int);
extern int UpdateDirectionSelection_pal(void *, void *), table_find_last_used_entry(int);
extern void menu_clear_field_150(void *);

/* Updates the mission select menu each frame and returns the chosen mission when the button is released, else -1. */
int UpdateMissionSelectionMenu_pal(void) {
 int result, changed;
 if (g_mission_menu_depth == 0) return -1;
 if (g_notice_owner != 0) return -1;
 if (D_001A8CFC_gp != 0) {
  menu_update_mission_select_enable_pal();
  {
   int enabled = 0;
   switch (g_mission_select_enabled) {
    case 0: return -1;
    case 1:
     changed = 0;
     RefreshMissionMenuItems_pal();
     if (g_pad_state.flags & 0x10) {
      g_mission_menu_flag = 1;
      g_pad_state.state = 2;
     } else if (g_mission_menu_flag != 0) {
      g_mission_menu_flag = 0;
      changed = 1;
     }
     circle_menu_position_label_pal(g_resident_data_base + 0x3F860);
     enabled = g_mission_menu_flag;
     break;
    default: changed = 0; break;
   }
   circle_menu_set_enabled_pal(g_resident_data_base + 0x3F860, enabled);
  }
  result = UpdateDirectionSelection_pal(g_resident_data_base + 0x3CDF8, &g_pad_state);
  if (result >= 0 && table_find_last_used_entry(g_mission_menu_ids[result]) < 0) result = -1;
  if (changed) {
   menu_clear_field_150(D_001A8CFC_gp + 0x3CDF8);
   if (g_mission_menu_result < 0) g_mission_menu_result = result;
  }
  circle_menu_set_selection_pal(g_resident_data_base + 0x3F860, result);
  return changed ? result : -1;
 }
 g_mission_menu_depth--;
 if (g_mission_menu_depth < 0) g_mission_menu_depth = 0;
 return 0;
}
