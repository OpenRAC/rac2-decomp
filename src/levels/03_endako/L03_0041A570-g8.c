#include "common.h"
/* Local vector transfers retain all four components. */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int D_L03_001AEBF8;
extern int D_L03_001B1B50 __attribute__((sda));
extern float D_L03_001B1B30[8] SDATA(D_L03_001B1B30) __attribute__((sda)), D_L03_001B1B28[2] SDATA(D_L03_001B1B28) __attribute__((sda)), D_L03_001B1B20[2] SDATA(D_L03_001B1B20) __attribute__((sda));
extern void FastVecScale(void *,void *,float);
extern void *part_spawn_object_following_effect(void *,void *,int,float,int,int,float,int,int,int);
extern void *part_find_owned_effect_slot(void *,u32,int);
extern void moby_set_state(void *,int,int);
extern void part_explode_object_into_pieces(void *,float *,float *,float *,int,int,int,int,int,u8,void *);
extern void *SpawnExplosion(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern int PlayMobySound(int,int,void *);
extern char *moby_l00_spawn_child(void *,int,int);
extern int flag_set_first_pending(void *);
extern void SpawnParticleBurst(void *,void *,void *,void *,void *,int,int);
extern void lerp_vector(void *,void *,void *,float);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);

typedef struct { int enabled; void *handle; int timer; } DestructionState;

/* Waits for a hit, then explodes with a burst of sparks and debris. */
void UpdateDestructibleObjectEffects(u8 *moby) {
    DestructionState *vars=*(DestructionState **)(moby+0x68);
    Vec pos, a,b,c,d,f,g,h,i,j,k,l,m;
    pos.q=0; pos.f[2]=-8.0f;
    switch(moby[0x20]) {
    case 0:
        FastVecScale(&pos,&pos,*(float *)(moby+0x2c));
        vars->handle=part_spawn_object_following_effect(&pos,moby,0x40202080,*(float *)(moby+0x2c)*4200000.0f,-1,1,1.5f,-1,0,-1);
        moby_set_state(moby,1,-1);
        if (vars->enabled) D_L03_001AEBF8--;
        break;
    case 1:
        if(part_find_owned_effect_slot(moby,0x4010000,0) && !vars->enabled) {
            D_L03_001AEBF8--; moby_set_state(moby,2,-1);
        }
        moby[0xa8]=255;
        break;
    case 2: {
        int skip = D_L03_001B1B50;
        part_explode_object_into_pieces(moby,D_L03_001B1B30,D_L03_001B1B28,D_L03_001B1B20,63,0,skip,0,65535,255,0);
        PlayMobySound(0,0,moby);
        SpawnExplosion(moby+0x10,0,25,20,20,20,45,1,0.75f,20.0f,1,1,0,0);
        { u16 *flags=(u16 *)(moby+0x34);
          *flags |= 0x41;
          vars->timer=30; }
        moby_l00_spawn_child(moby,0xf40,0);
        moby_set_state(moby,3,-1);
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
        if(flag_set_first_pending(moby)) SpawnParticleBurst(moby,&a,&b,&f,&g,40,1);
        lerp_vector(&l,&f,&h,1.0f-(float)vars->timer*0.033333335f);
        lerp_vector(&m,&g,&i,1.0f-(float)vars->timer*0.033333335f);
        lerp_vector(&j,&a,&c,1.0f-(float)vars->timer*0.033333335f);
        lerp_vector(&k,&b,&d,1.0f-(float)vars->timer*0.033333335f);
        SpawnParticleBurst(moby,&j,&k,&l,&m,3,1);
        if(math_fast_float_d(&vars->timer)) moby_mark_spawned(moby);
        break;
    }
}
