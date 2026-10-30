/* Complete C near miss; not linked and no matching credit.
 * 2026-10-30: game -O2 -G8 -ffunction-sections.
 * us: 0/4; us2: 0/4; pal: absent.
 * 1200/1204 bytes; frame 0x40. Full constructor state, all table/flag selections, paired factory
 * results, conditional flag reload and signed kind values are retained. Factory handles/pointers
 * and actual FP scale are kept. Initializer/store scheduling and live factory-result priorities
 * differ.
 * Reopen: Independent constructor result/state lifetime witness.
 */
#include "common.h"
extern void func_L05_00418200(void *, int);
extern void func_00282C88(void *);
extern u8 *func_L05_0041C708(void *, void *, int, float);
extern u8 *func_L05_00432080(void *, float);
extern int func_002ED8A0(int);
extern int func_L05_0037AC00(void), func_L05_0037AC40(void);
extern int func_00282948(void *);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L05_00418288(void *);
extern void func_L00_004450C0(void *);
extern u32 D_001A7AF0;
extern u32 D_001A7AF0_gp SDATA(D_001A7AF0);
extern void *D_0018B650;
extern char D_L05_001B34F0[], D_L05_001B3510[];
extern int D_L05_001B3500;
extern s16 D_L05_001A8F70[], D_L05_001A8F78[], D_L05_001A8F80[];
extern s16 D_L05_001A8F88[], D_L05_001A8F90[], D_L05_001A8F98[], D_L05_001A8FA0[];

void func_L05_00417D48(u8 *actor)
{
    u8 *state = *(u8 **)(actor + 0x68);
    u8 *first, *second;
    int kind;
    u32 flags;
    int mode = actor[0x20];
    switch (mode) {
    case 0:
        *(int *)(state + 0x270) = -1;
        *(int *)(state + 0x30) = -1;
        *(int *)(state + 0x260) = 1;
        *(int *)(state + 0x264) = 14400;
        *(int *)(state + 0) = 0;
        *(int *)(state + 4) = 0;
        *(s16 *)(state + 8) = 0;
        *(s16 *)(state + 10) = 0;
        *(int *)(state + 0x20C) = 0;
        *(int *)(state + 0x210) = 0;
        *(int *)(state + 0x14) = 0;
        *(int *)(state + 0x18) = 0;
        *(int *)(state + 0x1C) = 0;
        *(int *)(state + 0x34) = 0;
        *(int *)(state + 0x38) = 0;
        *(int *)(state + 0x3C) = 0;
        *(int *)(state + 0x268) = 0;
        *(int *)(state + 0x26C) = 0;
        *(int *)(state + 0x27C) = 0;
        actor[0x20] = 1;
        *(u16 *)(actor + 0x34) |= 0x100;
        func_L05_00418200(actor, 1);
        func_00282C88(D_L05_001B34F0);
        D_0018B650 = actor;
        flags = D_001A7AF0;
        D_L05_001B3500 = 0;
        *(u16 *)(actor + 0x34) |= 0x41;
        first = func_L05_0041C708(actor, 0, D_L05_001A8F70[flags & 3], 0.05f);
        *(u8 **)(state + 0x40) = first;
        if (first != 0) *(int *)(first + 0x98) = 0;
        kind = D_L05_001A8F78[(D_001A7AF0 >> 2) & 3];
        first = func_L05_0041C708(actor, 0, kind, 0.05f);
        *(u8 **)(state + 0x44) = first;
        second = func_L05_0041C708(actor, (void *)1, kind, 0.05f);
        *(u8 **)(state + 0x48) = second;
        if (first != 0) *(int *)(first + 0x98) = 0;
        if (second != 0) *(int *)(second + 0x98) = 0;
        first = func_L05_0041C708(actor, 0, D_L05_001A8F80[(D_001A7AF0 >> 4) & 3], 0.05f);
        *(u8 **)(state + 0x4C) = first;
        if (first != 0) *(int *)(first + 0x98) = 0;
        *(u8 **)(state + 0x50) = func_L05_00432080(actor, 0.05f);
        kind = D_L05_001A8F88[(D_001A7AF0 >> 6) & 1];
        first = func_L05_0041C708(actor, 0, kind, 0.05f);
        *(u8 **)(state + 0xAC) = first;
        second = func_L05_0041C708(actor, (void *)1, kind, 0.05f);
        *(u8 **)(state + 0x1F0) = second;
        if (first != 0) *(int *)(first + 0x98) = 0;
        if (second != 0) *(int *)(second + 0x98) = 0;
        kind = D_L05_001A8F98[(D_001A7AF0 >> 9) & 1];
        first = func_L05_0041C708(actor, 0, kind, 0.05f);
        *(u8 **)(state + 0x1F4) = first;
        second = func_L05_0041C708(actor, (void *)1, kind, 0.05f);
        *(u8 **)(state + 0x1F8) = second;
        if (first != 0) *(int *)(first + 0x98) = 0;
        if (second != 0) *(int *)(second + 0x98) = 0;
        flags = D_001A7AF0_gp;
        if (func_002ED8A0(3) != 0) {
            kind = D_L05_001A8F90[(flags >> 7) & 3];
            if (kind != 0) {
                first = func_L05_0041C708(actor, 0, kind, 0.05f);
                *(u8 **)(state + 0x1FC) = first;
                second = func_L05_0041C708(actor, (void *)1, kind, 0.05f);
                *(u8 **)(state + 0x200) = second;
                if (first != 0) *(int *)(first + 0x98) = 0;
                if (second != 0) *(int *)(second + 0x98) = 0;
                flags = D_001A7AF0;
            }
        } else {
            flags = D_001A7AF0;
        }
        kind = D_L05_001A8FA0[(flags >> 10) & 3];
        first = func_L05_0041C708(actor, 0, kind, 0.05f);
        *(u8 **)(state + 0x204) = first;
        second = func_L05_0041C708(actor, (void *)1, kind, 0.05f);
        *(u8 **)(state + 0x208) = second;
        if (first != 0) *(int *)(first + 0x98) = 0;
        if (second != 0) *(int *)(second + 0x98) = 0;
        if (func_002ED8A0(4) != -1) {
            first = func_L05_0041C708(actor, 0, 0x10E2, 0.05f);
            *(u8 **)(state + 0x274) = first;
            if (first != 0) *(int *)(first + 0x98) = 0;
        }
        if (func_002ED8A0(5) != -1) {
            first = func_L05_0041C708(actor, 0, 0x10E4, 0.05f);
            *(u8 **)(state + 0x278) = first;
            if (first != 0) *(int *)(first + 0x98) = 0;
        }
        *(int *)(state + 0x58) = 70;
        *(int *)(state + 0x54) = 60;
        *(int *)(state + 0xA0) = 0;
        *(int *)(state + 0x5C) = 0;
        return;
    case 1:
        kind = func_L05_0037AC00();
        if (kind < func_L05_0037AC40()) *(int *)(state + 0x260) = mode;
        if (*(int *)(state + 0x260) != 0 && func_00282948(state + 0x264) != 0)
            *(int *)(state + 0x268) = mode;
        if (func_002E59B0(actor, *(int *)(state + 0x30)) == 0)
            *(int *)(state + 0x30) = func_002E5CF8(0, 4, actor);
        func_L05_00418288(actor);
        qcopy(D_L05_001B3510, actor + 0x10);
        func_L00_004450C0(actor);
        break;
    }
}
