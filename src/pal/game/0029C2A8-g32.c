#include "common.h"

/* func_PAL_0029C2A8, PAL's func_0029B910: the same C, where the menu offset
 * 0x3F138 becomes 0x3F860 and the store of the item id is gone. */
extern int g_mission_menu_ids[4] __attribute__((sda));
extern char *g_resident_data_base MACRO_ADDR;
extern int table_find_last_used_entry(int);
extern void circle_menu_set_entry_mode_pal(char *, int, int);

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

/* Item of the mission selection menu (0x18 bytes). */
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

void RefreshMissionMenuItems_pal(void) {
    int i;
    int *ids;
    if (g_resident_data_base != 0) {
        ids = g_mission_menu_ids;
        for (i = 0; i < 4; i++) {
            int idx = table_find_last_used_entry(ids[i]);
            if (idx >= 0) {
                g_mission_menu_items[i].second = g_mission_records[idx].count;
                g_mission_menu_items[i].color = g_mission_records[idx].flag >= 1 ? 0x6029A1FF : 0x60F0F0B0;
                circle_menu_set_entry_mode_pal(g_resident_data_base + 0x3F860, i, 0);
            } else {
                circle_menu_set_entry_mode_pal(g_resident_data_base + 0x3F860, i, 2);
            }
        }
    }
}
