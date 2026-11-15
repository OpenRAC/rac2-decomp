#include "common.h"

extern float IntToFloat(int);
extern char *g_route_path_table[];
extern void anim_sample_key_track(void *, void *, void *, void *, float, float);
extern void func_002A05A8(void *);

#include "include_asm.h"

extern int part_find_owned_effect_slot(unsigned char *a0, int a1, int a2);

extern void gfx_start_color_fade(unsigned char *a0, unsigned char *a1);

extern void gfx_update_color_fade(unsigned char *a0, unsigned char *a1);

extern void *CreateMoby(void *a0);

extern void func_002A0F48(void *a0);

extern int moby_count_group_not_in_state(void *a0, int a1);

extern int math_random_int_below(int a0);

extern void glow_ring_update_variant(unsigned char *a0);

#ifndef RAC2_T_Q16_B0E5D8F83
#define RAC2_T_Q16_B0E5D8F83
typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));
#endif

/* func_L04_003C8380 is in L04_003C8380-stream.c. */

extern char D_L04_001B9680[];
extern void vec_scale_to_length(char *, char *, float);
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern float math_random_signed_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int FloatToInt(float);
extern void FastVecSub(void *, void *, void *);

/* Emits paired particles with opposite spin and randomized velocities. */
void part_l04_spawn_paired_sparks(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    FastVecSub(direction, (float *)D_L04_001B9680, pos);
    vec_scale_to_length((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (!sign) sign--;
        angle = func_002A7878_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        vec_scale_to_length((char *)velocity, (char *)velocity, func_002A7878_range(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = func_002A7878_range(1.0f, 5.0f) * 0.0166666675f;
        FastVecAdd(origin, pos, offset);
        pos[0] += math_random_signed_float_range(0, 0.15f);
        pos[1] += math_random_signed_float_range(0, 0.15f);
        pos[2] += math_random_signed_float_range(0, 0.15f);
        particle = part_spawn_ground_effect(origin, 60, size * 0.1f, size, 0x80CA00CB, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = part_spawn_ground_effect(origin, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}


/* Creates a new moby of the given class at the parent's position and turning, sized from its class scale. */
void *moby_spawn_at_parent_pose(unsigned char *parent, void *class_id, float scale_factor) {
    unsigned char *child = CreateMoby(class_id);

    if (child != 0) {
        child[0x30] = 0xFF;
        child[0x31] = 1;
        *(unsigned short *)(child + 0x32) = 0xFF;
        child[0x20] = 0;
        *(float *)(child + 0x2C) = *(float *)(*(unsigned char **)(child + 0x24) + 0x24) * scale_factor;
        *(Q16_B0e5d8f83 *)(child + 0x10) = *(Q16_B0e5d8f83 *)(parent + 0x10);
        *(Q16_B0e5d8f83 *)(child + 0xF0) = *(Q16_B0e5d8f83 *)(parent + 0xF0);
        child[0x62] = 1;
        func_002A0F48(child);
    }
    return child;
}

typedef union {
    Q16_B0e5d8f83 q;
    float f[4];
} Vec;

/* A moby class, as far as these functions read it. */
typedef struct {
    u8 pad00[0x0F];
    u8 f0F;                     /* 0x0F */
    int f10;                    /* 0x10: copied to the moby's +0x98 */
    u8 pad14[0x24 - 0x14];
    float scale;                /* 0x24 */
    u8 pad28[0x40 - 0x28];
    int f40;                    /* 0x40 */
    u16 modeBits;               /* 0x44: the moby's initial mode bits */
} MobyClass;

/* The moby, as far as func_L04_003EDD40 and func_L04_003F9ED0 read it. */
typedef struct Moby {
    u8 pad00[0x10];
    Vec position;               /* 0x10 */
    u8 state;                   /* 0x20 */
    u8 pad21[0x24 - 0x21];
    MobyClass *mclass;          /* 0x24 */
    u8 pad28[0x2C - 0x28];
    float scale;                /* 0x2C */
    u8 f30;                     /* 0x30 */
    u8 f31;                     /* 0x31 */
    s16 f32;                    /* 0x32 */
    u16 modeBits;               /* 0x34 */
    s16 f36;                    /* 0x36 */
    u8 pad38[0x40 - 0x38];
    u8 f40[4];                  /* 0x40 */
    u8 pad44[0x61 - 0x44];
    u8 f61;                     /* 0x61 */
    u8 f62;                     /* 0x62 */
    u8 pad63[0x68 - 0x63];
    void *vars;                 /* 0x68: the instance data */
    u8 pad6C[0x7F - 0x6C];
    u8 f7F;                     /* 0x7F */
    u8 pad80[0x98 - 0x80];
    int f98;                    /* 0x98 */
    u8 pad9C[0xA8 - 0x9C];
    u8 impactSlot;              /* 0xA8 */
    u8 padA9;
    s16 oClass;                 /* 0xAA */
    u8 padAC[0xB2 - 0xAC];
    s16 uid;                    /* 0xB2 */
    u8 padB4[0xB8 - 0xB4];
    struct Moby *parent;        /* 0xB8 */
    u8 fBC;                     /* 0xBC: func_L04_003F9ED0's hit: 1 surface, 2 moby */
    u8 padBD[0xF0 - 0xBD];
    Vec rotation;               /* 0xF0 */
} Moby;

/* The instance data of a moby that hands out children. */
typedef struct {
    u8 pad00[0x81];
    u8 childCount;              /* 0x81 */
    u8 pad82;
    u8 smallChildren;           /* 0x83: children start at a tenth of their class scale */
    int group;                  /* 0x84: the moby group the children come from */
} SpawnerVars;

/* What ref_L04_003EDD40_02 returns for a moby. */
typedef struct {
    u8 pad00[0x68];
    s16 f68;                    /* 0x68 */
    u8 pad6A[0x6C - 0x6A];
    int f6C;                    /* 0x6C */
    u8 pad70[0x94 - 0x70];
    int f94;                    /* 0x94 */
} ChildState;

/* What ref_L04_003EDD40_05 returns for a moby. */
typedef struct {
    float f00;                  /* 0x00 */
    s16 f04;                    /* 0x04 */
    u8 pad06[0x20 - 0x06];
    int f20;                    /* 0x20 */
    int f24;                    /* 0x24 */
} ChildInfo;

/* In level 04 these resolve to func_002A8600 (GetFirstMobyInGroup), func_0029F390,
   func_L00_00345AF0, func_002AB650, func_002A0F48, func_002AB1F0 and func_0026FEB8. */
extern int ref_L04_003EDD40_00(Moby **, int, int, int);
extern void ref_L04_003EDD40_01(Moby *);
extern ChildState *ref_L04_003EDD40_02(Moby *);
extern void ref_L04_003EDD40_03(Moby *);
extern void ref_L04_003EDD40_04(Moby *);
extern ChildInfo *ref_L04_003EDD40_05(Moby *);
extern void ref_L04_003EDD40_06(char *, int, int);
extern char ref_L04_003EDD40_07[];
extern int ref_L04_003EDD40_08[] __attribute__((sda));

/* Takes the first moby of the parent's group as a new child: places it at position with
   its class defaults, links it to the parent and counts it. Returns the child, or 0 when
   there is no parent or no moby to take (which is reported with the parent's uid). */
Moby *SpawnChildMoby(Moby *parent, Vec *position)
{
    Moby *child;
    Moby *result;
    SpawnerVars *vars;
    ChildInfo *info;
    Q16_B0e5d8f83 startCopy;
    float *start = (float *)&startCopy;

    *(Q16_B0e5d8f83 *)start = position->q;
    if (!parent)
        return 0;
    result = 0;
    vars = parent->vars;
    child = 0;
    if (!ref_L04_003EDD40_00(&child, vars->group, 1, 1)) {
        vars->childCount++;
        {
            Moby *copy = child;
            qcopy(&copy->position, start);
            copy->position.f[3] = 0;
        }
        child->state = 0;
        child->fBC = 0;
        child->modeBits = child->mclass->modeBits;
        child->scale = child->mclass->scale;
        child->f30 = 255;
        child->f32 = 255;
        child->f31 = 1;
        child->f40[0] = 0;
        child->f40[1] = 0;
        child->f40[2] = 0;
        child->f40[3] = 0;
        ref_L04_003EDD40_01(child);
        if (child->mclass->f40)
            child->modeBits |= 0x10;
        if (child->mclass->f0F)
            child->modeBits |= 0x400;
        child->f36 = 0x7F80;
        child->f61 = 255;
        child->f62 = 255;
        child->impactSlot = 255;
        if (vars->smallChildren)
            child->scale = child->mclass->scale * 0.1f;
        {
            ChildState *childState = ref_L04_003EDD40_02(child);
            if (childState) {
                childState->f94 = 0;
                childState->f68 = 0;
                childState->f6C = 0;
            }
        }
        child->parent = parent;
        child->f98 = child->mclass->f10;
        ref_L04_003EDD40_03(child);
        ref_L04_003EDD40_04(child);
        result = child;
        info = ref_L04_003EDD40_05(result);
        if (info) {
            info->f24 = 0;
            info->f20 = 0;
            info->f00 = (float)info->f04;
        }
        child->f7F = 0;
    } else {
        ref_L04_003EDD40_06(ref_L04_003EDD40_07, parent->uid, ref_L04_003EDD40_08[0]);
    }
    return result;
}

/* Switches the moby to state 2 and starts a timed effect on it when a check passes, then refreshes the effect. */
void moby_start_timed_effect(unsigned char *moby, unsigned char *vars) {
    if (part_find_owned_effect_slot(moby, 0x10000, 0) != 0) {
        moby[0x20] = 2;
        vars[0x57] = 0x78;
        gfx_start_color_fade(moby, vars + 0x50);
    }
    moby[0xA8] = 0xFF;
    gfx_update_color_fade(moby, vars + 0x50);
}

/* Stamps byte 0x81 from the per-record lookup, then walks the twenty slots: a slot whose
   object is live (not in either harness state) without the 0xB66 mark raises the count,
   every other slot is remembered in the returned index (-1 when all twenty pass). */
/* Counts the live objects of one kind among twenty slots and returns the last slot that is free, or -1 if none is. */
int moby_count_slot_objects_find_free(unsigned char *moby, char *vars_arg)
{
    char *vars = vars_arg;
    int i;
    int last = -1;

    *(unsigned char *)(vars + 0x81) = moby_count_group_not_in_state(*(void **)(vars + 0x84), -1);
    for (i = 0; i < 20; i++) {
        char *slot_moby = *(char **)(vars + 0xA0 + i * 4);

        if (slot_moby != 0 && *(short *)(slot_moby + 0xAA) == 0xB66 /* moby class 2918 */
            && *(unsigned char *)(slot_moby + 0x20) != 0xFE
            && *(unsigned char *)(slot_moby + 0x20) != 0xFD) {
            *(unsigned char *)(vars + 0x81) = *(unsigned char *)(vars + 0x81) + 1;
        } else {
            last = i;
        }
    }
    return last;
}




/* Sets up four glow sprites with random start phases, sizes and fading brightness. */
void glow_l04_ring_init(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float *phase_ptr;
    unsigned int *alpha_ptr;
    unsigned int alpha_value;
    int i;
    int j;

    phase_ptr = (float *)(vars + 0x14);
    for (i = 3; i >= 0; i--) {
        *phase_ptr++ = (float)math_random_int_below(0xFF);
    }
    *(float *)(vars + 0x24) = -1.0f;
    *(float *)(vars + 0x28) = -2.25f;
    *(float *)(vars + 0x2C) = 1.25f;
    *(float *)(vars + 0x30) = 2.5f;
    j = 3;
    alpha_ptr = (unsigned int *)(vars + 0x40);
    alpha_value = 0xFF;
    for (; j >= 0; j--) {
        *alpha_ptr = alpha_value;
        alpha_ptr--;
        alpha_value -= 0x40;
    }
    *(float *)(vars + 0x44) = 2.0f;
    *(float *)(vars + 0x48) = 2.5f;
    *(float *)(vars + 0x4C) = 2.5f;
    *(float *)(vars + 0x50) = 2.0f;
}


/* Sets up four glow sprites with random start phases, sizes and fading brightness (variant with a smaller state block). */
void glow_ring_init_variant(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float *phase_ptr;
    unsigned int *alpha_ptr;
    unsigned int alpha_value;
    int i;
    int j;

    phase_ptr = (float *)(vars + 0x10);
    for (i = 3; i >= 0; i--) {
        *phase_ptr++ = (float)math_random_int_below(0xFF);
    }
    *(float *)(vars + 0x20) = -1.0f;
    *(float *)(vars + 0x24) = -2.25f;
    *(float *)(vars + 0x28) = 1.25f;
    *(float *)(vars + 0x2C) = 2.5f;
    j = 3;
    alpha_ptr = (unsigned int *)(vars + 0x3C);
    alpha_value = 0xFF;
    for (; j >= 0; j--) {
        *alpha_ptr = alpha_value;
        alpha_ptr--;
        alpha_value -= 0x40;
    }
    *(float *)(vars + 0x40) = 2.0f;
    *(float *)(vars + 0x44) = 2.5f;
    *(float *)(vars + 0x48) = 2.5f;
    *(float *)(vars + 0x4C) = 2.0f;
}


/* func_L04_003F9320 is in L04_003C8380-shot.c. */

/* func_L04_003F9718 is in L04_003C8380-homing.c. */

/* func_L04_003F9C60 is in L04_003F9C60-zero.c. */

/* The probe func_002761F8 and func_00277F48 test with. */
typedef struct {
    float v[4];                 /* 0x00 */
    void *owner;                /* 0x10 */
    int flags;                  /* 0x14 */
    u8 mode;                    /* 0x18 */
    u8 enabled;                 /* 0x19 */
    u16 oClass;                 /* 0x1A: the class of owner */
    float radius;               /* 0x1C */
    int active;                 /* 0x20 */
} CollisionProbe;

/* The hit of the last collision probe: D_L04_001BFAC0's +0x20, which retail also
   addresses under its own symbol, D_L04_001BFAE0. */
typedef struct {
    Vec point;                  /* 0x00 */
    u8 pad10[0x20 - 0x10];
    Vec normal;                 /* 0x20 */
    Vec f30;                    /* 0x30 */
    Vec f40;                    /* 0x40 */
} CollisionHit;
/* func_L04_003FA350 is defined in L04_003FA350.c. */

/* The result of the last collision probe. */
typedef struct {
    u8 pad00[0x18];
    Moby *moby;                 /* 0x18: the moby hit, or 0 */
    int count;                  /* 0x1C: above 0 when a surface was hit */
    CollisionHit hit;           /* 0x20 */
} Collision;

/* The projectile's instance data. */
typedef struct {
    u8 pad00[0x20];
    Moby *ignored;              /* 0x20: the moby its probes pass through */
} ProjectileVars;

extern void vec_fast_normalize_helper(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
/* The radius comes first: the EE ABI keeps the order within each register bank. */
extern int coll_process_hit(float, void *, int, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern void func_001290E0(void *, void *);
extern void add_vectors(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern void part_l04_spawn_burst(void *, void *, int, int);
extern Collision D_L04_001BFAC0;
extern CollisionHit D_L04_001BFAE0;

/* Sweeps a projectile from *position by direction (a line probe over the whole move and,
   when that is clear, a 0.5 sphere probe every 0.49 units) and works out its response.
   Hitting a moby other than the ignored one sets fBC to 2, moves onto that moby (or
   stays, for class 0xA1F) and returns the projectile. A surface whose normal lies 45 to
   90 degrees from direction bends direction by the normal, re-aims the projectile and
   marks the hit point; any other surface hit sets fBC to 1 and moves to the hit point.
   Moby and stopping surface hits fill response, hitNormal and hitDelta. The final
   position is written back to *position; the result is 0 unless a moby was hit. */
Moby *SweepProjectileCollision(Moby *projectile, ProjectileVars *vars, float *position,
    float *direction, float *response, float *hitNormal, float *hitDelta)
{
    float pos[4];
    float unit[4];
    float step[4];
    CollisionProbe probe;
    float forward[4];
    float hitPoint[4];
    float target[4];
    Collision *collision;
    Moby *hitMoby;
    Moby *result = 0;
    float remaining;
    float stride = 0;
    float dot;
    int lineHit;
    int collided = 0;

    *(Q16_B0e5d8f83 *)pos = *(Q16_B0e5d8f83 *)position;
    probe.flags = 0x30000;
    probe.radius = 2;
    probe.owner = projectile;
    probe.active = 1;
    qcopy(probe.v, direction);
    vec_fast_normalize_helper(&probe, &probe, 1);
    probe.enabled = 1;
    probe.v[3] = 5627.925f;
    probe.mode = 3;
    probe.oClass = projectile->oClass;
    probe.v[2] = 1;

    FastVecAdd(step, pos, direction);
    lineHit = CollLine(pos, step, 0, vars->ignored, &probe);
    if (lineHit) {
        collided = 1;
        remaining = 0;
    } else {
        stride = 0.49f;
        remaining = FastVecLength(direction);
        if (remaining > 0)
            FastVecScale(unit, direction, 1.0f / remaining);
        else
            qzero(unit);
    }
    while (remaining > 0 && !collided) {
        if (stride < remaining) {
            FastVecScale(step, unit, stride);
            remaining -= stride;
        } else {
            FastVecScale(step, unit, remaining);
            remaining = 0;
        }
        FastVecAdd(pos, pos, step);
        if (coll_process_hit(0.5f, pos, 0, vars->ignored, &probe))
            collided = 1;
    }

    if (collided) {
        collision = &D_L04_001BFAC0;
        if (collision->moby) {
            if (collision->moby == vars->ignored)
                goto done;
            projectile->fBC = 2;
            hitMoby = collision->moby;
            if (hitMoby->oClass == 0xA1F /* moby class 2591 */)
                qcopy(pos, &projectile->position);
            else
                qcopy(pos, &hitMoby->position);
            FastVecSub(hitDelta, &D_L04_001BFAE0.f30, &D_L04_001BFAE0.f40);
            vec_scale_to_length((char *)hitDelta, (char *)hitDelta, 1);
            result = projectile;
            vec_fast_normalize(response, direction, &D_L04_001BFAE0.normal);
            vec_scale_to_length((char *)response, (char *)response, 0.033333335f);
            vec_scale_to_length((char *)hitNormal, (char *)&D_L04_001BFAE0.normal, 1);
        } else if (collision->count > 0) {
            *(Q16_B0e5d8f83 *)forward = *(Q16_B0e5d8f83 *)direction;
            func_001290E0(&collision->hit.normal, &collision->hit.normal);
            func_001290E0(forward, forward);
            dot = FastVecDot(forward, &collision->hit.normal);
            if (dot > 0 && dot < 0.707f) {
                FastVecScale(&collision->hit.normal, &collision->hit.normal, dot);
                FastVecAdd(direction, direction, &collision->hit.normal);
                add_vectors(target, pos, direction);
                projectile->rotation.f[2] = mat_fast_helper_a(direction[0], direction[1]);
                projectile->rotation.f[1] = -mat_fast_helper_a(vec_length_xy(direction), direction[2]);
                *(Q16_B0e5d8f83 *)hitPoint = collision->hit.point.q;
                part_l04_spawn_burst(hitPoint, direction, 4, 0);
            } else {
                projectile->fBC = 1;
                qcopy(pos, &D_L04_001BFAE0.point);
                FastVecSub(hitDelta, &D_L04_001BFAE0.f30, &D_L04_001BFAE0.f40);
                vec_scale_to_length((char *)hitDelta, (char *)hitDelta, 1);
                vec_fast_normalize(response, direction, &D_L04_001BFAE0.normal);
                vec_scale_to_length((char *)response, (char *)response, 0.033333335f);
                vec_scale_to_length((char *)hitNormal, (char *)&D_L04_001BFAE0.normal, 1);
            }
        }
    }
done:
    *(Q16_B0e5d8f83 *)position = *(Q16_B0e5d8f83 *)pos;
    return result;
}

extern void ref_L04_003FA5A8_00(void *, float, float, float);
extern unsigned char *ref_L04_003FA5A8_01(void *, void *, void *, float *, float *, float *, float, float);
extern void ref_L04_003FA5A8_02(void *, void *, void *);
extern void ref_L04_003FA5A8_03(void *, void *, void *, void *, void *, void *, void *);
/* Creates a homing rocket for its owner and aims it at the given target, or at the best target found ahead. */
unsigned char *homing_rocket_spawn(unsigned char *owner, float *pos,
    unsigned char *target, float aim_yaw, float aim_pitch, float aim_height, float facing_yaw, float facing_pitch)
{
    float origin[4], matrix[16], position[4];
    unsigned char *rocket = CreateMoby((void *)0xABD /* moby class 2749 */);
    unsigned char *vars;

    if (rocket != 0) {
        rocket[0x30] = 255;
        *(short *)(rocket + 0x32) = 255;
        rocket[0x31] = 1;
        rocket[0x20] = 0;
        *(float *)(rocket + 0xF8) = facing_yaw;
        *(float *)(rocket + 0xF4) = facing_pitch;
        *(float *)(rocket + 0x2C) =
            *(float *)(*(unsigned char **)(rocket + 0x24) + 0x24) * 3.0f;
        vars = *(unsigned char **)(rocket + 0x68);
        if (target == 0) {
            ref_L04_003FA5A8_00(matrix, 0.33333334f, facing_yaw, facing_pitch);
            *(Q16_B0e5d8f83 *)position = *(Q16_B0e5d8f83 *)pos;
            target = ref_L04_003FA5A8_01(rocket, position, matrix, &aim_yaw, &aim_pitch, &aim_height,
                0.349065899848938f, 30.0f);
        }
        *(void **)(vars + 0x20) = owner;
        qcopy(rocket + 0x10, pos);
        *(int *)(vars + 0x48) = 1;
        *(float *)(vars + 0x44) = 0.8333333730697632f;
        *(int *)(vars + 0x34) = 0;
        *(int *)(vars + 0x38) = 0;
        *(int *)(vars + 0x30) = 0;
        *(int *)(vars + 0x54) = -1;
        *(int *)(vars + 0x50) = -1;
        *(void **)(vars + 0x28) = target;
        *(float *)(vars + 0x3C) = aim_yaw;
        *(float *)(vars + 0x40) = aim_pitch;
        *(int *)(vars + 0x24) = 300;
        if (target != 0) {
            qcopy(vars, target + 0x10);
            *(float *)(vars + 8) += aim_height;
            *(float *)(vars + 0x2C) = aim_height;
        }
        if (owner != 0 && *(short *)(owner + 0xAA) == 0xBBC /* moby class 3004 */) {
            *(short *)(vars + 0x4E) = 60;
            *(short *)(vars + 0x4C) = 60;
        } else {
            *(short *)(vars + 0x4E) = 1;
            *(short *)(vars + 0x4C) = 1;
        }
        *(Q16_B0e5d8f83 *)origin = *(Q16_B0e5d8f83 *)(owner + 0x10);
        origin[2] = pos[2];
        ref_L04_003FA5A8_02(matrix, pos, origin);
        if (target != 0 && *(short *)(target + 0xAA) != 0xBBC /* moby class 3004 */) {
            ref_L04_003FA5A8_03(rocket, vars, origin, matrix,
                matrix + 12, matrix + 4, matrix + 8);
        }
        func_002A0F48(rocket);
        *(float *)(rocket + 0x2C) += *(float *)(rocket + 0x2C);
    }
    return rocket;
}

/* func_L04_003FA7E0 is defined in L04_003FA7E0.c. */


extern int PlayMobySound(int, int, char *);

extern unsigned char *D_L04_001C3B40[];
extern float FastDiffRots(float, float);
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(char *, char *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_float_g(float);
extern float FastAddRotations(float, float);
extern void QueueMobyImpact(void *, void *);
extern void vec_build_spherical_offset(void *, float, float, float);

/* The impact record func_002A8E20 queues: the layout of Rac2Impact32 in engine.h,
   rounded up to whole quadwords as its stack slot is. */
typedef struct {
    float vector[4];
    void *source;
    int flags;
    unsigned char unk18, unk19;
    unsigned short objectClass;
    float strength;
    int unk20;
    int unk24;
    int pad[2];
} B990Impact;

/* Hits the mobys around m inside its firing cone, then traces the cone's edge rays and
   leaves an effect where one is blocked. gcse numbers the two spilled pointers in hash-bucket
   order, and retail's stack slots need at least 228 insns there: the argument locals, range
   and the initial values of angle, angle0, angle1, sign and i supply them, and leave no code. */
void moby_damage_in_firing_cone(unsigned char *m, void *vars)
{
    unsigned char *v = vars;
    float radius = *(float *)(v + 0x70) * *(float *)(v + 0x7C);
    float angle = 0.0f, angle0 = 0.0f, angle1 = 0.0f, sign = 0.0f;
    int count, n, side, i = 0;
    int soundId = 10, soundArg = 0;
    int rayMask = 18;
    void *rayResult = 0;
    int sparkKind = 8, sparkArg = 0;
    if (radius < 0.75f) radius = 0.75f;
    n = coll_process_hit(radius, m + 0x10, 16, *(void **)(v + 0x74), 0);
    for (count = 0; count < n; count++) {
        if (D_L04_001C3B40[count] == *(unsigned char **)(v + 0x74)) continue;
        if (*(float *)(v + 0x7C) > 0) {
            angle = mat_fast_helper_a(*(float *)(D_L04_001C3B40[count] + 0x10) - *(float *)(m + 0x10),
                                  *(float *)(D_L04_001C3B40[count] + 0x14) - *(float *)(m + 0x14));
            if (FastDiffRots(angle, *(float *)(m + 0xF8)) > 0.741765022277832f) continue;
            angle = mat_fast_helper_a(vec_distance_xy(m + 0x10, D_L04_001C3B40[count] + 0x10),
                                  *(float *)(D_L04_001C3B40[count] + 0x18) - *(float *)(m + 0x18));
            if (FastDiffRots(angle, -*(float *)(m + 0xF4)) > 0.523598849773407f) continue;
        }
        if (fast_vec_dist((char *)m + 0x10, (char *)D_L04_001C3B40[count] + 0x10) > radius * 0.75f) {
            B990Impact impact;
            impact.source = *(void **)(v + 0x74);
            impact.flags = 0x230000;
            impact.unk18 = 2;
            impact.unk19 = 3;
            impact.objectClass = *(unsigned short *)(m + 0xAA);
            impact.strength = 1.0f;
            impact.unk20 = 0x230000;
            angle = mat_fast_helper_a(*(float *)(D_L04_001C3B40[count] + 0x10) - *(float *)(m + 0x10),
                                  *(float *)(D_L04_001C3B40[count] + 0x14) - *(float *)(m + 0x14));
            impact.vector[0] = math_fast_sin_or_cos_a(angle);
            impact.vector[1] = math_fast_sin_or_cos_b(angle);
            impact.vector[2] = 1.0f;
            impact.vector[3] = 5627.9248046875f;
            QueueMobyImpact(D_L04_001C3B40[count], &impact);
            PlayMobySound(soundId, soundArg, *(void **)(v + 0x74));
        }
    }
    {
    float ray[3][4];
    float range = radius;
    for (side = 0; side < 2; side++) {
        sign = (side & 1) ? 1.0f : -1.0f;
        for (i = 0; i < 5; i++) {
            angle0 = math_fast_float_g(IntToFloat(i) * sign * 0.1396263688802719f);
            angle1 = math_fast_float_g(IntToFloat(i + 1) * sign * 0.1396263688802719f);
            vec_build_spherical_offset(ray[0], range, FastAddRotations(angle0, *(float *)(m + 0xF8)), -*(float *)(m + 0xF4));
            vec_build_spherical_offset(ray[1], range, FastAddRotations(angle1, *(float *)(m + 0xF8)), -*(float *)(m + 0xF4));
            add_vectors(ray[2], ray[0], m + 0x10);
            add_vectors(ray[2], ray[1], m + 0x10);
            if (CollLine(ray[0], ray[1], rayMask, *(void **)(v + 0x74), rayResult)) {
                vec_build_spherical_offset(ray[2], 0.33333334326744f, *(float *)(m + 0xF8), -*(float *)(m + 0xF4));
                part_l04_spawn_burst(&D_L04_001BFAE0, ray[2], sparkKind, sparkArg);
            }
        }
    }
    }
}

/* func_L04_003FBD80 is in the sibling file L04_003C8380-g8.c (it stores through $gp). */

/* func_L04_003FBEF8 is in L04_003C8380-dome.c (its file has -g). */

typedef struct {
    unsigned char pad0[0x74];
    unsigned char active;
    unsigned char pad75[0x88 - 0x75];
    void *owner;
} L04_C678Slot;
typedef int L04_C678Quad __attribute__((mode(TI)));

typedef struct {
    unsigned char pad0[0x74];
    unsigned char *owner;
    int timer;
    float age;
} L04_C678Vars;

extern int math_fast_float_d(void *);
extern int FloatToInt(float);
extern void moby_mark_spawned(void *);
extern float StepAngleTowardTarget(void *, int, float, float);
extern void snd_stop_voice(int);
extern void gfx_add_draw_callback_second(void *, void *);
extern void moby_damage_in_firing_cone(unsigned char *, void *);
extern void DrawDomeEffect(void);
extern unsigned char g_sound_state[];
extern int D_L04_001B0488 __attribute__((sda));

/* Keeps the blast effect on its owner and damages nearby objects each frame until its short timer runs out. */
void blast_effect_update(unsigned char *effect)
{
    L04_C678Vars *vars = *(L04_C678Vars **)(effect + 0x68);
    int sound_slot;
    L04_C678Slot *sound_record;

    *(L04_C678Quad *)(effect + 0x10) = *(L04_C678Quad *)(vars->owner + 0x10);
    StepAngleTowardTarget(effect + 0xF8, 0, *(float *)(vars->owner + 0xF8), 0.026179943f);
    vars->age = vars->age + 1.0f;
    if (vars->timer != 0 && math_fast_float_d(&vars->timer) != 0) {
        sound_slot = D_L04_001B0488;
        if (sound_slot != -1) {
            sound_record = (L04_C678Slot *)(g_sound_state + sound_slot * 0x70);
            if (sound_record->owner == vars->owner && sound_record->active != 0) {
                snd_stop_voice(sound_slot);
            }
        }
        D_L04_001B0488 = -1;
        moby_mark_spawned(effect);
        return;
    }
    if (30.0f < vars->age && vars->timer == 0) {
        vars->timer = FloatToInt(15.0f);
    } else {
        moby_damage_in_firing_cone(effect, vars);
    }
    gfx_add_draw_callback_second(DrawDomeEffect, effect);
}

/* Creates a new moby of the given class at the parent's position and turning, sized from its class scale (without the extra flag). */
void *moby_create_at_parent_pose(unsigned char *parent, void *class_id, float scale_factor) {
    unsigned char *child = CreateMoby(class_id);

    if (child != 0) {
        child[0x30] = 0xFF;
        *(unsigned short *)(child + 0x32) = 0xFF;
        child[0x31] = 1;
        child[0x20] = 0;
        *(float *)(child + 0x2C) = *(float *)(*(unsigned char **)(child + 0x24) + 0x24) * scale_factor;
        *(Q16_B0e5d8f83 *)(child + 0x10) = *(Q16_B0e5d8f83 *)(parent + 0x10);
        *(Q16_B0e5d8f83 *)(child + 0xF0) = *(Q16_B0e5d8f83 *)(parent + 0xF0);
        func_002A0F48(child);
    }
    return child;
}

/* func_L04_00400AB0 and func_L04_00400D48 are in L04_003C8380-path-g8.c. */

typedef union { Q16_B0e5d8f83 q; float f[4]; } EffectVector;
typedef struct { EffectVector row[4]; } EffectMatrix4;
extern int GetFirstMobyInGroup(unsigned char **, int, int, int);
extern int GetNextMobyInGroup(unsigned char **, unsigned char *, int, int);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void set_identity_matrix(void *);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern float math_fabs(float);
extern int PlayMobySound(int, int, char *);
extern float ApproachValue(float *, float, float);
extern int FastDecTimer(short *);

/* Blend the nearby pressure-surface contact using a full64-byte inverse matrix. */
/* Checks whether the racer is inside a nearby boost pad area and keeps a boost timer going, easing the boost up or down. */
void racer_update_boost_pad_contact(unsigned char *racer, unsigned char *racer_vars) {
    EffectVector delta;
    EffectMatrix4 inverse;
    unsigned char *pad;
    unsigned char *pad_vars;
    int pad_class;
    float distance;
    if (*(int *)(racer_vars + 0x80) == -1) return;
    GetFirstMobyInGroup(&pad, *(int *)(racer_vars + 0x80), 0, 0);
    while (pad) {
        pad_class = *(short *)(pad + 0xAA);
        if (pad_class == 0x474 /* moby class 1140 */ || pad_class == 0xCEF /* moby class 3311 */) {
            FastVecSub(&delta, pad + 0x10, racer + 0x10);
            distance = FastVecDot(&delta, &delta);
            if (!(20.0f < distance)) {
                set_identity_matrix(&inverse);
                matrix_from_basis_rows(&inverse, pad + 0xC0);
                transform_vector(&delta, &delta, &inverse);
                if (math_fabs(delta.f[0]) < 2.8f && math_fabs(delta.f[1]) < 1.25f && math_fabs(delta.f[2]) < 1.5f) {
                    pad_vars = *(unsigned char **)(pad + 0x68);
                    if (*(short *)(racer_vars + 0x140) == 0 && (*(unsigned char **)(racer_vars + 0x164))[0x20] != 3)
                        PlayMobySound(0, 0, (char *)pad);
                    *(unsigned short *)(racer_vars + 0x140) = *(unsigned short *)pad_vars;
                }
            }
        }
        GetNextMobyInGroup(&pad, pad, 0, 0);
    }
    if (*(short *)(racer_vars + 0x140) != 0) {
        *(short *)(racer_vars + 0x142) = 1;
        ApproachValue((float *)(racer_vars + 0x13C), 0.10000000894069672f, 0.0055555556900799274f);
        if (*(short *)(racer_vars + 0x140)) FastDecTimer((short *)(racer_vars + 0x140));
    } else {
        *(short *)(racer_vars + 0x142) = 0;
        ApproachValue((float *)(racer_vars + 0x13C), 0.0f, 0.002777777845039964f);
    }
}

/* Puts a racer back at its start spot, clears its race state and restarts its route. */
void racer_reset_for_race(unsigned char *racer) {
    unsigned char *vars = *(unsigned char **)(racer + 0x68);
    float offset;
    unsigned char *route;
    vars[0xA2] = vars[0x9C];
    *(Q16_B0e5d8f83 *)(racer+0x10) = *(Q16_B0e5d8f83 *)(vars+0xB0);
    *(Q16_B0e5d8f83 *)(racer+0xF0) = *(Q16_B0e5d8f83 *)(vars+0xC0);
    vars[0xA0] = 0;
    offset = IntToFloat(vars[0xA2]-1);
    *(float *)(vars+0x134) = 0.36916667222976685f - offset * 0.011666666716337204f - (1.0f - (float)*(int *)(vars+0x1A8)*0.1f)*0.03333333507180214f;
    *(int *)(vars+0x138)=0;
    *(int *)(vars+0x158)=0;
    *(int *)(vars+0x13C)=0;
    *(short *)(vars+0x142)=0;
    *(short *)(vars+0x140)=0;
    *(int *)(vars+0x160)=0;
    *(int *)(vars+0x24C)=0;
    if (*(int *)(vars+0x54)==-1) *(char **)(vars+0x110)=g_route_path_table[*(int *)(vars+0x50)];
    else *(char **)(vars+0x110)=g_route_path_table[*(int *)(vars+0x54)];
    *(float *)(vars+0xA8)=5.0f;
    *(float *)(vars+0x1F8)=1.0f;
    *(int *)(vars+0xAC)=0;
    *(int *)(vars+0x114)=0;
    *(int *)(vars+0x118)=0;
    *(int *)(vars+0x128)=0;
    *(int *)(vars+0x12C)=0;
    *(int *)(vars+0x130)=0;
    *(int *)(vars+0x244)=0;
    *(int *)(vars+0x1F4)=0;
    *(int *)(vars+0x144)=0;
    vars[0xA4]=0; vars[0xA5]=0; *(short *)(vars+0xA6)=0;
    *(int *)(vars+0x154)=0;
    *(int *)(vars+0x150)=0;
    *(int *)(vars+0x148)=0;
    *(int *)(vars+0x178)=0;
    *(int *)(vars+0x248)=0;
    *(int *)(vars+0x14C)=0;
    *(int *)(vars+0x15C)=0;
    vars[0xA1]=0;
    qzero(vars+0xD0); qzero(vars+0xE0); qzero(vars+0x100);
    route=*(unsigned char **)(vars+0x110);
    anim_sample_key_track(route,vars+0x114,vars+0x118,vars+0xF0,*(float *)(vars+0xA8),*(float *)(route+0x1C));
    *(float *)(vars+0x16C)=func_002A7878_range(-1.5f,1.5f);
    *(int *)(vars+0x174)=FloatToInt(func_002A7878_range(3.0f,6.0f)*60.0f);
    *(int *)(vars+0x170)=0;
    *(int *)(racer+0x98)=*(int *)(*(unsigned char **)(racer+0x24)+0x10);
    *(unsigned short *)(racer+0x34)=(*(unsigned short *)(racer+0x34)&0xFFBE)|0x1400;
    if (!*(void **)(vars+0x8C)) {
        *(void **)(vars+0x8C)=moby_spawn_at_parent_pose(racer,(void *)MOBY_CLASS_ENEMY_HOVERBIKE_RACER,0.25f);
        if (!*(void **)(vars+0x8C)) goto done;
    }
    {
    unsigned char *child=*(unsigned char **)(vars+0x8C);
    *(unsigned short *)(child+0x34)&=0xFFBE;
    }
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(vars+0x8C)+0x10)=*(Q16_B0e5d8f83 *)(racer+0x10);
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(vars+0x8C)+0xF0)=*(Q16_B0e5d8f83 *)(racer+0xF0);
    (*(unsigned char **)(vars+0x8C))[0x30]=0;
    func_002A05A8(*(void **)(vars+0x8C));
    func_002A0F48(*(void **)(vars+0x8C));
done:
    *(short *)(vars+0x17E)=0; *(short *)(vars+0x17C)=-1;
    *(int *)(vars+0x180)=0; racer[0x20]=2;
    *(int *)(vars+0x120)=-1;
    *(int *)(vars+0x240)=*(int *)(vars+0x1C0)=*(int *)(vars+0x124)=
    *(int *)(vars+0x11C)=*(int *)(vars+0x1AC)=*(int *)(vars+0x1A0)=*(int *)(vars+0x19C)=0;
}

extern float fast_vec_dist(char *arg0, char *arg1);

extern char *D_001FE340[];

/* Works out the length of each leg of the racer's routes. */
void racer_compute_route_lengths(char *racer) {
    char *vars = *(char **)(racer + 0x68);
    char *route;

    {
        int *slot;
        int i;

        slot = (int *)(vars + 0x54);
        for (i = 5; i >= 0; i--, slot++) {
            if (*slot != -1) {
                route = D_001FE340[*slot];
                *(float *)(route + 0x1C) = fast_vec_dist(route + 0x10, route + 0x20);
            }
        }
    }
    {
        int none = -1;
        int *slot;
        int i;

        slot = (int *)(vars + 0x6C);
        for (i = 3; i >= 0; i--, slot++) {
            if (*slot != none) {
                route = D_001FE340[*slot];
                *(float *)(route + 0x1C) = fast_vec_dist(route + 0x10, route + 0x20);
            }
        }
    }
    if (*(int *)(vars + 0x7C) != -1) {
        route = D_001FE340[*(int *)(vars + 0x7C)];
        *(float *)(route + 0x1C) = fast_vec_dist(route + 0x10, route + 0x20);
    }
}
