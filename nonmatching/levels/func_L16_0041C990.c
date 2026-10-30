/* 30 October 2026 recheck: -O2 -G8 -ffunction-sections, 412/412 bytes.
 * USA v1.01, v2.00 and PAL: 0/1 placements each, first mismatch +0x54.
 * Contrary to the earlier shorthand below, case 2 also keeps its entity pointer
 * in v0 where retail uses a0. A shared next-state local becomes movz; inverted
 * nested calls and an explicit state-two label tie the existing branch layout.
 * Reopen with a real state-selection/source-lifetime witness, not another
 * equivalent three-way spelling. This remains ordinary C, not ASM_FUNC.
 */
/* Mid worker 11 near miss (func_L16_0041C990).
   Profile: -O2 -G8 -ffunction-sections (file named -g8.c).
   Status: jump table, both loops and the gp/lui table accesses match; case 0's three-way selection of the next state lays out its branch tails differently (nop vs addiu in the b delay slot). */
#include "common.h"

#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)

extern char D_00189EA0[];
extern char *D_L16_001B2B1C;

extern void func_002A7750(char *, int, int);
extern int func_002ACBC8(char *, int);
extern int func_002A8508(int, int);

void func_L16_0041C990(char *obj) {
    int *p = FLD(obj, int *, 0x68);
    char *entry;
    int i;
    char *first;

    switch (FLD(obj, u8, 0x20)) {
    case 0:
        if (p[1] == -1) {
            if (p[2] != p[1]) {
                func_002A7750(obj, 2, -1);
            } else {
                func_002A7750(obj, 4, -1);
            }
        } else {
            func_002A7750(obj, 1, -1);
        }
        break;
    case 1:
        first = D_L16_001B2B1C + (p[0] << 8);
        if (first == 0 || FLD(first, u8, 0x20) == 0xFE || FLD(first, u8, 0x20) == 0xFD) {
            if (func_002ACBC8(D_00189EA0, p[1]) != 0) {
                for (i = 0; i < 8; i++) {
                    if (p[4 + i] != -1) {
                        entry = D_L16_001B2B1C + (p[4 + i] << 8);
                        if (FLD(entry, s16, 0xAA) == 0xEA3) {
                            FLD(FLD(entry, char *, 0x68), int, 0x24C) = 1;
                        } else {
                            FLD(entry, u8, 0xBC) = 1;
                        }
                    }
                }
                func_002A7750(obj, 4, -1);
            }
        }
        break;
    case 2:
        if (func_002A8508(p[2], -1) == 0) {
            for (i = 0; i < 8; i++) {
                if (p[4 + i] != -1) {
                    entry = D_L16_001B2B1C + (p[4] << 8);
                    if (FLD(entry, s16, 0xAA) == 0xEA3) {
                        FLD(FLD(entry, char *, 0x68), int, 0x24C) = 1;
                    } else {
                        FLD(entry, u8, 0xBC) = 1;
                    }
                }
            }
            func_002A7750(obj, 4, -1);
        }
        break;
    case 3:
    case 4:
        break;
    }
}
