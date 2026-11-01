#include "common.h"

/* Partial model and class layouts measured from the item fields. */
typedef struct { int group; int pad[3]; } UpgradeGroup;
typedef union {
    struct { char prefix[0x144]; UpgradeGroup rows[0];
} groups;
    struct { char prefix[0x140]; UpgradeGroup rows[0];
} slots;
    struct { char prefix[0x148]; UpgradeGroup rows[0];
} prices;
} UpgradeModel;
extern UpgradeModel D_L00_0022F7C0;
extern unsigned char D_001A7A80[] __attribute__((sda));
extern int D_L00_001A8E40[] __attribute__((sda));
extern unsigned char D_00139568[];
typedef struct { char prefix[8]; int name; char tail[0xE0-12]; } UpgradeInfo;
extern UpgradeInfo D_L00_00262570[];
extern char D_L00_001AD738[10];
extern char D_L00_001AD748[9];
extern char D_L00_001AD758[9];
extern int D_L00_001AD718 __attribute__((sda));
extern int D_L00_001AD71C;
extern int D_L00_001AD724;
extern int D_L00_001AD728 __attribute__((sda));
extern int D_L00_001AD72C;
extern int D_L00_001AD730 __attribute__((sda));
extern int D_L00_001AD734;
extern float D_L00_001B25E0;
extern int func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);
extern int func_0027FB40(int, int, unsigned long long, unsigned char *, int);
extern void func_002F9BC0(char *, int);
extern int func_0028E588(int, int);
extern int func_L00_002E9120(unsigned char *, int);
extern void func_0028EA58(int, int, int, int, int, unsigned int *);
extern int func_002B0D70(void);

void func_L00_00377580(void) {
    char first[256];
    char second[256];
    unsigned int colors[4];
    char *model = (char *)&D_L00_0022F7C0;
    int group = D_L00_0022F7C0.groups.rows[*(int *)(model + 0x80)].group;
    int slot = D_L00_0022F7C0.slots.rows[*(int *)(model + 0x80)].group;
    int handle;
    int width;
    if (((unsigned long)D_001A7A80[group] & ((1U << (slot * 2)) & 255UL)) != 0) return;
    if (group != 0) {
        func_00115DA8(first, D_L00_001AD738,
            (unsigned char *)func_00288FB8(D_L00_001A8E40[slot]),
            (unsigned char *)func_00288FB8(((UpgradeInfo *)((char *)D_L00_00262570 + D_00139568[D_L00_0022F7C0.groups.rows[*(int *)(model + 0x80)].group] * 224))->name));
        func_0027FB40(D_L00_001AD728, (int)((float)D_L00_001AD72C * D_L00_001B25E0 + 0.5f),
                      0x80F0F0F0ULL, (unsigned char *)first, -1);
    }
    func_002F9BC0(first, D_L00_0022F7C0.prices.rows[*(int *)(model + 0x80)].group);
    func_00115DA8(second, D_L00_001AD748, (unsigned char *)func_00288FB8(0x114E), first,
        (unsigned char *)func_00288FB8(0x3262));
    func_0027FB40(D_L00_001AD718, (int)((float)D_L00_001AD71C * D_L00_001B25E0 + 0.5f),
                  0x80F0F0F0ULL, (unsigned char *)second, -1);
    colors[0] = 0x60F0F0B0;
    colors[1] = 0x60F0F0B0;
    colors[2] = 0x60F0F0B0;
    colors[3] = 0x60F0F0B0;
    handle = func_0028E588(0xEAA2, 0);
    width = func_L00_002E9120((unsigned char *)second, -1);
    func_0028EA58(handle, D_L00_001AD718 + (width >> 1) + 4,
                  (int)((float)D_L00_001AD724 * D_L00_001B25E0 + 0.5f), 16,
                  (int)(D_L00_001B25E0 * 16.0f + 0.5f), colors);
    func_00115DA8(first, D_L00_001AD758, (unsigned char *)func_00288FB8(0x2F2D),
        func_002B0D70(), (unsigned char *)func_00288FB8(0x3262));
    func_0027FB40(D_L00_001AD730, (int)((float)D_L00_001AD734 * D_L00_001B25E0 + 0.5f),
                  0x80F0F0F0ULL, (unsigned char *)first, -1);
    handle = func_0028E588(0xEAA2, 0);
    width = func_L00_002E9120((unsigned char *)first, -1);
    func_0028EA58(handle, D_L00_001AD730 + (width >> 1) + 4,
                  (int)((float)D_L00_001AD734 * D_L00_001B25E0 + 0.5f), 16,
                  (int)(D_L00_001B25E0 * 16.0f + 0.5f), colors);
}
