#include "common.h"
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

/* Draws the boss's laser beam from its body to its target, hurts whatever it hits and sprays sparks along the beam. */
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
    int j, k, texture, seed;
    float size, speed;
    float *pos;
    /* These named values are what retail's slot order measures: gcse's reaching registers
       take spill slots in hash-bucket order, with 157 buckets (312 insns when gcse starts)
       and the counter's pseudo at 145 or above. The block around the counter's loop serves
       the same purpose. Removing or adding one moves the spill slots. */
    int joint = 2;
    float drop = -0.1f;
    int layers = 0x90001;
    int ignore = 0;
    int lowerRow = 2;
    int drawFirst = 0;
    int drawCount = 1;
    void *body;
    float *muzzle;
    float *eye;
    BeamDamageData *damage;
    int shift = 24;
    float length;

    body = *(void **)(state + 0x1f0);
    TransformMobyJointPoint(body, joint, bone);
    muzzle = D_L16_001B16D0;
    transform_vector(start, muzzle, bone);
    object = *(u8 **)(state + 0x24c);
    if (object) {
        qcopy(target, (object + 0x10));
        target[2] = GetTurretHorizontalSpeed((char *)object);
    } else qcopy(target, (state + 0x210));
    FastVecSub(end, moby + 0x10, target);
    end[2] = drop;
    length = *(float *)(state + 0x250);
    FastVectorNormalizeHelper(end, end, length);
    FastVecAdd(end, end, target);
    damage = &D_L16_001A8F20;
    make_hit_descriptor(effect, (int)moby, layers, (float)state[0x36], damage);
    if (CollLine(start, end, ignore, moby, effect))
        qcopy_nc(end, D_L16_001BFF60);
    eye = D_L16_001B9B00;
    FastVecSub(camera, eye, start);
    FastVecSub(ray, end, start);
    FastVecCross(side, ray, camera);
    vec_scale_to_length(side, side, 1.0f);
    {
        int i;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 4; j++) {
                batch[i].color[j] = FastTweenColor(D_L16_001B1820[i] & 0xff000000,
                    D_L16_001B1820[i], *(float *)(state + 0x254));
                batch[i].uv[j][0] = D_L16_001B1800_GP[j][0];
                batch[i].uv[j][1] = D_L16_001B1800[j][1];
                pos = batch[i].position[j];
                if (j & 1)
                    FastVecScale(pos, side, D_L16_001B17F8[i]);
                else FastVecScale(pos, side, -D_L16_001B17F8[i]);
                if (j < lowerRow) FastVecAdd(pos, pos, start);
                else FastVecAdd(pos, pos, end);
                pos[3] = 1.0f;
            }
            batch[i].packet[1] = GetEffectTextureDescriptor(D_L16_001B17E8[i]);
            batch[i].packet[0] = 0;
            batch[i].packet[2] = 0xff9000000260UL;
            batch[i].packet[3] = 0x8000000048UL;
        }
    }
    draw_world_quad(&batch[0], drawFirst, drawCount);
    draw_world_quad(&batch[1], drawFirst, drawCount);
    if (*(int *)(state + 0x258) != D_L16_001B2648) {
        *(int *)(state + 0x258) = D_L16_001B2648;
        FastVecSub(delta, end, start);
        for (k = 0; k < D_L16_001B1828; k++) {
            texture = RandomIntRange(D_L16_001B1840_GP, D_L16_001B1840[1]);
            seed = FloatToInt(RandomSignedFloatRange(1.0f, 2.0f));
            size = RandomFloatRange(D_L16_001B1848_GP, D_L16_001B1848[1]) * 210000.0f;
            speed = RandomFloatRange(D_L16_001B1830[2], D_L16_001B1830[3]);
            vec_scale_to_length(velocity, delta, speed * 0.016666668f);
            lerp_vector(sample, end, start, RandomFloatRange(0.0f, 1.0f));
            SpawnBurstParticle_002C16C0(sample, velocity, texture, (int)D_L16_001B182C >> shift,
                D_L16_001B182C & 0xffffff, seed, size,
                500.0f, 1.0f, 0.0f, 1.0f);
            size = RandomFloatRange(10.0f, 20.0f);
            SpawnTrailParticle_002C6DD8(sample, velocity, texture, size * 0.00027777778f);
            RandomDirectionVector(velocity, D_L16_001B1830_GP * 0.016666668f,
                D_L16_001B1830[1] * 0.016666668f);
            velocity[2] += RandomFloatRange(D_L16_001B1830[2], D_L16_001B1830[3]) * 0.016666668f;
            SpawnTrailParticle_002C6DD8(end, velocity, texture, 0.0040555559f);
        }
    }
}
