#include "common.h"

/* Update the four-mission selection menu and return a completed selection.
 * The four table entries are also read by func_0029B910's bounded loop. */
extern int D_001A9A50 __attribute__((sda)), D_001A9A54 __attribute__((sda)), D_001A9A58 __attribute__((sda));
extern int D_001A9AD8 __attribute__((sda));
extern int D_001A9AC8[4] __attribute__((sda));
extern int D_001A8C64 MACRO_ADDR;
extern char *D_001A8CFC MACRO_ADDR;
extern char *D_001A8CFC_gp SDATA(D_001A8CFC);
typedef struct { char pad[0x1C0]; int flags; int pad2[2]; int state; } MenuInput;
extern MenuInput D_00138180;
extern void func_0029BA58(void), func_0029B910(void);
extern void func_0033A688(void *), func_0033A9F8(void *, int), func_0033A9E0(void *, int);
extern int func_00349190(void *, void *), func_002ED8A0(int);
extern void func_00349488(void *);
extern void func_0033A9D0(char *, int, int);

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

extern MissionRecord D_00262940[];
extern MissionMenuItem D_00256418[];

/* Refresh the four mission menu items from the mission IDs in D_001A9AC8:
 * a known mission's item gets its count, id and color and is passed to
 * func_0033A9D0 with 0, an unknown one with 2. */
void func_0029B910(void) {
    int i;
    int *ids;
    if (D_001A8CFC != 0) {
        ids = D_001A9AC8;
        for (i = 0; i < 4; i++) {
            int idx = func_002ED8A0(ids[i]);
            if (idx >= 0) {
                D_00256418[i].second = D_00262940[idx].count;
                D_00256418[i].id = D_00262940[idx].level;
                D_00256418[i].color = D_00262940[idx].flag >= 1 ? 0x6029A1FF : 0x60F0F0B0;
                func_0033A9D0(D_001A8CFC + 0x3F138, i, 0);
            } else {
                func_0033A9D0(D_001A8CFC + 0x3F138, i, 2);
            }
        }
    }
}
int func_0029BB30(void) {
 int result, changed;
 if (D_001A9A50 == 0) return -1;
 if (D_001A8C64 != 0) return -1;
 if (D_001A8CFC_gp != 0) {
  func_0029BA58();
  {
   int enabled = 0;
   switch (D_001A9A54) {
    case 0: return -1;
    case 1:
     changed = 0;
     func_0029B910();
     if (D_00138180.flags & 0x10) {
      D_001A9AD8 = 1;
      D_00138180.state = 2;
     } else if (D_001A9AD8 != 0) {
      D_001A9AD8 = 0;
      changed = 1;
     }
     func_0033A688(D_001A8CFC + 0x3F138);
     enabled = D_001A9AD8;
     break;
    default: changed = 0; break;
   }
   func_0033A9F8(D_001A8CFC + 0x3F138, enabled);
  }
  result = func_00349190(D_001A8CFC + 0x3C950, &D_00138180);
  if (result >= 0 && func_002ED8A0(D_001A9AC8[result]) < 0) result = -1;
  if (changed) {
   func_00349488(D_001A8CFC_gp + 0x3C950);
   if (D_001A9A58 < 0) D_001A9A58 = result;
  }
  func_0033A9E0(D_001A8CFC + 0x3F138, result);
  return changed ? result : -1;
 }
 D_001A9A50--;
 if (D_001A9A50 < 0) D_001A9A50 = 0;
 return 0;
}
