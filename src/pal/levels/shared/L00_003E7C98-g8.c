#include "include_asm.h"

#include "common.h"
typedef float UpdateVector[4] __attribute__((aligned(16)));
typedef struct { char pad[0x54]; float rate; char rest[0x88]; } UpdateTuning;
typedef struct {
    char pad000[0x760];
    float direction[4];
    char pad770[0xBF8-0x770];
    int saved;
    char padBFC[0x1230-0xBFC];
    int input;
    char pad1234[0x1244-0x1234];
    int state;
    char pad1248[0x1450-0x1248];
    int controller;
    char pad1454[0x1500-0x1454];
    int scope;
    char pad1504[0x2290-0x1504];
    void *camera;
    int mode;
    char pad2298[0x22B8-0x2298];
    u8 active;
    char pad22B9[3];
    u8 blocked;
    char pad22BD[0x24EC-0x22BD];
    short alternate;
    char pad24EE[0x2534-0x24EE];
    int delay;
} HeroUpdate;
extern HeroUpdate D_00189E20;
extern float D_L00_001B05C4 __attribute__((sda));
extern float D_L00_001B05C8 __attribute__((sda));
extern float D_L00_001B05CC __attribute__((sda));
extern float D_L00_001B05D0 __attribute__((sda));
extern float D_L00_001B15CC MACRO_ADDR;
extern float D_L00_001B15D0 MACRO_ADDR;
extern float D_L00_001B15D4 MACRO_ADDR;
extern float D_L00_001B15D8 MACRO_ADDR;
extern int D_L00_001AA0F8 MACRO_ADDR;
extern int D_L00_001B19C8;
typedef struct { UpdateVector position; char pad[0x220]; UpdateVector forward; } ScopeCamera;
extern ScopeCamera D_L00_001B8DC0;
extern u8 *D_L00_001BF218 NOT_SDA;
extern float D_L00_001BD370 NOT_SDA;
extern int D_00138320 NOT_SDA;
extern int D_00138180[];
extern unsigned char D_0013957F NOT_SDA;
extern UpdateTuning D_L00_00262570[];
typedef struct { float red, green, blue, unused; UpdateVector position; } ScopeLight;
extern ScopeLight D_L00_001C6F40[];
extern char D_L00_00296AA0[];
extern void func_002A75E0(char *, int, int, int, int);
extern void func_0026FF08(int, int, float, float, float, float);
extern void func_00291450(int);
extern void func_L00_00368F58(int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern float *func_002AB1F0(char *);
extern int func_002ABB78(char *);
extern int func_L00_002D4040(int);
extern void func_00273318(char *, unsigned int, int, int, int, int, float, float, float);
extern float func_00283248(float, float);
extern int func_L00_00329E90(char *, int, int *);
extern char *func_L00_0032A088(int, int);
extern int *func_L00_0032A0B8(int, int);
extern char *func_L00_00329FF0(char *);
extern void func_00282A88(void *, int);
extern void ref_L00_003E3A18_00(int);
extern void func_PAL_L00_002C4480(int, int);
extern int func_00282948(int *);
extern int func_L00_002D3F30(int, int);
extern void func_PAL_L00_002AF458(void);
extern int func_L00_002D6998(void *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_002E5CF8(int, int, char *);
extern void func_L00_002D6B70(int);
extern int func_00282978(short *);
extern void func_PAL_L00_003E8788(char *);
extern int func_002829D8(float *);
extern int func_00291308(float, void *, unsigned int, float);
extern void func_0029FCC0(char *, int, void *);
extern float func_00283CE0(int);
typedef struct {
    short scoped;
    short firingDelay;
    float cooldown, initialFov, zoomFov;
    int light, flashTimer, resource, sound;
    char *resourceBase;
    int unused;
    short targeting, targetFrames;
    u8 *target;
} ScopedWeaponState;

/* Update targeting, zoom, fire/recharge states and the muzzle light.
 * Debug labels reproduce retail division padding; keep the tuning lookup and
 * the reciprocal on separate lines.
 */
void func_PAL_L00_003E7C98(u8 *object)
{
    UpdateVector position, first, second;
    int loaded;
    ScopedWeaponState *data = *(ScopedWeaponState **)(object + 0x68);
    u8 *target;
    float *health;
    char *base, *cursor;
    int *offsets;
    UpdateTuning *tuning;
    char **slot;
    int remaining, canFire;
    unsigned int color;
    float angle, fraction, intensity;
    float horizontal, vertical, blend;

    if ((u8)object[0x42] == (u8)object[0x43] && ((u8)object[0x60] & 2))
        func_002A75E0(object, 1, 0, 2, 0);
    if (D_00189E20.state == 3) {
        if ((u8)object[0x20] == 0) return;
        D_L00_001B15D0 = D_L00_001B05C4;
        D_L00_001B15D4 = D_L00_001B05C8;
        D_L00_001B15D8 = D_L00_001B05CC;
        D_L00_001B15CC = D_L00_001B05D0;
        func_0026FF08(0, 3, 1.1243411302566528f, 0.005f, 0.2f, 0.0f);
        if (data->light >= 0) func_00291450(data->light);
        data->light = -1;
        D_L00_001AA0F8 = 224;
        func_L00_00368F58(1);
        return;
    }
    if (D_00189E20.mode == 111) {
        if ((u8)object[0x20] == 4) return;
        object[0x20] = 4;
        if (data->light >= 0) func_00291450(data->light);
        data->light = -1;
        D_L00_001B15D0 = D_L00_001B05C4;
        D_L00_001B15D4 = D_L00_001B05C8;
        D_L00_001B15D8 = D_L00_001B05CC;
        D_L00_001B15CC = D_L00_001B05D0;
        func_0026FF08(0, 3, 1.1243411302566528f, 0.005f, 0.2f, 0.0f);
        func_L00_00368F58(1);
        return;
    }
    if ((u8)object[0x20] == 4) object[0x20] = 1;
    qcopy(position, object + 0x10);
    if (D_00189E20.scope) {
        if (D_L00_001B19C8 & 4) {
            data->target = 0;
            data->targeting = 0;
            func_00282F20(first, D_L00_001B8DC0.forward, 128.0f);
            func_00282CC0(first, first, D_L00_001B8DC0.position);
            if (func_002761F8(D_L00_001B8DC0.position, first, 16, D_00189E20.camera, 0)) {
                target = D_L00_001BF218;
                if (target && (u8)target[0x31]) {
                    health = func_002AB1F0(target);
                    if (func_002ABB78(target) || (health && *health > 0.0f &&
                        *(char **)(target + 0x24) && *(short *)(*(char **)(target + 0x24) + 0x46) == 5)) {
                        data->target = target;
                        data->targeting = 1;
                    }
                }
            }
        }
        if (D_00189E20.delay == 0) {
            if (data->targeting) {
                if (++data->targetFrames > 17) data->targetFrames = 0;
                if (data->cooldown <= 0.0f && func_L00_002D4040(-1) && data->targetFrames >= 9)
                    func_00273318(object, 0x400000FF, 0, 32, -1, 4, 1.5f, 0.0f, 90.0f);
            }
            if (data->cooldown > 0.0f && func_L00_002D4040(-1)) color = 0x600000FF;
            else color = 0x600FFF0F;
            func_00273318(object, color, 0, 39, -1, 4, 2.0f, 0.0f, 90.0f);
        }
    }
    switch ((u8)object[0x20]) {
    case 0:
        data->scoped = 0;
        data->cooldown = 0.36666667461395264f;
        object[0x20] = 3;
        angle = func_00283248(1.0f, D_L00_001BD370);
        angle += angle;
        data->initialFov = angle;
        data->zoomFov = angle + (0.174532949924469f - angle) * 0.25f;
        D_L00_001B05C4 = D_L00_001B15D0;
        D_L00_001B05C8 = D_L00_001B15D4;
        D_L00_001B05CC = D_L00_001B15D8;
        D_L00_001B05D0 = D_L00_001B15CC;
        data->flashTimer = 0;
        data->targeting = 0;
        data->targetFrames = 0;
        data->target = 0;
        data->light = -1;
        data->resource = func_L00_00329E90(object, 0, &loaded);
        if (!loaded) {
            cursor = func_L00_0032A088(*(short *)(object + 0xAA), data->resource);
            data->resourceBase = cursor;
            base = cursor;
            offsets = func_L00_0032A0B8(*(short *)(object + 0xAA), data->resource);
            cursor = func_L00_00329FF0(base + 12);
            slot = (char **)base;
            for (remaining = 2; remaining >= 0; remaining--) {
                *slot = cursor;
                cursor += 0xF00;
                slot++;
            }
            cursor = func_L00_00329FF0(cursor);
            offsets[0] = cursor - base;
            func_00282A88(cursor, 0x120);
            cursor = func_L00_00329FF0(cursor + 0x120);
            offsets[1] = cursor - base;
            func_00282A88(cursor, 0x1E00);
        }
        if (data->resource >= 0) ref_L00_003E3A18_00(data->resource);
        break;
    case 1:
        if (D_00189E20.mode == 1) func_PAL_L00_002C4480(29, 1);
        if (D_00189E20.scope) {
            if (data->scoped == 0) D_L00_001AA0F8 = 0;
            data->scoped = 1;
        }
        if (D_00189E20.controller) D_00189E20.saved = D_00189E20.controller;
        if (D_00189E20.scope) {
            if (D_00138320 & 8) data->zoomFov -= 0.01f;
            else if (D_00138320 & 2) data->zoomFov += 0.01f;
            if (data->zoomFov > data->initialFov) data->zoomFov = data->initialFov;
            else if (data->zoomFov < 0.174532949924469f) data->zoomFov = 0.174532949924469f;
            func_0026FF08(0, 3, data->zoomFov, 0.02f, 0.2f, 0.0f);
            func_L00_00368F58(0);
        } else if (data->scoped) {
            data->zoomFov = data->initialFov + (0.174532949924469f - data->initialFov) * 0.25f;
            func_0026FF08(0, 3, data->initialFov, 0.005f, 0.2f, 0.0f);
            data->scoped = 0;
            D_L00_001AA0F8 = 224;
            func_L00_00368F58(1);
        }
        fraction = (data->zoomFov - 0.174532949924469f) / (data->initialFov - 0.174532949924469f);
        horizontal = (D_L00_001B05C4 - 0.03f) * fraction + 0.03f;
        vertical = (D_L00_001B05C8 - 0.4f) * fraction + 0.4f;
        blend = (D_L00_001B05D0 - 0.010471977293491364f) * fraction + 0.010471977293491364f;
        D_L00_001B15D0 = horizontal;
        D_L00_001B15CC = blend;
        D_L00_001B15D4 = vertical;
        canFire = 1;
        if (D_00189E20.scope) {
            if (!func_00282948(&D_00189E20.delay)) canFire = 0;
        } else D_00189E20.delay = 33;
        if (D_00189E20.blocked == 0 && (D_00138180[0x1A4/4] & D_00189E20.input) && canFire) {
            if (func_L00_002D3F30(-1, 1)) {
                func_PAL_L00_002AF458();
                data->sound = func_L00_002D6998(D_L00_00296AA0);
                data->firingDelay = 2;
                object[0x20] = 2;
                func_PAL_002A7E68(object, 2, 0, 0);
            } else func_002E5CF8(1, 0, object);
            if ((D_00138180[0x1A0/4] & D_00189E20.input) && func_L00_002D4040(-1) && D_00189E20.active) break;
            if (data->sound >= 0) {
                func_L00_002D6B70(data->sound);
                data->sound = -1;
            }
        }
        break;
    case 2:
        if (D_00189E20.controller) D_00189E20.saved = D_00189E20.controller;
        if (func_00282978(&data->firingDelay) || data->scoped) {
            func_002E5CF8(0, 0, object);
            func_PAL_L00_003E8788(object);
            tuning = (UpdateTuning *)(D_0013957F * 224 + (char *)D_L00_00262570);
        data->cooldown = 1.0f / tuning->rate;
            object[0x20] = 3;
        }
        break;
    case 3:
        if (func_002829D8(&data->cooldown)) object[0x20] = 1;
        break;
    }
    if (data->flashTimer) {
        if (func_00282948(&data->flashTimer)) {
            if (data->light >= 0) func_00291450(data->light);
            data->light = -1;
        } else {
            if (data->light == -1)
                data->light = func_00291308(10.0f, object + 0x10, 0xFF0000FF, 0.0f);
            if (data->light >= 0) {
                if (D_00189E20.alternate == 1) {
                    func_0029FCC0(object, 0, first);
                    func_00282F20(second, object + 0xD0, -1.5f);
                } else {
                    func_0029FCC0(object, 0, first);
                    func_00282F20(second, D_00189E20.direction, 1.5f);
                }
                func_00282CC0(D_L00_001C6F40[data->light].position, first, second);
                D_L00_001C6F40[data->light].position[3] = 10.0f;
                intensity = func_00283CE0(data->flashTimer);
                intensity /= func_00283CE0(25);
                D_L00_001C6F40[data->light].red = intensity;
                intensity *= 0.7f;
                D_L00_001C6F40[data->light].green = intensity;
                D_L00_001C6F40[data->light].blue = 0;
            }
        }
    }
}
