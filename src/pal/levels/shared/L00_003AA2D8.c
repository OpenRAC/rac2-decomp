#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003AA2D8);

#include "common.h"
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern char *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
typedef struct { char prefix[0xD4]; unsigned char *material; } SceneMaterialPrefix;
extern SceneMaterialPrefix D_L00_001FE940;
extern char D_L00_001A8F20[] __attribute__((sda));

/* Emit the two layers of a short particle trail. */
void func_PAL_L00_003AAFC8(char *moby)
{
    float point[3], offset[3], step[3], jitter[3];
    float *state = (float *)(*(char **)(moby + 0x68) + 0x14);
    float size = 0.175f;
    int i;
    point[0] = state[0];
    point[1] = state[1];
    point[2] = state[2];
    point[3] = 0.0f;
    func_00282D30(offset, moby + 0xD0, -0.1f);
    func_00282CC0(point, point, offset);
    func_00282D30(step, moby + 0xE0, 0.15f);
    func_00282CC0(point, point, step);
    func_00282D30(step, moby + 0xE0, -0.03333333507f);
    for (i = 8; i >= 0; i--) {
        char *particle;
        int rotation;
        jitter[0] = point[0] + func_002A78D8(0.0f, 0.1f);
        jitter[1] = point[1] + func_002A78D8(0.0f, 0.1f);
        jitter[2] = point[2] + func_002A78D8(0.0f, 0.1f);
        rotation = func_002A77E0(255);
        func_002C65A0(jitter, D_L00_001A8F20, 3, 0x808080, rotation, 127, 127,
                      size * 210000.0f, size * 210000.0f, 0.0f, 1);
        particle = func_002C65A0(point, D_L00_001A8F20, 3, 0x203080, rotation, 16, 16,
                                 262500.0f, 262500.0f, 0.0f, 1);
        if (particle)
            *(unsigned char *)(particle + 2) = *D_L00_001FE940.material;
        func_00282CC0(point, point, step);
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003AB208);


