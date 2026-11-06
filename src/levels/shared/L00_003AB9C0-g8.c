#include "common.h"

/* Spawns moby 0x5DA as a projectile fired by owner, aimed at target when there is one. */

typedef struct SpawnObject SpawnObject;

typedef struct {
    float position[3];
    SpawnObject *owner, *target;
    float scale, speed, spread, turn;
    unsigned short life;
    unsigned char enabled, active;
    float phase;
    int material;
    float basis[4], argument[4];
    int sound;
} SpawnData;

struct SpawnObject {
    char pad0[0x10];
    float position[4];
    unsigned char state;
    char pad21[0xB];
    float radius;
    unsigned char alpha, mode;
    unsigned short group, flags;
    char pad36[0x32];
    SpawnData *data;
    char pad6c[0x50];
    unsigned char blocked;
    char padbd[3];
    float forward[4], right[4], up[4];
};

typedef struct {
    unsigned char pad[0xB], kind;
    unsigned char gap[0x12];
    unsigned short flags;
} TargetState;

typedef struct {
    char pad[0x50];
    float speed;
    char tail[0x8C];
} Material;

typedef struct {
    char pad0[0x750];
    float up[4], forward[4];
    char pad770[0xD90];
    int aiming;
    char pad1504[0xD8C];
    SpawnObject *target;
    char pad2294[0x258];
    short mode;
} HeroState;

typedef int Quad __attribute__((mode(TI)));

extern SpawnObject *func_0029EFD0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_L00_0037FA90(void *, void *, float, float, float);
extern float func_002A7878(float, float), func_002A78D8(float, float), func_002A7940(void);
extern void func_002AFFD8(void *, void *, int);
extern TargetState *func_002AB1F0(void *);
extern int func_00283CF0(float);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_L00_003ACC88(void *, void *);
extern void func_002A0F48(void *), func_002ACA50(void *, void *, int);
extern int func_002FED90(void *, int, float, float, float);

extern Material D_L00_00262570[];
extern int D_L00_001AF7A0 __attribute__((sda));
extern unsigned char D_00139583 NOT_SDA;
extern int D_L00_001A8FF0[] __attribute__((sda));
extern char D_L00_001BF220[], D_L00_0023B710[], D_L00_001B1FB0[] __attribute__((sda));
extern HeroState D_00189E20;

SpawnObject *func_L00_003AB9C0(SpawnObject *owner, char *pos, SpawnObject *target, char *arg,
                               float scale, float lo, float hi, float unused)
{
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    float tmp[4] __attribute__((aligned(16)));
    SpawnObject *obj = func_0029EFD0(0x5da);
    SpawnData *data;
    float *basis;
    float speed;
    unsigned char on = 1;

    if (obj) {
        obj->alpha = 255;
        obj->mode = on;
        obj->state = 0;
        obj->group = 255;
        obj->flags |= 0x100;
        data = obj->data;

        if ((unsigned)D_L00_001AF7A0 >= 9)
            D_L00_001AF7A0 = 0;
        {
            int index = D_L00_001AF7A0;
            data->material = index;
            D_L00_001AF7A0 = (index + 1) % 8;
        }

        speed = ((Material *)(D_00139583 * 0xE0 + (char *)D_L00_00262570))->speed * (1.0f / 60.0f);
        qcopy(obj->position, pos);

        if (target) {
            func_00282D30(w, target->up, scale);
            func_00282CC0(v, target->position, w);
        } else {
            /* A plain quadword store, not qzero: reload loads its zero into a register,
             * which moves on the reload registers below, and $zero replaces it after reload. */
            *(Quad *)v = 0;
        }

        if (D_00189E20.mode == 1) {
            func_00282F20(obj->forward, owner->right, -1.0f);
            func_00282D30(obj->right, owner->forward, -1.0f);
            qcopy(obj->up, owner->up);
            basis = obj->forward;
        } else if (target) {
            float *direction = obj->forward;
            func_00282CF0(direction, v, obj->position);
            func_00282F20(direction, direction, 1.0f);
            func_00282DD8(obj->right, direction, D_00189E20.target->up);
            func_00282F20(obj->right, obj->right, 1.0f);
            func_00282DD8(obj->up, obj->right, direction);
            basis = direction;
        } else {
            qcopy(obj->forward, D_00189E20.forward);
            basis = obj->forward;
            if (D_00189E20.aiming)
                func_L00_0037FA90(basis, pos, 1.0f, 75.0f, 0.52359885f);
            func_00282DD8(obj->right, basis, D_00189E20.up);
            func_00282F20(obj->right, obj->right, 1.0f);
            func_00282DD8(obj->up, obj->right, basis);
        }

        obj->forward[3] = obj->right[3] = obj->up[3] = 0.0f;
        data->owner = owner;
        data->spread = func_002A7878(lo, hi);
        if (target)
            data->spread = 0;
        data->turn = func_002A78D8(6.0f, 10.0f);
        data->speed = speed;
        data->phase = func_002A7940();
        data->enabled = on;
        data->target = target;
        data->active = on;
        qcopy(data->basis, basis);
        qcopy(data->argument, arg);

        if (D_L00_001A8FF0[0]) {
            float projection;
            func_002AFFD8(obj->position, w, 1);
            projection = func_00282DB0(w, data->basis);
            func_00282D30(tmp, w, projection);
            func_00282CF0(data->basis, data->basis, tmp);
        }

        if (target) {
            TargetState *state = func_002AB1F0(target);
            if (state) {
                state->flags |= 0x80;
                if (state->kind)
                    data->enabled = 0;
            }
        }

        data->life = func_00283CF0(75.0f / speed);

        if (target) {
            func_00282D30(w, target->up, scale);
            func_00282CC0(w, target->position, w);
            data->position[0] = w[0];
            data->position[1] = w[1];
            data->position[2] = w[2];
            data->scale = scale;
        }

        *(Quad *)w = *(Quad *)(owner->position);
        w[2] = ((float *)pos)[2];

        if (func_002761F8(w, pos, 0, D_00189E20.target, 0)) {
            obj->blocked = on;
            qcopy(obj->position, D_L00_001BF220);
        }

        func_L00_003ACC88(obj, D_L00_0023B710 + (data->material << 6));
        func_002A0F48(obj);
        func_002ACA50(obj, D_L00_001B1FB0, 31);
        obj->radius *= 2.5f;
        data->sound = func_002FED90(obj, 0, 1.0f, 1.0f, 1.0f);
    }
    return obj;
}
