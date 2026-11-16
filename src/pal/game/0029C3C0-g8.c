#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern int g_mission_select_enabled __attribute__((sda));
extern char g_mission_menu_field __attribute__((sda));
extern char g_mission_circle_menu __attribute__((sda));
extern char g_mission_menu_items[];
extern int level_is_mode_in_set(void), level_run_mode_update_zero(void);
extern void func_0029BCC8(void), RefreshMissionMenuItems_pal(void);
extern void menu_set_field_144(void *, int);
extern void circle_menu_init_entries_pal(void *,void *,void *);
extern void circle_menu_set_radius_pal(void *,float);
extern void circle_menu_set_selection_pal(void *,int);

/* Turns the mission select menu on or off to match the current mode, setting up the circle menu when it turns on. */
void menu_update_mission_select_enable_pal(void) {
 int enabled;
 if (g_resident_data_base[0] != 0) {
  enabled=0;
  if(level_is_mode_in_set()) enabled=level_run_mode_update_zero()!=0;
  if(g_mission_select_enabled != enabled) {
   func_0029BCC8();
   g_mission_select_enabled=enabled;
   if(enabled==1) {
    menu_set_field_144(g_resident_data_base[0]+0x3CDF8,(int)&g_mission_menu_field);
    circle_menu_init_entries_pal(g_resident_data_base[0]+0x3F860,&g_mission_circle_menu,g_mission_menu_items);
    circle_menu_set_radius_pal(g_resident_data_base[0]+0x3F860,36.0f);
    circle_menu_set_selection_pal(g_resident_data_base[0]+0x3F860,-1);
    RefreshMissionMenuItems_pal();
   }
  }
 }
}
