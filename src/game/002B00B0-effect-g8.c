#include "common.h"

typedef int EffectVector __attribute__((mode(TI)));

extern int D_001B1A20[] __attribute__((sda));
extern float D_001B1A18[] __attribute__((sda));
extern EffectVector D_001BAFA0 NOT_SDA;
extern float D_001B5340[4] NOT_SDA;
extern float D_001A9FCC __attribute__((sda));
extern void *D_001A9E74 __attribute__((sda));

extern float func_002B0520(void *);
extern int func_002761F8(void *, void *, int, int, int);
extern int func_00278E78(void);
extern float func_002A7878(float, float);
extern void *func_002C19D8(void *, float, void *, float, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E20(void *);
extern void func_002BA8A0(void *, int, int);

void func_002B0668(float *position)
{
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float *hit = start;
    float active = 0.0f;
    int kind;

    *(EffectVector *)start = *(EffectVector *)position;
    if (D_001B1A20[0]) {
        start[2] = func_002B0520(&start) + D_001B1A18[0];
        if (start[2] < D_001B5340[2] + 5.0f) {
            *(EffectVector *)end = *(EffectVector *)start;
            active = 1.0f;
            end[2] = end[2] - (D_001B1A18[0] + D_001B1A18[0]) - 2.0f;
        }
    } else if (start[0] > 0.0f && start[1] > 0.0f &&
               start[0] < 1024.0f && start[1] < 1024.0f) {
        *(EffectVector *)end = *(EffectVector *)position;
        end[2] = D_001B5340[2] - 20.0f;
        active = 1.0f;
    }

    if (active != 0.0f) {
        if (CollLine(hit, &end, 18, 0, 0)) {
            kind = GetCollHitMaterial();
            if (kind == 0 || kind == 4 || kind == 3) {
                float scale;

                *(EffectVector *)hit = D_001BAFA0;
                hit[2] += D_001A9FCC;
                scale = func_002A7878(0.4f, 0.6f);
                func_002C19D8(hit, scale, D_001A9E74, 5250.0f, -1);
            } else {
                FastVecSub(&offset, &D_001BAFA0, &D_001B5340);
                func_002BA8A0(&D_001BAFA0,
                    (unsigned char)(int)(vec_length_xy(&offset) * 3.1833334f + 64.0f), 0);
            }
        }
    }
}
