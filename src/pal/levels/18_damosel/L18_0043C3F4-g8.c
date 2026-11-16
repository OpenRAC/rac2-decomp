#include "names.h"
/* func_PAL_L18_0043C3F4, the PAL copy of func_L18_00437190: the same C at 50 Hz. The particle lifetime
   120 becomes 100, written in its arm; the tuning counts go through ((x) * 5 + 2) / 6; the speed step
   D_L18_001B1918 is scaled by 1.2f; 0.016666668f becomes 0.020000001f and the spin clamp follows.
   func_002BDCE8 becomes func_PAL_002BE9A8, func_L18_00437BA8 becomes func_PAL_L18_0043CE90 and
   func_002ABBB8 becomes func_PAL_002AC718. */
#include "common.h"
#define H(p,o) (*(short *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern int flag_set_first_pending(void *);
extern int PlayMobySound(int,int,void *);
extern void FastVecAdd(char *,char *,char *);
extern void moby_set_state(void *,int,int);
extern int FastDecTimer(void *);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern float math_random_float_range(float,float);
extern void LerpVector4(void *,void *,void *,float);
typedef struct { int pad0; int flags; u8 pad8[2]; u8 alpha; u8 lifetime; } ParticleRender;
typedef struct { u8 pad0[0xa]; s16 lifetime; u8 padc[0x14]; ParticleRender render; } Particle;
extern Particle *func_PAL_002BE9A8(void *,float,float,float,float,int,void *,int,int);
extern int CollLine(void *,void *,int,void *,int);
extern int coll_test_point(void *,int,void *,float);
extern void vec_scale_to_length(char *,char *,float);
extern void vec_fast_normalize(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern float vec_length_xy(void *);
extern void vec_fast_normalize_helper(void *,void *,float);
extern int FloatToInt(float);
extern int math_fast_float_d(void *);
extern void func_PAL_L18_0043CE90(void *,int);
extern void SpawnExplosionEffects_pal(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void moby_mark_spawned(void *);
extern int coll_process_hit(void *,int,void *,int,float);
extern void part_queue_impact_effect(void *,void *,int,void *,void *,float);
extern float FastAddRotations(float,float);
typedef int TI128 __attribute__((mode(TI)));
extern TI128 g_default_quad MACRO_ADDR;
extern u8 g_hero_ground_hit[];
extern u8 g_hero_state[];
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u8 *p[0x980]; TI128 q[0x260]; } HeroView;
typedef union { u8 b[0x100]; s16 h[0x80]; u16 u[0x80]; s32 i[0x40]; float f[0x40]; u8 *p[0x40]; TI128 q[0x10]; } ObjectView;
#define OBJ ((ObjectView *)obj)
#define STATE ((ObjectView *)st)
typedef union { u8 b[0x60]; float f[0x18]; u8 *p[0x18]; TI128 q[6]; } CollisionView;
extern u8 *g_nearby_hit_targets[];
extern float g_fireball_delta_vector[3];
extern float g_fireball_collision_radius __attribute__((sda));
extern int g_fireball_lifetime_frames __attribute__((sda));
extern int g_fireball_spark_count __attribute__((sda));
extern int g_fireball_spark_lifetime __attribute__((sda));
extern float g_fireball_spark_speed_min __attribute__((sda));
extern float g_fireball_spark_speed_max __attribute__((sda));
extern float g_fireball_spark_size __attribute__((sda));
extern float g_fireball_min_speed __attribute__((sda));
extern float g_fireball_speed_scale __attribute__((sda));
extern float g_fireball_damping __attribute__((sda));
extern float g_fireball_normalize_speed __attribute__((sda));
extern int g_fireball_grow_frames __attribute__((sda));
extern int g_fireball_fade_frames __attribute__((sda));
extern float g_fireball_radius __attribute__((sda));
extern int g_fireball_ring_spark_count __attribute__((sda));
static inline int same_group(u8 *st) {
    int valid=0;
    if(((CollisionView *)g_hero_ground_hit)->p[6] && STATE->p[0x9]) valid=H(((CollisionView *)g_hero_ground_hit)->p[6],0xaa)==H(STATE->p[0x9],0xaa);
    return valid;
}
static inline float clamp_speed(float speed, float low, float high) {
    if(speed<low) speed=low;
    if(speed>high) speed=high;
    return speed;
}
void func_PAL_L18_0043C3F4(u8 *obj) {
    float delta[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    u8 *st=OBJ->p[0x1a], *p, *other;
    u8 **targets;
    int i, n, mode=obj[0x20], amount, r,g,b;
    float t, x, minimum;
    switch(mode) {
    case 0: case 1:
        if(flag_set_first_pending(obj)) PlayMobySound(1,0,obj);
        FastVecAdd((char *)delta,(char *)obj+0x10,(char *)st+0x10);
        STATE->f[0x6]-=STATE->f[0x7];
        if(obj[0x20]==1 && STATE->f[0x6]<0) moby_set_state(obj,0,-1);
        FastDecTimer(st+0x28);
        {s16 life=STATE->h[0x14];
        if(life) {
            for(i=0;i<g_fireball_spark_count;i++) {
                float ratio, denominator, random, fraction;
                Particle *spark;
                *(TI128 *)temp=*(TI128 *)(obj+0x10);
                fraction=(float)i; fraction*=0.3333f;
                LerpVector4(pos,temp,delta,fraction);
                amount=math_random_int_below(6);
                if(math_random_int_below(2)) amount=-amount;
                denominator=IntToFloat((g_fireball_lifetime_frames*5+2)/6);
                ratio=(float)STATE->h[0x14]; ratio/=denominator;
                random=math_random_float_range(0.9f,1.0f);
                spark=func_PAL_002BE9A8(pos,g_fireball_spark_size,1,1,random*(g_fireball_spark_speed_min+(g_fireball_spark_speed_max-g_fireball_spark_speed_min)*ratio),amount,&g_default_quad,g_fireball_spark_lifetime,0);
                if(spark) { ParticleRender *particle; spark->lifetime=100; particle=&spark->render; particle->flags=2; particle->alpha=127; particle->lifetime=*(u8 *)&spark->lifetime; }
            }
        }
        }
        if(CollLine(obj+0x10,delta,0,obj,0) && !same_group(st)) qcopy(obj+0x10,&((CollisionView *)g_hero_ground_hit)->q[2]);
        else qcopy(obj+0x10,delta);
        if(coll_test_point(obj+0x10,0,obj,g_fireball_collision_radius) && (obj[0x20]==0 || OBJ->f[0x6]-((CollisionView *)g_hero_ground_hit)->f[10]<0)) {
            if(!same_group(st)) {
                vec_scale_to_length((char *)pos,(char *)(u8 *)&((CollisionView *)g_hero_ground_hit)->q[4],g_fireball_collision_radius);
                FastVecAdd((char *)obj+0x10,(char *)(u8 *)&((CollisionView *)g_hero_ground_hit)->q[2],(char *)pos);
                vec_fast_normalize(st+0x10,st+0x10,(u8 *)&((CollisionView *)g_hero_ground_hit)->q[4]);
                PlayMobySound(1,0,obj);
                if(obj[0x20]!=0) goto bounce_done;
                moby_set_state(obj,1,-1);
                if(++STATE->h[0x15]==1) {
                    vec_fast_normalize_helper(st+0x10,st+0x10,g_fireball_normalize_speed*0.020000001f);
                    STATE->f[0x6]*=g_fireball_damping;
                } else {
                    FastVecScale(temp,st+0x10,g_fireball_damping);
                    if(vec_length_xy(temp)<g_fireball_min_speed*0.020000001f) {
                        vec_fast_normalize_helper(st+0x10,st+0x10,g_fireball_min_speed*0.020000001f);
                        STATE->f[0x6]*=g_fireball_damping;
                    } else qcopy(st+0x10,temp);
                }
bounce_done:
                if(STATE->h[0x15]>=4) {
                    moby_set_state(obj,2,-1); STATE->f[0x6]=0;
                    STATE->f[0x7]=vec_length_xy(st+0x10);
                    STATE->f[0x7]*=g_fireball_damping;
                    minimum=g_fireball_min_speed*0.020000001f;
                    if(STATE->f[0x7]<minimum) STATE->f[0x7]=minimum;
                    vec_scale_to_length((char *)st+0x10,(char *)st+0x10,STATE->f[0x7]);
                    STATE->f[0xb]=1.0f/IntToFloat(STATE->i[0x8]);
                }
            }
        }
        break;
    case 2:
        { typedef struct { float a,b,c; } Triple; *(Triple *)delta=*(Triple *)g_fireball_delta_vector; }
        t=(float)STATE->i[0x8]*STATE->f[0xb];
        r=FloatToInt((delta[0]-255.0f)*t+255.0f);
        g=FloatToInt(delta[1]*t); b=FloatToInt(delta[2]*t);
        {u32 color=(u32)b<<16; color|=0xff000000; color|=g<<8; color|=r; OBJ->i[0x1e]=color;}
        {float speed=STATE->f[0x7]*((g_fireball_speed_scale-1.0f)*1.2f+1.0f);
        minimum=g_fireball_min_speed*0.020000001f;
        STATE->f[0x7]=speed;
        if(speed<minimum) STATE->f[0x7]=minimum;}
        vec_scale_to_length((char *)st+0x10,(char *)st+0x10,STATE->f[0x7]);
        FastVecAdd((char *)obj+0x10,(char *)obj+0x10,(char *)st+0x10);
        if(math_fast_float_d(st+0x20)) moby_set_state(obj,3,-1);
        break;
    case 3:
        if(flag_set_first_pending(obj)) {
            func_PAL_L18_0043CE90(obj+0x10,g_fireball_ring_spark_count);
            SpawnExplosionEffects_pal(obj,st+0x10,obj+0x10,0,0,3,3,5,1,0.2f,9,1,-1,0,1,1,-1,0,0x810001);
            PlayMobySound(0,0,obj);
        }
        else {
        if(((g_fireball_grow_frames+g_fireball_fade_frames)*5+2)/6<OBJ->u[0x4b]) {moby_mark_spawned(obj);return;}
        x=g_fireball_radius;
        if(OBJ->u[0x4b]<(g_fireball_grow_frames*5+2)/6) x=x*(float)OBJ->u[0x4b]/(float)((g_fireball_grow_frames*5+2)/6);
        n=coll_process_hit(obj+0x10,0,obj,0,x);
        if(!n) break;
        if(n>0) {
        int remaining;
        targets=g_nearby_hit_targets;
        remaining=n;
        do {
            u8 *other=*targets;
            int valid=0;
            if(other==((HeroView *)g_hero_state)->p[0x2290/4]) {qcopy(delta,&((HeroView *)g_hero_state)->q[8]); if(((HeroView *)g_hero_state)->i[0x340/4]) valid=1;}
            else {qcopy(delta,other+0x10); if(U(other,0x34)&0x20) {u8 *owner=P(P(other,0x68),0x18);if(owner) {if(H(owner,0xc0)) valid=1;}}}
            if(valid) part_queue_impact_effect(other,obj,0x10001,other+0x10,&g_default_quad,STATE->f[0xc]);
            targets++;
        } while(--remaining);
        }
        }
        break;
    }
    if(OBJ->u[0x4b]<65535) OBJ->u[0x4b]++;
    {
        float speed, angle;
        if(obj[0x20]<2) speed=vec_length_xy(st+0x10);
        else if(obj[0x20]==2) speed=STATE->f[0x7];
        else return;
        speed=clamp_speed(speed,0.004f,0.120000005f);
        speed-=0.004f;
        angle=0.116000004f;
        angle=speed/angle;
        angle*=7.0f;
        angle+=1.0f;
        angle*=0.017453294f;
        OBJ->f[0x3d]=FastAddRotations(angle,OBJ->f[0x3d]);
    }
    if(OBJ->f[0x4]<2 || OBJ->f[0x4]>1021 || OBJ->f[0x5]<2 || OBJ->f[0x5]>1021 || OBJ->f[0x6]<2 || OBJ->f[0x6]>1021)moby_mark_spawned(obj);
}
