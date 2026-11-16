#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void part_explode_object_into_pieces_pal(void *,void *,void *,void *,int,int,int,int,int,unsigned char,int);
extern void moby_mark_spawned(void *);
extern int g_debris_piece_lifetime __attribute__((sda));
extern int g_debris_piece_spread_range __attribute__((sda));
extern int g_debris_piece_speed_range __attribute__((sda));
extern int g_debris_piece_offset __attribute__((sda));
extern int math_random_int_below(int);
extern void moby_compute_local_point(void *, void *, float, float, float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void *part_spawn_spark_moby_pal(void *,void *,void *,int,float,float);

/* Breakable debris: when its effect slot is hit, breaks into pieces and shoots out lower few sparks (PAL: 50 Hz speeds). */
void breakable_l18_debris_update_pal(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68), *hit;
    int spark_count, i;
    float lower[4] __attribute__((aligned(16))), upper[4] __attribute__((aligned(16)));
    float spread[4] __attribute__((aligned(16)));
    switch(moby[0x20]) {
    case 0: moby_set_state(moby,1,-1); break;
    case 1:
        hit=part_find_owned_effect_slot(moby,0x4010000,0);
        if(hit && !*(int *)vars) {
            *(Quad *)spread=0;
            spread[0]=3.0f;
            spread[1]=3.0f;
            *(float *)(hit+0x18)=0.75f;
            FastVecScale(lower,hit+0x10,math_random_float_range(6.0f,8.0f));
            qcopy(upper,lower);
            FastVecSub(lower,lower,spread);
            FastVecAdd(upper,upper,spread);
            part_explode_object_into_pieces_pal(moby,lower,&g_debris_piece_spread_range,&g_debris_piece_speed_range,65535,-1,g_debris_piece_lifetime,9,2,255,0);
            moby_set_state(moby,2,-1);
        }
        moby[0xA8]=255;
        break;
    case 2:
        part_explode_object_into_pieces_pal(moby,&g_debris_piece_offset,&g_debris_piece_spread_range,&g_debris_piece_speed_range,65535,0,g_debris_piece_lifetime,6,61,255,0);
        spark_count=math_random_int_below(5);
        moby_compute_local_point(moby,lower,0.35f,0.0f,1.8f);
        for(i=0;i<spark_count;i++) {
            float x,y;
            upper[0]=math_random_float_range(8.0f,12.0f)*(0.020000001f);
            upper[1]=(2*i-spark_count+1)*(0.080000006f);
            upper[2]=math_random_float_range(0.0f,2.0f)*(0.020000001f);
            matrix_mul_vec3(upper,upper,moby+0xC0);
            x=math_random_float_range(0.75f,1.25f);
            y=math_random_float_range(0.75f,1.25f);
            part_spawn_spark_moby_pal(moby,lower,upper,1,x,y);
        }
        moby_mark_spawned(moby);
        break;
    }
}
