#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad00[0x10];
    float position[4];
    char pad20[0x48];
    char *state;
    char pad6c[0x3E];
    unsigned short type;
    char padac[0x14];
    float forward[4];
    char padd0[0x10];
    float up[4];
    char padf0[0x10];
} Moby;
typedef struct {
    char pad[0x18];
    char *object;
    int flags;
    float hit[4];
    float position[4];
    float normal[4];
} Collision;
typedef struct {
    float normal[3];
    float value;
    void *object;
    int flags;
    unsigned char a, b;
    unsigned short type;
    float amount;
    int enabled;
    float extra;
} ImpactRequest;
extern char *D_L05_001B1EC4;
extern Moby *D_L05_001B251C;
extern int D_001A79F0 MACRO_ADDR;
extern Collision D_L05_001BFB00;
extern char D_L05_002B8770[];
extern int D_L05_001B2048;
extern float D_L05_001B1C10 __attribute__((sda));
extern float D_L05_001B1C14 __attribute__((sda));
extern float D_L05_001B1C18 __attribute__((sda));
extern float D_L05_001B1C1C __attribute__((sda));
extern float D_L05_001B1C20 __attribute__((sda));
extern int D_L05_001B1AE4 __attribute__((sda));
extern int func_00282948(void *);
extern int func_00277258(void *, int, void *, float);
extern void func_PAL_L05_0037D3D0(float);
extern void func_PAL_L05_004485A0(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_00282DF0(void *);
extern float func_00283CE0(int);
extern float func_00282DB0(void *, void *);
extern float func_00282C48(float);
extern float func_00282E48(void *, void *);
extern int func_00283CF0(float);
extern int func_00278E78(void);
extern int func_L00_0031BE88(void *);
extern int func_L05_00445980(void);
extern int func_L00_002D6998(void *);
extern void func_002833F0(void *, void *);
extern void func_002A8E20(void *, void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L05_00445C38(void *);

/* Sweeps the linked moby's movement in short steps, resolving contacts and
 * producing impact damage, recoil and a deferred collision trail. */
void func_PAL_L05_0044B738(char *obj, void *target)
{
    float delta[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float hit[4] __attribute__((aligned(16)));
    float move[4] __attribute__((aligned(16)));
    /* The facing matrix and the later impact request share the retail scratch. */
    union {
        ImpactRequest message;
        float rotation[3][4];
    } event;
    char *record = *(char **)(D_L05_001B1EC4 + *(short *)(obj + 0x84) * 32 + 0x1C);
    Moby *moby = &D_L05_001B251C[*(int *)(record + 0x20)];
    float distance, divisor;
    int count, i;

    func_00282948(record + 0x58);
    if (D_001A79F0 == 10 && func_00277258(moby->position, 16, moby, 0.5f) &&
        D_L05_001BFB00.object &&
        *(short *)(D_L05_001BFB00.object + 0xAA) == 0xF86) {
        func_PAL_L05_0037D3D0(1000);
        func_PAL_L05_004485A0(obj);
        return;
    }
    func_00282CF0(delta, moby->position, target);
    distance = func_00282DF0(delta);
    if (distance <= D_L05_001B1C1C) {
        count = 2;
        divisor = 2;
    } else {
        if (distance > 30)
            return;
        count = func_00283CF0(distance / D_L05_001B1C1C) + 2;
        divisor = func_00283CE0(count);
    }
    func_00282D30(step, delta, 1.0f / divisor);
    func_00282D30(offset, moby->up, D_L05_001B1C20);
    func_00282CC0(pos, target, offset);
    for (i = 0; i < count; i++) {
        float *direction;

        func_00282CC0(pos, pos, step);
        if (!func_00277258(pos, 16, moby, D_L05_001B1C1C) || func_00278E78() == 6)
            continue;

        if (D_L05_001BFB00.object && !func_L00_0031BE88(D_L05_001BFB00.object)) {
            if (D_L05_001BFB00.object) {
                char *link = *(char **)(D_L05_001BFB00.object + 0x24);

                if (link && *(short *)(link + 0x46) == 11) {
                    func_00282CF0(dir, moby->position, D_L05_001BFB00.object + 0x10);
                    func_00282F20(dir, dir, 1);
                    qcopy(hit, D_L05_001BFB00.object + 0x10);
                    direction = dir;
                    goto impact;
                }
            }
            if (D_L05_001BFB00.object && D_001A79F0 == 10 &&
                *(short *)(D_L05_001BFB00.object + 0xAA) == 0x1315)
                return;
            {
                int kind = *(short *)(D_L05_001BFB00.object + 0xAA);

                if (kind == 0x1327)
                    return;
                if (kind == 0x1328)
                    return;
            }
            func_00282CF0(move, D_L05_001BFB00.position, pos);
            func_00282CC0(moby->position, moby->position, move);
            func_00282CC0(obj + 0x30, obj + 0x30, move);
            qcopy(pos, D_L05_001BFB00.position);
            {
                float facing;

                if (*(unsigned short *)(D_L05_001BFB00.object + 0x34) & 0x100) {
                    facing = func_00282DB0(D_L05_001BFB00.object + 0xC0, moby->forward);
                } else {
                    func_002833F0(event.rotation, D_L05_001BFB00.object + 0xF0);
                    facing = func_00282DB0(event.rotation, moby->forward);
                }
                if (facing > 0)
                    continue;
            }
            if (!*(int *)(record + 0x58)) {
                event.message.flags = 0x10000;
                event.message.amount = D_L05_001B1C14;
                event.message.enabled = 1;
                event.message.object = moby;
                func_00282CF0(&event.message, D_L05_001BFB00.object + 0x10, moby->position);
                func_00282F20(&event.message, &event.message, 1);
                event.message.value = 5627.925f;
                event.message.a = 1;
                event.message.b = 1;
                event.message.type = moby->type;
                func_002A8E20(D_L05_001BFB00.object, &event.message);
                func_PAL_L05_0037D3D0(D_L05_001B1C18);
                *(int *)(record + 0x58) = ((s32)(D_L05_001B1AE4) * 5 + 2) / 6;
            }
            func_L00_002D6998(D_L05_002B8770);
            qcopy(moby->state + 0x90, D_L05_001BFB00.hit);
            func_L00_002E6EF8(func_L05_00445C38, moby);
            continue;
        }
        func_00282D30(dir, D_L05_001BFB00.normal, 0.0009765625f);
        func_00282F20(dir, dir, 1);
        qcopy(hit, D_L05_001BFB00.hit);
        direction = dir;
impact:
        if (func_00282C48(func_00282DB0(direction, moby->forward)) > 0.75f) {
            func_PAL_L05_004485A0(obj);
            continue;
        }
        func_00282D30(D_L05_001BFB00.position, direction, D_L05_001B1C1C);
        func_00282CC0(D_L05_001BFB00.position, D_L05_001BFB00.hit, D_L05_001BFB00.position);
        func_00282CF0(move, D_L05_001BFB00.position, pos);
        func_00282CC0(moby->position, moby->position, move);
        func_00282CC0(obj + 0x30, obj + 0x30, move);
        qcopy(pos, D_L05_001BFB00.position);
        func_L00_002D6998(D_L05_002B8770);
        if (!(D_L05_001B2048 & 3)) {
            float value = D_L05_001B1C10;

            if (func_L05_00445980())
                value += value;
            func_PAL_L05_0037D3D0(value);
        }
        {
            char *state = moby->state;

            func_00282D30(move, direction, D_L05_001B1C1C * 0.8f);
            func_00282CC0(state + 0x90, move, D_L05_001BFB00.hit);
        }
        func_L00_002E6EF8(func_L05_00445C38, moby);
        if (func_00282E48(target, moby->position) < 0.1f)
            func_PAL_L05_004485A0(obj);
    }
}
