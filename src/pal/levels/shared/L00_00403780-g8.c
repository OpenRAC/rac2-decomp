#include "common.h"

extern void vec_transform_or_copy(void *, void *);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
typedef struct EffectParticle {
    unsigned char prefix[10];
    short life;
    unsigned char gap[20];
} EffectParticle;
typedef struct EffectParticleExtension {
    int color, mode;
    short spin;
    unsigned char alpha, life;
} EffectParticleExtension;
extern EffectParticle *SpawnSpinningSparkParticle(void *, float, float, float, int, void *, float, unsigned, int);
extern float D_L00_001A8F20[4] MACRO_ADDR;


extern void cam_compute_view_direction(void *, void *, int);
extern void moby_forward_position_call(void *, void *, int);
extern void part_steer_effect_direction(int, void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void LerpVector4(void *, void *, void *, float);
extern int CollideSweptSphere(void *);
extern int weapon_get_group(int);
extern int coll_process_hit(void *, int, void *, void *, float);
extern void StartAttachedEffect(void *, int, void *);
extern int PlayMobySound(int, int, void *);
extern void shot_spawn_fragments(void *);
extern void part_queue_ground_shadow(void *, float);
extern float FastVecDot(void *, void *);
extern unsigned char D_0013958D[];
typedef struct EffectPlayer {
    unsigned char prefix[0x70];
    float scale;
    unsigned char suffix[0x6C];
} EffectPlayer;
extern EffectPlayer g_weapon_l00_table[];
extern void *g_hero_moby[];
extern void *g_area_hit_targets[];
extern int D_L00_001A8FF0[] MACRO_ADDR, D_L00_001A8FF4[] MACRO_ADDR;
extern float D_L00_001B0C20 __attribute__((sda));
extern float D_L00_001B0C28 __attribute__((sda));
extern float D_L00_001B0C30 __attribute__((sda));
extern float D_L00_001B0C34 __attribute__((sda));
extern float D_L00_001B0C3C __attribute__((sda));
extern float D_L00_001B0C40 __attribute__((sda));
extern int D_L00_001B0C44 __attribute__((sda));
extern char D_L00_001BF230[];
extern unsigned char D_L00_001B0C48[8] NOT_SDA;

typedef int EffectQuad __attribute__((mode(TI)));
typedef union EffectVector { EffectQuad quad; float f[4]; } EffectVector;
typedef struct EffectState {
    EffectVector velocity, axis;
    int timer, bounces, trail, charged, rotation;
} EffectState;
typedef struct SweepQuery {
    EffectVector start, end, delta;
    void *owner;
    int *params;
    int mode;
    float radius, scale, extra;
    int field48, field4c, field50, hit, field58;
    float tolerance;
} SweepQuery;
typedef struct HitQuery {
    float pos[3], radius;
    void *owner;
    unsigned flags;
    unsigned char type, active;
    unsigned short classId;
    float scale;
    int enabled;
} HitQuery;

typedef struct EffectWorkspace {
    EffectVector normal, old;
    union { EffectVector point; int excluded[2]; } params;
    EffectVector tmp;
    SweepQuery query;
    HitQuery hit;
    EffectVector offset, step;
} EffectWorkspace;

/* func_PAL_L00_00403780, the PAL copy of func_L00_003FEEA0: the same C at 50 Hz, where the life 50
   becomes 42, the steps 0.0040555559f, 0.05235989f and 0.10471977f become 0.00584f, 0.062831864f and
   0.12566373f, the timer takes the 5/6 scale and the two per-frame factors (x - 1.0f) take 1.2f.
   The three initial values on result, kind and swept give gcse its 193 buckets: self + 0x10 then
   numbers ahead of the workspace's tmp, as retail's spill slots have them. */
void func_PAL_L00_00403780(char *self)
{
    EffectState *p = *(EffectState **)(self + 0x68);
    EffectWorkspace work;
    int i, result = 0, kind = 0, swept = 0;
    float radius, extra, speed, scale;
    float fadeRadius;
    int remaining;
    void **targets;
    cam_compute_view_direction(self + 0x10, work.normal.f, 1);
    vec_transform_or_copy(self + 0x10, self + 0x10);
    switch ((unsigned char)self[0x20]) {
    case 0:
        qcopy(work.old.f, self + 0x10);
        FastVecAdd(self + 0x10, self + 0x10, p);
        part_steer_effect_direction(p->rotation, p, 0);
        vec_add_object_direction_scaled(self + 0x10, p, 0.00584f);
        math_fast_float_d(&p->trail);
        if (p->trail) {
            for (i = 0; i < 3; i++) {
                int id;
                EffectParticle *r;
                float x;
                float f;
                float third = 0.33329999446868896f;
                float one = 1.0f;
                *(EffectQuad *)work.tmp.f = *(EffectQuad *)(self + 0x10);
                LerpVector4(work.params.point.f, work.old.f, work.tmp.f, IntToFloat(i) * third);
                id = math_random_int_below(6);
                if (math_random_int_below(2)) {
                    id = -id;
                }
                x = (float)p->trail / IntToFloat(42) * 65000.0f + 10000.0f;
                r = SpawnSpinningSparkParticle(work.params.point.f, 0.025f, one, one, id, D_L00_001A8F20, x, 0x80808080, 1);
                if (r) {
                    short life = 42;
                    EffectParticleExtension *extension = (EffectParticleExtension *)(r + 1);
                    r->life = life;
                    extension->mode = 2;
                    extension->alpha = 127;
                    { int l = r->life & 0xFF; extension->life = l; }
                }
            }
        }
        __builtin_memcpy(work.params.excluded, D_L00_001B0C48, 8);
        extra = 1.5f;
        if ((float)p->bounces == 3.0f) {
            extra = 0.0f;
        }
        radius = D_L00_001B0C30;
        if (p->charged) {
            radius = D_L00_001B0C3C;
        }
        qcopy(work.query.start.f, work.old.f);
        qcopy(work.query.end.f, self + 0x10);
        qcopy(work.query.delta.f, p);
        work.query.params = work.params.excluded;
        work.query.owner = self;
        work.query.mode = 2;
        work.query.radius = radius;
        work.query.scale = (D_L00_001B0C20 - 1.0f) * 1.2f + 1.0f;
        work.query.extra = extra;
        work.query.field48 = 0;
        work.query.field4c = 0;
        work.query.field58 = 0;
        swept = CollideSweptSphere(&work.query);
        kind = weapon_get_group(work.query.hit);
        if (swept > 0 && (unsigned)(kind - 1) < 2) {
            shot_spawn_fragments(self);
            moby_mark_spawned(self);
            return;
        }
        qcopy(self + 0x10, work.query.end.f);
        qcopy(p, work.query.delta.f);
        vec_rotate_by_quaternion(self + 0xC0, self + 0xC0, p->axis.f);
        vec_rotate_by_quaternion(self + 0xD0, self + 0xD0, p->axis.f);
        vec_rotate_by_quaternion(self + 0xE0, self + 0xE0, p->axis.f);
        work.hit.owner = self;
        work.hit.flags = 0x830000;
        { EffectPlayer *pl = &g_weapon_l00_table[D_0013958D[0]]; work.hit.scale = pl->scale; }
        work.hit.enabled = 1;
        qcopy(work.hit.pos, p);
        vec_scale_to_length(work.hit.pos, work.hit.pos, 1.0f);
        work.hit.type = 3;
        work.hit.radius = 5627.9248046875f;
        work.hit.classId = *(unsigned short *)(self + 0xAA);
        work.hit.active = 1;
        result = coll_process_hit(self + 0x10, 1, g_hero_moby[0], &work.hit, radius + 0.1f);
        if (result) {
            if (p->charged) {
                if (result > 0) {
                    targets = g_area_hit_targets;
                    remaining = result;
                    do {
                        StartAttachedEffect(*targets, 0x4C, *(void **)(self + 0xB8));
                        targets++;
                    } while (--remaining);
                }
            } else {
                if (result > 0) {
                    targets = g_area_hit_targets;
                    remaining = result;
                    do {
                        StartAttachedEffect(*targets, 0x25, *(void **)(self + 0xB8));
                        targets++;
                    } while (--remaining);
                }
            }
            shot_spawn_fragments(self);
            moby_mark_spawned(self);
            return;
        }
        if (swept > 0) {
            qcopy(work.tmp.f, p);
            work.tmp.f[2] = 0;
            FastVecCross(work.tmp.f, work.tmp.f, work.normal.f);
            vec_scale_to_length(work.tmp.f, work.tmp.f, 1.0f);
            math_build_axis_angle_quat(p->axis.f, work.tmp.f, math_random_float_range(0.062831864f, 0.12566373f));
            PlayMobySound(1, 0, self);
            p->bounces += 1;
            if (p->bounces >= 4) {
                qcopy(self + 0x10, D_L00_001BF230);
                self[0x20] = 1;
                p->timer = ((s32)(D_L00_001B0C44) * 5 + 2) / 6;
                speed = D_L00_001B0C28 * 0.062831864f;
                if (p->charged) {
                    speed *= D_L00_001B0C34;
                }
                moby_forward_position_call(self, work.offset.f, 1);
                scale = FastVecDot(work.offset.f, p);
                FastVecScale(work.step.f, work.offset.f, scale);
                FastVecSub(p, p, work.step.f);
                vec_scale_to_length(p, p, speed);
                qcopy(p->axis.f, work.tmp.f);
                p->axis.f[3] = 0.062831864f;
            }
        }
        break;
    case 1:
        FastVecAdd(self + 0x10, self + 0x10, p);
        math_build_axis_angle_quat(work.old.f, p->axis.f, p->axis.f[3]);
        vec_rotate_by_quaternion(self + 0xC0, self + 0xC0, work.old.f);
        vec_rotate_by_quaternion(self + 0xD0, self + 0xD0, work.old.f);
        vec_rotate_by_quaternion(self + 0xE0, self + 0xE0, work.old.f);
        scale = (D_L00_001B0C40 - 1.0f) * 1.2f + 1.0f;
        p->axis.f[3] *= scale;
        FastVecScale(p, p, scale);
        if (math_fast_float_d(&p->timer)) {
            shot_spawn_fragments(self);
            moby_mark_spawned(self);
            return;
        }
        break;
    }
    fadeRadius = D_L00_001B0C28;
    if (p->charged) {
        fadeRadius *= D_L00_001B0C34;
    }
    if (D_L00_001A8FF0[0] == 0 && D_L00_001A8FF4[0] == 0) {
        part_queue_ground_shadow(self, fadeRadius);
    }
}
