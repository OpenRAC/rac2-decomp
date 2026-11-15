#include "common.h"

extern float FastAddRotations(float, float);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_sin_or_cos_b(float);

extern void render_water_grids(char *, s32);

extern char D_L18_002A9C40[];

extern float g_camera_l18_position[];

extern float math_random_float_range(float, float);

extern void moby_transform_joint_to_world(void *, int, void *);

extern void FastVecSub(float *, const float *, const float *);

extern void vec_scale_to_length(char *, char *, float);

extern void FastVecAdd(char *, char *, char *);

extern int math_random_int_range(int, int);

extern float math_random_angle(void);

extern int D_L18_001C9D40;

extern void gfx_draw_aimed_effect_packet(void *, int, float, int, float, int, int);

extern s32 snd_is_voice_playing_for_owner(void *, s32);

extern s32 PlayMobySound(s32, s32, void *);

extern void *part_find_owned_effect_slot(void *, s32, s32);

extern float moby_update_aim_target_strength(void *, void *);

extern void gfx_start_color_fade(void *, void *);

extern void gfx_update_color_fade(void *, void *);

extern void moby_set_state(void *, int, int);


extern int FloatToInt(float);
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern void moby_mark_spawned(void *);
extern void cam_mode_noop(void *);
extern void part_spawn_masked_debris(void *, int, void *, float, float, float, float, int);
extern void SetDeathBits(void *, int, int);
extern char g_sound_state[], g_hero_position[];
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern int func_001163B0(void);
extern void FastVecScale(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern u8 *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } RibbonVector;
struct RibbonQuad { RibbonVector position[4]; u32 color[4]; float uv[4][2]; u64 clear, texture, giftag, flags; };
extern unsigned long GetEffectTextureDescriptor(int);
extern void effect_reset_record(void *);
extern void FastVecCross(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);

/* Runs the shared effect routine with this level's effect data. It is handed to the effect controller as a callback. */
void part_effect_callback(void) {
    render_water_grids(D_L18_002A9C40, 0x12);
}

/* Updates the two lightning arcs of the Extermibot beam: it eases their angles toward the targets and works out the sideways offsets. */
void extermibot_update_arc_offsets(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 i;
    for (i = 0; i < 2; i++) {
        u8 *p = &state[i * 0xA0 + 0x610];
        s32 j;
        for (j = 1; j >= 0; j--) {
            float x;
            *(float *)(p + 0x40) = FastAddRotations(*(float *)(p + 0x40), *(float *)(p + 0x60));
            *(float *)(p + 0x44) = FastAddRotations(*(float *)(p + 0x44), *(float *)(p + 0x64));
            *(float *)(p + 0x48) = FastAddRotations(*(float *)(p + 0x48), *(float *)(p + 0x68));
            x = math_fast_sin_or_cos_a(*(float *)(p + 0x40));
            *(float *)(p + 0x20) = x * *(float *)(p + 0x80);
            *(float *)(p + 0x24) = math_fast_sin_or_cos_b(*(float *)(p + 0x44)) * *(float *)(p + 0x84);
            *(float *)(p + 0x28) = -math_fast_sin_or_cos_b(*(float *)(p + 0x48)) * *(float *)(p + 0x88);
            p += 0x10;
        }
    }
}

extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(float *, const float *, const float *);
extern void FastVecAdd(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern char g_sound_state[];

#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern void vec_random_direction(void *,float,float);
extern float IntToFloat(int);
extern int snd_is_voice_playing_for_owner(void *,int),PlayMobySound(int,int,void *);
extern void snd_stop_voice(int);
extern int coll_sweep_from_object(void *,void *,int,int,int,int,float,float,float);
extern void make_hit_descriptor(void *,void *,int,void *,float);

extern int CollLine(void *,void *,int,void *,void *);
extern void part_spawn_large_spark_smoke(char *,int);

extern struct { u8 pad[24];u8 *object;u8 pad1[4];float position[4] __attribute__((aligned(16))); } D_L18_001BFC00;
extern int D_L18_001B2348 __attribute__((sda));
typedef struct {
 u8 pad[0x7e4]; u8 *attached; u8 gap[0x1c]; s16 timer, mode;
} DamoselBeamState;
/* Runs the Extermibot's electric beam: it charges, shoots out to the target, sticks to what it hits, and then pulls back. It also throws sparks where the beam lands. */
void extermibot_beam_update(u8 *obj) {
 float startPoint[4] __attribute__((aligned(16))),endPoint[4] __attribute__((aligned(16))),delta[4] __attribute__((aligned(16)));
 struct { float direction[4] __attribute__((aligned(16))); int owner,mode; u8 type,flags;u16 id; float distance;int enabled; } hit;
 u8 *vars=P(obj,0x68),*other;float progress;
 moby_transform_joint_to_world(P(vars,0x7c8),0,startPoint);moby_transform_joint_to_world(P(vars,0x7c8),1,endPoint);F(vars,0x7e0)=0;
 switch(H(vars,0x806)) {
 case 0:
  qcopy(vars+0x610,startPoint);qcopy(vars+0x620,endPoint);qcopy(vars+0x6b0,endPoint);qcopy(vars+0x6c0,startPoint);
  if(I(vars,0x7f0)!=-1) {
   u8 *entry=g_sound_state+I(vars,0x7f0)*0x70;
   if(P(entry,0x88)==obj && entry[0x74])snd_stop_voice(I(vars,0x7f0));
  }
  I(vars,0x7f0)=-1;break;
 case 1:
  qcopy(vars+0x610,startPoint);qcopy(vars+0x620,endPoint);qcopy(vars+0x6b0,endPoint);qcopy(vars+0x6c0,startPoint);
  coll_sweep_from_object(obj,startPoint,0x10001,0,1,0,0.2f,(float)vars[0x34],1);
  if(H(vars,0x804)>=6) {
   u8 *target=vars+0x760;
   u8 *p3=vars+0x6a0,*p2=vars+0x690,*p1=vars+0x680,*p0=vars+0x670;
   int i;
   for(i=1;i>=0;i--) {
    vec_random_direction(p0,0.232710599899292f,0.290888249874115f);
    vec_random_direction(p1,0.232710599899292f,0.290888249874115f);
    vec_random_direction(p2,2,5);vec_random_direction(p3,2,5);
    p0+=0xa0;p1+=0xa0;p2+=0xa0;p3+=0xa0;
   }
   H(vars,0x804)=0;H(vars,0x806)=2;
   if(!snd_is_voice_playing_for_owner(obj,I(vars,0x7f0)))I(vars,0x7f0)=PlayMobySound(1,4,obj);
   if(P(vars,0x7bc))qcopy(target,P(vars,0x7bc)+0x10);else qcopy(target,vars+0x1f0);
  } else F(vars,0x7e0)=IntToFloat(H(vars,0x804))/IntToFloat(5);
  break;
 case 2:
  qcopy(vars+0x610,startPoint);qcopy(vars+0x6b0,endPoint);
  coll_sweep_from_object(obj,startPoint,0x10001,0,1,0,0.2f,(float)vars[0x34],1);
  if(H(vars,0x804)<6) {
   progress=IntToFloat(H(vars,0x804))/IntToFloat(5);
   F(vars,0x620)=startPoint[0]+(F(vars,0x760)-startPoint[0])*progress;
   F(vars,0x624)=startPoint[1]+(F(vars,0x764)-startPoint[1])*progress;
   F(vars,0x628)=startPoint[2]+(F(vars,0x768)-startPoint[2])*progress;
   qcopy(vars+0x6c0,vars+0x620);
   FastVecSub(delta,vars+0x620,vars+0x610);vec_scale_to_length(delta,delta,1.0f/30.0f);
   make_hit_descriptor(&hit,obj,0x210001,delta,(float)vars[0x34]);
   hit.type=5;hit.flags=3;hit.id=*(u16 *)(obj+0xaa);
   if(CollLine(vars+0x610,vars+0x620,0,obj,&hit)) {
    part_spawn_large_spark_smoke(vars+0x620,15);qcopy(vars+0x760,vars+0x620);H(vars,0x804)=0;
    if(D_L18_001BFC00.object) {
     float *point=D_L18_001BFC00.position;
     u8 *attached;
     H(vars,0x806)=3;attached=D_L18_001BFC00.object;P(vars,0x7e4)=attached;
     qcopy(vars+0x620,point);qcopy(vars+0x770,attached+0x10);
    } else H(vars,0x806)=4;
   }
  } else {H(vars,0x806)=4;part_spawn_large_spark_smoke(vars+0x620,10);}
  break;
 case 3:
  qcopy(vars+0x610,startPoint);qcopy(vars+0x6b0,endPoint);
  if(H(vars,0x804)<51 && (other=P(vars,0x7e4)) && other[0x20]!=254 && other[0x20]!=253) {
   FastVecSub(delta,other+0x10,vars+0x770);FastVecAdd(vars+0x620,vars+0x620,delta);
   qcopy(vars+0x6c0,vars+0x620);qcopy(vars+0x770,P(vars,0x7e4)+0x10);
   if((D_L18_001B2348&15)==(((int)obj>>8)&15))part_spawn_large_spark_smoke(vars+0x620,1);
  } else {
   DamoselBeamState *state=(DamoselBeamState *)vars;
   state->attached=0;state->mode=4;state->timer=0;
  }
  break;
 case 4:
  qcopy(vars+0x610,startPoint);qcopy(vars+0x6b0,endPoint);
  if(H(vars,0x804)<5) {
   progress=IntToFloat(H(vars,0x804))/IntToFloat(5);
   F(vars,0x620)=F(vars,0x760)+(startPoint[0]-F(vars,0x760))*progress;
   F(vars,0x624)=F(vars,0x764)+(startPoint[1]-F(vars,0x764))*progress;
   F(vars,0x628)=F(vars,0x768)+(startPoint[2]-F(vars,0x768))*progress;
   F(vars,0x6c0)=F(vars,0x760)+(endPoint[0]-F(vars,0x760))*progress;
   F(vars,0x6c4)=F(vars,0x764)+(endPoint[1]-F(vars,0x764))*progress;
   F(vars,0x6c8)=F(vars,0x768)+(endPoint[2]-F(vars,0x768))*progress;
  } else {
   H(vars,0x804)=0;H(vars,0x806)=0;
   { u8 *p3=vars+0x6a0,*p2=vars+0x690,*p1=vars+0x680,*p0=vars+0x670;
   int i;
   for(i=1;i>=0;i--) {
    vec_random_direction(p0,0.232710599899292f,0.290888249874115f);
    vec_random_direction(p1,0.232710599899292f,0.290888249874115f);
    vec_random_direction(p2,1,1.7f);vec_random_direction(p3,1,1.7f);
    p0+=0xa0;p1+=0xa0;p2+=0xa0;p3+=0xa0;
   } }
  }
 }
 extermibot_update_arc_offsets(obj);
}

#undef F
#undef I
#undef H
#undef P

/* func_L18_00433B70 lives in L18_00433B70.c. */

/* Draws a glowing lightning ribbon along a list of points, as a wide main strip with a thinner inner strip. */
void gfx_l18_draw_lightning_ribbon(RibbonVector *points, int count, int flags, u32 color0, u32 color1, float width, float scale) {
    RibbonVector basis[4];
    struct RibbonQuad mainQuad, innerQuad;
    RibbonVector template0, template1;
    float u, nextU, step;
    int i;
    mainQuad.texture = GetEffectTextureDescriptor(0x2B);
    mainQuad.flags = ((u64)(u32)flags << 32) | 0x68;
    mainQuad.giftag = 0xFF9000000260ULL;
    mainQuad.color[0] = mainQuad.color[1] = mainQuad.color[2] = mainQuad.color[3] = color0;
    mainQuad.clear = 0;
    effect_reset_record(&mainQuad);
    mainQuad.uv[0][0] = 0.0f; mainQuad.uv[0][1] = 0.0f;
    mainQuad.uv[1][0] = 0.0f; mainQuad.uv[1][1] = 1.0f;
    mainQuad.uv[2][0] = 1.0f; mainQuad.uv[2][1] = 0.0f;
    mainQuad.uv[3][0] = 1.0f; mainQuad.uv[3][1] = 1.0f;
    innerQuad.texture = GetEffectTextureDescriptor(0x2B);
    innerQuad.giftag = 0xFF9000000260ULL;
    innerQuad.clear = 0;
    innerQuad.flags = ((u64)(long)(flags / 3) << 32) | 0x68;
    innerQuad.color[0] = innerQuad.color[1] = innerQuad.color[2] = innerQuad.color[3] = color1;
    effect_reset_record(&innerQuad);
    innerQuad.uv[0][0] = 0.0f; innerQuad.uv[0][1] = 0.0f;
    innerQuad.uv[1][0] = 0.0f; innerQuad.uv[1][1] = 1.0f;
    innerQuad.uv[2][0] = 0.33f; innerQuad.uv[2][1] = 0.0f;
    innerQuad.uv[3][0] = 0.33f; innerQuad.uv[3][1] = 1.0f;
    template0.q = 0;
    template1.q = 0;
    template0.f[3] = 1.0f;
    template1.f[3] = 1.0f;
    template0.f[2] = width;
    template1.f[2] = width * scale;
    FastVecSub((float *)&basis[0], (float *)&points[1], (float *)&points[0]);
    vec_scale_to_length((char *)&basis[0], (char *)&basis[0], 1.0f);
    FastVecSub((float *)&basis[1], g_camera_l18_position, (float *)&points[0]);
    FastVecCross(&basis[2], &basis[1], &basis[0]);
    vec_scale_to_length((char *)&basis[2], (char *)&basis[2], 1.0f);
    FastVecCross(&basis[1], &basis[0], &basis[2]);
    qcopy(&basis[3], &points[0]);
    qcopy(&mainQuad.position[0], &template0);
    FastVecScale(&mainQuad.position[1], &mainQuad.position[0], -1.0f);
    transform_vector(&mainQuad.position[0], &mainQuad.position[0], basis);
    transform_vector(&mainQuad.position[1], &mainQuad.position[1], basis);
    qcopy(&innerQuad.position[0], &template1);
    FastVecScale(&innerQuad.position[1], &innerQuad.position[0], -1.0f);
    transform_vector(&innerQuad.position[0], &innerQuad.position[0], basis);
    transform_vector(&innerQuad.position[1], &innerQuad.position[1], basis);
    for (i = 1; i < count - 1; i++) {
        qcopy(&mainQuad.position[2], &template0);
        FastVecScale(&mainQuad.position[3], &mainQuad.position[2], -1.0f);
        qcopy(&innerQuad.position[2], &template1);
        FastVecScale(&innerQuad.position[3], &innerQuad.position[2], -1.0f);
        FastVecSub((float *)&basis[0], (float *)&points[i + 1], (float *)&points[i]);
        vec_scale_to_length((char *)&basis[0], (char *)&basis[0], 1.0f);
        FastVecSub((float *)&basis[1], g_camera_l18_position, (float *)&points[i]);
        FastVecCross(&basis[2], &basis[1], &basis[0]);
        vec_scale_to_length((char *)&basis[2], (char *)&basis[2], 1.0f);
        FastVecCross(&basis[1], &basis[0], &basis[2]);
        qcopy(&basis[3], &points[i]);
        transform_vector(&mainQuad.position[2], &mainQuad.position[2], basis);
        transform_vector(&mainQuad.position[3], &mainQuad.position[3], basis);
        transform_vector(&innerQuad.position[2], &innerQuad.position[2], basis);
        transform_vector(&innerQuad.position[3], &innerQuad.position[3], basis);
        if (i == count - 2) {
            mainQuad.color[2] = 0; mainQuad.color[3] = 0;
            innerQuad.color[2] = 0; innerQuad.color[3] = 0;
        }
        draw_world_quad(&mainQuad, 0, 0);
        draw_world_quad(&innerQuad, 0, 0);
        step = 0.33f;
        u = step * IntToFloat(i);
        nextU = u + step;
        if (u >= 1.0f) {
            u -= 1.0f;
            nextU -= 1.0f;
        }
        innerQuad.uv[0][0] = u; innerQuad.uv[1][0] = u;
        innerQuad.uv[2][0] = nextU; innerQuad.uv[3][0] = nextU;
        qcopy(&mainQuad.position[0], &mainQuad.position[2]);
        qcopy(&mainQuad.position[1], &mainQuad.position[3]);
        qcopy(&innerQuad.position[0], &innerQuad.position[2]);
        qcopy(&innerQuad.position[1], &innerQuad.position[3]);
    }
}

/* Throws a burst of smoke and spark particles outward from a point. */
void part_spawn_large_spark_smoke(char *pos, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    *(TI128 *)axis = 0;
    axis[2] = 1.0f;
    FastVecSub(direction, g_camera_l18_position, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (sign == 0)
            sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        speed = math_random_float_range(0.05f, 3.0f) * (1.0f / 60.0f);
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = math_random_float_range(1.0f, 5.0f) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += math_random_signed_float_range(0.0f, 0.15f);
        point[1] += math_random_signed_float_range(0.0f, 0.15f);
        point[2] += math_random_signed_float_range(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            FastVecScale(velocity, velocity, 1.5f);
            particle = part_spawn_ground_effect(point, 60, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(point, 60, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        } else {
            FastVecSub(extra, g_camera_l18_position, point);
            vec_scale_to_length((char *)extra, (char *)extra, speed);
            FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
            particle = part_spawn_ground_effect(point, 40, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(point, 40, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        }
        if (particle)
            particle[9] = FloatToInt(4.0f) + 0x70;
    }
}

/* Makes a quick glow flash at a moby's position. */
void part_spawn_glow_flash(u8 *obj) {
    float v[4];
    float w[4];
    float a;

    a = math_random_float_range(0.5f, 0.8f);
    moby_transform_joint_to_world(obj, 0, v);
    a = a * 0.5f;
    FastVecSub(w, g_camera_l18_position, v);
    w[2] = 0.0f;
    vec_scale_to_length((char *)w, (char *)w, 0.2f);
    FastVecAdd((char *)v, (char *)v, (char *)w);
    gfx_draw_aimed_effect_packet(v, 0x807070, a, math_random_int_range(0x50, 0x60), math_random_angle(), 0x31, 2);
    gfx_draw_aimed_effect_packet(v, 0x802020, 0.56f, math_random_int_range(0x16, 0x32), math_random_angle(), 0xB, 2);
}

/* Throws a small burst of smoke and spark particles outward from a point; a smaller version of the bigger burst. */
void part_spawn_small_spark_smoke(char *pos, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    *(TI128 *)axis = 0;
    axis[2] = 1.0f;
    FastVecSub(direction, g_camera_l18_position, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (sign == 0)
            sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        speed = math_random_float_range(0.05f, 3.0f) * (1.0f / 60.0f);
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = math_random_float_range(1.0f, 5.0f) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += math_random_signed_float_range(0.0f, 0.15f);
        point[1] += math_random_signed_float_range(0.0f, 0.15f);
        point[2] += math_random_signed_float_range(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            FastVecScale(velocity, velocity, 1.5f);
            particle = part_spawn_ground_effect(point, 60, size * 0.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(point, 60, size * 0.035f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        } else {
            FastVecSub(extra, g_camera_l18_position, point);
            vec_scale_to_length((char *)extra, (char *)extra, speed);
            FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
            particle = part_spawn_ground_effect(point, 40, size * 0.15f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(point, 40, size * 0.105000004f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        }
        if (particle)
            particle[9] = FloatToInt(4.0f) + 0x70;
    }
}

/* func_L18_004354F8 is defined in L18_004354F8-g8.c. */

/* func_L18_00435B10 is defined in L18_00435B10-g8.c. */

/* func_L18_00436B80 is in L18_00433460-f7-g8.c. */

/* func_L18_00437190 is defined in L18_00437190-g8.c. */

/* func_L18_00439960 lives in L18_00437AA0.c. */

extern int D_L18_001C9D40;

extern float FastAddRotations(float, float);

extern s32 snd_is_voice_playing_for_owner(void *, s32);

extern s32 PlayMobySound(s32, s32, void *);

extern void *part_find_owned_effect_slot(void *, s32, s32);

extern float moby_update_aim_target_strength(void *, void *);

extern void gfx_start_color_fade(void *, void *);

extern void gfx_update_color_fade(void *, void *);


/* A spinning target: it turns slowly, flashes and loses health when hit, and plays a sound while it is being hit. */
void spinning_target_update(u8 *obj) {
    u8 *state;
    u8 *hitFlash;
    float hitDamage;

    if (D_L18_001C9D40 != 0) return;
    state = *(u8 **)(obj + 0x68);
    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        *(short *)(state + 0x24) = 0x12;
        *(float *)(state + 0x20) = 18.0f;
        moby_set_state(obj, 1, -1);
        return;
    case 1:
        if (snd_is_voice_playing_for_owner(obj, *(s32 *)(state + 0x68)) == 0) {
            *(s32 *)(state + 0x68) = PlayMobySound(0, 4, obj);
        }
        hitFlash = state + 0x50;
        *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8),
                                               *(float *)(state + 0x64) * 0.000290888245f);
        hitDamage = moby_update_aim_target_strength(obj, part_find_owned_effect_slot(obj, 0x230000, 0));
        if (hitDamage > 0.0f) {
            *(u8 *)(state + 0x57) = 0xFF;
            *(u8 *)(state + 0x58) = 0x40;
            *(u8 *)(state + 0x59) = 0;
            gfx_start_color_fade(obj, hitFlash);
            *(float *)(state + 0x20) = *(float *)(state + 0x20) - hitDamage;
        }
        gfx_update_color_fade(obj, hitFlash);
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    }
}


/* func_L18_0043C258 lives in L18_0043C258-g8.c. */

/* func_L18_0043C778 is defined in L18_0043C778-g64.c. */

/* func_L18_0043CAF8 is defined in L18_0043CAF8-g8.c. */

/* func_L18_0043F130 is defined in L18_0043F130-qcopy-barrier.c. */

/* Works out a point on a smooth curve between two points, using the points before and after them to shape the curve. */
void math_cubic_spline_point(float *out, float *start, float *end, float *before, float *after, float amount)
{
    float amountSquared, amountCubed, cubicCoeff, quadraticCoeff, linearCoeff;

    if (amount == 0.0f) {
        qcopy(out, start);
        return;
    }
    if (amount == 1.0f) {
        qcopy(out, end);
        return;
    }
    amountSquared = amount * amount;
    amountCubed = amountSquared * amount;

    cubicCoeff = (after[0] - end[0]) - (before[0] - start[0]);
    quadraticCoeff = (before[0] - start[0]) - cubicCoeff;
    linearCoeff = end[0] - before[0];
    out[0] = cubicCoeff * amountCubed + quadraticCoeff * amountSquared + linearCoeff * amount + start[0];

    cubicCoeff = (after[1] - end[1]) - (before[1] - start[1]);
    quadraticCoeff = (before[1] - start[1]) - cubicCoeff;
    linearCoeff = end[1] - before[1];
    out[1] = cubicCoeff * amountCubed + quadraticCoeff * amountSquared + linearCoeff * amount + start[1];

    cubicCoeff = (after[2] - end[2]) - (before[2] - start[2]);
    quadraticCoeff = (before[2] - start[2]) - cubicCoeff;
    linearCoeff = end[2] - before[2];
    out[2] = cubicCoeff * amountCubed + quadraticCoeff * amountSquared + linearCoeff * amount + start[2];
    out[3] = 0.0f;
}



/* func_L18_0043FC70 is defined in L18_0043FC70-g8.c. */

/* func_L18_00440718 is defined in L18_00440718-g8.c. */

/* func_L18_00441050 is defined in L18_00441050-g8.c. */

typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } DamoselSoundAnchor;
extern char g_sound_state[];
extern char g_hero_position[];
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void vec_transform_and_set_height(void *, void *, void *, void *, float);
extern void part_spawn_masked_debris(void *, int, void *, float, float, float, float, int);
extern void SetDeathBits(void *, int, int), moby_mark_spawned(void *);
extern void cam_mode_noop(void *);

/* A destructible object that takes damage from most hits, flashes, and explodes when its health runs out. Hits from a Protopet or a fireball are ignored. */
void destructible_object_update(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    char *hit;
    char *owner;
    int excluded;
    float zero, damage;
    float direction[4];
    switch (object[0x20]) {
    case 0:
        *(int *)(state + 0x100) = -1;
        *(unsigned short *)(object + 0x34) |= 0x1000;
        state[0x48] = FloatToInt(15.0f);
        state[0x4a] = FloatToInt(6.0f);
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (flag_set_first_pending(object)) {
            if (*(int *)(state + 0x100) != -1 && ((DamoselSoundAnchor *)(g_sound_state + *(int *)(state + 0x100) * 112))->owner == object && ((DamoselSoundAnchor *)(g_sound_state + *(int *)(state + 0x100) * 112))->active)
                snd_stop_voice(*(int *)(state + 0x100));
            *(int *)(state + 0x100) = -1;
        }
        hit = part_find_owned_effect_slot(object, 0x10000, 0);
        if (!hit) goto intact;
        owner = *(char **)(hit + 0x20);
        excluded = 0;
        if (owner && (*(short *)(owner + 0xaa) == 0xb69 /* Protopet */ || *(short *)(owner + 0xaa) == 0xf9e /* moby class 3998 */)) excluded = 1;
        if (excluded) break;
        zero = 0.0f;
        damage = moby_update_aim_target_strength(object, hit);
        object[0xa8] = 255;
        *(float *)(state + 0x20) -= damage;
        if (*(float *)(state + 0x20) <= zero) {
            SpawnExplosionEffects(object, object + 0x10, 0, zero, zero, 10, 3, 9,
                         4.0f, 2.0f, 9.0f, zero, -1, 15.0f, 1, 1, -1, 0, 0x810001);
            PlayMobySound(0, 0, object);
            FastVecSub(direction, (float *)(object + 0x10), (float *)g_hero_position);
            vec_transform_and_set_height(object, direction, direction, 0, zero);
            vec_scale_to_length((char *)direction, (char *)direction, 0.10000001f);
            part_spawn_masked_debris(object, 0x1fff, direction, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            SetDeathBits(object, 0, 3);
            moby_mark_spawned(object);
        }
        break;
intact:
        cam_mode_noop(object);
        break;
    }
}

/* func_L18_00447128 is defined in L18_00447128-g8.c. */
