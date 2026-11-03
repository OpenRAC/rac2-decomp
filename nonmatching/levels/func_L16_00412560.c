/* Claude Opus 5.5 xhigh (opus-2), task v2179, 2026-11-03: NOT MATCHED.
 * Flags (own unit): -O2 -G8 -ffunction-sections -Wa,-G32 (gp D_L16_001B16D0).
 * USA v1.01 cdiff: 1420/1420 bytes, 0/1 places; 10 rows differ beyond relocations,
 * all of them outer-loop spill-slot offsets 0x22C-0x23C (stores +0x1CC..+0x1D8,
 * loads +0x208/+0x210/+0x21C, i+1 at +0x224/+0x31C, &batch[1] reload at +0x35C).
 * Fixed since opus-1 (v2082, 32 rows): pos = batch[i].position[j] after the uv
 * stores (giv discovery order gives retail's cursor registers and increments);
 * &D_L16_001A8F20 MACRO_ADDR (unsplit la: lui/addiu adjacent, after the a0/a1
 * copies); i = 0 as the for-init, so no call precedes the loop label and flow
 * adds no (use 0) after func_00282F20 (that USE took sched1's second issue slot
 * beside the camera call, pushing i = 0 past the ray call).
 * Remaining: the five slots are gcse PRE reaching regs, numbered in hash-bucket
 * order. Raw hash (plus at X) = 14030+X, (plus (reg r) 1) = 14030+r, bucket =
 * raw % T, T = (max_cuid/2)|1 = 153 here (Expression hash table in -dG).
 * Retail's order (at+144, i+1, at+64, at+80, at+84) needs T in {143,149,157,
 * 159,161} AND the i+1 base regno r >= 145 (ours: i = reg 87; a block-local i
 * declared at the loop would be ~136). So retail's loop counter is created late
 * (inlined or nested scope after more pseudos?). Putting the whole i loop in a
 * static inline helper was far worse (344 rows).
 */
#include "common.h"
typedef int BeamQuadword __attribute__((mode(TI)));
typedef struct { int word[4]; } BeamDamageData __attribute__((aligned(16)));
typedef struct {
    float position[4][4];
    u32 color[4];
    float uv[4][2];
    unsigned long packet[4];
} BeamBatch __attribute__((aligned(16)));
extern float D_L16_001B16D0[4] __attribute__((sda));
extern float D_L16_001B17F8[2] __attribute__((sda));
extern int D_L16_001B17E8[2] __attribute__((sda));
extern float D_L16_001B1800[4][2] MACRO_ADDR;
extern float D_L16_001B1800_GP[4][2] SDATA(D_L16_001B1800);
extern u32 D_L16_001B1820[2] __attribute__((sda));
extern int D_L16_001B1828 __attribute__((sda));
extern u32 D_L16_001B182C __attribute__((sda));
extern float D_L16_001B1830[4] MACRO_ADDR;
extern float D_L16_001B1830_GP SDATA(D_L16_001B1830);
extern int D_L16_001B1840[2];
extern int D_L16_001B1840_GP SDATA(D_L16_001B1840);
extern float D_L16_001B1848[2];
extern float D_L16_001B1848_GP SDATA(D_L16_001B1848);
extern float D_L16_001B9B00[4], D_L16_001BFF60[4];
extern BeamDamageData D_L16_001A8F20 MACRO_ADDR;
extern int D_L16_001B2648;
extern void func_0029FC20(void *, int, void *), func_002830C0(void *, void *, void *);
extern float func_L16_00416EB8(char *);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_00282F70(void *, void *, float), func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *), func_00282D30(void *, void *, float);
extern void func_002A8C00(char *, int, int, float, BeamDamageData *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern u32 func_00283D38(u32, u32, float);
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, int, int);
extern int func_002A7820(int, int), func_00283CF0(float);
extern float func_002A78D8(float, float), func_002A7878(float, float);
extern void func_00282D08(void *, void *, void *, float);
/* Particle calls consume six/three GPR inputs and five/one FP inputs.
 * Both return their allocated pointer or null; this caller ignores those results. */
extern void *func_002C16C0(void *, void *, int, int, int, int, float, float, float, float, float);
extern void *func_002C6DD8(void *, void *, int, float);
extern void func_002A7A00(void *, float, float);

void func_L16_00412560(u8 *moby)
{
    BeamBatch batch[2];
    float bone[16] __attribute__((aligned(16)));
    float side[4] __attribute__((aligned(16)));
    float camera[4] __attribute__((aligned(16)));
    float ray[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    char effect[48] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float sample[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *object;
    int i, j, k, texture, seed;
    float size, speed;
    func_0029FC20(*(void **)(state + 0x1f0), 2, bone);
    func_002830C0(start, D_L16_001B16D0, bone);
    object = *(u8 **)(state + 0x24c);
    if (object) {
        qcopy(target, (object + 0x10));
        target[2] = func_L16_00416EB8((char *)object);
    } else qcopy(target, (state + 0x210));
    func_00282CF0(end, moby + 0x10, target);
    end[2] = -0.1f;
    func_00282F70(end, end, *(float *)(state + 0x250));
    func_00282CC0(end, end, target);
    func_002A8C00(effect, (int)moby, 0x90001, (float)state[0x36], &D_L16_001A8F20);
    if (func_002761F8(start, end, 0, moby, effect))
        qcopy_nc(end, D_L16_001BFF60);
    func_00282CF0(camera, D_L16_001B9B00, start);
    func_00282CF0(ray, end, start);
    func_00282DD8(side, ray, camera);
    func_00282F20(side, side, 1.0f);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            float *pos;
            batch[i].color[j] = func_00283D38(D_L16_001B1820[i] & 0xff000000,
                D_L16_001B1820[i], *(float *)(state + 0x254));
            batch[i].uv[j][0] = D_L16_001B1800_GP[j][0];
            batch[i].uv[j][1] = D_L16_001B1800[j][1];
            pos = batch[i].position[j];
            if (j & 1)
                func_00282D30(pos, side, D_L16_001B17F8[i]);
            else func_00282D30(pos, side, -D_L16_001B17F8[i]);
            if (j < 2) func_00282CC0(pos, pos, start);
            else func_00282CC0(pos, pos, end);
            pos[3] = 1.0f;
        }
        batch[i].packet[1] = func_0027C878(D_L16_001B17E8[i]);
        batch[i].packet[0] = 0;
        batch[i].packet[2] = 0xff9000000260UL;
        batch[i].packet[3] = 0x8000000048UL;
    }
    func_00280B90(&batch[0], 0, 1);
    func_00280B90(&batch[1], 0, 1);
    if (*(int *)(state + 0x258) != D_L16_001B2648) {
        *(int *)(state + 0x258) = D_L16_001B2648;
        func_00282CF0(delta, end, start);
        for (k = 0; k < D_L16_001B1828; k++) {
            texture = func_002A7820(D_L16_001B1840_GP, D_L16_001B1840[1]);
            seed = func_00283CF0(func_002A78D8(1.0f, 2.0f));
            size = func_002A7878(D_L16_001B1848_GP, D_L16_001B1848[1]) * 210000.0f;
            speed = func_002A7878(D_L16_001B1830[2], D_L16_001B1830[3]);
            func_00282F20(velocity, delta, speed * 0.016666668f);
            func_00282D08(sample, end, start, func_002A7878(0.0f, 1.0f));
            func_002C16C0(sample, velocity, texture, (int)D_L16_001B182C >> 24,
                D_L16_001B182C & 0xffffff, seed, size,
                500.0f, 1.0f, 0.0f, 1.0f);
            size = func_002A7878(10.0f, 20.0f);
            func_002C6DD8(sample, velocity, texture, size * 0.00027777778f);
            func_002A7A00(velocity, D_L16_001B1830_GP * 0.016666668f,
                D_L16_001B1830[1] * 0.016666668f);
            velocity[2] += func_002A7878(D_L16_001B1830[2], D_L16_001B1830[3]) * 0.016666668f;
            func_002C6DD8(end, velocity, texture, 0.0040555559f);
        }
    }
}
