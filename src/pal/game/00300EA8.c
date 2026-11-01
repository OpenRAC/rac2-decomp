#include "include_asm.h"

#include "common.h"
#define MACRO_ADDR __attribute__((section(".sdata")))
extern int *r1_D_00161000 MACRO_ADDR;
typedef struct {
    int w[4];
} Qword_r002FCF90;
extern Qword_r002FCF90 *r1_D_00161000_q __asm__("r1_D_00161000") MACRO_ADDR;
extern void func_00282D30(float *, float *, float);
extern void func_00282D30(float *, float *, float);
extern void func_00282CC0(float *, float *, float *);
typedef struct {
    char reserved00[0x140];
    float position[4];
    char reserved150[0x220];
    float forward[4];
} PreviewCameraPrefix;
typedef struct {
    short s00;
    short frames;
    float rate;
    char pad08[0x34 - 0x08];
    unsigned char phase;
    unsigned char spin;
} PreviewState;
extern PreviewCameraPrefix D_001B5200;
extern PreviewState D_001B2310 __attribute__((sda));
extern float D_001AD808 SDATA(D_001AD808) __attribute__((sda));
extern float D_001AD80C SDATA(D_001AD80C) __attribute__((sda));
extern float D_001AD810 SDATA(D_001AD810) __attribute__((sda));
extern float D_001AD814 SDATA(D_001AD814) __attribute__((sda));
extern float D_001AD818 SDATA(D_001AD818) __attribute__((sda));
typedef struct {
    float velocity[3], gravity, size_delta;
    unsigned char alpha_delta, phase_delta;
    unsigned short pad16;
    int pad18;
    void (*update)(char *);
} ParticleContext_C65A0;
typedef struct {
    unsigned char byte0, byte1, shade, kind;
    unsigned int color;
    unsigned char phase, variation;
    short timer;
    float size, position[4];
    ParticleContext_C65A0 context;
} Particle_C65A0;
extern float D_001AD81C SDATA(D_001AD81C) __attribute__((sda));
extern float D_001A8BD0[] MACRO_ADDR;
extern unsigned char *D_001F2614;
extern float func_00283CE0(int);
extern void func_00282D08(float *, float *, float *, float);
extern int func_00283CF0(float);
extern Particle_C65A0 *func_002C65A0(const float *, const float *, int, unsigned int, int, int, int,
                                   float, float, float, int);

/* Emits three particles between 0.1 and 9 units in front of the camera,
   at the point the preview timer has reached; their phase advances once
   per call. */
void func_PAL_00300EA8(void)
{
    float offset[3] __attribute__((aligned(16)));
    float farPoint[3] __attribute__((aligned(16)));
    float nearPoint[3] __attribute__((aligned(16)));
    float position[3] __attribute__((aligned(16)));
    int phase = D_001B2310.phase;
    int secondPhase;
    float size, interpolation;
    Particle_C65A0 *particle;
    func_00282D30(offset, D_001B5200.forward, 9.0f);
    func_00282CC0(farPoint, D_001B5200.position, offset);
    func_00282D30(offset, D_001B5200.forward, 0.1f);
    func_00282CC0(nearPoint, D_001B5200.position, offset);
    interpolation = func_00283CE0(D_001B2310.frames) * D_001B2310.rate;
    func_00282D08(position, nearPoint, farPoint, interpolation);
    size = D_001AD81C * 210000.0f;
    particle = func_002C65A0(position, D_001A8BD0, 3, 0xFF2020, phase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = func_00283CF0(0.4f) + 64;
    }
    secondPhase = (phase + 128) % 255;
    particle = func_002C65A0(position, D_001A8BD0, 3, 0xFF2020, secondPhase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = func_00283CF0(0.4f) + 64;
    }
    size *= 0.5f;
    particle = func_002C65A0(position, D_001A8BD0, 3, 0xFFFFFF, secondPhase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = func_00283CF0(0.4f) + 64;
    }
    D_001B2310.phase++;
}

