/* func_US2_L08_00424F74, the USA v2.00 copy of func_L08_00423970: the same C, with a new test of game
   state 0x6F after the height gates, a new clear of the 0x34 bit on actors in state 4 and above, and
   the destroy path calling func_US2_002A7AA8 for func_002A6C58, with flag 0x1000 when the 0x18A byte is 2. */
#include "common.h"

#define FIELD(base, type, offset) (*(type *)((base) + (offset)))

extern float func_00282C48(float);
extern float func_0029F530(void *);
extern int func_002B3868(void *);
extern void func_002E5CF8(int, int, void *);
extern void func_002AA548(void *, float, void *, float, float, float);
extern void func_L08_00422190(void *, void *, int, float, float, float, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(void *, float, int, void *);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283CE0(int);
extern float func_002ABB18(float);
extern void func_L08_00422B98(void *);
extern int func_L08_00423010(void *, float, float, float, float, float, float, float, float);
extern void func_L08_00422EE0(void *);
extern float func_00282E80(void *, void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A8C28(void *, void *, float, float, float, int, int, int, int);
extern void func_L08_00422B60(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002B1C20(void *, void *);
extern void func_L08_00422428(void *);
extern void func_L08_00422578(void *, void *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_US2_002A7AA8(void *, int, int);
extern char *D_L08_001BFF58 NOT_SDA;
extern int D_L08_001B2508 MACRO_ADDR;
extern struct { char pad[0x2294]; int state; int pad2298; int secondaryState; } D_00189E20;
extern char D_L08_001A8F20[] __attribute__((sda));
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021DE80;
extern unsigned char D_L08_001B2840[] __attribute__((sda));
extern unsigned char D_0019B2E8[];
extern s32 D_L08_001B29DC __attribute__((sda));
typedef struct {
    int state;
    char pad04[8];
    int mode;
    char pad10[0x18];
    float height;
    char pad2C[0xC];
    float secondHeight;
} HeightGate;
extern HeightGate D_L08_001CA080;
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021EAF0;
extern unsigned char D_0019B4A8[];

extern int D_001A79F0 MACRO_ADDR;
extern void func_L08_004238A0(char *);
extern void func_L08_004233E0(char *);
extern void func_L08_004237F0(char *);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_L08_0032F898(char *, char *, float, float, int, int, int, int);
extern int func_L08_004229C8(int);
extern int func_L08_00422A40(int);
extern int func_L08_004229F8(int);
extern int func_L08_00422A88(int);
extern void func_0026FEB8(char *, int, int);
extern char D_L08_002B5600[];
extern int func_00282978(short *);
extern void func_002A7470(char *, int, int, int);
extern void func_002A7750(char *, int, int);
extern void func_0029F338(char *);

/* Apply the height gates, dispatch the actor state, and update timers and bounds. */
void func_US2_L08_00424F74(char *actor) {
    char *p;
    int ready;
    int condition;
    float local[4];
    float z;
    int mode = D_L08_001CA080.mode;
    if (mode != 0) {
        float height = *(float *)(actor + 0x18);
        if (height < D_L08_001CA080.height && D_L08_001CA080.state == 1) return;
        if (D_L08_001CA080.height < height && D_L08_001CA080.state == 0) return;
        if (mode == 2) {
            if (D_L08_001CA080.secondHeight < height && D_L08_001CA080.state == 1) return;
            if (height < D_L08_001CA080.secondHeight && D_L08_001CA080.state == mode) return;
        }
    }
    p = *(char **)(actor + 0x68);
    if (D_00189E20.state == 0x6F) {
        *(unsigned char *)(actor + 0x31) = 0;
        *(unsigned short *)(actor + 0x34) |= 1;
        return;
    }
    if ((*(unsigned short *)(actor + 0x34) & 1) && *(unsigned char *)(actor + 0x20) >= 4) {
        *(unsigned short *)(actor + 0x34) &= 0xFFFE;
        *(unsigned char *)(actor + 0x31) = 1;
    }
    func_L08_004238A0(actor);
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0: {
        int id = *(int *)(p + 0x184);
        if (id != -1) {
            char *other = (char *)D_L08_001B29DC + (id << 8);
            if (*(unsigned char *)(other + 0xB0) != 255) {
                unsigned short tag = *(unsigned short *)(other + 0xB2);
                if (D_L08_0021EAF0.flags[(short)tag] ||
                    ((D_0019B4A8[((short)tag >> 1) + (D_001A79F0 << 10)] >> ((tag & 1) ? 4 : 0)) & 7)) {
                    unsigned short ownTag = *(unsigned short *)(actor + 0xB2);
                    if ((D_0019B4A8[((short)ownTag >> 1) + (D_001A79F0 << 10)] >> ((ownTag & 1) ? 4 : 0)) & 7) goto destroy;
                }
            }
        }
        func_L08_004233E0(actor);
        break;
    }
    case 1:
        ready = 0;
        switch (*(unsigned char *)(p + 0x18B)) {
        case 0:
            if (!func_002A77E0(7)) {
                /* Result 2 is false; normalize this with the other nonzero triggers. */
                condition = func_L08_0032F898(actor, p + 0x100,
                    (float)*(unsigned char *)(p + 0x18D), 0.0f,
                    *(int *)(p + 0x190), *(int *)(p + 0x198),
                    *(int *)(p + 0x194), -1) ^ 2;
                goto normalize;
            }
            break;
        case 1:
            if (*(int *)(p + 0x180) != -1) ready = func_L08_004229C8(*(int *)(p + 0x180)) != 0;
            else {
                func_0026FEB8(D_L08_002B5600, *(short *)(actor + 0xAA), *(short *)(actor + 0xB2));
                *(unsigned char *)(p + 0x18B) = 0;
            }
            break;
        case 2: condition = *(u8 *)(actor + 0xBC); goto normalize;
        case 3: ready = func_L08_00422A40(*(int *)(p + 0x1AC)) != 0; break;
        case 4: ready = func_L08_004229F8(*(int *)(p + 0x180)) != 0; break;
        case 5:
            condition = func_L08_00422A88(*(int *)(p + 0x184));
normalize:
            ready = condition != 0;
            break;
        }
        if (*(unsigned char *)(actor + 0xBC) & 2) ready = 1;
        if (ready) {
            *(unsigned char *)(actor + 0x30) = *(unsigned char *)(p + 0x188);
            qzero(p + 0x170);
            *(short *)(p + 0x1B8) = func_002A7820(0, 180);
            func_002A7750(actor, 3, -1);
        }
        break;
    case 3:
        if (func_00282978((short *)(p + 0x1B8))) {
            if (*(unsigned char *)(actor + 0x43)) func_002A7470(actor, 0, 0, 10);
            *(unsigned char *)(actor + 0x31) = 1;
            *(unsigned short *)(actor + 0x34) &= 0xFFFE;
            func_002A7750(actor, 2, 0);
        }
        break;
    case 2:
        z = FIELD(actor, float, 0x18);
        switch (FIELD(actor, u8, 0x95)) {
        case 0: z = FIELD(p, float, 0x1B4); break;
        case 1: z = FIELD(p, float, 0x1B0) - 1.7f; break;
        }
        if (func_002B3868(actor)) func_002E5CF8(4, 0, actor);
        func_002AA548(actor + 0x18, z, p + 0x178,
                       0.0069444444961845875f, 0.004166666883975267f, 0.5f);
        if (func_0029F530(actor) < 12.0f) {
            qcopy(local, actor + 0x10);
            local[2] = FIELD(p, float, 0x1B0);
            func_L08_00422190(actor, local, 3, 1.0f, 1.5f, 0.5f, 0.0f, 0.1f, 0.8f);
        }
        if (func_00282C48(FIELD(actor, float, 0x18) - z) < 0.2f) {
            switch (FIELD(actor, u8, 0x95)) {
            case 0:
                FIELD(actor, u16, 0x34) |= 0x1000;
                if (FIELD(actor, u8, 0x43) != 3) func_002A7470(actor, 3, 0, 3);
                FIELD(p, s16, 0x1B8) = func_002A7820(180, 360);
                func_002A7750(actor, 5, -1);
                break;
            case 1:
                FIELD(actor, u16, 0x34) &= 0xEFFF;
                if (FIELD(actor, u8, 0x43) != 1) func_002A7470(actor, 1, 0, 3);
                FIELD(p, s16, 0x1B8) = 0;
                FIELD(actor, u8, 0x31) = 0;
                FIELD(actor, u16, 0x34) |= 1;
                func_002A7750(actor, 1, -1);
                break;
            }
        }
        break;
    case 4:
        func_00282CC0(actor + 0x10, actor + 0x10, p + 0x170);
        FIELD(p, float, 0x178) -= 0.0027222223579883575f;
        FIELD(actor, float, 0x18) += 0.75f;
        if (func_00277258(actor + 0x10, 0.75f, 0, actor)) {
            if (D_L08_001BFF58 == 0 || FIELD(D_L08_001BFF58, s16, 0xAA) != 0x945) {
                if (FIELD(actor, u8, 0x43) != 3) func_002A7470(actor, 3, 0, 3);
                FIELD(p, s16, 0x1B8) = func_002A7820(180, 360);
                func_002A7750(actor, 5, -1);
            }
        }
        if (FIELD(p, float, 0x178) < 0 || FIELD(actor, u16, 0x96) > 240) {
            if (FIELD(actor, u8, 0x43) != 3) func_002A7470(actor, 3, 0, 3);
            FIELD(p, s16, 0x1B8) = func_002A7820(180, 360);
            func_002A7750(actor, 5, -1);
        }
        FIELD(actor, float, 0x18) -= 0.75f;
        FIELD(p, float, 0x178) -= 0.0027222223579883575f;
        if (FIELD(actor, float, 0x18) < FIELD(p, float, 0x1B0))
            FIELD(actor, float, 0x18) = FIELD(p, float, 0x1B0);
        break;
    case 5: {
        float angle = FIELD(p, float, 0x16C);
        float phase;
        if (FIELD(actor, u16, 0x96) == 0 || D_L08_001B2508 % 50 == FIELD(actor, s16, 0xB2) % 50) {
            if (angle > 0.0f) angle = func_002A7878(0.2f, 0.5f) * -1.5707963705062866f;
            else angle = func_002A7878(0.2f, 0.5f) * 1.5707963705062866f;
        }
        FIELD(p, float, 0x160) = func_00283180(func_00283B98(FIELD(actor, float, 0xF8), angle)) * 2.0f;
        FIELD(p, float, 0x164) = func_00283198(func_00283B98(FIELD(actor, float, 0xF8), angle)) * 2.0f;
        FIELD(p, s32, 0x168) = 0;
        func_00282CC0(p + 0x160, p + 0x160, actor + 0x10);
        phase = func_002ABB18(func_00283CE0(D_L08_001B2508) * 0.025f);
        func_L08_00422B98(actor);
        if (func_L08_00423010(actor, 360.0f, 180.0f, 560.0f, 20.0f, 0.0f, 16.0f,
                              FIELD(p, float, 0x15C) + 1.7f + 1.0f + func_00283198(phase), -2.0f))
            angle *= 1.025f;
        FIELD(p, float, 0x16C) = angle;
        if (FIELD(p, s16, 0x1B8) == 0) {
            if (FIELD(actor, u8, 0x43) != 1) func_002A7470(actor, 1, 0, 3);
            func_002A7750(actor, 6, 0);
        }
        break;
    }
    case 6:
        switch (FIELD(actor, u8, 0x95)) {
        case 0:
            if (FIELD(p, s16, 0x1B8) == 0) {
                FIELD(p, s16, 0x1B8) = func_002A7820(30, 90);
                if (FIELD(p, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 3)
                    func_002A7470(actor, 3, 0, 3);
                func_002A7750(actor, 6, 1);
            }
            break;
        case 1:
            func_L08_00423010(actor, 120.0f, 360.0f, 120.0f, 30.0f, 0.0f, 8.0f,
                              FIELD(p, float, 0x15C) + 1.7f, 1.0f);
            if (FIELD(p, s16, 0x1B8) == 0) {
                func_L08_00422EE0(actor);
                FIELD(p, s16, 0x1B8) = func_002A7820(0, 0);
                if (FIELD(p, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 1)
                    func_002A7470(actor, 1, 0, 3);
                func_002A7750(actor, 6, 0);
            }
            break;
        case 2:
            qcopy(p + 0x160, p + 0x150);
            if (func_L08_00423010(actor, 120.0f, 360.0f, 120.0f, 30.0f, 0.0f, 8.0f,
                                  FIELD(p, float, 0x15C) + 1.7f, 1.0f) & 8) {
                if (FIELD(actor, u8, 0x43) != 2) func_002A7470(actor, 2, 0, 10);
                func_002A7750(actor, 2, 1);
            }
            break;
        }
        if (func_L08_0032F898(actor, p + 0x100, (float)FIELD(actor, s16, 0x32), 0.0f,
                             FIELD(p, int, 0x19C), FIELD(p, int, 0x1A4), FIELD(p, int, 0x1A0), -1) != 2) {
            if (!func_002A77E0(9)) {
                FIELD(p, s16, 0x1BA) = func_002A7820(300, 360);
                func_002A7750(actor, 7, 0);
            }
        } else if (FIELD(actor, u8, 0x20) == 6 && FIELD(p, u8, 0x18A) == 0) {
            func_002A7750(actor, 6, 2);
        }
        break;
    case 7:
        switch (FIELD(actor, u8, 0x95)) {
        case 0:
            if (FIELD(p, s16, 0x1B8) == 0) {
                FIELD(p, s16, 0x1B8) = func_002A7820(30, 90);
                if (FIELD(p, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 3)
                    func_002A7470(actor, 3, 0, 3);
                func_002A7750(actor, 7, 1);
            }
            break;
        case 1:
            if (func_L08_00423010(actor, 250.0f, 180.0f, 250.0f, 32.0f, 0.1f, 13.0f,
                                  FIELD(p, float, 0x15C) + 1.7f, 1.0f) & 8)
                FIELD(p, s16, 0x1B8) = 0;
            if (FIELD(p, s16, 0x1B8) == 0) {
                func_L08_00422EE0(actor);
                FIELD(p, s16, 0x1B8) = func_002A7820(0, 0);
                if (FIELD(p, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 1)
                    func_002A7470(actor, 1, 0, 3);
                func_002A7750(actor, 7, 0);
            }
            break;
        }
        if (func_L08_0032F898(actor, p + 0x100, (float)FIELD(actor, s16, 0x32), (float)FIELD(p, u8, 0x18D),
                             FIELD(p, int, 0x19C), FIELD(p, int, 0x1A4), FIELD(p, int, 0x1A0), -1) == 2 ||
            D_00189E20.state == 0x31 || D_00189E20.secondaryState == 0x11 ||
            D_00189E20.secondaryState == 0x12) {
            FIELD(p, int, 0x144) = 2;
            if (FIELD(p, s16, 0x1BA) == 0) func_002A7750(actor, 6, 0);
        } else if (**(int **)(p + 0x1CC) < 3 && FIELD(p, s16, 0x1BC) == 0 &&
                    func_00282E80(actor + 0x10, p + 0x120) < 12.0f) {
            FIELD(p, u8, 0x18C) = 1;
            qcopy(p + 0x160, p + 0x120);
            func_002A7750(actor, 8, 0);
            ++**(int **)(p + 0x1CC);
        }
        break;
    case 8: {
        qcopy(p + 0x160, p + 0x120);
        switch (FIELD(actor, u8, 0x95)) {
        case 0:
            func_L08_00423010(actor, 260.0f, 180.0f, 270.0f, 32.0f, 0.15f, 8.0f, 0.4f, 0.5f);
            if (func_00282E80(actor + 0x10, p + 0x120) < 1.5f &&
                func_00282C48(FIELD(actor, float, 0x18) - FIELD(p, float, 0x128)) < 1.1f) {
                if (FIELD(actor, u8, 0x43) != 4) func_002A7470(actor, 4, 0, 3);
                func_002A7750(actor, 8, 1);
            }
            break;
        case 1:
            func_L08_00423010(actor, 260.0f, 180.0f, 270.0f, 32.0f, 0.15f, 8.0f, 0.3f, 0.5f);
            func_002A7750(actor, 8, 2);
            break;
        case 2:
            if (FIELD(actor, u8, 0x42) == 4) {
                if (func_0029F530(actor) > 19.5f && func_0029F530(actor) < 29.0f) {
                    func_0029FCC0(actor, 1, local);
                    func_002A8C28(actor, local, 0.5f, (float)FIELD(p, u8, 0x34), 1.0f, 1, 0, 1, 0);
                }
                if (FIELD(actor, u8, 0x60) & 2) {
                    FIELD(p, s16, 0x1B8) = 120;
                    FIELD(p, s16, 0x1BC) = func_002A7820(180, 260);
                    if (FIELD(actor, u8, 0x43) != 1) func_002A7470(actor, 1, 0, 3);
                    func_002A7750(actor, 8, 3);
                }
            }
            break;
        case 3:
            func_L08_00423010(actor, 260.0f, 180.0f, 270.0f, 32.0f, 0.15f, 8.0f, 0.3f, 0.5f);
            if (func_00282978((s16 *)(p + 0x1B8))) {
                if (func_00282E80(actor + 0x10, p + 0x120) < 1.5f &&
                    func_00282C48(FIELD(actor, float, 0x18) - FIELD(p, float, 0x128)) < 1.1f) {
                    if (FIELD(actor, u8, 0x43) != 4) func_002A7470(actor, 4, 0, 3);
                    func_002A7750(actor, 8, 1);
                } else {
                    qcopy(p + 0x160, p + 0x120);
                    func_002A7750(actor, 8, 0);
                }
            }
            break;
        }
        if (func_L08_0032F898(actor, p + 0x100, (float)FIELD(actor, s16, 0x32), (float)FIELD(p, u8, 0x18D),
                             FIELD(p, int, 0x19C), FIELD(p, int, 0x1A4), FIELD(p, int, 0x1A0), -1) == 2 ||
            D_00189E20.state == 0x31 || D_00189E20.secondaryState == 0x11 ||
            D_00189E20.secondaryState == 0x12) {
            func_L08_00422B60(actor);
            if (FIELD(p, s16, 0x1BA) != 0) {
                FIELD(p, s16, 0x1B8) = 0;
                if (FIELD(actor, u8, 0x43) != 3) func_002A7470(actor, 3, 0, 3);
                func_002A7750(actor, 6, 0);
            } else {
                func_00282CF0(p + 0x160, actor + 0x10, p + 0x160);
                func_00282CC0(p + 0x160, p + 0x160, actor + 0x10);
                func_00282F20(p + 0x160, p + 0x160, 5.0f);
                func_L08_00422B98(actor);
                func_L08_00423010(actor, 260.0f, 180.0f, 270.0f, 32.0f, 0.15f, 8.0f, 0.3f, 0.5f);
                FIELD(p, s16, 0x1B8) = 0;
                if (FIELD(actor, u8, 0x43) != 3) func_002A7470(actor, 3, 0, 3);
                FIELD(p, s16, 0x1BC) = func_002A7820(180, 260);
                func_002A7750(actor, 7, 0);
            }
        }
        break;
    }
    case 9: {
        int result;
        ++FIELD(p, u16, 0x1BE);
        if (func_002B3868(actor)) func_002E5CF8(0, 0, actor);
        result = func_002B1C20(actor, p + 0x50);
        if (result & 1) {
            func_002A7750(actor, 10, -1);
        } else if ((result & 2) || FIELD(p, s16, 0x1BE) > 360) {
            FIELD(p, u8, 0x6A) = 2;
            if (FIELD(actor, u8, 0x43) != 1) func_002A7470(actor, 1, 0, 3);
            FIELD(p, s16, 0x1BE) = 0;
            qzero(p + 0x170);
            if (FIELD(p, float, 0x20) <= 0.0f) func_002A7750(actor, 10, -1);
            else func_002A7750(actor, 7, 0);
        }
        break;
    }
    case 10: {
        u16 tag;
        int kind;
        u32 bits;
        if (func_002B3868(actor)) func_002E5CF8(1, 0, actor);
        func_L08_00422428(actor);
        func_L08_00422578(actor, D_L08_001A8F20);
        func_002ABBB8(actor, p + 0x170, 0, 0.0f, 0.0f, 4, 0, 0,
                      2.0f, 1.0f, 9.0f, 1.0f, -1, 0.0f, 0, 0, -1, 1, 0x810001);
        func_L08_00422B60(actor);
        func_US2_002A7AA8(actor, FIELD(p, u8, 0x18A) == 2 ? 0x1000 : 0, 3);
        D_L08_0021DE80.flags[FIELD(actor, s16, 0xB2)] = FIELD(actor, u8, 0xB0) + 2;
        kind = FIELD(actor, u8, 0xB0);
        if (kind == 255 || (!(D_L08_001B2840[(u8)kind] & 0x80) &&
                            (D_0019B2E8[(u8)kind + (D_001A79F0 << 4)] & 0x80))) {
            D_L08_0021EAF0.flags[FIELD(actor, s16, 0xB2)] = kind + 2;
        }
        tag = FIELD(actor, u16, 0xB2);
        if (tag & 1) {
            bits = D_0019B4A8[((s16)tag >> 1) + (D_001A79F0 << 10)];
            if (((bits >> 4) & 7) != 7)
                D_0019B4A8[((s16)tag >> 1) + (D_001A79F0 << 10)] = bits + 0x10;
        } else {
            bits = D_0019B4A8[((s16)tag >> 1) + (D_001A79F0 << 10)];
            if ((bits & 7) != 7)
                D_0019B4A8[((s16)tag >> 1) + (D_001A79F0 << 10)] = bits + 1;
        }
destroy:
        func_0029F338(actor);
        return;
    }
    }
    func_L08_004237F0(actor);
    if (*(float *)(actor + 0x10) < 20.0f || 1003.0f < *(float *)(actor + 0x10) ||
        *(float *)(actor + 0x14) < 20.0f || 1003.0f < *(float *)(actor + 0x14) ||
        *(float *)(actor + 0x18) < 20.0f || 1003.0f < *(float *)(actor + 0x18)) func_0029F338(actor);
}
