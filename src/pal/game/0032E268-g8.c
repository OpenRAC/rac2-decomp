/* func_PAL_0032E268, the PAL copy of func_0032CA40: the same C, where the per-frame steps 1/60 become 1/50
 * (0.0166667f, 0.0333333f, 0.0040556f, 0.133333f become 0.02f, 0.04f, 0.00584f, 0.16f) and frame counts
 * pass through the 50 Hz scale ((x) * 5 + 2) / 6.  The two fixed-count loops count up here. */
#include "common.h"

extern float D_001B06C4 __attribute__((sda));
extern float D_001B06C8 __attribute__((sda));
extern int D_001B06CC __attribute__((sda));
extern unsigned char *D_001F26B0 __attribute__((section(".data")));
typedef struct {
    char pad0[0xD4];
    unsigned char *a;
    char pad1[0x98];
    unsigned char *b;
} EffectTextures;
extern unsigned char *D_001F2540[];
extern char D_001A8BD0[] __attribute__((sda));
typedef struct {
    char pad[0x140];
    float x, y, z;
} EffectCamera;
extern EffectCamera D_001B5200;
/* These typed interleavings preserve the EE integer and floating-point argument banks. */
extern char *func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern char *func_002C7970(void *, void *, int, int, int, int, int, float, float, float, int);
extern char *func_002C6DD8(void *, void *, int, float);
extern float func_002A7878(float, float), func_002A78D8(float, float);
extern int func_002A7820(int, int), func_00283CF0(float);
extern float func_00283CE0(int), func_00283248(float, float);
extern float func_00283B98(float, float), func_00283180(float), func_00283198(float);
extern void func_00282CC0(void *, void *, void *), func_00282D30(void *, void *, float);
extern void func_002AB668(void *, void *, float), func_002ACDE8(void *, void *, void *);
extern void func_00308408(void *, void *, void *, int, int, int, int, int, float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_002AF000(void *, float, float, float);
extern char *func_002BDCE8(void *, float, float, float, float, int, void *, int, int);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))

typedef struct {
    int unused, mode;
    char pad[2];
    unsigned char alpha, life;
    char padC[16];
    float growth;
} EffectParticleData;
typedef unsigned int EffectQuad __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } EffectVec __attribute__((aligned(16)));

/* Emits the explosion layers, debris and spinning sparks configured by the object. */
void func_PAL_0032E268(char *object, void *radial, void *attachment, float distance)
{
    EffectVec pos, velocity, rotated;
    char *state = *(char **)(object + 0x68), *particle;
    int i, sign;
    {
        float angle, size;
        angle = D_001B06C4 * F(state, 0x14) * 210000.0f;
        size = D_001B06C8 * F(state, 0x14) * 210000.0f;
        {
            particle = func_002C65A0(object + 0x10, attachment, (D_001B06CC * 5 + 2) / 6, 0x388EF7, 0, 100, 0, angle, size, 0.0f, 0);
            if (particle) particle[2] = D_001F26B0[0];
            particle = func_002C65A0(object + 0x10, attachment, (D_001B06CC * 5 + 2) / 6, 0x63F7, 0, 100, 0, angle, size, 0.0f, 0);
            if (particle) particle[2] = D_001F26B0[0];
        }
        {
            int i;
            for (i = 0; i < 2; i++) {
                particle = func_002C65A0(object + 0x10, attachment, (D_001B06CC * 5 + 2) / 6, 0x388EF7, 0, 127, 0, angle, size, 0.0f, 0);
                if (particle) particle[2] = ((EffectTextures *)D_001F2540)->b[5];
            }
        }
        {
            int i;
            for (i = 0; i < 2; i++) {
                particle = func_002C65A0(object + 0x10, attachment, (D_001B06CC * 5 + 2) / 6, 0x388EF7, 0, 127, 0, angle, size, 0.0f, 0);
                if (particle) particle[2] = ((EffectTextures *)D_001F2540)->b[6];
            }
        }
    }
    {
        int i;
        for (i = 0; i < I(state, 32); i++) {
            int spin, life;
            char *particle;
            float facing, size, speed, angle;
            facing = func_00283248(D_001B5200.x - F(object, 0x10), D_001B5200.y - F(object, 0x14));
            spin = func_00283CF0(func_002A78D8(2.0f, 5.0f));
            life = func_002A7820(30, 50);
            pos.x = F(object, 0x10) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
            pos.y = F(object, 0x14) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
            pos.z = F(object, 0x18) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
            size = func_002A7878(0.6f, 1.0f) * F(state, 0x14);
            speed = func_002A7878(9.0f, 12.0f) * F(state, 0x14);
            angle = func_00283B98(facing, func_002A78D8(0.0f, 1.396263599395752f));
            velocity.x = func_00283180(angle) * 0.020000001f * speed;
            velocity.y = func_00283198(angle) * 0.020000001f * speed;
            velocity.z = 0.0f;
            speed = func_002A7878(0.0f, 12.0f) * F(state, 0x14);
            velocity.z = speed * 0.020000001f;
            func_00282CC0(&velocity, &velocity, attachment);
            particle = func_002C7970(&pos, &velocity, (life * 5 + 2) / 6, 0x407FFF, spin, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 1);
            particle = func_002C7970(&pos, &velocity, (life * 5 + 2) / 6, 0x20FF, -(spin * 2), 48, 48, size * 1260000.0f, F(state, 0x14) * 4200.0f, 0.00584f, 0);
            if (particle) particle[2] = ((EffectTextures *)D_001F2540)->a[0];
        }
    }
    {
        int i;
        for (i = 0; i < I(state, 36); i++) {
            int spin, life;
            char *particle;
            float facing, size, speed, angle;
            facing = func_00283248(D_001B5200.x - F(object, 0x10), D_001B5200.y - F(object, 0x14));
            spin = func_00283CF0(func_002A78D8(2.0f, 5.0f));
            life = func_002A7820(30, 50);
            pos.x = F(object, 0x10) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
            pos.y = F(object, 0x14) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
            pos.z = F(object, 0x18) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
            size = func_002A7878(0.75f, 1.5f) * F(state, 0x14);
            speed = func_002A7878(9.0f, 12.0f) * F(state, 0x14);
            angle = func_00283B98(facing, func_002A78D8(0.0f, 1.396263599395752f));
            velocity.x = func_00283180(angle) * 0.020000001f * speed;
            velocity.y = func_00283198(angle) * 0.020000001f * speed;
            velocity.z = 0.0f;
            speed = func_002A7878(0.0f, 12.0f) * F(state, 0x14);
            velocity.z = speed * 0.020000001f;
            func_00282CC0(&velocity, &velocity, attachment);
            particle = func_002C7970(&pos, &velocity, (life * 5 + 2) / 6, 0x8FFF, spin, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 5);
        }
    }
    {
        int i;
        for (i = 0; i < I(state, 40); i++) {
            int spin, life;
            char *particle;
            float facing, size, speed, angle;
            facing = func_00283248(D_001B5200.x - F(object, 0x10), D_001B5200.y - F(object, 0x14));
            spin = func_00283CF0(func_002A78D8(2.0f, 5.0f));
            life = func_002A7820(30, 50);
            pos.x = F(object, 0x10) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
            pos.y = F(object, 0x14) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
            pos.z = F(object, 0x18) + func_002A78D8(0.0f, 0.1f) * F(state, 0x14);
            size = func_002A7878(0.6f, 1.0f) * F(state, 0x14);
            speed = func_002A7878(9.0f, 12.0f) * F(state, 0x14);
            angle = func_00283B98(facing, func_002A78D8(0.0f, 1.396263599395752f));
            velocity.x = func_00283180(angle) * 0.020000001f * speed;
            velocity.y = func_00283198(angle) * 0.020000001f * speed;
            velocity.z = 0.0f;
            speed = func_002A7878(0.0f, 12.0f) * F(state, 0x14);
            velocity.z = speed * 0.020000001f;
            func_00282CC0(&velocity, &velocity, attachment);
            particle = func_002C7970(&pos, &velocity, (life * 5 + 2) / 6, 0x3064FF, spin, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 3);
        }
    }
    {
        int i;
        for (i = 0; i < I(state, 0x30); i++) {
            float speed, angle, turn;
            int life;
            speed = func_002A7878(15.0f, 20.0f) * F(state, 0x14);
            func_00282D30(&pos, object + 0xC0, speed * 0.020000001f);
            angle = func_002A78D8(0.2617994248867035f, 1.396263599395752f);
            turn = func_002A78D8(0.2617994248867035f, 1.396263599395752f);
            func_002AB668(&rotated, object + 0xD0, angle);
            func_002ACDE8(&velocity, &pos, &rotated);
            func_002AB668(&rotated, object + 0xC0, turn);
            func_002ACDE8(&velocity, &velocity, &rotated);
            func_00282CC0(&velocity, &velocity, attachment);
            life = func_002A7820(20, 35);
            func_002C6DD8(object + 0x10, &velocity, (life * 5 + 2) / 6, 0.00584f);
        }
    }
    if (I(state, 0x34)) {
        *(EffectQuad *)&velocity = 0;
        velocity.z = F(state, 0x14) * 0.16000001f;
        *(EffectQuad *)&pos = *(EffectQuad *)&velocity;
        func_00282CC0(&pos, &pos, attachment);
        func_00308408(object, object + 0x10, &pos, (16 * 5 + 2) / 6, 255, 0, 0, 40, F(state, 0x14) * 3.5f);
    }
    func_002ABBB8(object, D_001A8BD0, object + 0x10, 0.0f, 0.0f, 0, 0, 0, 0.0f, 0.0f, 9.0f, 0.0f, -1, distance * F(state, 0x14), 0, 0, -1, 0, 0x810001);
    {
        float angle;
        sign = 1;
        angle = func_00283248(D_001B5200.x - F(object, 0x10), D_001B5200.y - F(object, 0x14));
        for (i = 0; i < I(state, 0x2C); i++) {
            float size, turn, height;
            char *particle;
            sign = -sign;
            pos.x = F(object, 0x10) + func_002A78D8(0.0f, 1.0f) * F(state, 0x14);
            pos.y = F(object, 0x14) + func_002A78D8(0.0f, 1.0f) * F(state, 0x14);
            pos.z = F(object, 0x18) + func_002A78D8(0.0f, 1.0f) * F(state, 0x14);
            size = func_002A7878(0.020000001f, 0.040000003f) * F(state, 0x14);
            turn = func_002A78D8(0.0f, 1.396263599395752f);
            height = func_00283B98(angle, func_002A78D8(0.0f, 1.5707964897155762f));
            func_002AF000(&velocity, size, height, turn);
            func_00282CC0(&velocity, &velocity, attachment);
            particle = func_002BDCE8(&pos, 0.0f, 1.0f, 1.0099999904632568f, F(state, 0x14) * 315000.0f, sign, &velocity, 0x7F60A0FF, 0);
            if (particle) {
                EffectParticleData *data = (EffectParticleData *)(particle + 0x20);
                *(short *)(particle + 0xA) = (func_002A7820(40, 70) * 5 + 2) / 6;
                particle[9] = func_00283CF0(4.0f) + 64;
                data->mode = 3;
                data->growth = func_00283CE0((func_002A7820(1, 10) * 5 + 2) / 6);
                data->alpha = 64;
                data->life = particle[0xA];
            }
        }
    }
}
