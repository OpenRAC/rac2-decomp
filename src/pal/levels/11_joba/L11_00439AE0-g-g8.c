#include "names.h"
/* func_PAL_L11_00439ADC, the PAL copy of func_L11_00434580: the same C, where the spin step 1
 * becomes 1.2f (also the distance test), 0.06666667f becomes 0.080000006f, 1.66666675f becomes
 * 2.0000002f and the particle counts 15, 10, 20 become 12, 8, 17 (the 50 Hz scale of each).
 */
#include "common.h"

typedef int QuadPAL439ADC __attribute__((mode(TI)));
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern float vec_distance_xy(void *,void *);
extern void make_hit_descriptor(void *,void *,int,void *,float);
extern int CollLine(void *,void *,int,void *,void *);
extern int flag_is_third_pending_set(void *);
extern void part_l11_spawn_impact_burst_pal(float *,int);
extern void moby_set_flag_bit(void *,int);
extern void moby_mark_spawned(void *);
extern float math_random_float_range(float,float);
extern int math_random_int_range(int,int);
extern void *part_spawn_ground_effect(void *,int,float,float,unsigned int,int,int,void *,float,int);
extern void gfx_add_draw_callback_third(void *,void *);
extern char g_aim_position[];
extern char g_identity_l11_matrix[16] MACRO_ADDR;
extern unsigned int g_thrown_projectile_spark_color_a __attribute__((sda));
extern unsigned int g_thrown_projectile_spark_color_b __attribute__((sda));
extern unsigned int g_thrown_projectile_spark_color_c __attribute__((sda));
extern unsigned int g_thrown_projectile_spark_color_d __attribute__((sda));
extern void projectile_run_trail_steps(char *);
void func_PAL_L11_00439ADC(char *obj) {
    float vel[4]; char collision[48]; float pos[4],pos2[4];
    char *st=*(char **)(obj+0x68);
    float scale=*(float *)(st+0x3C);
    float *impact;
    *(float *)(st+0x38)+=1;
    if (*(float *)(st+0x38)<25) {
        float size; int sign;
        *(float *)(st+0x34)+=1.2f;
        vec_scale_to_length(st+0x10,st+0x20,*(float *)(st+0x34));
        vec_scale_to_length(vel,st+0x20,0.080000006f);
        make_hit_descriptor(collision,obj,0x10001,vel,scale);
        *(unsigned short *)(collision+0x1A)=*(unsigned short *)(obj+0xAA);
        FastVecAdd(st+0x10,st,st+0x10);
        if(CollLine(st,st+0x10,0,obj,collision)) {
            impact=(float *)g_aim_position;
            *(QuadPAL439ADC *)(st+0x10)=*(QuadPAL439ADC *)impact;
            if(!flag_is_third_pending_set(obj)) {
                part_l11_spawn_impact_burst_pal(impact,6);
                moby_set_flag_bit(obj,1);
            }
            moby_mark_spawned(obj); return;
        }
        size=math_random_float_range(1,4);
        sign=math_random_int_range(25,35); if(!sign) sign--;
        qcopy(pos,st+0x10); pos[2]-=0.1f;
        part_spawn_ground_effect(pos,12,size*0.3f,size,g_thrown_projectile_spark_color_a,0,sign,g_identity_l11_matrix,0.0f,0);
        sign = -sign;
        part_spawn_ground_effect(st,8,size*0.3f,size,g_thrown_projectile_spark_color_b,0,sign,g_identity_l11_matrix,0.0f,0);
        part_spawn_ground_effect(st,8,size*0.04f,size*0.4f,g_thrown_projectile_spark_color_c,1,-sign,g_identity_l11_matrix,0.0f,0);
        gfx_add_draw_callback_third(projectile_run_trail_steps,obj);
        return;
    } else if (*(float *)(st+0x38)>=25 && *(float *)(st+0x38)<34) {
        if(vec_distance_xy(st,st+0x10)>1.2f) {
            float size; int sign;
            *(float *)(st+0x34)+=1.2f;
            vec_scale_to_length(st+0x10,st+0x20,*(float *)(st+0x34));
            vec_scale_to_length(vel,st+0x20,0.080000006f);
            make_hit_descriptor(collision,obj,0x10001,vel,scale);
            *(unsigned short *)(collision+0x1A)=*(unsigned short *)(obj+0xAA);
            FastVecAdd(st+0x10,st,st+0x10);
            if(CollLine(st,st+0x10,0,obj,collision)) {
                impact=(float *)g_aim_position;
            *(QuadPAL439ADC *)(st+0x10)=*(QuadPAL439ADC *)impact;
                if(!flag_is_third_pending_set(obj)) {
                    part_l11_spawn_impact_burst_pal(impact,3);
                    moby_set_flag_bit(obj,1);
                }
                moby_mark_spawned(obj); return;
            }
            vec_scale_to_length(pos,st+0x20,2.0000002f);
            FastVecAdd(st,st,pos);
            size=math_random_float_range(1,4);
            sign=math_random_int_range(25,35); if(!sign) sign--;
            qcopy(pos2,st+0x10); pos2[2]-=0.1f;
            part_spawn_ground_effect(pos2,12,size*0.3f,size,g_thrown_projectile_spark_color_a,0,sign,g_identity_l11_matrix,0.0f,0);
            part_spawn_ground_effect(pos2,17,size*0.4f,size*0.2f,g_thrown_projectile_spark_color_d,1,-sign,g_identity_l11_matrix,0.0f,0);
            gfx_add_draw_callback_third(projectile_run_trail_steps,obj);
            return;

        }
        return;
    }
    moby_mark_spawned(obj);
}
