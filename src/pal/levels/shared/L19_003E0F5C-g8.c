/* func_PAL_L19_003E0F5C, the PAL copy of func_L19_003DCCC8: the same C at 50 Hz, where the last
 * argument of every func_PAL_002A7E68 call, 10, becomes 8, object[0xBC] is scaled by 5/6 and the
 * func_002B60B0 floats change. */
#include "common.h"

extern int func_002B3868(u8 *);
extern int func_002A77E0(int);
extern void func_PAL_002A7E68(u8 *, int, int, int);
extern void func_002A7750(u8 *, int, int);
extern void func_002B60B0(u8 *, float, float, float, float);
extern int func_L09_0033E690(u8 *, int, float);
/* Defined in L18_003F8EA8-qcopy.c; the float takes its place among the integers here. */
extern int func_L18_003F8EA8(u8 *, u8 *, int, float, s16 *, int);
extern int func_L18_0033B628(u8 *, int, int);
extern int func_L18_003FA8E0(int);
extern void func_L18_003FA908(int);
extern float func_L02_002F21C0(u8 *, u8 *);
extern void func_L18_003FB5E8(u8 *, u8 *);
extern void func_00282F20(u8 *, u8 *, float);
extern void func_00282CC0(u8 *, u8 *, u8 *);
extern int func_L02_004127F8(u8 *);
extern void func_PAL_L18_003FF648(u8 *, int);
extern int func_002B1C20(u8 *, u8 *);
extern void func_PAL_002A7650(u8 *, int, int);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_0029F338(u8 *);
extern void func_L18_003F8FA8(u8 *);
extern int D_0018C0B4 NOT_SDA;
extern u8 D_00189EA0[];
extern u8 D_L19_001A8F20[] __attribute__((sda));
extern u16 *D_L19_001FB5A0[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern int D_L19_001B2A38 __attribute__((sda));
extern u8 *D_L19_001B2B0C[] __attribute__((sda));

typedef struct { u8 pad[0x30]; u8 pos[0x10]; u8 rest[0x40]; } TargetRecord;

#define WORD(p,o) (*(int *)((p)+(o)))
#define HALF(p,o) (*(s16 *)((p)+(o)))
#define UHALF(p,o) (*(u16 *)((p)+(o)))
#define FLOAT(p,o) (*(float *)((p)+(o)))
#define PTR(p,o) (*(u8 **)((p)+(o)))

void func_PAL_L19_003E0F5C(u8 *object)
{
    u8 temp[16] __attribute__((aligned(16)));
    u8 position[16] __attribute__((aligned(16)));
    u8 *state = PTR(object, 0x68);
    u8 *entity;
    u16 *p;
    float best, distance;
    int hit;
    switch (object[0x20]) {
    case 0: break;
    case 1:
        if (func_002B3868(object)) {
            if (object[0x43] != func_002A77E0(2))
                func_PAL_002A7E68(object, func_002A77E0(2), 0, 8);
        }
        break;
    case 2:
        if (func_002B3868(object)) {
            func_002B60B0(object, 0.0032000002f, 0.080000006f, 0.010053098f, 0.25132746f);
            if (object[0x43] != func_002A77E0(2))
                func_PAL_002A7E68(object, func_002A77E0(2), 0, 8);
        } else if (HALF(state, 0x768)) {
            func_002A7750(object, 5, 2);
            func_002A7750(object, 4, -1);
        }
        break;
    case 3:
        if (func_002B3868(object)) {
            if (object[0x43] != func_002A77E0(2) + 4)
                func_PAL_002A7E68(object, func_002A77E0(2) + 4, 0, 8);
            object[0xBC] = ((s32)(func_002A77E0(180) + 120) * 5 + 2) / 6;
        } else if (UHALF(object, 0x96) > object[0xBC])
            func_002A7750(object, object[0x94], -1);
        break;
    case 4:
        if (func_002B3868(object)) {
            if (object[0x43] != func_002A77E0(2) + 2)
                func_PAL_002A7E68(object, func_002A77E0(2) + 2, 0, 8);
        } else if (object[0x60] & 2)
            func_002A7750(object, object[0x94], -1);
        break;
    case 5:
        if (func_002B3868(object)) {
            if (WORD(state, 0x714) == -1 || D_0018C0B4 == 0x6F) {
                goto enter_pause;
            }
            object[0xBC] = 0;
            func_002B60B0(object, 0.006f, 0.15f, 0.010053098f, 0.25132746f);
            if (object[0x43] != func_002A77E0(2) + 6)
                func_PAL_002A7E68(object, func_002A77E0(2) + 6, 0, 8);
            HALF(state, 0x760) = func_L09_0033E690(object+0x10, WORD(state, 0x714), 0.0f);
        } else if (object[0xBC] == 0) {
            func_L18_003F8EA8(object, state+0x700, WORD(state, 0x714), 4.0f, (s16 *)(state+0x760), HALF(state, 0x76C));
            if (D_0018C0B4 == 0x6F || (UHALF(object, 0x96) % 180 == 0 && func_002A77E0(4) == 0)) {
enter_pause:
                object[0xBC] = 1;
                if (object[0x43] != func_002A77E0(2) + 4)
                    func_PAL_002A7E68(object, func_002A77E0(2)+4, 0, 8);
            }
        } else if (object[0xBC] == 1 && (object[0x60] & 2)) {
            func_002A7750(object, 5, -1);
            func_002A7750(object, 4, -1);
        }
        if (!HALF(state, 0x768)) {
            if (WORD(state, 0x750)) func_002A7750(object, 7, -1);
            else if (WORD(state, 0x744) != -1) func_002A7750(object, 8, -1);
            else func_002A7750(object, 2, -1);
        } else if (WORD(state, 0x754) != -1) {
            if (func_L18_0033B628(object+0x10, WORD(state, 0x754), 0) &&
                func_L18_0033B628(D_00189EA0, WORD(state, 0x754), 0) &&
                func_L18_003FA8E0(WORD(object, 0xB8)))
                func_002A7750(object, 6, -1);
        } else if (func_L18_003FA8E0(WORD(object, 0xB8)))
            func_002A7750(object, 6, -1);
        break;
    case 6:
        if (func_002B3868(object)) {
            object[0xBC] = 0;
            if (object[0x43] != func_002A77E0(2)+2)
                func_PAL_002A7E68(object, func_002A77E0(2)+2, 0, 8);
        } else if (object[0xBC] == 0 && (object[0x60] & 2)) {
            object[0xBC] = 1;
            func_002B60B0(object, 0.006f, 0.15f, 0.010053098f, 0.25132746f);
            if (object[0x43] != func_002A77E0(2)+6)
                func_PAL_002A7E68(object, func_002A77E0(2)+6, 0, 8);
        } else if (object[0xBC] == 1) {
            qcopy(state+0x700, D_00189EA0);
            HALF(state, 0x76A) = 1;
            if (WORD(state, 0x754) != -1 &&
                (!func_L18_0033B628(object+0x10, WORD(state, 0x754), 0) ||
                 !func_L18_0033B628(D_00189EA0, WORD(state, 0x754), 0))) {
                func_L18_003FA908(WORD(object, 0xB8));
                func_002A7750(object, 5, -1);
            } else if (func_L02_002F21C0(object+0x10, state+0x700) < FLOAT(state, 0x72C)*FLOAT(state, 0x72C)) {
                object[0xBC] = 2;
                if (object[0x43] != func_002A77E0(2)+4)
                    func_PAL_002A7E68(object, func_002A77E0(2)+4, 0, 8);
            }
        } else if (object[0xBC] == 2 && (object[0x60] & 2))
            func_002A7750(object, 6, -1);
        if (!HALF(state, 0x768)) {
            func_L18_003FA908(WORD(object, 0xB8));
            if (WORD(state, 0x750)) func_002A7750(object, 7, -1);
            else if (WORD(state, 0x744) != -1) func_002A7750(object, 8, -1);
            else func_002A7750(object, 2, -1);
        }
        break;
    case 7:
        if (func_002B3868(object)) {
            if (object[0x43] != func_002A77E0(2)+6)
                func_PAL_002A7E68(object, func_002A77E0(2)+6, 0, 8);
            best = 1000.0f;
            for (p=D_L19_001FB5A0[WORD(state, 0x74C)];
                 (WORD(state, 0x74C)&255)!=255 && WORD(state, 0x74C)<=D_L19_001B2A38 && p &&
                 ((p != 0 && (s16)p[-1]>=0) || p==D_L19_001FB5A0[WORD(state, 0x74C)]); p++) {
                entity=D_L19_001B2A1C[0]+((*p&0x7FFF)<<8);
                if (!entity) break;
                distance=func_L02_002F21C0(object+0x10, entity+0x10);
                if (distance<best) { PTR(state, 0x750)=entity; best=distance; }
            }
            func_L18_003FB5E8(PTR(state, 0x750), position);
            func_00282F20(temp, PTR(state, 0x750)+0xD0, -1.0f);
            func_00282CC0(state+0x700, position, temp);
        }
        HALF(state, 0x76A)=1;
        if (func_L02_002F21C0(object+0x10, state+0x700)<0.25f) {
            if (HALF(state, 0x76E)>=5) func_0029F338(object);
            else { HALF(state, 0x76E)++; func_L18_003F8FA8(object); }
        } else if (!func_L02_004127F8(PTR(state, 0x750))) {
            func_L18_003FB5E8(PTR(state, 0x750), temp);
            if (func_L02_002F21C0(object+0x10, temp)<4.0f)
                func_PAL_L18_003FF648(PTR(state, 0x750), 0);
        }
        break;
    case 8:
        if (func_002B3868(object)) {
            if (object[0x43] != func_002A77E0(2)+6)
                func_PAL_002A7E68(object, func_002A77E0(2)+6, 0, 8);
            qcopy(state+0x700, ((TargetRecord *)D_L19_001B2B0C[0])[WORD(state, 0x744)].pos);
        }
        HALF(state, 0x76A)=1;
        if (func_L02_002F21C0(object+0x10, state+0x700)<0.25f)
            func_002A7750(object, 2, -1);
        break;
    case 9:
        hit=func_002B1C20(object, state+0x60);
        if ((object[0x42]==9 && func_002A77E0(30)==0) || (hit&1)) {
                if (object[0x94]==6) func_L18_003FA908(WORD(object, 0xB8));
                func_PAL_002A7650(object, 0, 3);
                func_PAL_002AC718(object, D_L19_001A8F20, object+0x10, 0.0f, 0.0f, 20, 0, 10,
                             0.0f, 0.0f, 9.0f, 1.0f, -1, 3.0f, 1, 5, -1, 0, 0x810001);
                if (HALF(state, 0x76E)>=4) func_0029F338(object);
                else { HALF(state, 0x76E)++; func_L18_003F8FA8(object); }
        } else if (hit&2) func_002A7750(object, object[0x94], 2);
        break;
    }
}
