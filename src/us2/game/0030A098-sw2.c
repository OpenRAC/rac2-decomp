#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; } Hero;
typedef struct { u16 count; u16 pad; u32 maximum; u32 levels; } Statistics;
typedef struct {
    Vector start, end;
    char *target;
    float length;
    short targetAge, secondaryAge;
    int timer, light, fade;
    char *secondary;
    short ammoTimer, cooldown, targetReady, secondaryReady, targetTimer, secondaryTimer;
    int sound;
} DualBeamState;
extern Hero D_00189E20;
extern u32 D_00138180[];
extern u8 D_00188660[];
extern float D_001B323C NOT_SDA;
extern u8 D_0013957A[];
typedef struct { u8 pad[4]; u8 flag; u8 rest[0xDB]; } LevelInfo;
extern LevelInfo D_00239BA0[];
typedef struct { float color[3]; float pad; float pos[3]; float radius; } Light;
extern Light D_001C2B40[];
extern int D_001AEDF0 __attribute__((sda)), D_001B23E0 __attribute__((sda));
extern u32 D_001A7390, D_001A79F0;
extern Statistics D_0018C360[], D_0018C750[];
extern int func_0026F740(int);
extern int func_0026F738(int, int);
extern int func_00282948(int *), func_00282978(short *);
extern void func_00273318(void *, u32, void *, int, int, int, float, float, float);
extern s16 func_00291308(void *, int, float, float);
extern int func_002E5CF8(int, int, char *), func_002E59B0(void *, int);
extern float func_00283248(float, float), func_00283C80(float, float), func_00282E48(void *, void *), func_00283CE0(int);
extern void func_002AFFD8(void *, void *, int), func_00282D30(void *, void *, float), func_00282CC0(void *, void *, void *);
extern char *func_002AB1F0(char *);
extern void func_0029FCC0(void *, int, void *), func_00283098(void *, void *, void *), func_00282F20(void *, void *, float);
extern void func_0030A188(char *), func_0030A348(char *), func_0030BA38(void *);
extern void func_0027CFD0(void (*)(void *), void *), func_002E59F8(int);
extern void func_0026F768(void), func_0026F768(void), func_00291450(int);
extern void func_0026F760(void), func_0026F760(void), func_00291450(int);

/* Maintains two beam targets, their acquisition delays, ammunition and the light/sound state. */
void func_US2_0030A510(char *actor) {
    Vector direction, offset;
    float local[4] __attribute__((aligned(16)));
    DualBeamState *beam;
    char *entry;
    u8 *sound;
    int stopping, active, permitted, ammo, limit;
    float fade;

    stopping = D_00189E20.i[0x1244 / 4] == 3;
    beam = *(DualBeamState **)(actor + 0x68);
    if ((D_00138180[0x1A4 / 4] & D_00189E20.u[0x1230 / 4]) && !D_00189E20.b[0x22BC]) beam->length = 0.8f;
    D_001B323C = 0.9f;
    active = 0;
    permitted = 1;
    ammo = func_0026F740(-1);
    if (D_00189E20.i[0x2294 / 4] == 1) {
        if (!func_00282948(&D_00189E20.i[0x2534 / 4])) permitted = 0;
        else func_00273318(actor, !func_0026F740(-1) ? 0x600000FF : 0x600FFF0F, 0, 31, -1, 4, 1, 0, 90);
    } else D_00189E20.i[0x2534 / 4] = 40;
    if ((D_00138180[0x1A0 / 4] & D_00189E20.u[0x1230 / 4]) && (u8)actor[0x20] != 4 && (u8)actor[0x20] &&
        !D_00189E20.b[0x22BC] && D_00189E20.i[0x2294 / 4] != 0x6F && D_00189E20.i[0x1240 / 4] >= 23 && permitted) {
        if (!beam->timer) {
            if (ammo > 0) {
            if (func_00282978(&beam->ammoTimer)) {
                func_00282978(&beam->targetTimer);
                func_00282978(&beam->secondaryTimer);
                func_0026F738(-1, 1);
                beam->ammoTimer = 10;
            }
            if (beam->light == -1) beam->light = func_00291308(actor + 0x10, 0, 7.5f, 0);
            else if (beam->fade < 10) beam->fade++;
            active = 1;
            if (beam->target) {
                if (func_00283C80(D_00189E20.f[0x98 / 4],
                                  func_00283248(*(float *)(beam->target + 0x10) - D_00189E20.f[0x80 / 4],
                                                *(float *)(beam->target + 0x14) - D_00189E20.f[0x84 / 4])) > 2.0943f ||
                    !((u8 *)beam->target)[0x31] || func_00282E48(beam->target + 0x10, &D_00189E20.f[0x80 / 4]) > 20) {
                    beam->target = 0;
                    beam->targetReady = 0;
                }
            }
            if (beam->secondary) {
                if (func_00283C80(D_00189E20.f[0x98 / 4],
                                  func_00283248(*(float *)(beam->secondary + 0x10) - D_00189E20.f[0x80 / 4],
                                                *(float *)(beam->secondary + 0x14) - D_00189E20.f[0x84 / 4])) > 2.0943f ||
                    !((u8 *)beam->secondary)[0x31] || func_00282E48(beam->secondary + 0x10, &D_00189E20.f[0x80 / 4]) > 20) {
                    beam->secondary = 0;
                    beam->secondaryReady = 0;
                }
            }
            func_002AFFD8(beam, &direction, 1);
            qcopy(&beam->start, actor + 0x10);
            func_00282D30(&offset, &direction, 0.7f);
            func_00282CC0(&beam->start, &beam->start, &offset);
            qcopy(&beam->end, &beam->start);
            if (beam->target && beam->targetReady) {
                limit = 50;
                beam->targetAge++;
                entry = func_002AB1F0(beam->target);
                if (entry && *(short *)(entry + 4) == 1) limit = 5;
                if (beam->targetAge >= limit) {
                    beam->target = 0;
                    beam->targetReady = 0;
                }
            } else beam->targetAge = 0;
            if (beam->secondary && beam->secondaryReady) {
                limit = 50;
                beam->secondaryAge++;
                entry = func_002AB1F0(beam->secondary);
                if (entry && *(short *)(entry + 4) == 1) limit = 5;
                if (beam->secondaryAge >= limit) {
                    beam->secondary = 0;
                    beam->secondaryReady = 0;
                }
            } else beam->secondaryAge = 0;
            beam->length += (((D_00239BA0 + D_0013957A[0])->flag ? 18.0f : 12.0f) - beam->length) * 0.07f;
            if (D_00189E20.h[0x24EC / 2] == 1) {
                func_0029FCC0(actor, 0, &beam->start);
                local[0] = 0;
                local[1] = -beam->length;
                local[2] = 0;
                func_00283098(local, local, actor + 0xC0);
                func_00282CC0(&beam->end, &beam->start, local);
            } else {
                func_0029FCC0(actor, 0, &beam->start);
                func_00282F20(&beam->end, &D_00189E20.f[0x730 / 4], beam->length);
                func_00282CC0(&beam->end, &beam->start, &beam->end);
            }
            func_0030A188(actor);
            func_0030A348(actor);
            func_0027CFD0(func_0030BA38, actor);
            } else {
                beam->target = 0;
                beam->secondary = 0;
                beam->targetReady = 0;
                beam->secondaryReady = 0;
                beam->targetTimer = 0;
                beam->secondaryTimer = 0;
            }
        }
    } else {
        beam->target = 0;
        beam->secondary = 0;
        beam->targetReady = 0;
        beam->secondaryReady = 0;
    }
    if (!active) {
        D_001AEDF0 = 1;
        if (beam->fade > 0) beam->fade--;
        if (beam->sound != -1) {
            sound = D_00188660 + beam->sound * 0x70;
            if (*(char **)(sound + 0x88) == actor && sound[0x74]) func_002E59F8(beam->sound);
        }
        beam->sound = -1;
    } else {
        if (!func_002E59B0(actor, beam->sound)) beam->sound = func_002E5CF8(4, 4, actor);
    }
    if (!beam->target || (u8)beam->target[0x20] == 0xFE || (u8)beam->target[0x20] == 0xFD ||
        !(*(u16 *)(beam->target + 0x34) & 0x1000))
        beam->targetReady = 1;
    if (!beam->secondary || (u8)beam->secondary[0x20] == 0xFE || (u8)beam->secondary[0x20] == 0xFD ||
        !(*(u16 *)(beam->secondary + 0x34) & 0x1000))
        beam->secondaryReady = 1;
    switch ((u8)actor[0x20]) {
    case 0:
        beam->timer = 16;
        beam->light = func_00291308(&beam->start, 0, 0, 0);
        D_001AEDF0 = 1;
        actor[0x20] = 1;
        beam->cooldown = 20;
        beam->sound = -1;
        beam->secondary = 0;
        beam->target = 0;
        beam->targetReady = 0;
        beam->secondaryReady = 0;
        beam->secondaryTimer = 0;
        beam->targetTimer = 0;
        D_001B23E0 = 10;
        break;
    case 1:
        func_00282948(&beam->timer);
        if (active) {
            func_0026F760();
            actor[0x20] = 3;
        }
        if ((D_00138180[0x1A4 / 4] & D_00189E20.u[0x1230 / 4]) && !D_00189E20.b[0x22BC]) {
            if (active) {
                if (D_0018C360[18].count < 0xFFFF) D_0018C360[18].count++;
                if (D_001A7390 > D_0018C360[18].maximum) D_0018C360[18].maximum = D_001A7390;
                D_0018C360[18].levels = (D_0018C360[18].levels | (1u << D_001A79F0)) | 0x80000000u;
                func_0026F760();
                actor[0x20] = 3;
            } else {
                beam->target = 0;
                beam->secondary = 0;
                beam->targetReady = 0;
                beam->secondaryReady = 0;
                actor[0x20] = 1;
                func_002E5CF8(0, 0, actor);
                func_0026F768();
            }
        }
        break;
    case 3:
        if (!(D_00138180[0x1A8 / 4] & D_00189E20.u[0x1230 / 4]) && active && !D_00189E20.b[0x22BC]) break;
        if (D_00189E20.i[0x1D8 / 4] > 70) {
            if (D_0018C750[26].count < 0xFFFF) D_0018C750[26].count++;
        }
        if (D_001A7390 > D_0018C750[26].maximum) D_0018C750[26].maximum = D_001A7390;
        D_0018C750[26].levels = (D_0018C750[26].levels | (1u << D_001A79F0)) | 0x80000000u;
        if (D_00189E20.i[0x1D8 / 4] < 30) D_00189E20.b[0x22C5]++;
        else D_00189E20.b[0x22C5] = 0;
        beam->target = 0;
        beam->secondary = 0;
        beam->targetReady = 0;
        beam->secondaryReady = 0;
        beam->length = 0;
        func_0026F768();
        actor[0x20] = 1;
        break;
    case 2:
    case 4:
    case 5:
        break;
    }
    if (beam->light != -1) {
        qzero_nc(&direction);
        direction.f[0] = 2;
        direction.f[2] = 2;
        func_00283098(&direction, &direction, &D_00189E20.f[0x730 / 4]);
        (D_001C2B40 + beam->light)->pos[0] = D_00189E20.f[0x80 / 4] + direction.f[0];
        (D_001C2B40 + beam->light)->pos[1] = D_00189E20.f[0x84 / 4] + direction.f[1];
        (D_001C2B40 + beam->light)->pos[2] = D_00189E20.f[0x88 / 4] + direction.f[2];
        (D_001C2B40 + beam->light)->radius = 7.5f;
        fade = func_00283CE0(beam->fade) * 0.1f;
        (D_001C2B40 + beam->light)->color[2] = fade;
        (D_001C2B40 + beam->light)->color[1] = fade * 0.7f;
        (D_001C2B40 + beam->light)->color[0] = (D_001C2B40 + beam->light)->color[1];
        if (stopping && beam->light != -1) {
            func_00291450(beam->light);
            beam->light = -1;
        }
    }
    if (stopping && beam->light == -1) actor[0x20] = 4;
}
