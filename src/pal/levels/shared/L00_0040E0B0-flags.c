#include "include_asm.h"

#include "common.h"
extern void func_002AFFD8(char *, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern float D_L00_001B8DC0[4];
typedef struct SoundSlotA4A8 { char pad[0x74]; unsigned char active; char pad75[0x13]; void *object; } SoundSlotA4A8;
typedef struct PlayerLinkA4A8 { char pad[0x2290]; void *object; } PlayerLinkA4A8;
typedef struct CollisionResultA4A8 { char pad[0x18]; void *object; int surface; float position[4]; char pad30[0x10]; float normal[4]; } CollisionResultA4A8;
typedef struct TuningA4A8 { char pad[0x70]; float damage; char tail[0x6c]; } TuningA4A8;
extern char D_00188660[], D_00189EA0[];
extern PlayerLinkA4A8 D_00189E20;
extern unsigned char D_00139568[];
extern TuningA4A8 D_L00_00262570[];
extern char D_L00_00255BA0[];
extern unsigned short D_L00_001B1FB0[] MACRO_ADDR;
extern CollisionResultA4A8 D_L00_001BF200;
extern void *D_L00_001ADB2C MACRO_ADDR;
extern float *func_002AB1F0(void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern float func_00283198(float);
extern float func_00282C48(float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern float func_00283B98(float, float);
extern void func_002FEE70(int, void *, int);
extern void func_002FEE50(int);
extern void func_00300190(void *, void *);
extern void func_002ACAD0(void *, void *);
extern void func_L00_0040B2C0(void *, void *);
extern void func_L00_0040B330(void *);
extern void ref_L00_0040A4A8_00(void (*)(void *), void *);
extern void func_PAL_L00_0040FC40(void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_002A77E0(int);
extern void func_002A89A8(void *, int, float);
extern void *func_PAL_L00_00418F28(void *, float, int, int, int, int, int, int, int, int, int, int, void *);
extern void func_L00_0040AFB8(void *, void *, void *);
extern void func_0029F338(void *);
extern int func_00282978(void *);
extern float func_00282E80(void *, void *);
typedef struct ProjectileCollisionA4A8 {
    float direction[3];
    float marker;
    void *object;
    int flags;
    unsigned char kind, enabled;
    unsigned short class_id;
    float damage;
    int active;
} ProjectileCollisionA4A8;
typedef struct ProjectileStateA4A8 {
    float last_target[3];
    void *owner;
    struct ProjectileObjectA4A8 *target;
    float height, speed, yaw, spin_speed;
    short life;
    unsigned char homing, age;
    float spin;
    int history_index;
    float forward[4], target_offset[4];
    int sound, handle;
} ProjectileStateA4A8;
typedef struct ProjectileObjectA4A8 {
    char pad00[0x10];
    float position[4];
    signed char status;
    char pad21[0x47];
    ProjectileStateA4A8 *state;
    char pad6c[0x3e];
    unsigned short class_id;
    char padac[0x10];
    unsigned char hit;
    char padbd[3];
    float forward[4], right[4], up[4];
} ProjectileObjectA4A8;

void func_PAL_L00_0040F050(ProjectileObjectA4A8 *object)
{
    float old[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    float target_position[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float desired[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    union { ProjectileCollisionA4A8 record; float v[3][4]; } scratch __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    void *hit_object = 0;
    ProjectileStateA4A8 *state = object->state;
    ProjectileObjectA4A8 *target = state->target;
    float *health;
    float length, distance, angle, turn;
    int target_status;
    char *history;
    int i, explode;

    qcopy(old, object->position);
    func_002AFFD8((char *)object->position, up, 1);
    {
        SoundSlotA4A8 *sound = (SoundSlotA4A8 *)(D_00188660 + state->sound * 0x70);
        if (sound->object != object || sound->active == 0)
            state->sound = func_002E5CF8(1, 4, object);
    }
    {
        if (target != 0) {
            health = func_002AB1F0(target);
            target_status = (unsigned char)target->status;
            if (target_status == 0xfe) goto target_lost;
            if (target_status == 0xfd) goto target_lost;
            if (health != 0 && *health <= 0.0f) {
            target_lost:
                state->target = 0;
                target = 0;
            } else {
                qcopy(target_position, target->position);
                func_00282D30(step, up, state->height);
                func_00282CC0(target_position, target_position, step);
            }
        }
        if (target != 0 && state->life < 296 && target->status >= 0 && state->homing != 0) {
            step[0] = state->last_target[0];
            step[1] = state->last_target[1];
            step[2] = state->last_target[2];
            step[3] = 0.0f;
            func_00282CF0(delta, target_position, step);
            length = func_00282DF0(delta);
            func_00282CC0(desired, target_position, state->target_offset);
            func_00282CF0(direction, object->position, desired);
            distance = func_00282DF0(direction);
            if (distance != 0.0f) {
                angle = func_00282DB0(direction, delta) / distance;
                angle = 1.5707963705f - func_002831B0(angle);
                func_00282DD8(scratch.v[0], delta, direction);
                func_00282DD8(scratch.v[1], delta, scratch.v[0]);
                if (func_00282DB0(direction, scratch.v[1]) < 0.0f)
                    angle = -angle;
                turn = length / state->speed;
                turn *= func_00283198(angle);
                while (turn > 1.0f) turn -= 1.0f;
                while (turn < -1.0f) turn += 1.0f;
                angle = func_002831B0(turn);
                func_00282D30(direction, direction, -1.0f);
                func_00282F20(direction, direction, 1.0f);
                if (func_00282C48(angle) > 0.00001f) {
                    func_00282F20(scratch.v[2], scratch.v[0], 1.0f);
                    func_002AB668(scratch.v[2], scratch.v[2], angle);
                    func_002ACDE8(object->forward, direction, scratch.v[2]);
                    func_00282DD8(object->right, object->forward, up);
                    func_00282F20(object->right, object->right, 1.0f);
                    func_00282DD8(object->up, object->right, object->forward);
                    qcopy(state->forward, object->forward);
                }
            }
        } else {
            func_002FEE70(state->handle, state->forward, 0);
            qcopy(object->forward, state->forward);
            func_00282DD8(object->right, object->forward, up);
            func_00282F20(object->right, object->right, 1.0f);
            func_00282DD8(object->up, object->right, object->forward);
        }
        if (target != 0) {
            state->last_target[0] = target_position[0];
            state->last_target[1] = target_position[1];
            state->last_target[2] = target_position[2];
        }
        if (func_00282C48(state->yaw) > 0.0021f) {
            qcopy(step, object->forward);
            func_002AB668(delta, object->right, state->yaw * 0.017453294f);
            func_002ACDE8(object->forward, object->forward, delta);
            func_002ACDE8(object->up, object->up, delta);
            func_002AB668(delta, step, state->spin);
            func_002ACDE8(object->forward, object->forward, delta);
            func_002ACDE8(object->right, object->right, delta);
            func_002ACDE8(object->up, object->up, delta);
            func_002AB668(delta, object->forward, state->spin);
            func_002ACDE8(object->right, object->right, delta);
            func_002ACDE8(object->up, object->up, delta);
            state->spin = func_00283B98(state->spin, state->spin_speed * 0.017453294f);
        }
        object->forward[3] = object->right[3] = object->up[3] = 0.0f;
        func_00282D30(step, object->forward, state->speed);
        func_00282CC0(object->position, object->position, step);
        func_00300190(object->position, object->position);
        if (object->position[0] < 2.0f || object->position[0] > 1021.0f ||
            object->position[1] < 2.0f || object->position[1] > 1021.0f ||
            object->position[2] < 2.0f || object->position[2] > 1021.0f) {
            func_002ACAD0(object, D_L00_001B1FB0);
            func_0029F338(object);
        } else {
            func_L00_0040B2C0(object, delta);
            history = D_L00_00255BA0 + state->history_index * 0x40;
            for (i = 3; i > 0; i--) qcopy(history + i * 16, history + (i - 1) * 16);
            qcopy(history, delta);
            if (++state->age >= 4)
                ref_L00_0040A4A8_00(func_L00_0040B330, object);
            func_PAL_L00_0040FC40(object, old);
            qcopy(desired, object->position);
            func_00282D30(direction, up, -0.3f);
            func_00282CC0(direction, object->position, direction);
            if (func_002761F8(desired, direction, 2, 0, 0)) {
                func_00282D30(desired, up, 0.3f);
                func_00282CC0(object->position, D_L00_001BF200.position, desired);
            }
            {
                int settings_index = D_00139568[0x2c];
                TuningA4A8 *settings = &D_L00_00262570[settings_index];
                scratch.record.damage = settings->damage;
            }
            scratch.record.flags = 0x830000;
            scratch.record.object = object;
            scratch.record.active = 1;
            qcopy(scratch.record.direction, step);
            func_00282F20(scratch.record.direction, scratch.record.direction, 1.0f);
            scratch.record.marker = 5627.925f;
            scratch.record.kind = 3;
            scratch.record.enabled = 1;
            scratch.record.class_id = object->class_id;
            if (func_002761F8(old, object->position, 0, D_00189E20.object, &scratch.record)) {
                if (D_L00_001BF200.object != 0) {
                    if (D_L00_001BF200.object != D_00189E20.object &&
                        D_L00_001BF200.object != state->owner) {
                        object->hit = 2;
                        qcopy(object->position, D_L00_001BF200.position);
                        hit_object = object;
                    }
                } else if (D_L00_001BF200.surface > 0) {
                    object->hit = 1;
                    qcopy(object->position, D_L00_001BF200.position);
                }
            }
            if (object->hit != 0) {
                {
                    int sound_index = state->sound;
                    if (sound_index != -1) {
                        SoundSlotA4A8 *sound = (SoundSlotA4A8 *)(D_00188660 + sound_index * 0x70);
                        if (sound->object == object && sound->active != 0) func_002E59F8(sound_index);
                    }
                }
                state->sound = -1;
                func_002E5CF8(0, 0, object);
                qcopy(object->position, D_L00_001BF200.position);
                func_002AFFD8((char *)object->position, axis, 1);
                explode = 1;
                if (D_L00_001BF200.object != 0 && D_L00_001BF200.surface <= 0) {
                    func_00282CF0(normal, D_L00_001B8DC0, object->position);
                    func_00282F20(normal, normal, 1.0f);
                } else {
                    func_00282F20(normal, D_L00_001BF200.normal, 1.0f);
                    if (func_00282C48(func_00282DB0(normal, axis)) >= 0.1f) explode = 0;
                }
                if (explode) func_002A89A8(object->position, 0, 0.5f);
                {
                    int draw_effect = func_002A77E0(5) == 0;
                    func_PAL_L00_00418F28(object->position, 0.5f, 1, 15, 0, 0, 8, 15, 0, 1, 0, draw_effect, D_L00_001ADB2C);
                }
                func_L00_0040AFB8(object, axis, hit_object);
                func_002ACAD0(object, D_L00_001B1FB0);
                func_002FEE50(state->handle);
                func_0029F338(object);
            } else if (func_00282978(&state->life) || func_00282E80(object->position, D_00189EA0) > 60.0f) {
                {
                    int sound_index = state->sound;
                    if (sound_index != -1) {
                        SoundSlotA4A8 *sound = (SoundSlotA4A8 *)(D_00188660 + sound_index * 0x70);
                        if (sound->object == object && sound->active != 0) func_002E59F8(sound_index);
                    }
                }
                state->sound = -1;
                func_002ACAD0(object, D_L00_001B1FB0);
                func_002FEE50(state->handle);
                func_0029F338(object);
            }
        }
    }
}
