#include "include_asm.h"
#include "names.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001A9A54 __attribute__((sda));
extern char D_001A9A60 __attribute__((sda));
extern char D_001A9AB8 __attribute__((sda));
extern char g_mission_menu_items[];
extern int level_is_mode_in_set(void), level_run_mode_update_zero(void);
extern void func_0029BCC8(void), func_PAL_0029C2A8(void);
extern void menu_set_field_144(void *, int);
extern void func_PAL_0033C928(void *,void *,void *);
extern void func_PAL_0033C8F0(void *,float);
extern void func_PAL_0033C908(void *,int);

void func_PAL_0029C3C0(void) {
 int enabled;
 if (D_001A8CFC[0] != 0) {
  enabled=0;
  if(level_is_mode_in_set()) enabled=level_run_mode_update_zero()!=0;
  if(D_001A9A54 != enabled) {
   func_0029BCC8();
   D_001A9A54=enabled;
   if(enabled==1) {
    menu_set_field_144(D_001A8CFC[0]+0x3CDF8,(int)&D_001A9A60);
    func_PAL_0033C928(D_001A8CFC[0]+0x3F860,&D_001A9AB8,g_mission_menu_items);
    func_PAL_0033C8F0(D_001A8CFC[0]+0x3F860,36.0f);
    func_PAL_0033C908(D_001A8CFC[0]+0x3F860,-1);
    func_PAL_0029C2A8();
   }
  }
 }
}
