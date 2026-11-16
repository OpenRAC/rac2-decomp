#include "common.h"

typedef struct {
    u8 pad00[0x20];
    float hit[4];
    float adjusted[4];
    float normal[4];
} CollisionResult;

extern CollisionResult g_collision_l08_result;
extern int coll_test_point(void *, int, void *, float);
extern void vec_fast_normalize(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void moby_mark_spawned(void *);
extern int CollLine(void *, void *, int, void *, int);



typedef struct { u8 pad_0[0x20]; u8 flags; } FlareMoby;
typedef struct {
    FlareMoby *moby; s32 state; f32 intensity; s32 pad_c;
    s16 alpha[16]; s16 tex[16]; s32 color[16]; f32 dist[16]; f32 scale[16];
} LensFlare;
typedef struct {
    int width, height, half_width, half_height;
    int left, top, right, bottom;
} ScreenExtent;
extern LensFlare g_lens_flare_2;
extern u8 g_hero_position_vec[];
extern int g_lens_l08_flare_base_size;
extern ScreenExtent g_screen_width __attribute__((sda));
extern f32 fast_vec_dist(void *, void *);
extern f32 IntToFloat(int);
extern void gfx_project_world_point_to_screen(f32 *, void *);
extern long long GetEffectTextureDescriptor(int);
extern f32 math_fabs(f32);
extern int FloatToInt(f32);
extern void VU1_addGSregister(int, long long);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, long long, long long);


extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);


extern int FloatToInt(float);
extern char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);
extern int coll_test_hit_at_bone(void *, int, int, int, int, int, float, float, float);
extern void copy_matrix_rotation(void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern unsigned char *effect_create_timed(void *, void *, int, int, int, int, int, float);
extern int coll_cast_object_line(void *, void *, void *, int, int, int, int, float, float);
extern float FastAddRotations(float, float);
extern int g_hero_mode;

/* the level's object-handle table entry: 0x100 bytes, indexed by the handle */
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

/* what an entry points at; only the queue flag and its sound handle are named here */
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

/* the 16-byte block at Ent+0x10 the driver works on */
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
} Quad;

typedef int V4 __attribute__((mode(TI)));

/* a sub-object hung off Ent::f24 */
typedef struct {
    u8  pad00[0x24];
    f32 f24;
} Sub24;

extern s32 func_2F9A60();
extern int func_2F9A90();
extern void func_328A38(s32, s32);
extern s32 func_327898(s32, s32);
extern s32 func_2EA300(void *, void *, s32, s32, s32);
extern void func_3347E0(Ent *, void *, s32, s32, f32);
extern s32 func_3357E8(Ent *, void *, s32);
extern void func_329EC0(Ent *, f32);
extern f32 func_3278F0(f32, f32);
extern f32 func_2FA3C8(f32);
extern f32 func_2FA3E0(f32);
extern void func_2F9DF0(void *, void *, void *);
extern void func_2F9E20(void *, void *, void *);
extern void func_2FA0B8(void *, void *, f32);
extern void sandfly_pick_flight_target(Ent *);
extern f32 g_ground_height_result;
extern f32 g_hero_height_limit;
extern char g_hero_position[];

extern f32 coll_find_ground_height(Quad *, f32, f32, f32, f32);
extern void vehicle_compute_height_limits(Ent *);
extern void sandfly_release_sounds(Ent *);

/* func_L08_003D8348 is defined in L08_003D8348-init.c. */

/* the entry's sound handle and both of the moby's own handles are released */
/* Stops the sounds this creature is playing and marks it as finished. */
void crawler_release_sounds(Ent *moby)
{
    Moby *vars = moby->f68;
    s32 done, second_handle;

    if (moby->f21 != 0xFF) func_328A38(moby->f21, 1);
    if (vars->f484 != -1) func_328A38(vars->f484, 1);
    second_handle = vars->f488;
    done = 1;
    if (second_handle == -1) {
        done = 1;
    } else {
        func_328A38(vars->f484, 1);
        done = 1;
    }
    moby->fBC = done;
}

/* func_L08_003D8AB0 uses -fno-gcse in L08_003D8AB0.c. */

/* func_L08_003D8CA8 is matched in its own unit, src/levels/08_tabora/L08_003D8CA8.c (-g). */

extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern int math_fast_float_d(void *);
extern float math_random_float_range(float, float);
extern float vec_distance_xy(void *, void *);
extern int moby_turn_toward_target_and_step(u8 *, void *, float);
extern float FastVecLength(void *);
extern float math_fabs(float);

/* Walks the Spitting Dune Crawler toward its goal at the given speed and turn rate, switches its wobble now and then, and sets its animation speed from how fast it moves. */
int crawler_move_toward_goal(u8 *object, float accel, float unused1, float damping,
                     float speed, float unused4, float turn, float friction) {
    u8 *state = *(u8 **)(object + 0x68);
    int result;
    float amount;

    moby_set_controller_speed_limits(object, speed * 0.00027777778450399637f,
                  turn * 0.01666666753590107f,
                  accel * 4.848137450608192e-06f,
                  damping * 0.0002908882452175021f);
    *(float *)(state + 0x154) = friction;
    if (math_fast_float_d(state + 0x474) != 0) {
        *(float *)(state + 0x46C) = -*(float *)(state + 0x46C);
        *(float *)(state + 0x470) = *(float *)(state + 0x46C) * 0.01745329424738884f;
        *(int *)(state + 0x474) = math_random_float_range(30.0f, 90.0f);
    }
    if (*(int *)(state + 0x48C) != 0 ||
        (object[0x20] == 8 && object[0x95] != 0) ||
        vec_distance_xy(object + 0x10, state + 0x3F0) < 5.0f)
        *(float *)(state + 0x470) = 0;
    result = moby_turn_toward_target_and_step(object, state + 0x3F0, *(float *)(state + 0x470));
    amount = FastVecLength(state + 0x1C0);
    amount += math_fabs(*(float *)(state + 0x1D4));
    if (result & 15) {
        math_fast_float_d(state + 0x448);
        amount = math_fabs(*(float *)(state + 0x1D4)) + 0.010000000707805157f;
    }
    *(float *)(object + 0x48) = amount * 29.999998092651367f;
    if (*(float *)(object + 0x48) > 1.5f)
        *(float *)(object + 0x48) = 1.5f;
    else if (*(float *)(object + 0x48) < 0.0f)
        *(float *)(object + 0x48) = 0;
    return result;
}

/* the countdown runs while the entry is flagged, then the timer field saturates */
/* Counts down the crawler's timers and ages it by one frame. */
void crawler_tick_timers(Ent *moby)
{
    Moby *vars = moby->f68;
    u16 age;

    if (moby->fBC != 0) {
        moby->fBC = 0;
        if (vars->f448 < 200) {
            vars->f448 = func_327898(300, 360);
            vars->f40E = 12;
        }
    }
    age = moby->f96;
    if (vars->f254 == 2) {
        if (func_2F9A60(&vars->f448)) vars->f40E = 3;
    }
    age = moby->f96;
    if (age <= 0xFFFDu) moby->f96 = age + 1;
    if (moby->f20 == 8) {
        if (moby->f95 == 0) func_2F9A60(&vars->f48C);
    }
    func_2F9A60(&vars->f440);
    func_2F9A60(&vars->f44C);
}

typedef struct {
    int mode;
    char pad4[8];
    int active;
    char pad10[0x18];
    float lower;
    char pad2C[12];
    float upper;
} HeightGate;
typedef struct {
    u8 pad0[0x80];
    V4 position;
    u8 pad90[0x40];
    V4 other;
    u8 padE0[0x21B0];
    int handle;
} HeroTarget;
extern HeroTarget g_hero_state;
extern HeightGate g_init_context;
extern char g_collision_aim_vector[];
extern int GetCollHitMaterial(void);
extern void moby_update_ground_check(void *);
extern void moby_store_ground_height(void *);
extern void euler_to_matrix(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern float mat_fast_helper_a(float, float);
/* EE ABI interleaving of (f32 *, f32 *, s32, f32, f32, f32, f32): each bank keeps its order. */
extern float math_approach_target_with_direction_mode(void *, void *, float, float, float, float, int);
extern float fast_subtract_rotations(float, float);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern void matrix_mul_vec3(void *, void *, void *);

/* Handles hits on the Spitting Dune Crawler and turns its body and three joints to face the hero. */
void crawler_update_hits_aim(u8 *object)
{
    float point[4], angles[4], matrix[16], inverse[16], other[16];
    char *state = *(char **)(object + 0x68);
    float yaw, pitch, target;
    float pointX, pointY;
    float *pitchAngle, *rollAngle;
    int hit;

    if (g_init_context.active) {
        if (*(float *)(object + 0x18) < g_init_context.lower && g_init_context.mode == 1) return;
        if (g_init_context.lower < *(float *)(object + 0x18) && g_init_context.mode == 0) return;
        if (g_init_context.active == 2) {
            if (g_init_context.upper < *(float *)(object + 0x18) && g_init_context.mode == 1) return;
            if (*(float *)(object + 0x18) < g_init_context.upper && g_init_context.mode == 2) return;
        }
    }
    if (object[0x31] && fast_vec_dist(object + 0x10, g_hero_position_vec) < 24.0f) {
        moby_update_ground_check(object);
        object[0x6F] = 22;
    }
    moby_store_ground_height(object);
    if (*(float *)(object + 0x18) < *(float *)(state + 0x434) + 0.12f) {
        if (GetCollHitMaterial() == 1 || GetCollHitMaterial() == 11) {
            *(int *)(state + 0x20) = 0;
            object[0x20] = 11;
            return;
        }
    }
    *(float *)(object + 0x2C) +=
        (*(float *)(*(char **)(object + 0x24) + 0x24) * 1.7f - *(float *)(object + 0x2C)) * 0.05f;
    hit = func_3357E8((Ent *)object, state + 0x50, 0);
    if (hit) {
        if (hit == 5) *(int *)(state + 0xE0) = 0;
        *(int *)(state + 0x48C) = 240;
        crawler_release_sounds((Ent *)object);
    }
    if (object[0x20] < 9 && object[0x20] != 4) {
        pitchAngle = (float *)(object + 0xF4);
        rollAngle = (float *)(object + 0xF0);
        *(V4 *)angles = 0;
        angles[2] = *(float *)(object + 0xF8);
        *(V4 *)point = *(V4 *)angles;
        euler_to_matrix(matrix, point);
        matrix_from_basis_rows(inverse, matrix);
        matrix_from_basis_rows(other, object + 0xC0);
        coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
        func_2FA0B8(angles, g_collision_aim_vector, 1.0f);
        matrix_mul_vec3(angles, angles, inverse);
        target = mat_fast_helper_a(angles[2], angles[0]);
        math_approach_target_with_direction_mode(pitchAngle, state + 0x460, target, 0.0017453294713050127f,
                      0.0017453294713050127f, 0.10471977293491364f, 0);
        target = -mat_fast_helper_a(angles[2], angles[1]);
        math_approach_target_with_direction_mode(rollAngle, state + 0x464, target, 0.0017453294713050127f,
                      0.0017453294713050127f, 0.10471977293491364f, 0);
    }
    if (object[0x20] == 8 && !object[0x95]) {
        moby_transform_joint_to_world(object, 1, point);
        if (*(int *)(state + 0x250) == g_hero_state.handle) {
            qcopy(state + 0x210, &g_hero_state.position);
            qcopy(state + 0x230, &g_hero_state.other);
        }
        pointY = point[1];
        pointX = point[0];
        yaw = mat_fast_helper_a(*(float *)(state + 0x230) - pointX, *(float *)(state + 0x234) - pointY);
        pitch = mat_fast_helper_a(vec_distance_xy(point, state + 0x230), *(float *)(state + 0x238) - point[2]);
        yaw = fast_subtract_rotations(yaw, *(float *)(object + 0xF8)) * 0.5f;
        pitch = fast_subtract_rotations(-pitch, *(float *)(object + 0xF4)) * 0.3333333432674408f;
        {
            int i;
            for (i = 0; i < 3; i++) {
                *(float *)(state + 0x2C8 + i * 0x80) = yaw;
                if (yaw > 0.523598849773407f) *(float *)(state + 0x2C8 + i * 0x80) = 0.523598849773407f;
                else if (yaw < -0.523598849773407f) *(float *)(state + 0x2C8 + i * 0x80) = -0.523598849773407f;
                *(float *)(state + 0x2C4 + i * 0x80) = pitch;
            }
        }
    } else {
        int i;
        for (i = 0; i < 3; i++) {
            *(float *)(state + 0x2C0 + i * 0x80) = 0;
            *(float *)(state + 0x2C4 + i * 0x80) = 0;
        }
    }
    {
        int i;
        for (i = 0; i < 3; i++) moby_update_eased_node(object, state + 0x260 + i * 0x80, 3, 0.02f, 0.4f);
    }
}

/* Makes the Spitting Dune Crawler's spit attack: a flash in front of it and two sprays of particles. */
void crawler_spawn_spit_effect(char *object)
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
        velocity[0]=math_fast_sin_or_cos_a(heading)*0.28333336114883423f;
        velocity[1]=math_fast_sin_or_cos_b(heading)*0.28333336114883423f;
        velocity[2]=0;
        velocity[2]=math_random_float_range(0,0);
        angle=math_random_float_range(-90,90)*0.01745329424738884f;
        accel[0]=math_fast_sin_or_cos_a(FastAddRotations(heading,angle))*0.008333333767950535f;
        accel[1]=math_fast_sin_or_cos_b(FastAddRotations(heading,angle))*0.008333333767950535f;
        accel[2]=0;
        accel[2]=math_random_float_range(0.015000000596046448f,0.01833333447575569f);
        a=FloatToInt(math_random_float_range(2,4));
        b=FloatToInt(math_random_float_range(12,14.40000057220459f));
        c=FloatToInt(math_random_float_range(200,240.00001525878906f));
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
        velocity[0]=math_fast_sin_or_cos_a(FastAddRotations(heading,angle))*0.20000001788139343f;
        velocity[1]=math_fast_sin_or_cos_b(FastAddRotations(heading,angle))*0.20000001788139343f;
        velocity[2]=0;
        velocity[2]=math_random_float_range(0,0);
        angle=math_random_float_range(-90,90)*0.01745329424738884f;
        accel[0]=math_fast_sin_or_cos_a(FastAddRotations(heading,angle))*0.008333333767950535f;
        accel[1]=math_fast_sin_or_cos_b(FastAddRotations(heading,angle))*0.008333333767950535f;
        accel[2]=0;
        accel[2]=math_random_float_range(0.011666666716337204f,0.02500000223517418f);
        a=FloatToInt(math_random_float_range(2,4));
        b=FloatToInt(math_random_float_range(20,24));
        c=FloatToInt(math_random_float_range(200,240.00001525878906f));
        particle=part_spawn_trail(position,velocity,accel,0x801010FF,0x801010FF,a,b,c,-1);
        if(particle && (func_001163B0()&1)) particle[3]=0x48;
    }
    }
}


/* func_L08_003D9F68 is defined in L08_003D9F68-g8.c. */

/* func_L08_003F6D30 is defined in L08_003F6D30-g8.c. */

/* func_L08_003F6E18 is defined in L08_003F6E18-g8.c. */




extern u32 g_far_target_flag;

/* 128-bit copies reach lq/sq only through TImode. */
typedef int TQ_003F79E0 __attribute__((mode(TI)));

/* func_L08_003F79E0 is defined in L08_003F79E0-qcopy-barrier.c. */

/* Projects the flare object to the screen and draws its 12 sprites along the line
   through the screen centre, faded by distance and by how far off-centre it is
   (RAC1 draw_lens_flare). The base size is read through a pointer: retail
   rematerializes its address inside the loop. */
void gfx_l08_draw_lens_flare(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    f32 scr[4], ctr[4], d[4], off[4], at[4];
    f32 dist, fade, fx, fy, half;
    int i, size, rgba, x, y;
    long long tex;
    int *base_size;

    if (g_lens_flare_2.state != 1 || (g_lens_flare_2.moby->flags & 0x80)) {
        g_lens_flare_2.state = 0;
        return;
    }
    if (g_lens_flare_2.intensity <= 0.0f)
        return;
    dist = fast_vec_dist(g_hero_position_vec, vars + 0x10);
    ctr[0] = IntToFloat(g_screen_width.half_width);
    ctr[1] = IntToFloat(g_screen_width.half_height);
    base_size = &g_lens_l08_flare_base_size;
    gfx_project_world_point_to_screen(scr, vars + 0x10);
    scr[0] = (scr[0] - IntToFloat(g_screen_width.left)) * 0.0625f;
    scr[1] = (scr[1] - IntToFloat(g_screen_width.top)) * 0.0625f;
    d[0] = ctr[0] - scr[0];
    d[1] = ctr[1] - scr[1];
    for (i = 0; i < 12; i++) {
        tex = GetEffectTextureDescriptor(g_lens_flare_2.tex[i] + 0x45);
        off[0] = d[0] * g_lens_flare_2.dist[i];
        off[1] = d[1] * g_lens_flare_2.dist[i];
        at[0] = ctr[0] + off[0];
        at[1] = ctr[1] + off[1];
        fade = dist - 5.0f;
        if (fade > 1.0f)
            fade = 1.0f;
        else if (fade < 0.0f)
            fade = 0.0f;
        fx = math_fabs(d[0]) / ctr[0] * -5.0f + 5.5f;
        if (fx > 1.0f)
            fx = 1.0f;
        else if (fx < 0.0f)
            fx = 0.0f;
        fy = math_fabs(d[1]) / ctr[1] * -5.0f + 5.5f;
        if (fy > 1.0f)
            fy = 1.0f;
        else if (fy < 0.0f)
            fy = 0.0f;
        fade *= fx * fy * g_lens_flare_2.intensity;
        rgba = (FloatToInt(fade * g_lens_flare_2.alpha[i]) << 24) | (g_lens_flare_2.color[i] & 0xFFFFFF);
        size = FloatToInt(*base_size * g_lens_flare_2.scale[i]);
        VU1_addGSregister(0x42, 0x8000000048LL);
        half = size >> 1;
        x = FloatToInt(at[0] - half);
        y = FloatToInt(at[1] - half);
        DrawTexturedQuad(x, y, size, size, 0, 0, 0x40, 0x40, rgba, tex);
    }
    g_lens_flare_2.intensity = 0.0f;
}


extern void moby_set_state(void *, s32, s32);
extern u8 g_inventory_have_flags[] __attribute__((sda));
extern u8 g_request_l08_queue[];
extern s32 g_cutscene_l08_active_flag[] __attribute__((sda));
extern s32 g_glider_flag_table[] __attribute__((sda));
extern u8 *g_collision_box_table[] __attribute__((sda));
extern s32 IsPointInCuboid(void *, s32);
extern s32 req_push_queue(void *, s32);
extern s32 req_launch_queued(void *);
extern void part_spawn_sparkles_and_glow_rings(u8 *);
extern s32 game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(u8 *, u8 *, s32, s32);
extern void help_unlock_entry(s32);
extern void value_set_entry_by_index(s32, s32);
extern int MemcardSave(s32, s32);

/* Updates the Glider moby (class 3675): it rises into place, turns slowly, and when the hero is near it plays a sound and removes itself. */
void glider_update(u8 *self) {
    u8 *vars = *(u8 **)(self + 0x68);
    u8 *entry;

    switch (self[0x20]) {
    case 0:
        if (g_inventory_have_flags[13] != 0) {
            moby_mark_spawned(self);
            break;
        }
        *(float *)(self + 0x18) = *(float *)(self + 0x18) + 0.75f;
        *(float *)(self + 0x2C) = *(float *)(*(u8 **)(self + 0x24) + 0x24) * 1.5f;
        moby_set_state(self, 1, -1);
        break;
    case 1:
        *(float *)(self + 0xF8) = FastAddRotations(*(float *)(self + 0xF8), 0.07853982597589493f);
        if (IsPointInCuboid(g_hero_position, *(s32 *)(vars + 4)) != 0) {
            if (req_push_queue(g_request_l08_queue, 0x5B) != 0) {
                req_launch_queued(g_request_l08_queue);
                self[0x20] = 2;
            }
        }
        if (self[0x31] != 0)
            part_spawn_sparkles_and_glow_rings(self);
        break;
    case 2:
        g_glider_flag_table[10] = 1;
        if (g_cutscene_l08_active_flag[0] == 2) {
            self[0x31] = 0;
            *(u16 *)(self + 0x34) |= 1;
        }
        if (game_is_either_mode_two() != 0)
            break;
        g_glider_flag_table[10] = 0;
        self[0x31] = 1;
        entry = g_collision_box_table[0];
        *(u16 *)(self + 0x34) &= 0xFFFE;
        entry += *(s32 *)(vars + 8) * 0x80;
        hero_reset_position_and_direction(entry + 0x30, entry + 0x70, 0, 1);
        help_unlock_entry(0x15);
        value_set_entry_by_index(0x122B, -1);
        MemcardSave(0, -1);
        moby_mark_spawned(self);
        break;
    }
}

/* func_L08_0040F9D0 is matched in its own unit, src/levels/shared/L08_0040F9D0-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* Moves a thrown object by its speed, bounces it off walls, carries its mount along, and removes it when it stops or leaves the level. */
void thrown_l08_object_update(char *object)
{
    float position[4];
    char *state = *(char **)(object + 0x68);
    char *mount;
    int hit;

    FastVecAdd(position, object + 0x10, state);
    hit = CollLine(object + 0x10, position, 0, *(void **)(state + 0x18), 0);
    if (!hit) {
        position[2] += 0.3f;
        hit = coll_test_point(position, 0, *(void **)(state + 0x18), 0.3f);
        position[2] -= 0.3f;
    } else {
        qcopy(g_collision_l08_result.adjusted, g_collision_l08_result.hit);
        g_collision_l08_result.adjusted[2] += 0.3f;
    }
    if (hit) {
        qcopy(object + 0x10, g_collision_l08_result.adjusted);
        *(float *)(object + 0x18) -= 0.3f;
        vec_fast_normalize(state, state, g_collision_l08_result.normal);
        FastVecScale(state, state, 0.75f);
        if (FastVecLength(state) < 0.01f) {
            moby_mark_spawned(object);
            return;
        }
    } else {
        qcopy_nc(object + 0x10, position);
    }
    *(float *)(state + 8) -= *(float *)(state + 0x10);
    *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4), *(float *)(state + 0x14));
    mount = *(char **)(state + 0x1C);
    if (!mount || *(short *)(mount + 0xAA) != 0x326 /* moby class 806 */ ||
        (unsigned char)mount[0x20] == 0xFE || (unsigned char)mount[0x20] == 0xFD ||
        *(float *)(object + 0x10) < 2 || *(float *)(object + 0x10) > 1021 ||
        *(float *)(object + 0x14) < 2 || *(float *)(object + 0x14) > 1021 ||
        *(float *)(object + 0x18) < 2 || *(float *)(object + 0x18) > 1021) {
        moby_mark_spawned(object);
        return;
    }
    qcopy_nc(mount + 0x10, object + 0x10);
    qcopy_nc(mount + 0xF0, object + 0xF0);
}


extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int FloatToInt(float);
extern char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);

/* Sprays a ring of dust puffs around a point, flying outward and upward. */
void part_spawn_dust_burst(char *moby, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4];
    int fade_in, hold, fade_out;
    char *particle;

    {
        int i;
        for (i = 0; i < count; i++) {
            float x, y;
            x = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * math_random_float_range(minRadius, maxRadius);
            y = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            y *= math_random_float_range(minRadius, maxRadius);
            offset[1] = y;
            offset[2] = 0;
            matrix_mul_vec3(offset, offset, moby + 0xC0);
            {
                float range = speed * ((maxRadius - FastVecLength(offset)) * 0.01666666753590107f) / maxRadius;
                vec_scale_to_length(velocity, offset, math_random_float_range(range * 0.25f, range));
            }
            velocity[2] += math_random_float_range(rise * 0.25f, rise) * 0.01666666753590107f;
            qzero_nc(accel);
            FastVecAdd(offset, offset, position);
            velocity[3] = size;
            accel[3] = endSize;
            fade_in = FloatToInt(math_random_float_range(15.0f, 25.0f));
            hold = FloatToInt(math_random_float_range(20.0f, 40.0f));
            fade_out = FloatToInt(math_random_float_range(30.0f, 60.0f));
            particle = part_spawn_trail(offset, velocity, accel, 0x50204050, 0x7F7F7F, fade_in, hold, fade_out, -1);
            if (particle && (func_001163B0() & 1))
                particle[3] = 0x48;
        }
    }
}


extern f32 math_random_angle(void);
extern s32 math_random_int_range(s32, s32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern void FastVecAdd(void *, void *, void *);
extern void *part_l01_spawn_glow(void *, int, int, float, float, int);

/* five rounds: each picks a direction, two spreads and a life time */
/* Drops five small sparkles around the creature that float up from the ground. */
void part_spawn_ground_sparkles(Ent *moby)
{
    Moby *vars = moby->f68;
    f32 position[4];
    f32 angle, radius, first, second;
    int life, i;

    for (i = 4; i >= 0; i--) {
        angle = math_random_angle();
        radius = math_random_float_range(0.0f, 0.8f);
        first = math_random_float_range(0.0f, 1.5f);
        second = math_random_float_range(1.5f, 5.7f);
        life = math_random_int_range(100, 180);
        position[0] = math_fast_sin_or_cos_a(angle) * radius;
        position[1] = math_fast_sin_or_cos_b(angle) * radius;
        position[2] = 0.0f;
        FastVecAdd(position, position, (char *)moby + 0x10);
        position[2] = vars->f1B0 + 0.025f;
        part_l01_spawn_glow(position, 0x38002028, 0x2020, first, second, life);
    }
}




/* the entry's own two handles and its sound handle are released */
/* Stops the sounds this creature is playing and marks it as finished. */
void sandfly_release_sounds(Ent *moby)
{
    Moby *vars = moby->f68;
    s32 done, second_handle;

    if (moby->f21 != 0xFF) func_328A38(moby->f21, 1);
    if (vars->f1D8 != -1) func_328A38(vars->f1D8, 1);
    second_handle = vars->f1DC;
    done = 1;
    if (second_handle == -1) {
        done = 1;
    } else {
        func_328A38(vars->f1D8, 1);
        done = 1;
    }
    moby->fBC = done;
}

/* the queued sound of the entry is released and the flag cleared */
/* Stops the creature's queued sound and clears its flag. */
void snd_stop_queued(Ent *moby)
{
    Moby *vars = moby->f68;

    if (vars->f18C != 0) {
        func_2F9A60(vars->f1CC);
        vars->f18C = 0;
    }
}

extern char g_collision_l08_hit_point[];
extern void FastVecSub(void *, void *, void *);
extern char *g_path_segment_list;
extern char *g_moby_array[] __attribute__((sda));
extern s32 math_closest_point_on_polygon_edge(void *, void *, void *, int);
extern int coll_test_point_against_shapes(void *, int, int, int, int);
extern float coll_probe_ground_height_below(void *, int, float);

/* Picks the next point the sandfly flies to: near a friend or the hero, or at random, pushed away from walls. */
void sandfly_pick_flight_target(Ent *object) {
    char *state = object->f68;

    if (!coll_test_point_against_shapes(state + 0x160, *(int *)(state + 0x1A8), -1, -1, -1)) {
        if ((func_001163B0() & 1) || *(int *)(state + 0x144) == 2 || *(short *)(state + 0x1BC)) {
            if (*(int *)(state + 0x184) == -1 || (func_001163B0() & 1)) {
                qcopy(state + 0x160, state + 0x150);
            } else {
                *(float *)(state + 0x160) = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927f, 3.1415927f)) * 3.0f;
                {
                    float y = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927f, 3.1415927f)) * 3.0f;
                    int handle = *(int *)(state + 0x184);
                    char *entry = g_moby_array[0];
                    *(float *)(state + 0x168) = 0;
                    *(float *)(state + 0x164) = y;
                    FastVecAdd(state + 0x160, state + 0x160, entry + (handle << 8) + 0x10);
                }
            }
            *(float *)(state + 0x168) += 1.7f;
        } else {
            *(float *)(state + 0x160) = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927f, 3.1415927f)) * 1.2f;
            {
                float y = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927f, 3.1415927f)) * 1.2f;
                *(float *)(state + 0x168) = 0;
                *(float *)(state + 0x164) = y;
                FastVecAdd(state + 0x160, state + 0x160, g_hero_position);
            }
            *(float *)(state + 0x168) += 1.7f;
        }
        if (*(short *)(state + 0x1BC) && vec_distance_xy(state + 0x160, g_hero_position) < 3.0f) {
            float offset = math_random_float_range(3.0f, 5.0f);
            float value = *(float *)(state + 0x160);
            *(float *)(state + 0x160) = (func_001163B0() & 1) ? value - offset : value + offset;
            offset = math_random_float_range(3.0f, 5.0f);
            value = *(float *)(state + 0x164);
            *(float *)(state + 0x164) = (func_001163B0() & 1) ? value - offset : value + offset;
        }
    } else if (*(int *)(state + 0x1A8) == -1) {
        math_closest_point_on_polygon_edge(state + 0x160, state + 0x160, g_path_segment_list + 0x10, *(int *)g_path_segment_list);
    }
    if (CollLine((char *)object + 0x10, state + 0x160, 2, object, 0)) {
        FastVecSub(state + 0x160, g_collision_l08_hit_point, state + 0x160);
        vec_scale_to_length(state + 0x160, state + 0x160, 2.0f);
        FastVecAdd(state + 0x160, state + 0x160, g_collision_l08_hit_point);
    }
    *(float *)(state + 0x168) = coll_probe_ground_height_below(state + 0x160, 0, 4.0f) + 1.7f;
}

/* the swing angle is folded into the moby's frame and the subobject is ticked */
/* Picks a random spot around the sandfly (kept away from the hero), then picks its final flight point. */
void sandfly_pick_random_target(Ent *moby)
{
    Moby *vars = moby->f68;
    Quad local;
    f32 min_angle = -3.1415927f;
    f32 max_angle = 3.1415927f;
    f32 angle;

    angle = func_3278F0(min_angle, max_angle);
    vars->f160 = func_2FA3C8(angle) * (f32)vars->f189;
    angle = func_3278F0(min_angle, max_angle);
    vars->f164 = func_2FA3E0(angle) * (f32)vars->f189;
    vars->f168 = 0.0f;
    func_2F9DF0((char *)vars + 0x160, (char *)vars + 0x160, (char *)vars + 0x150);
    vars->f168 = vars->f168 + 1.7f;
    if (vars->f1BC != 0) {
        func_2F9E20(&local, (char *)vars + 0x160, (void *)g_hero_position);
        *(s32 *)((char *)&local + 8) = 0;
        func_2FA0B8(&local, &local, 8.0f);
        func_2F9DF0((char *)vars + 0x160, (char *)vars + 0x160, &local);
    }
    sandfly_pick_flight_target(moby);
}

/* func_L08_00423010 is in its own unit. */

/* func_L08_004233E0 is defined in L08_004233E0-init.c. */

/* func_L08_004237F0 is matched in its own unit, src/levels/08_tabora/L08_004237F0.c (default flags). */

/* the driver is primed, the entry follows its mount and then its own update runs */
/* Checks the sandfly for hits: when it is hurt a timer starts or it begins to die, and its sounds are stopped. */
void sandfly_check_hit(Ent *moby)
{
    Moby *vars = moby->f68;
    Sub24 *sub;
    f32 half_size;
    s32 hit_result;

    func_3347E0(moby, vars->f1E0, 2, 1, 2.5f);
    vehicle_compute_height_limits(moby);
    sub = moby->f24;
    half_size = sub->f24 * 0.5f;
    moby->f2C = half_size;
    hit_result = func_3357E8(moby, vars->f50, 0);
    if (hit_result != 0) {
        if (vars->f20 <= 0.0f) {
            vars->f88 |= 2;
            vars->fE4 = 0.8377582f;
        } else {
            vars->f1BE = 330;
        }
        snd_stop_queued(moby);
        sandfly_release_sounds(moby);
    }
}
