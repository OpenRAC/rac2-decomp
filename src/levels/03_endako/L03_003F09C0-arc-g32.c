
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int g_arc_effect_count;
extern int g_wall_arc_flag_bit __attribute__((sda));
extern float g_wall_arc_piece_lifetimes[8] SDATA(D_L03_001B1AF0) __attribute__((sda)), g_wall_arc_piece_spin[2] SDATA(D_L03_001B1AE8) __attribute__((sda)), g_wall_arc_piece_speeds[2] SDATA(D_L03_001B1AE0) __attribute__((sda));
extern void *part_find_owned_effect_slot(void *,int,int);
extern void moby_set_state(void *,int,int);
extern void part_explode_object_into_pieces(void *,void *,void *,void *,int,int,int,int,int,u8,void *);
extern char *SpawnExplosion(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern int PlayMobySound(int,int,void *);
extern void SpawnParticleBurst(void *,void *,void *,void *,void *,int,int);
extern void moby_mark_spawned(void *);
extern void vec_local_offset_to_world(void *,void *,float,float,float);
extern u8 *moby_create_configured(void *,void *,int,void *,int,int);
extern void moby_compute_local_point(void *,void *,float,float,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void SpawnTintedEffects(void *,void *,int,int,float,float,float,float,void *,int,int);

/* Per-frame update of a wall arc effect moby: lays down light beams, then smoke and sparks, then waits to be removed. */
void wall_arc_effect_update(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68);
    Vec p,a,b,c,d,f,g;
    switch(moby[0x20]) {
    case 0:
        if(!*(int *)(vars+4)) {
            vec_local_offset_to_world(moby,&a,12,-10,20);
            vec_local_offset_to_world(moby,&b,12,-25,20);
            a.f[3]=0.5f; b.f[3]=1.5f;
            moby_create_configured(&a,&b,0x50285050,moby,5,*(int *)(vars+8)!=0);
            vec_local_offset_to_world(moby,&a,-12,-10,20);
            vec_local_offset_to_world(moby,&b,-12,-25,20);
            moby_create_configured(&a,&b,0x50285050,moby,5,*(int *)(vars+8)!=0);
        }
        if(*(int *)vars) g_arc_effect_count--;
        moby_set_state(moby,1,-1);
        break;
    case 1:
        if(part_find_owned_effect_slot(moby,0x4010000,0) && !*(int *)vars) {
            g_arc_effect_count--; moby_set_state(moby,2,-1);
        }
        moby[0xa8]=255;
        break;
    case 2:
        part_explode_object_into_pieces(moby,g_wall_arc_piece_lifetimes,g_wall_arc_piece_spin,g_wall_arc_piece_speeds,63,0,g_wall_arc_flag_bit,0,65535,255,0);
        vec_local_offset_to_world(moby,&p,0,0,0);
        SpawnExplosion(moby+0x10,0,25,20,20,20,45,1,0.75f,20,1,1,0,0);
        PlayMobySound(0,0,moby);
        moby_compute_local_point(moby,&a,*(float *)(moby+0x2c)*12,*(float *)(moby+0x2c)*-15,*(float *)(moby+0x2c)*20);
        b.f[0]=0; b.f[1]=-0.050000004f; b.f[2]=0;
        matrix_mul_vec3(&b,&b,moby+0xc0);
        SpawnTintedEffects(moby,&a,2,1,0.15f,2,0.5f,1,&b,0x50404040,0);
        moby_compute_local_point(moby,&a,*(float *)(moby+0x2c)*-12,*(float *)(moby+0x2c)*-15,*(float *)(moby+0x2c)*20);
        SpawnTintedEffects(moby,&a,2,1,0.15f,2,0.5f,1,&b,0x50404040,0);
        c.q=0; d.q=0; f.q=0; g.q=0;
        c.f[0]=12; c.f[1]=-12; c.f[2]=20;
        d.f[0]=12; d.f[1]=-12; d.f[2]=20;
        f.f[0]=-1.5f; f.f[1]=-5; f.f[2]=-1.5f;
        g.f[0]=1.5f; g.f[1]=-15; g.f[2]=1.5f;
        SpawnParticleBurst(moby,&c,&d,&f,&g,15,0); c.f[0]=-12;
        d.f[0]=-12;
        SpawnParticleBurst(moby,&c,&d,&f,&g,15,0);
        if(g_wall_arc_flag_bit>=0) {
            *(u16 *)(moby+0x7c)=(1<<g_wall_arc_flag_bit)|0x8000;
            moby_set_state(moby,3,-1);
        } else moby_mark_spawned(moby);
        break;
    }
}
