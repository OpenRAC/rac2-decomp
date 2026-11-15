#include "include_asm.h"

#include "common.h"
extern int D_001A9A50 __attribute__((sda)), D_001A9A54 __attribute__((sda)), D_001A9A58 __attribute__((sda));
extern int D_001A9AD8 __attribute__((sda));
extern int D_001A9AC8[4] __attribute__((sda));
extern int g_notice_owner MACRO_ADDR;
extern char *D_001A8CFC MACRO_ADDR;
extern char *D_001A8CFC_gp SDATA(D_001A8CFC);
typedef struct { char pad[0x1C0]; int flags; int pad2[2]; int state; } MenuInput;
extern MenuInput g_pad_state;
extern void func_PAL_0029C3C0(void), func_PAL_0029C2A8(void);
extern void func_PAL_0033C5B0(void *), func_PAL_0033C920(void *, int), func_PAL_0033C908(void *, int);
extern int func_PAL_0034B358(void *, void *), table_find_last_used_entry(int);
extern void menu_clear_field_150(void *);

int func_PAL_0029C498(void) {
 int result, changed;
 if (D_001A9A50 == 0) return -1;
 if (g_notice_owner != 0) return -1;
 if (D_001A8CFC_gp != 0) {
  func_PAL_0029C3C0();
  {
   int enabled = 0;
   switch (D_001A9A54) {
    case 0: return -1;
    case 1:
     changed = 0;
     func_PAL_0029C2A8();
     if (g_pad_state.flags & 0x10) {
      D_001A9AD8 = 1;
      g_pad_state.state = 2;
     } else if (D_001A9AD8 != 0) {
      D_001A9AD8 = 0;
      changed = 1;
     }
     func_PAL_0033C5B0(D_001A8CFC + 0x3F860);
     enabled = D_001A9AD8;
     break;
    default: changed = 0; break;
   }
   func_PAL_0033C920(D_001A8CFC + 0x3F860, enabled);
  }
  result = func_PAL_0034B358(D_001A8CFC + 0x3CDF8, &g_pad_state);
  if (result >= 0 && table_find_last_used_entry(D_001A9AC8[result]) < 0) result = -1;
  if (changed) {
   menu_clear_field_150(D_001A8CFC_gp + 0x3CDF8);
   if (D_001A9A58 < 0) D_001A9A58 = result;
  }
  func_PAL_0033C908(D_001A8CFC + 0x3F860, result);
  return changed ? result : -1;
 }
 D_001A9A50--;
 if (D_001A9A50 < 0) D_001A9A50 = 0;
 return 0;
}
