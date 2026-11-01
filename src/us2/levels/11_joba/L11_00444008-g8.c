#include "include_asm.h"

extern unsigned char D_001395B8[0x100];
extern int D_001A7A08[2];
extern int D_001A79F8;
extern unsigned char D_001A7A60 __attribute__((sda));
extern int D_001A903C;
typedef struct {
    char pad0[0x22C8];
    int w22C8;
} L11_004427B8_Hero;
extern L11_004427B8_Hero D_00189E20;
extern int func_L11_0043E108(int);
extern int func_L11_00445D28(char *, int);
extern void func_00288308(int);
extern void func_002AD860(int);
extern int func_002A77E0(int);
extern int func_L02_003FCF08(int);
extern int func_L02_003FCDF8(int);
extern void func_US2_L00_0030D9F8(int);
extern int func_002E5E58(int, unsigned int, void *);
extern void func_US2_002B1880(int, int);
extern void func_0029B3E0(int, int);

/* Starts the next scene for a1 and counts the entry, as func_L02_003FCCA0 does in level 2. For
   a1 == 0 and a1 == 1 with no count yet it plays scene 1 or 3 and keeps the hero's word at
   +0x22C8; otherwise it takes scene func_002A77E0(2) + 0x1E, adds the two scores and starts
   func_US2_L00_0030D9F8(0x168). For a1 == 10
   with the once-only byte clear it sets it, starts func_002E5E58 and raises D_001A903C. */
void func_US2_L11_00444008(char *a0, int a1) {
    char *state = *(char **)(a0 + 0x68);
    int saved;
    int v;

    if (a1 == 0 && D_001395B8[func_L11_0043E108(0)] == 0) {
        saved = D_00189E20.w22C8;
        func_L11_00445D28(a0, 1);
        func_00288308(0x13);
        func_002AD860(0x13);
        D_00189E20.w22C8 = saved;
    } else if (a1 == 1 && D_001395B8[func_L11_0043E108(1)] == 0) {
        saved = D_00189E20.w22C8;
        func_L11_00445D28(a0, 3);
        func_00288308(0x33);
        D_00189E20.w22C8 = saved;
    } else {
        func_L11_00445D28(a0, func_002A77E0(2) + 0x1E);
        D_001A7A08[1] = D_001A7A08[1] + func_L02_003FCF08(a1);
        v = func_L02_003FCDF8(a1);
        *(int *)(state + 0x1E0) = v;
        D_001A79F8 = D_001A79F8 + v;
        func_US2_L00_0030D9F8(0x168);
    }
    if (a1 == 10 && D_001A7A60 == 0) {
        D_001A7A60 = 1;
        func_002E5E58(1, 0, 0);
        func_US2_002B1880(0x1233, -1);
        D_001A903C = 1;
    }
    D_001395B8[func_L11_0043E108(a1)] += 1;
    func_0029B3E0(0, -1);
}
