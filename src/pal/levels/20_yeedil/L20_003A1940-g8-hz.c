/* func_PAL_L20_003A1940, the PAL copy of func_L20_0039E9F8: the same C, where 0.00027777778f
   becomes 0.00040000002f; 0.016666668f becomes 0.020000001f; 0.00087266474f becomes 0.0012566373f;
   0.052359886f becomes 0.062831864f. */
#include "common.h"

#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)

extern float D_L20_001AED10 __attribute__((sda));
extern float D_L20_001AED0C __attribute__((sda));
extern char *D_L20_001B308C __attribute__((nosda));

extern float FastAddRotations(float, float);
extern float FastDiffRots(float, float);
extern float math_approach_target_with_direction_mode(void *, float, float, float, float, void *, int);
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern float math_fabs(float);
extern int subtract_integer_with_clamp(int);
extern void vec_store_helper(char *);
extern void transform_vector(char *, char *, char *);

void func_PAL_L20_003A1940(char *obj) {
    char *state = FLD(obj, char *, 0x68);
    char *entry;
    float turn;
    float spin;
    float target;
    float r;

    entry = (char *)((FLD(state, int, 0x84) << 7) + (unsigned int)D_L20_001B308C);
    turn = D_L20_001AED10 * 0.00040000002f;
    spin = D_L20_001AED0C * 0.020000001f;
    target = FLD(entry, float, 0x78);
    if (FLD(state, int, 0x190) < 0) {
        target = FastAddRotations(target, 3.1415927f);
    }
    r = FastDiffRots(FLD(obj, float, 0xF8), target);
    if (r > 0.017453294f) {
        math_approach_target_with_direction_mode(obj + 0xF8, target, 0.0012566373f, 0.0012566373f, 0.062831864f,
                      state + 0x19C, 0);
    } else {
        math_step_value_toward_target(state + 0x194, state + 0x198, (float)FLD(state, int, 0x190), turn,
                      turn, spin);
        r = FLD(state, float, 0x194) * (float)FLD(state, int, 0x190);
        if (r > 0.0f) {
            target = math_fabs(FLD(state, float, 0x194));
            if ((float)subtract_integer_with_clamp(FLD(state, int, 0x190)) <= target) {
                FLD(state, int, 0x190) = -FLD(state, int, 0x190);
            }
        }
    }
    vec_store_helper(obj + 0x10);
    FLD(obj, float, 0x10) = FLD(state, float, 0x194);
    transform_vector(obj + 0x10, obj + 0x10, D_L20_001B308C + (FLD(state, int, 0x84) << 7));
}
