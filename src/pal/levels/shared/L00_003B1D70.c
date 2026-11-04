/* func_PAL_L00_003B1D70, the PAL copy of func_L00_003AE550: the same C, where 120 becomes 100;
   0.0027222224f becomes 0.00392f. */
#include "include_asm.h"
#include "common.h"

extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);

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
extern ArcHero D_00189E20;
extern int D_L00_001A8F00 MACRO_ADDR;
extern ArcCollision D_L00_001BF200;
extern float D_L00_001B8DC0[];
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002AD0B0(void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern int func_00282948(int *);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L00_003AD7C8(void *);
extern void func_00282D30(void *, void *, float);

/* Steps a thrown object's arc until it lands and records the impact point;
   RAC1's predict_mine_impact (overlays/shared/bolts_and_wrench.c) is the same routine. */
int func_PAL_L00_003B1D70(char *motion, char *object, int mode)
{
    ArcVector position;
    ArcVector velocity;
    ArcVector previous;
    ArcVector probe;
    int timer;
    ArcHero *hero = &D_00189E20;
    int i;
    char *vars;

    if (hero->state == 0x6F)
        return 0;
    if (D_L00_001A8F00 != 0)
        return 0;
    qcopy(previous, object + 0x10);
    if (*(unsigned char *)(object + 0x20) == 1) {
        position[0] = func_00283180(func_00283B98(-0.36196801f, func_00283248(hero->facingX, hero->facingY))) * 0.859039f;
        position[1] = func_00283198(func_00283B98(-0.36196801f, func_00283248(hero->facingX, hero->facingY))) * 0.859039f;
        *(int *)&position[2] = 0;
        func_00282CC0(position, position, hero->pos);
        position[2] = position[2] + 0.49082f;
        qcopy(velocity, motion);
        if (hero->ground != 0 && func_002AD0B0(hero->ground) != 0 && mode != 0) {
            func_00282CC0(velocity, velocity, hero->displacement);
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
        ArcHero *player = &D_00189E20;
        char *moby = player->moby;

        *(ArcQuad *)probe = *(ArcQuad *)(moby + 0x10);
        probe[2] = position[2];
        if (func_002761F8(probe, position, 0x10, moby, 0) != 0) {
            if (func_00278E78() != 0 && D_L00_001BF200.count > 0) {
                qcopy(motion + 0x10, D_L00_001BF200.point);
            }
        }
    }
    while (func_00282948(&timer) == 0) {
        qcopy(previous, position);
        i = 9;
        do {
            func_00282CC0(position, position, velocity);
            velocity[2] = velocity[2] - 0.00392f;
        } while (--i >= 0);
        if (func_002761F8(previous, position, 0x12, object, 0) == 0)
            continue;
        if (func_00278E78() == 0 && 0.0f < velocity[2])
            continue;
        if (D_L00_001BF200.count > 0) {
            qcopy(motion + 0x10, D_L00_001BF200.point);
            break;
        }
    }
    if (timer != 0) {
        if (mode == 0) {
            if (D_L00_001BF200.hit == 0)
                return 0;
            if (func_002AD0B0(D_L00_001BF200.hit) == 0)
                return 0;
        }
        if (mode != 2 || D_L00_001BF200.hit == 0 || func_002AD0B0(D_L00_001BF200.hit) == 0) {
            func_L00_002E6CF0(func_L00_003AD7C8, object);
        }
        {
            float *camera = D_L00_001B8DC0;
            char *impact = motion + 0x10;

            *(ArcQuad *)(motion + 0x20) = *(ArcQuad *)D_L00_001BF200.normal;
            func_00282CF0(previous, impact, camera);
            func_00282D30(previous, previous, 0.95f);
            func_00282CC0(impact, previous, camera);
        }
        return 1;
    }
    return 0;
}
