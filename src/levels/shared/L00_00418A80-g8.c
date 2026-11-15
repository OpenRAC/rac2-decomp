#include "common.h"

typedef unsigned int EffectQuad __attribute__((mode(TI)));
typedef union { EffectQuad word; float v[4]; } EffectVector;
extern char D_L00_001A8F20[] MACRO_ADDR;
typedef struct {
    char pad[0x140];
    float position[4];
} EffectCamera;
extern char D_L00_001B8C80[];
typedef struct {
    char pad[0xD4];
    unsigned char *smoke;
    char padD8[0x98];
    unsigned char *flash;
} EffectTextures;
extern char D_L00_001FE940[];
extern float D_L00_001B1438 __attribute__((sda));
extern float D_L00_001B143C __attribute__((sda));
extern int D_L00_001B1440 __attribute__((sda));
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern char *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern char *func_002C7970(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void func_00308408(void *, void *, void *, int, int, int, int, int, float);
extern void func_002AF000(void *, float, float, float);
extern char *func_002BDCE8(void *, float, float, float, float, int, void *, unsigned int, int);

typedef struct {
    short life, timer, delay, pad06;
    float outer, inner, fade, scale;
    int flags, control, brightCount, largeCount, smallCount, smokeCount, enabled, shockwave;
} EffectBurstState;
typedef struct {
    char pad00[0x10];
    EffectVector position;
    char pad20[0x48];
    EffectBurstState *state;
    char pad6C[0x54];
    EffectVector forward;
} EffectBurstObject;

/* Spawns a burst's particles: fixed sprites at the object, the three counted groups from the state record,
   an optional shockwave and the counted smoke group. */
void func_L00_00418A80(char *object, char *unused)
{
    EffectVector position, velocity;
    EffectBurstObject *m = (EffectBurstObject *)object;
    EffectBurstState *state = m->state;
    float heading;
    int i, sign;
    {
        int i, j;
        for (i = 0; i < 1; i++) {
            char *particle;
            float size, speed;
            FastVecScale(&position, &m->forward, 0.5f);
            qcopy(&velocity, &m->position);
            FastVecAdd(&velocity, &velocity, &position);
            size = D_L00_001B1438 * state->scale * 210000.0f;
            speed = D_L00_001B143C * state->scale * 210000.0f;
            particle = func_002C65A0(&velocity, D_L00_001A8F20, D_L00_001B1440, 0xF78E38, 0, 100, 0, size, speed, 0.0f, 0);
            if (particle) particle[2] = (((EffectTextures *)D_L00_001FE940)->flash)[0];
            particle = func_002C65A0(&velocity, D_L00_001A8F20, D_L00_001B1440, 0xF7, 0, 100, 0, size, speed, 0.0f, 0);
            if (particle) particle[2] = (((EffectTextures *)D_L00_001FE940)->flash)[0];
            for (j = 0; j < 2; j++) {
                char *particle;
                particle = func_002C65A0(&velocity, D_L00_001A8F20, D_L00_001B1440, 0xF78E38, 0, 127, 0, size, speed, 0.0f, 0);
                if (particle) particle[2] = (((EffectTextures *)D_L00_001FE940)->flash)[5];
            }
            for (j = 0; j < 2; j++) {
                char *particle;
                particle = func_002C65A0(&velocity, D_L00_001A8F20, D_L00_001B1440, 0xF78E38, 0, 127, 0, size, speed, 0.0f, 0);
                if (particle) particle[2] = (((EffectTextures *)D_L00_001FE940)->flash)[6];
            }
        }
    }
    for (i = 0; i < state->brightCount; i++) {
        char *particle;
        float size, speed, angle, dir;
        int turn, life;
        angle = func_00283248(((EffectCamera *)D_L00_001B8C80)->position[0] - m->position.v[0],
                               ((EffectCamera *)D_L00_001B8C80)->position[1] - m->position.v[1]);
        turn = FloatToInt(func_002A78D8(2.0f, 5.0f));
        life = func_002A7820(30, 50);
        position.v[0] = m->position.v[0] + func_002A78D8(0.0f, 0.1f) * state->scale;
        position.v[1] = m->position.v[1] + func_002A78D8(0.0f, 0.1f) * state->scale;
        position.v[2] = m->position.v[2] + func_002A78D8(0.0f, 0.1f) * state->scale;
        size = func_002A7878(0.6f, 1.0f) * state->scale;
        speed = 2.0f * (func_002A7878(9.0f, 12.0f) * state->scale);
        dir = FastAddRotations(angle, func_002A78D8(0.0f, 1.396263599395752f));
        velocity.v[0] = func_00283180(dir) * 0.01666666753590107f * speed;
        velocity.v[1] = func_00283198(dir) * 0.01666666753590107f * speed;
        velocity.v[2] = 0.0f;
        speed = 2.0f * (func_002A7878(3.0f, 12.0f) * state->scale);
        velocity.v[2] = speed * 0.01666666753590107f;
        func_002C7970(&position, &velocity, life, 0xF78E38, turn, 127, 127, size * 210000.0f, state->scale * 2100.0f, 0.004055555909872055f, 1);
        particle = func_002C7970(&position, &velocity, life, 0xF71E00, turn * -2, 48, 48, size * 1260000.0f, state->scale * 4200.0f, 0.004055555909872055f, 0);
        if (particle) particle[2] = (((EffectTextures *)D_L00_001FE940)->smoke)[0];
    }
    for (i = 0; i < state->largeCount; i++) {
        float size, speed, angle, dir;
        int turn, life;
        angle = func_00283248(((EffectCamera *)D_L00_001B8C80)->position[0] - m->position.v[0],
                               ((EffectCamera *)D_L00_001B8C80)->position[1] - m->position.v[1]);
        turn = FloatToInt(func_002A78D8(2.0f, 5.0f));
        life = func_002A7820(30, 50);
        position.v[0] = m->position.v[0] + func_002A78D8(0.0f, 0.1f) * state->scale;
        position.v[1] = m->position.v[1] + func_002A78D8(0.0f, 0.1f) * state->scale;
        position.v[2] = m->position.v[2] + func_002A78D8(0.0f, 0.1f) * state->scale;
        size = func_002A7878(0.75f, 1.5f) * state->scale;
        speed = 2.0f * (func_002A7878(9.0f, 12.0f) * state->scale);
        dir = FastAddRotations(angle, func_002A78D8(0.0f, 1.396263599395752f));
        velocity.v[0] = func_00283180(dir) * 0.01666666753590107f * speed;
        velocity.v[1] = func_00283198(dir) * 0.01666666753590107f * speed;
        velocity.v[2] = 0.0f;
        speed = 2.0f * (func_002A7878(3.0f, 12.0f) * state->scale);
        velocity.v[2] = speed * 0.01666666753590107f;
        func_002C7970(&position, &velocity, life, 0xF78E38, turn, 127, 127, size * 210000.0f, state->scale * 2100.0f, 0.004055555909872055f, 5);
    }
    for (i = 0; i < state->smallCount; i++) {
        float size, speed, angle, dir;
        int turn, life;
        angle = func_00283248(((EffectCamera *)D_L00_001B8C80)->position[0] - m->position.v[0],
                               ((EffectCamera *)D_L00_001B8C80)->position[1] - m->position.v[1]);
        turn = FloatToInt(func_002A78D8(2.0f, 5.0f));
        life = func_002A7820(30, 50);
        position.v[0] = m->position.v[0] + func_002A78D8(0.0f, 0.1f) * state->scale;
        position.v[1] = m->position.v[1] + func_002A78D8(0.0f, 0.1f) * state->scale;
        position.v[2] = m->position.v[2] + func_002A78D8(0.0f, 0.1f) * state->scale;
        size = func_002A7878(0.6f, 1.0f) * state->scale;
        speed = func_002A7878(9.0f, 12.0f) * state->scale;
        dir = FastAddRotations(angle, func_002A78D8(0.0f, 1.396263599395752f));
        velocity.v[0] = func_00283180(dir) * 0.01666666753590107f * speed;
        velocity.v[1] = func_00283198(dir) * 0.01666666753590107f * speed;
        velocity.v[2] = 0.0f;
        speed = func_002A7878(0.0f, 12.0f) * state->scale;
        velocity.v[2] = speed * 0.01666666753590107f;
        func_002C7970(&position, &velocity, life, 0xF71E00, turn, 127, 127, size * 210000.0f, state->scale * 2100.0f, 0.004055555909872055f, 3);
    }
    if (state->shockwave) {
        velocity.word = 0;
        velocity.v[2] = state->scale * 0.13333334028720856f;
        position.word = velocity.word;
        func_00308408(object, &m->position, &position, 16, 0, 0, 255, 40, state->scale * 3.5f);
    }
    heading = func_00283248(((EffectCamera *)D_L00_001B8C80)->position[0] - m->position.v[0],
                           ((EffectCamera *)D_L00_001B8C80)->position[1] - m->position.v[1]);
    sign = 1;
    for (i = 0; i < state->smokeCount; i++) {
        char *particle;
        float size, spread, angle;

        sign = -sign;
        position.v[0] = m->position.v[0] + func_002A78D8(0.0f, 1.0f) * state->scale;
        position.v[1] = m->position.v[1] + func_002A78D8(0.0f, 1.0f) * state->scale;
        position.v[2] = m->position.v[2] + func_002A78D8(0.0f, 1.0f) * state->scale;
        size = func_002A7878(0.01666666753590107f, 0.03333333507180214f) * state->scale;
        spread = func_002A78D8(0.0f, 1.396263599395752f);
        angle = func_002A78D8(0.0f, 1.5707964897155762f);
        angle = FastAddRotations(heading, angle);
        func_002AF000(&velocity, size, angle, spread);
        particle = SpawnSpinningSparkParticle(&position, 0.0f, 1.0f, 1.0099999904632568f, state->scale * 315000.0f,
                                sign, &velocity, 0x323232, 0);
        if (particle) {
            char *particleState = particle + 0x20;
            particle[3] = 0x44;
            *(short *)(particle + 10) = func_002A7820(40, 70);
            particle[9] = FloatToInt(4.0f) + 64;
            *(float *)(particleState + 0x1C) = IntToFloat(func_002A7820(1, 10));
            *(int *)(particleState + 4) = 3;
            particleState[0xA] = 127;
            particleState[0xB] = particle[10];
        }
    }
}
