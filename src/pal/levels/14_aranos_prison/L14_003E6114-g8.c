/* func_PAL_L14_003E6114, the PAL copy of func_L14_003E1E78: the same C, where each timer scales 5/6, written before
   the emit timer, and the closing state clears flags ahead of requested. */
#include "common.h"

typedef struct {
    char pad00[0x5C];
    int flags;
    int proximity;
    int contact;
    int mobIndex;
    unsigned char *linked;
    int openTime;
    int activeTime;
    int closeTime;
    int timer;
    int requested;
    int color;
    int emitTimer;
} FieldState;

typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char state;
    char pad21[3];
    char *model;
    char pad28[9];
    unsigned char active;
    char pad32[2];
    unsigned short flags;
    char pad36[0x32];
    FieldState *data;
    char pad6C[0xC];
    int color;
    char pad7C[0x1C];
    int animation;
} FieldMob;

extern void func_002A04B8(void *, int *, int *, int *);
extern void func_002A0488(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern int func_00282948(int *);
extern int func_00283D38(int, int, float);
extern void func_L00_002E6EF8(void (*)(char *), char *);
extern int func_L00_00324120(void *);
extern void func_L14_00328E70(void *, void *, void *);
extern void func_L14_00328E90(void *, void *, void *);
extern void func_L14_003E2238(void *);
extern float func_PAL_L14_003E6618(void *);
extern void func_L14_003E2328(char *self);
extern void func_L14_003E2980(void *);

/* The level's entity array, read as a bare symbol (lui/lw) as in the level's other units. */
extern unsigned char *D_L14_001B259C_base[3] __asm__("D_L14_001B259C") __attribute__((sda));
extern float D_00189EA8 NOT_SDA;
extern FieldMob *D_0018A0B4 NOT_SDA;
extern int D_L14_001B04C4 __attribute__((sda));
extern int D_L14_001B04C8 __attribute__((sda));
extern int D_L14_001B04CC __attribute__((sda));
extern int D_L14_001B04D0 __attribute__((sda));

/* Widening after the three high-channel terms preserves the color grouping. */

/* A field that cycles off (1) -> rising (2) -> on (3) -> falling (4) -> off. Rising and
   falling run the same emitter, colour fade and draw (written out in both cases; the compiler
   cross-jumps the copies into one tail, as in retail); the on state can pass a request on to
   the linked entity when that is another field (class 0xAFE). */
void func_PAL_L14_003E6114(FieldMob *self) {
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    int r, g, bl, c;
    FieldState *s = self->data;
    unsigned char *e;

    switch (self->state) {
    case 0:
        func_002A04B8(self, &r, &g, &bl);
        s->color = (long long)(int)(0x80000000 + (bl << 16) + (g << 8)) + r;
        if (s->mobIndex != -1) {
            s->linked = D_L14_001B259C_base[0] + (s->mobIndex << 8);
        } else {
            s->linked = 0;
        }
        s->requested = 0;
        self->color = 0x80008000;
        self->flags |= 0x10;
        if (s->proximity) {
            func_002A7750(self, 3, -1);
        } else {
            func_002A7750(self, 1, -1);
        }
        break;
    case 4:
        if (func_002B3868(self)) {
            self->flags |= 0x100;
            s->flags = 0;
            s->requested = 0;
            self->color = 0x80000080;
            s->timer = ((s32)(s->closeTime) * 5 + 2) / 6;
            s->requested = 0;
            s->emitTimer = ((s32)(D_L14_001B04D0) * 5 + 2) / 6;
        }
        if (func_00282948(&s->timer)) {
            func_002A7750(self, 1, -1);
        }
        if (func_00282948(&s->emitTimer)) {
            func_L14_003E2980(self);
            s->emitTimer = ((s32)(D_L14_001B04D0) * 5 + 2) / 6;
        }
        c = (long long)(int)(0xFF000000 | (D_L14_001B04CC << 16) | (D_L14_001B04C8 << 8)) | D_L14_001B04C4;
        c = func_00283D38(c, s->color, func_PAL_L14_003E6618(self));
        func_002A0488(self, c & 0xFF, (c >> 8) & 0xFF, (c >> 16) & 0xFF);
        func_L14_00328E70(self, a, b);
        func_L14_003E2238(self);
        func_L14_00328E90(self, a, b);
        func_L00_002E6EF8(func_L14_003E2328, (char *)self);
        break;
    case 1:
        if (func_002B3868(self)) {
            self->active = 0;
            self->animation = 0;
            self->flags |= 1;
        }
        if (s->requested || (s->proximity && self->position[2] > D_00189EA8)) {
            func_002A7750(self, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(self)) {
            self->active = 1;
            self->flags = (self->flags | 0x100) & 0xFFFE;
            self->animation = *(int *)(self->model + 0x10);
            s->timer = ((s32)(s->openTime) * 5 + 2) / 6;
            s->emitTimer = ((s32)(D_L14_001B04D0) * 5 + 2) / 6;
        }
        if (func_00282948(&s->timer)) {
            func_002A7750(self, 3, -1);
        }
        if (func_00282948(&s->emitTimer)) {
            func_L14_003E2980(self);
            s->emitTimer = ((s32)(D_L14_001B04D0) * 5 + 2) / 6;
        }
        c = (long long)(int)(0xFF000000 | (D_L14_001B04CC << 16) | (D_L14_001B04C8 << 8)) | D_L14_001B04C4;
        c = func_00283D38(c, s->color, func_PAL_L14_003E6618(self));
        func_002A0488(self, c & 0xFF, (c >> 8) & 0xFF, (c >> 16) & 0xFF);
        func_L14_00328E70(self, a, b);
        func_L14_003E2238(self);
        func_L14_00328E90(self, a, b);
        func_L00_002E6EF8(func_L14_003E2328, (char *)self);
        break;
    case 3:
        if (func_002B3868(self)) {
            self->flags &= 0xFEFF;
            if (s->contact) {
                s->flags |= 0x20;
            } else {
                s->flags |= 1;
            }
            s->timer = ((s32)(s->activeTime) * 5 + 2) / 6;
            self->color = 0x80008000;
        }
        if ((func_L00_00324120(self) && !s->contact) || (D_0018A0B4 == self && s->contact)) {
            e = s->linked;
            if (e != 0 && *(short *)(e + 0xAA) == 0xAFE) {
                *(int *)(*(char **)(e + 0x68) + 0x80) = 1;
            }
        }
        if (s->proximity && self->position[2] > D_00189EA8) {
            s->timer = ((s32)(s->activeTime) * 5 + 2) / 6;
        }
        if (func_00282948(&s->timer)) {
            func_002A7750(self, 4, -1);
        }
        break;
    }
}

