#include "include_asm.h"

#include "common.h"
extern f32 ref_L06_003E4F08_00 __attribute__((sda));
extern f32 ref_L06_003E4F08_01 __attribute__((sda));
extern f32 ref_L06_003E4F08_02 __attribute__((sda));
extern f32 ref_L06_003E4F08_03 __attribute__((sda));
extern f32 ref_L06_003E4F08_04 __attribute__((sda));
extern void ref_L06_003E4F08_05(void *, void *, void *, f32, f32, f32);
extern void ref_L06_003E4F08_06(void *, void *, void *, f32, f32, f32);

/* Turns the two moving parts of the object toward their targets, except while it is in states 5 or 7 (PAL: 50 Hz rates). */
void moby_turn_parts_toward_targets_pal(void *moby) {
    u8 state;
    s8 *vars;

    state = (*(u8 *)((s8 *)(moby) + (0x20)));
    vars = (*(s8 **)((s8 *)(moby) + (0x68)));
    if ((state != 5) && (state != 7)) {
        ref_L06_003E4F08_05(moby, vars + 0xEC, vars + 0xE8, ref_L06_003E4F08_00, ref_L06_003E4F08_01 * 0.0003490659f, (*(f32 *)((s8 *)(vars) + (0x108))));
    }
    ref_L06_003E4F08_06(moby, vars + 0xF0, vars + 0xF4, ref_L06_003E4F08_02, ref_L06_003E4F08_03 * 0.0003490659f, ref_L06_003E4F08_04 * 0.0003490659f);
}
