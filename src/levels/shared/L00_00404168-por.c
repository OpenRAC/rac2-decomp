#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_00282DF0(void *);
extern float func_002A7940(void);
extern void func_00281EB8(void *, int, unsigned int, int, float, float, float);
extern void func_L00_002ECFE8(void *, void *, int, unsigned int, unsigned int, float, float, float, int);

void func_L00_00404168(char *arg) {
    float v[4];
    char *pl = *(char **)(arg + 0x68);
    float f;
    float t;

    *(TI128 *)v = 0;
    v[3] = 1.0f;
    f = *(float *)(pl + 0x14) - 0.1f;
    *(float *)(pl + 0x14) = f;
    if (f <= -8.0f) {
        *(float *)(pl + 0x14) = f + 8.0f;
    }
    t = FastVecLength(pl);
    *(float *)(pl + 0x18) = *(float *)(pl + 0x18) + t;
    func_00281EB8(arg + 0x10, 0x31, 0x40801010, 1, 0.2f, 0.0f, func_002A7940());
    func_00281EB8(arg + 0x10, 0x31, 0x707F7F7F, 1, 0.1f, 0.0f, func_002A7940());
    func_00281EB8(arg + 0x10, 0x2F, 0x407F7F7F, 1, 0.05f, 0.0f, func_002A7940());
    if (*(float *)(pl + 0x18) > 1.0f) {
        DrawOrientedQuadsAtPoints(arg, v, 1, 0x7F804040, 0x00804040, 0.03f, 1.2f, *(float *)(pl + 0x14), 0x17);
        DrawOrientedQuadsAtPoints(arg, v, 1, 0x7F801010, 0x00801010, 0.1f, 1.2f, *(float *)(pl + 0x14), 0x17);
        DrawOrientedQuadsAtPoints(arg, v, 1, 0x7F801010, 0x00801010, 0.1f, 1.2f, *(float *)(pl + 0x14), 0x17);
    }
}

