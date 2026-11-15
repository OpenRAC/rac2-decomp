#include "include_asm.h"
#include "names.h"

/* func_L26_003D4930 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef int TI128 __attribute__((mode(TI)));

extern int D_L26_001B1C38 __attribute__((sda));

extern u8 *D_L26_001B1C1C_1[3] __attribute__((sda));

extern u16 *D_L26_001FA6E0[];

extern int D_L26_001B1748;

extern void mat_get_euler_angles(u8 *, u8 *);

extern void mat_build_rotation_from_angles(u8 *, u8 *);

extern void gfx_add_draw_callback_first(void *, u8 *);

extern void part_submit_group_trail_effects(u8 *a0);

/* Every 8th tick of the frame word D_L26_001B1748 the object's ring of eight samples advances; the
   object's rotation angles are refreshed from its matrix, the matrix of the current slot is
   rebuilt from them and the object's position vector is copied into the slot's 16-byte record.
   When the state's stamp (+0x19C) differs from the frame word, every entity of the object's group
   is stamped and the object is registered with func_L26_003D4AE8 first. */
void trail_advance_samples(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);
    u16 *p;
    u8 *e;
    float phase;

    if (*(int *)(state + 0x19C) != D_L26_001B1748) {
        for (p = D_L26_001FA6E0[a0[0x21]];
             a0[0x21] != 0xFF && a0[0x21] <= D_L26_001B1C38 && p != 0 &&
             ((p != 0 && (short)p[-1] >= 0) || p == D_L26_001FA6E0[a0[0x21]]);
             p++) {
            e = D_L26_001B1C1C_1[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            *(int *)(*(u8 **)(e + 0x68) + 0x19C) = D_L26_001B1748;
        }
        gfx_add_draw_callback_first((void *)part_submit_group_trail_effects, a0);
    }
    phase = (float)(D_L26_001B1748 % 8) * 0.125f;
    *(float *)(state + 0x198) = phase;
    if (phase == 0.0f) {
        *(int *)(state + 0x194) = (*(int *)(state + 0x194) + 1) % 8;
        if (*(int *)(state + 0x190) < 8)
            *(int *)(state + 0x190) = *(int *)(state + 0x190) + 1;
    }
    mat_get_euler_angles(a0 + 0xC0, a0 + 0xF0);
    mat_build_rotation_from_angles(state + 0x100 + *(int *)(state + 0x194) * 16, a0 + 0xF0);
    *(TI128 *)(state + 0x80 + *(int *)(state + 0x194) * 16) = *(TI128 *)(a0 + 0x10);
}
