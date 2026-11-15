#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern float coll_get_ground_distance_below(void *, void *, void *);
extern int moby_get_private_value_2(void *);
extern int IsPointInCuboid(void *, int);
extern int flag_is_third_pending_set(void *);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
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
extern int D_L07_001B0A48_gp[] SDATA(D_L07_001B0A48);
extern float D_L07_001B0A40[] __attribute__((sda));

/* Update the launcher state, dispatch its target effect and emit particles. */
void func_PAL_L07_003E8E10(unsigned char *o)
{
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    int count;
    char *p = *(char **)(o+0x68);
    unsigned char *target;
    float angle, size, speed;
    const float lift = 0.05f;
    const float turn = 0.0003490659f;
    int color, life;
    switch (o[0x20]) {
    case 0:
        D_L07_001BF640.object=0;
        coll_get_ground_distance_below(o+0x10,o,o+0x10);
        {
            float height = *(float *)(o + 0x18);
            height = lift + height;
            *(float *)(o + 0x18) = height;
        }
        *(int *)(p+0x20)=-1;
        if (D_L07_001BF640.object && moby_get_private_value_2(D_L07_001BF640.object))
            *(int *)(p+0x10)=(int)D_L07_001BF640.object;
        moby_set_state(o,1,-1);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position,*(int *)(p+4)) || flag_is_third_pending_set(o)) moby_set_state(o,2,-1);
        break;
    case 2:
        if (flag_set_first_pending(o) && o[0x43]!=1) func_PAL_002A7E68(o,1,0,17);
        if (math_fast_float_d(p+0x14)) {
            target=entity_find_last_idle_member(*(int *)p,&count);
            if (target) {
                *(u128 *)a=0;
                a[2]=0.7f;
                matrix_mul_vec3(a,a,o+0xC0);
                FastVecAdd(a,a,o+0x10);
                if (!coll_test_point(a,0.5f,0,o)) {
                    *(u128 *)b=0;
                    b[2]=0.5f;
                    FastVecAdd(b,b,o+0x10);
                    entity_send_and_shrink(target,o+0x10,b,*(int *)(p+0x10));
                    PlayMobySound(0,0,o);
                    *(int *)(p+0x14)=50;
                }
            } else if (!count) moby_set_state(o,3,-1);
        }
        ApproachValue(p+0x18,1.0f,0.060000002f);
        {
            float delta = D_L07_001B0A50;
            delta = turn * delta;
            *(float *)(p + 0x1C) = FastAddRotations(*(float *)(p + 0x1C), delta);
        }
        gfx_add_draw_callback_first(entity_draw_glow_disc,o);
        if (o[0x31] && !math_random_int_below(5)) {
            qzero_nc(b); qzero_nc(a);
            if (*(void **)(p+0x10)) {
                moby_transform_point_and_rotation_by_parent(o,*(void **)(p+0x10),o+0x10,a,b,a);
                FastVecSub(b,b,o+0x10);
            }
            angle=math_random_angle();
            c[0]=math_fast_sin_or_cos_a(angle)*0.4f;
            c[1]=math_fast_sin_or_cos_b(angle)*0.4f;
            c[2]=0;
            FastVecAdd(c,c,o+0x10);
            size=math_random_float_range(D_L07_001B0A40[0],D_L07_001B0A40[1]);
            color=FastTweenColor(D_L07_001B0A48_gp[0],D_L07_001B0A48[1],math_random_float_range(0,1));
            speed=math_random_float_range(1,2);
            life=((s32)(math_random_int_range(30,60)) * 5 + 2) / 6;
            qcopy(d,b);
            d[2]=speed/IntToFloat(life);
            part_spawn_hero_relative(c,d,color,size,(unsigned char)life,(unsigned char)math_random_int_below(255),0);
        }
        break;
    case 3:
        if (flag_set_first_pending(o) && o[0x43]) func_PAL_002A7E68(o,0,0,17);
        ApproachValue(p+0x18,0,0.060000002f);
        gfx_add_draw_callback_first(entity_draw_glow_disc,o);
        if (o[0x42]==o[0x43] && *(float *)(p+0x18)<=0) *(unsigned short *)(o+0x34)|=2;
        break;
    }
}
