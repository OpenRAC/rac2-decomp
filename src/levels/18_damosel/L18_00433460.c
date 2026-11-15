#include "common.h"

extern float func_00283B98(float, float);

extern float func_00283180(float);

extern float func_00283198(float);

extern void func_L04_003A21F8(char *, s32);

extern char D_L18_002A9C40[];

extern float D_L18_001B97C0[];

extern float func_002A7878(float, float);

extern void func_0029FCC0(void *, int, void *);

extern void func_00282CF0(float *, const float *, const float *);

extern void func_00282F20(char *, char *, float);

extern void func_00282CC0(char *, char *, char *);

extern int func_002A7820(int, int);

extern float func_002A7940(void);

extern int D_L18_001C9D40;

extern void func_L02_003FFC48(void *, int, float, int, float, int, int);

extern s32 func_002E59B0(void *, s32);

extern s32 func_002E5CF8(s32, s32, void *);

extern void *func_002A9640(void *, s32, s32);

extern float func_002A96A0(void *, void *);

extern void func_002AB800(void *, void *);

extern void func_002AB8C0(void *, void *);

extern void func_002A7750(void *, int, int);


extern int func_00283CF0(float);
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern void func_0029F338(void *);
extern void func_L00_00426478(void *);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_002A6C58(void *, int, int);
extern char D_00188660[], D_00189EA0[];
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern int func_001163B0(void);
extern void func_00282D30(void *, void *, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern u8 *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } RibbonVector;
struct RibbonQuad { RibbonVector position[4]; u32 color[4]; float uv[4][2]; u64 clear, texture, giftag, flags; };
extern unsigned long func_0027C878(int);
extern void func_L00_00412088(void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);

/* Runs the shared effect routine with this level's effect data. It is handed to the effect controller as a callback. */
void func_L18_00435CC8(void) {
    render_water_grids(D_L18_002A9C40, 0x12);
}

/* Updates the two lightning arcs of the Extermibot beam: it eases their angles toward the targets and works out the sideways offsets. */
void func_L18_00434128(u8 *obj) {
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
            x = FastSinOrCosA(*(float *)(p + 0x40));
            *(float *)(p + 0x20) = x * *(float *)(p + 0x80);
            *(float *)(p + 0x24) = FastSinOrCosB(*(float *)(p + 0x44)) * *(float *)(p + 0x84);
            *(float *)(p + 0x28) = -FastSinOrCosB(*(float *)(p + 0x48)) * *(float *)(p + 0x88);
            p += 0x10;
        }
    }
}

extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern char D_00188660[];

#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern void func_002A7A00(void *,float,float);
extern float func_00283CE0(int);
extern int func_002E59B0(void *,int),func_002E5CF8(int,int,void *);
extern void func_002E59F8(int);
extern int func_002A8C28(void *,void *,int,int,int,int,float,float,float);
extern void func_002A8C00(void *,void *,int,void *,float);

extern int func_002761F8(void *,void *,int,void *,void *);
extern void func_L18_00434A98(char *,int);

extern struct { u8 pad[24];u8 *object;u8 pad1[4];float position[4] __attribute__((aligned(16))); } D_L18_001BFC00;
extern int D_L18_001B2348 __attribute__((sda));
typedef struct {
 u8 pad[0x7e4]; u8 *attached; u8 gap[0x1c]; s16 timer, mode;
} DamoselBeamState;
/* Runs the Extermibot's electric beam: it charges, shoots out to the target, sticks to what it hits, and then pulls back. It also throws sparks where the beam lands. */
void func_L18_00433460(u8 *obj) {
 float startPoint[4] __attribute__((aligned(16))),endPoint[4] __attribute__((aligned(16))),delta[4] __attribute__((aligned(16)));
 struct { float direction[4] __attribute__((aligned(16))); int owner,mode; u8 type,flags;u16 id; float distance;int enabled; } hit;
 u8 *vars=P(obj,0x68),*other;float progress;
 TransformMobyJointToWorld(P(vars,0x7c8),0,startPoint);TransformMobyJointToWorld(P(vars,0x7c8),1,endPoint);F(vars,0x7e0)=0;
 switch(H(vars,0x806)) {
 case 0:
  qcopy(vars+0x610,startPoint);qcopy(vars+0x620,endPoint);qcopy(vars+0x6b0,endPoint);qcopy(vars+0x6c0,startPoint);
  if(I(vars,0x7f0)!=-1) {
   u8 *entry=gSoundState+I(vars,0x7f0)*0x70;
   if(P(entry,0x88)==obj && entry[0x74])StopSoundVoice(I(vars,0x7f0));
  }
  I(vars,0x7f0)=-1;break;
 case 1:
  qcopy(vars+0x610,startPoint);qcopy(vars+0x620,endPoint);qcopy(vars+0x6b0,endPoint);qcopy(vars+0x6c0,startPoint);
  SweepCollisionFromObject(obj,startPoint,0x10001,0,1,0,0.2f,(float)vars[0x34],1);
  if(H(vars,0x804)>=6) {
   u8 *target=vars+0x760;
   u8 *p3=vars+0x6a0,*p2=vars+0x690,*p1=vars+0x680,*p0=vars+0x670;
   int i;
   for(i=1;i>=0;i--) {
    RandomDirectionVector(p0,0.232710599899292f,0.290888249874115f);
    RandomDirectionVector(p1,0.232710599899292f,0.290888249874115f);
    RandomDirectionVector(p2,2,5);RandomDirectionVector(p3,2,5);
    p0+=0xa0;p1+=0xa0;p2+=0xa0;p3+=0xa0;
   }
   H(vars,0x804)=0;H(vars,0x806)=2;
   if(!IsVoicePlayingForOwner(obj,I(vars,0x7f0)))I(vars,0x7f0)=PlayMobySound(1,4,obj);
   if(P(vars,0x7bc))qcopy(target,P(vars,0x7bc)+0x10);else qcopy(target,vars+0x1f0);
  } else F(vars,0x7e0)=IntToFloat(H(vars,0x804))/IntToFloat(5);
  break;
 case 2:
  qcopy(vars+0x610,startPoint);qcopy(vars+0x6b0,endPoint);
  SweepCollisionFromObject(obj,startPoint,0x10001,0,1,0,0.2f,(float)vars[0x34],1);
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
    SpawnLargeSparkSmokeBurst(vars+0x620,15);qcopy(vars+0x760,vars+0x620);H(vars,0x804)=0;
    if(D_L18_001BFC00.object) {
     float *point=D_L18_001BFC00.position;
     u8 *attached;
     H(vars,0x806)=3;attached=D_L18_001BFC00.object;P(vars,0x7e4)=attached;
     qcopy(vars+0x620,point);qcopy(vars+0x770,attached+0x10);
    } else H(vars,0x806)=4;
   }
  } else {H(vars,0x806)=4;SpawnLargeSparkSmokeBurst(vars+0x620,10);}
  break;
 case 3:
  qcopy(vars+0x610,startPoint);qcopy(vars+0x6b0,endPoint);
  if(H(vars,0x804)<51 && (other=P(vars,0x7e4)) && other[0x20]!=254 && other[0x20]!=253) {
   FastVecSub(delta,other+0x10,vars+0x770);FastVecAdd(vars+0x620,vars+0x620,delta);
   qcopy(vars+0x6c0,vars+0x620);qcopy(vars+0x770,P(vars,0x7e4)+0x10);
   if((D_L18_001B2348&15)==(((int)obj>>8)&15))SpawnLargeSparkSmokeBurst(vars+0x620,1);
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
    RandomDirectionVector(p0,0.232710599899292f,0.290888249874115f);
    RandomDirectionVector(p1,0.232710599899292f,0.290888249874115f);
    RandomDirectionVector(p2,1,1.7f);RandomDirectionVector(p3,1,1.7f);
    p0+=0xa0;p1+=0xa0;p2+=0xa0;p3+=0xa0;
   } }
  }
 }
 UpdateBeamArcOffsets(obj);
}

#undef F
#undef I
#undef H
#undef P

/* func_L18_00433B70 lives in L18_00433B70.c. */

/* Draws a glowing lightning ribbon along a list of points, as a wide main strip with a thinner inner strip. */
void func_L18_00434510(RibbonVector *points, int count, int flags, u32 color0, u32 color1, float width, float scale) {
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
    ResetEffectRecord(&mainQuad);
    mainQuad.uv[0][0] = 0.0f; mainQuad.uv[0][1] = 0.0f;
    mainQuad.uv[1][0] = 0.0f; mainQuad.uv[1][1] = 1.0f;
    mainQuad.uv[2][0] = 1.0f; mainQuad.uv[2][1] = 0.0f;
    mainQuad.uv[3][0] = 1.0f; mainQuad.uv[3][1] = 1.0f;
    innerQuad.texture = GetEffectTextureDescriptor(0x2B);
    innerQuad.giftag = 0xFF9000000260ULL;
    innerQuad.clear = 0;
    innerQuad.flags = ((u64)(long)(flags / 3) << 32) | 0x68;
    innerQuad.color[0] = innerQuad.color[1] = innerQuad.color[2] = innerQuad.color[3] = color1;
    ResetEffectRecord(&innerQuad);
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
    FastVecSub((float *)&basis[1], gCameraPosition_L18, (float *)&points[0]);
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
        FastVecSub((float *)&basis[1], gCameraPosition_L18, (float *)&points[i]);
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
void func_L18_00434A98(char *pos, int count) {
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
    FastVecSub(direction, gCameraPosition_L18, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = RandomFloatRange(0.5f, 2.0f);
        sign = RandomIntBelow(2);
        if (sign == 0)
            sign--;
        angle = RandomFloatRange(-1.0471977f, 1.0471977f);
        ApplyAxisRotationToQuaternion(velocity, direction, axis, angle);
        speed = RandomFloatRange(0.05f, 3.0f) * (1.0f / 60.0f);
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = RandomFloatRange(1.0f, 5.0f) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += RandomSignedFloatRange(0.0f, 0.15f);
        point[1] += RandomSignedFloatRange(0.0f, 0.15f);
        point[2] += RandomSignedFloatRange(0.0f, 0.15f);
        if (!(Rand() & 1)) {
            FastVecScale(velocity, velocity, 1.5f);
            particle = SpawnGroundEffectParticle(point, 60, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = SpawnGroundEffectParticle(point, 60, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        } else {
            FastVecSub(extra, gCameraPosition_L18, point);
            vec_scale_to_length((char *)extra, (char *)extra, speed);
            FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
            particle = SpawnGroundEffectParticle(point, 40, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = SpawnGroundEffectParticle(point, 40, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        }
        if (particle)
            particle[9] = FloatToInt(4.0f) + 0x70;
    }
}

/* Makes a quick glow flash at a moby's position. */
void func_L18_00434FC0(u8 *obj) {
    float v[4];
    float w[4];
    float a;

    a = RandomFloatRange(0.5f, 0.8f);
    TransformMobyJointToWorld(obj, 0, v);
    a = a * 0.5f;
    FastVecSub(w, gCameraPosition_L18, v);
    w[2] = 0.0f;
    vec_scale_to_length((char *)w, (char *)w, 0.2f);
    FastVecAdd((char *)v, (char *)v, (char *)w);
    DrawAimedEffectPacket(v, 0x807070, a, RandomIntRange(0x50, 0x60), RandomAngle(), 0x31, 2);
    DrawAimedEffectPacket(v, 0x802020, 0.56f, RandomIntRange(0x16, 0x32), RandomAngle(), 0xB, 2);
}

/* Throws a small burst of smoke and spark particles outward from a point; a smaller version of the bigger burst. */
void func_L18_004350E0(char *pos, int count) {
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
    FastVecSub(direction, gCameraPosition_L18, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = RandomFloatRange(0.5f, 2.0f);
        sign = RandomIntBelow(2);
        if (sign == 0)
            sign--;
        angle = RandomFloatRange(-1.0471977f, 1.0471977f);
        ApplyAxisRotationToQuaternion(velocity, direction, axis, angle);
        speed = RandomFloatRange(0.05f, 3.0f) * (1.0f / 60.0f);
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = RandomFloatRange(1.0f, 5.0f) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += RandomSignedFloatRange(0.0f, 0.15f);
        point[1] += RandomSignedFloatRange(0.0f, 0.15f);
        point[2] += RandomSignedFloatRange(0.0f, 0.15f);
        if (!(Rand() & 1)) {
            FastVecScale(velocity, velocity, 1.5f);
            particle = SpawnGroundEffectParticle(point, 60, size * 0.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = SpawnGroundEffectParticle(point, 60, size * 0.035f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        } else {
            FastVecSub(extra, gCameraPosition_L18, point);
            vec_scale_to_length((char *)extra, (char *)extra, speed);
            FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
            particle = SpawnGroundEffectParticle(point, 40, size * 0.15f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = SpawnGroundEffectParticle(point, 40, size * 0.105000004f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
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

extern float func_00283B98(float, float);

extern s32 func_002E59B0(void *, s32);

extern s32 func_002E5CF8(s32, s32, void *);

extern void *func_002A9640(void *, s32, s32);

extern float func_002A96A0(void *, void *);

extern void func_002AB800(void *, void *);

extern void func_002AB8C0(void *, void *);


/* A spinning target: it turns slowly, flashes and loses health when hit, and plays a sound while it is being hit. */
void func_L18_00439FC8(u8 *obj) {
    u8 *state;
    u8 *hitFlash;
    float hitDamage;

    if (D_L18_001C9D40 != 0) return;
    state = *(u8 **)(obj + 0x68);
    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        *(short *)(state + 0x24) = 0x12;
        *(float *)(state + 0x20) = 18.0f;
        SetMobyState(obj, 1, -1);
        return;
    case 1:
        if (IsVoicePlayingForOwner(obj, *(s32 *)(state + 0x68)) == 0) {
            *(s32 *)(state + 0x68) = PlayMobySound(0, 4, obj);
        }
        hitFlash = state + 0x50;
        *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8),
                                               *(float *)(state + 0x64) * 0.000290888245f);
        hitDamage = UpdateAimTargetStrength(obj, FindOwnedEffectSlot(obj, 0x230000, 0));
        if (hitDamage > 0.0f) {
            *(u8 *)(state + 0x57) = 0xFF;
            *(u8 *)(state + 0x58) = 0x40;
            *(u8 *)(state + 0x59) = 0;
            StartColorFade(obj, hitFlash);
            *(float *)(state + 0x20) = *(float *)(state + 0x20) - hitDamage;
        }
        UpdateColorFade(obj, hitFlash);
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    }
}


/* func_L18_0043C258 lives in L18_0043C258-g8.c. */

/* func_L18_0043C778 is defined in L18_0043C778-g64.c. */

/* func_L18_0043CAF8 is defined in L18_0043CAF8-g8.c. */

/* func_L18_0043F130 is defined in L18_0043F130-qcopy-barrier.c. */

/* Works out a point on a smooth curve between two points, using the points before and after them to shape the curve. */
void func_L18_0043F308(float *out, float *start, float *end, float *before, float *after, float amount)
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
extern char D_00188660[];
extern char D_00189EA0[];
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_002AFEB8(void *, void *, void *, void *, float);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_002A6C58(void *, int, int), func_0029F338(void *);
extern void func_L00_00426478(void *);

/* A destructible object that takes damage from most hits, flashes, and explodes when its health runs out. Hits from a Protopet or a fireball are ignored. */
void func_L18_00441438(unsigned char *object)
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
        SetMobyState(object, 1, -1);
        break;
    case 1:
        if (SetFirstPendingFlag(object)) {
            if (*(int *)(state + 0x100) != -1 && ((DamoselSoundAnchor *)(gSoundState + *(int *)(state + 0x100) * 112))->owner == object && ((DamoselSoundAnchor *)(gSoundState + *(int *)(state + 0x100) * 112))->active)
                StopSoundVoice(*(int *)(state + 0x100));
            *(int *)(state + 0x100) = -1;
        }
        hit = FindOwnedEffectSlot(object, 0x10000, 0);
        if (!hit) goto intact;
        owner = *(char **)(hit + 0x20);
        excluded = 0;
        if (owner && (*(short *)(owner + 0xaa) == 0xb69 /* Protopet */ || *(short *)(owner + 0xaa) == 0xf9e /* moby class 3998 */)) excluded = 1;
        if (excluded) break;
        zero = 0.0f;
        damage = UpdateAimTargetStrength(object, hit);
        object[0xa8] = 255;
        *(float *)(state + 0x20) -= damage;
        if (*(float *)(state + 0x20) <= zero) {
            SpawnExplosionEffects(object, object + 0x10, 0, zero, zero, 10, 3, 9,
                         4.0f, 2.0f, 9.0f, zero, -1, 15.0f, 1, 1, -1, 0, 0x810001);
            PlayMobySound(0, 0, object);
            FastVecSub(direction, (float *)(object + 0x10), (float *)gHeroPosition);
            TransformAndSetHeight(object, direction, direction, 0, zero);
            vec_scale_to_length((char *)direction, (char *)direction, 0.10000001f);
            SpawnDebrisForMaskedParts(object, 0x1fff, direction, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            SetDeathBits(object, 0, 3);
            MarkMobySpawned(object);
        }
        break;
intact:
        CameraModeNoOp(object);
        break;
    }
}

/* func_L18_00447128 is defined in L18_00447128-g8.c. */
