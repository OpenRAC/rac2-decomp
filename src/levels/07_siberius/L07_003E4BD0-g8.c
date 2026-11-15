#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern float coll_get_ground_distance_below(void *, void *, void *);
extern int moby_get_private_value_2(void *);
extern int IsPointInCuboid(void *, int);
extern int flag_is_third_pending_set(void *);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern void anim_start_blended(void *, int, int, int);
extern int math_fast_float_d(void *);
extern unsigned char *entity_find_last_idle_member(int, int *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int coll_test_point(void *, float, int, void *);
extern void entity_send_and_shrink(void *, void *, void *, int);
extern int PlayMobySound(int, int, void *);
extern float ApproachValue(void *, float, float);
extern float FastAddRotations(float, float);
extern void gfx_add_draw_callback_first(void (*)(char *), void *);
extern void entity_draw_glow_disc(char *);
extern int math_random_int_below(int);
extern void moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_random_float_range(float, float);
extern int FastTweenColor(int, int, float);
extern int math_random_int_range(int, int);
extern float IntToFloat(int);
extern void part_spawn_hero_relative(void *, void *, int, float, int, int, int);
struct Collision1310 { char pad[0x18]; void *object; };
extern struct Collision1310 D_L07_001BF640;
extern char g_hero_position[];
extern float D_L07_001B0A50 __attribute__((sda));
extern int D_L07_001B0A48[] __attribute__((sda));
/* The first color is GP-relative; the second uses the absolute table view. */
extern int D_L07_001B0A48_gp[] SDATA(D_L07_001B0A48);
extern float D_L07_001B0A40[] __attribute__((sda));
/* Update the launcher state, dispatch its target effect and emit particles. */
/* Per-frame update for moby class 3356: it waits, then looks for a group member to send off
   while giving off sparks. */
void entity_sender_update(unsigned char *moby)
{
    float probePos[4] __attribute__((aligned(16)));
    float aimPos[4] __attribute__((aligned(16)));
    float sparkPos[4] __attribute__((aligned(16)));
    float sparkVel[4] __attribute__((aligned(16)));
    int count;
    char *vars = *(char **)(moby+0x68);
    unsigned char *target;
    float angle, size, speed;
    const float lift = 0.05f;
    const float turn = 0.0002908882457f;
    int color, life;
    switch (moby[0x20]) {
    case 0:
        D_L07_001BF640.object=0;
        coll_get_ground_distance_below(moby+0x10,moby,moby+0x10);
        {
            float height = *(float *)(moby + 0x18);
            height = lift + height;
            *(float *)(moby + 0x18) = height;
        }
        *(int *)(vars+0x20)=-1;
        if (D_L07_001BF640.object && moby_get_private_value_2(D_L07_001BF640.object))
            *(int *)(vars+0x10)=(int)D_L07_001BF640.object;
        moby_set_state(moby,1,-1);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position,*(int *)(vars+4)) || flag_is_third_pending_set(moby)) moby_set_state(moby,2,-1);
        break;
    case 2:
        if (flag_set_first_pending(moby) && moby[0x43]!=1) anim_start_blended(moby,1,0,20);
        if (math_fast_float_d(vars+0x14)) {
            target=entity_find_last_idle_member(*(int *)vars,&count);
            if (target) {
                *(u128 *)probePos=0;
                probePos[2]=0.7f;
                matrix_mul_vec3(probePos,probePos,moby+0xC0);
                FastVecAdd(probePos,probePos,moby+0x10);
                if (!coll_test_point(probePos,0.5f,0,moby)) {
                    *(u128 *)aimPos=0;
                    aimPos[2]=0.5f;
                    FastVecAdd(aimPos,aimPos,moby+0x10);
                    entity_send_and_shrink(target,moby+0x10,aimPos,*(int *)(vars+0x10));
                    PlayMobySound(0,0,moby);
                    *(int *)(vars+0x14)=60;
                }
            } else if (!count) moby_set_state(moby,3,-1);
        }
        ApproachValue(vars+0x18,1.0f,0.05000000447f);
        {
            float delta = D_L07_001B0A50;
            delta = turn * delta;
            *(float *)(vars + 0x1C) = FastAddRotations(*(float *)(vars + 0x1C), delta);
        }
        gfx_add_draw_callback_first(entity_draw_glow_disc,moby);
        if (moby[0x31] && !math_random_int_below(5)) {
            qzero_nc(aimPos); qzero_nc(probePos);
            if (*(void **)(vars+0x10)) {
                moby_transform_point_and_rotation_by_parent(moby,*(void **)(vars+0x10),moby+0x10,probePos,aimPos,probePos);
                FastVecSub(aimPos,aimPos,moby+0x10);
            }
            angle=math_random_angle();
            sparkPos[0]=math_fast_sin_or_cos_a(angle)*0.4f;
            sparkPos[1]=math_fast_sin_or_cos_b(angle)*0.4f;
            sparkPos[2]=0;
            FastVecAdd(sparkPos,sparkPos,moby+0x10);
            size=math_random_float_range(D_L07_001B0A40[0],D_L07_001B0A40[1]);
            color=FastTweenColor(D_L07_001B0A48_gp[0],D_L07_001B0A48[1],math_random_float_range(0,1));
            speed=math_random_float_range(1,2);
            life=math_random_int_range(30,60);
            qcopy(sparkVel,aimPos);
            sparkVel[2]=speed/IntToFloat(life);
            part_spawn_hero_relative(sparkPos,sparkVel,color,size,(unsigned char)life,(unsigned char)math_random_int_below(255),0);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby) && moby[0x43]) anim_start_blended(moby,0,0,20);
        ApproachValue(vars+0x18,0,0.05000000447f);
        gfx_add_draw_callback_first(entity_draw_glow_disc,moby);
        if (moby[0x42]==moby[0x43] && *(float *)(vars+0x18)<=0) *(unsigned short *)(moby+0x34)|=2;
        break;
    }
}
