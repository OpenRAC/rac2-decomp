#include "names.h"
/* func_PAL_L00_003B1D70, the PAL copy of func_L00_003AE550: the same C, where 120 becomes 100;
   0.0027222224f becomes 0.00392f. */
#include "include_asm.h"
#include "common.h"

extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);

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
extern int moby_get_private_value_2(void *);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern int math_fast_float_d(int *);
extern void gfx_add_draw_callback_first(void *, void *);
extern void gfx_draw_spinning_quad_pair(void *);
extern void FastVecScale(void *, void *, float);

/* Steps a thrown object's arc until it lands and records the impact point;
   RAC1's predict_mine_impact (overlays/shared/bolts_and_wrench.c) is the same routine. */
int func_PAL_L00_003B1D70(char *motion, char *object, int mode)
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
        timer = 100;
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
            velocity[2] = velocity[2] - 0.00392f;
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
