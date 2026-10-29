/* Nonmatching preview particle triplet: USA608/612 bytes, 0/28 places under
 * the measured -O2 -G0 -fno-gcse diagnostic. Six bounded checks: initial608;
 * canonical address/lifetime correction604; incomplete SDA forms600; no-split
 * addresses624; macro-array forms600; no-GCSE608. No build flags retained.
 * The clean retained view keeps real scalar types and a complete camera prefix.
 * Remaining: a cached phase-symbol high half adds s4, while retail rebuilds
 * absolute addresses; interpolation lifetime and constructor argument setup
 * differ. No volatile, raw alias, fake object bound or forced register added.
 * Reopen on real owner/address-class or argument-bank/lifetime evidence.
 *
 * C65A0 real C definition returns a pointer to the complete 64-byte particle;
 * its interface is two pointers, three float and six integer parameters, using
 * eight GPRs/three FP registers and no stack. Context is 32 bytes. The four local
 * vectors cover every 16-byte primitive access. The external zero vector remains
 * incomplete and is not shrunk for GP. Radius is the sole actual GP scalar.
 * CE0 returns float from int; CF0 returns int from float; D30/CC0/D08 return void,
 * checked against current C or actual retail primitive bodies. Current RAC1
 * pause/preview helpers and qualified RAC2 camera/particle neighbors inspected.
 */
/* Screened, not matched in wave 13 (worker g3): 12 call(s), 0 $gp-relative small-data access(es), MMI words [none], float constants [none]. The body is straight-line code
   whose register allocation and the materialisation of its constant addresses have to be
   reproduced word for word; no C was written in this wave. */

#include "common.h"

typedef struct {
    char reserved00[0x140];
    float position[4];
    char reserved150[0x220];
    float forward[4];
} PreviewCameraPrefix;
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
extern PreviewCameraPrefix D_001B5200;
extern unsigned char D_001B2344 NOT_SDA;
extern short D_001B2312 NOT_SDA;
extern float D_001B2314 MACRO_ADDR;
extern float D_001AD81C SDATA(D_001AD81C) __attribute__((sda));
extern float D_001A8BD0[] MACRO_ADDR;
extern unsigned char *D_001F2614;
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_00282D08(void *, void *, void *, float);
extern int func_00283CF0(float);
extern Particle_C65A0 *func_002C65A0(const float *, const float *, float, float, float,
                                   int, unsigned int, int, int, int, int);

/* The constructor owns a complete 64-byte particle. All four local vectors
 * cover the full16-byte accesses of the actual EE vector helpers. */
void func_002FFD78(void)
{
    float offset[4] __attribute__((aligned(16)));
    float farPoint[4] __attribute__((aligned(16)));
    float nearPoint[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    int phase = D_001B2344;
    int secondPhase;
    float size, interpolation;
    Particle_C65A0 *particle;
    func_00282D30(offset, D_001B5200.forward, 9.0f);
    func_00282CC0(farPoint, D_001B5200.position, offset);
    func_00282D30(offset, D_001B5200.forward, 0.1f);
    func_00282CC0(nearPoint, D_001B5200.position, offset);
    interpolation = func_00283CE0(D_001B2312) * D_001B2314;
    func_00282D08(position, nearPoint, farPoint, interpolation);
    size = D_001AD81C * 210000.0f;
    particle = func_002C65A0(position, D_001A8BD0, size, size, 0.0f,
                            4, 0xFF2020, phase, 127, 127, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = func_00283CF0(0.4f) + 64;
    }
    secondPhase = (phase + 128) % 255;
    particle = func_002C65A0(position, D_001A8BD0, size, size, 0.0f,
                            4, 0xFF2020, secondPhase, 127, 127, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = func_00283CF0(0.4f) + 64;
    }
    size *= 0.5f;
    particle = func_002C65A0(position, D_001A8BD0, size, size, 0.0f,
                            4, 0xFFFFFF, secondPhase, 127, 127, 0);
    if (particle) {
        particle->shade = *D_001F2614;
        particle->variation = func_00283CF0(0.4f) + 64;
    }
    D_001B2344++;
}
