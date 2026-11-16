#include "include_asm.h"

#include "common.h"
extern u8 g_hero_position_vec[];
extern f32 fast_vec_dist(void *, void *);
extern f32 IntToFloat(int);
extern f32 math_fabs(f32);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
} Quad;
extern f32 func_3278F0(f32, f32);
extern f32 func_2FA3C8(f32);
extern f32 func_2FA3E0(f32);
extern f32 g_ground_height_result;
extern f32 g_hero_height_limit;
extern f32 coll_find_ground_height(Quad *, f32, f32, f32, f32);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern int math_fast_float_d(void *);
extern float math_random_float_range(float, float);
extern float vec_distance_xy(void *, void *);
extern int moby_turn_toward_target_and_step_pal(u8 *, void *, float);
extern float FastVecLength(void *);
extern float math_fabs(float);
extern u8 g_inventory_have_flags[] __attribute__((sda));
extern u8 g_request_l08_queue[];
extern u8 *g_collision_box_table[] __attribute__((sda));
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern f32 math_random_angle(void);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);

int func_PAL_L08_003DD170(u8 *object, float accel, float unused1, float damping,
                     float speed, float unused4, float turn, float friction) {
    u8 *state = *(u8 **)(object + 0x68);
    int result;
    float amount;

    moby_set_controller_speed_limits(object, speed * 0.00040000002f,
                  turn * 0.020000001f,
                  accel * 6.981318e-06f,
                  damping * 0.0003490659f);
    *(float *)(state + 0x154) = friction;
    if (math_fast_float_d(state + 0x474) != 0) {
        *(float *)(state + 0x46C) = -*(float *)(state + 0x46C);
        *(float *)(state + 0x470) = *(float *)(state + 0x46C) * 0.01745329424738884f;
        *(int *)(state + 0x474) = ((s32)(math_random_float_range(30.0f, 90.0f)) * 5 + 2) / 6;
    }
    if (*(int *)(state + 0x48C) != 0 ||
        (object[0x20] == 8 && object[0x95] != 0) ||
        vec_distance_xy(object + 0x10, state + 0x3F0) < 5.0f)
        *(float *)(state + 0x470) = 0;
    result = moby_turn_toward_target_and_step_pal(object, state + 0x3F0, *(float *)(state + 0x470));
    amount = FastVecLength(state + 0x1C0);
    amount += math_fabs(*(float *)(state + 0x1D4));
    if (result & 15) {
        math_fast_float_d(state + 0x448);
        amount = math_fabs(*(float *)(state + 0x1D4)) + 0.012000001f;
    }
    *(float *)(object + 0x48) = amount * 24.999998f;
    if (*(float *)(object + 0x48) > 1.5f)
        *(float *)(object + 0x48) = 1.5f;
    else if (*(float *)(object + 0x48) < 0.0f)
        *(float *)(object + 0x48) = 0;
    return result;
}


typedef struct {
    u8 pad00[0x20];
    u8 f20;
    u8 f21;
    u8 pad22[0x24 - 0x22];
    void *f24;
    u8 pad28[0x2C - 0x28];
    f32 f2C;
    u8 pad30[0x68 - 0x30];
    void *f68;
    u8 pad6C[0x95 - 0x6C];
    u8 f95;
    u16 f96;
    u8 pad98[0xBC - 0x98];
    u8 fBC;
    u8 padBD[0x100 - 0xBD];
} Ent;
typedef struct {
    u8  pad00[0x20];
    f32 f20;
    void *f24;
    u8  pad28[0x2C - 0x28];
    f32 f2C;
    u8  pad30[0x50 - 0x30];
    u8  f50[0x88 - 0x50];
    u16 f88;
    u8  pad8A[0xE4 - 0x8A];
    f32 fE4;
    u8  padE8[0x144 - 0xE8];
    s32 f144;
    u8  pad148[0x150 - 0x148];
    f32 f150[4];
    f32 f160;
    f32 f164;
    f32 f168;
    u8  pad16C[0x189 - 0x16C];
    u8  f189;
    u8  pad18A[0x18C - 0x18A];
    u8  f18C;
    u8  pad18D[0x1B0 - 0x18D];
    f32 f1B0;
    f32 f1B4;
    u8  f1B8[0x1BA - 0x1B8];
    s16 f1BA;
    s16 f1BC;
    u16 f1BE;
    u8  pad1C0[0x1CC - 0x1C0];
    s32 f1CC;
    f32 f1D0;
    f32 f1D4;
    s32 f1D8;
    s32 f1DC;
    u8  f1E0[0x254 - 0x1E0];
    s32 f254;
    u8  pad258[0x40E - 0x258];
    u16 f40E;
    u8  pad410[0x440 - 0x410];
    u8  f440[0x448 - 0x440];
    s32 f448;
    u8  f44C[0x484 - 0x44C];
    s32 f484;
    s32 f488;
    u8  f48C[8];
} Moby;
extern s32 math_fast_float_d();
extern s32 math_random_int_range(s32, s32);
extern s32 func_2EA300(void *, void *, s32, s32, s32);
extern s32 func_3357E8(Ent *, void *, s32);
extern s32 g_cutscene_l08_active_flag[] __attribute__((sda));
extern s32 g_glider_flag_table[] __attribute__((sda));
extern s32 IsPointInCuboid(void *, s32);
extern s32 req_push_queue(void *, s32);
extern s32 req_launch_queued(void *);
extern s32 game_is_either_mode_two(void);
extern s32 math_random_int_range(s32, s32);

/* the countdown runs while the entry is flagged, then the timer field saturates */
void func_PAL_L08_003DD368(Ent *a0)
{
    Moby *s0 = a0->f68;
    u16 v1;

    if (a0->fBC != 0) {
        a0->fBC = 0;
        if (s0->f448 < 167) {
            s0->f448 = ((s32)(math_random_int_range(300, 360)) * 5 + 2) / 6;
            s0->f40E = 12;
        }
    }
    v1 = a0->f96;
    if (s0->f254 == 2) {
        if (math_fast_float_d(&s0->f448)) s0->f40E = 3;
    }
    v1 = a0->f96;
    if (v1 <= 0xFFFDu) a0->f96 = v1 + 1;
    if (a0->f20 == 8) {
        if (a0->f95 == 0) math_fast_float_d(&s0->f48C);
    }
    math_fast_float_d(&s0->f440);
    math_fast_float_d(&s0->f44C);
}



extern int coll_test_hit_at_bone(void *, int, int, int, int, int, float, float, float);
extern void copy_matrix_rotation(void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int g_hero_mode;
extern void FastVecAdd(void *, void *, void *);
extern unsigned char *effect_create_timed(void *, void *, int, int, int, int, int, float);
extern int coll_cast_object_line(void *, void *, void *, int, int, int, int, float, float);
extern float FastAddRotations(float, float);
extern int FloatToInt(float);
extern char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);

/* func_PAL_L08_003DD918, the PAL copy of func_L08_003D9798: the same C, with speeds and
   accelerations times 6/5 and each particle lifetime scaled to 50 Hz, (x * 5 + 2) / 6. */
void func_PAL_L08_003DD918(char *object)
{
    float origin[4], end[4], start[4], step[4], matrix[12], point[4];
    float velocity[4], accel[4], position[4];
    char *state = *(char **)(object + 0x68), *particle;
    float heading, angle;
    int a, b, c;
    coll_test_hit_at_bone(object,1,1,0,1,0,0.5f,(float)*(u8 *)(state+0x34),1.0f);
    copy_matrix_rotation(matrix,object+0xC0);
    moby_transform_joint_to_world(object,1,point);
    qcopy_nc(origin,point);
    matrix[2]=0;
    qcopy_nc(start,origin);
    vec_scale_to_length(end,matrix,3.0f);
    if (*(int *)(state+0x250)) {
        if ((unsigned)(g_hero_mode-17)<2) end[2]=*(float *)(state+0x218)-start[2];
        else end[2]=*(float *)(state+0x248)-start[2];
        if (end[2]>1.2f) end[2]=1.2f;
        else if(end[2]<-1.2f) end[2]=-1.2f;
    }
    FastVecAdd(end,end,start);
    effect_create_timed(end,object,1,0x808080,127,30,255,0.5f);
    coll_cast_object_line(object,start,end,1,0,1,0,(float)*(u8 *)(state+0x34),1.0f);
    vec_scale_to_length(step,matrix+4,0.1f);
    FastVecAdd(start,start,step);
    FastVecAdd(end,end,step);
    end[2]+=math_random_float_range(-0.2f,0.2f);
    coll_cast_object_line(object,start,end,1,0,1,0,(float)*(u8 *)(state+0x34),1.0f);
    vec_scale_to_length(step,matrix+4,-0.2f);
    FastVecAdd(start,start,step);
    FastVecAdd(end,end,step);
    end[2]+=math_random_float_range(-0.2f,0.2f);
    coll_cast_object_line(object,start,end,1,0,1,0,(float)*(u8 *)(state+0x34),1.0f);
    heading=*(float *)(object+0xF8);
    velocity[3]=0.6f; accel[3]=1.5f;
    { int i; for(i=1;i>=0;i--) {
        qcopy_nc(position,origin);
        position[0]+=math_random_float_range(-0.065f,0.065f);
        position[1]+=math_random_float_range(-0.065f,0.065f);
        position[2]+=math_random_float_range(-0.065f,0.065f);
        velocity[0]=math_fast_sin_or_cos_a(heading)*0.34000003f;
        velocity[1]=math_fast_sin_or_cos_b(heading)*0.34000003f;
        velocity[2]=0;
        velocity[2]=math_random_float_range(0,0);
        angle=math_random_float_range(-90,90)*0.01745329424738884f;
        accel[0]=math_fast_sin_or_cos_a(FastAddRotations(heading,angle))*0.010000001f;
        accel[1]=math_fast_sin_or_cos_b(FastAddRotations(heading,angle))*0.010000001f;
        accel[2]=0;
        accel[2]=math_random_float_range(0.018000001f,0.022000002f);
        a=FloatToInt((math_random_float_range(2,4)*5.0f+2.0f)*0.16666667f);
        b=FloatToInt((math_random_float_range(12,14.40000057220459f)*5.0f+2.0f)*0.16666667f);
        c=FloatToInt((math_random_float_range(200,240.00001525878906f)*5.0f+2.0f)*0.16666667f);
        particle=part_spawn_trail(position,velocity,accel,0x40101080,0x10101080,a,b,c,-1);
        if(particle && (func_001163B0()&1)) particle[3]=0x48;
    }
    }
    velocity[3]=0.05f; accel[3]=0.07f;
    { int i; for(i=1;i>=0;i--) {
        qcopy_nc(position,origin);
        position[0]+=math_random_float_range(-0.2f,0.2f);
        position[1]+=math_random_float_range(-0.2f,0.2f);
        position[2]+=math_random_float_range(-0.2f,0.2f);
        angle=math_random_float_range(-10,10)*0.01745329424738884f;
        velocity[0]=math_fast_sin_or_cos_a(FastAddRotations(heading,angle))*0.24000001f;
        velocity[1]=math_fast_sin_or_cos_b(FastAddRotations(heading,angle))*0.24000001f;
        velocity[2]=0;
        velocity[2]=math_random_float_range(0,0);
        angle=math_random_float_range(-90,90)*0.01745329424738884f;
        accel[0]=math_fast_sin_or_cos_a(FastAddRotations(heading,angle))*0.010000001f;
        accel[1]=math_fast_sin_or_cos_b(FastAddRotations(heading,angle))*0.010000001f;
        accel[2]=0;
        accel[2]=math_random_float_range(0.014f,0.030000001f);
        a=FloatToInt((math_random_float_range(2,4)*5.0f+2.0f)*0.16666667f);
        b=FloatToInt((math_random_float_range(20,24)*5.0f+2.0f)*0.16666667f);
        c=FloatToInt((math_random_float_range(200,240.00001525878906f)*5.0f+2.0f)*0.16666667f);
        particle=part_spawn_trail(position,velocity,accel,0x801010FF,0x801010FF,a,b,c,-1);
        if(particle && (func_001163B0()&1)) particle[3]=0x48;
    }
    }
}
