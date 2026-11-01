#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern int func_002AAFA0(unsigned int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern char *func_002BBCB0(void *, void *, int, int, float, int, int, float, int, int);
extern char *func_PAL_003096D0(void *, void *, void *, float, int, int, int, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_00312B70(void *, void *, int, int);
typedef struct { int colors[6]; } __attribute__((packed)) BurstColors;
typedef struct {
    float origin[4];
    void *owner;
    int flags;
    unsigned char kind, enabled;
    unsigned short uid;
    float damage;
    int reserved;
} ExplosionDamage;
typedef struct { float vector[4], random[4]; } ExplosionVectors;
extern BurstColors D_001A9F20, D_001A9F38;
extern float D_001B168C[] __attribute__((sda)), D_001B1690[] __attribute__((sda));
extern char D_001B5340[];
typedef struct {
    char unknown[0x160];
    float shake;
    int unknown164;
    int timer;
    int phase;
} ExplosionCamera;
extern ExplosionCamera D_001B5200;
typedef struct { char unknown[32]; float scale[3]; } BlastEffect;
extern BlastEffect D_00258C80, D_00258CD0;
extern void func_002A8BD0(void *, void *, int, float);
extern int func_00277F48(float, void *, int, void *, void *);
extern void *func_PAL_002BD790(void *, void *, int, int, float, int, int, int, int, int);
extern void *func_PAL_003098C8(void *, void *, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282FB8(void *, void *, float);
extern void func_002BB838(void *, void *, int, int, int, float);
extern int func_00283DB8(void *, float);
extern float func_00283CE0(int);
extern void func_002AF000(void *, float, float, float);

void func_PAL_002AC718(char *owner, void *direction, float *position,
    float radius, float damage, int sparks, int flashes, int smoke,
    float glow, float white, float cutoff, float scale, int sound, float blast,
    int shake, int debris, int quality, unsigned char channels, int flags)
{
    float drift[4];
    float delta[4];
    float distance;
    float load = D_001B1690[0] + D_001B168C[0];
    *(Quad *)drift = 0;
    drift[2] = scale * 0.16000001f;
    if (quality == -1 && load > 1.7000000476837158f) quality = 1;
    if (!position) {
        if (!owner) return;
        position = (float *)(owner + 0x10);
    }
    if (radius > 0.0f) {
        {
            ExplosionDamage message;
            func_002A8BD0(&message, owner, flags, damage);
            message.kind = 2;
            message.enabled = 1;
            message.uid = *(unsigned short *)(owner + 0xAA);
            func_00277F48(radius, position, 16, owner, &message);
        }
    }
    {
        int i;
        for (i = 0; i < sparks; i++) {
            {
                float vector[4];
                float angle, azimuth, speed;
                int c1, c2, life;
                angle = func_002A7878(0.2617994248867035f, 1.396263599395752f);
                azimuth = func_002A7940();
                speed = func_002A7878(7.0f, 10.5f);
                func_002AF000(vector, scale * 0.020000001f * speed, azimuth, angle);
                vector[2] += 0.060000002f;
                c1 = func_002AAFA0(0x4F007FFF, channels);
                c2 = func_002AAFA0(0x1F00007F, channels);
                life = func_002A7820(50, 100);
                func_PAL_002BD790(position, vector, c1, c2, scale * 40000.0f, life - quality * 10, 1, -1, -1, 0);
            }
        }
    }
    func_00282CF0(delta, D_001B5340, position);
    distance = func_00282DF0(delta);
    if (debris) {
        {
            ExplosionVectors v;
            int i;
            *(Quad *)v.random = 0;
            v.random[0] = func_002A7878(-1.0f, 1.0f);
            v.random[1] = func_002A7878(-1.0f, 1.0f);
            v.random[2] = func_002A7878(-1.0f, 1.0f);
            *(Quad *)v.vector = *(Quad *)v.random;
            if (distance < 14.0f) {
                delta[2] += distance * 0.5f;
                func_00282F20(v.vector, v.vector, distance * 0.004f);
                func_00282F20(delta, delta, (distance + distance) * 0.020000001f);
                func_00282CC0(v.vector, v.vector, delta);
                func_00282FB8(v.vector, v.vector, 0.20000002f);
                func_PAL_003098C8(position, v.vector, func_002A7820(50, 75), 0, 0);
            }
            debris--;
            for (i = 0; i < debris; i++) {
                int special;
                float angle, azimuth, speed;
                int life;
                angle = func_002A7878(0.2617994248867035f, 1.3089970350265503f);
                azimuth = func_002A7940();
                speed = func_002A7878(7.0f, 10.5f);
                func_002AF000(v.random, scale * 0.020000001f * speed, azimuth, angle);
                v.random[2] += 0.040000003f;
                {
                    int rem = i % 3;
                    int one = 1;
                    int zero = 0;
                    special = zero;
                    if (rem == 0) special = one;
                }
                life = func_002A7820(50, 75);
                func_PAL_003098C8(position, v.random, life, special, 0);
            }
        }
    }
    {
        int count;
        float under;
        int i;
        if (distance < func_00283CE0(flashes) * 2.0f)
        count = func_00283CF0(distance) / 2;
        else
        count = flashes;
        under = 0.0f;
        if (distance < 7.0f) under = 7.0f - distance;
        for (i = 0; i < count; i++) {
            {
                BurstColors colors1, colors2;
                float size, big;
                int c1, c2;
                size = func_002A7878(8.0f, 10.0f) * 0.020000001f;
                colors1 = D_001A9F20;
                colors2 = D_001A9F38;
                size = size - under * 0.020000001f;
                c1 = func_002A77E0(6);
                size *= scale;
                c1 = func_002AAFA0(colors1.colors[c1], channels);
                c2 = func_002AAFA0(colors2.colors[func_002A77E0(6)], channels);
                big = scale * 400000.0f;
                {
                    int life = func_002A7820(12, 17) - quality * 3;
                    int life2 = func_002A7820(25, 37) - quality * 5;
                    func_002BBCB0(position, drift, c1, c2, big, life, life2, size, 0, 0);
                }
                {
                    int life = func_002A7820(4, 8) - quality * 2;
                    int life2 = func_002A7820(12, 17) - quality * 3;
                    func_002BBCB0(position, drift, 0x7FFFFFFF, 0xFFFFFF, big, life, life2, size * 0.5f, 0, 0);
                }
            }
        }
    }
    {
        int i;
        for (i = 0; i < smoke; i++) {
            {
                BurstColors colors1, colors2;
                ExplosionVectors v;
                float speed, k;
                int c1, c2;
                colors1 = D_001A9F20;
                colors2 = D_001A9F38;
                *(Quad *)v.random = 0;
                v.random[0] = func_002A7878(-1.0f, 1.0f);
                v.random[1] = func_002A7878(-1.0f, 1.0f);
                v.random[2] = func_002A7878(-1.0f, 1.0f);
                *(Quad *)v.vector = *(Quad *)v.random;
                k = 0.020000001f;
                speed = func_002A7878(0.0f, 3.0f);
                func_00282F20(v.vector, v.vector, scale * k * speed);
                c1 = func_002AAFA0(colors1.colors[func_002A77E0(6)], channels);
                c2 = func_002AAFA0(colors2.colors[func_002A77E0(6)], channels);
                func_002BB838(position, v.vector, c1, c2, func_002A7820(25, 37) - quality * 5, 200000.0f);
            }
        }
    }
    if (owner && glow > 0.0f) {
        int r = 150, g = 150, b = 150, r2 = 127, g2 = 127, b2 = 0;
        if (channels) {
            if (!(channels & 4)) { r = 70; b = 70; r2 = 60; }
            else { r = 35; g = 0; b = 250; r2 = 32; g2 = 0; b2 = 100; }
        }
        if (D_001B168C[0] < 0.949999988079071f && cutoff < distance) {
            func_PAL_003096D0(owner, position, drift, glow, 13, r, g, b, 32);
            func_PAL_003096D0(owner, position, drift, glow, 18, r2 & 255, g2 & 255, b2 + 80, 32);
        }
        func_PAL_003096D0(owner, position, drift, glow, 25, r2 & 255, g2 & 255, b2, 48);
    }
    if (owner && white > 0.0f) func_PAL_003096D0(owner, position, drift, white, 22, 255, 255, 255, 32);
    if (shake) {
        {
            float vector[4];
            *(Quad *)vector = *(Quad *)position;
            vector[3] = 2.0f;
            if (func_00283DB8(vector, 10.0f) != -1) {
                ExplosionCamera *camera = &D_001B5200;
                if (distance < 20.0f) camera->shake = 0.4f - distance * 0.017500000074505806f;
                else camera->shake = 0.050000011920928955f;
                {
                    ExplosionCamera *state = &D_001B5200;
                    state->timer = 21;
                    state->phase = 0;
                }
            }
        }
    }
    if (owner && sound != -1) func_002E5CF8(sound, 0, owner);
    if (blast != 0.0f && quality == 0) {
        {
            float vector[4];
            qcopy(vector, position);
            vector[3] = blast;
            if (func_00283DB8(vector, 100.0f) != -1) {
                if (blast > 0.0f) {
                    BlastEffect *effect = &D_00258C80;
                    effect->scale[1] = blast;
                    effect->scale[2] = blast;
                    effect->scale[0] = blast;
                } else {
                    BlastEffect *effect = &D_00258C80;
                    effect->scale[1] = 15.0f;
                    effect->scale[2] = 15.0f;
                    effect->scale[0] = 15.0f;
                }
                if (channels) func_00312B70(&D_00258CD0, position, 0, 0);
                else func_00312B70(&D_00258C80, position, 0, 0);
            }
        }
    }
}
