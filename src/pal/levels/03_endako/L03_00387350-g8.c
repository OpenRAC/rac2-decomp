/* func_PAL_L03_00387350, the PAL copy of func_L03_003844D8: the same C, where 1.0f/60.0f becomes
 * 0.020000001f and the last three emitter values take the 50 Hz scale. */
#include "common.h"
typedef int ParticleQuad __attribute__((mode(TI)));
typedef struct { int id[16]; } ParticleIds;
extern char *D_L03_001B2B0C MACRO_ADDR;
extern float D_L03_001AEC40 __attribute__((sda)), D_L03_001AEC48 __attribute__((sda));
extern float D_L03_001AEC4C __attribute__((nosda)), D_L03_001AEC50 __attribute__((nosda)), D_L03_001AEC54 __attribute__((nosda));
extern float D_L03_001AEC58 __attribute__((sda)), D_L03_001AEC5C __attribute__((nosda)), D_L03_001AEC60 __attribute__((nosda)), D_L03_001AEC64 __attribute__((nosda));
extern unsigned int D_L03_001AEC68 __attribute__((sda)), D_L03_001AEC6C __attribute__((nosda)), D_L03_001AEC70 __attribute__((sda)), D_L03_001AEC74 __attribute__((nosda)), D_L03_001AEC78 __attribute__((nosda));
extern int func_00283DB8(void *, float);
extern float func_002A7878(float, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern void func_002BAA28(void *, void *, void *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, int);
void func_PAL_L03_00387350(char *m)
{
    float point[4], position[4], velocity[4], params[4];
    int i;
    ParticleIds *ids = *(ParticleIds **)(m + 0x68);
    for (i = 0; i < 16; i++) {
        int index = ids->id[i];
        char *base = D_L03_001B2B0C;
        if (index != -1) {
            char *entry = (char *)(index * 128 + (unsigned int)base);
            float count = D_L03_001AEC40 * *(float *)(entry + 0x7C);
            qcopy(point, entry + 0x30);
            point[3] = *(float *)(entry + 0x3C);
            if (func_00283DB8(point, 64) == -1) count *= 0.5f;
            while (count > 0) {
                if (count >= 1 || func_002A7878(0, 1) < count) {
                    unsigned int color;
                    *(ParticleQuad *)velocity = 0;
                    velocity[0] = func_002A7878(-0.9f, 0.9f);
                    velocity[1] = func_002A7878(-0.9f, 0.9f);
                    *(ParticleQuad *)position = *(ParticleQuad *)velocity;
                    func_00283098(position, position, D_L03_001B2B0C + ids->id[i] * 128);
                    func_00282CC0(position, position, D_L03_001B2B0C + ids->id[i] * 128 + 0x30);
                    {
                        float *p = velocity;
                        {
                            qzero_nc(p);
                        }
                    }
                    {
                        float upper = D_L03_001AEC4C;
                        float lower = D_L03_001AEC48;
                        velocity[2] = func_002A7878(lower, upper) * 0.020000001f;
                    }
                    {
                        float *p = params;
                        {
                            qzero_nc(p);
                        }
                    }
                    params[2] = func_002A7878(D_L03_001AEC50, D_L03_001AEC54) * 0.020000001f;
                    velocity[3] = func_002A7878(D_L03_001AEC58, D_L03_001AEC5C);
                    params[3] = func_002A7878(D_L03_001AEC60, D_L03_001AEC64);
                    {
                        float blend = func_002A7878(0, 1);
                        color = func_00283D38(D_L03_001AEC68, D_L03_001AEC6C, blend);
                    }
                    {
                        unsigned int flags = ((s32)D_L03_001AEC70 * 5 + 2) / 6;
                        unsigned int start = ((s32)D_L03_001AEC74 * 5 + 2) / 6;
                        unsigned int end = ((s32)D_L03_001AEC78 * 5 + 2) / 6;
                        func_002BAA28(position, velocity, params, color, color & 0xFFFFFF, flags, start, end, -1);
                    }
                }
                count -= 1;
            }
        }
    }
}
