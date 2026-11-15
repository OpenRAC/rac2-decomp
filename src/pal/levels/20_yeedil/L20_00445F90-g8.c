#include "include_asm.h"
#include "names.h"

extern float D_L20_001B2110 __attribute__((sda));
extern float D_L20_001B2114 __attribute__((sda));
extern float D_L20_001B2118 __attribute__((sda));
extern float D_L20_001B211C __attribute__((sda));
extern void moby_set_controller_speed_limits(char *, float, float, float, float);

void func_PAL_L20_00447B78(char *arg0) {
    moby_set_controller_speed_limits(arg0, D_L20_001B2114 * 0.00040000002f,
                  D_L20_001B2110 * 0.020000001f,
                  D_L20_001B2118 * 6.981318e-06f,
                  D_L20_001B211C * 0.0003490659f);
}

extern float D_L20_001B213C __attribute__((sda));
extern float D_L20_001B2140 __attribute__((sda));
extern float D_L20_001B2144 __attribute__((sda));
extern float D_L20_001B2148 __attribute__((sda));

void func_PAL_L20_00448178(char *arg0, float f) {
    char *state = *(char **)(arg0 + 0x68);

    moby_set_controller_speed_limits(arg0, D_L20_001B2140 * 0.00040000002f,
                  D_L20_001B213C * 0.020000001f,
                  D_L20_001B2148 * 6.981318e-06f,
                  D_L20_001B2144 * 0.0003490659f);
    *(float *)(state + 0x84) = f;
}
