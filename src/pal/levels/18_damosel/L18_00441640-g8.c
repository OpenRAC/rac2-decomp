#include "common.h"

extern void *func_002A9640(void *, int, int);
extern float func_PAL_002AA108(void *, void *);
extern void func_PAL_002AC290(void *, void *), func_PAL_002AC3C0(void *, void *);
extern void func_002A7750(void *, int, int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float), func_00283B98(float, float);
extern int func_002ACBC8(void *, int), func_002B3868(void *);
extern void func_0029F338(void *), func_00282948(void *);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern void func_00282F20(void *, void *, float), func_00283098(void *, void *, void *), func_002ACB48(void *, float), func_00282CC0(void *, void *, void *);
extern u8 D_00189EA0[];
extern u8 D_L18_001A8F20[] __attribute__((sda));
extern float D_L18_001B1AB0 __attribute__((sda));
extern float D_L18_001B1AB4 __attribute__((sda));
extern float D_L18_001B1AB8 __attribute__((sda));
extern float D_L18_001B1ABC __attribute__((sda));
extern float D_L18_001B1AC0 __attribute__((sda));
extern float D_L18_001B1AC4 __attribute__((sda));
extern float D_L18_001B1ACC __attribute__((sda));
extern int D_L18_001B1AD0 __attribute__((sda));
extern int D_L18_001B1AD4 __attribute__((sda));
extern u8 D_L18_001B1AE0[] SDATA(D_L18_001B1AE0);
extern u8 D_L18_001B1AF0[] SDATA(D_L18_001B1AF0);
extern u8 *func_L18_003F75E8(int, int *);
extern void func_L18_003F76F0(void *, void *, void *);

typedef struct {
    u8 pad00[0x20];
    float health;
    s16 initialized;
    u8 pad26[0xa];
    float scale;
    u8 pad34[0x1c];
    float transform[4];
    float turnX, turnY;
    u8 pad68[8];
    s32 startRegion, fireRegion, childId;
    float baseZ, velocityZ;
    s32 fireTimer;
} LauncherState;

typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 mode;
    u8 pad21[0x47];
    LauncherState *state;
    u8 pad6c[0x2a];
    u16 timer;
    u8 pad98[0x10];
    u8 opacity;
    u8 pada9[0x17];
    float matrix[12];
    float rotation[4];
} LauncherObject;

/* func_PAL_L18_00441640, the PAL copy of func_L18_0043C258: the same C, where the per-frame rates scale to
 * 50 Hz and the fire delay goes through ((s32)(x) * 5 + 2) / 6. */
void func_PAL_L18_00441640(LauncherObject *obj) {
    LauncherState *s = obj->state;
    u8 *child;
    float damage, z;
    float v[4] __attribute__((aligned(16)));
    float p[4] __attribute__((aligned(16)));
    int zero;
    int low;

    damage = func_PAL_002AA108(obj, func_002A9640(obj, 0x10000, 0));
    s->health -= damage;
    if (damage > 0.0f) {
        func_PAL_002AC290(obj, s->transform);
        if (s->health <= 0.0f) {
            func_PAL_L00_003FB330(obj->position, 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
            func_PAL_002B15D8(obj, 0x3a, D_L18_001A8F20, 3, 6, 3, 6, 255);
            func_002E5CF8(1, 0, obj);
            func_0029F338(obj);
            return;
        }
    }
    obj->opacity = 255;
    func_PAL_002AC3C0(obj, s->transform);
    switch (obj->mode) {
    case 0:
        s->baseZ = obj->position[2];
        if (!s->initialized) {
            s->initialized = 1;
            s->health = 1;
        }
        s->fireTimer = -1;
        s->scale = 1;
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        if (s->startRegion != -1 && func_002ACBC8(D_00189EA0, s->startRegion))
            func_002A7750(obj, 2, -1);
        break;
    case 2:
        if (func_002B3868(obj)) {
            obj->rotation[0] = 0;
            obj->rotation[1] = 0;
            z = obj->rotation[0];
            obj->position[2] = s->baseZ;
            s->velocityZ += func_002A7878(z, D_L18_001B1AB0 * 0.020000001f);
            s->turnX = func_002A7878(z, D_L18_001B1AB4 * 0.0003490659f);
            s->turnY = func_002A7878(z, D_L18_001B1AB8 * 0.0003490659f);
            obj->position[2] = s->baseZ;
            func_002E5CF8(0, 0, obj);
        }
        if (obj->position[2] >= s->baseZ) {
            obj->position[2] += s->velocityZ;
            s->velocityZ -= D_L18_001B1ACC * 0.00040000002f;
            if (s->velocityZ > 0) {
                obj->rotation[0] = func_00283B98(s->turnX, obj->rotation[0]);
                obj->rotation[1] = func_00283B98(s->turnY, obj->rotation[1]);
            } else {
                obj->rotation[0] = func_00283B98(-s->turnX, obj->rotation[0]);
                obj->rotation[1] = func_00283B98(-s->turnY, obj->rotation[1]);
            }
        } else {
            func_002A7750(obj, 2, -1);
        }
        if (s->fireTimer == 0) {
            zero = 0;
            child = func_L18_003F75E8(s->childId, &zero);
            if (child) {
                func_00282F20(v, D_L18_001B1AF0, D_L18_001B1AC0 * 0.020000001f);
                func_00283098(v, v, obj->matrix);
                func_002ACB48(v, D_L18_001B1ABC * 0.020000001f);
                func_00283098(p, D_L18_001B1AE0, obj->matrix);
                func_00282CC0(p, p, obj->position);
                func_L18_003F76F0(child, p, v);
                low = D_L18_001B1AD0;
                *(s32 *)(child + 0xB8) = (s32)obj;
                s->fireTimer = ((s32)func_002A7820(low, D_L18_001B1AD4) * 5 + 2) / 6;
            }
        } else if (s->fireTimer == -1) {
            if (s->fireRegion != -1 && func_002ACBC8(D_00189EA0, s->fireRegion)) {
                s->fireTimer++;
                func_PAL_L00_003FB330(obj->position, 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
                func_002E5CF8(1, 0, obj);
                func_00282F20(v, D_L18_001B1AF0, D_L18_001B1AC4 * 0.020000001f);
                func_00283098(v, v, obj->matrix);
                func_002ACB48(p, D_L18_001B1ABC * 0.020000001f);
                func_00282CC0(v, v, p);
                func_PAL_002B15D8(obj, 5, v, 3, 6, 3, 6, 255);
            }
        } else {
            func_00282948(&s->fireTimer);
        }
        break;
    }
    if (obj->timer < 65535)
        (obj->timer)++;
}
