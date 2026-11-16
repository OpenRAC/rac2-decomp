/* func_PAL_L04_003FE9E8, the PAL copy of func_L04_003FA7E0. */
#include "common.h"
/* Projectile steering, collision response and impact effects shared by Barlow and Joba.
 * The aligned 0x50-byte template uses the compiler's normal quadword block move.
 * Keep the real helper returns even when ignored: they affect call scheduling. */
typedef int HomingUpdateQuad __attribute__((mode(TI), aligned(16)));
typedef union { float v[4]; HomingUpdateQuad q; } HomingUpdateVector;
typedef struct { HomingUpdateVector v[5]; } __attribute__((aligned(16))) HomingUpdateTemplate;
typedef struct { unsigned int v[6]; } HomingUpdateColors;
typedef union { HomingUpdateColors colors; HomingUpdateVector vectors[2]; } HomingUpdateColorScratch;
extern HomingUpdateTemplate g_homing_update_template;
extern unsigned char *g_homing_rocket_particle_color;
extern float g_camera_alignment_value MACRO_ADDR;
extern unsigned char g_hero_l04_state[];
extern unsigned char g_special_moby_list[];
extern char g_tether_zero_vec[];
extern HomingUpdateColors g_homing_rocket_colors_a, g_homing_rocket_colors_b;
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void add_vectors(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern float vec_length_xy(void *);
extern float FastVecDot(void *, void *);
extern float FastVecLength(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int math_fast_float_d(void *);
extern int FastDecTimer(void *);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_approach_with_velocity(void *, float, void *, float, float, float, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_fast_divide_helper(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void * part_spawn_trailing_spark(void *, void *, int, int, int, int, float);
extern unsigned char *part_spawn_burst_pal(void *, void *, int, int, int, int, float, float, float, float, float);
extern unsigned char *bike_find_aim_target(void *, void *, void *, void *, void *, void *, float, float);
extern void projectile_steer_around_walls_pal(void *, void *, void *);
extern void racer_update_event_streak(void);
extern void *SweepProjectileCollision_pal(void *, void *, void *, void *, void *, void *, void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern int coll_process_hit(void *, int, void *, float, int);
extern void moby_queue_knockback_for_nodes(void *, void *, void *, int, int, int, int, int, float, float, float);
extern void multiply_matrix(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void func_L03_002EFB60(void *, void *, float);
extern void level_draw_helper(void *, void *, void *);
extern void set_identity_matrix(void *);
extern void transform_vector(void *, void *, void *);
extern void * part_spawn_spark_pal(void *, void *, int, int, int, int, int, int, int, float);
extern void * part_spawn_spinning_debris_pal(void *, void *, int, int, int);
extern void * part_spawn_firework_spark(void *, void *, int, int, int, int, float, float, int, int);
extern void part_spawn_color_blend(void *, void *, int, int, int, float);
extern void * part_spawn_shockwave_ring_pal(void *, void *, void *, float, int, unsigned char, unsigned char, unsigned char, unsigned char);
extern void *moby_spawn_template_effect(void *, void *, int, void *);
extern void * part_spawn_blast_effect_moby_pal(void *, void *, void *, float);
extern void moby_mark_spawned(void *);
typedef struct {
    unsigned char pad0[0x140];
    float focus[4];
    unsigned char pad150[0x10];
    float shakeA;
    int pad164;
    int shakeTimeA;
    int shakeClockA;
    unsigned char pad170[0x10];
    float shakeB;
    int pad184;
    int shakeTimeB;
} HomingCamera;
#define BF(p,o) (*(float *)((unsigned char *)(p)+(o)))
#define BI(p,o) (*(int *)((unsigned char *)(p)+(o)))
#define BP(p,o) (*(unsigned char **)((unsigned char *)(p)+(o)))
/* Updates a homing rocket: steers it to its target or ahead, leaves a smoke and spark trail, and on impact bursts into fireworks, shakes the camera and removes itself. */
void homing_rocket_update_pal(unsigned char *moby) {
    HomingUpdateTemplate settings;
    HomingUpdateVector camera_motion, old_pos, velocity, normal, trail_motion, direction, hit_pos, acceleration, motion, steering_temp, target_pos, temp, random;
    float cross[16], cross_squared[16], matC[16], matB[16], matA[16];
    HomingUpdateColorScratch colors_a;
    HomingUpdateColors colors_b, colors_c;
    float outX, outY, outZ;
    int collision;
    unsigned char *state, *target, *owner, *owner_state, *particle;
    HomingCamera *camera;
    float yaw, pitch, jitter, threshold, cam_dist, angle, speed, fade;
    int i, j, count, life_a, life_b;
    settings=g_homing_update_template;
    collision=0;
    velocity.q = 0; velocity.v[2] = 0.16000001f;
    normal.q = 0; normal.v[2] = 1.0f;
    acceleration.q = 0;
    state = BP(moby,0x68);
    BF(state,0x30) += (BF(state,0x44) - BF(state,0x30)) * 0.14400001f;
    target = BP(state,0x28);
    if (target && *(short *)(target+0xAA) == 0xBBC) {
        if (target[0xBC] == 6) goto destroy;
        owner_state = BP(target,0x68);
        qcopy(&target_pos,target+0x10);
        FastVecScale(&steering_temp,target+0xC0,1.75f);
        FastVecAdd(&target_pos,&target_pos,&steering_temp);
        if (BI(owner_state,0x744)) {
            jitter = math_random_float_range(-0.25f,0.25f);
            if (!(BI(owner_state,0x744)&1)) jitter += 1.5f;
            else jitter -= 1.5f;
            FastVecScale(&steering_temp,target+0xD0,jitter);
            FastVecAdd(&target_pos,&target_pos,&steering_temp);
            FastVecScale(&steering_temp,target+0xC0,1.0f);
            FastVecAdd(&target_pos,&target_pos,&steering_temp);
        }
        yaw = mat_fast_helper_a(target_pos.v[0]-BF(moby,0x10),target_pos.v[1]-BF(moby,0x14));
        pitch = -mat_fast_helper_a(vec_distance_xy(moby+0x10,&target_pos),target_pos.v[2]-BF(moby,0x18));
    } else {
        if (!target) {
            *(HomingUpdateQuad *)&temp = *(HomingUpdateQuad *)(moby+0x10);
            *(HomingUpdateQuad *)&random = *(HomingUpdateQuad *)(moby+0xC0);
            target = bike_find_aim_target(moby,&temp,&random,&outX,&outY,&outZ,0.3490659f,30.0f);
            if (target) { BP(state,0x28)=target; BF(state,0x2C)=outZ; }
        }
        owner = BP(state,0x20);
        if (owner && *(short *)(owner+0xAA)==0xBBC) {
            unsigned char *owner_data = BP(owner,0x68);
            FastDecTimer(state+0x4C);
            jitter = IntToFloat(*(short *)(state+0x4C));
            jitter /= IntToFloat(*(short *)(state+0x4E));
            FastVecScale(&acceleration,owner_data+0x290,jitter);
        }
        if (target) {
            FastVecSub(&motion,target+0x10,moby+0x10);
            jitter = FastVecDot(&motion,&motion);
        } else jitter=200.0f;
        if (jitter>32.0f && (target || BI(state,0x24)>50)) {
            projectile_steer_around_walls_pal(moby,state+0x3C,state+0x40);
            yaw=BF(state,0x3C);
            pitch=BF(state,0x40);
        } else if (target && BI(state,0x24)<250 && (signed char)target[0x20]>=0) {
            qcopy(&target_pos,target+0x10);
            target_pos.v[2]+=BF(state,0x2C);
            FastVecSub(&motion,&target_pos,moby+0x10);
            yaw=mat_fast_helper_a(motion.v[0],motion.v[1]);
            pitch=-mat_fast_helper_a(vec_length_xy(&motion),motion.v[2]);
        } else if (BI(state,0x24)<250) {
            yaw=BF(state,0x3C); pitch=BF(state,0x40);
        } else { yaw=BF(moby,0xF8); pitch=BF(moby,0xF4); }
    }
    if (target) {
        if (*(short *)(target+0xAA)==0xBBC) {
            math_approach_with_velocity(moby+0xF8,yaw,state+0x34,0.14400001f,0.40320003f,0.25132746f,0);
            math_approach_with_velocity(moby+0xF4,pitch,state+0x38,0.14400001f,0.40320003f,0.25132746f,0);
        } else {
            math_approach_with_velocity(moby+0xF8,yaw,state+0x34,3.4560003f,0.2592f,0.20943955f,0);
            math_approach_with_velocity(moby+0xF4,pitch,state+0x38,3.4560003f,0.2592f,0.20943955f,0);
        }
    } else {
        math_approach_with_velocity(moby+0xF8,yaw,state+0x34,5760.0f,0.2592f,0.25132746f,0);
        math_approach_with_velocity(moby+0xF4,pitch,state+0x38,14400.001f,0.2592f,0.37699118f,0);
    }
    vec_build_spherical_offset(&direction,BF(state,0x30),BF(moby,0xF8),-BF(moby,0xF4));
    random.q = 0;
    random.v[0]=math_random_float_range(-1.0f,1.0f);
    random.v[1]=math_random_float_range(-1.0f,1.0f);
    random.v[2]=math_random_float_range(-1.0f,1.0f);
    *(HomingUpdateQuad *)&temp = *(HomingUpdateQuad *)(&random);
    vec_scale_to_length(&temp,&temp,math_random_float_range(0.1f,0.2f)*0.020000001f);
    vec_scale_to_length(&trail_motion,&direction,-math_random_float_range(0.002f,0.020000001f));
    FastVecAdd(&temp,&temp,&trail_motion);
    vec_scale_to_length(&trail_motion,&direction,math_random_float_range(0,1)*BF(state,0x30));
    FastVecAdd(&trail_motion,&trail_motion,moby+0x10);
    particle=part_spawn_burst_pal(&trail_motion,&temp,50,127,0x606060,3,40000,1000,1,-0.0002f,0);
    if(particle) { unsigned char b=*g_homing_rocket_particle_color; particle[3]=0x44; particle[2]=b; }
    part_spawn_burst_pal(moby+0x10,&temp,5,127,0xB0B0B0,3,40000,1000,1,-0.0004f,0);
    random.q = 0; random.v[2]=0.02f;
    matrix_mul_vec3(&random,&random,moby+0xC0);
    math_apply_axis_rotation_to_quat(&random,&random,moby+0xC0,math_random_angle());
    part_spawn_trailing_spark(&trail_motion,&random,0x4F007FFF,0x1FFFFFFF,4,1,20000);
    qcopy(&old_pos,moby+0x10);
    add_vectors(&temp,&direction,&acceleration);
    if(target && *(short *)(target+0xAA)==0xBBC) {
        FastVecAdd(moby+0x10,moby+0x10,&direction);
        FastVecSub(&direction,moby+0x10,&target_pos);
        threshold=0.5f;
        if(BI(BP(target,0x68),0x744)) threshold=1;
        if(FastVecDot(&direction,&direction)<threshold) { racer_update_event_streak(); moby[0xBC]=2; }
    } else {
        if(BF(moby,0x10)<0 || BF(moby,0x14)<0 || BF(moby,0x18)<0) goto destroy;
        collision=SweepProjectileCollision_pal(moby,state,moby+0x10,&direction,&velocity,&normal,&hit_pos);
    }
    if(!moby[0xBC]) goto finish;
    snd_play_from_class_bank(11,0,moby,0xBBC);
    if(target && *(short *)(target+0xAA)!=0xBBC) {
        life_a=coll_process_hit(moby+0x10,16,moby,2.0f,0);
        *(HomingUpdateQuad *)&temp = *(HomingUpdateQuad *)(moby+0x10);
        moby_queue_knockback_for_nodes(moby,&temp,g_special_moby_list,life_a,collision,0x30000,3,1,2,1,1);
    }
    cross[0]=0; cross[4]=-normal.v[2]; cross[8]=normal.v[1]; cross[12]=0;
    cross[1]=normal.v[2]; cross[5]=0; cross[9]=-normal.v[0]; cross[13]=0;
    cross[2]=-normal.v[1]; cross[6]=normal.v[0]; cross[10]=0; cross[14]=0;
    cross[3]=0; cross[7]=0; cross[11]=0; cross[15]=0;
    multiply_matrix(cross_squared,cross,cross);
    for(i=0;i<10;i++) {
        angle=math_random_angle();
        func_L03_002EFB60(matA,cross_squared,1-math_fast_sin_or_cos_a(angle));
        func_L03_002EFB60(matB,cross,math_fast_sin_or_cos_b(angle));
        level_draw_helper(matB,matB,matA);
        set_identity_matrix(matA);
        level_draw_helper(matC,matB,matA);
        transform_vector(&temp,&hit_pos,matC);
        vec_scale_to_length(&temp,&temp,math_random_float_range(8.5f,16.5f)*0.020000001f);
        temp.v[2]+=0.10000001f;
        FastVecAdd(&temp,&temp,&velocity);
        part_spawn_spark_pal(moby+0x10,&temp,0x4F007FFF,0x1F00007F,math_random_int_range(50,100),1,-1,-1,0,40000);
    }
    random.q = 0;
    random.v[0]=math_random_float_range(-1,1); random.v[1]=math_random_float_range(-1,1); random.v[2]=math_random_float_range(-1,1);
    *(HomingUpdateQuad *)&temp = *(HomingUpdateQuad *)(&random);
    FastVecSub(&camera_motion,g_tether_zero_vec,moby+0x10);
    cam_dist=FastVecLength(&camera_motion);
    camera_motion.v[2]+=cam_dist*0.5f;
    vec_scale_to_length(&temp,&temp,cam_dist*0.004f);
    vec_scale_to_length(&camera_motion,&camera_motion,(cam_dist+cam_dist)*0.020000001f);
    FastVecAdd(&temp,&temp,&camera_motion);
    vec_fast_divide_helper(&temp,&temp,0.20000002f);
    part_spawn_spinning_debris_pal(moby+0x10,&temp,math_random_int_range(50,75),0,0);
    if(cam_dist<6) count=FloatToInt(cam_dist)/2;
    else count=3;
    fade=0;
    if(cam_dist<7) fade=7-cam_dist;
    for(j=0;j<count;j++) {
        speed=math_random_float_range(8,10)*0.020000001f;
        colors_a.colors=g_homing_rocket_colors_a; colors_b=g_homing_rocket_colors_b;
        speed-=fade*0.020000001f;
        {
            unsigned int *ca=colors_a.colors.v+math_random_int_below(6), *cb=colors_b.v+math_random_int_below(6);
            int la=math_random_int_range(12,17), lb=math_random_int_range(21,25);
            part_spawn_firework_spark(moby+0x10,&velocity,*ca,*cb,la,lb,400000,speed,0,0);
        }
        {
            int la=math_random_int_range(4,8), lb=math_random_int_range(12,17);
            part_spawn_firework_spark(moby+0x10,&velocity,0x7FFFFFFF,0xFFFFFF,la,lb,400000,speed*0.5f,0,0);
        }
    }
    for(j=0;j<10;j++) {
        colors_a.colors=g_homing_rocket_colors_a; colors_c=g_homing_rocket_colors_b;
        random.q = 0;
        random.v[0]=math_random_float_range(-1,1); random.v[1]=math_random_float_range(-1,1); random.v[2]=math_random_float_range(-1,1);
        *(HomingUpdateQuad *)&colors_b = *(HomingUpdateQuad *)(&random);
        vec_scale_to_length(&colors_b,&colors_b,math_random_float_range(0,3)*0.020000001f);
        {
            unsigned int *ca=colors_a.colors.v+math_random_int_below(6), *cb=colors_c.v+math_random_int_below(6);
            part_spawn_color_blend(moby+0x10,&colors_b,*ca,*cb,math_random_int_range(17,29),200000);
        }
    }
    if(g_camera_alignment_value<0.95f && cam_dist>9) {
        part_spawn_shockwave_ring_pal(moby,moby+0x10,&velocity,4,12,127,127,127,32);
        part_spawn_shockwave_ring_pal(moby,moby+0x10,&velocity,4,20,127,127,127,32);
    }
    part_spawn_shockwave_ring_pal(moby,moby+0x10,&velocity,4,17,127,127,0,48);
    part_spawn_shockwave_ring_pal(moby,moby+0x10,&velocity,2,16,255,255,255,32);
    direction.v[0]=0;
    moby[0xBC]=0;
    {
        HomingCamera *shake=(HomingCamera *)g_hero_l04_state;
        if(cam_dist<20) shake->shakeA=0.4f-cam_dist*0.0175f;
        else shake->shakeA=0.050000012f;
    }
    camera=(HomingCamera *)g_hero_l04_state;
    camera->shakeTimeA=21; camera->shakeClockA=0;
    moby_spawn_template_effect(&settings,moby+0x10,0,0);
    FastVecSub(&random,moby+0x10,camera->focus);
    if(FastVecLength(&random)<64) {
        FastVecSub(&colors_a.vectors[1],camera->focus,&colors_a);
        vec_scale_to_length(&colors_a.vectors[1],&colors_a.vectors[1],1);
        part_spawn_blast_effect_moby_pal(moby,moby+0x10,&colors_a.vectors[1],5);
        camera->shakeB=0.1f; camera->shakeTimeB=75;
        camera->shakeA=0.2f; camera->shakeTimeA=50; camera->shakeClockA=0;
    }
destroy:
    moby_mark_spawned(moby);
    return;
finish:
    if(target && *(short *)(target+0xAA)==0xBBC) return;
    if(math_fast_float_d(state+0x24) || !BP(state,0x20) || vec_distance_xy(moby+0x10,BP(state,0x20)+0x10)>260) moby_mark_spawned(moby);
}
#undef BF
#undef BI
#undef BP
