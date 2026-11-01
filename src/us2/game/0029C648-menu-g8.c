#include "include_asm.h"

#include "common.h"
extern int D_001A9A50 __attribute__((sda)), D_001A9A54 __attribute__((sda)), D_001A9A58 __attribute__((sda));
extern int D_001A9AD8 __attribute__((sda));
extern int D_001A9AC8[4] __attribute__((sda));
extern int D_001A8C64 MACRO_ADDR;
extern char *D_001A8CFC MACRO_ADDR;
extern char *D_001A8CFC_gp SDATA(D_001A8CFC);
typedef struct { char pad[0x1C0]; int flags; int pad2[2]; int state; } MenuInput;
extern MenuInput D_00138180;
extern void func_US2_0029C818(void), func_US2_0029C700(void);
extern void func_US2_0033B6D0(void *), func_US2_0033BA40(void *, int), func_US2_0033BA28(void *, int);
extern int func_00349190(void *, void *), func_002ED8A0(int);
extern void func_00349488(void *);

int func_US2_0029C8F0(void) {
 int result, changed;
 if (D_001A9A50 == 0) return -1;
 if (D_001A8C64 != 0) return -1;
 if (D_001A8CFC_gp != 0) {
  func_US2_0029C818();
  {
   int enabled = 0;
   switch (D_001A9A54) {
    case 0: return -1;
    case 1:
     changed = 0;
     func_US2_0029C700();
     if (D_00138180.flags & 0x10) {
      D_001A9AD8 = 1;
      D_00138180.state = 2;
     } else if (D_001A9AD8 != 0) {
      D_001A9AD8 = 0;
      changed = 1;
     }
     func_US2_0033B6D0(D_001A8CFC + 0x3F7B0);
     enabled = D_001A9AD8;
     break;
    default: changed = 0; break;
   }
   func_US2_0033BA40(D_001A8CFC + 0x3F7B0, enabled);
  }
  result = func_00349190(D_001A8CFC + 0x3CD48, &D_00138180);
  if (result >= 0 && func_002ED8A0(D_001A9AC8[result]) < 0) result = -1;
  if (changed) {
   func_00349488(D_001A8CFC_gp + 0x3CD48);
   if (D_001A9A58 < 0) D_001A9A58 = result;
  }
  func_US2_0033BA28(D_001A8CFC + 0x3F7B0, result);
  return changed ? result : -1;
 }
 D_001A9A50--;
 if (D_001A9A50 < 0) D_001A9A50 = 0;
 return 0;
}
