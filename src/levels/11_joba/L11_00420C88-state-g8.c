/* func_L11_00420C88: the Joba NPC state machine (two switches over the object's
 * mode bytes 0x95 and 0x20). Its own unit for the -frac2-qcopy profile
 * (config/cflags.txt). Control-flow notes: each arm that ends in a
 * func_002A7750 call has its own call and break, so jump2 cross-jumps only the
 * shared call; float compares are strict (x < c); case-local pointers keep
 * object, state and path in $s2, $s3 and $s1. func_002B60B0 returns nothing
 * (src/game/002B60B0.c; no retail call reads $v0), so the index load after it
 * may take $v0 (cases 14, 15 and 22).
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
extern void func_002B60B0(unsigned char *, float, float, float, float);
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
extern int D_L11_001CAE40 __attribute__((nosda));
/* One hero-state object: retail retains its common base across cases. */
typedef struct {
    unsigned char unknown0000[0x80];
    Vector position;
    unsigned char unknown0090[0x40];
    Vector aim;
    unsigned char unknown00E0[0x1168];
    int state;
    unsigned char unknown124C[0x1044];
    char *moby;
    int mode;
} Hero20C88;
extern Hero20C88 D_00189E20;
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
extern int func_002B1C20(void *, void *);
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
extern int func_002A7EA0(void *, void *, void *, float, float, float, float, int);
extern int func_L04_0033D4B0(unsigned char *);
extern int func_L01_00321178(char *, char *);
extern float func_002A7E08(struct family_27f9_object *, float *, float *, float, float, float);
extern float func_002A7CA0(struct family_27f9_object *, float *, float, float, float, float);
extern int func_002B4FF0(char *, float *, float);
extern int func_L11_00425788(char *, char *, float, float, float, float);
extern float func_00282C48(float);
extern int func_002AEB60(char *, float);
extern void func_002AF000(float *, float, float, float);
extern char *func_L11_00450328(void *, void *, void *, int, float);
extern int func_002A8C28(void *, void *, int, float, float, float, int, int, int);
extern void func_L11_00425A50(char *);

/* A group's ID list entry names an object; bit 15 only marks the list's last entry. */
static inline int group_entry_id(unsigned short *entry)
{
    return *entry & 0x7fff;
}

static inline char *moby_at(int id)
{
    return (char *)(D_L11_001B359C + id * 0x100);
}

static inline signed char moby_state(char *moby)
{
    return SIGNED_BYTE(moby, 0x20);
}

static inline short moby_class(char *moby)
{
    return HALF(moby, 0xaa);
}

static inline char *moby_vars(char *moby)
{
    return POINTER(moby, 0x68);
}

static inline int rider_kind(char *moby)
{
    return WORD(moby_vars(moby), 0x540);
}

/* The guarded animation transition is repeated throughout both state machines. */
#define PLAY(p, animation, start, blend) \
    (BYTE((p), 0x43) != (animation) ? func_002A7470((p), (animation), (start), (blend)) : (void)0)

void func_L11_00420C88(unsigned char *object)
{
    Vector offset, side, point;
    char *state, *path;
    int index, kind;
    float old_z, distance, angle, other_angle, pitch, limit;
    int flags;

    if (D_L11_001CAE40 != 0) return;
    if (D_00189E20.mode == 0x6f && BYTE(object, 0x95) != 4) return;
    old_z = REAL(object, 0x18);
    state = POINTER(object, 0x68);
    if (func_L11_00424A60(object) != 0) {
        func_0029F338(object);
        return;
    }
    switch (BYTE(object, 0x95)) {
    case 10:
        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 6.0f) {
            limit = 1.5707965f;
            angle = func_00283248(REAL(D_00189E20.moby, 0x10) - REAL(object, 0x10), REAL(D_00189E20.moby, 0x14) - REAL(object, 0x14));
            angle = func_00283BE0(angle, REAL(object, 0xf8));
            if (func_002B38B8(object) != 0) angle = -angle;
            if (angle > limit) angle = limit;
            else if (angle < -limit) angle = -limit;
            REAL(state, 0x308) = angle;
        }
        if (D_00189E20.state != 0x41) BYTE(object, 0x95) = 0;
        break;
    case 0: {
        char *linked;

        if (func_002B3890(object) != 0)
            func_002B60B0(object, 0.001527777873f, 0.04583333433f, 0.001163552981f, 0.1047197729f);
        if (HALF(state, 0x264) == 2) {
            if (WORD(state, 0x284) != -1) {
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x1e, 2);
            }
            if (WORD(state, 0x548) != -1) {
                linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
                if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) {
                    PLAY(object, 15, 0, 10);
                    func_002A7750(object, 0x1d, 2);
                    BYTE(linked, 0x20) = 6;
                    BYTE(object, 0xbc) = 1;
                    break;
                }
                if (WORD(state, 0x294) == 1) {
                    if (BYTE(object, 0x43) != 0x22)
                        func_002A7470(object, 0x22, 0, func_002A7820(7, 20));
                    func_002A7750(object, 0x18, 2);
                } else {
                    if (WORD(state, 0x570) != 0) {
                        PLAY(object, 0x21, 0, 10);
                        func_002A7750(object, 0x18, 3);
                    } else {
                        WORD(state, 0x290) = 1;
                        PLAY(object, 14, 0, 5);
                        func_002A7750(object, 0x18, 3);
                    }
                }
            } else {
                if (WORD(state, 0x580) != -1) {
                    PLAY(object, 15, 0, 10);
                    func_002A7750(object, 0x20, 2);
                } else {
                    if (WORD(state, 0x294) == 1) {
                        if (BYTE(object, 0x43) != 0x22)
                            func_002A7470(object, 0x22, 0, func_002A7820(7, 20));
                        func_002A7750(object, 0x18, 2);
                    } else {
                        if (WORD(state, 0x570) != 0) {
                            PLAY(object, 0x21, 0, 10);
                            func_002A7750(object, 0x18, 3);
                        } else {
                            WORD(state, 0x290) = 1;
                            PLAY(object, 14, 0, 5);
                            func_002A7750(object, 0x18, 3);
                        }
                    }
                    if (WORD(state, 0x270) == -1) break;
                    WORD(state, 0x274) = D_L11_001B359C + WORD(state, 0x270) * 0x100;
                    func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.003393696155f, 0.2617994249f);
                    PLAY(object, 15, 0, 10);
                    func_002A7750(object, 0x1f, 2);
                }
            }
            break;
        } else {
            if (HALF(state, 0x266) == 0) break;
            if (WORD(state, 0x558) != -1 && WORD(state, 0x560) == 1) {
                if (BYTE(object, 0x43) != 0x18)
                    func_002A7470(object, 0x18, 0, func_002A7820(5, 15));
                func_002A7750(object, 6, -1);
            } else if (WORD(state, 0x558) != -1 && WORD(state, 0x560) > 1) {
                if (BYTE(object, 0x43) != 15)
                    func_002A7470(object, 15, 0, func_002A7820(5, 15));
                func_002A7750(object, 7, -1);
                func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.003393696155f, 0.2617994249f);
            } else {
                BYTE(object, 0x95) = 1;
                PLAY(object, 0x18, 0, 20);
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
                } else if (WORD(state, 0x570) != 0) {
                    PLAY(object, 0x21, 0, 5);
                    func_002A7750(object, 0x18, 3);
                } else {
                    WORD(state, 0x290) = 1;
                    PLAY(object, 14, 0, 10);
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
    }
    case 1: {
        char *linked;

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
            float nearest_distance;
            int node, nearest;

            PLAY(object, 15, 0, 10);
            nearest_distance = 100.0f;
            func_002A7750(object, 0x1e, 2);
            node = 0;
            nearest = 0;
            for (; node < WORD(D_L11_001FF580[WORD(state, 0x284)], 0); ++node) {
                float d = func_00282E80(((char *)object + 0x10), D_L11_001FF580[WORD(state, 0x284)] + 0x10 + node * 0x10);
                if (d < nearest_distance) {
                    nearest_distance = d;
                    nearest = node;
                }
            }
            func_002B6228(object, D_L11_001FF580[WORD(state, 0x284)], -1, nearest);
        }
        if (WORD(state, 0x548) != -1) {
            linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
            if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) {
                WORD(state, 0x178) &= ~0x10;
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x1d, 2);
                BYTE(linked, 0x20) = 6;
                BYTE(object, 0xbc) = 1;
                break;
            }
            if (WORD(state, 0x294) == 1) {
                if (BYTE(object, 0x43) != 0x19) {
                    index = func_002A77E0(4);
                    func_002A7470(object, 0x19, index, func_002A7820(7, 20));
                }
                func_002A7750(object, 0x18, 2);
            } else {
                WORD(state, 0x290) = 1;
                PLAY(object, 14, 0, 40);
                func_002A7750(object, 0x18, 3);
            }
        } else {
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
        }
        break;
    }
    case 2: {
        char *linked;

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
    }
    case 8: {
        char *linked;

        if (D_00189E20.mode != 0x31) {
            if (WORD(state, 0x548) != -1) {
                linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
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
    }
    case 4:
        if (REAL(state, 0x20) > 0.0f) {
            func_002B50E0(object, ((char *)object + 0x10),
                          func_00283248(D_00189E20.position.v[0] - REAL(object, 0x10), D_00189E20.position.v[1] - REAL(object, 0x14)));
        }
        flags = func_002B1C20(object, state + 0x60);
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
            if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 2.5f) {
                angle = func_00283248(D_00189E20.position.v[0] - REAL(object, 0x10), D_00189E20.position.v[1] - REAL(object, 0x14));
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
            if (D_00189E20.mode == 0x31 && WORD(state, 0x574) != -1) {
                if (BYTE(object, 0x43) != 15) func_002A7470(object, 15, 0, func_002A7820(5, 15));
                func_002A7750(object, 8, 8);
            }
        } else if (WORD(state, 0x558) != -1) {
            WORD(state, 0x178) &= ~0x10;
            if (BYTE(object, 0x43) != 15) func_002A7470(object, 15, 0, func_002A7820(5, 15));
            func_002A7750(object, 7, 1);
            func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.003393696155f, 0.2617994249f);
        } else {
            PLAY(object, 0x18, 0, 10);
            func_002A7750(object, 0x13, 1);
            HALF(state, 0x260) = func_002A7820(580, 600);
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
        if (D_00189E20.mode == 0x31 && WORD(state, 0x574) != -1) {
            if (BYTE(object, 0x43) != 15) func_002A7470(object, 15, 0, func_002A7820(5, 15));
            func_002A7750(object, 9, 8);
            func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.003393696155f, 0.2617994249f);
        }
        break;
    case 5: {
        char *linked;

        if (POINTER(state, 0x278) != 0) func_002AF1D0(object, POINTER(state, 0x278), 1, 0);
        linked = POINTER(state, 0x274);
        QUAD(object, 0x10) = QUAD(linked, 0x10);
        QUAD(object, 0xf0) = QUAD(linked, 0xf0);
        {
            char *carrier = POINTER(state, 0x280);
            QUAD(carrier, 0x10) = QUAD(object, 0x10);
            QUAD(carrier, 0xf0) = QUAD(object, 0xf0);
            QUAD(carrier, 0x10) = QUAD(object, 0x10);
            REAL(carrier, 0x18) += 0.65f;
        }
        if (WORD(state, 0x26c) == 0 || POINTER(state, 0x274) == 0 ||
            BYTE(POINTER(state, 0x274), 0x20) == 0xfe || BYTE(POINTER(state, 0x274), 0x20) == 0xfd) {
            func_002AC728(object, POINTER(state, 0x278) + 0x10, -1, 0.5f, 3.0f);
            func_0029F338(POINTER(state, 0x278));
            POINTER(state, 0x278) = 0;
            func_0029F338(POINTER(state, 0x280));
            WORD(POINTER(POINTER(state, 0x274), 0x68), 0x27c) = 0;
            func_002A7750(object, 2, 6);
        } else {
            if (func_L11_00420C38(object) == 0) break;
            func_002AC728(object, POINTER(state, 0x278) + 0x10, -1, 0.5f, 3.0f);
            func_0029F338(POINTER(state, 0x278));
            POINTER(state, 0x278) = 0;
            func_0029F338(POINTER(state, 0x280));
            WORD(POINTER(POINTER(state, 0x274), 0x68), 0x27c) = 0;
            PLAY(object, 9, 0, 0);
            func_002A7750(object, 3, 6);
        }
        break;
    }
    case 6:
        if (func_002B3890(object) != 0 && POINTER(state, 0x29c) == 0) {
            POINTER(state, 0x29c) = func_0029EFD0(0x9ac);
            if (POINTER(state, 0x29c) != 0) {
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
            } else {
                func_0029F338(object);
                return;
            }
        }
        break;
    case 7: {
        char *other_state;
        char *linked;

        linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
        WORD(state, 0x290) = 0;
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
            func_002B50E0(object, ((char *)object + 0x10), func_00283248(D_00189E20.position.v[0] - REAL(object, 0x10), D_00189E20.position.v[1] - REAL(object, 0x14)));
            distance = func_00282E80(((char *)object + 0x10), &D_00189E20.aim);
            pitch = func_00283248(distance, D_00189E20.aim.v[2] - REAL(object, 0x18));
            if (pitch < -0.52359885f) pitch = -0.52359885f;
            else if (pitch > 0.52359885f) pitch = 0.52359885f;
            REAL(other_state, 0xb4) = -pitch;
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
    }
    case 9:
        distance = func_002A89A8(((char *)object + 0x10), 0, 0.5f);
        func_002AA3A8((float *)(object + 0x18), (float *)(state + 0x550), distance,
                     0.000555555569f, 0.0002777777845f, 0.3133333325f);
        break;
    default:
        break;
    }
    switch (BYTE(object, 0x20)) {
    case 2:
    case 3: {
        float range;

        if ((BYTE(object, 0x60) & 2) != 0) {
            UHALF(object, 0x34) |= 0x5000;
            WORD(object, 0x98) = WORD(POINTER(object, 0x24), 0x10);
            func_002A7750(object, 0x13, 1);
            if (HALF(state, 0x260) < 300) HALF(state, 0x260) = func_002A7820(480, 600);
            PLAY(object, 13, 0, 10);
            if (REAL(state, 0x20) <= 0.0f) REAL(state, 0x20) = 0.1f;
        }
        range = func_0029F530((char *)object);
        if (range >= 10.0f) REAL(object, 0x18) = func_002A89A8(((char *)object + 0x10), 0, 0.5f);
        if (range >= 1.5f && range <= 17.0f) {
            offset.v[0] = func_00283180(REAL(object, 0xf8) + 3.141593f) * 0.15f;
            offset.v[1] = func_00283198(REAL(object, 0xf8) + 3.141593f) * 0.15f;
            offset.v[2] = 0.0f;
            side.v[0] = func_00283180(REAL(object, 0xf8) + 1.5707965f) * 0.05f;
            side.v[1] = func_00283198(REAL(object, 0xf8) + 1.5707965f) * 0.05f;
            side.v[2] = 0.0f;
            point.word = QUAD(object, 0x10);
            func_00282CC0(&point, ((char *)object + 0x10), &side);
            func_00282CC0(&point, ((char *)object + 0x10), &offset);
            func_002A7EA0(object, ((char *)object + 0x10), &point, 0.5f, 0.55f, 0.5f, 0.52359885f, 0);
        }
        break;
    }
    case 5: {
        char *target = POINTER(state, 0x55c);

        if (target == 0) break;
        if (WORD(state, 0x540) == 3 && BYTE(object, 0x95) != 10) {
            limit = 1.5707965f;
            angle = func_00283248(REAL(target, 0x10) - REAL(object, 0x10), REAL(target, 0x14) - REAL(object, 0x14));
            angle = func_00283BE0(angle, REAL(object, 0xf8));
            if (func_002B38B8(object) != 0) angle = -angle;
            if (angle > limit) angle = limit;
            else if (angle < -limit) angle = -limit;
            REAL(state, 0x308) = angle;
        }
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
                unsigned short *ids;
                char *linked;

                ids = D_L11_001FC420[BYTE(object, 0x21)];
                for (;;) {
                    linked = moby_at(group_entry_id(ids));
                    if (moby_state(linked) >= 0 && moby_class(linked) == 0xcf5 &&
                        rider_kind(linked) == 1)
                        break;
                    if (*(short *)ids++ < 0) goto partner_done;
                }
                POINTER(state, 0x55c) = linked;
            partner_done:;
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
        if (func_00282E80(((char *)object + 0x10), D_L11_001FF580[WORD(state, 0x574)] + 0x10) < 0.5f) {
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
        func_002B50E0(object, ((char *)object + 0x10),
                      func_00283248(REAL(POINTER(state, 0x55c), 0x10) - REAL(object, 0x10), REAL(POINTER(state, 0x55c), 0x14) - REAL(object, 0x14)));
        angle = func_00283248(REAL(POINTER(state, 0x55c), 0x10) - REAL(object, 0x10), REAL(POINTER(state, 0x55c), 0x14) - REAL(object, 0x14));
        if (func_00283C80(REAL(object, 0xf8), angle) < 0.087266475f) func_002A7750(object, 5, -1);
        break;
    case 14:
        func_002B60B0(object, 0.001527777873f, 0.04583333433f, 0.003781547071f, 0.2967060208f);
        if (func_002B6120((char *)object, D_L11_001FF580[WORD(state, 0x54c)]) != 0) {
            func_002A7750(object, 0x11, -1);
            PLAY(object, 13, 0, 20);
        }
        break;
    case 15: {
        float turn_scale = 1.0f;
        float turned;

        func_002B60B0(object, 0.001527777873f, 0.04583333433f, 0.007563094143f, 0.5934120417f);
        if (func_002B6120((char *)object, D_L11_001FF580[WORD(state, 0x54c)]) != 0) {
            path = D_L11_001FF580[WORD(state, 0x54c)];
            distance = func_00282E80(((char *)object + 0x10), path + 0x10);
            other_angle = func_00282E80(((char *)object + 0x10), path + WORD(path, 0) * 0x10);
            if (other_angle < distance) func_002B6228(object, D_L11_001FF580[WORD(state, 0x54c)], 0, WORD(path, 0) - 1);
            else func_002B6228(object, D_L11_001FF580[WORD(state, 0x54c)], WORD(path, 0) - 1, 0);
            if (func_002A77E0(5) == 1) {
                PLAY(object, 0x19, 0, 15);
                func_002A7750(object, 0x10, -1);
            }
        }
        limit = 1.5707965f;
        angle = func_00283248(D_00189E20.position.v[0] - REAL(object, 0x10), D_00189E20.position.v[1] - REAL(object, 0x14));
        angle = func_00283BE0(angle, REAL(object, 0xf8));
        if (func_002B38B8(object) != 0) angle = func_00283B98(angle, 3.141593f);
        if (angle > limit) angle = limit;
        else if (angle < -limit) angle = -limit;
        turned = func_00283B98(angle * turn_scale, REAL(state, 0x308));
        REAL(state, 0x308) = turned;
        if (turned > limit) REAL(state, 0x308) = limit;
        else if (turned < -limit) REAL(state, 0x308) = -limit;
        break;
    }
    case 16:
        func_002B50E0(object, ((char *)object + 0x10), func_00283248(D_00189E20.position.v[0] - REAL(object, 0x10), D_00189E20.position.v[1] - REAL(object, 0x14)));
        if ((BYTE(object, 0x60) & 2) != 0) {
            func_002A7750(object, 15, -1);
            PLAY(object, 0x10, 0, 20);
        }
        break;
    case 17:
        if ((BYTE(object, 0x60) & 2) != 0) {
            path = D_L11_001FF580[WORD(state, 0x54c)];
            distance = func_00282E80(((char *)object + 0x10), path + 0x10);
            other_angle = func_00282E80(((char *)object + 0x10), path + WORD(path, 0) * 0x10);
            if (other_angle < distance) func_002B6228(object, D_L11_001FF580[WORD(state, 0x54c)], 0, WORD(path, 0) - 1);
            else func_002B6228(object, D_L11_001FF580[WORD(state, 0x54c)], WORD(path, 0) - 1, 0);
            func_002A7750(object, 14, -1);
            PLAY(object, 0x10, 0, 20);
        }
        break;
    case 19:
        func_002A7E08((struct family_27f9_object *)object, (float *)D_00189E20.moby, (float *)(state + 0x27c),
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
        func_002A7E08((struct family_27f9_object *)object, (float *)D_00189E20.moby, (float *)(state + 0x27c),
                     0.001f, 0.01f, 0.1f);
        func_002B60B0(object, 0.000555555569f, 0.01666666754f, 0.001163552981f, 0.1047197729f);
        func_L01_00321178((char *)object, state + 0x110);
        if (func_00282E80(((char *)object + 0x10), state + 0x110) < 2.0f) {
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
            distance = func_00282E80(((char *)object + 0x10), path + 0x10);
            other_angle = func_00282E80(((char *)object + 0x10), path + WORD(path, 0) * 0x10);
            if (other_angle < distance) func_002B6228(object, D_L11_001FF580[WORD(state, 0x56c)], 0, WORD(path, 0) - 1);
            else func_002B6228(object, D_L11_001FF580[WORD(state, 0x56c)], WORD(path, 0) - 1, 0);
            func_002A7750(object, 22, -1);
            PLAY(object, 0x10, 0, 20);
        }
        break;
    case 28: {
        char *other_state;

        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 3.5f && REAL(state, 0x20) > 1.0f) {
            WORD(state, 0x290) = 1;
            func_002B60B0(object, 0.000555555569f, 0.01666666754f, 0.001163552981f, 0.1047197729f);
            func_002A7750(object, 0x1b, -1);
            PLAY(object, 0x17, 0, 10);
            break;
        }
        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 2.5f) {
            angle = func_00283248(D_00189E20.position.v[0] - REAL(object, 0x10), D_00189E20.position.v[1] - REAL(object, 0x14));
            if (func_00283C80(REAL(object, 0xf8), angle) < 0.3490659f) {
                PLAY(object, 0x11, 0, 10);
                func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.001163552981f, 0.1047197729f);
                func_002A7750(object, 0x22, 2);
                break;
            }
        }
        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 2.5f) {
            func_002B50E0(object, ((char *)object + 0x10), func_00283248(D_00189E20.position.v[0] - REAL(object, 0x10), D_00189E20.position.v[1] - REAL(object, 0x14)));
            break;
        }
        if (WORD(state, 0x528) == 0) {
            func_002B4FF0((char *)object, D_00189E20.position.v, REAL(state, 0x298));
        } else if (func_L11_00425788((char *)object, (char *)&D_00189E20.position, REAL(object, 0xf8), 7.0f, 0.25f, REAL(state, 0x298)) != 0 &&
                   BYTE(object, 0x21) <= D_L11_001B35B8 && func_002A8508(BYTE(object, 0x21), -1) > 1) {
            unsigned short *ids;
            unsigned int id;

            ids = D_L11_001FC420[BYTE(object, 0x21)];
            do {
                char *partner;

                id = *ids;
                partner = (char *)(D_L11_001B359C + (id & 0x7fff) * 0x100);
                other_state = POINTER(partner, 0x68);
                if (WORD(other_state, 0x294) == 0) {
                    distance = func_00282E80(partner + 0x10, &D_00189E20.position);
                    other_angle = func_00282E80(((char *)object + 0x10), &D_00189E20.position);
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
    }
    case 29: {
        char *other_state;
        char *linked;

        linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
        other_state = POINTER(linked, 0x68);
        if (BYTE(linked, 0x20) != 5) {
            func_002AA458(linked + 0xf0, object + 0xf0, state + 0x550, 0.001163552981f, 0.002327105962f, 0.1047197729f);
            func_002833F0(linked + 0xc0, linked + 0xf0);
            REAL(linked, 0x18) += ((REAL(other_state, 0x5c) - 1.2f) - REAL(linked, 0x18)) * 0.11f;
        }
        func_L01_00321178((char *)object, linked + 0x10);
        if (func_00282E80(((char *)object + 0x10), linked + 0x10) < 1.5f && BYTE(linked, 0x20) != 5) {
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
    }
    case 32: {
        char *linked;

        linked = (char *)(D_L11_001B359C + WORD(state, 0x580) * 0x100);
        func_L01_00321178((char *)object, linked + 0x10);
        if (func_00282E80(((char *)object + 0x10), linked + 0x10) < 0.25f) {
            if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 8.0f) {
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
    }
    case 38: {
        char *linked;

        linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
        func_002AA3A8((float *)(linked + 0x18), (float *)(state + 0x550), REAL(state, 0x554),
                     0.0002777777845f, 0.001666666707f, 0.03333333507f);
        REAL(object, 0x18) = REAL(linked, 0x18) + 1.5f;
        if (func_00282C48(REAL(linked, 0x18) - REAL(state, 0x554)) < 0.1f) {
            PLAY(object, 0x20, 0, 5);
            func_002A7750(object, 0x27, -1);
            PLAY(linked, 1, 0, 5);
        }
        angle = func_00283248(D_00189E20.position.v[0] - REAL(object, 0x10), D_00189E20.position.v[1] - REAL(object, 0x14));
        if (func_00283C80(REAL(object, 0xf8), angle) < 0.26179942f && BYTE(linked, 0x43) != 1) {
            func_002A7470(linked, 1, 0, 5);
            PLAY(object, 0x20, 0, 5);
            break;
        }
        if (BYTE(linked, 0x42) != 1) break;
        if (func_002AEB60(linked, 6.0f) != 0 || func_002AEB60(linked, 12.0f) != 0 || func_002AEB60(linked, 0.0f) != 0) {
            func_0029FCC0(linked, 1, (char *)&offset);
            func_00282CF0(&side, &D_00189E20.aim, &offset);
            func_00282F20(&side, &side, 0.5f);
            func_L11_00450328(linked, &side, &offset, 0, (float)BYTE(state, 0x36));
            break;
        } else if (func_002AEB60(linked, 3.0f) != 0 || func_002AEB60(linked, 9.0f) != 0 || func_002AEB60(linked, 15.0f) != 0) {
            func_0029FCC0(linked, 0, (char *)&offset);
            func_00282CF0(&side, &D_00189E20.aim, &offset);
            func_00282F20(&side, &side, 0.5f);
            func_L11_00450328(linked, &side, &offset, 0, (float)BYTE(state, 0x36));
            break;
        }
        break;
    }
    case 39: {
        char *linked;

        linked = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
        if (func_002AEB60(linked, 6.0f) != 0 || func_002AEB60(linked, 12.0f) != 0 || func_002AEB60(linked, 0.0f) != 0) {
            func_0029FCC0(linked, 1, (char *)&offset);
            func_00282CF0(&side, &D_00189E20.aim, &offset);
            func_00282F20(&side, &side, 0.5f);
            func_L11_00450328(linked, &side, &offset, 0, (float)BYTE(state, 0x36));
            break;
        } else if (func_002AEB60(linked, 3.0f) != 0 || func_002AEB60(linked, 9.0f) != 0 || func_002AEB60(linked, 15.0f) != 0) {
            func_0029FCC0(linked, 0, (char *)&offset);
            func_00282CF0(&side, &D_00189E20.aim, &offset);
            func_00282F20(&side, &side, 0.5f);
            func_L11_00450328(linked, &side, &offset, 0, (float)BYTE(state, 0x36));
            break;
        }
        break;
    }
    case 40: {
        char *mount, *node, *next;

        if (WORD(state, 0x564) == -1) break;
        func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.001939254929f, 0.005817765370f);
        node = D_L11_001FF580[WORD(state, 0x564)] + WORD(state, 0x568) * 0x10;
        mount = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
        func_002B50E0(object, ((char *)object + 0x10), func_00283248(REAL(node, 0x10) - REAL(object, 0x10), REAL(node, 0x14) - REAL(object, 0x14)));
        REAL(object, 0x10) = REAL(mount, 0x10);
        REAL(object, 0x14) = REAL(mount, 0x14);
        REAL(object, 0x18) = REAL(mount, 0x18) + 1.5f;
        func_002833F0(mount + 0xc0, object + 0xf0);
        next = D_L11_001FF580[WORD(state, 0x564)] + WORD(state, 0x568) * 0x10;
        angle = func_00283248(REAL(next, 0x10) - REAL(object, 0x10), REAL(next, 0x14) - REAL(object, 0x14));
        if (func_00283C80(REAL(object, 0xf8), angle) <= 0.087266475f) {
            ++WORD(state, 0x568);
            if (WORD(state, 0x568) > 1) WORD(state, 0x568) = 0;
            if (BYTE(object, 0x42) == 0x20 && UHALF(object, 0x96) > 120) {
                PLAY(object, 0x1f, 0, 10);
                func_002A7470(mount, 0, 0, 10);
            }
        }
        if (WORD(state, 0x584) != 0) {
            func_0026FEB8(D_L11_001B0FC8);
            PLAY(object, 0x20, 0, 5);
            func_002A7470(mount, 1, 0, 5);
            WORD(state, 0x584) = 0;
            UHALF(object, 0x96) = 0;
        }
        if (BYTE(object, 0x42) != 0x20) break;
        if (func_002AEB60(mount, 6.0f) != 0 || func_002AEB60(mount, 12.0f) != 0 || func_002AEB60(mount, 0.0f) != 0) {
            func_0029FCC0(mount, 1, (char *)&offset);
            func_002AF000(side.v, 0.5f, REAL(object, 0xf8),
                          func_00283248(func_00282E80(&offset, &D_00189E20.aim), D_00189E20.aim.v[2] - offset.v[2]));
            func_L11_00450328(mount, &side, &offset, 0, (float)BYTE(state, 0x36));
        } else if (func_002AEB60(mount, 3.0f) != 0 || func_002AEB60(mount, 9.0f) != 0 || func_002AEB60(mount, 15.0f) != 0) {
            func_0029FCC0(mount, 0, (char *)&offset);
            func_002AF000(side.v, 0.5f, REAL(object, 0xf8),
                          func_00283248(func_00282E80(&offset, &D_00189E20.aim), D_00189E20.aim.v[2] - offset.v[2]));
            func_L11_00450328(mount, &side, &offset, 0, (float)BYTE(state, 0x36));
        }
        break;
    }
    case 24:
        WORD(state, 0x290) = 0;
        func_002B50E0(object, ((char *)object + 0x10), func_00283248(D_00189E20.position.v[0] - REAL(object, 0x10), D_00189E20.position.v[1] - REAL(object, 0x14)));
        if ((BYTE(object, 0x60) & 2) == 0 && WORD(state, 0x578) == 0 && BYTE(object, 0x42) != 15) break;
        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 8.0f) {
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
        if (func_00282E80(((char *)object + 0x10), POINTER(state, 0x274) + 0x10) < 2.1f) {
            PLAY(object, 0, 0, 20);
            func_002A7750(object, 0x21, -1);
        }
        break;
    case 33:
        func_002A7CA0((struct family_27f9_object *)object, (float *)(state + 0x27c), REAL(POINTER(state, 0x274), 0xf8),
                     0.003f, 0.03f, 0.1047197729f);
        func_00282CF0(&offset, POINTER(state, 0x274) + 0x10, ((char *)object + 0x10));
        func_00282F20(&offset, &offset, 0.1000000089f);
        func_00282CC0(((char *)object + 0x10), ((char *)object + 0x10), &offset);
        if (func_00282E80(((char *)object + 0x10), POINTER(state, 0x274) + 0x10) < 0.05f) {
            func_002A7750(object, 1, 5);
            {
                char *dock = POINTER(state, 0x274);

                QUAD(object, 0x10) = QUAD(dock, 0x10);
                QUAD(object, 0xf0) = QUAD(dock, 0xf0);
            }
            WORD(object, 0x98) = 0;
            UHALF(object, 0x34) &= 0xafff;
            {
                char *dock_state = POINTER(POINTER(state, 0x274), 0x68);

                POINTER(dock_state, 0x27c) = (char *)object;
                WORD(dock_state, 0x2c8) = 0;
            }
            POINTER(state, 0x280) = func_0029EFD0(0x911);
            if (POINTER(state, 0x280) != 0) {
                BYTE(POINTER(state, 0x280), 0x30) = BYTE(object, 0x30);
                BYTE(POINTER(state, 0x280), 0x31) = 0;
                func_002A0F48(POINTER(state, 0x280));
                {
                    char *carrier = POINTER(state, 0x280);

                    QUAD(carrier, 0x10) = QUAD(object, 0x10);
                    REAL(carrier, 0x18) += 0.75f;
                }
            }
            WORD(state, 0x26c) = 1;
        }
        break;
    case 25:
        func_002A7E08((struct family_27f9_object *)object, (float *)D_00189E20.moby, (float *)(state + 0x27c), 0.001f, 0.01f, 0.1f);
        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) > 12.0f) {
            PLAY(object, 15, 0, 10);
            func_002A7750(object, 0x1a, -1);
        }
        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 2.5f) {
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
        if (WORD(state, 0x528) != 0) {
            if (func_L11_00425788((char *)object, (char *)&D_00189E20.position, REAL(object, 0xf8), 7.0f, 0.25f, REAL(state, 0x298)) != 0) {
                PLAY(object, 0x15, 0, 10);
                func_002A7750(object, 0x19, -1);
            }
        } else {
            func_002B4FF0((char *)object, D_00189E20.position.v, REAL(state, 0x298));
        }
        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 8.0f) {
            PLAY(object, 0x15, 0, 10);
            func_002A7750(object, 0x19, -1);
        }
        break;
    case 27:
        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 2.5f) {
            angle = func_00283248(D_00189E20.position.v[0] - REAL(object, 0x10), D_00189E20.position.v[1] - REAL(object, 0x14));
            if (func_00283C80(REAL(object, 0xf8), angle) < 0.3490659f) {
                PLAY(object, 0x11, 0, 6);
                func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.001163552981f, 0.1047197729f);
                func_002A7750(object, 0x22, 2);
                break;
            }
        }
        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 2.5f) {
            func_002B50E0(object, ((char *)object + 0x10), func_00283248(D_00189E20.position.v[0] - REAL(object, 0x10), D_00189E20.position.v[1] - REAL(object, 0x14)));
            break;
        }
        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) > 5.0f) {
            func_002B60B0(object, 0.00388888898f, 0.1166666746f, 0.001163552981f, 0.1047197729f);
            PLAY(object, 15, 0, 10);
            func_002A7750(object, 0x1c, -1);
        } else {
            func_002B60B0(object, 0.000555555569f, 0.01666666754f, 0.001163552981f, 0.1047197729f);
            func_002B4FF0((char *)object, D_00189E20.position.v, REAL(state, 0x298));
        }
        break;
    case 30:
        if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 2.5f) {
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
    case 34: {
        float range;

        WORD(state, 0x290) = 0;
        range = func_0029F530((char *)object);
        if (BYTE(object, 0x42) == 0x11 && range >= 10.0f && range <= 15.0f) {
            func_0029FCC0((char *)object, 2, (char *)&offset);
            side.v[0] = func_00283180(REAL(object, 0xf8)) * 0.5f;
            side.v[1] = func_00283198(REAL(object, 0xf8)) * 0.5f;
            side.v[2] = 0.0f;
            func_00282CC0(&offset, &offset, &side);
            func_002A8C28(object, &offset, 1, 0.4f, REAL(state, 0x28c), 1.0f, 0, 1, 0);
            side.v[0] = func_00283180(REAL(object, 0xf8));
            side.v[1] = func_00283198(REAL(object, 0xf8));
            side.v[2] = 0.0f;
            func_00282CC0(&offset, &offset, &side);
            func_002A8C28(object, &offset, 1, 0.4f, REAL(state, 0x28c), 1.0f, 0, 1, 0);
        } else REAL(object, 0x48) = 1.0f;
        if ((BYTE(object, 0x60) & 2) == 0) break;
        if (REAL(state, 0x20) > 1.0f) {
            PLAY(object, 0x22, 0, 10);
            if (func_002A77E0(2) == 1) PLAY(object, 14, 0, 10);
            func_002A7750(object, 0x23, -1);
        } else {
            PLAY(object, 0x22, 0, 10);
            if (func_002A77E0(2) == 1) PLAY(object, 14, 0, 10);
            func_002A7750(object, 0x23, -1);
        }
        if (BYTE(object, 0x95) != 2) {
            func_002A7750(object, 0x19, -1);
            PLAY(object, 0x15, 0, 10);
        }
        break;
    }
    case 35:
        if ((BYTE(object, 0x60) & 2) != 0) {
            if (func_00282E80(((char *)object + 0x10), &D_00189E20.position) < 2.5f) {
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x1c, -1);
            } else {
                PLAY(object, 15, 0, 10);
                func_002A7750(object, 0x1c, -1);
            }
        }
        break;
    case 1:
    default:
        break;
    }
    func_L11_00425A50((char *)object);
    if (func_00282C48(REAL(object, 0x18) - old_z) < 0.005f) REAL(object, 0x18) = old_z;
}
