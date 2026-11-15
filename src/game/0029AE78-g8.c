#include "names.h"
extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001A9A54 __attribute__((sda));
extern char D_001A9A60 __attribute__((sda));
extern char D_001A9AB8 __attribute__((sda));
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
 if (D_001A8CFC[0] != 0) {
  enabled=0;
  if(stub_empty_23()) enabled=stub_empty_24()!=0;
  if(D_001A9A54 != enabled) {
   func_0029BCC8();
   D_001A9A54=enabled;
   if(enabled==1) {
    menu_set_field_144(D_001A8CFC[0]+0x3C950,(int)&D_001A9A60);
    circle_menu_init_entries(D_001A8CFC[0]+0x3F138,&D_001A9AB8,g_mission_menu_items);
    circle_menu_set_radius(D_001A8CFC[0]+0x3F138,36.0f);
    circle_menu_set_selection(D_001A8CFC[0]+0x3F138,-1);
    RefreshMissionMenuItems();
   }
  }
 }
}
