#include "include_asm.h"

#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
typedef struct {
    char pad0[0x110];
    Vector motion;
    char pad120[0x220];
    int motionActive;
    char pad344[0x3EC];
    Vector axis, side;
} ContactHero;
extern ContactHero D_00189E20;
typedef struct {
    unsigned char pad0[3];
    unsigned char flags;
    unsigned char pad4[5];
    unsigned char tile;
    union { short frames; unsigned char bytes[2]; } life;
} ContactParticle;
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern float func_00283B98(float, float);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern char *func_PAL_002BE9A8(void *, float, float, float, int, void *, float, unsigned int, int);
extern void func_00282CF0(void *, void *, void *);
extern char *func_PAL_002C23B8(void *, void *, unsigned int, int, int, int, float, float, float, float, float);
extern float func_00282C48(float);
extern void func_002AB668(void *, int, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_002AF000(float *, float, float, float);
extern int func_002AAFA0(unsigned int, int);
extern int func_002A7820(int, int);
extern char *func_PAL_002BD790(void *, void *, int, int, int, int, int, int, int, float);

/* Spawn layered particles and two falling streaks at the supplied position. */
void func_PAL_L00_003A9668(void *owner, void *position)
{
    Vector rotation, direction, base, origin, velocity, jitter, drift, offset, scatter;
    float angle = 0.0f;
    int count;

    *(VectorBits *)base = 0;
    base[0] = 0.3f;
    base[1] = -1.0f;
    base[3] = 1.0f;
    qcopy(origin, position);
    func_002ACEC0(base, D_00189E20.axis, D_00189E20.side, 0.349065899848938f);
    qcopy(direction, base);
    /* This clear precedes every read of drift; surrounding objects do not alias it. */
    qzero_nc(drift);
    if (D_00189E20.motionActive)
        func_00282D30(drift, D_00189E20.motion, 1.7f);
    func_00282D30(offset, D_00189E20.axis, 0.4f);
    func_00282CC0(origin, origin, offset);
    for (count = 19; count >= 0; count--) {
        char *particle;
        float size;
        int spin;
        angle = func_00283B98(angle, func_002A7878(0.0f, 0.6283186078f));
        func_00282D30(velocity, direction, func_002A7878(0.24000001f, 0.32000002f));
        func_00282CC0(velocity, velocity, drift);
        jitter[0] = origin[0] + func_002A78D8(0.0f, 0.3f);
        jitter[1] = origin[1] + func_002A78D8(0.0f, 0.3f);
        jitter[2] = origin[2] + func_002A78D8(0.0f, 0.3f);
        spin = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        size = func_002A7878(0.2f, 0.75f) * 210000.0f;
        particle = func_PAL_002BE9A8(jitter, 0.0f, 1.0f, 1.00999999f, spin,
                                 D_00189E20.motion, size, 0x7F202020, 0);
        if (particle) {
            char *tail = particle + 0x20;
            ((ContactParticle *)particle)->flags = 0x44;
            ((ContactParticle *)particle)->life.frames = 50;
            ((ContactParticle *)particle)->tile = func_00283CF0(4.0f) + 0x40;
            *(float *)(tail + 0x1C) = func_00283CE0(4);
            *(int *)(tail + 4) = 3;
            *(unsigned char *)(tail + 0xA) = 0x30;
            *(unsigned char *)(tail + 0xB) = ((ContactParticle *)particle)->life.bytes[0];
        }
        jitter[0] = origin[0] + func_002A78D8(0.0f, 0.6f);
        jitter[1] = origin[1] + func_002A78D8(0.0f, 0.6f);
        jitter[2] = origin[2] + func_002A78D8(0.0f, 0.6f);
        size = func_002A7878(0.2f, 1.75f) * 210000.0f;
        func_00282CF0(jitter, jitter, velocity);
        func_PAL_002C23B8(jitter, velocity, 5, 0x7F, 0x404040, spin,
                      size, 500.0f, 0.95f, 0.0f, 0.0f);
        if (func_00282C48(angle) > 0.00001f) {
            func_002AB668(rotation, (int)D_00189E20.axis, angle);
            func_002ACDE8(direction, base, rotation);
        }
    }
    {
        int streakCount;
        float speed = func_002A7878(8.0f, 12.0f);
        float scale = 0.5f;
        func_00282D30(base, D_00189E20.axis, speed * (0.020000001f));
        for (streakCount = 1; streakCount >= 0; streakCount--) {
            float cone = func_002A7878(0.2617994249f, 1.396263599395752f);
            float heading = func_002A7940();
            float length = func_002A7878(7.0f, 10.5f);
            int firstColor, secondColor, life;
            func_002AF000(scatter, scale * (0.020000001f) * length, heading, cone);
            func_00282CC0(scatter, scatter, base);
            scatter[2] += 0.060000002f;
            firstColor = func_002AAFA0(0x4F007FFF, 0);
            secondColor = func_002AAFA0(0x1F00007F, 0);
            life = func_002A7820(50, 100);
            func_PAL_002BD790(position, scatter, firstColor, secondColor, life, 1, -1, -1, 0, scale * 40000.0f);
        }
    }
}
