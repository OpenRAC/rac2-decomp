#include "common.h"
typedef union { unsigned int q __attribute__((mode(TI))); struct { float x,y,z,w; } f; } V413;
typedef struct {
    V413 velocity;
    int charge, age;
    char pad18[0x14];
    short light, triggered;
    V413 orientation;
    short kind, pad42;
    int override;
    char pad48[8];
    V413 direction;
} State413;
typedef struct { float inner, outer; char pad[8]; V413 position; } Light413;
typedef struct { char pad[0x98]; float angle; char gap[0x21F4]; int owner; char gap2[0x20]; unsigned char mode; } Player413;
extern Player413 g_hero_state;
extern int g_homing_handle_hero __attribute__((sda)), g_homing_handle_other __attribute__((sda));
extern int g_homing_voice_player __attribute__((sda)), g_homing_voice_other __attribute__((sda));
extern float g_homing_factor_normal __attribute__((sda)), g_homing_factor_charged __attribute__((sda));
extern int g_hero_flag_a MACRO_ADDR;
typedef struct { int enabled; unsigned int color; unsigned long long counter; } ChargeFx413;
extern ChargeFx413 g_charged_shot_screen_effect[] __attribute__((sda));
extern int g_charged_shot_active;
extern int g_frame_l22_counter;
extern float g_homing_shot_knockback_value;
extern char g_hit_l22_moby_list[];
/* sda: one la macro per use, so its address is not kept across the loop. */
extern char g_effect_position_params[] __attribute__((sda));
/* Unsized view: read through a separate lui rather than the small-data lw macro. */
extern unsigned char *g_spark_texture[];
extern Light413 g_effect_l22_light_table[];
extern float IntToFloat(int), math_random_float_range(float,float), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern int FloatToInt(float), math_random_int_range(int,int), math_random_int_below(int);
extern void vec_scale_to_length(void*,void*,float), add_vectors(void*,void*,void*);
extern void part_spawn_homing_trail(int,void*,void*);
extern void part_spawn_glow_record(void*,int,int,int,int,float,float);
extern short gfx_add_point_light(void*,int,float,float);
extern int snd_start_in_slot(int,int,int);
extern void snd_stop_voice(int), gfx_free_point_light(int), moby_mark_spawned(int);
extern void FastVecScale(void*,void*,float),cam_compute_view_direction(void*,void*,int),vec_negate_and_forward(void*,void*,int);
extern void FastVecCross(void*,void*,void*),quaternion_to_rotation_basis(void*,void*),multiply_matrix3x3(void*,void*,void*);
extern float FastVecLength(void*),square_root(float);
extern int coll_process_hit(void*,int,void*,int,float);
extern void moby_queue_knockback_for_nodes(void*,void*,void*,int,int,int,int,int,float,float,float);
extern char *SpawnExplosion(void*,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern void part_spawn_random_direction_effect(void*,float,float);
extern void *SpawnJointFollowParticle(void*,int,int,int,float);
extern void *part_spawn_spark(void*,void*,int,int,int,int,int,int,int,float);
extern char *part_spawn_short_lived(void*,void*,int,void*);

/* Updates the charge-up shot: while charged it gathers sparks and a glow, then fires and flies forward, hitting things and spawning light and sparkles until it expires. */
void UpdateChargedProjectile(unsigned char *obj)
{
    struct { V413 velocity, random, position, scaled, matrix[3], rotation, normalized, temp; } frame;
    State413 *state;
    int *handle = &g_homing_handle_other;
    int i, j, hit, color;
    float radius, spread, fade, factor;
    char *particle, *sub;
    if (*(int *)(obj+0xB8) == g_hero_state.owner) handle=&g_homing_handle_hero;
    state = *(State413 **)(obj+0x68);
    switch (obj[0x20]) {
    case 0: {
        float charge;
        if (state->triggered && (g_hero_state.mode==2 || !state->kind)) {
            if (!state->charge && handle==&g_homing_handle_other) {
                g_charged_shot_screen_effect[0].enabled=1;
                g_charged_shot_screen_effect[0].color=0xFFFF00;
            }
            charge=IntToFloat(++state->charge)*0.033333335f;
            if (charge>1.0f) charge=1.0f;
            charge *= charge * (state->kind ? 10.0f : 5.0f);
            for (j=0;j<FloatToInt(charge);j++) {
                int loop_r,loop_g,loop_b;
                frame.random.q=0;
                frame.random.f.x=math_random_float_range(-1.0f,1.0f);
                frame.random.f.y=math_random_float_range(-1.0f,1.0f);
                frame.random.f.z=math_random_float_range(-1.0f,1.0f);
                frame.velocity.q=frame.random.q;
                if (state->kind) { loop_r=0x4F;loop_g=0xAF;loop_b=0xFF; }
                else { loop_r=0x6F;loop_g=0x1F;loop_b=0xF; }
                loop_g=math_random_int_range(loop_r,loop_g);
                loop_b=math_random_int_range(loop_r,loop_b);
                if (loop_b>255) loop_b=255;
                if (loop_g>255) loop_g=255;
                vec_scale_to_length(&frame.velocity,&frame.velocity,math_random_float_range(15.0f,30.0f));
                add_vectors(&frame.random,&frame.velocity,obj+0x10);
                {
                    int high=(loop_g<<8)|0x7F000000;
                    part_spawn_homing_trail((loop_b<<16)|high|loop_r,&frame.velocity,obj);
                }
            }
            if (state->charge<50) {
                int alpha=g_charged_shot_screen_effect[0].color>>24;
                if (!g_charged_shot_screen_effect[0].counter && alpha==255) alpha=37;
                if (alpha<36) alpha++; else alpha=37;
                g_charged_shot_screen_effect[0].counter=0x1F00000042ULL;
                g_charged_shot_screen_effect[0].color=(g_charged_shot_screen_effect[0].color&0xFFFF00)|(alpha<<24);
            } else g_charged_shot_screen_effect[0].color |= 0xFF000000;
            if (state->light != -1) {
                float light_charge;
                float inner, outer;
                g_effect_l22_light_table[state->light].position.f.x=*(float *)(obj+0x10);
                g_effect_l22_light_table[state->light].position.f.y=*(float *)(obj+0x14);
                g_effect_l22_light_table[state->light].position.f.z=*(float *)(obj+0x18);
                { int n=state->charge;
                if (n>50) n=50;
                if (n<0) n=0;
                g_effect_l22_light_table[state->light].position.f.w=IntToFloat(n)*0.14f; }
                light_charge=IntToFloat(state->charge)*0.033333335f;
                if (light_charge>1) light_charge=1;
                part_spawn_glow_record(&g_effect_l22_light_table[state->light].position,
                    math_random_int_range(15,47)&255,math_random_int_range(47,63)&255,math_random_int_range(63,127)&255,20,light_charge*840000.0f,0.0f);
                g_effect_l22_light_table[state->light].inner=math_random_float_range(g_effect_l22_light_table[state->light].inner*0.8f,
                    (g_effect_l22_light_table[state->light].position.f.w+g_effect_l22_light_table[state->light].position.f.w)*0.14285715f);
                outer=g_effect_l22_light_table[state->light].outer*0.8f;
                inner=g_effect_l22_light_table[state->light].inner;
                g_effect_l22_light_table[state->light].outer=math_random_float_range(inner < outer ? inner : outer,inner);
            } else if (!(g_frame_l22_counter&3)) {
                state->light=gfx_add_point_light(obj+0x10,0,0.0f,0.0f);
            }
        } else {
            g_charged_shot_active=0;
            g_charged_shot_screen_effect[0].enabled=0;
            state->charge=0;
            snd_start_in_slot(22,0,0);
            if (state->kind) {
                if (g_homing_voice_player != -1) {
                    snd_stop_voice(g_homing_voice_player);
                    g_homing_voice_player=snd_start_in_slot(21,0,0);
                }
            } else if (g_homing_voice_other != -1) {
                snd_stop_voice(g_homing_voice_other);
                g_homing_voice_other=snd_start_in_slot(21,0,0);
            }
            if (!g_hero_flag_a) {
                state->velocity.f.x=math_fast_sin_or_cos_a(g_hero_state.angle)*0.6666667f;
                state->velocity.f.y=math_fast_sin_or_cos_b(g_hero_state.angle)*0.6666667f;
                state->velocity.f.z=0;
                obj[0x20]=1;
                state->age=0;
            } else {
                FastVecScale(state,obj+0xC0,2.0f);
                obj[0x20]=1;
                state->age=0;
            }
        }
    break;
    }
    case 1: {
        float extra = 3.5f;
        radius=IntToFloat(state->age)*0.33333334f+1.3f;
        ++state->age;
        cam_compute_view_direction(obj+0x10,&frame.position,1);
        spread=radius+extra;
        if (state->kind) vec_scale_to_length(&frame.scaled,obj+0xC0,2.0f);
        else vec_scale_to_length(&frame.scaled,obj+0xC0,extra);
        vec_scale_to_length(&frame.normalized,&frame.position,1.0f);
        FastVecCross(&frame.rotation,obj+0xE0,&frame.normalized);
        if (state->kind) factor=g_homing_factor_charged; else factor=g_homing_factor_normal;
        FastVecScale(&frame.rotation,&frame.rotation,factor);
        fade=FastVecLength(&frame.rotation);
        frame.rotation.f.w=-square_root(1.0f-fade*fade);
        quaternion_to_rotation_basis(&frame.rotation,frame.matrix);
        multiply_matrix3x3(obj+0xC0,frame.matrix,obj+0xC0);
        if (state->override) {
            if (state->kind) FastVecScale(&frame.scaled,&state->direction,0.6666667f);
            else FastVecScale(&frame.scaled,&state->direction,1.0f);
            vec_scale_to_length(&frame.temp,&frame.scaled,1.0f);
            qcopy(obj+0xC0, &frame.temp);
        }
        state->velocity.q=frame.scaled.q;
        if (state->light!=-1) {
            Light413 *lights = g_effect_l22_light_table;
            lights[state->light].position.f.w *= 0.39999998f;
            if (lights[state->light].position.f.w<0.0001f) {
                gfx_free_point_light(state->light);
                state->light=-1;
            }
        }
        if (state->age>=51 || g_hero_state.mode!=2) {
            if (*(int *)(obj+0xB8)==g_hero_state.owner) {
                if(g_homing_voice_player!=-1) {snd_stop_voice(g_homing_voice_player);g_homing_voice_player=-1;}
            } else if(g_homing_voice_other!=-1) {snd_stop_voice(g_homing_voice_other);g_homing_voice_other=-1;}
            moby_mark_spawned(*handle);
            *handle=0;
            return;
        } else {
            add_vectors(&frame.position,obj+0x10,state);
            if (*(float *)(obj+0x10)<2 || *(float *)(obj+0x10)>1021 ||
                *(float *)(obj+0x14)<2 || *(float *)(obj+0x14)>1021 ||
                *(float *)(obj+0x18)<2 || *(float *)(obj+0x18)>1021) {
                if (*(int *)(obj+0xB8)==g_hero_state.owner) {
                    if(g_homing_voice_player!=-1) {snd_stop_voice(g_homing_voice_player);g_homing_voice_player=-1;}
                } else if(g_homing_voice_other!=-1) {snd_stop_voice(g_homing_voice_other);g_homing_voice_other=-1;}
                moby_mark_spawned(*handle);
                *handle=0;
                return;
            } else if (state->kind) {
                hit=coll_process_hit(obj+0x10,16,obj,0,radius);
                frame.position.q=((V413 *)(obj+0x10))->q;
                moby_queue_knockback_for_nodes(obj,&frame.position,g_hit_l22_moby_list,hit,0,0x8B0000,2,1,g_homing_shot_knockback_value,1.0f,1.0f);
                if (hit) SpawnExplosion(obj+0x10,0,25,20,20,20,45,1,1,0,0,0,1.0f,20.0f);
                {
                /* Block scopes keep these local to one basic block, as retail allocates them. */
                float effect=spread*105000.0f, diameter;
                int count=50-state->age;
                if(count>5) count=5;
                diameter=spread+spread;
                {
                int b=math_random_int_range(63,127);
                int g=math_random_int_range(47,63);
                int r=math_random_int_range(15,47);
                int high=(g<<8)|0x4F000000;
                SpawnJointFollowParticle(obj,(b<<16)|high|r,count,-1,effect);
                }
                part_spawn_random_direction_effect(&frame.velocity,spread*0.016666668f,diameter*0.016666668f);
                {
                int b=math_random_int_range(63,127);
                int g=math_random_int_range(47,63);
                int r=math_random_int_range(15,47);
                int high=(g<<8)|0x7F000000;
                part_spawn_spark(obj+0x10,&frame.velocity,(b<<16)|high|r,0x4F7F4F2F,45,1,*g_spark_texture[0],-1,0,210000.0f);
                }
                }
                i=5;
                do {
                    part_spawn_random_direction_effect(&frame.velocity,spread*0.016666668f,(spread+spread)*0.016666668f);
                    part_spawn_random_direction_effect(&frame.random,0.0f,spread*0.5f);
                    add_vectors(&frame.position,&frame.random,obj+0x10);
                    particle=part_spawn_short_lived(&frame.random,&frame.velocity,127,obj);
                    /* reorg merges the two decrements into the test's delay slot. */
                    if(particle) {
                        *(float *)(particle+12)=math_random_float_range(6000,32000)*spread*0.4f;
                        --i;
                    } else --i;
                } while(i>=0);
                for(i=0;i<8;i++) {
                    particle=part_spawn_short_lived(obj+0x10,g_effect_position_params,127,obj);
                    if(particle) {
                        sub=particle+0x20;
                        if(i==2 && !math_random_int_below(8)) *(float *)(particle+12)=180000;
                        else *(float *)(particle+12)=math_random_float_range(80000,120000);
                        *(short *)(particle+10)=2;
                        *(float *)(particle+12)*=spread;
                        fade=IntToFloat(2);
                        color=0x7F7F7F;
                        *(short *)(sub+0x16)=3;
                        *(int *)(sub+0x18)=color;
                        *(float *)(sub+0x10)=1.0f/fade;
                    }
                }
            } else {
                hit=coll_process_hit(obj+0x10,16,*(void **)(obj+0xB8),0,radius);
                frame.position.q=((V413 *)(obj+0x10))->q;
                moby_queue_knockback_for_nodes(obj,&frame.position,g_hit_l22_moby_list,hit,0,0x8B0007,2,1,g_homing_shot_knockback_value,1,1);
                if(hit) SpawnExplosion(obj+0x10,0,25,20,20,20,45,1,1,0,0,0,1,20);
                {
                float effect=spread*105000.0f;
                int count=50-state->age;
                if(count>5)count=5;
                {
                int r=math_random_int_range(15,47);
                int g=math_random_int_range(47,63);
                int b=math_random_int_range(63,127);
                int high=(g<<8)|0x4F000000;
                SpawnJointFollowParticle(obj,(r<<16)|high|b,count,-1,effect);
                }
                }
                part_spawn_random_direction_effect(&frame.velocity,spread*0.016666668f,(spread+spread)*0.016666668f);
                {
                int r=math_random_int_range(15,47);
                int g=math_random_int_range(31,47);
                int b=math_random_int_range(63,127);
                int high=(g<<8)|0x7F000000;
                part_spawn_spark(obj+0x10,&frame.velocity,(r<<16)|high|b,0x4F1F1F7F,45,1,*g_spark_texture[0],-1,0,210000);
                }
            }
        }
    }
    }
    if(g_hero_flag_a) {
        cam_compute_view_direction(obj+0x10,&state->orientation,0);
        vec_negate_and_forward(obj+0xC0,&state->orientation,0);
    }
    state->triggered=0;
}
