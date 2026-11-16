#include "common.h"

/* Update the four-mission selection menu and return a completed selection.
 * The four table entries are also read by func_0029B910's bounded loop. */
extern int g_mission_menu_depth __attribute__((sda)), g_mission_select_enabled __attribute__((sda)), g_mission_menu_result __attribute__((sda));
extern int g_mission_menu_flag __attribute__((sda));
extern int g_mission_menu_ids[4] __attribute__((sda));
extern int g_notice_owner MACRO_ADDR;
extern char *g_resident_data_base MACRO_ADDR;
extern char *D_001A8CFC_gp SDATA(D_001A8CFC);
typedef struct { char pad[0x1C0]; int flags; int pad2[2]; int state; } MenuInput;
extern MenuInput g_pad_state;
extern void menu_update_mission_select_enable(void), RefreshMissionMenuItems(void);
extern void circle_menu_position_label(void *), circle_menu_set_enabled(void *, int), circle_menu_set_selection(void *, int);
extern int UpdateDirectionSelection(void *, void *), table_find_last_used_entry(int);
extern void menu_clear_field_150(void *);
extern void circle_menu_set_entry_mode(char *, int, int);

/* Mission record table entry (0x28 bytes). */
typedef struct {
    unsigned short id;           /* +0x00 */
    short pad02;
    int next;                    /* +0x04 */
    int pad08[4];
    int state;                   /* +0x18 */
    short count;                 /* +0x1C */
    short pad1E;
    int level;                   /* +0x20, read through the short item id */
    int flag;                    /* +0x24 */
} MissionRecord;

/* Item of the mission selection menu (0x18 bytes); D_00256418 is the item
 * array func_0029BA58 hands to the menu at D_001A8CFC + 0x3F138. */
typedef struct {
    int first;                   /* +0x00 */
    int second;                  /* +0x04 */
    int color;                   /* +0x08 */
    float angle;                 /* +0x0C */
    short id;                    /* +0x10 */
    short pad12;
    int text;                    /* +0x14 */
} MissionMenuItem;

extern MissionRecord g_mission_records[];
extern MissionMenuItem g_mission_menu_items[];

/* Refresh the four mission menu items from the mission IDs in D_001A9AC8:
 * a known mission's item gets its count, id and color and is passed to
 * func_0033A9D0 with 0, an unknown one with 2. */
void RefreshMissionMenuItems(void) {
    int i;
    int *ids;
    if (g_resident_data_base != 0) {
        ids = g_mission_menu_ids;
        for (i = 0; i < 4; i++) {
            int idx = table_find_last_used_entry(ids[i]);
            if (idx >= 0) {
                g_mission_menu_items[i].second = g_mission_records[idx].count;
                g_mission_menu_items[i].id = g_mission_records[idx].level;
                g_mission_menu_items[i].color = g_mission_records[idx].flag >= 1 ? 0x6029A1FF : 0x60F0F0B0;
                circle_menu_set_entry_mode(g_resident_data_base + 0x3F138, i, 0);
            } else {
                circle_menu_set_entry_mode(g_resident_data_base + 0x3F138, i, 2);
            }
        }
    }
}
int UpdateMissionSelectionMenu(void) {
 int result, changed;
 if (g_mission_menu_depth == 0) return -1;
 if (g_notice_owner != 0) return -1;
 if (D_001A8CFC_gp != 0) {
  menu_update_mission_select_enable();
  {
   int enabled = 0;
   switch (g_mission_select_enabled) {
    case 0: return -1;
    case 1:
     changed = 0;
     RefreshMissionMenuItems();
     if (g_pad_state.flags & 0x10) {
      g_mission_menu_flag = 1;
      g_pad_state.state = 2;
     } else if (g_mission_menu_flag != 0) {
      g_mission_menu_flag = 0;
      changed = 1;
     }
     circle_menu_position_label(g_resident_data_base + 0x3F138);
     enabled = g_mission_menu_flag;
     break;
    default: changed = 0; break;
   }
   circle_menu_set_enabled(g_resident_data_base + 0x3F138, enabled);
  }
  result = UpdateDirectionSelection(g_resident_data_base + 0x3C950, &g_pad_state);
  if (result >= 0 && table_find_last_used_entry(g_mission_menu_ids[result]) < 0) result = -1;
  if (changed) {
   menu_clear_field_150(D_001A8CFC_gp + 0x3C950);
   if (g_mission_menu_result < 0) g_mission_menu_result = result;
  }
  circle_menu_set_selection(g_resident_data_base + 0x3F138, result);
  return changed ? result : -1;
 }
 g_mission_menu_depth--;
 if (g_mission_menu_depth < 0) g_mission_menu_depth = 0;
 return 0;
}
