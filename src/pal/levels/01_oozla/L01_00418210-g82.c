#include "include_asm.h"

#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef union { BurstQuad q; f32 f[4]; } BurstVec;
extern s32 g_spark_burst_flag_bit __attribute__((sda));
extern u8 g_spark_piece_params_a[8] __attribute__((sda));
extern u8 g_spark_piece_params_b[8] __attribute__((sda));
extern u8 g_spark_piece_params_c[8] __attribute__((sda));
extern void *part_spawn_object_following_effect(void *,void *,s32,s32,s32,s32,s32,s32,f32,f32);
extern void moby_set_state(void *,s32,s32);
extern void *part_find_owned_effect_slot(void *,s32,s32);
extern void part_explode_object_into_pieces_pal(void *,void *,void *,void *,s32,s32,s32,s32,s32,s32,s32);
extern void part_spawn_scaled_bolts_pal(void *,s32,f32);
extern void moby_compute_local_point(void *,void *,f32,f32,f32);
extern char *SpawnExplosion_pal(void *,s32,s32,s32,s32,s32,s32,s32,s32,s32,s32,s32,f32,f32);
extern void SpawnExplosionEffects_pal(void *,void *,void *,f32,f32,s32,s32,s32,f32,f32,f32,f32,s32,f32,s32,s32,s32,s32,s32);
extern void matrix_mul_vec3(void *,void *,void *);
extern void part_spawn_glow_fade_effects_pal(void *,void *,f32,s32,s32,void *,f32,u32,s32,f32,f32);
extern void moby_mark_spawned(void *);

/* Spark burst object: shows sparkle effects, then on a hit explodes into pieces, bolts and sparks (PAL copy). */
void spark_l01_burst_update_pal(void *arg) {
    BurstVec offset, point, lift;
    f32 direction[4] __attribute__((aligned(16)));
    u8 *moby=arg;
    u8 *vars=*(u8 **)(moby+0x68);
    s32 i;
    point.q=0;
    point.f[2]=21.5f * *(f32 *)(moby+0x2C);
    offset.q=point.q;
    switch(moby[0x20]) {
    case 0:
        part_spawn_object_following_effect(&offset,moby,0x28806020,-1,0,-1,0,0x60,409500.0f,0.0f);
        part_spawn_object_following_effect(&offset,moby,0x20806020,-1,1,-1,0,0x60,262500.0f,0.75f);
        moby_set_state(moby,1,-1);
        break;
    case 1:
        if(part_find_owned_effect_slot(moby,0x4010000,0) && !*(s32 *)vars) moby_set_state(moby,2,-1);
        moby[0xA8]=255;
        break;
    case 2:
        part_explode_object_into_pieces_pal(moby,g_spark_piece_params_a,g_spark_piece_params_b,g_spark_piece_params_c,65535,0,g_spark_burst_flag_bit,1,0xC7F,255,0);
        part_spawn_scaled_bolts_pal(moby,3,1.1f);
        lift.q=0; lift.f[2]=0.20000002f;
        moby_compute_local_point(moby,&point,offset.f[0],offset.f[1],offset.f[2]);
        SpawnExplosion_pal(&point,0,2,2,2,2,2,0,1,0,0,0,*(f32 *)(moby+0x2C),20.0f);
        SpawnExplosionEffects_pal(moby,&lift,&point,0,0,20,1,1,0,0,9.0f,0.75f,-1,0,0,0,-1,0,0x810001);
        for(i=0;i<4;i++) {
            direction[0]=(i/2*2-1)*(0.040000003f);
            direction[1]=(i%2*2-1)*(0.040000003f);
            direction[2]=0.080000006f;
            matrix_mul_vec3(direction,direction,moby+0xC0);
            part_spawn_glow_fade_effects_pal(moby,&point,0.25f,3,1,direction,5.0f,0x4080FF00,0,0.75f,1.25f);
        }
        if(g_spark_burst_flag_bit>=0) {
            *(u16 *)(moby+0x7C)=(1<<g_spark_burst_flag_bit)|0x8000;
            moby_set_state(moby,3,-1);
        } else moby_mark_spawned(moby);
        break;
    }
}
