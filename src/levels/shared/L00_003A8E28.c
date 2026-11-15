#include "include_asm.h"
#include "common.h"

typedef struct { char pad[12]; int active; char gap[4]; unsigned char links[8]; } PathSearchNode;

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

extern void func_3251D0();

extern int func_31E7A8();

extern float func_2EE238();

extern void func_2EE178(void *, void *, float);

extern void func_2EE108();

extern void func_2EE138();

extern void func_2EE3D0(void *, void *, float);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


/* func_L00_003A91A0 is defined in L00_003A91A0-rings-g8.c. */


/* The 16-byte value of func_L00_003A98E8's vectors, the projectile's own variables and the game's
 * collision result. */
typedef int ProjectileQuad __attribute__((mode(TI)));
typedef float ProjectilePoint[4] __attribute__((aligned(16)));
typedef union {
    ProjectileQuad q;
    float f[4];
} ProjectileVector;
typedef struct {
    ProjectileVector velocity;
    char *owner;
    short age;
    short mode;
    float life;
    float speed;
    float scale;
    int counter24;
    int counter28;
    short counter2C;
    short counter2E;
    float spinX;
    float spinY;
    float spinZ;
    int pad3C;
    int target;
    int pad44;
    int effect;
    int pad4C;
    ProjectileVector backup;
} ProjectileVars;
typedef struct {
    char pad[0x18];
    char *moby;
    int count;
    ProjectileVector point;
    ProjectileVector pushOut;
    ProjectileVector normal;
} ProjectileCollision;

extern char *CreateMoby(int);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void func_002A0F48(void *);
extern char *g_hero_moby;
extern int CollLine(void *, void *, int, void *, int);
extern void vec_fast_normalize(void *, void *, void *);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float,
                          float, int, float, int, int, int, int, int);
extern void projectile_damage_nearby_on_hit(void *, void *, void *, int);
extern void moby_mark_spawned(void *);
extern int part_alloc_effect_slot(void *, void *, float, float, float);
extern void cam_compute_view_direction(void *, void *, int);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern ProjectileCollision ref_L00_003A98E8_0;
extern int ref_L00_003A98E8_1 MACRO_ADDR;

/* Spawns a projectile moby at `position' and fills in its variables, then tests the first stretch
 * of its flight. A hit on anything but moby classes 0xC87 and 0xECC finishes the projectile on the
 * spot, with a burst of particles, and returns 0. Otherwise it starts the projectile's effect and
 * returns the moby. `mode' follows the FP arguments: the integer and FP banks are assigned apart,
 * so it stays in $a3, and its argument move comes late enough to give it the shorter life. */
char *SpawnProjectile(void *position, void *velocity, char *owner, float speed, float life,
                        float scale, int mode)
{
    ProjectilePoint from;
    ProjectilePoint near;
    ProjectilePoint step;
    ProjectilePoint forward;
    ProjectilePoint projected;
    char *moby = CreateMoby(MOBY_CLASS_HOVERBOMB_PROJECTILE);
    char *hit;
    ProjectileVars *vars;
    float along;

    if (moby != 0) {
        *(unsigned char *)(moby + 0x20) = 0;
        *(unsigned char *)(moby + 0x30) = 255;
        *(short *)(moby + 0x32) = 255;
        *(unsigned char *)(moby + 0x31) = 1;
        vars = *(ProjectileVars **)(moby + 0x68);
        *(float *)(moby + 0xF8) = math_random_angle();
        *(float *)(moby + 0xF4) = math_random_angle();
        *(float *)(moby + 0xF0) = math_random_angle();
        *(float *)(moby + 0x2C) = *(float *)(*(char **)(moby + 0x24) + 0x24) * 0.5f;
        qcopy(moby + 0x10, position);
        vec_scale_to_length(vars, velocity, speed);
        qcopy(&vars->backup, vars);

        vars->owner = owner;
        vars->speed = speed;
        vars->mode = mode;
        vars->life = life;
        vars->scale = scale;
        vars->age = 0;
        vars->counter2E = 0;
        vars->counter24 = 0;
        vars->counter28 = 0;
        vars->counter2C = 12;
        vars->spinX = math_random_signed_float_range(0.00087266473565f, 0.00436332356185f);
        vars->spinY = math_random_signed_float_range(0.00174532947131f, 0.00872664712369f);
        vars->spinZ = math_random_signed_float_range(0.00698131788522f, 0.0349065884948f);
        vars->target = -1;
        func_002A0F48(moby);

        *(ProjectileQuad *)step = 0;
        step[2] = 0.1333333333f;
        *(ProjectileQuad *)near = *(ProjectileQuad *)(g_hero_moby + 0x10);
        near[2] = *(float *)((char *)position + 8);
        if (CollLine(near, position, 0, g_hero_moby, 0)) {
            hit = ref_L00_003A98E8_0.moby;
            if (hit == 0
                || (*(short *)(hit + 0xAA) != 0xC87 && *(short *)(hit + 0xAA) != 0xECC)) {
                qcopy(moby + 0x10, &ref_L00_003A98E8_0.point);
                vec_fast_normalize(step, from, &ref_L00_003A98E8_0.normal);
                vec_scale_to_length(step, step, 0.0333333333f);
                SpawnExplosionEffects(moby, step, 0, 0, 0, 10, 3, 9, 6, 3, 9, 0, -1, 15, 1, 1, -1, 0,
                              0x810001);
                projectile_damage_nearby_on_hit(moby, vars, moby + 0x10, 0);
                moby_mark_spawned(moby);
                return 0;
            }
        }

        vars->effect = part_alloc_effect_slot(moby, 0, 1, 1, 1);
        if (ref_L00_003A98E8_1) {
            cam_compute_view_direction(moby + 0x10, forward, 1);
            along = FastVecDot(forward, vars);
            FastVecScale(projected, forward, along);
            FastVecSub(vars, vars, projected);
            qcopy(&vars->backup, vars);
        }
    }
    return moby;
}

/* func_L00_003AA4C8 is defined in L00_003AA4C8-effects-g.c. */

/* func_L00_003AA708 is defined in L00_003AA708-g.c. */

/* func_L00_003AB388 is defined in L00_003AB388-hit.c. */

/* Applies a state record to a 3D point when the record carries a live tag. */
void vec_steer_toward_target(char *position, char *direction, char *target)
{
    if (target != 0) {
        unsigned char kind = *(unsigned char *)(target + 0x20);

        if (kind != 0xFE)
            if (kind != 0xFD) {
                char forward[16];
                char offset[16];
                char aimed[16];
                float amount;

                func_3251D0(position, forward, 1);
                amount = *(float *)(func_31E7A8(target) + 0x10);
                func_2EE178(offset, forward, amount);
                func_2EE108(aimed, target + 0x10, offset);
                amount = func_2EE238(direction);
                func_2EE138(direction, aimed, position);
                func_2EE3D0(direction, direction, amount);
            }
    }
}

extern int math_random_int_below(int);
extern int FloatToInt(float);
extern char *SpawnSpinningSparkParticle(void *, int, void *, float, float, unsigned int, float, float, int);
extern char D_L00_001A8F20[] __attribute__((section(".sdata")));
/* Sprays a few sparks from a point when a seeker shot hits. */
void seeker_spawn_impact_sparks(void *unused, void *position)
{
    int i, sign;
    char *particle, *payload;
    for (i=1; i>=0; i--) {
        int n=math_random_int_below(16);
        sign=math_random_int_below(2);
        particle=SpawnSpinningSparkParticle(position, sign ? -n : n, D_L00_001A8F20, 0.04f, 1.0f, 0x7f204080, 0.9f, 50000.0f, 1);
        payload=particle+32;
        if(particle) {
            *(short *)(particle+10)=10;
            particle[9]=FloatToInt(4.0f)+64;
            *(int *)(payload+4)=2;
            payload[10]=127;
            payload[11]=*(unsigned char *)(particle+10);
        }
    }
    { int n=16;
    int j;
    for(j=0;j<2;j++) {
        particle=SpawnSpinningSparkParticle(position,n,D_L00_001A8F20,0.02f,1.0f,0x7fffffff,0.97f,15000.0f,1);
        n=-n;
        payload=particle+32;
        if(particle) {
            particle[9]=FloatToInt(4.0f)+64;
            *(short *)(particle+10)=2;
            particle[8]=math_random_int_below(255);
            *(int *)(payload+4)=2;
            payload[10]=127;
            payload[11]=*(unsigned char *)(particle+10);
        }
    }
    }
}


/* func_L00_003AB8B8 is defined in L00_003AB8B8.c. */

/* func_L00_003AB9C0 is defined in L00_003AB9C0-g8.c (the ring index is read through $gp). */

/* func_L00_003ABEC0 is defined in L00_003ABEC0.c. */

/* func_L00_003ACA60 is defined in L00_003ACA60-particles-g.c. */

/* func_L00_003ACC88 is defined in L00_003A8E28-g8.c (the scale is read through $gp). */


/* func_L00_003AD7C8 is defined in L00_003AD7C8.c. */


typedef int TI128_ADA30 __attribute__((mode(TI)));
typedef float VecADA30[4] __attribute__((aligned(16)));

/* The quad record handed to func_00280B90, as in RAC1 sentrybot.c draw_spiderbot_effect_quad. */
typedef struct {
    VecADA30 v[4];
    unsigned int col[4];
    float uv[4][2];
    long a, b, c, d;
} QuadADA30;

/* Per-row lists of linked mobys (eight entries and a null terminator), filled by func_L00_003ADEA0. */
extern char *ref_L00_003ADA30_0[10][9];
extern float ref_L00_003ADA30_1[];
/* The quad's four (u, v) pairs. With sda cc1 costs each address as one instruction, so the u and v
   streams keep separate bases (the assembler still expands each to lui/addiu at -G0). */
extern float ref_L00_003ADA30_2[][2] __attribute__((sda));
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern unsigned long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int);

/* Draws an effect quad (texture 14) from this moby to every active moby of its class linked in its row. */
void DrawMobyLinkQuads(char *moby)
{
    QuadADA30 q;
    VecADA30 left, right, diff, pos, tmp;
    char *vars = *(char **)(moby + 0x68);
    char *other;
    int n, i;

    n = 0;
    while (n < 9 && (other = ref_L00_003ADA30_0[*(short *)(vars + 0x4A)][n++]) != 0) {
        if (*(unsigned char *)(other + 0x20) == 6 && other != moby && other
            && *(short *)(other + 0xAA) == *(short *)(moby + 0xAA)) {
            *(TI128_ADA30 *)pos = *(TI128_ADA30 *)(moby + 0x10);
            FastVecSub(diff, pos, other + 0x10);
            FastVecSub(left, pos, ref_L00_003ADA30_1);
            FastVecSub(right, other + 0x10, ref_L00_003ADA30_1);
            FastVecCross(left, left, diff);
            vec_scale_to_length(left, left, 0.1f);
            FastVecCross(right, right, diff);
            vec_scale_to_length(right, right, 0.1f);
            q.b = GetEffectTextureDescriptor(14);
            q.c = 0xFF9000000260L;
            q.d = 0x8000000048L;
            q.a = 0;
            q.col[3] = 0x80243278;
            q.col[2] = 0x80243278;
            q.col[1] = 0x80243278;
            q.col[0] = 0x80243278;
            for (i = 0; i < 4; i++) {
                q.uv[i][0] = ref_L00_003ADA30_2[i][0];
                q.uv[i][1] = ref_L00_003ADA30_2[i][1];
            }
            FastVecSub(tmp, pos, left);
            *(TI128_ADA30 *)q.v[0] = *(TI128_ADA30 *)tmp;
            FastVecAdd(tmp, pos, left);
            *(TI128_ADA30 *)q.v[1] = *(TI128_ADA30 *)tmp;
            FastVecSub(tmp, other + 0x10, right);
            *(TI128_ADA30 *)q.v[2] = *(TI128_ADA30 *)tmp;
            FastVecAdd(tmp, other + 0x10, right);
            *(TI128_ADA30 *)q.v[3] = *(TI128_ADA30 *)tmp;
            draw_world_quad(&q, 0, 0);
        }
    }
}

/* func_L00_003ADCD8 is defined in L00_003ADCD8-g8.c. */


/* func_L00_003ADEA0 is defined in L00_003A8E28-g8.c. */

typedef float ArcVector[4] __attribute__((aligned(16)));
typedef int ArcQuad __attribute__((mode(TI)));
typedef struct {
    char pad0[0x80];
    ArcVector pos;
    char pad90[0x80];
    ArcVector displacement;
    char pad120[0x21C];
    char *ground;
    char pad340[0x420];
    float facingX;
    float facingY;
    char pad768[0x1B28];
    char *moby;
    int state;
} ArcHero;
typedef struct {
    char pad[0x18];
    char *hit;
    int count;
    ArcVector point;
    ArcVector unknown30;
    ArcVector normal;
} ArcCollision;
extern ArcHero g_hero_state;
extern int D_L00_001A8F00 MACRO_ADDR;
extern ArcCollision g_collision_result;
extern float g_camera_l00_position[];
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern int moby_get_private_value_2(void *);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern int math_fast_float_d(int *);
extern void gfx_add_draw_callback_first(void *, void *);
extern void gfx_draw_spinning_quad_pair(void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);

/* Steps a thrown object's arc until it lands and records the impact point;
   RAC1's predict_mine_impact (overlays/shared/bolts_and_wrench.c) is the same routine. */
int PredictMineImpact(char *motion, char *object, int mode)
{
    ArcVector position;
    ArcVector velocity;
    ArcVector previous;
    ArcVector probe;
    int timer;
    ArcHero *hero = &g_hero_state;
    int i;
    char *vars;

    if (hero->state == 0x6F)
        return 0;
    if (D_L00_001A8F00 != 0)
        return 0;
    qcopy(previous, object + 0x10);
    if (*(unsigned char *)(object + 0x20) == 1) {
        position[0] = math_fast_sin_or_cos_a(FastAddRotations(-0.36196801f, mat_fast_helper_a(hero->facingX, hero->facingY))) * 0.859039f;
        position[1] = math_fast_sin_or_cos_b(FastAddRotations(-0.36196801f, mat_fast_helper_a(hero->facingX, hero->facingY))) * 0.859039f;
        *(int *)&position[2] = 0;
        FastVecAdd(position, position, hero->pos);
        position[2] = position[2] + 0.49082f;
        qcopy(velocity, motion);
        if (hero->ground != 0 && moby_get_private_value_2(hero->ground) != 0 && mode != 0) {
            FastVecAdd(velocity, velocity, hero->displacement);
        }
        timer = 120;
    } else {
        vars = *(char **)(*(char **)(motion + 0x30) + 0x68);
        qcopy(position, object + 0x10);
        qcopy(velocity, motion);
        {
            short frames = *(short *)(motion + 0x34);
            int flag = *(int *)(vars + 0x50);

            timer = frames;
            if (flag != 0)
                *(short *)(motion + 0x36) = 1;
        }
    }
    {
        ArcHero *player = &g_hero_state;
        char *moby = player->moby;

        *(ArcQuad *)probe = *(ArcQuad *)(moby + 0x10);
        probe[2] = position[2];
        if (CollLine(probe, position, 0x10, moby, 0) != 0) {
            if (GetCollHitMaterial() != 0 && g_collision_result.count > 0) {
                qcopy(motion + 0x10, g_collision_result.point);
            }
        }
    }
    while (math_fast_float_d(&timer) == 0) {
        qcopy(previous, position);
        i = 9;
        do {
            FastVecAdd(position, position, velocity);
            velocity[2] = velocity[2] - 0.0027222224f;
        } while (--i >= 0);
        if (CollLine(previous, position, 0x12, object, 0) == 0)
            continue;
        if (GetCollHitMaterial() == 0 && 0.0f < velocity[2])
            continue;
        if (g_collision_result.count > 0) {
            qcopy(motion + 0x10, g_collision_result.point);
            break;
        }
    }
    if (timer != 0) {
        if (mode == 0) {
            if (g_collision_result.hit == 0)
                return 0;
            if (moby_get_private_value_2(g_collision_result.hit) == 0)
                return 0;
        }
        if (mode != 2 || g_collision_result.hit == 0 || moby_get_private_value_2(g_collision_result.hit) == 0) {
            gfx_add_draw_callback_first(gfx_draw_spinning_quad_pair, object);
        }
        {
            float *camera = g_camera_l00_position;
            char *impact = motion + 0x10;

            *(ArcQuad *)(motion + 0x20) = *(ArcQuad *)g_collision_result.normal;
            FastVecSub(previous, impact, camera);
            FastVecScale(previous, previous, 0.95f);
            FastVecAdd(impact, previous, camera);
        }
        return 1;
    }
    return 0;
}


/* func_L00_003B0A28 is defined in L00_003B0A28-g8.c. */


/* Searches the node adjacency table with a byte-indexed backtracking stack. */
typedef struct {
    char pad0[0xC];
    int used;
    int pad10;
    unsigned char next[8];
} PathNode;

extern PathNode D_L00_0023BB78[];
extern void func_002EDE60(void *dst, int value, int size);
extern void func_002EDEB0(void *dst, void *src, int size);

int path_find_between_nodes(unsigned char from, unsigned char to, unsigned char *out)
{
    unsigned char path[256];
    unsigned char tried[256];
    unsigned char cur;
    unsigned char next;
    unsigned char len;
    int best;
    int done;

    if (D_L00_0023BB78[from].used == 0 || D_L00_0023BB78[to].used == 0)
        return 0;
    func_002EDE60(path, 0, 256);
    len = 0;
    func_002EDE60(tried, 0, 256);
    cur = from;
    done = 0;
    best = 0;
    do {
        while (D_L00_0023BB78[cur].next[tried[cur]] == cur) {
            tried[cur]++;
            if (tried[cur] == 8)
                break;
        }
        if (tried[cur] == 8) {
            if (len == 0) {
                done = 1;
            } else {
                tried[cur] = 0;
                len--;
                cur = path[len];
            }
        } else {
            next = D_L00_0023BB78[cur].next[tried[cur]];
            tried[cur]++;
            if (next == to) {
                if (best < len + 2) {
                    if (out) {
                        out[0] = from;
                        func_002EDE60(out, 0, 256);
                        func_002EDEB0(out + 1, path, len);
                        out[len + 2] = next;
                        out[len + 1] = cur;
                    }
                    best = len + 3;
                }
            } else {
                path[len++] = cur;
                cur = next;
            }
        }
    } while (!done);
    return best;
}



/* func_L00_003B1270 is defined in L00_003A8E28-g8.c. */

/* func_L00_003B14D0 is defined in L00_003A8E28-por.c. */

/* A variadic forwarder whose whole retail body is the register save area the EE compiler
   emits for a variadic function: four named integer arguments consume $a0-$a3, so the
   variadic ones are saved out of $t0-$t3 and $f12/$f18. Nothing else is left of it. */
void stub_empty_variadic(int a0, int a1, int a2, int a3, ...)
{
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void transform_reset_record(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void vec_l00_derive_element_from_neighbours(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

/* func_L00_003B3090 is matched in its own unit, src/levels/shared/L00_003B3090-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */
