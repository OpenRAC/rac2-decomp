/* func_PAL_L08_0042BE14, the PAL copy of func_L08_00426730: the same C at 50 Hz. Both func_002A7820
 * results are scaled by ((s32)(x) * 5 + 2) / 6, with their arguments unchanged; 240 becomes 200,
 * 120 becomes 100, 115 becomes 96, 90 becomes 75, 38 becomes 32; floats 0.012f, 0.006f, 0.64000005f,
 * 0.020000001f, 0.024434613f. Callees renamed to their PAL rows. */
#include "common.h"
#define FIELD(p, type, off) (*(type *)((p) + (off)))
extern int D_L08_001B29DC __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern unsigned char D_0019B4A8[];
extern char D_L08_001B9B00[];
extern struct { char pad[0x160]; float amount; int pad164; int timer; int phase; } D_L08_001B99C0;
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021DE80;
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021EAF0;
extern int func_002ACD38(void *);
extern void func_0029F338(void *);
extern float func_00282E80(void *, void *);
extern void func_PAL_L08_0042B190(char *);
extern void func_PAL_L08_0042B610(char *);
extern int func_002A77E0(int);
extern int func_L08_0032F898(char *, char *, float, float, int, int, int, int);
extern int func_L04_00343498(char *, float);
extern int func_L08_004254D0(int);
extern int func_L08_00425518(int);
extern void func_002A7470(char *, int, int, int);
extern void func_002A7750(char *, int, int);
extern int func_002B3868(char *);
extern void func_002E5CF8(int, int, char *);
extern float func_002AA548(void *, float, void *, float, float, float);
extern void func_PAL_L08_0042A6A0(char *, void *, int, float, float, float, float, float, float);
extern void func_L08_004257A0(char *);
extern int func_001163B0(void);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A7820(int, int);
extern float func_00283248(float, float);
extern int func_PAL_L08_0042B6D0(char *, float, float, int, float, float, float);
extern void func_L08_004258D0(char *);
extern int func_00282978(void *);
extern float func_00282DF0(void *);
extern int func_L08_00429238(char *, int, int);
extern float func_00283C80(float, float);
extern float func_00283B98(float, float);
extern void func_L08_004262C0(char *);
extern void func_L08_00424ED0(char *);
extern int func_L08_00429350(char *);
extern int func_002B1C20(char *, void *);
extern char *func_0029EFD0(int);
extern void func_002A0F48(char *);
extern void func_002AB650(char *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_L08_00424F40(char *);
extern void func_002A6C58(char *, int, int);
extern void func_PAL_L08_0042AC50(char *);
extern void func_L08_003D3928(char *, void *);

/* Per-frame state machine of a level-08 moby: wait for its trigger, rise above and sink
   below the height at +0x1C4, patrol and attack, recover
   from a hit, and on death spawn a replacement moby and clear its saved flag bits.
   Case 0 of the patrol switch repeats case 4's attack check; jump2 cross-jumps them. */
void func_PAL_L08_0042BE14(char *actor) {
    char *p;
    float local[4] __attribute__((aligned(16)));
    float local2[4] __attribute__((aligned(16)));
    int ready;
    int flags;
    float angle;
    if (!func_002ACD38(actor + 0x10)) return;
    p = FIELD(actor, char *, 0x68);
    if (FIELD(actor, u8, 0x20) == 0) {
        u16 id = FIELD(actor, u16, 0xB2);
        int bits = D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
        if ((id & 1) ? (((bits >> 4) & 7) != 0) : ((bits & 7) != 0)) {
            func_0029F338(actor);
            return;
        }
        func_PAL_L08_0042B190(actor);
    }
    if (func_00282E80(actor + 0x10, D_L08_001B9B00) > (float)FIELD(actor, u8, 0x30)) return;
    func_PAL_L08_0042B610(actor);
    switch (FIELD(actor, u8, 0x20)) {
    case 0: break;
    case 1: {
        int condition;
        ready = 0;
        switch (FIELD(p, u8, 0x20C)) {
        case 0:
        case 1:
            if (!func_002A77E0(7)) {
                func_L08_0032F898(actor, p + 0x120, (float)FIELD(actor, s16, 0x32), 0.0f,
                    FIELD(p, int, 0x1D0), -1, FIELD(p, int, 0x1D4), -1);
                if (FIELD(p, int, 0x164) != 2)
                    condition = ~func_L04_00343498(actor, (float)FIELD(actor, s16, 0x32));
                else break;
                goto ready_nonzero;
            }
            break;
        case 2:
            if (FIELD(actor, u8, 0xBC)) {
                FIELD(actor, u8, 0xBC) = 0;
                ready = 1;
            }
            break;
        case 3: ready = func_L08_004254D0(FIELD(p, int, 0x1EC)) != 0; break;
        case 5:
            condition = func_L08_00425518(FIELD(p, int, 0x1E8));
ready_nonzero:
            ready = condition != 0;
            break;
        }
        if (FIELD(actor, u8, 0xBC) & 2) {
            FIELD(actor, u8, 0xBC) = 0;
            ready = 1;
        }
        if (ready && func_L04_00343498(actor, (float)FIELD(actor, s16, 0x32)) != -1) {
            FIELD(actor, u8, 0x30) = FIELD(p, u8, 0x20E);
            qzero(p + 0x190);
            if (FIELD(actor, u8, 0x43) != 1) func_002A7470(actor, 1, 0, 10);
            FIELD(actor, u8, 0x31) = 1;
            FIELD(actor, u16, 0x34) &= 0xFFFE;
            func_002A7750(actor, 2, -1);
            D_L08_001B99C0.amount = 0.25f;
            D_L08_001B99C0.timer = 32;
            D_L08_001B99C0.phase = 0;
            if (FIELD(p, char *, 0x22C)) {
                FIELD(FIELD(p, char *, 0x22C), u8, 0xBC) = 1;
                FIELD(p, char *, 0x22C) = 0;
            }
        }
        break;
    }
    case 2: {
        float height;
        if (func_002B3868(actor)) func_002E5CF8(0, 0, actor);
        func_002AA548(actor + 0x18, FIELD(p, float, 0x1C8), p + 0x198,
            0.012f, 0.006f, 0.64000005f);
        height = FIELD(p, float, 0x1C4);
        if (FIELD(actor, float, 0x18) < height + 1.5f) {
            qcopy(local, actor + 0x10);
            local[2] = height;
            func_PAL_L08_0042A6A0(actor, local, 8, 10.0f, 4.0f, 4.0f, 0.0f, 0.25f, 3.5f);
        }
        if (FIELD(actor, u8, 0x60) & 2) {
            FIELD(actor, int, 0x98) = FIELD(FIELD(actor, char *, 0x24), int, 0x10);
            FIELD(actor, u16, 0x34) |= 0x1000;
            func_L08_004257A0(actor);
            if (FIELD(actor, u8, 0x43) != (func_001163B0() & 1) + 4)
                func_002A7470(actor, (func_001163B0() & 1) | 4, 0, 10);
            func_002A7750(actor, 4, 0);
        }
        break;
    }
    case 3: {
        float height;
        func_002AA548(actor + 0x18, FIELD(p, float, 0x1C4) - 1.5f, p + 0x198,
            0.012f, 0.006f, 0.64000005f);
        func_00282CF0(local, p + 0x170, actor + 0x10);
        func_00282D30(local, local, 0.025f);
        local[2] = 0.0f;
        func_00282CC0(actor + 0x10, actor + 0x10, local);
        height = FIELD(p, float, 0x1C4);
        if (FIELD(actor, float, 0x18) < height + 1.5f) {
            qcopy(local2, actor + 0x10);
            local2[2] = height;
            func_PAL_L08_0042A6A0(actor, local2, 8, 10.0f, 4.0f, 4.0f, 0.0f, 0.25f, 3.5f);
        }
        if (FIELD(actor, float, 0x18) < FIELD(p, float, 0x1C4) - 1.4f && !FIELD(actor, u8, 0x42)) {
            func_PAL_L08_0042A6A0(actor, actor + 0x10, 8, 10.0f, 4.0f, 2.0f, 0.0f, 0.25f, 3.5f);
            FIELD(actor, int, 0x98) = 0;
            FIELD(actor, u16, 0x34) &= 0xEFFF;
            FIELD(actor, float, 0x18) = FIELD(p, float, 0x1C4);
            if (FIELD(actor, u8, 0x43)) func_002A7470(actor, 0, 0, 2);
            func_002A7750(actor, 1, -1);
            FIELD(actor, u8, 0x30) = FIELD(p, u8, 0x20F);
        }
        break;
    }
    case 4:
        if (!func_002A77E0(7))
            func_L08_0032F898(actor, p + 0x120, (float)FIELD(actor, s16, 0x32), 60.0f,
                FIELD(p, int, 0x1D8), FIELD(p, int, 0x1E0), FIELD(p, int, 0x1DC), -1);
        if (func_00282E80(actor + 0x10, p + 0x120) < 8.0f) FIELD(p, s16, 0x1B8) = 100;
        switch (FIELD(actor, u8, 0x95)) {
        case 1:
            if (!FIELD(p, s16, 0x1B0)) {
                u16 timer;
                FIELD(p, s16, 0x1B0) = ((s32)func_002A7820(240, 480) * 5 + 2) / 6;
                if (FIELD(actor, u8, 0x43) != 6) func_002A7470(actor, 6, 0, func_002A7820(15, 30));
                timer = FIELD(actor, u16, 0x96);
                func_002A7750(actor, 4, 0);
                FIELD(actor, u16, 0x96) = timer;
            }
            if (FIELD(p, int, 0x164) != 2 && !FIELD(p, s16, 0x1BC)) {
                if (FIELD(actor, u8, 0x43) != 6) func_002A7470(actor, 6, 0, func_002A7820(15, 30));
                FIELD(actor, u8, 0x30) = 255;
                func_002A7750(actor, 4, 2);
            }
            break;
        case 0:
            if (func_PAL_L08_0042B6D0(actor, 5.5f, 5.5f, 1,
                func_00283248(FIELD(p, float, 0x120) - FIELD(actor, float, 0x10),
                             FIELD(p, float, 0x124) - FIELD(actor, float, 0x14)), 0.0f, 0.0f)) FIELD(p, s16, 0x1B0) = 0;
            if (!FIELD(p, s16, 0x1B0)) {
                if (FIELD(actor, u16, 0x96) < 60) {
                    u16 timer;
                    func_L08_004257A0(actor);
                    FIELD(p, s16, 0x1B0) = ((s32)func_002A7820(90, 180) * 5 + 2) / 6;
                    if (FIELD(actor, u8, 0x43) != (func_001163B0() & 1) + 2)
                        func_002A7470(actor, (func_001163B0() & 1) | 2, 0, 30);
                    timer = FIELD(actor, u16, 0x96);
                    func_002A7750(actor, 4, 1);
                    FIELD(actor, u16, 0x96) = timer;
                } else {
                    FIELD(p, s16, 0x1B0) = 32767;
                    qcopy(p + 0x180, p + 0x170);
                    FIELD(p, float, 0x188) = FIELD(actor, float, 0x18);
                    func_002A7750(actor, 4, 4);
                }
            }
            /* Same check as case 4; jump2 cross-jumps the two, sharing the call above. */
            if (FIELD(p, int, 0x164) != 2 && !FIELD(p, s16, 0x1BC)) {
                if (FIELD(actor, u8, 0x43) != 6) func_002A7470(actor, 6, 0, func_002A7820(15, 30));
                FIELD(actor, u8, 0x30) = 255;
                func_002A7750(actor, 4, 2);
            }
            goto patrol_heading;
        case 4:
            if (func_PAL_L08_0042B6D0(actor, 5.5f, 5.5f, 1,
                func_00283248(FIELD(p, float, 0x120) - FIELD(actor, float, 0x10),
                             FIELD(p, float, 0x124) - FIELD(actor, float, 0x14)), 0.0f, 0.0f)) {
                if (FIELD(actor, u8, 0x43)) func_002A7470(actor, 0, 0, 180);
                func_002A7750(actor, 3, -1);
            }
            if (FIELD(p, int, 0x164) != 2 && !FIELD(p, s16, 0x1BC)) {
                if (FIELD(actor, u8, 0x43) != 6) func_002A7470(actor, 6, 0, func_002A7820(15, 30));
                FIELD(actor, u8, 0x30) = 255;
                func_002A7750(actor, 4, 2);
            }
            goto patrol_heading;
        case 2:
            func_L08_004258D0(actor);
            FIELD(p, float, 0x188) = FIELD(p, float, 0x1C8);
            if (func_00282978(p + 0x1B8)) {
                func_PAL_L08_0042B6D0(actor, 5.5f, 5.5f, 1,
                    func_00283248(FIELD(p, float, 0x120) - FIELD(actor, float, 0x10),
                                 FIELD(p, float, 0x124) - FIELD(actor, float, 0x14)), 0.0f, 0.0f);
            } else {
                func_PAL_L08_0042B6D0(actor, 32.0f, 12.0f, 1,
                    func_00283248(FIELD(p, float, 0x120) - FIELD(actor, float, 0x10),
                                 FIELD(p, float, 0x124) - FIELD(actor, float, 0x14)), 0.0f, 0.0f);
            }
            if (FIELD(actor, u8, 0x60) & 2) {
                if (func_00282DF0(p + 0x190) < 0.020000001f) {
                    if (FIELD(actor, u8, 0x43) != (func_001163B0() & 1) + 4)
                        func_002A7470(actor, (func_001163B0() & 1) | 4, 0, 10);
                } else if (FIELD(actor, u8, 0x43) != 6) func_002A7470(actor, 6, 0, 10);
            }
            if (FIELD(p, int, 0x164) == 2) {
                if (!func_00282978(p + 0x1B4)) goto patrol_heading;
                goto resume_patrol;
            }
            if (FIELD(p, s16, 0x1BC) >= 200) {
resume_patrol:
            if (FIELD(actor, u8, 0x43) != (func_001163B0() & 2) + 2)
                func_002A7470(actor, (func_001163B0() & 2) + 2, 0, 10);
            FIELD(actor, u8, 0x30) = FIELD(p, u8, 0x20E);
            func_002A7750(actor, 4, 0);
                goto patrol_heading;
            } else {
                FIELD(p, s16, 0x1B4) = 200;
                if ((FIELD(actor, u8, 0x21) != 255 &&
                        FIELD(FIELD(p, char *, 0x1F8), int, 0) != FIELD(p, u8, 0x20D)) ||
                    !func_00282978(p + 0x1B6) || !func_L08_00429238(actor, 1, 0) ||
                    FIELD(p, s16, 0x1BC)) goto patrol_heading;
                FIELD(p, float, 0x1F4) = -0.78539824f;
                FIELD(p, float, 0x1F0) = 1.0f;
                FIELD(p, int, 0x204) = 0;
                FIELD(p, int, 0x21C) = 0;
                FIELD(p, u8, 0x219) = 0;
                if (FIELD(actor, u8, 0x43) != 6) func_002A7470(actor, 6, 0, func_002A7820(15, 30));
                func_002A7750(actor, 4, 3);
                FIELD(p, u8, 0x218) = 0;
                FIELD(actor, u8, 0x30) = 255;
                goto patrol_heading;
            }
            goto patrol_heading;
        case 3:
            func_L08_004258D0(actor);
            angle = func_00283248(FIELD(p, float, 0x120) - FIELD(actor, float, 0x10),
                                 FIELD(p, float, 0x124) - FIELD(actor, float, 0x14));
            if (func_00282978(p + 0x1B8)) {
                func_PAL_L08_0042B6D0(actor, 5.5f, 5.5f, 1, angle, 0.0f,
                    -func_00283248(func_00282E80(actor + 0x10, p + 0x140),
                        FIELD(p, float, 0x148) - FIELD(actor, float, 0x18)));
            } else {
                func_PAL_L08_0042B6D0(actor, 32.0f, 12.0f, 1, angle, 0.0f,
                    -func_00283248(func_00282E80(actor + 0x10, p + 0x140),
                        FIELD(p, float, 0x148) - FIELD(actor, float, 0x18)));
            }
            switch (FIELD(p, u8, 0x218)) {
            case 0:
                if (func_00283C80(angle, FIELD(p, float, 0x208)) < 0.6981318f) {
                    FIELD(p, float, 0x1F4) = -0.78539824f;
                    FIELD(p, float, 0x1F0) = 1.0f;
                    if (FIELD(actor, u8, 0x43) != 7) func_002A7470(actor, 7, 0, func_002A7820(8, 15));
                    FIELD(p, u8, 0x218) = 1;
                }
                goto attack_check_cancel;
            case 1:
                FIELD(p, float, 0x21C) += 0.012f;
                if (FIELD(p, float, 0x21C) >= 1.0f) {
                    FIELD(p, float, 0x21C) = 1.0f;
                    FIELD(p, u8, 0x218) = 2;
                    FIELD(p, u8, 0x219) = 0;
                }
                goto attack_move;
            case 2: {
                float sweep, direction;
                FIELD(p, float, 0x1F4) = func_00283B98(FIELD(p, float, 0x1F4), FIELD(p, float, 0x1F0) * 0.024434613f);
                sweep = FIELD(p, float, 0x1F4);
                direction = FIELD(p, float, 0x1F0);
                if (direction > 0.0f) {
                    if (!(sweep >= 0.78539824f)) goto sweep_done;
                } else if (!(sweep <= -0.78539824f)) goto sweep_done;
                {
                    FIELD(p, s16, 0x21A) = 0;
                    FIELD(p, float, 0x1F0) = -direction;
                    FIELD(p, u8, 0x219)++;
                }
sweep_done:
                if (FIELD(p, u8, 0x219) >= 3 && !FIELD(p, s16, 0x1B8)) FIELD(p, u8, 0x218) = 4;
                else FIELD(p, u8, 0x218) = 3;
                goto attack_move;
            }
            case 3:
                if (func_00282978(p + 0x21A)) FIELD(p, u8, 0x218) = 2;
                goto attack_move;
            case 4:
                FIELD(p, float, 0x21C) -= 0.012f;
                if (FIELD(p, float, 0x21C) <= 0.012f) {
                    FIELD(p, u8, 0x219) = 0;
                    FIELD(p, u8, 0x218) = 5;
                }
attack_move:
                func_L08_004262C0(actor);
                goto attack_check_cancel;
            case 5:
                func_L08_00424ED0(actor);
                func_L08_00429350(actor);
                FIELD(p, int, 0x204) = 0;
                FIELD(p, s16, 0x1B6) = 75;
                if (FIELD(actor, u8, 0x43) != 6) func_002A7470(actor, 6, 0, func_002A7820(8, 15));
                func_002A7750(actor, 4, 0);
                goto attack_check_cancel;
            default: goto attack_check_cancel;

            }
attack_check_cancel:
            if (FIELD(p, int, 0x164) == 2 || FIELD(p, s16, 0x1BC) >= 200) {
                func_L08_00424ED0(actor);
                func_L08_00429350(actor);
                FIELD(p, s16, 0x1B6) = 0;
                if (FIELD(actor, u8, 0x43) != 6) func_002A7470(actor, 6, 0, func_002A7820(8, 15));
                FIELD(actor, u8, 0x30) = FIELD(p, u8, 0x20E);
                func_002A7750(actor, 4, 0);
            } else FIELD(p, s16, 0x1B4) = 200;
patrol_heading:
            FIELD(actor, float, 0xF8) = FIELD(p, float, 0x208);
            break;
        }
        break;
    case 5:
        FIELD(actor, u8, 0x30) = 255;
        FIELD(actor, s16, 0x32) = 255;
        func_L08_00429350(actor);
        FIELD(p, u16, 0x1BA)++;
        flags = func_002B1C20(actor, p + 0x50);
        FIELD(p, float, 0x208) = FIELD(actor, float, 0xF8);
        if (flags & 1) func_002A7750(actor, 6, -1);
        else if ((flags & 2) || FIELD(p, s16, 0x1BA) >= 96) {
            if (FIELD(p, float, 0x20) > 0.0f) {
                qzero(p + 0x1A0);
                FIELD(p, u8, 0x6A) = 2;
                if (FIELD(actor, u8, 0x43) != 4) func_002A7470(actor, 4, 0, 40);
                FIELD(p, s16, 0x1BA) = 0;
                qzero(p + 0x190);
                FIELD(actor, u8, 0x30) = FIELD(p, u8, 0x20E);
                func_002A7750(actor, 4, 2);
                func_L08_00424ED0(actor);
            } else func_002A7750(actor, 6, -1);
        }
        if ((flags & 4) || FIELD(actor, float, 0x18) < FIELD(p, float, 0x1C4) + 1.5f) {
            FIELD(p, u16, 0x1BA)++;
            qcopy(local, actor + 0x10);
            local[2] = FIELD(p, float, 0x1C4);
            func_PAL_L08_0042A6A0(actor, local, 10, 14.0f, 6.0f, 5.5f, 0.0f, 0.5f, 4.0f);
        }
        break;
    case 6:
    case 7: {
        char *child;
        u16 id;
        u8 *bits;
        func_L08_00429350(actor);
        child = func_0029EFD0(0x8C4);
        if (!child) break;
        FIELD(child, u8, 0x23) = 80;
        FIELD(child, u16, 0x34) |= 0x800;
        FIELD(child, u8, 0x30) = 255;
        FIELD(child, s16, 0x32) = 255;
        FIELD(child, u8, 0x31) = 1;
        FIELD(child, u8, 0x20) = 0;
        FIELD(child, u8, 0xBC) = 0;
        qcopy(child + 0x10, actor + 0x10);
        if (FIELD(p, float, 0x1C4) != 0.0f) FIELD(child, float, 0x18) = FIELD(p, float, 0x1C4);
        FIELD(FIELD(child, char *, 0x68), char *, 4) = actor;
        func_002A0F48(child);
        func_002AB650(child);
        if (FIELD(actor, u8, 0x20) == 7)
            func_002ABBB8(actor, p + 0x190, 0, 0.0f, 0.0f, 20, 6, 32,
                8.0f, 4.0f, 9.0f, 2.0f, -1, 30.0f, 1, 2, -1, 0, 0x810001);
        func_L08_00424F40(actor);
        func_002A6C58(actor, 0, 3);
        D_L08_0021DE80.flags[FIELD(actor, s16, 0xB2)] = 0;
        D_L08_0021EAF0.flags[FIELD(actor, s16, 0xB2)] = 0;
        id = FIELD(actor, u16, 0xB2);
        bits = &D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
        {
            u8 value = *bits;
            u8 low = value & 0xF8;
            u8 high = value & 0x8F;
            value = !(id & 1) ? low : high;
            *bits = value;
        }
        func_0029F338(actor);
        return;
    }
    case 8: break;
    }
    func_PAL_L08_0042AC50(actor);
    if ((unsigned int)(FIELD(actor, u8, 0x20) - 2) < 4 && FIELD(actor, u8, 0x31)) {
        int index = FIELD(p, int, 0x1E8);
        if (index != -1 && FIELD(FIELD(p, char *, 0x1FC), int, 0)) {
            char *target = (char *)(D_L08_001B29DC + (index << 8));
            if (!target || FIELD(target, u8, 0x20) == 0xFE || FIELD(target, u8, 0x20) == 0xFD)
                func_L08_003D3928(actor, actor + 0x10);
            else func_L08_003D3928(actor, target + 0x10);
        } else func_L08_003D3928(actor, actor + 0x10);
    }
    if (FIELD(actor, float, 0x10) < 30.0f || FIELD(actor, float, 0x10) > 993.0f ||
        FIELD(actor, float, 0x14) < 30.0f || FIELD(actor, float, 0x14) > 993.0f ||
        FIELD(actor, float, 0x18) < 30.0f || FIELD(actor, float, 0x18) > 993.0f) {
        func_L08_00424F40(actor);
        func_0029F338(actor);
    }
}
