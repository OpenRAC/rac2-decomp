#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int g_arc_effect_count;
extern int g_explode_skip_flag __attribute__((sda));
extern float g_explode_piece_lifetimes[8] SDATA(D_L03_001B1B30) __attribute__((sda)), g_explode_piece_spin[2] SDATA(D_L03_001B1B28) __attribute__((sda)), g_explode_piece_speeds[2] SDATA(D_L03_001B1B20) __attribute__((sda));
extern void FastVecScale(void *,void *,float);
extern void *part_spawn_object_following_effect(void *,void *,int,float,int,int,float,int,int,int);
extern void *part_find_owned_effect_slot(void *,u32,int);
extern void moby_set_state(void *,int,int);
extern void part_explode_object_into_pieces_pal(void *,float *,float *,float *,int,int,int,int,int,u8,void *);
extern void *SpawnExplosion_pal(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern int PlayMobySound(int,int,void *);
extern char *moby_l00_spawn_child(void *,int,int);
extern int flag_set_first_pending(void *);
extern void func_PAL_L03_002EE460(void *,void *,void *,void *,void *,int,int);
extern void lerp_vector(void *,void *,void *,float);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
typedef struct { int enabled; void *handle; int timer; } DestructionState;

void UpdateDestructibleObjectEffects_pal(u8 *e) {
    DestructionState *s=*(DestructionState **)(e+0x68);
    Vec pos, a,b,c,d,f,g,h,i,j,k,l,m;
    pos.q=0; pos.f[2]=-8.0f;
    switch(e[0x20]) {
    case 0:
        FastVecScale(&pos,&pos,*(float *)(e+0x2c));
        s->handle=part_spawn_object_following_effect(&pos,e,0x40202080,*(float *)(e+0x2c)*4200000.0f,-1,1,1.5f,-1,0,-1);
        moby_set_state(e,1,-1);
        if (s->enabled) g_arc_effect_count--;
        break;
    case 1:
        if(part_find_owned_effect_slot(e,0x4010000,0) && !s->enabled) {
            g_arc_effect_count--; moby_set_state(e,2,-1);
        }
        e[0xa8]=255;
        break;
    case 2: {
        int skip = g_explode_skip_flag;
        part_explode_object_into_pieces_pal(e,g_explode_piece_lifetimes,g_explode_piece_spin,g_explode_piece_speeds,63,0,skip,0,65535,255,0);
        PlayMobySound(0,0,e);
        SpawnExplosion_pal(e+0x10,0,25,20,20,20,45,1,0.75f,20.0f,1,1,0,0);
        { u16 *flags=(u16 *)(e+0x34);
          *flags |= 0x41;
          s->timer=25; }
        moby_l00_spawn_child(e,0xf40,0);
        moby_set_state(e,3,-1);
        break;
    }
    case 3:
        a.q=0; b.q=0; c.q=0; d.q=0; f.q=0; g.q=0; h.q=0; i.q=0;
        a.f[0]=-1; a.f[1]=-1; a.f[2]=-7;
        b.f[0]=1; b.f[1]=1; b.f[2]=-5;
        c.f[0]=-3; c.f[1]=-1; c.f[2]=-6.5f;
        d.f[0]=-1; d.f[1]=1; d.f[2]=-4.5f;
        f.f[0]=-5; f.f[1]=-5; f.f[2]=-25;
        g.f[0]=5; g.f[1]=5; g.f[2]=-7;
        h.f[0]=-15; h.f[1]=-5; h.f[2]=-10;
        i.f[0]=-7; i.f[1]=5;
        if(flag_set_first_pending(e)) func_PAL_L03_002EE460(e,&a,&b,&f,&g,40,1);
        lerp_vector(&l,&f,&h,1.0f-(float)s->timer*0.04f);
        lerp_vector(&m,&g,&i,1.0f-(float)s->timer*0.04f);
        lerp_vector(&j,&a,&c,1.0f-(float)s->timer*0.04f);
        lerp_vector(&k,&b,&d,1.0f-(float)s->timer*0.04f);
        func_PAL_L03_002EE460(e,&j,&k,&l,&m,3,1);
        if(math_fast_float_d(&s->timer)) moby_mark_spawned(e);
        break;
    }
}
