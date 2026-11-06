/* func_US2_002FBCEC, the v2.00 boot copy of func_002FAE68 and the C of func_US2_L00_0037A5D0, where D_001A7A20
 * is a plain extern read with lui/lw. */
#include "include_asm.h"

/* Measured from func_002FAE68: the state it steps and the status block it tests. */
typedef struct { char pad[0x38]; int st; } CardPrompt;
typedef struct {
    char p0[0x8]; int f8;
    char p1[0x8]; int f14;
    char p2[0x4]; int f1C;
    char p3[0x88]; int fA8;
    char p4[0x8]; int fB4;
    char p5[0x4]; int fBC;
    char p6[0x9C]; int f15C;
    char p7[0x4]; int f164;
    int f168;
} CardStatus;
extern void *D_0026DBE0[];
extern CardPrompt D_0021F240;
extern CardStatus D_001393E0;
extern int D_001A7A20;
extern void func_002F88D8(char *);
extern void func_002FADB0(void);
extern int func_00288FB8(int);

/* func_US2_002FBCEC, the v2.00 copy of func_002FAE68: the same state machine, where the
 * prompts are looked up in the text table. */
void func_US2_002FBCEC(void) {
    {
    static void *volatile rc2_labels[] = {&&rc2_case_0, &&rc2_case_1, &&rc2_case_2, &&rc2_case_3, &&rc2_case_4, &&rc2_case_5, &&rc2_case_6};
    unsigned int rc2_selector = (unsigned int)(D_0021F240.st);
    if (rc2_selector > 6U) goto rc2_default;
goto *D_0026DBE0[rc2_selector];

    rc2_case_0:
    rc2_case_2:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0 && D_001393E0.f8 == 2) {
            if (D_001393E0.f14 != 0) {
                D_001393E0.f164 = 0x18;
                D_0021F240.st = 3;
                D_001393E0.f168 = 0;
                goto rc2_switch_end;
            }
        }
        if (D_0021F240.st != 0) {
            D_0021F240.st = 4;
        } else {
            D_0021F240.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_1:
    rc2_case_3:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (D_001393E0.f1C == 1) {
                    func_002F88D8((char *)func_00288FB8(0x313A));
                } else if (D_001393E0.f1C >= 3) {
                    func_002F88D8((char *)func_00288FB8(0x3138));
                } else {
                    func_002F88D8((char *)func_00288FB8(0x3139));
                }
            } else {
                func_002F88D8((char *)func_00288FB8(0x3137));
            }
            func_002FADB0();
            if (D_0021F240.st != 0) {
                D_0021F240.st = 4;
            } else {
                D_0021F240.st = 6;
            }
        }
        goto rc2_switch_end;
    rc2_case_4:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0 && D_001393E0.fA8 == 2 && D_001393E0.fB4 != 0) {
            D_001393E0.f164 = 0x18;
            D_001393E0.f168 = 1;
            D_0021F240.st = 5;
            goto rc2_switch_end;
        }
        D_0021F240.st = 6;
        goto rc2_switch_end;
    rc2_case_5:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (D_001393E0.fBC == 1) {
                    func_002F88D8((char *)func_00288FB8(0x313A));
                } else if (D_001393E0.fBC >= 3) {
                    func_002F88D8((char *)func_00288FB8(0x3138));
                } else {
                    func_002F88D8((char *)func_00288FB8(0x3139));
                }
            } else {
                func_002F88D8((char *)func_00288FB8(0x3137));
            }
            func_002FADB0();
            D_0021F240.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_6:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0) {
            if (D_001393E0.f1C == 0) {
                int a = D_001393E0.f8;
                if (a == 2 && D_001393E0.f14 != 0) {
                    D_0021F240.st = a;
                    goto rc2_switch_end;
                }
            }
            if (D_001393E0.fBC == 0 && D_001393E0.fA8 == 2 && D_001393E0.fB4 != 0) {
                D_0021F240.st = 4;
            }
        }
        goto rc2_switch_end;
    rc2_default:
        goto rc2_switch_end;

rc2_switch_end: ;
}
}
