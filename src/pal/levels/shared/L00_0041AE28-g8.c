#include "common.h"

/* func_PAL_L00_0041AE28, the PAL copy of func_L00_00415DE8: the same C, where the
 * frame counts are scaled to 50 Hz and the per-frame rates grow by 6/5 (36/25 for
 * the acceleration). The two-pass emitter loops count up here: loop.c reverses them,
 * so their counter is set after the hoisted divisor, as retail has it. It is also
 * func_PAL_L13_004175B8's C with this level's colours. */

typedef int Quad __attribute__((mode(TI)));
extern float D_L00_001B13EC __attribute__((sda)), D_L00_001B13F0 __attribute__((sda));
extern int D_L00_001B13F4 __attribute__((sda));
/* Keep the full vector size: sda selects symbolic address formation in cc1,
 * while the assembler keeps this 16 - byte object absolute under -G8. */
extern float D_L00_001A8F20[4] __attribute__((sda));
typedef struct Cam_00435CE8 Cam_00435CE8;
typedef struct CamMgr_00435CE8 {
    u8 pad000[0x140];
    f32 f140[4];
    u8 pad150[0x40];
    Cam_00435CE8 *cam;
} CamMgr_00435CE8;
extern CamMgr_00435CE8 D_L00_001B8C80;
extern u8 *D_L00_001FE940[] NOT_SDA;
/* Integer and FP arguments retain their respective EE ABI bank order. */
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
extern void func_002AB668(void *, int, float);
extern void func_002ACDE8(void *, void *, void *);
extern u8 *func_002C6DD8(void *, void *, int, float);
extern void func_00308408(void *, void *, void *, int, int, int, int, int, float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
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
extern u8 *func_002BDCE8(void *, float, float, int, void *, int, float, float, int);
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
void func_PAL_L00_0041AE28(BurstObject *object)
{
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float rotation[4];
    BurstSettings *state = object->settings;

    /* The initial emitters share one result variable; later groups own theirs. */
    {
        float inner, outer;
        int i;
        u8 *effect;
        inner = D_L00_001B13EC * state->scale * 210000.0f;
        outer = D_L00_001B13F0 * state->scale * 210000.0f;
        effect = func_002C65A0(object->position, D_L00_001A8F20, ((s32)(D_L00_001B13F4) * 5 + 2) / 6, 0x388EF7, 0, 100, 0, inner,
            outer, 0.0f, 0);
        if (effect) effect[2] = D_L00_001FE940[92][0];
        effect = func_002C65A0(object->position, D_L00_001A8F20, ((s32)(D_L00_001B13F4) * 5 + 2) / 6, 0x63F7, 0, 100, 0, inner,
            outer, 0.0f, 0);
        if (effect) effect[2] = D_L00_001FE940[92][0];
        for (i = 0; i < 2; i++) {
            effect = func_002C65A0(object->position, D_L00_001A8F20, ((s32)(D_L00_001B13F4) * 5 + 2) / 6, 0x388EF7, 0, 127, 0,
                inner, outer, 0.0f, 0);
            if (effect) effect[2] = D_L00_001FE940[92][5];
        }
        for (i = 0; i < 2; i++) {
            effect = func_002C65A0(object->position, D_L00_001A8F20, ((s32)(D_L00_001B13F4) * 5 + 2) / 6, 0x388EF7, 0, 127, 0,
                inner, outer, 0.0f, 0);
            if (effect) effect[2] = D_L00_001FE940[92][6];
        }
    }
    {
        int i;
        for (i = 0; i < state->count20; i++) {
            /* Heading and perturbed angle have separate lifetimes. Speed is reused
             * for the later vertical component. */
            float heading, angle, size, speed;
            int phase, lifetime;
            u8 *effect;
            heading = func_00283248(D_L00_001B8C80.f140[0] - object->position[0],
                D_L00_001B8C80.f140[1] - object->position[1]);
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
            func_002C7970(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0x407FFF, phase, 127, 127, size * 210000.0f,
                state->scale * 2100.0f, 0.00584f, 1);
            phase *= 2;
            effect = func_002C7970(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0x20FF, -phase, 48, 48, size * 1260000.0f,
                state->scale * 4200.0f, 0.00584f, 0);
            if (effect) effect[2] = D_L00_001FE940[53][0];
        }
    }
    {
        int i;
        for (i = 0; i < state->count24; i++) {
            float heading, angle, size, speed;
            int phase, lifetime;
            heading = func_00283248(D_L00_001B8C80.f140[0] - object->position[0],
                D_L00_001B8C80.f140[1] - object->position[1]);
            phase = func_00283CF0(func_002A78D8(2.0f, 5.0f));
            lifetime = func_002A7820(30, 50);
            position[0] = object->position[0] + func_002A78D8(0.0f, 0.1f) * state->scale;
            position[1] = object->position[1] + func_002A78D8(0.0f, 0.1f) * state->scale;
            position[2] = object->position[2] + func_002A78D8(0.0f, 0.1f) * state->scale;
            size = func_002A7878(0.75f, 1.5f) * state->scale;
            speed = func_002A7878(9.0f, 12.0f) * state->scale;
            angle = func_00283B98(heading, func_002A78D8(0.0f, 1.3962636f));
            velocity[0] = func_00283180(angle) * 0.020000001f * speed;
            velocity[1] = func_00283198(angle) * 0.020000001f * speed;
            velocity[2] = 0.0f;
            speed = func_002A7878(0.0f, 12.0f) * state->scale;
            velocity[2] = speed * 0.020000001f;
            func_002C7970(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0x8FFF, phase, 127, 127, size * 210000.0f,
                state->scale * 2100.0f, 0.00584f, 5);
        }
    }
    {
        int i;
        for (i = 0; i < state->count28; i++) {
            float heading, angle, size, speed;
            int phase, lifetime;
            heading = func_00283248(D_L00_001B8C80.f140[0] - object->position[0],
                D_L00_001B8C80.f140[1] - object->position[1]);
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
            func_002C7970(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0x3064FF, phase, 127, 127, size * 210000.0f,
                state->scale * 2100.0f, 0.00584f, 3);
        }
    }
    {
        int i;
        for (i = 0; i < state->count30; i++) {
            float speed, roll, turn;
            int lifetime;
            speed = func_002A7878(15.0f, 20.0f) * state->scale * 0.020000001f;
            func_00282D30(position, object->forward, speed);
            roll = func_002A78D8(0.26179942f, 1.3962636f);
            turn = func_002A78D8(0.26179942f, 1.3962636f);
            func_002AB668(rotation, (int)(object->right), roll);
            func_002ACDE8(velocity, position, rotation);
            func_002AB668(rotation, (int)(object->forward), turn);
            func_002ACDE8(velocity, velocity, rotation);
            lifetime = func_002A7820(20, 35);
            func_002C6DD8(object->position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0.00584f);
        }
    }
    if (state->enabled34) {
        *(Quad *)velocity = 0;
        velocity[2] = state->scale * 0.16000001f;
        *(Quad *)position = *(Quad *)velocity;
        func_00308408(object, object->position, position, (16 * 5 + 2) / 6, 255, 0, 0, 40, state->scale * 3.5f);
    }
    func_002ABBB8(object, D_L00_001A8F20, object->position, 0.0f, 0.0f, 0, 0, 0, 0.0f, 0.0f, 9.0f, 0.0f, -1,
        state->scale * 20.0f, 0, 0, -1, 0, 0x810001);
    {
        int sign = 1, i;
        float angle;
        angle = func_00283248(D_L00_001B8C80.f140[0] - object->position[0],
            D_L00_001B8C80.f140[1] - object->position[1]);
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
            effect = func_002BDCE8(position, 0.0f, 1.0f, sign, velocity, 0x7F60A0FF, 1.01f,
                state->scale * 315000.0f, 0);
            if (effect) {
                BurstParticle *particle = (BurstParticle *)effect;
                BurstPayload *payload = &particle->payload;
                particle->lifetime = ((s32)(func_002A7820(40, 70)) * 5 + 2) / 6;
                particle->rate = func_00283CF0(4.0f) + 64;
                payload->kind = 3;
                payload->size = func_00283CE0(((s32)(func_002A7820(1, 10)) * 5 + 2) / 6);
                payload->alpha = 64;
                payload->fade = particle->lifetime;
            }
        }
    }
}
