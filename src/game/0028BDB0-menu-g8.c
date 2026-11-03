#include "common.h"

extern int D_001A8FBC SDATA(D_001A8FBC);
extern unsigned char D_00139568[];
extern int D_00139688[];
typedef struct { int active; unsigned char pad04[0x38]; unsigned short label; unsigned char pad3E[0x50]; unsigned short value; unsigned char pad90[0x50]; } MapClass;
extern MapClass D_00239BA0[];
extern unsigned char D_00189E20[];
typedef struct { int active; int selected; int handle; int busy; } MapMenuGlobals;
extern MapMenuGlobals D_001A8FB0 MACRO_ADDR;
extern int D_001A8FB0_gp SDATA(D_001A8FB0);
extern int func_0028FF50(char *);
extern int func_0028DDD8(char *);
extern int func_0028E260(void);
extern int func_0028B3D0(int, int, void *, void *, void *, int, int);
extern void func_0028B6C8(int, int);
extern void func_0028DF38(char *);
extern int func_0028DF68(void);
extern void func_0028BA50(void *);
extern void func_0028BA88(void *);

void func_0028E2A8(void)
{
    int selected;
    unsigned char *state;
    MapClass *record;
    int valid;
    unsigned short label;
    unsigned char *lookup;

    if (D_001A8FBC != 0) return;
    if (D_001A8FB0_gp != 0) return;
    selected = func_0028E260();
    lookup = D_00139568 + selected;
    record = (MapClass *)(*lookup * 0xE0 + (unsigned int)D_00239BA0);
    label = record->label;
    valid = record->active;
    if (selected != 0 && valid != 0) {
        D_001A8FB0.selected = selected;
        D_001A8FB0.handle = func_0028B3D0(0x10, label,
            func_0028DF38, func_0028FF50, func_0028DF68,
            (int)&D_00139688[selected],
            ((MapClass *)(*lookup * 0xE0 + (unsigned int)D_00239BA0))->value);
        return;
    }
    state = D_00189E20;
    if (state[0x22B4] == 2) {
        if (D_001A8FB0.handle != -1) {
            func_0028B6C8(D_001A8FB0.handle, 0);
            D_001A8FB0.handle = -1;
        }
        *(unsigned short *)(state + 0x1878) = func_0028B3D0(0x10, 0xFFFF,
            func_0028BA50, func_0028BA88, func_0028DDD8, (int)(state + 0x1874), 0xC8);
    } else if (D_001A8FB0.handle != -1) {
        func_0028B6C8(D_001A8FB0.handle, 0);
        D_001A8FB0.handle = -1;
    }
}
