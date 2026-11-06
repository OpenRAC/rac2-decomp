/* Per-frame state machine for the L03/L14 moby with class switch 0x940/0x964 (states 1..22).
   Own unit: -G8 globals, the hazard-nop branch label and -malign-loops=2 for the store group. */
#include "common.h"
typedef struct {
    u8 reserved00[0x134]; float acceleration;
    u8 reserved138[12]; float max_speed;
} MotionInit;
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } MotionVector;
typedef struct {
    u8 reserved00[0x18]; u8 enabled, count, kind; u8 reserved1B[0x65]; u8 payload[1];
} DispatchContext;
extern float D_00189EA0[], D_00189F00[];
extern u8 D_00189E20[];
typedef union { u8 b[0x2600]; u8 *ptr[0x980]; float f[0x980]; } Hero;
extern u16 D_0018CB20[], D_0018CB38[], D_0018CDCC[];
extern u16 D_0018CB2C[], D_0018CF58[], D_0018CDE4[];
extern int D_0018CB4C[];
extern int D_L03_001B2548 MACRO_ADDR;
extern u8 *D_L03_001B2A1C MACRO_ADDR;
extern u8 *D_L03_001B2A20 MACRO_ADDR;
extern u8 *D_L03_001BFDD8[];
extern float D_L03_001AFEE0 __attribute__((sda));
extern float D_L03_001AFEE4 __attribute__((sda));
extern float D_L03_001AFEE8 __attribute__((sda));
extern float D_L03_001AFEEC __attribute__((sda));
extern float D_L03_001AFEF0 __attribute__((sda));
extern float D_L03_001AFEF4 __attribute__((sda));
extern void func_L03_003C3220(u8 *);
extern int func_002B3890(u8 *);
extern int func_002B3868(u8 *);
extern int func_002B38B8(u8 *);
extern void func_002B60B0(u8 *, float, float, float, float);
extern u32 func_002B1C20(void *, DispatchContext *);
extern void func_002A7750(u8 *, s32, s32);
extern int func_00288E18(int, int);
extern int func_002A77E0(int);
extern void func_002A7470(u8 *, int, int, int);
extern void func_L03_003C4368(u8 *, void *);
extern void func_L03_003C4240(u8 *);
extern void func_L03_003C4BD8(u8 *);
extern void func_L03_003C4A10(u8 *, void *);
extern float func_00282E80(void *, void *);
extern int func_L03_00419BD8(u32, void *, void *);
extern float func_002AA340(int *, int, int);
extern int func_L03_003C41B8(u8 *, int, int);
extern int func_L03_003C58F0(u8 *, float *);
extern float func_00283180(float), func_00283198(float), func_00283248(float, float);
extern float func_00283B98(float, float), func_00283BE0(float, float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float), func_00283098(void *, void *, void *);
extern int func_L01_00322288(int, float);
extern int func_00282948(void *);
extern int func_L03_003C5DC8(u8 *, u8 *);
extern u32 func_L03_004197A8(u8 *);
extern void func_L03_00419818(u8 *, u32);
extern void func_002AFDD8(char *, char *, char *, char *);
extern void func_0029F338(void *);
extern u8 *func_L03_003C4D40(u8 *);
extern void func_L03_003C5B28(u8 *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_002AEB60(char *, float);
extern int func_002A8D70(float, float, float, void *, int, int, int, int, int);
extern float func_0029F530(char *);
extern float func_L02_00321C30(void *, void *, float);
extern void func_L03_00419A60(u32, u8 *, s32);
extern int func_L03_003C5CE8(u8 *);
extern u32 func_L03_003CAAC8(u8 *, u8 *);
extern void func_L03_003C5EE8(void *);
extern void func_002AC9F8(float *, float);
extern void func_0029FCC0(char *, int, char *);
extern void func_L03_003CA220(u8 *, float), func_L00_003294F0(u8 *, int);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float func_002A89A8(u8 *, int, float);
extern int func_L03_00419C00(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_002B5258(char *), func_L03_003C4468(u8 *), func_002A677C(u8 *);
#define SF(o) (*(float *)(state + (o)))
#define SI(o) (*(int *)(state + (o)))
#define SP(o) (*(u8 **)(state + (o)))
#define OF(o) (*(float *)(object + (o)))
#define ANIM_FRAMES(off) (*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + (off)) + 0x10))


void func_L03_003C1BF0(u8 *object)
{
    MotionVector point, other, delta;
    u8 *state = *(u8 **)(object + 0x68);
    u8 *target, *parent, *member, *pos, *mtx, *rot;
    u32 dispatch;
    int type, code, i, entered;
    float heading, turn, distance, floor, height;
    func_L03_003C3220(object);
    switch (object[0x95]) {
    case 0:
        break;
    case 1:
        if (func_002B3890(object)) {
            func_002B60B0(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                          0.0034906589426100254f, 0.10471977293491364f);
            ((MotionInit *)state)->acceleration = 0.0016666667f;
            ((MotionInit *)state)->max_speed = D_L03_001AFEE0;
        }
        break;
    case 2:
        if (func_002B3890(object)) {
            func_002B60B0(object, D_L03_001AFEE8 * 0.00027777778f, D_L03_001AFEEC * 0.016666668f,
                          0.006981317885220051f, 0.20943954586982727f);
            SF(0x144) = 0.0f; SF(0x134) = 0.0055555557f;
        }
        break;
    case 3:
        if (func_002B3890(object)) {
            func_002B60B0(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                          0.006981317885220051f, 0.20943954586982727f);
            SF(0x134) = 0.0055555557f; SF(0x144) = 0.1f;
        }
        break;
    case 4:
        func_002B60B0(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.0034906589426100254f, 0.10471977293491364f);
        SF(0x134) = 0.0016666667f; SF(0x144) = 0.4f;
        break;
    case 5:
        func_002B60B0(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.0034906589426100254f, 0.10471977293491364f);
        SF(0x134) = 0.0016666667f; SF(0x144) = 0.05f;
        break;
    case 6:
        func_002B60B0(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.006981317885220051f, 0.20943954586982727f);
        SF(0x134) = 0.005f; SF(0x144) = 0.05f;
        break;
    case 8:
        dispatch = func_002B1C20(object, (DispatchContext *)(state + 0x60));
        if (dispatch & 1) { func_0029F338(object); return; }
        if (dispatch & 2) func_002A7750(object, 2, 0);
        break;
    }
    {
        switch (object[0x20]) {
        case 1:
            if (func_002B38B8(SP(0x354))) {
                type = *(s16 *)(object + 0xAA);
                switch (type) {
                case 0x940:
                    if (D_0018CB20[0] == 0) func_00288E18(0x9CF, 0x26);
                    break;
                case 0x93C:
                    if (D_0018CB38[0] == 0) func_00288E18(0x9D1, 0x28);
                    break;
                case 0xA59:
                    if (D_0018CDCC[0] == 0) func_00288E18(0xA08, 0x5F);
                    break;
                case 0x964:
                default:
                    if (D_0018CB4C[0] >= 0) func_00288E18(0x9D2, 0x29);
                    break;
                }
                func_002A7750(object, 4, 1);
            }
            break;
        case 2:
            if (((Hero *)D_00189E20)->ptr[0x270 / 4] == object || ((Hero *)D_00189E20)->ptr[0x26C / 4] == object)
                func_L03_003C4368(object, &((Hero *)D_00189E20)->b[0x80]);
            func_L03_003C4240(object);
            if (object[0x31]) func_L03_003C4BD8(object);
            break;
        case 4:
            if (func_002B3868(object)) {
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 15);
                SI(0x380) = 2; qzero(state + 0x1B0);
            }
            if (((Hero *)D_00189E20)->ptr[0x270 / 4] == object || ((Hero *)D_00189E20)->ptr[0x26C / 4] == object)
                func_L03_003C4368(object, &((Hero *)D_00189E20)->b[0x80]);
            func_L03_003C4240(object);
            distance = func_00282E80(object + 0x10, D_00189E20 + 0x80);
            if (D_L03_001AFEE4 < distance && func_L03_00419BD8((u32)SI(0x220), object + 0x10, D_00189E20 + 0x80)) {
                func_002A7750(object, 3, -1);
                if (object[0x43] != 2) func_002A7470(object, 2, func_002A77E0(ANIM_FRAMES(0x50)), 10);
            } else {
                if (object[0x31] && object[0x42] != 1) {
                    if (SI(0x380) < 5) func_L03_003C4A10(object, D_00189F00);
                    else func_L03_003C4BD8(object);
                }
            }
            if ((object[0x60] & 2) && object[0x42] == object[0x43]) {
                if (object[0x42] == 1)
                    func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 15);
                else if (!func_002A77E0(SI(0x380))) {
                    func_002AA340((int *)(state + 0x380), 10, 1);
                    if (object[0x43] != 1) func_002A7470(object, 1, 0, 15);
                }
            }
            break;
        case 3:
            if (!func_L03_003C41B8(object, (int)D_00189EA0, 1) || SF(0x1DC) < D_L03_001AFEE0 ||
                (SI(0x190) > 60 && SF(0x1DC) < D_L03_001AFEE4)) {
                func_002A7750(object, 4, -1);
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 10);
            }
            if ((D_L03_001B2548 & 15) == (((int)object >> 8) & 15))
                SI(0x360) = func_L03_003C58F0(object, D_00189EA0);
            break;
        case 5:
            if (func_002B3868(object)) {
                if (object[0x43] != 2) func_002A7470(object, 2, func_002A77E0(ANIM_FRAMES(0x50)), 20);
                SF(0x144) = 0.1f;
            }
            point.f[0] = func_00283180(SF(0x374)); point.f[1] = func_00283198(SF(0x374)); point.f[2] = 0;
            func_00282CC0(&point, &point, object + 0x10);
            func_L03_003C41B8(object, (int)&point, 1);
            if (*(u16 *)(object + 0x96) >= 61) {
                SF(0x144) = D_L03_001AFEE0;
                func_002A7750(object, 4, 1);
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 10);
            }
            break;
        case 6:
        case 8:
            if (func_002B3868(object)) {
                if (object[0x20] == 8) { if (object[0x43] != 7) func_002A7470(object, 7, 0, 20); }
                else if (object[0x43] != 3) func_002A7470(object, 3, 0, 20);
            }
            func_L01_00322288((int)object, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - OF(0x10), ((Hero *)D_00189E20)->f[0x84 / 4] - OF(0x14)));
            if (object[0x60] & 2) func_002A7750(object, 4, -1);
            break;

        case 7:
            if (func_002B3868(object)) SF(0x144) = 0.1f;
            if (func_00282E80(object + 0x10, state + 0x340) > SF(0x144)) {
                func_L03_003C41B8(object, (int)(state + 0x340), 0);
                if (object[0x43] != 2) func_002A7470(object, 2, func_002A77E0(ANIM_FRAMES(0x50)), 20);
            } else if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 20);
            if (func_00282948(state + 0x37C)) func_002A7750(object, 4, -1);
            break;
        case 12:
            func_L03_003C41B8(object, (int)(state + 0x340), 0);
            if ((D_L03_001B2548 & 3) == (((int)object >> 8) & 3))
                SF(0x110) = func_L03_003C5DC8(object, state + 0x340) ? 0.11f : 0.15f;
            if (!func_L03_004197A8(SP(0x358))) {
                func_002A7750(object, 4, 1);
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 10);
            } else if (SF(0x1DC) < SF(0x144)) func_002A7750(object, 13, -1);
            break;
        case 13:
            if (func_002B3868(object)) {
                func_L03_00419818(SP(0x358), (u32)object); SF(0x140) = 0.174532949924469f;
                func_002AFDD8((char *)SP(0x358), (char *)(state + 0x1B0), (char *)(state + 0x1B0), 0);
                SF(0x1B4) = 0;
                func_00283098(state + 0x1B0, state + 0x1B0, SP(0x358) + 0xC0); SF(0x110) = 0;
            }
            func_L03_003C41B8(object, (int)(SP(0x358) + 0x10), 0);
            if (func_00282E80(object + 0x10, SP(0x358) + 0x10) < 0.1f) { func_0029F338(object); return; }
            break;
        case 9:
            if ((D_L03_001B2548 & 7) == (((int)object >> 8) & 7)) SP(0x358) = func_L03_003C4D40(object);
            parent = SP(0x194);
            if (parent) {
                if (SP(0x198) && *(s16 *)(SP(0x198) + 0xAA) == 0x97A) heading = OF(0xF8);
                else {
                    heading = func_00283248(*(float *)(parent + 0x10) - OF(0x10), *(float *)(parent + 0x14) - OF(0x14));
                    turn = func_00283BE0(heading, OF(0xF8));
                    heading = func_00283B98(turn < 0.0f ? -1.5707963705062866f : 1.5707963705062866f, OF(0xF8));
                }
                func_L03_003C5B28(object, heading);
            }
            target = SP(0x358);
            if (!target) {
                func_002A7750(object, 11, -1);
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 20);
                break;
            }
            func_L03_003C41B8(object, (int)(target + 0x10), 0);
            if ((D_L03_001B2548 & 3) == (((int)object >> 8) & 3)) {
                qcopy(&point, object + 0x10); point.f[2] += 0.2f;
                func_00282F20(&other, object + 0xC0, 0.3330000042915344f);
                func_00282CC0(&other, &other, object + 0x10); other.f[2] += 0.2f;
                if (func_002761F8(&point, &other, 0, object, 0) && D_L03_001BFDD8[0] == SP(0x358)) {
                    func_002A7750(object, 10, -1);
                    if (object[0x43] != 4) func_002A7470(object, 4, 0, 10);
                }
            }
            break;
        case 10:
            if (func_002AEB60((char *)object, 14.0f))
                func_002A8D70(0.3330000042915344f, 4.0f, 1.0f, object, 1, 0x10000, 0, 1, 0);
            else if (object[0x60] & 2) {
                SP(0x358) = func_L03_003C4D40(object);
                if (SP(0x358)) {
                    func_002A7750(object, 9, -1);
                    if (object[0x43] != 3) func_002A7470(object, 3, func_002A77E0(ANIM_FRAMES(0x54)), 10);
                } else {
                    func_002A7750(object, 11, -1);
                    if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 10);
                }
            }
            break;
        case 11:
            if ((D_L03_001B2548 & 7) == (((int)object >> 8) & 7)) SP(0x358) = func_L03_003C4D40(object);
            func_L03_003C4BD8(object);
            if (SP(0x358)) {
                func_002A7750(object, 9, -1);
                if (object[0x43] != 3) func_002A7470(object, 3, func_002A77E0(ANIM_FRAMES(0x54)), 20);
            } else if (*(u16 *)(object + 0x96) >= 301) {
                func_002A7750(object, 4, 1);
                if (object[0x43]) func_002A7470(object, 0, func_002A77E0(ANIM_FRAMES(0x48)), 20);
            }
            break;
        case 14:
            func_L03_003C41B8(object, (int)(state + 0x340), 0);
            if (func_002B3868(object)) D_0018CB2C[0] = -1;
            if (SP(0x194)) func_L03_003C5B28(object, func_00283B98(OF(0xF8), 3.141592741012573f));
            if (SI(0x1A4) & 0x80) func_002A7750(object, 15, -1);
            break;
        case 15:
            if (func_002B3868(object)) {
                if (object[0x43] != 4) func_002A7470(object, 4, 0, 10);
                *(int *)(object + 0x98) = 0;
                func_00282CF0(state + 0x340, state + 0x340, SP(0x358) + 0x10);
                func_002AFDD8((char *)SP(0x358), (char *)(state + 0x340), (char *)(state + 0x340), 0);
                SF(0x344) = 0;
                if (SF(0x340) < SF(0x344)) SF(0x340) = -3.8f;
                else SF(0x340) = 3.8f;
                func_00283098(state + 0x340, state + 0x340, SP(0x358) + 0xC0);
                func_00282CC0(state + 0x340, state + 0x340, SP(0x358) + 0x10);
            }
            heading = func_00283248(*(float *)(SP(0x358) + 0x10) - OF(0x10), *(float *)(SP(0x358) + 0x14) - OF(0x14));
            func_L01_00322288((int)object, heading);
            if (func_0029F530((char *)object) > 11.0f) func_L02_00321C30(object + 0x10, state + 0x340, 0.13333334f);
            if (object[0x60] & 2) {
                func_L03_00419A60(SI(0x220), SP(0x358) + 0x10, 1);
                func_002A7750(object, 16, -1);
                if (object[0x43] != 5) func_002A7470(object, 5, 0, 5);
                func_L00_003294F0(SP(0x358), 1);
            }
            break;
        case 16:
            if (func_002B3868(object)) SP(0x198) = 0;
            if (func_00282E80(D_00189EA0, SP(0x358) + 0x10) > 12.0f &&
                !func_L03_003C5CE8(object) && !func_L03_003CAAC8(SP(0x358), D_00189EA0))
                func_L03_003C5EE8(object);
            break;
        case 17:
            func_00282CF0(&point, state + 0x340, object + 0x10);
            func_002AC9F8(point.f, 0.4166666865348816f);
            func_00282CC0(object + 0x10, object + 0x10, &point);
            if (object[0x42] == object[0x43]) {
                qcopy(object + 0x10, state + 0x340);
                func_002A7750(object, 6, 1);
            }
            break;
        case 18:
            func_L03_003C41B8(object, (int)(state + 0x340), 0);
            if (SP(0x194)) func_L03_003C5B28(object, func_00283B98(OF(0xF8), 3.141592741012573f));
            if (SI(0x1A4) & 0x80) {
                func_002A7750(object, 19, -1);
                func_L00_003294F0(SP(0x358), 1);
            }
            break;
        case 19:
            if (func_002B3868(object) && object[0x43] != 4) func_002A7470(object, 4, 0, 10);
            func_L01_00322288((int)object, func_00283248(*(float *)(SP(0x358) + 0x10) - OF(0x10), *(float *)(SP(0x358) + 0x14) - OF(0x14)));
            if (object[0x42] == object[0x43]) {
                if (func_0029F530((char *)object) >= 10.0f) {
                    func_0029FCC0((char *)object, 3, (char *)&point);
                    func_L03_003CA220(SP(0x358), point.f[2] - OF(0x18));
                }
                if (object[0x60] & 2) {
                    func_002A7750(object, 6, 1); func_L00_003294F0(SP(0x358), 0);
                }
            }
            D_0018CF58[0] = -1;
            break;
        case 20:
            func_L03_003C41B8(object, (int)(state + 0x340), 0);
            if (SP(0x194)) func_L03_003C5B28(object, func_00283B98(OF(0xF8), 3.141592741012573f));
            if (SI(0x1A4) & 0x80) func_002A7750(object, 21, -1);
            break;
        case 21:
            if (func_002B3868(object)) {
                if (object[0x43] != 5) func_002A7470(object, 5, 0, 10);
                D_0018CDE4[0] = -1;
            }
            func_L01_00322288((int)object, func_00283248(*(float *)(SP(0x358) + 0x10) - OF(0x10), *(float *)(SP(0x358) + 0x14) - OF(0x14)));
            if (object[0x60] & 2) func_002A7750(object, 6, 1);
            else if (func_002AEB60((char *)object, 20.0f)) func_L00_003294F0(SP(0x358), 1);
            break;
        case 22: {
            MotionVector *offset;
            func_00282CC0(object + 0x10, object + 0x10, state + 0x1B0);
            qzero_nc(&point); qzero_nc(&other);
            type = *(s16 *)(object + 0xAA);
            height = 0.8f;
            switch (type) {
            case 0x964:
                height = 0.3f;
            case 0x940:
            case 0x93C:
            default:
                do {
                    point.f[2] = height;
                } while (0);
                other.f[2] = height;
                break;
            }
            offset = &other;
            func_00283098(&point, &point, object + 0xC0);
            if (SF(0x1B8) < 0.0f) {
                SF(0x1B8) -= SF(0x398);
                if (OF(0xF4) > 0.0f) func_002AA548(object + 0xF4, state + 0x39C, 0, 0.006981317885220051f, 0.006981317885220051f, 0.41887909173965454f);
                else OF(0xF4) = func_00283BE0(OF(0xF4), 0.41887909173965454f);
                if (OF(0x18) < SF(0x3A0)) {
                    floor = func_002A89A8(object + 0x10, 0, 0.5f);
                    if (OF(0x18) <= floor) {
                        OF(0x18) = floor; func_002A7750(object, 4, 1);
                        for (member = D_L03_001B2A1C; member <= D_L03_001B2A20; member += 256) {
                            if (*(s16 *)(member + 0xAA) == 0xF2D && func_L03_00419C00(member, object + 0x10, object + 0x10)) {
                                SI(0x220) = ((int)member - (int)D_L03_001B2A1C) >> 8;
                                SI(0x368) = -1; SI(0x36C) = -1;
                            }
                        }
                    }
                }
            } else {
                SF(0x1B8) -= SF(0x394); OF(0xF4) = func_00283BE0(OF(0xF4), 0.41887909173965454f);
            }
            func_002833F0(object + 0xC0, object + 0xF0);
            func_00283098(offset, offset, object + 0xC0);
            func_00282CF0(&delta, &point, offset);
            func_00282CC0(object + 0x10, object + 0x10, &delta);
            break;
        }
        }
    }
    code = object[0x20];
    if (code != 22 && code != 1 && code != 15 && code != 16 && (SF(0x1A0) < OF(0x18) - 0.05f || SP(0x198))) {
        float zero = 0.0f;
        OF(0xF0) = zero; OF(0xF4) = zero; func_002B5258((char *)object);
    }
    func_L03_003C4468(object);
    func_002A677C(object);
}
