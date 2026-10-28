/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/levels/shared/L01_00326DD8-qcopy.c
 * Game profile: -O2 -G0 -ffunction-sections
 * Compiled/retail bytes: 504/512. US: 0/3; US2: 0/3; PAL: 0/3.
 * Residual and reopening condition: The retained stack-vector base register and the initializer/copy ordering differ. Default TI copies preserve the required displaced particle stores; forcing qcopy changed them. Scope-local defaults recover the original frame. Reopen with a truthful shared-stack lifetime model.
 * Field views describe only measured prefixes, not complete game-object extents.
 */

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern unsigned char *func_002B9030(int type);
extern float func_002A7878(float min, float max);
extern void func_00282F20(void *out, void *in, float scale);
extern int func_00283CF0(float value);
extern void func_00282CC0(void *out, void *a, void *b);
extern unsigned char *D_L01_001FF040;

void func_L01_00326DD8(void *position, int mode, void *direction, float value)
{
    float vectors[3][4] __attribute__((aligned(16)));
    unsigned char *particle;
    int shade;
    int step;
    float speed;
    float magnitude;
    *(Quad *)vectors[0] = *(Quad *)direction;
    particle = func_002B9030(0);
    if (particle) {
        shade = 0;
        step = mode;
        speed = 0.0f;
        magnitude = 0.0f;
        switch (step) {
        case 0:
            magnitude = func_002A7878(0.01f, 1.0f);
            speed = 0.015f;
            shade = 20;
            break;
        case 1:
            magnitude = func_002A7878(1.0f, 5.0f);
            speed = 0.5f;
            shade = 13;
            break;
        case 2:
            magnitude = func_002A7878(20.0f, 30.0f);
            speed = 1.0f;
            shade = 13;
            step = 1;
            break;
        }
        *(Quad *)vectors[1] = *(Quad *)vectors[0];
        func_00282F20(vectors[1], vectors[1], magnitude);
        *(short *)(particle + 0xA) = mode;
        *(int *)(particle + 4) = ((shade >> 2) << 24) | 0x606060;
        *(int *)(particle + 0xC) = (shade << 24) | 0x907070;
        particle[9] = func_00283CF0(4.0f) + 96;
        particle[3] = 0x44;
        particle[1] = 3;
        particle[2] = D_L01_001FF040[step];
        *(Quad *)(particle + 0x10) = *(Quad *)position;
        func_00282CC0(vectors[2], position, vectors[1]);
        *(Quad *)(particle + 0x20) = *(Quad *)vectors[2];
        *(float *)(particle + 0x1C) = speed;
        *(float *)(particle + 0x2C) = 1.0f;
        *(Quad *)(particle + 0x30) = *(Quad *)vectors[0];
        *(float *)(particle + 0x3C) = value;
    }
}
