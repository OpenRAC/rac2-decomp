#include "include_asm.h"

#include "common.h"
typedef int ProjectileQuad __attribute__((mode(TI)));
typedef union {
    ProjectileQuad q;
    float f[4];
} ProjectileVector;
extern float g_turn_rate __attribute__((sda));
extern float g_turn_l05_limit __attribute__((sda));
extern float g_collision_radius_normal __attribute__((sda));
extern float g_collision_radius_alt __attribute__((sda));
extern char g_projectile_pos_scratch[], g_projectile_target_pos[];
extern u8 *g_particle_params_table[] NOT_SDA;
extern char *moby_get_motion_data(void *);
extern int FloatToInt(float);
extern float FastVecLength(void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecCross(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern int math_fast_float_d(void *);
extern int GetCollHitMaterial(void);
extern int coll_test_point(void *, int, void *, float);
extern int CollLine(void *, void *, int, void *, int);
extern void moby_build_timer_vectors_from_matrix(void *,void *,void *,void *,float,float,float);
extern void func_PAL_L05_003D50B0(void *,void *,void *);
extern int snd_play_from_class_bank(int,int,void *,int);
extern void moby_mark_spawned(void *);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *,float,float,float);
extern char *part_spawn_trailing_spark(void *,void *,int,int,int,int,float);

/* Steers the projectile, tests its lifetime and collisions, and emits its trail. */
void func_PAL_L05_003D4868(char *obj)
{
    ProjectileVector old, temp, delta, velocity;
    char *data = *(char **)(obj+0x68);
    int collision, i;
    float length;
    qcopy(&old, obj + 0x10);
    if (*(char **)(data+0x10) && *(int *)(moby_get_motion_data(*(char **)(data+0x10))+0x110)==1) {
        if (*(int *)(data+0x18)<FloatToInt(1.0f / *(float *)(data+0x1c))-3) {
            length=FastVecLength(data);
            FastVecSub(data,*(char **)(data+0x10)+0x10,obj+0x10);
            vec_scale_to_length(data,data,length);
        } else {
            float turn = g_turn_rate;
            if (*(int *)(data+0x24)) {
                FastVecSub(&temp, *(char **)(data + 0x10) + 0x10, obj + 0x10);
                length = FastVecLength(data);
                vec_scale_to_length(data, &temp, length);
            } else {
                moby_build_timer_vectors_from_matrix(obj + 0x10, data, *(char **)(data + 0x10),
                                   data + 0x14, turn, g_turn_l05_limit, 0.0f);
            }
        }
        temp.q = 0;
        temp.f[2] = 1.0f;
        vec_scale_to_length(obj + 0xC0, data, 1.0f);
        FastVecCross(obj + 0xD0, obj + 0xC0, &temp);
        vec_scale_to_length(obj + 0xD0, obj + 0xD0, 1.0f);
        FastVecCross(obj + 0xE0, obj + 0xD0, obj + 0xC0);
    }
    FastVecAdd(obj+0x10,obj+0x10,data);
    if (*(int *)(data+0x24)) {
        *(float *)(obj+0x2c)+=0.025f;
        if (*(float *)(obj+0x2c)>*(float *)(*(char **)(obj+0x24)+0x24)*0.75f)
            *(float *)(obj+0x2c)=*(float *)(*(char **)(obj+0x24)+0x24)*0.75f;
    } else {
        *(float *)(obj+0x2c)+=0.05f;
        if (*(float *)(obj+0x2c)>*(float *)(*(char **)(obj+0x24)+0x24))
            *(float *)(obj+0x2c)=*(float *)(*(char **)(obj+0x24)+0x24);
    }
    if (math_fast_float_d(data+0x18)) goto destroy;
    {
        if (*(float *)(obj+0x10)<2.0f || *(float *)(obj+0x10)>1021.0f ||
            *(float *)(obj+0x14)<2.0f || *(float *)(obj+0x14)>1021.0f ||
            *(float *)(obj+0x18)<2.0f || *(float *)(obj+0x18)>1021.0f) goto destroy;
        if (GetCollHitMaterial()!=6) {
            collision = 0;
            if (coll_test_point(obj+0x10,16,*(void **)(data+0x20),*(int *)(data+0x24)?g_collision_radius_alt:g_collision_radius_normal)) {
                collision = 1;
                qcopy(obj + 0x10, g_projectile_pos_scratch);
            }
            if (collision || CollLine(&old,obj+0x10,16,*(void **)(data+0x20),0)) goto impact;
        }
    }
    goto emit;
impact:
    {
        func_PAL_L05_003D50B0(obj,data,obj+0x10);
        snd_play_from_class_bank(7,0,obj,0xfbf);
        qcopy(obj+0x10,g_projectile_target_pos);
destroy:
        moby_mark_spawned(obj);
        return;
    }
emit:
    qcopy(&temp,&old);
    FastVecSub(&delta,obj+0x10,&old);
    FastVecScale(&delta,&delta,0.3330000042915344f);
    for (i=3;i>=0;i--) {
        float a, b;
        char *effect;
        FastVecAdd(&temp,&temp,&delta);
        a = math_random_angle();
        b = math_random_angle();
        vec_build_spherical_offset(&velocity,0.015000001f,a,b);
        if (*(int *)(data+0x24)) {
            effect=part_spawn_trailing_spark(&temp,&velocity,0x4fff0040,0x1fff0040,8,1,30000.0f);
            if (effect)
                effect[2] = g_particle_params_table[97][7];
            effect=part_spawn_trailing_spark(&temp,&velocity,0x4fff2040,0x1fff2040,8,1,15000.0f);
        } else {
            effect=part_spawn_trailing_spark(&temp,&velocity,0x4f00ffff,0x1f00ffff,8,1,30000.0f);
            if (effect)
                effect[2] = g_particle_params_table[97][7];
            effect=part_spawn_trailing_spark(&temp,&velocity,0x4f20ffff,0x1f20ffff,8,1,15000.0f);
        }
        if (effect)
            effect[2] = g_particle_params_table[97][7];
    }
}
