/* func_PAL_L00_003AD088, the PAL copy of func_L00_003A98E8: the same C, where rename func_002ABBB8 becomes func_PAL_002AC718; rename func_L00_003A9798 becomes func_PAL_L00_003ACF38. */
#include "common.h"

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
#endif

/* The 16-byte value of func_PAL_L00_003AD088's vectors, the projectile's own variables and the game's
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
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float,
                          float, int, float, int, int, int, int, int);
extern void func_PAL_L00_003ACF38(void *, void *, void *, int);
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
char *func_PAL_L00_003AD088(void *position, void *velocity, char *owner, float speed, float life,
                        float scale, int mode)
{
    ProjectilePoint from;
    ProjectilePoint near;
    ProjectilePoint step;
    ProjectilePoint forward;
    ProjectilePoint projected;
    char *moby = CreateMoby(0x5D8);
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
        vars->counter2C = 10;
        vars->spinX = math_random_signed_float_range(0.00087266473565f, 0.00436332356185f);
        vars->spinY = math_random_signed_float_range(0.00174532947131f, 0.00872664712369f);
        vars->spinZ = math_random_signed_float_range(0.00698131788522f, 0.0349065884948f);
        vars->target = -1;
        func_002A0F48(moby);

        *(ProjectileQuad *)step = 0;
        step[2] = 0.16000001f;
        *(ProjectileQuad *)near = *(ProjectileQuad *)(g_hero_moby + 0x10);
        near[2] = *(float *)((char *)position + 8);
        if (CollLine(near, position, 0, g_hero_moby, 0)) {
            hit = ref_L00_003A98E8_0.moby;
            if (hit == 0
                || (*(short *)(hit + 0xAA) != 0xC87 && *(short *)(hit + 0xAA) != 0xECC)) {
                qcopy(moby + 0x10, &ref_L00_003A98E8_0.point);
                vec_fast_normalize(step, from, &ref_L00_003A98E8_0.normal);
                vec_scale_to_length(step, step, 0.040000003f);
                func_PAL_002AC718(moby, step, 0, 0, 0, 10, 3, 9, 6, 3, 9, 0, -1, 15, 1, 1, -1, 0,
                              0x810001);
                func_PAL_L00_003ACF38(moby, vars, moby + 0x10, 0);
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
/* func_L00_003AB8B8 is defined in L00_003AB8B8.c. */

/* func_L00_003AB9C0 is defined in L00_003AB9C0-g8.c (the ring index is read through $gp). */

/* func_L00_003ACA60 is defined in L00_003ACA60-particles-g.c. */

/* func_L00_003ACC88 is defined in L00_003A8E28-g8.c (the scale is read through $gp). */

/* func_L00_003AD7C8 is defined in L00_003AD7C8.c. */

/* The quad record handed to func_00280B90, as in RAC1 sentrybot.c draw_spiderbot_effect_quad. */
/* Per-row lists of linked mobys (eight entries and a null terminator), filled by func_L00_003ADEA0. */
/* The quad's four (u, v) pairs. With sda cc1 costs each address as one instruction, so the u and v
   streams keep separate bases (the assembler still expands each to lui/addiu at -G0). */
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
/* Draws an effect quad (texture 14) from this moby to every active moby of its class linked in its row. */
/* func_L00_003ADEA0 is defined in L00_003A8E28-g8.c. */

typedef float ArcVector[4] __attribute__((aligned(16)));
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
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);

/* Steps a thrown object's arc until it lands and records the impact point;
   RAC1's predict_mine_impact (overlays/shared/bolts_and_wrench.c) is the same routine. */
/* func_L00_003B0A28 is defined in L00_003B0A28-g8.c. */

/* Searches the node adjacency table with a byte-indexed backtracking stack. */
typedef struct {
    char pad0[0xC];
    int used;
    int pad10;
    unsigned char next[8];
} PathNode;

extern PathNode D_L00_0023BB78[];
/* func_L00_003B1270 is defined in L00_003A8E28-g8.c. */

/* func_L00_003B14D0 is defined in L00_003A8E28-por.c. */

/* A variadic forwarder whose whole retail body is the register save area the EE compiler
   emits for a variadic function: four named integer arguments consume $a0-$a3, so the
   variadic ones are saved out of $t0-$t3 and $f12/$f18. Nothing else is left of it. */
/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
/* func_L00_003B3090 is matched in its own unit, src/levels/shared/L00_003B3090-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */
