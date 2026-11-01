/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Opus handoff (big1, 2026-10-26): func_L11_00420C88, 15832 bytes, 1 place (L11).
 * Step 0: one function (one prologue addiu $sp,-0xB0, one jr $ra; two jump tables:
 * jtbl_L11_002BAC20, 11 entries on byte +0x95; jtbl_L11_002BAC50, 40 entries on
 * byte +0x20 minus 1). No twin: best opcode ratio 0.65 (func_L11_00425F10); L22_0039D708
 * has the same two-switch shape but only 0.16 opcode similarity.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier (keep-block-order,
 * no-null-pointer-checks: no change; dropping qcopy-barrier is worse).
 * Measured against the current rac2-large-functions compiler (check.py, own unit
 * src/levels/11_joba/L11_00420C88-big.c): 15384 bytes vs 15832; aligned opcodes
 * 3243/3958 (0.819), opcode+register equal 1896/3958.
 * Changes this round over the 2026-10-23 draft (15268 bytes, 0.587 opcodes):
 *  - case bodies put in retail address order (GCC 2.95 emits case bodies in source order):
 *    selector 10,0,1,2,8,4,3,5,6,7,9; states 2/3,5-11,13-17,19,20,22,23,28,29,32,38,39,40,
 *    24,31,33,25,26,27,30,34,35 (+0.20);
 *  - the path-follow arms (3 copies) re-read D_L11_001FF580[WORD(state,0x54c)] for the
 *    func_002B6228 argument as retail does (+0.03 opcodes, register shifts follow).
 * Still off, by retail address:
 *  - selector case 0 (0x420E04-0x4213A4): retail takes the HALF(state,0x264) == 2 arm first
 *    and that arm is ~160 instructions with per-arm tails into the shared 0x4218xx/0x421650
 *    tails; the draft's == 2 arm is much shorter. Swapping the arms alone loses 0.013.
 *    Re-derive that arm from the listing.
 *  - the early-return block (func_0029F338; return) sits at 0x421FF4 between selector
 *    cases 7 and 9, not after the call; source shape unknown.
 *  - retail keeps D_00189EA0's high part in $s7 (addiu $v0,$s7,-0x61E0) and recomputes
 *    object+0x10 per case; state cases 25-27 (0x4239A4: 54 instructions missing).
 */
#include "common.h"

typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
#define BYTE(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define SIGNED_BYTE(p, o) (*(signed char *)((char *)(p) + (o)))
#define HALF(p, o) (*(short *)((char *)(p) + (o)))
#define UHALF(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define WORD(p, o) (*(int *)((char *)(p) + (o)))
#define REAL(p, o) (*(float *)((char *)(p) + (o)))
#define POINTER(p, o) (*(char **)((char *)(p) + (o)))
#define QUAD(p, o) (*(QuadWord *)((char *)(p) + (o)))

extern int D_L11_001AED04;
extern int D_L11_001AED00 __attribute__((sda));
extern int D_L11_001B30C8 __attribute__((sda));
extern int D_L11_001B359C;
extern int D_L11_001B35B8;
extern unsigned short *D_L11_001FC420[];
extern Vector D_L11_001BA8C0;
extern char D_L11_001B0FD8[], D_L11_002BACF0[];
extern float func_002A89A8(void *, int, float);
extern void func_0026FEB8(const char *, ...);
extern int func_002A77E0(int);
extern void func_L00_003294F0(unsigned char *, int);
extern void *func_002B60B0(unsigned char *, float, float, float, float);
extern void func_002A7750(unsigned char *, unsigned char, int);
extern void func_002A7470(void *, int, int, int);
extern char *func_0029EFD0(int);
extern void func_002A0F48(void *);
extern void func_002AF1D0(void *, void *, int, int);
extern void func_0029F338(void *);
extern void func_002AC728(void *, void *, int, float, float);
extern void func_0029FCC0(char *, int, char *);
extern int func_002A8508(int, int);
extern void func_002A6C58(void *, int, int);


struct family_27f9_object;
/* Same partial context view as canonical func_002B1C20. */
typedef struct {
    unsigned char reserved_00[0x18];
    unsigned char enabled, count, kind;
    unsigned char reserved_1b[0x65];
    unsigned char payload[1];
} Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext;
typedef unsigned long Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags;
extern int D_L11_001CAE40;
extern int D_0018C0B4, D_0018B068;
extern char *D_0018C0B0;
extern Vector D_00189EA0, D_00189EF0;
extern char *D_L11_001FF580[];
extern char D_L11_001B0FC8[];
extern int func_L11_00424A60(unsigned char *);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern int func_002B38B8(unsigned char *);
extern int func_002B3890(unsigned char *);
extern int func_002A7820(int, int);
extern int func_002B6228(void *, void *, int, int);
extern int func_002B50E0(void *, void *, float);
extern Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags func_002B1C20(void *, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *);
extern void func_L01_003E9CF8(void *, int, void (*)(void *));
extern int func_L11_00420C38(unsigned char *);
extern void func_002833F0(void *, void *);
extern void func_002AEC48(void *, void *, int, float, float);
extern float func_002AA3A8(float *, float *, float, float, float, float);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern float func_0029F530(char *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002A7EA0(void *, void *, void *, int, float, float, float, float);
extern int func_L04_0033D4B0(unsigned char *);
extern void func_L01_00321178(char *, char *);
extern float func_002A7E08(struct family_27f9_object *, float *, float *, float, float, float);
extern float func_002A7CA0(struct family_27f9_object *, float *, float, float, float, float);
extern int func_002B4FF0(char *, float *, float);
extern int func_L11_00425788(char *, char *, float, float, float, float);
extern float func_00282C48(float);
extern int func_002AEB60(char *, float);
extern void func_002AF000(float *, float, float, float);
extern char *func_L11_00450328(void *, void *, void *, int, float);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_L11_00425A50(char *);

/* The guarded animation transition is repeated throughout both state machines. */
#define PLAY(p, animation, start, blend) do { \
    if (BYTE((p), 0x43) != (animation)) \
        func_002A7470((p), (animation), (start), (blend)); \
} while (0)

void func_L11_00420C88(unsigned char *object)
{
    Vector offset, side, point;
    char *state, *linked, *other_state, *path;
    unsigned short *ids;
    unsigned short id;
    int index, closest, kind, next_state;
    float old_z, distance, angle, other_angle, pitch, limit;
    Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags flags;
    char *position;

    if (D_L11_001CAE40 != 0) return;
    if (D_0018C0B4 == 0x6f && BYTE(object, 0x95) != 4) return;
    old_z = REAL(object, 0x18);
    state = POINTER(object, 0x68);
    if (func_L11_00424A60(object) != 0) {
        func_0029F338(object);
        return;
    }
    position = (char *)object + 0x10;
    switch (BYTE(object, 0x95)) {
    case 10:
        if (func_00282E80(position, &D_00189EA0) < 6.0f) {
            angle = func_00283248(REAL(D_0018C0B0, 0x10) - REAL(object, 0x10), REAL(D_0018C0B0, 0x14) - REAL(object, 0x14));
            angle = func_00283BE0(angle, REAL(object, 0xf8));
            if (func_002B38B8(object) != 0) angle = -angle;
            limit = 1.5707965f;
            if (angle <= limit) { limit = angle; if (angle < -1.5707965f) limit = -1.5707965f; }
            REAL(state, 0x308) = limit;
        }
        if (D_0018B068 != 0x41) BYTE(object, 0x95) = 0;
        break;
    case 0:
        if (func_002B3890(object) != 0)
            func_002B60B0(object, 0.001527777873f, 0.04583333433f, 0.001163552981f, 0.1047197729f);
        if (HALF(state, 0x264) != 2) {
            if (HALF(state, 0x266) == 0) break;
            if (WORD(state, 0x558) == -1 || WORD(state, 0x560) < 1) {
                BYTE(object, 0x95) = 1;
                PLAY(object, 0x18, 0, 20);
            } else if (WORD(state, 0x560) == 1) {
                if (BYTE(object, 0x43) != 0x18)
                    func_002A7470(object, 0x18, 0, func_002A7820(5, 15));
                func_002A7750(object, 6, -1);
            } else {
                if (BYTE(object, 0x43) != 15)
                    func_002A7470(object, 15, 0, func_002A7820(5, 15));
                func_002A7750(object, 7, -1);
                func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.003393696155f, 0.2617994249f);
            }
            if ((unsigned int)(UHALF(state, 0x264) - 1) < 2) {
                if (WORD(state, 0x284) != -1) {
                    PLAY(object, 15, 0, 10);
                    func_002A7750(object, 0x1e, 2);
                } else if (WORD(state, 0x580) != -1) {
                    PLAY(object, 15, 0, 10);
                    func_002A7750(object, 0x20, 2);
                } else if (WORD(state, 0x294) == 1) {
                    if (BYTE(object, 0x43) != 0x22)
                        func_002A7470(object, 0x22, 0, func_002A7820(7, 20));
                    func_002A7750(object, 0x18, 2);
                } else {
                    if (WORD(state, 0x570) == 0) {
                        WORD(state, 0x290) = 1;
                        PLAY(object, 14, 0, 10);
                    } else PLAY(object, 0x21, 0, 5);
                    func_002A7750(object, 0x18, 3);
                }
            }
            HALF(state, 0x266) = 0;
            if (WORD(state, 0x548) != -1) {
                linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
                if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) {
                    PLAY(object, 15, 0, 10);
                    func_002A7750(object, 0x1d, 2);
                    BYTE(linked, 0x20) = 6;
                    BYTE(object, 0xbc) = 1;
                }
                HALF(state, 0x266) = 1;
            }
            break;
        }
        if (WORD(state, 0x284) != -1) {
            PLAY(object, 15, 0, 10);
            func_002A7750(object, 0x1e, 2);
        }
        if (WORD(state, 0x548) == -1) {
            if (WORD(state, 0x580) != -1) {
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x20, 2);
            } else {
                if (WORD(state, 0x294) == 1) {
                    if (BYTE(object, 0x43) != 0x22)
                        func_002A7470(object, 0x22, 0, func_002A7820(7, 20));
                    func_002A7750(object, 0x18, 2);
                } else {
                    if (WORD(state, 0x570) == 0) {
                        WORD(state, 0x290) = 1;
                        PLAY(object, 14, 0, 5);
                    } else PLAY(object, 0x21, 0, 10);
                    func_002A7750(object, 0x18, 3);
                }
                if (WORD(state, 0x270) == -1) break;
                WORD(state, 0x274) = D_L11_001B359C + WORD(state, 0x270) * 0x100;
                func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.003393696155f, 0.2617994249f);
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x1f, 2);
            }
        } else {
            linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
            if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) goto request_mount;
            if (WORD(state, 0x294) == 1) {
                if (BYTE(object, 0x43) != 0x22)
                    func_002A7470(object, 0x22, 0, func_002A7820(7, 20));
                func_002A7750(object, 0x18, 2);
            } else {
                if (WORD(state, 0x570) == 0) {
                    WORD(state, 0x290) = 1;
                    PLAY(object, 14, 0, 5);
                } else PLAY(object, 0x21, 0, 10);
                func_002A7750(object, 0x18, 3);
            }
        }
        break;
    case 1:
        if (func_002B3890(object) != 0) REAL(state, 0x12c) = 6.0f;
        if (WORD(state, 0x548) != -1) {
            linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
            if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) {
                WORD(state, 0x178) &= ~0x10;
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x1d, 2);
                BYTE(linked, 0x20) = 6;
                BYTE(object, 0xbc) = 1;
            }
        }
        if ((unsigned int)(UHALF(state, 0x264) - 1) > 1) break;
        WORD(state, 0x178) &= ~0x10;
        if (WORD(state, 0x284) != -1) {
            PLAY(object, 15, 0, 10);
            func_002A7750(object, 0x1e, 2);
            closest = 0;
            limit = 100.0f;
            for (index = 0; index < WORD(D_L11_001FF580[WORD(state, 0x284)], 0); ++index) {
                distance = func_00282E80(position, D_L11_001FF580[WORD(state, 0x284)] + 0x10 + index * 0x10);
                if (limit <= distance) distance = limit;
                else closest = index;
                limit = distance;
            }
            func_002B6228(object, D_L11_001FF580[WORD(state, 0x284)], -1, closest);
        }
        if (WORD(state, 0x548) == -1) {
            if (WORD(state, 0x294) == 1) {
                if (BYTE(object, 0x43) != 0x22) {
                    index = func_002A77E0(4);
                    func_002A7470(object, 0x22, index, func_002A7820(7, 20));
                }
                func_002A7750(object, 0x18, 2);
            } else {
                WORD(state, 0x290) = 1;
                PLAY(object, 14, 0, 40);
                func_002A7750(object, 0x18, 3);
            }
        } else {
            linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
            if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) {
                WORD(state, 0x178) &= ~0x10;
                goto request_mount;
            }
            if (WORD(state, 0x294) != 1) {
                WORD(state, 0x290) = 1;
                PLAY(object, 14, 0, 40);
                func_002A7750(object, 0x18, 3);
            } else {
                if (BYTE(object, 0x43) != 0x19) {
                    index = func_002A77E0(4);
                    func_002A7470(object, 0x19, index, func_002A7820(7, 20));
                }
                func_002A7750(object, 0x18, 2);
            }
        }
        break;
    case 2:
        if (func_002B3890(object) != 0)
            func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.003781547071f, 0.2967060208f);
        if ((unsigned int)(UHALF(state, 0x264) - 1) > 1 && BYTE(object, 0x20) != 0x1d &&
            BYTE(object, 0x20) != 0x22 && BYTE(object, 0x20) != 0x20 && func_002A77E0(4) == 1) {
            REAL(object, 0x48) = 1.0f;
            kind = func_002A77E0(4);
            if (kind == 0) PLAY(object, 14, 0, 10);
            else if (kind == 2) PLAY(object, 0x1e, 0, 20);
            else PLAY(object, 0x18, 0, 20);
            func_002A7750(object, 0x13, 1);
            WORD(state, 0x560) = 0;
            HALF(state, 0x260) = func_002A7820(580, 600);
        }
        if (WORD(state, 0x548) != -1) {
            linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
            if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) {
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x1d, 2);
                BYTE(linked, 0x20) = 6;
                BYTE(object, 0xbc) = 1;
            }
        }
        goto check_route;
    case 8:
        if (D_0018C0B4 != 0x31) {
            if (WORD(state, 0x548) != -1) {
                linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
            request_mount:
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x1d, 2);
                BYTE(linked, 0x20) = 6;
                BYTE(object, 0xbc) = 1;
            } else if (WORD(state, 0x294) != 0) {
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x1c, 2);
            } else {
                PLAY(object, 0x19, 0, 10);
                func_002A7750(object, 0x18, 2);
            }
        }
        break;
    case 4:
        if (REAL(state, 0x20) > 0.0f) {
            angle = func_00283248(D_00189EA0.v[0] - REAL(object, 0x10), D_00189EA0.v[1] - REAL(object, 0x14));
            func_002B50E0(object, position, angle);
        }
        flags = func_002B1C20(object, (Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *)(state + 0x60));
        if ((flags & 1) != 0) {
            --D_L11_001AED04;
            func_002A6C58(object, 0, 3);
            func_L01_003E9CF8(object, 0, 0);
            return;
        }
        if ((flags & 2) == 0) break;
        HALF(state, 0x26) = 0;
        if ((unsigned int)(UHALF(state, 0x264) - 1) < 2) {
            PLAY(object, 15, 0, 10);
            func_002A7750(object, 0x1c, 2);
            if (func_00282E80(position, &D_00189EA0) < 2.5f) {
                angle = func_00283248(D_00189EA0.v[0] - REAL(object, 0x10), D_00189EA0.v[1] - REAL(object, 0x14));
                if (func_00283C80(REAL(object, 0xf8), angle) < 0.6108653f) {
                    PLAY(object, 0x11, 9, 4);
                    func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.001163552981f, 0.1047197729f);
                    func_002A7750(object, 0x22, 2);
                }
            }
            if (BYTE(state, 0x37) == 10) {
                PLAY(object, 0x11, 9, 4);
                func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.001163552981f, 0.1047197729f);
                func_002A7750(object, 0x22, 2);
            }
            if (D_0018C0B4 == 0x31 && WORD(state, 0x574) != -1) {
                if (BYTE(object, 0x43) != 15) func_002A7470(object, 15, 0, func_002A7820(5, 15));
                func_002A7750(object, 8, 8);
            }
        } else if (WORD(state, 0x558) == -1) {
            PLAY(object, 0x18, 0, 10);
            func_002A7750(object, 0x13, 1);
            HALF(state, 0x260) = func_002A7820(580, 600);
        } else {
            WORD(state, 0x178) &= ~0x10;
            if (BYTE(object, 0x43) != 15) func_002A7470(object, 15, 0, func_002A7820(5, 15));
            func_002A7750(object, 7, 1);
            func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.003393696155f, 0.2617994249f);
        }
        break;
    case 3:
        if (func_002B3890(object) != 0)
            func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.001163552981f, 0.1047197729f);
        if (WORD(state, 0x294) == 1) {
            PLAY(object, 15, 0, 10);
            func_002A7750(object, 0x1c, 2);
        }
        if ((unsigned int)(UHALF(state, 0x264) - 1) > 1) {
            PLAY(object, 0x1a, 0, 30);
            func_002A7750(object, 0x13, 1);
            HALF(state, 0x260) = func_002A7820(580, 600);
            WORD(state, 0x560) = 0;
        }
    check_route:
        if (D_0018C0B4 == 0x31 && WORD(state, 0x574) != -1) {
            if (BYTE(object, 0x43) != 15) func_002A7470(object, 15, 0, func_002A7820(5, 15));
            func_002A7750(object, 9, 8);
            func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.003393696155f, 0.2617994249f);
        }
        break;
    case 5:
        if (POINTER(state, 0x278) != 0) func_002AF1D0(object, POINTER(state, 0x278), 1, 0);
        linked = POINTER(state, 0x274);
        QUAD(object, 0x10) = QUAD(linked, 0x10);
        QUAD(object, 0xf0) = QUAD(linked, 0xf0);
        QUAD(POINTER(state, 0x280), 0x10) = QUAD(object, 0x10);
        QUAD(POINTER(state, 0x280), 0xf0) = QUAD(object, 0xf0);
        QUAD(POINTER(state, 0x280), 0x10) = QUAD(object, 0x10);
        REAL(POINTER(state, 0x280), 0x18) += 0.65f;
        if (WORD(state, 0x26c) != 0 && POINTER(state, 0x274) != 0 &&
            BYTE(POINTER(state, 0x274), 0x20) != 0xfe && BYTE(POINTER(state, 0x274), 0x20) != 0xfd) {
            if (func_L11_00420C38(object) == 0) break;
            next_state = 3;
        } else next_state = 2;
        func_002AC728(object, POINTER(state, 0x278) + 0x10, -1, 0.5f, 3.0f);
        func_0029F338(POINTER(state, 0x278));
        POINTER(state, 0x278) = 0;
        func_0029F338(POINTER(state, 0x280));
        WORD(POINTER(POINTER(state, 0x274), 0x68), 0x27c) = 0;
        if (next_state == 3) PLAY(object, 9, 0, 0);
        func_002A7750(object, next_state, 6);
        break;
    case 6:
        if (func_002B3890(object) != 0 && POINTER(state, 0x29c) == 0) {
            POINTER(state, 0x29c) = func_0029EFD0(0x9ac);
            if (POINTER(state, 0x29c) == 0) { func_0029F338(object); return; }
            BYTE(POINTER(state, 0x29c), 0x30) = BYTE(object, 0x30);
            UHALF(POINTER(state, 0x29c), 0x32) = UHALF(object, 0x32);
            BYTE(POINTER(state, 0x29c), 0x31) = 1;
            *(long *)(POINTER(state, 0x29c) + 0x38) = *(long *)(object + 0x38);
            func_002A0F48(POINTER(state, 0x29c));
            WORD(POINTER(state, 0x29c), 0x98) = 0;
            func_002AF1D0(object, POINTER(state, 0x29c), 3, 0);
            WORD(state, 0x290) = 1;
            REAL(object, 0xf0) = 0.0f;
            REAL(object, 0xf4) = 0.0f;
            func_002833F0(object + 0xc0, object + 0xf0);
        }
        break;
    case 7:
        WORD(state, 0x290) = 0;
        linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
        other_state = POINTER(linked, 0x68);
        if (BYTE(linked, 0x43) == 1) {
            REAL(linked, 0x48) = 0.65f;
            REAL(object, 0x48) = 0.65f;
            if (WORD(state, 0x58c) != 0) {
                REAL(linked, 0x48) = 0.35f;
                REAL(object, 0x48) = 0.35f;
            }
        } else { REAL(linked, 0x48) = 1.0f; REAL(object, 0x48) = 1.0f; }
        if (BYTE(object, 0x20) != 0x28) {
            angle = func_00283248(D_00189EA0.v[0] - REAL(object, 0x10), D_00189EA0.v[1] - REAL(object, 0x14));
            func_002B50E0(object, position, angle);
            distance = func_00282E80(position, &D_00189EF0);
            pitch = func_00283248(distance, D_00189EF0.v[2] - REAL(object, 0x18));
            limit = -0.52359885f;
            if (-0.52359885f <= pitch) { limit = pitch; if (pitch > 0.52359885f) limit = 0.52359885f; }
            REAL(other_state, 0xb4) = -limit;
            func_002AEC48(linked, other_state + 0x70, 2, 0.03f, 0.3f);
        }
        REAL(object, 0x10) = REAL(linked, 0x10);
        REAL(object, 0x14) = REAL(linked, 0x14);
        REAL(object, 0x18) = REAL(linked, 0x18) + 1.5f;
        func_002833F0(linked + 0xc0, object + 0xf0);
        if ((unsigned int)(UHALF(state, 0x264) - 1) > 1 && BYTE(object, 0x20) != 0x26 && BYTE(object, 0x20) != 0x28) {
            PLAY(object, 0x1f, 0, 10);
            func_002A7470(linked, 0, 0, 10);
            func_002A7750(object, 0x28, -1);
        }
        if (BYTE(object, 0x20) == 0x28 && HALF(state, 0x264) == 2) {
            func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.001163552981f, 0.1047197729f);
            PLAY(object, 0x20, 0, 10);
            func_002A7750(object, 0x27, -1);
            func_002A7470(linked, 1, 0, 10);
        }
        break;
    case 9:
        distance = func_002A89A8(position, 0, 0.5f);
        func_002AA3A8((float *)(object + 0x18), (float *)(state + 0x550), distance,
                     0.000555555569f, 0.0002777777845f, 0.3133333325f);
        break;
    default:
        break;
    }
    switch (BYTE(object, 0x20)) {
    case 2:
    case 3:
        if ((BYTE(object, 0x60) & 2) != 0) {
            UHALF(object, 0x34) |= 0x5000;
            WORD(object, 0x98) = WORD(POINTER(object, 0x24), 0x10);
            func_002A7750(object, 0x13, 1);
            if (HALF(state, 0x260) < 300) HALF(state, 0x260) = func_002A7820(480, 600);
            PLAY(object, 13, 0, 10);
            if (REAL(state, 0x20) <= 0.0f) REAL(state, 0x20) = 0.1f;
        }
        distance = func_0029F530((char *)object);
        if (distance >= 10.0f) REAL(object, 0x18) = func_002A89A8(position, 0, 0.5f);
        if (distance >= 1.5f && distance <= 17.0f) {
            offset.v[0] = func_00283180(REAL(object, 0xf8) + 3.141593f) * 0.15f;
            offset.v[1] = func_00283198(REAL(object, 0xf8) + 3.141593f) * 0.15f;
            offset.v[2] = 0.0f;
            side.v[0] = func_00283180(REAL(object, 0xf8) + 1.5707965f) * 0.05f;
            side.v[1] = func_00283198(REAL(object, 0xf8) + 1.5707965f) * 0.05f;
            side.v[2] = 0.0f;
            point.word = QUAD(object, 0x10);
            func_00282CC0(&point, position, &side);
            func_00282CC0(&point, position, &offset);
            func_002A7EA0(object, position, &point, 0, 0.5f, 0.55f, 0.5f, 0.52359885f);
        }
        break;
    case 5:
        linked = POINTER(state, 0x55c);
        if (linked == 0) break;
        if (WORD(state, 0x540) == 3 && BYTE(object, 0x95) != 10) {
            angle = func_00283248(REAL(linked, 0x10) - REAL(object, 0x10), REAL(linked, 0x14) - REAL(object, 0x14));
            angle = func_00283BE0(angle, REAL(object, 0xf8));
            if (func_002B38B8(object) != 0) angle = -angle;
            limit = 1.5707965f;
            if (angle <= limit) { limit = angle; if (angle < -1.5707965f) limit = -1.5707965f; }
            REAL(state, 0x308) = limit;
        }
        if (WORD(state, 0x540) == 1 && BYTE(object, 0x42) == 0x1c && func_002A77E0(200) == 1) {
            PLAY(object, 0x1b, 0, 30);
            if (func_002A77E0(3) == 1) PLAY(object, 0x1a, 0, 30);
        }
        if ((unsigned int)(BYTE(object, 0x42) - 0x1a) < 2 && (BYTE(object, 0x60) & 2) != 0) {
            PLAY(object, 0x1d, 0, 30);
            if (HALF(POINTER(state, 0x55c), 0xaa) == 0xcf5) {
                WORD(POINTER(POINTER(state, 0x55c), 0x68), 0x540) = 1;
                WORD(state, 0x540) = 2;
            }
        }
        if (BYTE(object, 0x42) == 0x1d && (BYTE(object, 0x60) & 2) != 0) {
            PLAY(object, 0x1e, 0, 30);
            if (WORD(state, 0x540) == 1) PLAY(object, 0x1c, 0, 30);
            if (WORD(state, 0x540) == 3) {
                ids = D_L11_001FC420[BYTE(object, 0x21)];
                do {
                    id = *ids;
                    linked = (char *)(D_L11_001B359C + (id & 0x7fff) * 0x100);
                    if (SIGNED_BYTE(linked, 0x20) >= 0 && HALF(linked, 0xaa) == 0xcf5 &&
                        WORD(POINTER(linked, 0x68), 0x540) == 1) {
                        POINTER(state, 0x55c) = linked;
                        break;
                    }
                    ++ids;
                } while ((short)id >= 0);
            }
        }
        if (WORD(state, 0x540) == 1 && BYTE(object, 0x42) == 0x1e) PLAY(object, 0x1d, 0, 20);
        if (WORD(state, 0x540) == 3 && BYTE(POINTER(state, 0x55c), 0x42) == 0x1d) PLAY(object, 0x1d, 0, 35);
        break;
    case 6:
        WORD(state, 0x290) = 1;
        if ((BYTE(object, 0x60) & 2) != 0) {
            func_002A7750(object, 7, -1);
            PLAY(object, 0x10, 0, 30);
            WORD(state, 0x290) = 0;
        }
        break;
    case 7:
        if (func_002B6120((char *)object, D_L11_001FF580[WORD(state, 0x558)]) == 0) break;
        func_002A7750(object, 11, -1);
        PLAY(object, 0x18, 0, 20);
        if (BYTE(object, 0x95) == 1 && WORD(state, 0x56c) != -1) func_002A7750(object, 0x17, -1);
        break;
    case 8:
        if (func_002B6120((char *)object, D_L11_001FF580[WORD(state, 0x574)]) != 0) {
            func_002A7750(object, 11, -1);
            PLAY(object, 0x18, 0, 20);
        }
        break;
    case 9:
        func_L01_00321178((char *)object, D_L11_001FF580[WORD(state, 0x574)] + 0x10);
        if (func_00282E80(position, D_L11_001FF580[WORD(state, 0x574)] + 0x10) < 0.5f) {
            PLAY(object, 0x25, 0, 10);
            func_002A7750(object, 10, -1);
        }
        if (WORD(state, 0x588) != 0) {
            if (BYTE(object, 0x43) != 15) func_002A7470(object, 15, 0, func_002A7820(5, 15));
            func_002A7750(object, 8, 8);
        }
        break;
    case 10:
        if ((BYTE(object, 0x60) & 2) != 0) {
            if (BYTE(object, 0x43) != 15) func_002A7470(object, 15, 0, func_002A7820(5, 15));
            func_002A7750(object, 8, 8);
            WORD(state, 0x588) = 1;
        }
        break;
    case 11:
        if ((BYTE(object, 0x60) & 2) != 0) {
            func_002B60B0(object, 0.001527777873f, 0.04583333433f, 0.001163552981f, 0.1047197729f);
            if (func_002A8508(BYTE(object, 0x21), -1) > 1) {
                POINTER(state, 0x55c) = (char *)func_L04_0033D4B0(object);
                func_002A7750(object, 13, -1);
                PLAY(object, 0x1c, 0, 30);
                WORD(state, 0x540) = 1;
                if (BYTE(POINTER(state, 0x55c), 0x42) == 0x1c) {
                    PLAY(object, 0x1e, 0, 30);
                    WORD(state, 0x540) = 2;
                }
            }
        }
        break;
    case 13:
        linked = POINTER(state, 0x55c);
        angle = func_00283248(REAL(linked, 0x10) - REAL(object, 0x10), REAL(linked, 0x14) - REAL(object, 0x14));
        func_002B50E0(object, position, angle);
        linked = POINTER(state, 0x55c);
        angle = func_00283248(REAL(linked, 0x10) - REAL(object, 0x10), REAL(linked, 0x14) - REAL(object, 0x14));
        if (!(0.087266475f <= func_00283C80(REAL(object, 0xf8), angle))) func_002A7750(object, 5, -1);
        break;
    case 14:
        func_002B60B0(object, 0.001527777873f, 0.04583333433f, 0.003781547071f, 0.2967060208f);
        if (func_002B6120((char *)object, D_L11_001FF580[WORD(state, 0x54c)]) != 0) {
            func_002A7750(object, 0x11, -1);
            PLAY(object, 13, 0, 20);
        }
        break;
    case 15:
        func_002B60B0(object, 0.001527777873f, 0.04583333433f, 0.007563094143f, 0.5934120417f);
        if (func_002B6120((char *)object, D_L11_001FF580[WORD(state, 0x54c)]) != 0) {
            path = D_L11_001FF580[WORD(state, 0x54c)];
            distance = func_00282E80(position, path + 0x10);
            other_angle = func_00282E80(position, path + WORD(path, 0) * 0x10);
            if (other_angle < distance) func_002B6228(object, D_L11_001FF580[WORD(state, 0x54c)], 0, WORD(path, 0) - 1);
            else func_002B6228(object, D_L11_001FF580[WORD(state, 0x54c)], WORD(path, 0) - 1, 0);
            if (func_002A77E0(5) == 1) {
                PLAY(object, 0x19, 0, 15);
                func_002A7750(object, 0x10, -1);
            }
        }
        angle = func_00283248(D_00189EA0.v[0] - REAL(object, 0x10), D_00189EA0.v[1] - REAL(object, 0x14));
        angle = func_00283BE0(angle, REAL(object, 0xf8));
        if (func_002B38B8(object) != 0) angle = func_00283B98(angle, 3.141593f);
        limit = 1.5707965f;
        if (angle <= limit) { limit = angle; if (angle < -1.5707965f) limit = -1.5707965f; }
        angle = func_00283B98(limit * 1.0f, REAL(state, 0x308));
        REAL(state, 0x308) = angle;
        if (angle > 1.5707965f) REAL(state, 0x308) = 1.5707965f;
        else if (angle < -1.5707965f) REAL(state, 0x308) = -1.5707965f;
        break;
    case 16:
        angle = func_00283248(D_00189EA0.v[0] - REAL(object, 0x10), D_00189EA0.v[1] - REAL(object, 0x14));
        func_002B50E0(object, position, angle);
        if ((BYTE(object, 0x60) & 2) != 0) {
            func_002A7750(object, 15, -1);
            PLAY(object, 0x10, 0, 20);
        }
        break;
    case 17:
        if ((BYTE(object, 0x60) & 2) != 0) {
            path = D_L11_001FF580[WORD(state, 0x54c)];
            distance = func_00282E80(position, path + 0x10);
            other_angle = func_00282E80(position, path + WORD(path, 0) * 0x10);
            if (other_angle < distance) func_002B6228(object, D_L11_001FF580[WORD(state, 0x54c)], 0, WORD(path, 0) - 1);
            else func_002B6228(object, D_L11_001FF580[WORD(state, 0x54c)], WORD(path, 0) - 1, 0);
            func_002A7750(object, 14, -1);
            PLAY(object, 0x10, 0, 20);
        }
        break;
    case 19:
        func_002A7E08((struct family_27f9_object *)object, (float *)D_0018C0B0, (float *)(state + 0x27c),
                     0.001f, 0.01f, 0.1f);
        if ((BYTE(object, 0x60) & 2) != 0) {
            PLAY(object, 0x17, 0, 20);
            func_002A7750(object, 0x14, -1);
            WORD(state, 0x178) |= 0x10;
            if (WORD(state, 0x56c) != -1) QUAD(state, 0x110) = QUAD(D_L11_001FF580[WORD(state, 0x56c)], 0x10);
        }
        break;
    case 20:
        WORD(state, 0x290) = 1;
        func_002A7E08((struct family_27f9_object *)object, (float *)D_0018C0B0, (float *)(state + 0x27c),
                     0.001f, 0.01f, 0.1f);
        func_002B60B0(object, 0.000555555569f, 0.01666666754f, 0.001163552981f, 0.1047197729f);
        func_L01_00321178((char *)object, state + 0x110);
        if (!(2.0f <= func_00282E80(position, state + 0x110))) {
            WORD(state, 0x178) &= ~0x10;
            func_002A7750(object, 0x15, -1);
            PLAY(object, 0x18, 0, 20);
            if (WORD(state, 0x56c) != -1) func_002A7750(object, 0x17, -1);
        }
        break;
    case 22:
        func_002B60B0(object, 0.001527777873f, 0.04583333433f, 0.003781547071f, 0.2967060208f);
        if (func_002B6120((char *)object, D_L11_001FF580[WORD(state, 0x56c)]) != 0) {
            func_002A7750(object, 0x17, -1);
            PLAY(object, 0x18, 0, 20);
        }
        break;
    case 23:
        if ((BYTE(object, 0x60) & 2) != 0) {
            path = D_L11_001FF580[WORD(state, 0x56c)];
            distance = func_00282E80(position, path + 0x10);
            other_angle = func_00282E80(position, path + WORD(path, 0) * 0x10);
            if (other_angle < distance) func_002B6228(object, D_L11_001FF580[WORD(state, 0x54c)], 0, WORD(path, 0) - 1);
            else func_002B6228(object, D_L11_001FF580[WORD(state, 0x54c)], WORD(path, 0) - 1, 0);
            func_002A7750(object, 22, -1);
            PLAY(object, 0x10, 0, 20);
        }
        break;
    case 28:
        if (!(3.5f <= func_00282E80(position, &D_00189EA0) || REAL(state, 0x20) <= 1.0f)) {
            WORD(state, 0x290) = 1;
            func_002B60B0(object, 0.000555555569f, 0.01666666754f, 0.001163552981f, 0.1047197729f);
            func_002A7750(object, 0x1b, -1);
            PLAY(object, 0x17, 0, 10);
            break;
        }
        if (func_00282E80(position, &D_00189EA0) < 2.5f) {
            angle = func_00283248(D_00189EA0.v[0] - REAL(object, 0x10), D_00189EA0.v[1] - REAL(object, 0x14));
            if (func_00283C80(REAL(object, 0xf8), angle) < 0.3490659f) {
                PLAY(object, 0x11, 0, 10);
            begin_strike:
                func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.001163552981f, 0.1047197729f);
                func_002A7750(object, 0x22, 2);
                break;
            }
        }
        if (!(2.5f <= func_00282E80(position, &D_00189EA0))) {
        face_player:
            angle = func_00283248(D_00189EA0.v[0] - REAL(object, 0x10), D_00189EA0.v[1] - REAL(object, 0x14));
            func_002B50E0(object, position, angle);
            break;
        }
        if (WORD(state, 0x528) == 0) {
        approach_player:
            func_002B4FF0((char *)object, D_00189EA0.v, REAL(state, 0x298));
        } else if (func_L11_00425788((char *)object, (char *)&D_00189EA0, REAL(object, 0xf8), 7.0f, 0.25f, REAL(state, 0x298)) != 0 &&
                   BYTE(object, 0x21) <= D_L11_001B35B8 && func_002A8508(BYTE(object, 0x21), -1) > 1) {
            ids = D_L11_001FC420[BYTE(object, 0x21)];
            do {
                id = *ids;
                linked = (char *)(D_L11_001B359C + (id & 0x7fff) * 0x100);
                other_state = POINTER(linked, 0x68);
                if (WORD(other_state, 0x294) == 0) {
                    distance = func_00282E80(linked + 0x10, &D_00189EA0);
                    other_angle = func_00282E80(position, &D_00189EA0);
                    if (distance < other_angle && REAL(other_state, 0x20) > 0.0f) {
                        WORD(other_state, 0x294) = 1;
                        WORD(state, 0x294) = 0;
                        PLAY(object, 14, 0, 10);
                        func_002A7750(object, 0x18, 3);
                    }
                    break;
                }
                ++ids;
            } while ((short)id >= 0);
        }
        break;
    case 29:
        linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
        other_state = POINTER(linked, 0x68);
        if (BYTE(linked, 0x20) != 5) {
            func_002AA458(linked + 0xf0, object + 0xf0, state + 0x550, 0.001163552981f, 0.002327105962f, 0.1047197729f);
            func_002833F0(linked + 0xc0, linked + 0xf0);
            REAL(linked, 0x18) += ((REAL(other_state, 0x5c) - 1.2f) - REAL(linked, 0x18)) * 0.11f;
        }
        func_L01_00321178((char *)object, linked + 0x10);
        if (func_00282E80(position, linked + 0x10) < 1.5f && BYTE(linked, 0x20) != 5) {
            BYTE(linked, 0x20) = 6;
            REAL(object, 0x10) = REAL(linked, 0x10);
            REAL(object, 0x14) = REAL(linked, 0x14);
            REAL(object, 0x18) = REAL(linked, 0x18) + 1.5f;
            REAL(state, 0x554) = REAL(linked, 0x18) + 0.75f;
            PLAY(object, 0x1f, 0, 25);
            func_002A7750(object, 0x26, 7);
            WORD(state, 0x584) = 0;
            BYTE(object, 0xbc) = 1;
        }
        break;
    case 32:
        linked = (char *)(D_L11_001B359C + WORD(state, 0x580) * 0x100);
        func_L01_00321178((char *)object, linked + 0x10);
        if (func_00282E80(position, linked + 0x10) < 0.25f) {
            if (func_00282E80(position, &D_00189EA0) < 8.0f) {
                WORD(state, 0x290) = 1;
                PLAY(object, 0x15, 0, 10);
                func_002A7750(object, 0x19, -1);
            } else {
                WORD(state, 0x290) = 1;
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x1a, 3);
            }
            if (WORD(state, 0x294) != 0) {
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x1c, 2);
            }
            func_L00_003294F0((unsigned char *)linked, 5);
        }
        break;
    case 38:
        linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
        func_002AA3A8((float *)(linked + 0x18), (float *)(state + 0x550), REAL(state, 0x554),
                     0.0002777777845f, 0.001666666707f, 0.03333333507f);
        REAL(object, 0x18) = REAL(linked, 0x18) + 1.5f;
        if (func_00282C48(REAL(linked, 0x18) - REAL(state, 0x554)) < 0.1f) {
            PLAY(object, 0x20, 0, 5);
            func_002A7750(object, 0x27, -1);
            PLAY(linked, 1, 0, 5);
        }
        angle = func_00283248(D_00189EA0.v[0] - REAL(object, 0x10), D_00189EA0.v[1] - REAL(object, 0x14));
        if (func_00283C80(REAL(object, 0xf8), angle) < 0.26179942f && BYTE(linked, 0x43) != 1) {
            func_002A7470(linked, 1, 0, 5);
            PLAY(object, 0x20, 0, 5);
            break;
        }
        if (BYTE(linked, 0x42) != 1) break;
        goto test_projectile;
    case 39:
        linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
    test_projectile:
        if (func_002AEB60(linked, 6.0f) != 0 || func_002AEB60(linked, 12.0f) != 0 || func_002AEB60(linked, 0.0f) != 0) {
            kind = 1;
        } else {
            if (func_002AEB60(linked, 3.0f) == 0 && func_002AEB60(linked, 9.0f) == 0 && func_002AEB60(linked, 15.0f) == 0) break;
            kind = 0;
        }
        func_0029FCC0(linked, kind, (char *)&offset);
        func_00282CF0(&side, &D_00189EF0, &offset);
        func_00282F20(&side, &side, 0.5f);
        goto spawn_projectile;
    case 40:
        if (WORD(state, 0x564) == -1) break;
        func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.001939254929f, 0.005817765370f);
        path = D_L11_001FF580[WORD(state, 0x564)] + WORD(state, 0x568) * 0x10;
        linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
        angle = func_00283248(REAL(path, 0x10) - REAL(object, 0x10), REAL(path, 0x14) - REAL(object, 0x14));
        func_002B50E0(object, position, angle);
        REAL(object, 0x10) = REAL(linked, 0x10);
        REAL(object, 0x14) = REAL(linked, 0x14);
        REAL(object, 0x18) = REAL(linked, 0x18) + 1.5f;
        func_002833F0(linked + 0xc0, object + 0xf0);
        path = D_L11_001FF580[WORD(state, 0x564)] + WORD(state, 0x568) * 0x10;
        angle = func_00283248(REAL(path, 0x10) - REAL(object, 0x10), REAL(path, 0x14) - REAL(object, 0x14));
        if (func_00283C80(REAL(object, 0xf8), angle) <= 0.087266475f) {
            ++WORD(state, 0x568);
            if (WORD(state, 0x568) > 1) WORD(state, 0x568) = 0;
            if (BYTE(object, 0x42) == 0x20 && UHALF(object, 0x96) > 120) {
                PLAY(object, 0x1f, 0, 10);
                func_002A7470(linked, 0, 0, 10);
            }
        }
        if (WORD(state, 0x584) != 0) {
            func_0026FEB8(D_L11_001B0FC8);
            PLAY(object, 0x20, 0, 5);
            func_002A7470(linked, 1, 0, 5);
            WORD(state, 0x584) = 0;
            UHALF(object, 0x96) = 0;
        }
        if (BYTE(object, 0x42) != 0x20) break;
        if (func_002AEB60(linked, 6.0f) != 0 || func_002AEB60(linked, 12.0f) != 0 || func_002AEB60(linked, 0.0f) != 0) {
            kind = 1;
        } else {
            if (func_002AEB60(linked, 3.0f) == 0 && func_002AEB60(linked, 9.0f) == 0 && func_002AEB60(linked, 15.0f) == 0) break;
            kind = 0;
        }
        func_0029FCC0(linked, kind, (char *)&offset);
        distance = func_00282E80(&offset, &D_00189EF0);
        angle = func_00283248(distance, D_00189EF0.v[2] - offset.v[2]);
        func_002AF000(side.v, 0.5f, REAL(object, 0xf8), angle);
    spawn_projectile:
        func_L11_00450328(linked, &side, &offset, 0, (float)BYTE(state, 0x36));
        break;
    case 24:
        WORD(state, 0x290) = 0;
        angle = func_00283248(D_00189EA0.v[0] - REAL(object, 0x10), D_00189EA0.v[1] - REAL(object, 0x14));
        func_002B50E0(object, position, angle);
        if ((BYTE(object, 0x60) & 2) == 0 && WORD(state, 0x578) == 0 && BYTE(object, 0x42) != 15) break;
        if (func_00282E80(position, &D_00189EA0) < 8.0f) {
            WORD(state, 0x290) = 1;
            PLAY(object, 0x15, 0, 10);
            func_002A7750(object, 0x19, -1);
        } else {
            WORD(state, 0x290) = 1;
            PLAY(object, 15, 0, 10);
            func_002A7750(object, 0x1a, 3);
        }
        if (WORD(state, 0x294) != 0) {
            PLAY(object, 15, 0, 10);
            func_002A7750(object, 0x1c, 2);
        }
        break;
    case 31:
        func_L01_00321178((char *)object, POINTER(state, 0x274) + 0x10);
        if (!(2.1f <= func_00282E80(position, POINTER(state, 0x274) + 0x10))) {
            PLAY(object, 0, 0, 20);
            func_002A7750(object, 0x21, -1);
        }
        break;
    case 33:
        linked = POINTER(state, 0x274);
        func_002A7CA0((struct family_27f9_object *)object, (float *)(state + 0x27c), REAL(linked, 0xf8),
                     0.003f, 0.03f, 0.1047197729f);
        func_00282CF0(&offset, linked + 0x10, position);
        func_00282F20(&offset, &offset, 0.1000000089f);
        func_00282CC0(position, position, &offset);
        if (func_00282E80(position, POINTER(state, 0x274) + 0x10) < 0.05f) {
            func_002A7750(object, 1, 5);
            linked = POINTER(state, 0x274);
            QUAD(object, 0x10) = QUAD(linked, 0x10);
            QUAD(object, 0xf0) = QUAD(linked, 0xf0);
            WORD(object, 0x98) = 0;
            UHALF(object, 0x34) &= 0xafff;
            other_state = POINTER(linked, 0x68);
            WORD(other_state, 0x2c8) = 0;
            POINTER(other_state, 0x27c) = (char *)object;
            POINTER(state, 0x280) = func_0029EFD0(0x911);
            if (POINTER(state, 0x280) != 0) {
                BYTE(POINTER(state, 0x280), 0x30) = BYTE(object, 0x30);
                BYTE(POINTER(state, 0x280), 0x31) = 0;
                func_002A0F48(POINTER(state, 0x280));
                QUAD(POINTER(state, 0x280), 0x10) = QUAD(object, 0x10);
                REAL(POINTER(state, 0x280), 0x18) += 0.75f;
            }
            WORD(state, 0x26c) = 1;
        }
        break;
    case 25:
        func_002A7E08((struct family_27f9_object *)object, (float *)D_0018C0B0, (float *)(state + 0x27c), 0.001f, 0.01f, 0.1f);
        if (func_00282E80(position, &D_00189EA0) > 12.0f) {
            PLAY(object, 15, 0, 10);
            func_002A7750(object, 0x1a, -1);
        }
        if (func_00282E80(position, &D_00189EA0) < 2.5f) {
            PLAY(object, 0x11, 0, 10);
            func_002A7750(object, 0x22, -1);
        }
        if (func_002A77E0(3) == 1 && (BYTE(object, 0x60) & 2) != 0) {
            PLAY(object, 0x19, 0, 10);
            if (func_002A77E0(3) == 1) PLAY(object, 0x18, 0, 10);
            func_002A7750(object, 0x18, 3);
        }
        break;
    case 26:
        if (WORD(state, 0x528) == 0) {
            func_002B4FF0((char *)object, D_00189EA0.v, REAL(state, 0x298));
        } else if (func_L11_00425788((char *)object, (char *)&D_00189EA0, REAL(object, 0xf8), 7.0f, 0.25f, REAL(state, 0x298)) != 0) {
            PLAY(object, 0x15, 0, 10);
            func_002A7750(object, 0x19, -1);
        }
        if (!(8.0f <= func_00282E80(position, &D_00189EA0))) {
            PLAY(object, 0x15, 0, 10);
            func_002A7750(object, 0x19, -1);
        }
        break;
    case 27:
        if (func_00282E80(position, &D_00189EA0) < 2.5f) {
            angle = func_00283248(D_00189EA0.v[0] - REAL(object, 0x10), D_00189EA0.v[1] - REAL(object, 0x14));
            if (func_00283C80(REAL(object, 0xf8), angle) < 0.3490659f) {
                PLAY(object, 0x11, 0, 6);
                goto begin_strike;
            }
        }
        if (func_00282E80(position, &D_00189EA0) < 2.5f) goto face_player;
        if (func_00282E80(position, &D_00189EA0) <= 5.0f) {
            func_002B60B0(object, 0.000555555569f, 0.01666666754f, 0.001163552981f, 0.1047197729f);
            goto approach_player;
        }
        func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.001163552981f, 0.1047197729f);
        PLAY(object, 15, 0, 10);
        func_002A7750(object, 0x1c, -1);
        break;
    case 30:
        if (func_00282E80(position, &D_00189EA0) < 2.5f) {
            PLAY(object, 0x11, 0, 2);
            func_002A7750(object, 0x22, -1);
            WORD(state, 0x284) = -1;
            REAL(state, 0x164) = 0.0008333333535f;
        } else {
            REAL(state, 0x164) = 0.004166666884f;
            if (func_002B6120((char *)object, D_L11_001FF580[WORD(state, 0x284)]) != 0) {
                if (WORD(state, 0x294) == 1) {
                    PLAY(object, 15, 0, 10);
                    func_002A7750(object, 0x1c, 2);
                } else {
                    WORD(state, 0x290) = 1;
                    if (func_002A77E0(3) == 1) {
                        PLAY(object, 14, 0, 10);
                        func_002A7750(object, 0x18, 3);
                    } else {
                        PLAY(object, 15, 0, 10);
                        func_002A7750(object, 0x1a, 3);
                    }
                }
                WORD(state, 0x284) = -1;
            }
        }
        break;
    case 34:
        WORD(state, 0x290) = 0;
        distance = func_0029F530((char *)object);
        if (!(BYTE(object, 0x42) != 0x11 || distance < 10.0f || 15.0f < distance)) {
            func_0029FCC0((char *)object, 2, (char *)&offset);
            side.v[0] = func_00283180(REAL(object, 0xf8)) * 0.5f;
            side.v[1] = func_00283198(REAL(object, 0xf8)) * 0.5f;
            side.v[2] = 0.0f;
            func_00282CC0(&offset, &offset, &side);
            func_002A8C28(object, &offset, 1, 0, 1, 0, 0.4f, REAL(state, 0x28c), 1.0f);
            side.v[0] = func_00283180(REAL(object, 0xf8));
            side.v[1] = func_00283198(REAL(object, 0xf8));
            side.v[2] = 0.0f;
            func_00282CC0(&offset, &offset, &side);
            func_002A8C28(object, &offset, 1, 0, 1, 0, 0.4f, REAL(state, 0x28c), 1.0f);
        } else REAL(object, 0x48) = 1.0f;
        if ((BYTE(object, 0x60) & 2) == 0) break;
        PLAY(object, 0x22, 0, 10);
        if (func_002A77E0(2) == 1) PLAY(object, 14, 0, 10);
        func_002A7750(object, 0x23, -1);
        if (BYTE(object, 0x95) != 2) {
            func_002A7750(object, 0x19, -1);
            PLAY(object, 0x15, 0, 10);
        }
        break;
    case 35:
        if ((BYTE(object, 0x60) & 2) != 0) {
            distance = func_00282E80(position, &D_00189EA0);
            PLAY(object, 15, 0, 10);
            func_002A7750(object, 0x1c, -1);
        }
        break;
    default:
        break;
    }
    func_L11_00425A50((char *)object);
    if (func_00282C48(REAL(object, 0x18) - old_z) < 0.005f) REAL(object, 0x18) = old_z;
}
