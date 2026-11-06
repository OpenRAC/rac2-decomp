/* func_PAL_L00_0040E9F0, the PAL copy of func_L00_00409E48: the same C, where 1.0f / 60.0f becomes
   0.020000001f; 300 becomes 250. */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));

extern char *func_0029EFD0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern char *func_002AB1F0(void *);
extern void func_L00_0040B2C0(void *, void *);
extern void func_002A0F48(void *);
extern void func_002ACA50(void *, void *, int);
extern int func_002FED90(void *, int, float, float, float);

extern int D_L00_001B0FD8 __attribute__((sda));
extern unsigned char D_00139583 __attribute__((nosda));

typedef struct ScaleRecord {
    char pad00[0x50];
    float value;
    char pad54[0x8c];
} ScaleRecord;
extern ScaleRecord D_L00_00262570[];

typedef struct ProjectileState {
    /* 0x00 */ float last_target[3];
    /* 0x0C */ void *owner;
    /* 0x10 */ void *target;
    /* 0x14 */ float height;
    /* 0x18 */ float speed;
    /* 0x1C */ float yaw;
    /* 0x20 */ float spin_speed;
    /* 0x24 */ short life;
    /* 0x26 */ unsigned char homing;
    /* 0x27 */ unsigned char age;
    /* 0x28 */ float spin;
    /* 0x2C */ int index;
    /* 0x30 */ Vector forward;
    /* 0x40 */ Vector color;
    /* 0x50 */ int sound;
    /* 0x54 */ int handle;
} ProjectileState;

typedef struct ProjectileObject {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ Vector position;
    /* 0x20 */ signed char status;
    /* 0x21 */ char pad21[0x0b];
    /* 0x2C */ float radius;
    /* 0x30 */ unsigned char alpha;
    /* 0x31 */ signed char enabled;
    /* 0x32 */ short color;
    /* 0x34 */ unsigned short flags;
    /* 0x36 */ char pad36[0x32];
    /* 0x68 */ ProjectileState *state;
    /* 0x6C */ char pad6c[0x50];
    /* 0xBC */ unsigned char hit;
    /* 0xBD */ char padbd[3];
    /* 0xC0 */ Vector forward;
    /* 0xD0 */ Vector right;
    /* 0xE0 */ Vector up;
} ProjectileObject;

typedef struct PlayerState {
    /* 0x0000 */ char pad0000[0x750];
    /* 0x0750 */ Vector up;
    /* 0x0760 */ Vector forward;
    /* 0x0770 */ char pad0770[0x1b20];
    /* 0x2290 */ char *object;
    /* 0x2294 */ int mode;
    /* 0x2298 */ char pad2298[0x254];
    /* 0x24EC */ short orientation;
} PlayerState;
extern PlayerState D_00189E20;

extern Vector D_L00_001B8FF0[3];   /* camera basis rows */
extern float D_L00_001B8DC0[4];    /* camera position */
extern float D_L00_001BF220[4];    /* collision hit point */
extern char D_L00_00255BA0[];
extern char D_L00_001B1FB0[] MACRO_ADDR;

/* Spawns a projectile (moby 0xED7) from owner at position, aimed at target or along the view. */
char *func_PAL_L00_0040E9F0(char *owner, void *position, char *target, void *color, float height)
{
    Vector aim, offset, tmp1, tmp2, tmp3, tmp4;
    ProjectileObject *m = (ProjectileObject *)func_0029EFD0(0xed7);
    ProjectileState *s;
    char *hit;
    float scale;

    if (m) {
        m->alpha = 255;
        m->enabled = 1;
        m->status = 0;
        m->color = 255;
        m->flags |= 0x100;
        s = m->state;
        s->sound = -1;
        if ((unsigned)D_L00_001B0FD8 > 32)
            D_L00_001B0FD8 = 0;
        s->index = D_L00_001B0FD8;
        D_L00_001B0FD8 = (D_L00_001B0FD8 + 1) % 32;
        scale = (D_L00_00262570 + D_00139583)->value * (0.020000001f);
        qcopy(m->position, position);
        if (target) {
            func_00282D30(offset, target + 0xe0, height);
            func_00282CC0(aim, target + 0x10, offset);
        } else {
            qzero(aim);
        }

        if (D_00189E20.mode == 29) {
            qcopy(m->forward, D_L00_001B8FF0[0]);
            qcopy(m->right, D_L00_001B8FF0[1]);
            qcopy(m->up, D_L00_001B8FF0[2]);
            qcopy(m->position, D_L00_001B8DC0);
            func_00282D30(offset, D_L00_001B8FF0[2], -0.2f);
            func_00282CC0(m->position, m->position, offset);
            func_00282D30(tmp1, D_L00_001B8FF0[1], -0.25f);
            func_00282CC0(m->position, m->position, tmp1);
            func_00282D30(tmp2, D_L00_001B8FF0[0], 0.0f);
            func_00282CC0(m->position, m->position, tmp2);
            if (target) {
                func_00282CF0(m->forward, aim, m->position);
                func_00282F20(m->forward, m->forward, 1.0f);
                func_00282DD8(m->right, m->forward, D_00189E20.object + 0xe0);
                func_00282F20(m->right, m->right, 1.0f);
                func_00282DD8(m->up, m->right, m->forward);
            } else {
                func_00282D30(tmp3, D_L00_001B8FF0[0], 30.0f);
                func_00282CC0(tmp3, D_L00_001B8DC0, tmp3);
                if (func_002761F8(D_L00_001B8DC0, tmp3, 0, D_00189E20.object, 0))
                    qcopy(tmp3, D_L00_001BF220);
                func_00282CF0(tmp4, tmp3, m->position);
                func_00282F20(m->forward, tmp4, 1.0f);
                func_00282DD8(m->right, m->forward, D_00189E20.object + 0xe0);
                func_00282F20(m->right, m->right, 1.0f);
                func_00282DD8(m->up, m->right, m->forward);
            }
        } else if (D_00189E20.orientation == 1) {
            func_00282F20(m->forward, owner + 0xd0, -1.0f);
            func_00282D30(m->right, owner + 0xc0, -1.0f);
            qcopy(m->up, owner + 0xe0);
        } else if (target) {
            func_00282CF0(m->forward, aim, m->position);
            func_00282F20(m->forward, m->forward, 1.0f);
            func_00282DD8(m->right, m->forward, D_00189E20.object + 0xe0);
            func_00282F20(m->right, m->right, 1.0f);
            func_00282DD8(m->up, m->right, m->forward);
        } else {
            qcopy(m->forward, D_00189E20.forward);
            func_00282DD8(m->right, m->forward, D_00189E20.up);
            func_00282F20(m->right, m->right, 1.0f);
            func_00282DD8(m->up, m->right, m->forward);
        }
        m->forward[3] = m->right[3] = m->up[3] = 0;

        s->owner = owner;
        s->yaw = func_002A7878(4.0f, 10.0f);
        if (target)
            s->yaw = 0;
        s->spin_speed = func_002A78D8(6.0f, 10.0f);
        s->speed = scale;
        s->spin = func_002A7940();
        s->target = 0;
        s->age = 1;
        s->homing = 1;
        qcopy(s->forward, m->forward);
        qcopy(s->color, color);
        if (target) {
            hit = func_002AB1F0(target);
            if (hit) {
                *(unsigned short *)(hit + 0x1e) |= 0x80;
                if (*(unsigned char *)(hit + 0xb))
                    s->homing = 0;
            }
        }
        s->life = 250;
        if (target) {
            float *target_position = (float *)(target + 0x10);

            s->last_target[0] = *(float *)(target + 0x10);
            s->last_target[1] = target_position[1];
            s->last_target[2] = target_position[2] + height;
            s->height = height;
        }

        /* Trace from the owner (at the spawn height) to the spawn point. */
        *(Quadword *)offset = *(Quadword *)(owner + 0x10);
        offset[2] = ((float *)position)[2];
        if (func_002761F8(offset, position, 0, D_00189E20.object, 0)) {
            m->hit = 1;
            qcopy(m->position, D_L00_001BF220);
        }
        func_L00_0040B2C0(m, D_L00_00255BA0 + s->index * 64);
        func_002A0F48(m);
        func_002ACA50(m, D_L00_001B1FB0, 31);
        s->handle = func_002FED90(m, 0, 1.0f, 1.0f, 1.0f);
        m->radius *= 2.5f;
    }
    return (char *)m;
}
