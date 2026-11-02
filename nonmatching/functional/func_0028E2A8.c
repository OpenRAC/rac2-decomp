/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Best ordinary-C attempt, requalified on current master: 332 bytes against
   retail's 348 (0/28 USA v1.01 places, default -O2 -G8 -ffunction-sections).
   It reconstructs the selected-map setup and the mode-dependent cleanup, but
   the compiler's register allocation and instruction scheduling still differ. */
#include "include_asm.h"

extern int D_001A8FBC __attribute__((sda));
extern unsigned char D_00139568[];
extern unsigned char D_00139588[];
extern unsigned char D_00239BA0[];
extern unsigned char D_00189E20[];
extern int D_001A8FB8;
extern int D_001A8FB4;
extern int D_001A8FB0 __attribute__((sda));
extern char D_0028FF58[];
extern char D_0028DE18[];
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
    unsigned char *record;

    if (D_001A8FBC != 0) return;
    if (D_001A8FB0 != 0) return;
    selected = func_0028E260();
    record = D_00239BA0 + D_00139568[selected] * 0xE0;
    if (selected != 0 && *(int *)record != 0) {
        D_001A8FB4 = selected;
        D_001A8FB8 = func_0028B3D0(0x10, *(unsigned short *)(record + 0x3C),
            func_0028DF38, D_0028FF58, func_0028DF68,
            (int)(D_00139588 + selected * 4),
            *(unsigned short *)(D_00239BA0 + D_00139568[selected] * 0xE0 + 0x8E));
        return;
    }
    state = D_00189E20;
    if (state[0x22B4] == 2) {
        if (D_001A8FB8 != -1) {
            func_0028B6C8(D_001A8FB8, 0);
            D_001A8FB8 = -1;
        }
        *(unsigned short *)(state + 0x1878) = func_0028B3D0(0x10, 0xFFFF,
            func_0028BA50, func_0028BA88, D_0028DE18, (int)(state + 0x1874), 0xC8);
    } else if (D_001A8FB8 != -1) {
        func_0028B6C8(D_001A8FB8, 0);
        D_001A8FB8 = -1;
    }
}
