/* Tier: sol-high (v1161), 29 October 2026, pinned upstream toolchain.
 * USA v1.01, -O2 -G0 -ffunction-sections: 1540/1540 bytes, 0/1 places.
 * Final check.py: first difference +0x17c. Frame and save slots now match retail
 * (0x50); code outside case 2's movie-list handling matches after relocations.
 * Starting from the related func_L01_00410AD0 reconstruction, moving noList = 0
 * to the loop bottom removes the spill, but leaves noList in t1 and clears it
 * in the loop-back branch slot. Retail clears s5 in the preheader, keeps ready
 * in s6, -1 in s7 and the queue high half in fp; this retains shift-one in fp.
 * Remaining differences: flag/constant allocation, mask scheduling, loop-head
 * alignment nop, and t2 vs t1 level copies. No linked build was run.
 * The natural loop-top clear gives 1548/1540, frame 0x60, spilled noList;
 * u8 noList is identical, s64 noList still spills. Loop-bottom clear here is
 * ordinary C and introduces no extra accesses or dependencies.
 * -fno-rerun-loop-opt gives 1536/1540 with the related for-loop source: it
 * removes the spill but retains the bitset base instead of the queue high half.
 * -fno-strength-reduce and -fno-move-all-movables do not resolve the spill.
 * See nonmatching/levels/func_L01_00410AD0.c for the previously measured
 * allocation-priority blocker. Reopen with a new source-lifetime hypothesis;
 * do not repeat the rejected redundant pre-test clear from that file's notes.
 * Opus G2, 1 November 2026: retail clears noList in the preheader, so the clear is at the loop top.
 * That with `1 << (dep & 31)` inline gives 1540 bytes, but loop.c then hoists the bitset base as well
 * and noList spills (frame 0x60). Retail hoists only the queue high half and -1. MACRO_ADDR, operand
 * order and the mask local do not change it; the mask local keeps the base in the loop and hoists 1.
 * All required declarations are included below.
 */
#include "common.h"
typedef struct { u8 pad[0x80]; f32 pos[4]; f32 rot[4]; u8 padA0[0x2294 - 0xA0]; s32 state; u8 pad2298[0x24CC - 0x2298]; s32 health; } InteractionPlayer;
extern InteractionPlayer D_00189E20;
extern s32 D_001A79F0[] __attribute__((sda));
extern void func_0029F338(void *);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002B38B8(u8 *);
extern s32 func_002ACBC8(void *, s32);
extern s32 func_00288AA0(u8 *, s32);
extern void func_0026FEB8(const char *, ...);
extern s32 func_00288BE8(u8 *);
extern void func_002F5CC8(void);
extern s32 func_002F5D10(void);
extern void func_L00_002B9D60(void *, void *, s32, s32);
extern void func_002AD7B8(s32);
extern void func_002AF0A8(s32);
extern void func_002A0430(u32);
extern void func_002DF3F8(void *, void *);
extern void func_00288CB0(s32, s32);
extern s32 func_0029B3E0(s32, s32);
extern u8 D_001A7BC8[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern u32 D_00139768[];
extern s32 D_L00_001A8F00[] __attribute__((sda));
extern s32 D_L00_001B19C8[] __attribute__((sda));
typedef struct { u8 pad[0x30]; f32 pos[4]; u8 pad40[0x30]; f32 dir[4]; } PathNode;
extern PathNode *D_L00_001B1F8C __attribute__((sda));
extern s16 **D_L00_0029FC60[];
extern u8 D_L00_001BEFC0[];
extern char D_L00_001B1210[];
extern char D_L00_002A2CC0[];

void func_L00_0040EAA0(u8 *obj)
{
    u8 *rec = *(u8 **)(obj + 0x68);
    s32 i;
    s32 dep;
    s32 ready;
    s32 noList;
    s32 changed;
    u32 mask;

    switch (obj[0x20]) {
    case 0:
        if (((s8 *)rec)[9] != -1 && D_001A7BC8[((s8 *)rec)[9]] != 0) {
            func_0029F338(obj);
            return;
        }
        if (obj[0xB0] != 255 && (D_0019B2E8[obj[0xB0] + (D_001A79F0[0] << 4)] & 0x80)) {
            func_0029F338(obj);
            return;
        }
        func_002A7750(obj, 1, -1);
    case 1:
        if (!rec[10] && !func_002B38B8(obj) && !obj[0xBC])
            return;
        rec[10] = 1;
        func_002A7750(obj, 2, -1);
    case 2:
        if (!rec[10]) {
            func_002A7750(obj, 1, -1);
            return;
        }
        if (D_00189E20.state == 28 || D_00189E20.health <= 0 || D_L00_001A8F00[0])
            return;
        if (*(s32 *)rec != -1 && !func_002ACBC8(D_00189E20.pos, *(s32 *)rec))
            return;
        ready = 1;
        noList = 1;
        if (D_L00_0029FC60[D_001A79F0[0]] && D_L00_0029FC60[D_001A79F0[0]][rec[8]]) {
            for (i = 0; D_L00_0029FC60[D_001A79F0[0]][rec[8]][i] != -1; i++) {
                dep = D_L00_0029FC60[D_001A79F0[0]][rec[8]][i];
                if (rec[13] || (mask = 1 << (dep & 31), !(D_00139768[(u32)dep >> 2] & mask))) {
                    if (!func_00288AA0(D_L00_001BEFC0, dep) && i == 0) {
                        func_0026FEB8(D_L00_002A2CC0, *(s16 *)(obj + 0xAA), *(s16 *)(obj + 0xB2),
                                      D_001A79F0[0], rec[8], dep);
                        return;
                    }
                    ready = 0;
                }
                noList = 0;
            }
        }
        if (noList)
            func_0026FEB8(D_L00_001B1210, D_001A79F0[0], rec[8]);
        if (ready) {
            rec[15] = 0;
            func_002A7750(obj, 4, -1);
        } else {
            rec[15] = 1;
            func_00288BE8(D_L00_001BEFC0);
            if (D_L00_001B19C8[0] < 5 || (D_001A79F0[0] == 6 && rec[8] == 0))
                func_002F5CC8();
            func_002A7750(obj, 3, -1);
        }
        return;
    case 3:
        if (!func_002F5D10()) {
            if (*(s32 *)(rec + 4) != -1) {
                func_L00_002B9D60(D_L00_001B1F8C[*(s32 *)(rec + 4)].pos,
                                  D_L00_001B1F8C[*(s32 *)(rec + 4)].dir, 0, 1);
            }
            func_002A7750(obj, 4, -1);
        }
        if (D_001A79F0[0] || ((s8 *)rec)[9] == -1 || func_002F5D10())
            return;
        changed = 0;
        if (((s8 *)rec)[9] != -1) {
            func_002AD7B8(((s8 *)rec)[9]);
            if (((s8 *)rec)[9] != 24)
                func_002AF0A8(((s8 *)rec)[9]);
            changed = 1;
        }
        if (obj[0xB0] != 255 && !(D_0019B2E8[obj[0xB0] + (D_001A79F0[0] << 4)] & 0x80)) {
            changed = 1;
            func_002A0430(obj[0xB0]);
        }
        if (((s8 *)rec)[11] != 0) {
            if (*(u32 *)(rec + 12) & 0xFFFF0000) {
                if (*(s32 *)(rec + 4) != -1) {
                    func_002DF3F8(D_L00_001B1F8C[*(s32 *)(rec + 4)].pos,
                                  D_L00_001B1F8C[*(s32 *)(rec + 4)].dir);
                } else {
                    func_002DF3F8(obj + 0x10, obj + 0xF0);
                }
            }
        }
        if (((s8 *)rec)[12] != -1) {
            func_00288CB0(((s8 *)rec)[12], 1);
            return;
        }
        if (changed || rec[15])
            func_0029B3E0(0, -1);
        return;
    case 4: {
        s32 saved = 0;
        if (((s8 *)rec)[9] != -1) {
            func_002AD7B8(((s8 *)rec)[9]);
            if (((s8 *)rec)[9] != 24)
                func_002AF0A8(((s8 *)rec)[9]);
            saved = 1;
        }
        if (obj[0xB0] != 255 && !(D_0019B2E8[obj[0xB0] + (D_001A79F0[0] << 4)] & 0x80)) {
            saved = 1;
            func_002A0430(obj[0xB0]);
        }
        if (((s8 *)rec)[11] > 0) {
            if (*(u32 *)(rec + 12) & 0xFFFF0000) {
                if (*(s32 *)(rec + 4) != -1) {
                    func_002DF3F8(D_L00_001B1F8C[*(s32 *)(rec + 4)].pos,
                                  D_L00_001B1F8C[*(s32 *)(rec + 4)].dir);
                } else {
                    func_002DF3F8(D_00189E20.pos, D_00189E20.rot);
                }
            }
        }
        if (((s8 *)rec)[12] != -1)
            func_00288CB0(((s8 *)rec)[12], 1);
        else if ((saved || rec[15]) && ((s8 *)rec)[11] != -1)
            func_0029B3E0(0, -1);
        func_0029F338(obj);
        return;
    }
    }
}
