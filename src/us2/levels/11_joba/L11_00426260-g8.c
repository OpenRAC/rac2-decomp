/* func_US2_L11_00426260, the USA v2.00 copy of func_L11_00424A60: the same C, where the entry count only rises while
   D_US2_001A9050 is clear, and class 0xed8 joins the attackers that leave D_L11_001AED00 set. */
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
extern int D_US2_001A9050;
extern int D_L11_001AED00 __attribute__((sda));
extern int D_L11_001B30C8 __attribute__((sda));
extern char *D_L11_001B359C;
extern int D_L11_001B35B8;
extern unsigned short *D_L11_001FC420[];
extern Vector D_L11_001BA8C0;
extern char D_L11_001B0FD8[], D_L11_002BACF0[];
extern float func_002A89A8(void *, int, float);
extern int func_00283CF0(float);
extern int func_L02_0032E508(void *, int, void *, int);
extern void func_0026FEB8(const char *, ...);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern void func_L00_003294F0(unsigned char *, int);
extern void func_002B60B0(unsigned char *, float, float, float, float);
extern void func_002A7750(unsigned char *, int, int);
extern void func_002A7470(void *, int, int, int);
extern char *func_0029EFD0(int);
extern void func_002A0F48(void *);
extern void func_002AF1D0(void *, void *, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_0029F338(void *);
extern void func_002AC728(void *, void *, int, float, float);
extern int func_002B0ED8(void *, void *, int);
extern void func_0029FCC0(char *, int, char *);
extern void func_L04_00451150(void *, int);
extern void func_002AB800(int, char *);
extern void func_L11_00425AF8(void *);
extern int func_002A8508(int, int);
extern int func_002B3670(void *, int *, int, int, void *, float, float);
extern void func_002A6C58(void *, int, int);

/* A group's ID list entry names an object; bit 15 only marks the list's last entry. */
static inline int group_entry_id(unsigned short *entry)
{
    return *entry & 0x7fff;
}

static inline char *moby_at(int id)
{
    return D_L11_001B359C + id * 0x100;
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

/* Initializes the rider, maintains its linked objects and handles damage/removal. */
int func_US2_L11_00426260(unsigned char *object)
{
    Vector hit_position;
    char *state = POINTER(object, 0x68);
    char *other_state;
    int index, kind, result;
    float angle, altitude;

    if (BYTE(object, 0x20) == 0) {
        BYTE(object, 0x30) = 0x80;
        if (D_US2_001A9050 == 0) ++D_L11_001AED04;
        POINTER(state, 0x18) = state + 0x140;
        REAL(object, 0x18) = func_002A89A8(((char *)object + 0x10), 0, 0.5f);
        WORD(state, 0x554) = 0;
        WORD(state, 0x560) = 0;
        WORD(state, 0x568) = 0;
        BYTE(state, 0x48) = func_00283CF0(20.0f);
        BYTE(state, 0x4a) = func_00283CF0(14.0f);
        if (WORD(state, 0x528) != 0) {
            index = func_L02_0032E508(object, WORD(state, 0x524), state + 0x320, 16);
            WORD(state, 0x520) = index;
            func_0026FEB8(D_L11_001B0FD8, index);
        }
        angle = REAL(state, 0x298);
        if (angle == 0.0f) {
            REAL(state, 0x298) = 0.017453294f * func_002A78D8(15.0f, 25.0f);
        } else {
            REAL(state, 0x298) = angle * 0.017453294f;
        }
        if (func_002A77E0(2) == 1) {
            UHALF(object, 0x34) |= 0x8000;
            func_L00_003294F0(object, 1);
        }
        BYTE(state, 0x70) = 0x24;
        WORD(state, 0xa8) = 4;
        BYTE(state, 0x71) = 0x16;
        BYTE(state, 0x72) = 0x13;
        BYTE(state, 0x76) = 0x14;
        REAL(state, 0x7c) = 0.20000001788139343262f;
        REAL(state, 0x80) = 0.125f;
        REAL(state, 0x84) = 0.0055555556900799274445f;
        REAL(state, 0x88) = 0.0097222225740551948547f;
        REAL(state, 0x8c) = 0.0041666668839752674103f;
        BYTE(state, 0xcc) = 5;
        BYTE(state, 0xcd) = 10;
        BYTE(state, 0xce) = 8;
        BYTE(state, 0xcf) = 15;
        BYTE(state, 0xd2) = 6;
        BYTE(state, 0xd3) = 11;
        REAL(state, 0x10c) = 0.5f;
        REAL(state, 0xb8) = 0.18000000715255737305f;
        REAL(state, 0x90) = 0.75f;
        REAL(state, 0x94) = 0.75f;
        REAL(state, 0x9c) = 0.0f;
        if (WORD(state, 0x57c) != -1) WORD(state, 0xdc) = WORD(state, 0x57c);
        POINTER(state, 0x188) = state + 0x2a0;
        REAL(state, 0x174) = 0.25f;
        REAL(state, 0x140) = 0.75f;
        REAL(state, 0x144) = 0.75f;
        REAL(state, 0x148) = 0.60000002384185791016f;
        REAL(state, 0x14c) = 0.60000002384185791016f;
        if (WORD(state, 0x288) != -1) WORD(state, 0x17c) = WORD(state, 0x288);
        REAL(state, 0x150) = 1.5533431768417358398f;
        REAL(state, 0x170) = 1.4835300445556640625f;
        REAL(state, 0x16c) = 0.0013888889225199818611f;
        func_002B60B0(object, 0.0015277778729796409607f, 0.04583333432674407959f,
                     0.0011635529808700084686f, 0.10471977293491363525f);
        REAL(state, 0x28c) = (float)BYTE(state, 0x34);
        BYTE(state, 0x28) = 3;
        BYTE(state, 0x29) = 1;
        REAL(state, 0x30) = 0.75f;
        BYTE(state, 0x2e) = 1;
        if (WORD(state, 0x26c) != 0) {
            char *mount;
            func_002A7750(object, 1, 5);
            if (WORD(state, 0x270) != -1) {
                mount = (char *)(D_L11_001B359C + WORD(state, 0x270) * 0x100);
                POINTER(state, 0x274) = mount;
                qcopy(((char *)object + 0x10), mount + 0x10);
                qcopy((char *)(object)+0xf0, mount + 0xf0);
                WORD(object, 0x98) = 0;
                UHALF(object, 0x34) &= 0xafff;
                POINTER(POINTER(POINTER(state, 0x274), 0x68), 0x27c) = (char *)object;
                POINTER(state, 0x280) = func_0029EFD0(0x911);
                if (POINTER(state, 0x280) == 0) return 1;
                BYTE(POINTER(state, 0x280), 0x30) = BYTE(object, 0x30);
                BYTE(POINTER(state, 0x280), 0x31) = 0;
                func_002A0F48(POINTER(state, 0x280));
                {
                    char *child = POINTER(state, 0x280);
                    qcopy(child + 0x10, ((char *)object + 0x10));
                    REAL(child, 0x18) += 0.75f;
                }
                POINTER(state, 0x278) = func_0029EFD0(0xff9);
                if (POINTER(state, 0x278) == 0) return 1;
                BYTE(POINTER(state, 0x278), 0x30) = BYTE(object, 0x30);
                UHALF(POINTER(state, 0x278), 0x32) = UHALF(object, 0x32);
                BYTE(POINTER(state, 0x278), 0x31) = 1;
                *(long *)(POINTER(state, 0x278) + 0x38) = *(long *)(object + 0x38);
                func_002A0F48(POINTER(state, 0x278));
                func_002AF1D0(object, POINTER(state, 0x278), 1, 0);
                WORD(state, 0x290) = 0;
            } else {
                func_0026FEB8(D_L11_002BACF0);
                --D_L11_001AED04;
                WORD(state, 0x26c) = 0;
                func_002A7750(object, 4, 0);
                return 1;
            }
        } else {
            func_002A7750(object, 4, 0);
            if (BYTE(object, 0x43) != 0x24) func_002A7470(object, 0x24, 0, 0);
            kind = WORD(state, 0x540);
            if (kind == 1) {
                POINTER(state, 0x55c) = D_L11_001B359C + WORD(state, 0x544) * 0x100;
                func_002A7750(object, 5, 0);
                if (BYTE(object, 0x43) != 0x1c) func_002A7470(object, 0x1c, 0, 0);
            } else if (kind == 2) {
                POINTER(state, 0x55c) = D_L11_001B359C + WORD(state, 0x544) * 0x100;
                func_002A7750(object, 5, 0);
                if (BYTE(object, 0x43) != 0x1e) func_002A7470(object, 0x1e, 5, 0);
            } else if (kind == 3) {
                unsigned short *ids;
                char *candidate;
                ids = D_L11_001FC420[BYTE(object, 0x21)];
                for (;;) {
                    candidate = moby_at(group_entry_id(ids));
                    if (moby_state(candidate) >= 0 && moby_class(candidate) == 0xcf5 &&
                        rider_kind(candidate) == 1) {
                        POINTER(state, 0x55c) = candidate;
                        break;
                    }
                    if (*(short *)ids < 0) break;
                    ++ids;
                }
                func_002A7750(object, 5, 0);
                if (BYTE(object, 0x43) != 0x1e) func_002A7470(object, 0x1e, 0, 0);
            } else if (WORD(state, 0x54c) != -1) {
                func_002A7750(object, 0xe, 0);
                if (BYTE(object, 0x43) != 0x10) func_002A7470(object, 0x10, 0, 0);
                if (WORD(state, 0x578) != 0) func_002A7750(object, 0xf, 0);
            }
            POINTER(state, 0x29c) = func_0029EFD0(0x9ac);
            if (POINTER(state, 0x29c) == 0) return 1;
            BYTE(POINTER(state, 0x29c), 0x30) = BYTE(object, 0x30);
            UHALF(POINTER(state, 0x29c), 0x32) = UHALF(object, 0x32);
            BYTE(POINTER(state, 0x29c), 0x31) = 1;
            *(long *)(POINTER(state, 0x29c) + 0x38) = *(long *)(object + 0x38);
            func_002A0F48(POINTER(state, 0x29c));
            WORD(POINTER(state, 0x29c), 0x98) = 0;
            func_002AF1D0(object, POINTER(state, 0x29c), 3, 0);
        }
        if (WORD(state, 0x270) != -1 && POINTER(state, 0x278) == 0) {
            POINTER(state, 0x278) = func_0029EFD0(0xff9);
            if (POINTER(state, 0x278) == 0) return 1;
            BYTE(POINTER(state, 0x278), 0x30) = BYTE(object, 0x30);
            UHALF(POINTER(state, 0x278), 0x32) = UHALF(object, 0x32);
            BYTE(POINTER(state, 0x278), 0x31) = 1;
            *(long *)(POINTER(state, 0x278) + 0x38) = *(long *)(object + 0x38);
            func_002A0F48(POINTER(state, 0x278));
            func_002AF1D0(object, POINTER(state, 0x278), 1, 0);
            WORD(state, 0x290) = 0;
        }
        qcopy((char *)(state)+0x110, ((char *)object + 0x10));
        REAL(state, 0x120) = 1.0f;
        REAL(state, 0x12c) = 8.0f;
        REAL(state, 0x130) = 10.0f;
    }
    if (BYTE(object, 0x31) != 0 && func_00282E48(((char *)object + 0x10), &D_L11_001BA8C0) < 24.0f) {
        func_002A93B0(object);
        BYTE(object, 0x6f) = 0x16;
    }
    if (BYTE(state, 0x2e) == 2) {
        if (POINTER(state, 0x29c) != 0) {
            func_0029F338(POINTER(state, 0x29c));
            POINTER(state, 0x29c) = 0;
        }
        if (POINTER(state, 0x278) != 0) {
            func_0029F338(POINTER(state, 0x278));
            POINTER(state, 0x278) = 0;
        }
        if (POINTER(state, 0x280) != 0) {
            func_0029F338(POINTER(state, 0x280));
            POINTER(state, 0x280) = 0;
        }
        if (BYTE(object, 0xbc) == 1) {
            char *damaged = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
            if (BYTE(damaged, 0x20) != 5) {
                BYTE(damaged, 0x20) = 4;
                func_002A7470(damaged, 0, 0, 5);
                REAL(damaged, 0x48) = 1.0f;
                REAL(object, 0x48) = 1.0f;
                BYTE(object, 0xbc) = 0;
            }
        }
        return 1;
    }
    if (POINTER(state, 0x29c) != 0) func_002AF1D0(object, POINTER(state, 0x29c), 3, 0);
    if (REAL(state, 0x20) <= 1.0f) {
        if (POINTER(state, 0x29c) != 0) {
            func_002AC728(object, POINTER(state, 0x29c) + 0x10, -1, 0.5f, 3.0f);
            func_0029F338(POINTER(state, 0x29c));
            POINTER(state, 0x29c) = 0;
        }
        WORD(state, 0x290) = 0;
    }
    result = func_002B0ED8(object, state + 0x60, WORD(state, 0x290));
    if (result != 0) {
        char *attacker = POINTER(state, 0x38);
        if (attacker != 0) {
            kind = HALF(attacker, 0xaa);
            if (kind != 0xed8 && kind != 0x47 && kind != 0xdd9 && kind != 0xd1b && kind != 0xce7 && kind != 0xd07 && kind != 0)
                D_L11_001AED00 = 0;
        }
        if (BYTE(object, 0xbc) == 1 && result != 1) {
            char *damaged = (char *)(D_L11_001B359C + WORD(state, 0x548) * 0x100);
            if (BYTE(damaged, 0x20) != 5) {
                BYTE(damaged, 0x20) = 4;
                func_002A7470(damaged, 0, 0, 5);
                REAL(damaged, 0x48) = 1.0f;
                REAL(object, 0x48) = 1.0f;
                BYTE(object, 0xbc) = 0;
            }
        }
        if (REAL(object, 0x48) != 1.0f) REAL(object, 0x48) = 1.0f;
        if (WORD(state, 0x290) != 0) {
            func_0029FCC0((char *)object, 3, (char *)&hit_position);
            func_L04_00451150(&hit_position, 8);
        }
        if (result == 5) {
            REAL(state, 0xf4) = 0.83775818347930908203f;
            REAL(state, 0xf0) = 0.0f;
            if (POINTER(state, 0x29c) != 0) {
                func_002AC728(object, POINTER(state, 0x29c) + 0x10, -1, 0.5f, 3.0f);
                func_0029F338(POINTER(state, 0x29c));
                POINTER(state, 0x29c) = 0;
            }
        }
        WORD(state, 0x290) = 0;
        BYTE(state, 0x57) = 0xd2;
        func_002AB800((int)object, state + 0x50);
        if (BYTE(object, 0x95) != 2) func_L11_00425AF8(object);
        if ((unsigned int)(result - 4) < 2 && D_L11_001B35B8 >= BYTE(object, 0x21) &&
            func_002A8508(BYTE(object, 0x21), -1) >= 2) {
            unsigned short *ids;
            unsigned short id;
            ids = D_L11_001FC420[BYTE(object, 0x21)];
            do {
                char *candidate;
                id = *ids;
                candidate = (char *)(D_L11_001B359C + (id & 0x7fff) * 0x100);
                if (HALF(candidate, 0xaa) == 0xcf5 && WORD(POINTER(candidate, 0x68), 0x294) == 0) {
                    WORD(POINTER(candidate, 0x68), 0x294) = 1;
                    break;
                }
                ++ids;
            } while ((short)id >= 0);
        }
    }
    if (POINTER(state, 0x278) != 0 && WORD(state, 0x270) != -1)
        func_002AF1D0(object, POINTER(state, 0x278), 1, 0);
    HALF(state, 0x264) = func_002B3670(object, (int *)(state + 0x268), WORD(state, 0x250),
                                    WORD(state, 0x254), 0, REAL(state, 0x258), REAL(state, 0x25c));
    if (BYTE(object, 0x95) != 4 && BYTE(object, 0x20) != 0x25) {
        float ground = func_002A89A8(((char *)object + 0x10), 0, 0.5f);
        float drop = 0.31333333253860473633f;
        float height = REAL(object, 0x18) - drop;
        REAL(object, 0x18) = height;
        if (height < ground) REAL(object, 0x18) = ground;
    }
    altitude = func_002A89A8(((char *)object + 0x10), 0, 0.5f);
    if (REAL(object, 0x18) - altitude > 20.0f && altitude < REAL(object, 0x18) && BYTE(object, 0x95) != 5) {
        func_002A7750(object, 0x25, 9);
        if (BYTE(object, 0x43) != 0x23) func_002A7470(object, 0x23, 0, 10);
    }
    if (REAL(object, 0x18) < 75.0f && D_L11_001B30C8 >= 6) {
        func_002A6C58(object, 0, 3);
        if (D_L11_001B35B8 >= BYTE(object, 0x21) && func_002A8508(BYTE(object, 0x21), -1) >= 2) {
            unsigned short *ids;
            unsigned short id;
            ids = D_L11_001FC420[BYTE(object, 0x21)];
            do {
                char *member;
                id = *ids;
                member = D_L11_001B359C + (id & 0x7fff) * 0x100;
                other_state = POINTER(member, 0x68);
                if (WORD(other_state, 0x294) == 0) {
                    WORD(other_state, 0x294) = 1;
                    break;
                }
                ++ids;
            } while ((short)id >= 0);
        }
        if (POINTER(state, 0x29c) != 0) {
            func_002AC728(object, POINTER(state, 0x29c) + 0x10, -1, 0.5f, 3.0f);
            func_0029F338(POINTER(state, 0x29c));
            POINTER(state, 0x29c) = 0;
        }
        --D_L11_001AED04;
        return 1;
    }
    return 0;
}
