#include "names.h"
/* func_00313600: -G8 unit, so the two float scales are $gp reads. func_002ACEC0 has its
 * real prototype (the draft called it undeclared), and the loop indexes the two tables,
 * which strength reduction turns into retail's pointer pair and %hi registers. */
/* func_00313600 - 116 bytes, 1 place (the boot only).
   Retail at 0x00313600: the eight resident entries at 0x229B70 are turned
   around the axis at 0x229BF0 (func_002ACEC0 with the angle in small data,
   then func_00282F20 with the other small-data scale), the axis walks by
   0x10 and the entry by 0x10 per step, and the loop counts down from 7.
   The candidate below is that body and every instruction of it matches
   except the two %hi registers: retail keeps the axis' high half in $v0 and
   the table's in $v1, this cc1 gives them the other way round. The order of
   the declarations does not move the registers (measured: swapping the two
   declarations changes nothing) and the register follows the first use, so
   the axis would have to be used before the table entry - which the call's
   argument order forbids.
   The draft needs a -g8.c source unit (the two angles are small data) and
   the D_ names carry the boot's addresses. */
extern char D_00229BF0[];
extern char D_00229B70[];
extern float D_001AF108 __attribute__((sda));
extern float D_001AF130 __attribute__((sda));
extern void vec_scale_to_length(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);

void update_nanotech_ball_slot_offsets(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        char *entry = D_00229B70 + i * 16;
        math_apply_axis_rotation_to_quat(entry, entry, D_00229BF0 + i * 16, D_001AF108);
        vec_scale_to_length(entry, entry, D_001AF130);
    }
}
