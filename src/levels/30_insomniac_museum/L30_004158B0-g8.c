#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct {
    short life, initialLife, duration, pad;
    float inner, outer, strength, scale;
    int sound, flash, count0, count1, count2, count3, count4, count5, color;
} ExplosionState;
extern float D_L30_001B1EF8 __attribute__((sda));
extern float D_L30_001B1EFC __attribute__((sda));
extern int D_L30_001B1F00 __attribute__((sda));
extern char D_L30_001A8F20[] __attribute__((sda)) NOT_SDA;
extern unsigned char *D_L30_001FF940[];
extern unsigned char *D_L30_001FFAB0[];
extern struct { char pad[0x140]; float position[4]; } D_L30_001B9C80;
extern char *func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern char *func_002C7970(void *, void *, int, int, int, int, int, float, float, float, int);
extern void func_00282D30(void *, void *, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern char *func_002C6DD8(void *, void *, int, float);
extern void func_00308408(void *, void *, void *, int, float, int, int, int, int);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_002AF000(void *, float, float, float);
extern char *func_002BDCE8(void *, float, float, float, int, void *, float, int, int);

/* Spawns all the particles of a museum explosion: flash, sparks, smoke, debris and a shock ring. */
void func_L30_004158B0(char *moby) {
    float particlePos[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    ExplosionState *state = *(ExplosionState **)(moby + 0x68);
    float angle;
    int i, sign;
    {
        float burstSize, burstSpeed;
        int i;
        char *particle;
        burstSize = D_L30_001B1EF8 * state->scale * 210000.0f;
        burstSpeed = D_L30_001B1EFC * state->scale * 210000.0f;
        particle = SpawnGravityFadeParticle(moby + 0x10, D_L30_001A8F20, D_L30_001B1F00, state->color | 0x7F000000, 0, 100, 0, burstSize, burstSpeed, 0.0f, 0);
        if (particle) particle[2] = D_L30_001FFAB0[0][0];
        particle = SpawnGravityFadeParticle(moby + 0x10, D_L30_001A8F20, D_L30_001B1F00, state->color, 0, 100, 0, burstSize, burstSpeed, 0.0f, 0);
        if (particle) particle[2] = D_L30_001FFAB0[0][0];
        {
            int alpha = 0x7F000000;
            for (i = 1; i >= 0; i--) {
                particle = SpawnGravityFadeParticle(moby + 0x10, D_L30_001A8F20, D_L30_001B1F00, state->color | alpha, 0, 127, 0, burstSize, burstSpeed, 0.0f, 0);
                if (particle) particle[2] = D_L30_001FF940[0x170/4][5];
            }
        }
        {
            int alpha = 0x7F000000;
            for (i = 1; i >= 0; i--) {
                particle = SpawnGravityFadeParticle(moby + 0x10, D_L30_001A8F20, D_L30_001B1F00, state->color | alpha, 0, 127, 0, burstSize, burstSpeed, 0.0f, 0);
                if (particle) particle[2] = D_L30_001FF940[0x170/4][6];
            }
        }
    }
    for (i = 0; i < state->count0; i++) {
        float angle, direction, size, speed;
        int n, life;
        char *particle;
        angle = FastMatrixHelperA(D_L30_001B9C80.position[0] - *(float *)(moby+0x10), D_L30_001B9C80.position[1] - *(float *)(moby+0x14));
        n = FloatToInt(RandomSignedFloatRange(2.0f, 5.0f));
        life = RandomIntRange(30, 50);
        particlePos[0] = *(float *)(moby+0x10) + RandomSignedFloatRange(0.0f, 0.1f)*state->scale;
        particlePos[1] = *(float *)(moby+0x14) + RandomSignedFloatRange(0.0f, 0.1f)*state->scale;
        particlePos[2] = *(float *)(moby+0x18) + RandomSignedFloatRange(0.0f, 0.1f)*state->scale;
        size = RandomFloatRange(0.6f, 1.0f)*state->scale;
        speed = RandomFloatRange(9.0f, 12.0f)*state->scale;
        direction = FastAddRotations(angle, RandomSignedFloatRange(0.0f, 1.396263599395752f));
        velocity[0] = FastSinOrCosA(direction)*(1.0f/60.0f)*speed;
        velocity[1] = FastSinOrCosB(direction)*(1.0f/60.0f)*speed;
        velocity[2] = 0.0f;
        speed = RandomFloatRange(0.0f, 12.0f)*state->scale;
        velocity[2] = speed*(1.0f/60.0f);
        SpawnFadingDriftParticle(particlePos,velocity,life,state->color,n,127,127,size*210000.0f,state->scale*2100.0f,0.004055555909872055f,1);
        n *= 2;
        particle = SpawnFadingDriftParticle(particlePos,velocity,life,state->color&0xFFFFFF,-n,48,48,size*1260000.0f,state->scale*4200.0f,0.004055555909872055f,0);
        if (particle) particle[2] = D_L30_001FF940[0xD4/4][0];
    }
    for (i = 0; i < state->count1; i++) {
        float angle, direction, size, speed;
        int n, life;
        char *particle;
        angle = FastMatrixHelperA(D_L30_001B9C80.position[0] - *(float *)(moby+0x10), D_L30_001B9C80.position[1] - *(float *)(moby+0x14));
        n = FloatToInt(RandomSignedFloatRange(2.0f, 5.0f));
        life = RandomIntRange(30, 50);
        particlePos[0] = *(float *)(moby+0x10) + RandomSignedFloatRange(0.0f, 0.1f)*state->scale;
        particlePos[1] = *(float *)(moby+0x14) + RandomSignedFloatRange(0.0f, 0.1f)*state->scale;
        particlePos[2] = *(float *)(moby+0x18) + RandomSignedFloatRange(0.0f, 0.1f)*state->scale;
        size = RandomFloatRange(0.75f, 1.5f)*state->scale;
        speed = RandomFloatRange(9.0f, 12.0f)*state->scale;
        direction = FastAddRotations(angle, RandomSignedFloatRange(0.0f, 1.396263599395752f));
        velocity[0] = FastSinOrCosA(direction)*(1.0f/60.0f)*speed;
        velocity[1] = FastSinOrCosB(direction)*(1.0f/60.0f)*speed;
        velocity[2] = 0.0f;
        speed = RandomFloatRange(0.0f, 12.0f)*state->scale;
        velocity[2] = speed*(1.0f/60.0f);
        SpawnFadingDriftParticle(particlePos,velocity,life,state->color&0xFFFFFF,n,127,127,size*210000.0f,state->scale*2100.0f,0.004055555909872055f,5);
    }
    for (i = 0; i < state->count2; i++) {
        float angle, direction, size, speed;
        int n, life;
        char *particle;
        angle = FastMatrixHelperA(D_L30_001B9C80.position[0] - *(float *)(moby+0x10), D_L30_001B9C80.position[1] - *(float *)(moby+0x14));
        n = FloatToInt(RandomSignedFloatRange(2.0f, 5.0f));
        life = RandomIntRange(30, 50);
        particlePos[0] = *(float *)(moby+0x10) + RandomSignedFloatRange(0.0f, 0.1f)*state->scale;
        particlePos[1] = *(float *)(moby+0x14) + RandomSignedFloatRange(0.0f, 0.1f)*state->scale;
        particlePos[2] = *(float *)(moby+0x18) + RandomSignedFloatRange(0.0f, 0.1f)*state->scale;
        size = RandomFloatRange(0.6f, 1.0f)*state->scale;
        speed = RandomFloatRange(9.0f, 12.0f)*state->scale;
        direction = FastAddRotations(angle, RandomSignedFloatRange(0.0f, 1.396263599395752f));
        velocity[0] = FastSinOrCosA(direction)*(1.0f/60.0f)*speed;
        velocity[1] = FastSinOrCosB(direction)*(1.0f/60.0f)*speed;
        velocity[2] = 0.0f;
        speed = RandomFloatRange(0.0f, 12.0f)*state->scale;
        velocity[2] = speed*(1.0f/60.0f);
        SpawnFadingDriftParticle(particlePos,velocity,life,state->color&0xFFFFFF,n,127,127,size*210000.0f,state->scale*2100.0f,0.004055555909872055f,3);
    }
    for (i = 0; i < state->count4; i++) {
        float x, y;
        char *particle;
        FastVecScale(particlePos,moby+0xC0,RandomFloatRange(15.0f,20.0f)*state->scale*(1.0f/60.0f));
        x = RandomSignedFloatRange(0.2617994248867035f,1.396263599395752f);
        y = RandomSignedFloatRange(0.2617994248867035f,1.396263599395752f);
        BuildAxisAngleQuaternion(temp,moby+0xD0,x);
        RotateVectorByQuaternion(velocity,particlePos,temp);
        BuildAxisAngleQuaternion(temp,moby+0xC0,y);
        RotateVectorByQuaternion(velocity,velocity,temp);
        particle = SpawnTrailParticle_002C6DD8(moby+0x10,velocity,RandomIntRange(20,35),0.004055555909872055f);
        if (particle) *(int *)(particle+12) = *(int *)(particle+4) = state->color|0x7F000000;
    }
    if (state->count5) {
        *(Quadword *)velocity = 0;
        velocity[2] = state->scale*(2.0f/15.0f);
        *(Quadword *)particlePos = *(Quadword *)velocity;
        SpawnShockwaveRing(moby,moby+0x10,particlePos,16,state->scale*3.5f,(unsigned char)state->color,(unsigned char)(state->color>>8),(unsigned char)(state->color>>16),45);
    }
    SpawnExplosionEffects(moby,D_L30_001A8F20,moby+0x10,0.0f,0.0f,0,0,0,0.0f,0.0f,9.0f,0.0f,-1,state->scale*20.0f,0,0,-1,0,0x810001);
    sign = 1;
    angle = FastMatrixHelperA(D_L30_001B9C80.position[0] - *(float *)(moby+0x10), D_L30_001B9C80.position[1] - *(float *)(moby+0x14));
    for (i = 0; i < state->count3; i++) {
        float size, x, y;
        char *particle;
        particlePos[0] = *(float *)(moby+0x10) + RandomSignedFloatRange(0.0f,1.0f)*state->scale;
        sign = -sign;
        particlePos[1] = *(float *)(moby+0x14) + RandomSignedFloatRange(0.0f,1.0f)*state->scale;
        particlePos[2] = *(float *)(moby+0x18) + RandomSignedFloatRange(0.0f,1.0f)*state->scale;
        size = RandomFloatRange(1.0f/60.0f,1.0f/30.0f)*state->scale;
        x = RandomSignedFloatRange(0.0f,1.396263599395752f);
        y = RandomSignedFloatRange(0.0f,1.5707964897155762f);
        BuildSphericalOffset(velocity,size,FastAddRotations(angle,y),x);
        particle = SpawnSpinningSparkParticle(particlePos,0.0f,1.0f,1.01f,sign,velocity,state->scale*315000.0f,state->color|0x7F0000,0);
        if (particle) {
            char *sub = particle + 0x20;
            *(short *)(particle+10) = RandomIntRange(40,70);
            particle[9] = FloatToInt(4.0f)+64;
            *(int *)(sub+4) = 3;
            *(float *)(sub+0x1C) = IntToFloat(RandomIntRange(1,10));
            sub[0xA] = 64;
            sub[0xB] = particle[10];
        }
    }
}
