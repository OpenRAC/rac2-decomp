#include "include_asm.h"

#include "common.h"
#define MACRO_ADDR __attribute__((section(".sdata")))
extern int *r1_D_00161000 MACRO_ADDR;
typedef struct {
    int w[4];
} Qword_r002FCF90;
extern Qword_r002FCF90 *r1_D_00161000_q __asm__("r1_D_00161000") MACRO_ADDR;
extern void FastVecScale(float *, float *, float);
extern void FastVecScale(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);
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
extern PreviewCameraPrefix g_active_camera;
extern PreviewState g_object_preview_state __attribute__((sda));
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
extern float IntToFloat(int);
extern void lerp_vector(float *, float *, float *, float);
extern int FloatToInt(float);
extern Particle_C65A0 *part_spawn_gravity_fade(const float *, const float *, int, unsigned int, int, int, int,
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
    int phase = g_object_preview_state.phase;
    int secondPhase;
    float size, interpolation;
    Particle_C65A0 *particle;
    FastVecScale(offset, g_active_camera.forward, 9.0f);
    FastVecAdd(farPoint, g_active_camera.position, offset);
    FastVecScale(offset, g_active_camera.forward, 0.1f);
    FastVecAdd(nearPoint, g_active_camera.position, offset);
    interpolation = IntToFloat(g_object_preview_state.frames) * g_object_preview_state.rate;
    lerp_vector(position, nearPoint, farPoint, interpolation);
    size = D_001AD81C * 210000.0f;
    particle = part_spawn_gravity_fade(position, D_001A8BD0, 3, 0xFF2020, phase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = FloatToInt(0.4f) + 64;
    }
    secondPhase = (phase + 128) % 255;
    particle = part_spawn_gravity_fade(position, D_001A8BD0, 3, 0xFF2020, secondPhase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = FloatToInt(0.4f) + 64;
    }
    size *= 0.5f;
    particle = part_spawn_gravity_fade(position, D_001A8BD0, 3, 0xFFFFFF, secondPhase, 127, 127,
                            size, size, 0.0f, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = FloatToInt(0.4f) + 64;
    }
    g_object_preview_state.phase++;
}

