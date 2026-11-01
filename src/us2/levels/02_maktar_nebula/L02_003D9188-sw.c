#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef struct Actor Actor;
typedef struct {
    u8 pad000[0x30];
    float x30;
    u8 pad034[0x48];
    float x7C;
    u8 pad080[0x70];
    Quadword xF0;
    u8 pad100[0xF2];
    u8 x1F2;
    u8 pad1F3[0x1D];
    float scale[3];
    u8 pad21C[0x14];
    float home[4];
    Actor *target;
    int proxy;
    u8 pad248[4];
    float x24C;
    u8 pad250[0x10];
    Actor *launcher;
    Actor *child;
    u8 pad268[4];
    int sound;
    u8 pad270[0x10];
    short x280;
    u8 pad282[6];
    short timer;
    short savedMode;
    short savedAnim;
    u8 savedPhase;
    u8 pad28F;
    short forced;
    short x292;
} SentryState;
struct Actor {
    u8 pad00[0x10];
    float position[4];
    u8 mode;
    u8 pad21[0x13];
    unsigned short flags;
    u8 pad36[0xC];
    u8 previousAnim;
    u8 anim;
    u8 pad44[4];
    float x48;
    u8 pad4C[0x14];
    u8 x60;
    u8 pad61[7];
    SentryState *state;
    u8 pad6C[0x2A];
    unsigned short stateTime;
    u8 pad98[4];
    int x9C;
    u8 padA0[0x18];
    Actor *parent;
    u8 phase;
    u8 padBD[0x33];
    float rot[4];
    u8 pad100[0];
};
typedef struct { u8 prefix[0x160]; float amount; int reserved164; int kind; int detail; } EffectTuning;
extern u8 D_L02_001BA500[];
extern u8 D_L02_001BA3C0[];
#define EFFECT ((EffectTuning *)D_L02_001BA3C0)
extern int D_L02_001A903C;
typedef struct { u8 prefix[0x229C]; int motion; u8 reserved22A0[0x1FC]; Actor *damage; } ResidentView;
extern u8 D_00189E20[];
#define RESIDENT ((ResidentView *)D_00189E20)
extern u8 D_001A7A60[] MACRO_ADDR;
extern Actor *D_L02_001B359C;
extern float D_L02_001B03F0[4] __attribute__((sda));
extern float D_L02_001B0400[4] __attribute__((sda));
extern float D_L02_001A8F20[4] MACRO_ADDR;
extern u8 D_00188660[];
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283248(float, float);
extern float func_0029F530(Actor *);
extern int func_002B3868(Actor *);
extern void func_002A7470(Actor *, int, int, int);
extern void func_002A7750(Actor *, int, int);
extern float func_002A7878(float, float);
extern void func_L02_003FC020(Actor *, Actor *);
extern float func_00283C80(float, float);
extern void func_L02_003FC248(void *, int, int);
extern int func_002E5E58(int, int, void *);
extern void func_US2_002B1880(int, int);
extern int func_00282978(short *);
extern void func_00282C88(Quadword *);
extern void func_L02_003D91A0(Actor *);
extern float func_002A89A8(void *, int, float);
extern float *func_L02_003FC098(Actor *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_L02_003329C8(Actor *, void *, float, float);
extern void func_L02_003DB9E0(Actor *);
extern int func_002E5CF8(int, int, Actor *);
extern void func_L02_003DB938(Actor *);
extern void func_L02_003D4990(Actor *);
extern float func_L02_00321C30(void *, void *, float);
extern void func_L02_003DB2F0(Actor *);
extern int func_00283CF0(float);
extern int func_L02_003DB950(Actor *);
extern int func_002E59B0(Actor *, int);
extern void func_002E59F8(int);
extern void func_L02_003DB200(Actor *);
extern float func_00283CE0(int);
extern void func_L02_0032B468(Actor *, int, void *, void *, int, int, void *, void *, void *, float);
extern void func_L02_003DBB70(Actor *, void *);
extern void func_0029F338(Actor *);
extern int func_002E5DA0(int, int, Actor *, int);
extern void *func_0032C700(void *, int, int, float, int, int, int, int, int, float, int, int, int, void *);
extern void func_0029FCC0(Actor *, int, void *);
extern void func_002A7A00(float *, float, float);
extern void func_002B0A68(Actor *, int, float *, float, float, float, float, unsigned char);
extern void func_L02_003DB6D8(Actor *);
extern void func_L02_003D9608(Actor *);
#define PROXY (D_L02_001B359C + self->state->proxy)

/* Drive this actor's emergence, movement, attacks and destruction. */
void func_US2_L02_003D9188(Actor *self)
{
    SentryState *state;
    char *slot;
    Actor *child;
    float target[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float curve[4] __attribute__((aligned(16)));
    float distance, yaw, frame, facing, value;
    short damageKind;
    int sound;

    func_L02_003D91A0(self);
    state = self->state;
    *(Quadword *)target = 0;
    if (state->target) {
        qcopy(target, state->target->position);
    }
    distance = func_00282E80(self->position, target);
    yaw = func_00283248(target[0] - self->position[0], target[1] - self->position[1]);
    frame = func_0029F530(self);
    damageKind = 0;
    if (RESIDENT->damage) {
        damageKind = *(short *)((char *)RESIDENT->damage + 0xAA);
    }
    if (RESIDENT->motion == 7 || RESIDENT->damage == self || damageKind == 0xD08) {
        state->forced = 1;
    }
    switch (self->mode) {
    case 0:
    case 1:
        break;
    case 2:
        state->forced = 0;
        if (func_002B3868(self)) {
            self->phase = 0;
            self->stateTime = 0;
            func_002A7470(self, 0, 0, 3);
            if (PROXY->anim) {
                func_002A7470(PROXY, 0, 0, 10);
                break;
            }
            break;
        }
        if (self->phase == 0 && self->stateTime > 60) {
            self->phase = 1;
            if (self->anim != 3) {
                func_002A7470(self, 3, 0, 10);
            }
            if (PROXY->anim != 6) {
                func_002A7470(PROXY, 6, 0, 10);
            }
            self->position[2] = func_002A89A8(self->position, 0, 10.0f);
            func_00282CF0(direction, func_L02_003FC098(self->parent), self->position);
            direction[2] = 0.0f;
            func_00282F20(direction, direction, 30.0f);
            func_00282CC0(direction, direction, self->position);
            direction[2] = func_L02_003FC098(self->parent)[2];
            func_L02_003329C8(self, direction, 0.33333334f, state->x7C);
            break;
        }
        else if (self->phase == 1 && (self->x60 & 2)) {
            self->phase = 2;
            if (self->anim != 4) {
                func_002A7470(self, 4, 0, 7);
            }
            if (PROXY->anim != 7) {
                func_002A7470(PROXY, 7, 0, 10);
                break;
            }
            break;
        }
        else if (self->phase == 2 && self->position[2] < func_L02_003FC098(self->parent)[2] + 0.05f) {
            func_00282C88(&state->xF0);
            self->phase = 3;
            state->x292 = 0;
            if (self->anim != 5) {
                func_002A7470(self, 5, 3, 2);
            }
            if (PROXY->anim != 8) {
                func_002A7470(PROXY, 8, 0, 10);
            }
            func_L02_003DB9E0(self);
            break;
        }
        else if (self->phase == 3) {
            value = func_0029F530(self);
            if (value > 2.0f && !state->x292) {
                state->x292 = 1;
                func_002E5CF8(0, 0, self);
            }
            if (self->x60 & 2) {
                EFFECT->amount = 0.35f;
                EFFECT->kind = 25;
                EFFECT->detail = 0;
                func_00282C88(&state->xF0);
                if (self->anim) {
                    func_002A7470(self, 0, 0, 0);
                }
                if (PROXY->anim) {
                    func_002A7470(PROXY, 0, 0, 0);
                }
                func_002A7750(self, 5, 1);
                state->timer = func_00283CF0(func_002A7878(600.0f, 1200.0f));
            }
        }
        break;
    case 3:
        if (func_002B3868(self)) {
            self->phase = 0;
            qcopy(state->home, D_L02_001B0400);
            if (self->anim != 1) {
                func_002A7470(self, 1, 0, 10);
            }
            func_L02_003DB938(self);
            func_L02_003D4990(state->child);
            func_L02_003FC020(self->parent, state->child);
            func_00282C88(&state->xF0);
            self->stateTime = 0;
            break;
        }
        if (self->phase == 0) {
            value = func_00282E80(self->position, state->home);
            if (value < 0.01f) {
                self->phase = 1;
                if (self->anim != 3) {
                    func_002A7470(self, 3, 0, 10);
                }
                if (PROXY->anim != 6) {
                    func_002A7470(PROXY, 6, 0, 10);
                }
                func_00282C88(&state->xF0);
                func_L02_003329C8(self, D_L02_001B03F0, 0.33333334f, state->x7C);
                break;
            }
        }
        if (self->phase == 1 && (self->x60 & 2)) {
            self->phase = 2;
            self->stateTime = 0;
            if (self->anim != 4) {
                func_002A7470(self, 4, 0, 10);
            }
            if (PROXY->anim != 7) {
                func_002A7470(PROXY, 7, 0, 10);
                break;
            }
        } else if (self->phase == 2) {
            value = func_00282E48(self->position, D_L02_001B03F0);
            if (!(value < 1.0f) && self->stateTime < 301) {
                break;
            }
            self->phase = 3;
            if (self->anim != 5) {
                func_002A7470(self, 5, 0, 10);
            }
            if (PROXY->anim != 8) {
                func_002A7470(PROXY, 8, 0, 10);
                break;
            }
        } else if (self->phase == 3 && (self->x60 & 2)) {
            func_002A7750(self, 4, -1);
        }
        break;
    case 4:
        if (func_002B3868(self)) {
            if (self->anim) {
                func_002A7470(self, 0, 0, 10);
            }
            if (PROXY->anim) {
                func_002A7470(PROXY, 0, 0, 10);
            }
        }
        func_L02_00321C30(self->position, D_L02_001B03F0, 0.16666667f);
        if (state->x280 == 1 && func_00282E80(self->position, D_L02_001B03F0) < 0.001f) {
            func_002A7750(self, 2, 1);
        }
        break;
    case 5:
        if (func_002B3868(self)) {
            if (self->anim != 1) {
                func_002A7470(self, 1, 0, 15);
            }
            if (PROXY->anim != 1) {
                func_002A7470(PROXY, 1, 0, 10);
            }
            self->phase = 1;
        }
        facing = func_00283C80(yaw, self->rot[2]);
        if (self->phase == 1 && facing > 0.78539824f) {
            self->phase = 2;
            if (self->anim != 2) {
                func_002A7470(self, 2, 0, 15);
            }
            if (PROXY->anim != 3) {
                func_002A7470(PROXY, 3, 0, 10);
            }
        }
        if (self->phase == 2 && facing < 0.17453295f) {
            self->phase = 1;
            if (self->anim != 1) {
                func_002A7470(self, 1, 0, 15);
            }
            if (PROXY->anim != 1) {
                func_002A7470(PROXY, 1, 0, 10);
            }
        }
        if (self->phase == 1 && distance < 10.0f) {
            self->phase = 0;
            if (self->anim) {
                func_002A7470(self, 0, 0, 15);
            }
        }
        if (self->phase == 0 && distance > 20.0f) {
            self->phase = 1;
            if (self->anim != 1) {
                func_002A7470(self, 1, 0, 10);
            }
        }
        if (RESIDENT->damage) {
            func_L02_003DB2F0(self);
        }
        if (func_00282978(&state->timer)) {
            state->timer = func_00283CF0(func_002A7878(600.0f, 1200.0f));
            func_002A7750(self, 6, -1);
        }
        if (func_L02_003DB950(self)) {
            func_002A7750(self, 3, 0);
        }
        break;
    case 6:
        if (func_002B3868(self)) {
            if (self->previousAnim == 7) {
                self->phase = 1;
                if (PROXY->anim != 10) {
                    func_002A7470(PROXY, 10, 0, 10);
                }
            } else if (self->previousAnim == 6) {
                self->phase = 0;
                self->flags &= 0xEFFF;
            } else {
                if (self->anim != 6) {
                    func_002A7470(self, 6, 0, 0);
                }
                if (PROXY->anim != 9) {
                    func_002A7470(PROXY, 9, 0, 10);
                }
                self->phase = 0;
                self->flags &= 0xEFFF;
            }
        } else if (self->phase == 0 && frame > 28.0f) {
            if (self->anim != 7) {
                func_002A7470(self, 7, 0, 0);
            }
            if (PROXY->anim != 10) {
                func_002A7470(PROXY, 10, 0, 10);
            }
            self->phase = 1;
            state->x30 = 1.5f;
            self->flags |= 0x1000;
            if (!func_002E59B0(self, state->sound)) {
                state->sound = func_002E5CF8(6, 4, self);
            }
        } else if (self->phase == 1) {
            self->x9C = 1;
            if (func_00282978(&state->timer) || func_L02_003DB950(self)) {
                if (self->anim != 8) {
                    func_002A7470(self, 8, 0, 0);
                }
                if (PROXY->anim != 11) {
                    func_002A7470(PROXY, 11, 0, 10);
                }
                self->phase = 2;
                self->flags &= 0xEFFF;
            }
        }
        if (self->phase == 1 && RESIDENT->damage) {
            func_L02_003DB2F0(self);
            break;
        }
        if (self->phase == 2 && frame > 45.0f) {
            state->x30 = 11.0f;
            self->x9C = 0;
            self->flags |= 0x1000;
            state->timer = func_00283CF0(func_002A7878(600.0f, 1200.0f));
            func_002A7750(self, 5, -1);
            sound = state->sound;
            if (sound != -1) {
                slot = (char *)D_00188660 + sound * 0x70;
                if (*(Actor **)(slot + 0x88) == self && *(u8 *)(slot + 0x74)) {
                    func_002E59F8(sound);
                }
            }
            state->sound = -1;
        }
        break;
    case 7:
        if (func_002B3868(self)) {
            if (PROXY->anim != 7) {
                func_002A7470(PROXY, 7, 0, 15);
            }
            state->x24C += 0.1939255f;
            self->stateTime = 0;
        } else if (self->stateTime >= 181) {
            func_002A7750(self, 6, -1);
        }
        break;
    case 8:
        if (func_002B3868(self)) {
            if (self->anim != 8) {
                func_002A7470(self, 8, 0, 20);
            }
            if (PROXY->anim != 9) {
                func_002A7470(PROXY, 9, 0, 15);
            }
            state->x24C += 0.1939255f;
        } else if (frame > 45.0f) {
            func_002A7750(self, state->savedMode, -1);
        }
        break;
    case 9:
        if (func_002B3868(self)) {
            if (PROXY->anim != 12) {
                func_002A7470(PROXY, 12, 0, 15);
            }
        }
        func_L02_003DB200(self);
        if (!(PROXY->x60 & 2)) {
            break;
        }
        self->mode = state->savedMode;
        self->phase = state->savedPhase;
        if (PROXY->anim != state->savedAnim) {
            func_002A7470(PROXY, state->savedAnim, 0, 15);
        }
        break;
    case 10:
        if (func_002B3868(self)) {
            sound = state->sound;
            if (sound != -1) {
                slot = (char *)D_00188660 + sound * 0x70;
                if (*(Actor **)(slot + 0x88) == self && *(u8 *)(slot + 0x74)) {
                    func_002E59F8(sound);
                }
            }
            state->sound = -1;
            if (self->previousAnim == 7) {
                self->phase = 1;
                if (PROXY->anim != 13) {
                    func_002A7470(PROXY, 13, 0, 15);
                }
                break;
            }
            else {
                self->phase = 0;
                if (self->previousAnim != 6 && self->anim != 9) {
                    func_002A7470(self, 9, 0, 15);
                }
            }
            if (PROXY->anim != 13) {
                func_002A7470(PROXY, 13, 0, 15);
            }
            break;
        }
        if (self->phase == 0 && (self->x60 & 2)) {
            self->phase = 1;
            if (PROXY->anim != 13) {
                func_002A7470(PROXY, 13, 0, 15);
            }
            if (self->anim != 7) {
                func_002A7470(self, 7, 0, 10);
                break;
            }
        } else if (self->phase == 1 && (PROXY->x60 & 2)) {
            func_002A7750(self, 11, -1);
        }
        break;
    case 11:
        if (func_002B3868(self)) {
            if (!state->forced && !D_001A7A60[0x13]) {
                D_001A7A60[0x13] = 1;
                func_002E5E58(1, 0, 0);
                func_US2_002B1880(0x1233, -1);
                D_L02_001A903C = 1;
            }
            self->x48 = 0.0f;
            PROXY->x48 = 0.0f;
            self->stateTime = 0;
            func_00282CF0(direction, D_L02_001BA500, PROXY->position);
            func_00282F20(direction, direction, func_002A7878(0.083333336f, 0.116666675f));
            direction[2] += 0.06666667f;
            if (self->state->launcher) {
                func_L02_0032B468(self->state->launcher, 0xA4C, self->state->launcher->position, self->state->launcher->rot, 300, 0, direction,
                        D_L02_001A8F20, D_L02_001A8F20, 0.0013888889f);
                func_L02_003DBB70(self, D_L02_001A8F20);
                func_0029F338(self->state->launcher);
                self->state->launcher = 0;
                func_002E5DA0(5, 0, self, 0xA44);
            }
            func_L02_003FC248(self, 0, -1);
            state->x1F2 = 1;
            state->scale[0] = state->scale[1] = state->scale[2] = 2.0f;
            self->flags &= 0xEFFF;
        }
        value = func_00283CE0(self->stateTime) * -0.0111110555f + 2.0f;
        if (value < 0.0f) {
            value = 0.0f;
        }
        state->scale[0] = state->scale[1] = state->scale[2] = value;
        if (self->stateTime > 180) {
            self->x48 = 1.0f;
            PROXY->x48 = 1.0f;
            func_0032C700(self->position, 1, 25, 2.0f, 20, 30, 40, 45, 1, 20.0f, 0, 1, 0, 0);
            func_0029FCC0(self, 2, direction);
            func_0032C700(self->position, 0, 10, 0.7f, 5, 10, 5, 20, 1, 20.0f, 0, 0, 0, 0);
            func_0029FCC0(self, 6, direction);
            func_0032C700(self->position, 0, 0, 0.7f, 10, 20, 15, 45, 1, 20.0f, 0, 0, 0, 0);
            func_0029FCC0(self, 4, direction);
            func_0032C700(self->position, 0, 20, 0.7f, 0, 15, 10, 30, 1, 20.0f, 0, 0, 0, 0);
            func_0029FCC0(self, 8, direction);
            func_0032C700(self->position, 0, 5, 0.7f, 15, 5, 25, 25, 1, 20.0f, 0, 0, 0, 0);
            func_002A7A00(curve, 0.10000001f, 0.20000002f);
            func_002B0A68(self, 0xFFF, curve, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            func_002A7A00(curve, 0.13333334f, 0.26666668f);
            func_002B0A68(PROXY, 0x1F, curve, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            func_002E5DA0(5, 0, self, 0xA44);
            func_L02_003DB6D8(self);
            state->scale[0] = state->scale[1] = state->scale[2] = 1.0f;
            state->x1F2 = 0;
            child = state->child;
            if (child && child->mode != 254 && child->mode != 253 && child->mode > 2) {
                func_L02_003D4990(child);
                func_L02_003FC020(self->parent, state->child);
            }
        }
        break;
    }
    func_L02_003D9608(self);
}
