#include "common.h"

extern void *func_003100D8(int id);

extern int D_L00_001B1340 __attribute__((sda));

/* Allocates a record and tags it released-empty; returns it, or zero when the allocation failed. */
void *shot_alloc_record(int unused)
{
    char *p = (char *)func_003100D8(0x1136);

    if (p != 0) {
        int v = 0xFF;

        D_L00_001B1340 = (int)p;
        *(unsigned char *)(p + 0x20) = 1;
        *(unsigned short *)(p + 0x32) = v;
        *(unsigned char *)(p + 0x30) = v;
    }
    return p;
}


typedef struct {
    char reserved00[0x18];
    int active;
    char reserved1C[0x14];
} SettingSlot;

typedef struct {
    float amount;
    float scale;
    int kind;
    float multiplier;
} SettingRow;

typedef struct { SettingRow rows[238]; } SettingsBank;

extern SettingSlot D_L00_00256620[30];
extern SettingsBank D_L00_002592C0;

/* Sets up the shot tables at level start: clears 30 slots and fills in default values for two copies of 119 table rows. */
void shot_init_tables(void) {
    int i;

    for (i = 29; i >= 0; i--)
        D_L00_00256620[i].active = 0;
    D_L00_001B1340 = 0;
    shot_alloc_record(0);
    for (i = 119; i < 238; i++) {
        D_L00_002592C0.rows[i - 119].multiplier = 1.0f;
        D_L00_002592C0.rows[i].multiplier = 1.0f;
    }
    D_L00_002592C0.rows[30].amount = 2.0f;
    D_L00_002592C0.rows[30].scale = 0.67f;
    D_L00_002592C0.rows[30].kind = 4;
    D_L00_002592C0.rows[60].amount = 2.0f;
    D_L00_002592C0.rows[60].scale = 0.67f;
    D_L00_002592C0.rows[60].kind = 4;
    D_L00_002592C0.rows[23].amount = 10.0f;
    D_L00_002592C0.rows[23].scale = 5.00f;
    D_L00_002592C0.rows[23].kind = 2;
    D_L00_002592C0.rows[66].amount = 10.0f;
    D_L00_002592C0.rows[66].scale = 5.00f;
    D_L00_002592C0.rows[66].kind = 2;
    D_L00_002592C0.rows[41].amount = 1.0f;
    D_L00_002592C0.rows[41].scale = 2.00f;
    D_L00_002592C0.rows[41].kind = 3;
    D_L00_002592C0.rows[64].amount = 1.0f;
    D_L00_002592C0.rows[64].scale = 2.00f;
    D_L00_002592C0.rows[64].kind = 3;
    D_L00_002592C0.rows[24].amount = 2.0f;
    D_L00_002592C0.rows[24].scale = 2.00f;
    D_L00_002592C0.rows[24].kind = 2;
    D_L00_002592C0.rows[67].amount = 2.0f;
    D_L00_002592C0.rows[67].scale = 2.00f;
    D_L00_002592C0.rows[67].kind = 2;
    D_L00_002592C0.rows[31].amount = 1.0f;
    D_L00_002592C0.rows[31].scale = 1.00f;
    D_L00_002592C0.rows[31].kind = 1;
    D_L00_002592C0.rows[61].amount = 1.0f;
    D_L00_002592C0.rows[61].scale = 1.00f;
    D_L00_002592C0.rows[61].kind = 1;
    D_L00_002592C0.rows[149].amount = 10.0f;
    D_L00_002592C0.rows[149].scale = 4.00f;
    D_L00_002592C0.rows[149].kind = 6;
    D_L00_002592C0.rows[179].amount = 10.0f;
    D_L00_002592C0.rows[179].scale = 4.00f;
    D_L00_002592C0.rows[179].kind = 6;
    D_L00_002592C0.rows[142].amount = 10.0f;
    D_L00_002592C0.rows[142].scale = 8.00f;
    D_L00_002592C0.rows[142].kind = 3;
    D_L00_002592C0.rows[185].amount = 10.0f;
    D_L00_002592C0.rows[185].scale = 8.00f;
    D_L00_002592C0.rows[185].kind = 3;
    D_L00_002592C0.rows[160].amount = 2.0f;
    D_L00_002592C0.rows[160].scale = 4.00f;
    D_L00_002592C0.rows[160].kind = 3;
    D_L00_002592C0.rows[183].amount = 2.0f;
    D_L00_002592C0.rows[183].scale = 4.00f;
    D_L00_002592C0.rows[183].kind = 3;
    D_L00_002592C0.rows[143].amount = 6.0f;
    D_L00_002592C0.rows[143].scale = 2.00f;
    D_L00_002592C0.rows[143].kind = 3;
    D_L00_002592C0.rows[186].amount = 6.0f;
    D_L00_002592C0.rows[186].scale = 2.00f;
    D_L00_002592C0.rows[186].kind = 3;
    D_L00_002592C0.rows[150].amount = 1.0f;
    D_L00_002592C0.rows[150].scale = 1.00f;
    D_L00_002592C0.rows[150].kind = 1;
    D_L00_002592C0.rows[180].amount = 1.0f;
    D_L00_002592C0.rows[180].scale = 1.00f;
    D_L00_002592C0.rows[180].kind = 1;
}

typedef int Quadword __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));

extern char *CreateMoby(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern char *moby_get_private_value_0(void *);
extern void moby_get_offset_point(void *, void *);
extern void func_002A0F48(void *);
extern void AddMobyToIndexList(void *, void *, int);
extern int part_alloc_effect_slot(void *, int, float, float, float);

extern int D_L00_001B0FD8 __attribute__((sda));
extern unsigned char D_00139583 __attribute__((nosda));

typedef struct ScaleRecord {
    char pad00[0x50];
    float value;
    char pad54[0x8c];
} ScaleRecord;
extern ScaleRecord g_weapon_l00_table[];

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
extern PlayerState g_hero_state;

extern Vector D_L00_001B8FF0[3];   /* camera basis rows */
extern float g_camera_l00_position[4];    /* camera position */
extern float D_L00_001BF220[4];    /* collision hit point */
extern char D_L00_00255BA0[];
extern char D_L00_001B1FB0[] MACRO_ADDR;

/* Spawns a projectile (moby 0xED7) from owner at position, aimed at target or along the view. */
char *SpawnAimedProjectile(char *owner, void *position, char *target, void *color, float height)
{
    Vector aim, offset, tmp1, tmp2, tmp3, tmp4;
    ProjectileObject *m = (ProjectileObject *)CreateMoby(0xed7 /* moby class 3799 */);
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
        scale = (g_weapon_l00_table + D_00139583)->value * (1.0f / 60.0f);
        qcopy(m->position, position);
        if (target) {
            FastVecScale(offset, target + 0xe0, height);
            FastVecAdd(aim, target + 0x10, offset);
        } else {
            qzero(aim);
        }

        if (g_hero_state.mode == 29) {
            qcopy(m->forward, D_L00_001B8FF0[0]);
            qcopy(m->right, D_L00_001B8FF0[1]);
            qcopy(m->up, D_L00_001B8FF0[2]);
            qcopy(m->position, g_camera_l00_position);
            FastVecScale(offset, D_L00_001B8FF0[2], -0.2f);
            FastVecAdd(m->position, m->position, offset);
            FastVecScale(tmp1, D_L00_001B8FF0[1], -0.25f);
            FastVecAdd(m->position, m->position, tmp1);
            FastVecScale(tmp2, D_L00_001B8FF0[0], 0.0f);
            FastVecAdd(m->position, m->position, tmp2);
            if (target) {
                FastVecSub(m->forward, aim, m->position);
                vec_scale_to_length(m->forward, m->forward, 1.0f);
                FastVecCross(m->right, m->forward, g_hero_state.object + 0xe0);
                vec_scale_to_length(m->right, m->right, 1.0f);
                FastVecCross(m->up, m->right, m->forward);
            } else {
                FastVecScale(tmp3, D_L00_001B8FF0[0], 30.0f);
                FastVecAdd(tmp3, g_camera_l00_position, tmp3);
                if (CollLine(g_camera_l00_position, tmp3, 0, g_hero_state.object, 0))
                    qcopy(tmp3, D_L00_001BF220);
                FastVecSub(tmp4, tmp3, m->position);
                vec_scale_to_length(m->forward, tmp4, 1.0f);
                FastVecCross(m->right, m->forward, g_hero_state.object + 0xe0);
                vec_scale_to_length(m->right, m->right, 1.0f);
                FastVecCross(m->up, m->right, m->forward);
            }
        } else if (g_hero_state.orientation == 1) {
            vec_scale_to_length(m->forward, owner + 0xd0, -1.0f);
            FastVecScale(m->right, owner + 0xc0, -1.0f);
            qcopy(m->up, owner + 0xe0);
        } else if (target) {
            FastVecSub(m->forward, aim, m->position);
            vec_scale_to_length(m->forward, m->forward, 1.0f);
            FastVecCross(m->right, m->forward, g_hero_state.object + 0xe0);
            vec_scale_to_length(m->right, m->right, 1.0f);
            FastVecCross(m->up, m->right, m->forward);
        } else {
            qcopy(m->forward, g_hero_state.forward);
            FastVecCross(m->right, m->forward, g_hero_state.up);
            vec_scale_to_length(m->right, m->right, 1.0f);
            FastVecCross(m->up, m->right, m->forward);
        }
        m->forward[3] = m->right[3] = m->up[3] = 0;

        s->owner = owner;
        s->yaw = math_random_float_range(4.0f, 10.0f);
        if (target)
            s->yaw = 0;
        s->spin_speed = math_random_signed_float_range(6.0f, 10.0f);
        s->speed = scale;
        s->spin = math_random_angle();
        s->target = 0;
        s->age = 1;
        s->homing = 1;
        qcopy(s->forward, m->forward);
        qcopy(s->color, color);
        if (target) {
            hit = moby_get_private_value_0(target);
            if (hit) {
                *(unsigned short *)(hit + 0x1e) |= 0x80;
                if (*(unsigned char *)(hit + 0xb))
                    s->homing = 0;
            }
        }
        s->life = 300;
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
        if (CollLine(offset, position, 0, g_hero_state.object, 0)) {
            m->hit = 1;
            qcopy(m->position, D_L00_001BF220);
        }
        moby_get_offset_point(m, D_L00_00255BA0 + s->index * 64);
        func_002A0F48(m);
        AddMobyToIndexList(m, D_L00_001B1FB0, 31);
        s->handle = part_alloc_effect_slot(m, 0, 1.0f, 1.0f, 1.0f);
        m->radius *= 2.5f;
    }
    return (char *)m;
}

extern int FastDecTimer(void *);
extern void math_l00_interpolate_cubic_vector(void *, void *, void *, void *, void *, float);
extern short D_L00_001B2D40[] __attribute__((sda));
extern short D_L00_001B2D48[] __attribute__((sda));
extern short D_L00_001B2D50[] __attribute__((sda));
extern float D_0018BE30[4];
extern float D_L00_001B100C __attribute__((sda));
extern float D_L00_001B1004 __attribute__((sda));
extern Vector D_L00_002563A0[][10];

/* Updates four jagged lightning strands: when a strand timer ends it makes a new curve, otherwise it jitters the points a little. */
void lightning_strands_update(char *object)
{
    Vector p, delta, out, diffs[10];
    char *state = *(char **)(object + 0x68);
    int g, i, j, k, l, n;

    for (g = 0; g < 4; g++) {
        if (FastDecTimer(&D_L00_001B2D40[g])) {
            D_L00_001B2D48[g] = 0;
            D_L00_001B2D40[g] = D_L00_001B2D50[g];
            qcopy(p, state + 0x30);
            p[0] += math_random_float_range(-0.5f, 0.5f);
            p[1] += math_random_float_range(-0.5f, 0.5f);
            p[2] += math_random_float_range(-0.5f, 0.5f);
            FastVecSub(delta, p, D_0018BE30);
            vec_scale_to_length(delta, delta, D_L00_001B100C);
            FastVecAdd(delta, p, delta);
            for (i = 0; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9)
                    t = 1.0f;
                math_l00_interpolate_cubic_vector(out, D_0018BE30, p, state + 0x40, delta, t);
                qcopy(D_L00_002563A0[g][i], out);
            }
        } else {
            for (j = 1; j < 10; j++) {
                FastVecSub(diffs[j], D_L00_002563A0[g][j], (&((Vector *)D_L00_002563A0)[g * 10 + j])[-1]);
                diffs[j][0] += math_random_signed_float_range(0.0f, 0.05f);
                diffs[j][1] += math_random_signed_float_range(0.0f, 0.05f);
                diffs[j][2] += math_random_signed_float_range(0.0f, 0.05f);
            }
            qcopy(D_L00_002563A0[g][0], D_0018BE30);
            for (k = 1; k < 10; k++)
                FastVecAdd(D_L00_002563A0[g][k], (&((Vector *)D_L00_002563A0)[g * 10 + k])[-1], diffs[k]);
        }
        for (l = 2; l < 9; l++) {
            qcopy(p, D_L00_002563A0[0][l]);
            p[0] += math_random_signed_float_range(0.0f, D_L00_001B1004);
            p[1] += math_random_signed_float_range(0.0f, D_L00_001B1004);
            p[2] += math_random_signed_float_range(0.0f, D_L00_001B1004);
            qcopy(D_L00_002563A0[1][l], p);
        }
        for (n = 2; n < 9; n++) {
            qcopy(p, D_L00_002563A0[0][n]);
            p[0] += math_random_signed_float_range(0.0f, D_L00_001B1004);
            p[1] += math_random_signed_float_range(0.0f, D_L00_001B1004);
            p[2] += math_random_signed_float_range(0.0f, D_L00_001B1004);
            qcopy(D_L00_002563A0[2][n], p);
        }
        for (i = 2; i < 9; i++) {
            qcopy(p, D_L00_002563A0[0][i]);
            p[0] += math_random_signed_float_range(0.0f, D_L00_001B1004);
            p[1] += math_random_signed_float_range(0.0f, D_L00_001B1004);
            p[2] += math_random_signed_float_range(0.0f, D_L00_001B1004);
            qcopy(D_L00_002563A0[3][i], p);
        }
    }
}
