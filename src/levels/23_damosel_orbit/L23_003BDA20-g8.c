#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
/* Retail state update, reconstructed from USA v1.01 level 23. */
#define F32(p,o) (*(float *)((char *)(p)+(o)))
#define I32(p,o) (*(int *)((char *)(p)+(o)))
#define S16(p,o) (*(short *)((char *)(p)+(o)))
#define U8(p,o) (*(unsigned char *)((char *)(p)+(o)))
typedef struct {
    char prefix[0x80]; Vec position;
    char gap90[8]; float angle;
    char gap9c[0x2290-0x9c]; int object;
    char gap2294[0x20]; unsigned char state;
} Hero;
extern Hero g_hero_state;
extern char *g_shot_hero_slot __attribute__((sda)), *g_shot_default_slot __attribute__((sda));
extern int g_shot_hero_voice __attribute__((sda)), g_shot_alt_voice __attribute__((sda));
extern float g_shot_turn_rate_normal __attribute__((sda)), g_shot_turn_rate_alt __attribute__((sda));
extern float g_shot_predict_scale __attribute__((sda)), g_shot_turn_param_a __attribute__((sda));
extern float g_shot_turn_param_b __attribute__((sda)), g_shot_motion_length __attribute__((sda)), g_shot_hit_distance __attribute__((sda));
extern int g_hero_special_mode MACRO_ADDR, g_charged_shot_flag MACRO_ADDR;
typedef struct { int enabled; unsigned int color; unsigned long long command; } ScreenEffect;
extern ScreenEffect g_screen_effect MACRO_ADDR;
extern int g_frame_l23_counter MACRO_ADDR;
typedef struct { float size, secondary, unknown[2]; float position[3], radius; } Effect;
extern Effect g_light_effect_table[];
extern char g_hit_l23_moby_list[], g_zero_l23_vec[] MACRO_ADDR;
extern float g_arena_surface_offset MACRO_ADDR, g_boss_knockback_force MACRO_ADDR;
extern unsigned char *g_spark_color_ptr __attribute__((nosda));
extern float IntToFloat(int);
extern int FloatToInt(float), math_random_int_range(int,int), math_random_int_below(int);
extern float math_random_float_range(float,float), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float), square_root(float);
extern void vec_scale_to_length(void *,void *,float), FastVecScale(void *,void *,float);
extern void add_vectors(void *,void *,void *), FastVecAdd(void *,void *,void *), FastVecSub(void *,void *,void *);
extern void part_spawn_homing_trail(int,void *,void *), part_spawn_glow_record(void *,int,int,int,int,float,float);
extern int gfx_add_point_light(void *,float,float,int);
extern void snd_stop_voice(int), moby_mark_spawned(char *), gfx_free_point_light(int);
extern int snd_start_in_slot(int,int,int);
extern void cam_compute_view_direction(void *,void *,int), vec_negate_and_forward(void *,void *,int);
extern void quaternion_to_rotation_basis(void *,void *), multiply_matrix3x3(void *,void *,void *);
extern float FastVecLength(void *),FastVecDot(void *,void *),fast_vec_dist(void *,void *),gravity_get_center_distance(void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_turn_toward_target(void *,void *,void *,void *,float,float,float,void *,float,void *);
extern void arena_push_point_out(void *,float);
extern int coll_process_hit(void *,int,void *,int,float);
extern void moby_queue_knockback_for_nodes(void *,void *,void *,int,int,int,int,int,float,float,float);
extern char *SpawnExplosion(void *,int,int,int,float,float,int,int,int,int,int,int,int,void *);
extern void *SpawnJointFollowParticle(void *,int,int,int,float);
extern void part_spawn_random_direction_effect(void *,float,float);
/* Same registers as its definition: integers a0-t3 then one stack word, the float in $f12. */
extern void *part_spawn_spark(void *,void *,int,int,float,int,int,int,int,int);
extern char *part_spawn_short_lived(void *,void *,int,void *);
typedef struct { char prefix[0x10]; float inverse; char gap[2]; short kind; int color; } ParticleTail;
/* Updates a charged blast: while charging it gathers sparks and a glow, then it flies forward, leaves trails, and ends on hitting something or leaving the map. */
void UpdateChargedBlast(char *obj) {
    struct { Vec point, velocity, ground, motion, matrix[3], rotation, direction, scratch, intercept, result, predicted; } frame;
    char *ctx = *(char **)(obj+0x68);
    char **slot = &g_shot_default_slot;
    int hit;
    float radius, scale, length, turn;
    if (I32(obj,0xB8)==g_hero_state.object) slot=&g_shot_hero_slot;
    switch (U8(obj,0x20)) {
    case 0: {
        float charge, intensity, size;
        int r, g, b, count;
        if (S16(ctx,0x2E) && (g_hero_state.state==2 || !S16(ctx,0x40))) {
            if (!I32(ctx,0x10) && slot==&g_shot_default_slot) { g_screen_effect.enabled=1; g_screen_effect.color=0xFFFF00; }
            charge=IntToFloat(++I32(ctx,0x10))*0.033333335f;
            if(charge>1.0f) charge=1.0f;
            if(S16(ctx,0x40)) charge *= charge*10.0f;
            else charge *= charge*5.0f;
            { int i; for(i=0;i<FloatToInt(charge);i++) {
                int r, g, b;
                u32 color;
                frame.velocity.q=0;
                frame.velocity.f[0]=math_random_float_range(-1.0f,1.0f);
                frame.velocity.f[1]=math_random_float_range(-1.0f,1.0f);
                frame.velocity.f[2]=math_random_float_range(-1.0f,1.0f);
                frame.point.q=frame.velocity.q;
                if(S16(ctx,0x40)) {r=79;g=175;b=255;} else {r=111;g=31;b=15;}
                g=math_random_int_range(r,g); b=math_random_int_range(r,b);
                if(b>255)b=255; if(g>255)g=255;
                vec_scale_to_length(&frame.point,&frame.point,math_random_float_range(15.0f,30.0f));
                add_vectors(&frame.velocity,&frame.point,obj+0x10);
                color=((u32)g<<8)|0x7F000000;
                part_spawn_homing_trail(((u32)b<<16|color)|r,&frame.point,obj);
            } }
            if(I32(ctx,0x10)<50) {
                int alpha=g_screen_effect.color>>24;
                if(!g_screen_effect.command && alpha==255) alpha=37;
                g_screen_effect.command=0x1F00000042ULL;
                { int previous=alpha; alpha++; if (previous>=36) alpha=37; }
                g_screen_effect.color=(g_screen_effect.color&0xFFFF00)|(alpha<<24);
            } else g_screen_effect.color |= 0xFF000000;
            if(S16(ctx,0x2C)!=-1) {
                Effect *effects=g_light_effect_table; char *lights,*light;
                effects[S16(ctx,0x2C)].position[0]=F32(obj,0x10);
                effects[S16(ctx,0x2C)].position[1]=F32(obj,0x14);
                effects[S16(ctx,0x2C)].position[2]=F32(obj,0x18);
                count=I32(ctx,0x10); if(count>50)count=50; if(count<0)count=0;
                effects[S16(ctx,0x2C)].radius=IntToFloat(count)*0.14f;
                intensity=IntToFloat(I32(ctx,0x10))*0.033333335f; if(intensity>1.0f)intensity=1.0f;
                lights=(char *)effects->position; light=lights+S16(ctx,0x2C)*32;
                r=math_random_int_range(15,47)&255;g=math_random_int_range(47,63)&255;b=math_random_int_range(63,127)&255;
                part_spawn_glow_record(light,r,g,b,20,intensity*840000.0f,0.0f);
                effects[S16(ctx,0x2C)].size=math_random_float_range(effects[S16(ctx,0x2C)].size*0.8f,effects[S16(ctx,0x2C)].radius*2.0f*0.14285715f);
                size=effects[S16(ctx,0x2C)].size;
                {
                    float secondary=effects[S16(ctx,0x2C)].secondary*0.8f;
                    effects[S16(ctx,0x2C)].secondary=math_random_float_range(secondary>size?size:secondary,size);
                }
            } else if(!(g_frame_l23_counter&3)) S16(ctx,0x2C)=gfx_add_point_light(obj+0x10,0.0f,0.0f,0);
        } else {
            g_charged_shot_flag=0; g_screen_effect.enabled=0;I32(ctx,0x10)=0;
            snd_start_in_slot(22,0,0);
            if(S16(ctx,0x40)) { if(g_shot_hero_voice!=-1) {snd_stop_voice(g_shot_hero_voice);g_shot_hero_voice=snd_start_in_slot(21,0,0);} }
            else if(g_shot_alt_voice!=-1) {snd_stop_voice(g_shot_alt_voice);g_shot_alt_voice=snd_start_in_slot(21,0,0);}
            if(!g_hero_special_mode) {
                F32(ctx,0)=math_fast_sin_or_cos_a(g_hero_state.angle)*0.6666667f;
                F32(ctx,4)=math_fast_sin_or_cos_b(g_hero_state.angle)*0.6666667f;F32(ctx,8)=0.0f;U8(obj,0x20)=1;
            } else {FastVecScale(ctx,obj+0xC0,2.0f);U8(obj,0x20)=1;}
            I32(ctx,0x14)=0;
        }
    } break;
    case 1: {
        radius=IntToFloat(I32(ctx,0x14))*0.33333334f+1.3f;
        I32(ctx,0x14)++;scale=radius+3.5f;radius*=0.5f;
        cam_compute_view_direction(obj+0x10,&frame.ground,1);
        if (S16(ctx,0x40)) vec_scale_to_length(&frame.motion,obj+0xC0,2.0f);
        else vec_scale_to_length(&frame.motion,obj+0xC0,g_shot_motion_length);
        vec_scale_to_length(&frame.direction,&frame.ground,1.0f);
        FastVecCross(&frame.rotation,obj+0xE0,&frame.direction);
        turn=S16(ctx,0x40)?g_shot_turn_rate_alt:g_shot_turn_rate_normal;
        FastVecScale(&frame.rotation,&frame.rotation,turn);
        length=FastVecLength(&frame.rotation);
        frame.rotation.f[3]=-square_root(1.0f-length*length);
        quaternion_to_rotation_basis(&frame.rotation,frame.matrix);
        multiply_matrix3x3(obj+0xC0,frame.matrix,obj+0xC0);
        if(S16(ctx,0x40)) {
            if(fast_vec_dist(&g_hero_state.position,obj+0x10)<g_shot_hit_distance) { I32(ctx,0x44)=0;S16(ctx,0x42)=0; }
        } else {FastVecScale(&frame.motion,ctx+0x50,1.0f);vec_scale_to_length(&frame.scratch,&frame.motion,1.0f);qcopy(obj+0xC0,&frame.scratch);}
        if(I32(ctx,0x44) && S16(ctx,0x40) && S16(ctx,0x42) && I32(ctx,0x14)>=6) {
            FastVecSub(&frame.scratch,obj+0x10,*(char **)(ctx+0x44)+0x10);
            if(FastVecDot(&frame.scratch,&frame.motion)<0.0f) {
                FastVecScale(&frame.predicted,*(char **)(ctx+0x44)+0xE0,g_shot_predict_scale);
                FastVecAdd(&frame.result,*(char **)(ctx+0x44)+0x10,&frame.predicted);
                vec_turn_toward_target(obj+0x10,obj+0xC0,&frame.result,ctx+0x48,g_shot_turn_param_a,g_shot_turn_param_b,0.0f,&frame.ground,0.0f,&frame.intercept);
                vec_scale_to_length(obj+0xC0,obj+0xC0,1.0f);FastVecScale(&frame.motion,obj+0xC0,2.0f);
            }
        }
        *(Quad *)ctx=frame.motion.q;
        if(S16(ctx,0x2C)!=-1) {
            Effect *effects=g_light_effect_table;
            effects[S16(ctx,0x2C)].radius*=0.39999998f;
            if(effects[S16(ctx,0x2C)].radius<0.0001f) {gfx_free_point_light(S16(ctx,0x2C));S16(ctx,0x2C)=-1;}
        }
        if(I32(ctx,0x14)>50 || g_hero_state.state!=2) {
            if(I32(obj,0xB8)==g_hero_state.object) {if(g_shot_hero_voice!=-1){snd_stop_voice(g_shot_hero_voice);g_shot_hero_voice=-1;}}
            else if(g_shot_alt_voice!=-1){snd_stop_voice(g_shot_alt_voice);g_shot_alt_voice=-1;}
            moby_mark_spawned(*slot);*slot=0;return;
        }
        add_vectors(&frame.ground,obj+0x10,ctx);
        if(!S16(ctx,0x40) && gravity_get_center_distance(obj+0x10)-g_arena_surface_offset<1.3f) arena_push_point_out(obj+0x10,1.3f);
        if(F32(obj,0x10)<2.0f || F32(obj,0x10)>1021.0f || F32(obj,0x14)<2.0f || F32(obj,0x14)>1021.0f || F32(obj,0x18)<2.0f || F32(obj,0x18)>1021.0f) {
            if(I32(obj,0xB8)==g_hero_state.object) {if(g_shot_hero_voice!=-1){snd_stop_voice(g_shot_hero_voice);g_shot_hero_voice=-1;}}
            else if(g_shot_alt_voice!=-1){snd_stop_voice(g_shot_alt_voice);g_shot_alt_voice=-1;}
            moby_mark_spawned(*slot);*slot=0;return;
        }
        if(S16(ctx,0x40)) {
            int count,i; float emission; char *particle;
            hit=coll_process_hit(obj+0x10,16,obj,0,radius);
            frame.ground.q=*(Quad *)(obj+0x10);
            moby_queue_knockback_for_nodes(obj,&frame.ground,g_hit_l23_moby_list,hit,0,0x8B0000,2,1,g_boss_knockback_force,1.0f,1.0f);
            if(hit)SpawnExplosion(obj+0x10,0,25,20,1.0f,20.0f,20,20,45,1,1,0,0,0);
            count=50-I32(ctx,0x14);if(count>5)count=5;
            emission=scale*105000.0f;
            { int r=math_random_int_range(63,127),g=math_random_int_range(47,63),b=math_random_int_range(15,47);
            u32 x=(u32)g<<8|0x4F000000; SpawnJointFollowParticle(obj,((u32)r<<16|x)|b,count,-1,emission); }
            part_spawn_random_direction_effect(&frame.point,scale*0.016666668f,(scale+scale)*0.016666668f);
            { int r=math_random_int_range(63,127),g=math_random_int_range(47,63),b=math_random_int_range(15,47); u32 x=(u32)g<<8|0x7F000000;
            part_spawn_spark(obj+0x10,&frame.point,((u32)r<<16|x)|b,0x4F7F4F2F,210000.0f,45,1,*g_spark_color_ptr,-1,0); }
            for(i=5;i>=0;i--) {
                part_spawn_random_direction_effect(&frame.point,scale*0.016666668f,(scale+scale)*0.016666668f);
                part_spawn_random_direction_effect(&frame.velocity,0.0f,scale*0.5f);
                add_vectors(&frame.ground,&frame.velocity,obj+0x10);
                particle=part_spawn_short_lived(&frame.velocity,&frame.point,127,obj);
                if(particle)F32(particle,0xC)=math_random_float_range(6000.0f,32000.0f)*scale*0.4f;
            }
            for(i=0;i<8;i++) {
                particle=part_spawn_short_lived(obj+0x10,g_zero_l23_vec,127,obj);
                if(particle) {
                    ParticleTail *tail=(ParticleTail *)(particle+0x20);
                    if(i==2 && !math_random_int_below(8))F32(particle,0xC)=180000.0f;
                    else F32(particle,0xC)=math_random_float_range(80000.0f,120000.0f);
                    F32(particle,0xC)*=scale;S16(particle,0xA)=2;
                    { int color=0x7F7F7F; float inverse=1.0f/IntToFloat(2); tail->kind=3;tail->color=color;tail->inverse=inverse; }
                }
            }
        } else {
            int count; float emission;
            hit=coll_process_hit(obj+0x10,16,*(void **)(obj+0xB8),0,radius);
            frame.ground.q=*(Quad *)(obj+0x10);
            moby_queue_knockback_for_nodes(obj,&frame.ground,g_hit_l23_moby_list,hit,0,0x8B0007,2,1,g_boss_knockback_force,1.0f,1.0f);
            if(hit)SpawnExplosion(obj+0x10,0,25,20,1.0f,20.0f,20,20,45,1,1,0,0,0);
            count=50-I32(ctx,0x14);if(count>5)count=5;
            emission=scale*105000.0f;
            { int r=math_random_int_range(15,47),g=math_random_int_range(47,63),b=math_random_int_range(63,127);
            u32 x=(u32)g<<8|0x4F000000; SpawnJointFollowParticle(obj,((u32)r<<16|x)|b,count,-1,emission); }
            part_spawn_random_direction_effect(&frame.point,scale*0.016666668f,(scale+scale)*0.016666668f);
            { int r=math_random_int_range(15,47),g=math_random_int_range(31,47),b=math_random_int_range(63,127); u32 x=(u32)g<<8|0x7F000000;
            part_spawn_spark(obj+0x10,&frame.point,((u32)r<<16|x)|b,0x4F1F1F7F,210000.0f,45,1,*g_spark_color_ptr,-1,0); }
        }
    } break;
    default: break;
    }
    if(g_hero_special_mode) {cam_compute_view_direction(obj+0x10,ctx+0x30,0);vec_negate_and_forward(obj+0xC0,ctx+0x30,0);}
    S16(ctx,0x2E)=0;
}
