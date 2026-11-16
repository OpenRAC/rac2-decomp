#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));
extern f32 math_fabs(f32 f);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern void matrix_mul_vec3(f32 *, const f32 *, const f32 *);
extern void FastVecAdd(char *, char *, char *);
extern f32 FastAddRotations(f32, f32);
extern f32 ApproachValue(f32 *, f32, f32);
extern float ref_L22_003F5580_00 __attribute__((sda));
extern f32 FastVecDot(void *, void *);
extern f32 IntToFloat(int);
extern f32 math_lerp_float(f32, f32, f32);
extern u8 g_tether_origin[];
extern f32 g_linked_toggle_near_b __attribute__((sda));
extern f32 g_linked_toggle_far_b __attribute__((sda));
extern f32 g_linked_toggle_near_a __attribute__((sda));
extern f32 g_linked_toggle_far_a __attribute__((sda));
extern u8 *g_toggle_link_table_b;
extern u8 *g_toggle_link_table_a;

/* Scales the controller of the object: when the controller is idle its position is copied to
 * the object, otherwise the controller's values are scaled and written back.
 */
void sway_update_decaying_pal(u8 *obj) {
    u8 *vars = *(u8 **)(obj + 0x68);
    f32 offset[4];
    f32 phase_sin, amount, dx, dy, decay_rate, new_phase;

    if (*(f32 *)(vars + 0xBC) == 0.0f) {
        if (*(f32 *)(vars + 0xC0) == 0.0f)
            return;
        *(TI128 *)(obj + 0xE0) = *(TI128 *)vars;
        *(f32 *)(vars + 0xC0) = 0.0f;
        return;
    }
    phase_sin = math_fast_sin_or_cos_b(*(f32 *)(vars + 0xC4));
    amount = *(f32 *)(vars + 0xBC);
    dx = math_fast_sin_or_cos_a(*(f32 *)(vars + 0xB0));
    amount = amount * phase_sin;
    dx = dx * amount;
    offset[0] = dx;
    dy = math_fast_sin_or_cos_b(*(f32 *)(vars + 0xB0));
    dy = dy * amount;
    offset[1] = dy;
    offset[2] = 0.0f;
    matrix_mul_vec3(offset, offset, obj + 0xC0);
    offset[3] = 0.0f;
    FastVecAdd(obj + 0xE0, offset, vars);
    new_phase = FastAddRotations(*(f32 *)(vars + 0xC4), *(f32 *)(vars + 0xC0));
    decay_rate = ref_L22_003F5580_00;
    *(f32 *)(vars + 0xC4) = new_phase;
    ApproachValue((f32 *)(vars + 0xBC), 0.0f, decay_rate * (0.020000001f));
}
