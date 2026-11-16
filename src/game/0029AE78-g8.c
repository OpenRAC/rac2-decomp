#include "names.h"
extern char *g_resident_data_base[] __attribute__((sda));
extern int g_mission_select_enabled __attribute__((sda));
extern char g_mission_menu_field __attribute__((sda));
extern char g_mission_circle_menu __attribute__((sda));
extern char g_mission_menu_items[];
extern int stub_empty_23(void), stub_empty_24(void);
extern void func_0029BCC8(void), RefreshMissionMenuItems(void);
extern void menu_set_field_144(void *, int);
extern void circle_menu_init_entries(void *,void *,void *);
extern void circle_menu_set_radius(void *,float);
extern void circle_menu_set_selection(void *,int);
/* Switches the mission select menu on or off when the setting changes, and builds the menu list when it turns on. */
void menu_update_mission_select_enable(void) {
 int enabled;
 if (g_resident_data_base[0] != 0) {
  enabled=0;
  if(stub_empty_23()) enabled=stub_empty_24()!=0;
  if(g_mission_select_enabled != enabled) {
   func_0029BCC8();
   g_mission_select_enabled=enabled;
   if(enabled==1) {
    menu_set_field_144(g_resident_data_base[0]+0x3C950,(int)&g_mission_menu_field);
    circle_menu_init_entries(g_resident_data_base[0]+0x3F138,&g_mission_circle_menu,g_mission_menu_items);
    circle_menu_set_radius(g_resident_data_base[0]+0x3F138,36.0f);
    circle_menu_set_selection(g_resident_data_base[0]+0x3F138,-1);
    RefreshMissionMenuItems();
   }
  }
 }
}
