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

extern SpawnObject *CreateMoby(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void math_compute_aim_direction(void *, void *, float, float, float);
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float), math_random_angle(void);
extern void cam_compute_view_direction(void *, void *, int);
extern TargetState *moby_get_private_value_0(void *);
extern int FloatToInt(float);
extern int CollLine(void *, void *, int, void *, int);
extern void moby_transform_offset_to_world(void *, void *);
extern void func_002A0F48(void *), AddMobyToIndexList(void *, void *, int);
extern int part_alloc_effect_slot(void *, int, float, float, float);

extern Material g_weapon_l00_table[];
extern int D_L00_001AF7A0 __attribute__((sda));
extern unsigned char D_00139583 NOT_SDA;
extern int D_L00_001A8FF0[] __attribute__((sda));
extern char D_L00_001BF220[], D_L00_0023B710[], D_L00_001B1FB0[] __attribute__((sda));
extern HeroState g_hero_state;

SpawnObject *projectile_spawn_targeted(SpawnObject *owner, char *pos, SpawnObject *target, char *arg,
                               float scale, float lo, float hi, float unused)
{
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    float tmp[4] __attribute__((aligned(16)));
    SpawnObject *obj = CreateMoby(0x5da);
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

        speed = ((Material *)(D_00139583 * 0xE0 + (char *)g_weapon_l00_table))->speed * (1.0f / 60.0f);
        qcopy(obj->position, pos);

        if (target) {
            FastVecScale(w, target->up, scale);
            FastVecAdd(v, target->position, w);
        } else {
            /* A plain quadword store, not qzero: reload loads its zero into a register,
             * which moves on the reload registers below, and $zero replaces it after reload. */
            *(Quad *)v = 0;
        }

        if (g_hero_state.mode == 1) {
            vec_scale_to_length(obj->forward, owner->right, -1.0f);
            FastVecScale(obj->right, owner->forward, -1.0f);
            qcopy(obj->up, owner->up);
            basis = obj->forward;
        } else if (target) {
            float *direction = obj->forward;
            FastVecSub(direction, v, obj->position);
            vec_scale_to_length(direction, direction, 1.0f);
            FastVecCross(obj->right, direction, g_hero_state.target->up);
            vec_scale_to_length(obj->right, obj->right, 1.0f);
            FastVecCross(obj->up, obj->right, direction);
            basis = direction;
        } else {
            qcopy(obj->forward, g_hero_state.forward);
            basis = obj->forward;
            if (g_hero_state.aiming)
                math_compute_aim_direction(basis, pos, 1.0f, 75.0f, 0.52359885f);
            FastVecCross(obj->right, basis, g_hero_state.up);
            vec_scale_to_length(obj->right, obj->right, 1.0f);
            FastVecCross(obj->up, obj->right, basis);
        }

        obj->forward[3] = obj->right[3] = obj->up[3] = 0.0f;
        data->owner = owner;
        data->spread = math_random_float_range(lo, hi);
        if (target)
            data->spread = 0;
        data->turn = math_random_signed_float_range(6.0f, 10.0f);
        data->speed = speed;
        data->phase = math_random_angle();
        data->enabled = on;
        data->target = target;
        data->active = on;
        qcopy(data->basis, basis);
        qcopy(data->argument, arg);

        if (D_L00_001A8FF0[0]) {
            float projection;
            cam_compute_view_direction(obj->position, w, 1);
            projection = FastVecDot(w, data->basis);
            FastVecScale(tmp, w, projection);
            FastVecSub(data->basis, data->basis, tmp);
        }

        if (target) {
            TargetState *state = moby_get_private_value_0(target);
            if (state) {
                state->flags |= 0x80;
                if (state->kind)
                    data->enabled = 0;
            }
        }

        data->life = FloatToInt(75.0f / speed);

        if (target) {
            FastVecScale(w, target->up, scale);
            FastVecAdd(w, target->position, w);
            data->position[0] = w[0];
            data->position[1] = w[1];
            data->position[2] = w[2];
            data->scale = scale;
        }

        *(Quad *)w = *(Quad *)(owner->position);
        w[2] = ((float *)pos)[2];

        if (CollLine(w, pos, 0, g_hero_state.target, 0)) {
            obj->blocked = on;
            qcopy(obj->position, D_L00_001BF220);
        }

        moby_transform_offset_to_world(obj, D_L00_0023B710 + (data->material << 6));
        func_002A0F48(obj);
        AddMobyToIndexList(obj, D_L00_001B1FB0, 31);
        obj->radius *= 2.5f;
        data->sound = part_alloc_effect_slot(obj, 0, 1.0f, 1.0f, 1.0f);
    }
    return obj;
}
