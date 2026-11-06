#include "common.h"

/* func_PAL_L05_00326B88, the PAL copy of func_0029B910: the same C, where the
 * menu offset 0x3F138 becomes 0x3F860 and the store of the item id is gone. */
extern int D_001A9AC8[4] __attribute__((sda));
extern char *D_001A8CFC MACRO_ADDR;
extern int func_002ED8A0(int);
extern void func_PAL_0033C8F8(char *, int, int);

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

extern MissionRecord D_00262940[];
extern MissionMenuItem D_00256418[];

void func_PAL_L05_00326B88(void) {
    int i;
    int *ids;
    if (D_001A8CFC != 0) {
        ids = D_001A9AC8;
        for (i = 0; i < 4; i++) {
            int idx = func_002ED8A0(ids[i]);
            if (idx >= 0) {
                D_00256418[i].second = D_00262940[idx].count;
                D_00256418[i].color = D_00262940[idx].flag >= 1 ? 0x6029A1FF : 0x60F0F0B0;
                func_PAL_0033C8F8(D_001A8CFC + 0x3F860, i, 0);
            } else {
                func_PAL_0033C8F8(D_001A8CFC + 0x3F860, i, 2);
            }
        }
    }
}
