/* func_PAL_L00_00412C28, the PAL copy of func_L00_0040DF58: the same C, with the particle counts and
 * lifetimes scaled to 50 Hz ((x * 5 + 2) / 6, the fire lifetimes at the calls) and the per-frame rates
 * multiplied by 6/5. The flash group reads the object's position into a local before the forward-vector
 * call: the longer life lets the loop pass hoist it past the larger PAL loop, which gives it its own slot.
 *
 * func_L00_0040DF58: offset explosion burst (family F6, see func_L16_00406550). One flash group half
 * a forward vector ahead of the object, then the configured particle groups. The two fire loops count
 * up in the source: the loop pass reverses them after hoisting the colour table address, which is what
 * orders the first loop's preheader. The emitters take their float parameters interleaved with the ints.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern float D_L00_001B1030 __attribute__((sda)), D_L00_001B1034 __attribute__((sda));
extern int D_L00_001B1038 __attribute__((sda));
extern float D_L00_001A8F20[4] MACRO_ADDR;
typedef struct { u8 pad[0x140]; float target[4]; } CameraView;
typedef struct { u8 pad[0xD4]; u8 *sparkColors; u8 pad2[0x98]; u8 *fireColors; } EffectTables;
extern CameraView D_L00_001B8C80;
extern EffectTables D_L00_001FE940;
extern u8 *func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern u8 *func_002C7970(void *, void *, int, int, int, int, int, float, float, float, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00308408(void *, void *, void *, int, int, int, int, int, float);
extern void func_002AF000(float *, float, float, float);
typedef struct BurstPayload {
    u8 pad00[4];
    int kind;
    u8 pad08[2];
    u8 alpha, fade;
    u8 pad0C[0x10];
    float size;
} BurstPayload;
typedef struct BurstParticle {
    u8 pad00[9];
    u8 rate;
    u16 lifetime;
    u8 pad0C[0x14];
    BurstPayload payload;
} BurstParticle;
extern u8 *func_002BDCE8(void *, float, float, int, void *, int, int, float, float);
extern float func_00283CE0(int);
typedef struct BurstSettings {
    u8 pad00[0x14];
    float scale;
    u8 pad18[8];
    int count20, count24, count28, count2C, count30, enabled34;
} BurstSettings;
typedef struct BurstObject {
    u8 pad00[0x10];
    float position[4];
    u8 pad20[0x48];
    BurstSettings *settings;
    u8 pad6C[0x54];
    float forward[4], right[4];
} BurstObject;
void func_PAL_L00_00412C28(BurstObject *object, void *up)
{
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    BurstSettings *state = object->settings;

    {
        float inner, outer;
        int i, j;
        u8 *effect;
        for (j = 0; j < 1; j++) {
            float *origin = object->position;
            func_00282D30(position, object->forward, 0.5f);
            qcopy(velocity, origin);
            func_00282CC0(velocity, velocity, position);
            inner = D_L00_001B1030 * state->scale * 210000.0f;
            outer = D_L00_001B1034 * state->scale * 210000.0f;
            effect = func_002C65A0(velocity, D_L00_001A8F20, (D_L00_001B1038 * 5 + 2) / 6, 0x388EF7, 0, 100, 0,
                inner, outer, 0.0f, 0);
            if (effect) effect[2] = D_L00_001FE940.fireColors[0];
            effect = func_002C65A0(velocity, D_L00_001A8F20, (D_L00_001B1038 * 5 + 2) / 6, 0xF7, 0, 100, 0,
                inner, outer, 0.0f, 0);
            if (effect) effect[2] = D_L00_001FE940.fireColors[0];
            for (i = 0; i < 2; i++) {
                effect = func_002C65A0(velocity, D_L00_001A8F20, (D_L00_001B1038 * 5 + 2) / 6, 0x388EF7, 0,
                    127, 0, inner, outer, 0.0f, 0);
                if (effect) effect[2] = D_L00_001FE940.fireColors[5];
            }
            for (i = 0; i < 2; i++) {
                effect = func_002C65A0(velocity, D_L00_001A8F20, (D_L00_001B1038 * 5 + 2) / 6, 0x388EF7, 0,
                    127, 0, inner, outer, 0.0f, 0);
                if (effect) effect[2] = D_L00_001FE940.fireColors[6];
            }
        }
    }
    {
        int i;
        for (i = 0; i < state->count20; i++) {
            float heading, angle, size, speed;
            int phase, lifetime;
            u8 *effect;
            heading = func_00283248(D_L00_001B8C80.target[0] - object->position[0],
                D_L00_001B8C80.target[1] - object->position[1]);
            phase = func_00283CF0(func_002A78D8(2.0f, 5.0f));
            lifetime = func_002A7820(30, 50);
            position[0] = object->position[0] + func_002A78D8(0.0f, 0.1f) * state->scale;
            position[1] = object->position[1] + func_002A78D8(0.0f, 0.1f) * state->scale;
            position[2] = object->position[2] + func_002A78D8(0.0f, 0.1f) * state->scale;
            size = func_002A7878(0.6f, 1.0f) * state->scale;
            speed = func_002A7878(9.0f, 12.0f) * state->scale * 2.0f;
            angle = func_00283B98(heading, func_002A78D8(0.0f, 1.3962636f));
            velocity[0] = func_00283180(angle) * 0.020000001f * speed;
            velocity[1] = func_00283198(angle) * 0.020000001f * speed;
            velocity[2] = 0.0f;
            speed = func_002A7878(3.0f, 12.0f) * state->scale * 2.0f;
            velocity[2] = speed * 0.020000001f;
            func_002C7970(position, velocity, (lifetime * 5 + 2) / 6, 0x148EF7, phase, 127, 127,
                size * 210000.0f, state->scale * 2100.0f, 0.00584f, 1);
            phase *= 2;
            effect = func_002C7970(position, velocity, (lifetime * 5 + 2) / 6, 0x1E1EF7, -phase, 48, 48,
                size * 1260000.0f, state->scale * 4200.0f, 0.00584f, 0);
            if (effect) effect[2] = D_L00_001FE940.sparkColors[0];
        }
    }
    {
        int i;
        for (i = 0; i < state->count24; i++) {
            float heading, angle, size, speed;
            int phase, lifetime;
            heading = func_00283248(D_L00_001B8C80.target[0] - object->position[0],
                D_L00_001B8C80.target[1] - object->position[1]);
            phase = func_00283CF0(func_002A78D8(2.0f, 5.0f));
            lifetime = func_002A7820(30, 50);
            position[0] = object->position[0] + func_002A78D8(0.0f, 0.1f) * state->scale;
            position[1] = object->position[1] + func_002A78D8(0.0f, 0.1f) * state->scale;
            position[2] = object->position[2] + func_002A78D8(0.0f, 0.1f) * state->scale;
            size = func_002A7878(0.75f, 1.5f) * state->scale;
            speed = func_002A7878(9.0f, 12.0f) * state->scale * 2.0f;
            angle = func_00283B98(heading, func_002A78D8(0.0f, 1.3962636f));
            velocity[0] = func_00283180(angle) * 0.020000001f * speed;
            velocity[1] = func_00283198(angle) * 0.020000001f * speed;
            velocity[2] = 0.0f;
            speed = func_002A7878(3.0f, 12.0f) * state->scale * 2.0f;
            velocity[2] = speed * 0.020000001f;
            func_002C7970(position, velocity, (lifetime * 5 + 2) / 6, 0x328EF7, phase, 127, 127,
                size * 210000.0f, state->scale * 2100.0f, 0.00584f, 5);
        }
    }
    {
        int i;
        for (i = 0; i < state->count28; i++) {
            float heading, angle, size, speed;
            int phase, lifetime;
            heading = func_00283248(D_L00_001B8C80.target[0] - object->position[0],
                D_L00_001B8C80.target[1] - object->position[1]);
            phase = func_00283CF0(func_002A78D8(2.0f, 5.0f));
            lifetime = func_002A7820(30, 50);
            position[0] = object->position[0] + func_002A78D8(0.0f, 0.1f) * state->scale;
            position[1] = object->position[1] + func_002A78D8(0.0f, 0.1f) * state->scale;
            position[2] = object->position[2] + func_002A78D8(0.0f, 0.1f) * state->scale;
            size = func_002A7878(0.6f, 1.0f) * state->scale;
            speed = func_002A7878(9.0f, 12.0f) * state->scale;
            angle = func_00283B98(heading, func_002A78D8(0.0f, 1.3962636f));
            velocity[0] = func_00283180(angle) * 0.020000001f * speed;
            velocity[1] = func_00283198(angle) * 0.020000001f * speed;
            velocity[2] = 0.0f;
            speed = func_002A7878(0.0f, 12.0f) * state->scale;
            velocity[2] = speed * 0.020000001f;
            func_002C7970(position, velocity, (lifetime * 5 + 2) / 6, 0x1EF7, phase, 127, 127,
                size * 210000.0f, state->scale * 2100.0f, 0.00584f, 3);
        }
    }
    if (state->enabled34) {
        *(Quad *)velocity = 0;
        velocity[2] = state->scale * 0.16000001f;
        *(Quad *)position = *(Quad *)velocity;
        func_00308408(object, object->position, position, (16 * 5 + 2) / 6, 0, 0, 255, 40,
            state->scale * 3.5f);
    }
    {
        int sign = 1, i;
        float angle;
        angle = func_00283248(D_L00_001B8C80.target[0] - object->position[0],
            D_L00_001B8C80.target[1] - object->position[1]);
        for (i = 0; i < state->count2C; i++) {
            float radius, roll, turn;
            u8 *effect;
            position[0] = object->position[0] + func_002A78D8(0.0f, 1.0f) * state->scale;
            sign = -sign;
            position[1] = object->position[1] + func_002A78D8(0.0f, 1.0f) * state->scale;
            position[2] = object->position[2] + func_002A78D8(0.0f, 1.0f) * state->scale;
            radius = func_002A7878(0.020000001f, 0.040000003f) * state->scale;
            roll = func_002A78D8(0.0f, 1.3962636f);
            turn = func_00283B98(angle, func_002A78D8(0.0f, 1.5707965f));
            func_002AF000(velocity, radius, turn, roll);
            effect = func_002BDCE8(position, 0.0f, 1.0f, sign, velocity, 0x323232, 0, 1.01f,
                state->scale * 315000.0f);
            if (effect) {
                BurstParticle *particle = (BurstParticle *)effect;
                BurstPayload *payload = &particle->payload;
                effect[3] = 0x44;
                particle->lifetime = (func_002A7820(40, 70) * 5 + 2) / 6;
                particle->rate = func_00283CF0(4.0f) + 64;
                payload->size = func_00283CE0((func_002A7820(1, 10) * 5 + 2) / 6);
                payload->kind = 3;
                payload->alpha = 127;
                payload->fade = particle->lifetime;
            }
        }
    }
}
