/* func_PAL_L23_00428A98, the PAL copy of func_L23_004236B8: the same C, where rename func_L22_003398B8 becomes func_PAL_L22_0033BBB0; rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_002BCB00 becomes func_PAL_002BD790; rename func_L08_0034A078 becomes func_PAL_L08_0034C4A8; lit 1.0f becomes 1.2f. */
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
extern int g_hero_charged_shot_moby __attribute__((sda)), g_enemy_charged_shot_moby __attribute__((sda));
extern int g_hero_charge_sound_handle __attribute__((sda)), g_enemy_charge_sound_handle __attribute__((sda));
extern float D_L23_001B1934 __attribute__((sda)), D_L23_001B1938 __attribute__((sda));
extern int D_L23_001A8FF0 MACRO_ADDR;
typedef struct { int enabled; unsigned int color; unsigned long long counter; } ChargeFx413;
extern ChargeFx413 D_L23_001A8AC0[] __attribute__((sda));
extern int D_L23_001A8AB0;
extern int D_L23_001B22C8;
extern float D_L23_001B3704;
extern char D_L23_001C4B00[];
/* sda: one la macro per use, so its address is not kept across the loop. */
extern char D_L23_001A8F20[] __attribute__((sda));
/* Unsized view: read through a separate lui rather than the small-data lw macro. */
extern unsigned char *D_L23_002001EC[];
extern Light413 D_L23_001C87C0[];
extern float IntToFloat(int), math_random_float_range(float,float), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern int FloatToInt(float), math_random_int_range(int,int), math_random_int_below(int);
extern void vec_scale_to_length(void*,void*,float), add_vectors(void*,void*,void*);
extern void func_PAL_L22_0033BBB0(int,void*,void*);
extern void part_spawn_glow_record(void*,int,int,int,int,float,float);
extern short gfx_add_point_light(void*,int,float,float);
extern int snd_start_in_slot(int,int,int);
extern void snd_stop_voice(int), gfx_free_point_light(int), moby_mark_spawned(int);
extern void FastVecScale(void*,void*,float),cam_compute_view_direction(void*,void*,int),vec_negate_and_forward(void*,void*,int);
extern void FastVecCross(void*,void*,void*),quaternion_to_rotation_basis(void*,void*),multiply_matrix3x3(void*,void*,void*);
extern float FastVecLength(void*),square_root(float);
extern int coll_process_hit(void*,int,void*,int,float);
extern void moby_queue_knockback_for_nodes(void*,void*,void*,int,int,int,int,int,float,float,float);
extern void func_PAL_L00_003FB330(void*,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern void SpawnJointFollowParticle(void*,int,int,int,float),part_spawn_random_direction_effect(void*,float,float);
extern void func_PAL_002BD790(void*,void*,int,int,int,int,int,int,int,float);
extern char *func_PAL_L08_0034C4A8(void*,void*,int,void*);

void func_PAL_L23_00428A98(unsigned char *obj)
{
    struct { V413 velocity, random, position, scaled, matrix[3], rotation, normalized, temp; } frame;
    State413 *state;
    int *handle = &g_enemy_charged_shot_moby;
    int i, j, hit, color;
    float radius, spread, fade, factor;
    char *particle, *sub;
    if (*(int *)(obj+0xB8) == g_hero_state.owner) handle=&g_hero_charged_shot_moby;
    state = *(State413 **)(obj+0x68);
    switch (obj[0x20]) {
    case 0: {
        float charge;
        if (state->triggered && (g_hero_state.mode==2 || !state->kind)) {
            if (!state->charge && handle==&g_enemy_charged_shot_moby) {
                D_L23_001A8AC0[0].enabled=1;
                D_L23_001A8AC0[0].color=0xFFFF00;
            }
            charge=IntToFloat(++state->charge)*0.039473683f;
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
                    func_PAL_L22_0033BBB0((loop_b<<16)|high|loop_r,&frame.velocity,obj);
                }
            }
            if (state->charge<50) {
                int alpha=D_L23_001A8AC0[0].color>>24;
                if (!D_L23_001A8AC0[0].counter && alpha==255) alpha=37;
                if (alpha<36) alpha++; else alpha=37;
                D_L23_001A8AC0[0].counter=0x1F00000042ULL;
                D_L23_001A8AC0[0].color=(D_L23_001A8AC0[0].color&0xFFFF00)|(alpha<<24);
            } else D_L23_001A8AC0[0].color |= 0xFF000000;
            if (state->light != -1) {
                float light_charge;
                float inner, outer;
                D_L23_001C87C0[state->light].position.f.x=*(float *)(obj+0x10);
                D_L23_001C87C0[state->light].position.f.y=*(float *)(obj+0x14);
                D_L23_001C87C0[state->light].position.f.z=*(float *)(obj+0x18);
                { int n=state->charge;
                if (n>50) n=50;
                if (n<0) n=0;
                D_L23_001C87C0[state->light].position.f.w=IntToFloat(n)*0.14f; }
                light_charge=IntToFloat(state->charge)*0.039473683f;
                if (light_charge>1) light_charge=1;
                part_spawn_glow_record(&D_L23_001C87C0[state->light].position,
                    math_random_int_range(15,47)&255,math_random_int_range(47,63)&255,math_random_int_range(63,127)&255,17,light_charge*840000.0f,0.0f);
                D_L23_001C87C0[state->light].inner=math_random_float_range(D_L23_001C87C0[state->light].inner*0.8f,
                    (D_L23_001C87C0[state->light].position.f.w+D_L23_001C87C0[state->light].position.f.w)*0.14285715f);
                outer=D_L23_001C87C0[state->light].outer*0.8f;
                inner=D_L23_001C87C0[state->light].inner;
                D_L23_001C87C0[state->light].outer=math_random_float_range(inner < outer ? inner : outer,inner);
            } else if (!(D_L23_001B22C8&3)) {
                state->light=gfx_add_point_light(obj+0x10,0,0.0f,0.0f);
            }
        } else {
            D_L23_001A8AB0=0;
            D_L23_001A8AC0[0].enabled=0;
            state->charge=0;
            snd_start_in_slot(22,0,0);
            if (state->kind) {
                if (g_hero_charge_sound_handle != -1) {
                    snd_stop_voice(g_hero_charge_sound_handle);
                    g_hero_charge_sound_handle=snd_start_in_slot(21,0,0);
                }
            } else if (g_enemy_charge_sound_handle != -1) {
                snd_stop_voice(g_enemy_charge_sound_handle);
                g_enemy_charge_sound_handle=snd_start_in_slot(21,0,0);
            }
            if (!D_L23_001A8FF0) {
                state->velocity.f.x=math_fast_sin_or_cos_a(g_hero_state.angle)*0.8000001f;
                state->velocity.f.y=math_fast_sin_or_cos_b(g_hero_state.angle)*0.8000001f;
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
        radius=IntToFloat(state->age)*0.40000004f+1.3f;
        ++state->age;
        cam_compute_view_direction(obj+0x10,&frame.position,1);
        spread=radius+extra;
        if (state->kind) vec_scale_to_length(&frame.scaled,obj+0xC0,2.0f);
        else vec_scale_to_length(&frame.scaled,obj+0xC0,extra);
        vec_scale_to_length(&frame.normalized,&frame.position,1.0f);
        FastVecCross(&frame.rotation,obj+0xE0,&frame.normalized);
        if (state->kind) factor=D_L23_001B1938; else factor=D_L23_001B1934;
        FastVecScale(&frame.rotation,&frame.rotation,factor);
        fade=FastVecLength(&frame.rotation);
        frame.rotation.f.w=-square_root(1.0f-fade*fade);
        quaternion_to_rotation_basis(&frame.rotation,frame.matrix);
        multiply_matrix3x3(obj+0xC0,frame.matrix,obj+0xC0);
        if (state->override) {
            if (state->kind) FastVecScale(&frame.scaled,&state->direction,0.8000001f);
            else FastVecScale(&frame.scaled,&state->direction,1.2f);
            vec_scale_to_length(&frame.temp,&frame.scaled,1.0f);
            qcopy(obj+0xC0, &frame.temp);
        }
        state->velocity.q=frame.scaled.q;
        if (state->light!=-1) {
            Light413 *lights = D_L23_001C87C0;
            lights[state->light].position.f.w *= 0.27999997f;
            if (lights[state->light].position.f.w<0.0001f) {
                gfx_free_point_light(state->light);
                state->light=-1;
            }
        }
        if (state->age>=43 || g_hero_state.mode!=2) {
            if (*(int *)(obj+0xB8)==g_hero_state.owner) {
                if(g_hero_charge_sound_handle!=-1) {snd_stop_voice(g_hero_charge_sound_handle);g_hero_charge_sound_handle=-1;}
            } else if(g_enemy_charge_sound_handle!=-1) {snd_stop_voice(g_enemy_charge_sound_handle);g_enemy_charge_sound_handle=-1;}
            moby_mark_spawned(*handle);
            *handle=0;
            return;
        } else {
            add_vectors(&frame.position,obj+0x10,state);
            if (*(float *)(obj+0x10)<2 || *(float *)(obj+0x10)>1021 ||
                *(float *)(obj+0x14)<2 || *(float *)(obj+0x14)>1021 ||
                *(float *)(obj+0x18)<2 || *(float *)(obj+0x18)>1021) {
                if (*(int *)(obj+0xB8)==g_hero_state.owner) {
                    if(g_hero_charge_sound_handle!=-1) {snd_stop_voice(g_hero_charge_sound_handle);g_hero_charge_sound_handle=-1;}
                } else if(g_enemy_charge_sound_handle!=-1) {snd_stop_voice(g_enemy_charge_sound_handle);g_enemy_charge_sound_handle=-1;}
                moby_mark_spawned(*handle);
                *handle=0;
                return;
            } else if (state->kind) {
                hit=coll_process_hit(obj+0x10,16,obj,0,radius);
                frame.position.q=((V413 *)(obj+0x10))->q;
                moby_queue_knockback_for_nodes(obj,&frame.position,D_L23_001C4B00,hit,0,0x8B0000,2,1,D_L23_001B3704,1.0f,1.0f);
                if (hit) func_PAL_L00_003FB330(obj+0x10,0,25,20,20,20,45,1,1,0,0,0,1.0f,20.0f);
                {
                /* Block scopes keep these local to one basic block, as retail allocates them. */
                float effect=spread*105000.0f, diameter;
                int count=42-state->age;
                if(count>4) count=4;
                diameter=spread+spread;
                {
                int b=math_random_int_range(63,127);
                int g=math_random_int_range(47,63);
                int r=math_random_int_range(15,47);
                int high=(g<<8)|0x4F000000;
                SpawnJointFollowParticle(obj,(b<<16)|high|r,count,-1,effect);
                }
                part_spawn_random_direction_effect(&frame.velocity,spread*0.020000001f,diameter*0.020000001f);
                {
                int b=math_random_int_range(63,127);
                int g=math_random_int_range(47,63);
                int r=math_random_int_range(15,47);
                int high=(g<<8)|0x7F000000;
                func_PAL_002BD790(obj+0x10,&frame.velocity,(b<<16)|high|r,0x4F7F4F2F,37,1,*D_L23_002001EC[0],-1,0,210000.0f);
                }
                }
                i=5;
                do {
                    part_spawn_random_direction_effect(&frame.velocity,spread*0.020000001f,(spread+spread)*0.020000001f);
                    part_spawn_random_direction_effect(&frame.random,0.0f,spread*0.5f);
                    add_vectors(&frame.position,&frame.random,obj+0x10);
                    particle=func_PAL_L08_0034C4A8(&frame.random,&frame.velocity,127,obj);
                    /* reorg merges the two decrements into the test's delay slot. */
                    if(particle) {
                        *(float *)(particle+12)=math_random_float_range(6000,32000)*spread*0.4f;
                        --i;
                    } else --i;
                } while(i>=0);
                for(i=0;i<8;i++) {
                    particle=func_PAL_L08_0034C4A8(obj+0x10,D_L23_001A8F20,127,obj);
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
                moby_queue_knockback_for_nodes(obj,&frame.position,D_L23_001C4B00,hit,0,0x8B0007,2,1,D_L23_001B3704,1,1);
                if(hit) func_PAL_L00_003FB330(obj+0x10,0,25,20,20,20,45,1,1,0,0,0,1,20);
                {
                float effect=spread*105000.0f;
                int count=42-state->age;
                if(count>4)count=4;
                {
                int r=math_random_int_range(15,47);
                int g=math_random_int_range(47,63);
                int b=math_random_int_range(63,127);
                int high=(g<<8)|0x4F000000;
                SpawnJointFollowParticle(obj,(r<<16)|high|b,count,-1,effect);
                }
                }
                part_spawn_random_direction_effect(&frame.velocity,spread*0.020000001f,(spread+spread)*0.020000001f);
                {
                int r=math_random_int_range(15,47);
                int g=math_random_int_range(31,47);
                int b=math_random_int_range(63,127);
                int high=(g<<8)|0x7F000000;
                func_PAL_002BD790(obj+0x10,&frame.velocity,(r<<16)|high|b,0x4F1F1F7F,37,1,*D_L23_002001EC[0],-1,0,210000);
                }
            }
        }
    }
    }
    if(D_L23_001A8FF0) {
        cam_compute_view_direction(obj+0x10,&state->orientation,0);
        vec_negate_and_forward(obj+0xC0,&state->orientation,0);
    }
    state->triggered=0;
}
