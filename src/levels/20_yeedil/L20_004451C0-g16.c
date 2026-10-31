/* func_L20_004451C0: the launch platform's update (the Yeedil twin of func_L18_0042FBC8).
   Own unit, flags -O2 -G16 -ffunction-sections -Wa,-G16 (the -g16 precedent rows in
   config/cflags.txt): the two 16-byte vectors D_L20_001B2290/D_L20_001B22A0 are reached
   through $gp (addiu $aN,$gp,..), which -G8 does not give a 16-byte object.
   D_L20_001A8F20 is MACRO_ADDR, so its address is one `la` macro that the assembler
   expands to an adjacent lui/addiu, after the other argument moves as in retail (with a
   split address the lui is scheduled first). */
#include "common.h"

extern void *func_002A9640(void *, int, int);
extern float func_002A96A0(void *, void *);
extern void func_002AB800(void *, void *);
extern void func_002AB8C0(void *, void *);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern int func_002ACBC8(void *, int);
extern void func_002E59F8(int);
extern int func_002B3868(void *);
extern float func_002A7878(float, float);
extern int func_002E5CF8(int, int, void *);
extern float func_00283B98(float, float);
extern u8 *func_L18_003F75E8(int, int *);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_002ACB48(void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CD8(void *, void *, void *);
extern void func_L18_003F76F0(void *, void *, void *);
extern int func_002A7820(int, int);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_002A6C58(void *, int, int);
extern void func_0029F338(void *);

extern float D_L20_001B2260 __attribute__((sda));
extern float D_L20_001B2264 __attribute__((sda));
extern float D_L20_001B2268 __attribute__((sda));
extern float D_L20_001B226C __attribute__((sda));
extern float D_L20_001B2270 __attribute__((sda));
extern float D_L20_001B227C __attribute__((sda));
extern int D_L20_001B2280 __attribute__((sda));
extern int D_L20_001B2284 __attribute__((sda));
extern float D_L20_001B2290[4] __attribute__((sda));
extern float D_L20_001B22A0[4] __attribute__((sda));
extern u8 D_00189EA0[];
extern u8 D_L20_001A8F20[] MACRO_ADDR;

typedef struct {
    u8 pad00[0x20];
    float timer;
    s16 initialized;
    u8 pad26[0x30 - 0x26];
    float scale;
    u8 pad34[0x50 - 0x34];
    u8 effect[0x10];
    float spinX;
    float spinY;
    u8 pad68[0x70 - 0x68];
    int startId;
    int stopId;
    int group;
    float restHeight;
    float verticalSpeed;
    int spawnTimer;
    int sound;
} PlatformState;

typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[0x68 - 0x21];
    PlatformState *vars;
    u8 pad6C[0x96 - 0x6C];
    u16 frames;
    u8 pad98[0xA8 - 0x98];
    u8 flagA8;
    u8 padA9[0xC0 - 0xA9];
    float matrix[3][4];
    float rotation[4];
} PlatformObject;

/* The sound slots: 0x70 bytes apart, the owner at +0x88 and the active byte at +0x74. */
extern u8 D_00188660[];

void func_L20_004451C0(PlatformObject *self) {
    PlatformState *s = self->vars;
    float dt;
    float zero;
    int count;
    u8 *p;
    float velocity[4];
    float position[4];
    float offset[4];
    float tip[4];

    dt = func_002A96A0(self, func_002A9640(self, 0x10000, 0));
    s->timer -= dt;
    if (dt > 0.0f) {
        func_002AB800(self, s->effect);
        if (s->timer <= 0.0f) {
            func_002A7750(self, 3, -1);
        }
    }
    self->flagA8 = 0xFF;
    func_002AB8C0(self, s->effect);

    switch (self->state) {
    case 0:
        s->restHeight = self->position[2];
        if (s->initialized == 0) {
            s->initialized = 1;
            s->timer = 1.0f;
        }
        s->spawnTimer = -1;
        s->scale = 1.0f;
        func_002A7750(self, 1, -1);
        s->sound = -1;
        break;
    case 1:
        if (func_002A77E0(2) == 0 && s->startId != -1) {
            if (func_002ACBC8(D_00189EA0, s->stopId)) {
                func_002A7750(self, 3, -1);
            } else if (func_002ACBC8(D_00189EA0, s->startId)) {
                func_002A7750(self, 2, -1);
            }
        }
        break;
    case 2:
        if (func_002A77E0(2) == 0 && func_002ACBC8(D_00189EA0, s->stopId)) {
            func_002A7750(self, 3, -1);
            if (s->sound != -1) {
                u8 *slot = D_00188660 + s->sound * 0x70;

                if (*(PlatformObject **)(slot + 0x88) == self && slot[0x74] != 0) {
                    func_002E59F8(s->sound);
                }
            }
            s->sound = -1;
        }
        if (func_002B3868(self)) {
            self->rotation[0] = 0;
            self->rotation[1] = 0;
            zero = self->rotation[0];
            self->position[2] = s->restHeight;
            s->verticalSpeed += func_002A7878(zero, D_L20_001B2260 * 0.016666668f);
            s->spinX = func_002A7878(zero, D_L20_001B2264 * 0.00029088825f);
            s->spinY = func_002A7878(zero, D_L20_001B2268 * 0.00029088825f);
            self->position[2] = s->restHeight;
        }
        {
            u8 *slot = D_00188660 + s->sound * 0x70;

            if (*(PlatformObject **)(slot + 0x88) != self || slot[0x74] == 0) {
                s->sound = func_002E5CF8(0, 4, self);
            }
        }
        if (self->position[2] >= s->restHeight) {
            self->position[2] += s->verticalSpeed;
            s->verticalSpeed -= D_L20_001B227C * 0.00027777778f;
            if (s->verticalSpeed > 0.0f) {
                self->rotation[0] = func_00283B98(s->spinX, self->rotation[0]);
                self->rotation[1] = func_00283B98(s->spinY, self->rotation[1]);
            } else {
                self->rotation[0] = func_00283B98(-s->spinX, self->rotation[0]);
                self->rotation[1] = func_00283B98(-s->spinY, self->rotation[1]);
            }
        } else {
            func_002A7750(self, 2, -1);
        }
        break;
    case 3:
        count = 0;
        for (p = func_L18_003F75E8(s->group, &count); p != 0; p = func_L18_003F75E8(s->group, &count)) {
            func_00282F20(velocity, D_L20_001B22A0, D_L20_001B2270 * 0.016666668f);
            func_00283098(velocity, velocity, self->matrix);
            func_002ACB48(velocity, D_L20_001B226C * 0.016666668f);
            func_00283098(position, D_L20_001B2290, self->matrix);
            func_00282CC0(position, position, self->position);
            func_00282F20(offset, velocity, 0.3f);
            func_00282CD8(tip, position, offset);
            func_L18_003F76F0(p, position, velocity);
            *(PlatformObject **)(p + 0xB8) = self;
            s->spawnTimer = func_002A7820(D_L20_001B2280, D_L20_001B2284);
        }
        func_0032C700(self->position, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        func_002B0A68(self, 0x1FF, D_L20_001A8F20, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        func_002E5CF8(1, 0, self);
        func_002A6C58(self, 0, 3);
        func_0029F338(self);
        return;
    }
    if (self->frames <= 0xFFFE) {
        self->frames++;
    }
}
