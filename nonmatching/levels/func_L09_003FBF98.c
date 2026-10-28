/* func_L09_003FBF98 - 588 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L09_003FBF98 (588 B). Dropped as far: draft decodes the whole body
   (slot walk over D_L09_00255E90[16] {obj,other}, D_L09_001B35E0[i] state,
   D_L09_001B37E0[i] float fade, D_L09_00256510 0x60-byte records, two
   func_L09_003FC1E8 calls, final
   func_L08_00389B68(2,0x47,0x5340B,0x42,0x8000000044)), needs `#include
   "common.h"` for qcopy, vec/dir order (dir at sp+0, vec at sp+0x10). But it
   compiles to 644 B vs 588: with all 9 saved registers in use mine hoists the
   table bases (lui/addiu of A, F) into spill slots, retail recomputes
   `lui/addiu/addu` of D_L09_001B35E0 and D_L09_001B37E0 per iteration and
   only keeps B ptr ($s4), D_L09_00256510 ($fp). ~146 masked diff lines.
   Incomplete-array declarations did not change it. */

typedef struct {
    u8 *obj;
    u8 *other;
} Slot_L09_003FBF98;
extern Slot_L09_003FBF98 D_L09_00255E90[];
extern int D_L09_001B35E0[];
extern f32 D_L09_001B37E0[];
extern u8 D_L09_00256510[];
extern void func_002FC560(u32, unsigned long);
extern void func_00282D48(void *, void *, f32);
extern int func_00283DB8(void *, f32);
extern int func_L02_002F1658();
extern void func_L09_003FCA58(u8 *, int, int);
extern void func_L09_003FC1E8(int, int, void *, int, int, int, int, int);
extern void func_L08_00389B68(int, int, int, int, unsigned long);

void func_L09_003FBF98(u8 *a0) {
    int *s7 = *(int **)(a0 + 0x68);
    f32 dir[4] __attribute__((aligned(16)));
    f32 vec[4] __attribute__((aligned(16)));
    int i;
    int id;
    int s3;
    u8 *s2;
    int s0;
    int s1;
    f32 f;

    func_002FC560(0x47, 0x51001);
    for (i = 0; i < 16; i++) {
        if (D_L09_00255E90[i].obj == 0) {
            continue;
        }
        if (D_L09_00255E90[i].other == 0) {
            continue;
        }
        if (D_L09_001B35E0[i] < 2) {
            continue;
        }
        func_00282CC0(vec, D_L09_00255E90[i].obj + 0x10, D_L09_00255E90[i].other + 0x10);
        qcopy(dir, vec);
        func_00282D48(vec, dir, 0.5f);
        dir[3] = func_00282E48(D_L09_00255E90[i].obj + 0x10, D_L09_00255E90[i].other + 0x10) * 0.52f;
        id = func_00283DB8(dir, 64.0f);
        if (id == -1) {
            continue;
        }
        s3 = D_L09_00255E90[i].obj[0x23];
        if (func_L02_002F1658() != 0) {
            f = D_L09_001B37E0[i] - 0.2f;
            D_L09_001B37E0[i] = f;
            if (f <= -8.0f) {
                D_L09_001B37E0[i] = f + 8.0f;
            }
        }
        s2 = D_L09_00256510 + (i * 2 + 1) * 0x60;
        func_L09_003FCA58(D_L09_00255E90[i].obj, i, s3);
        s0 = s7[0] + 0x3F;
        s1 = s7[1] + 0x3F;
        func_L09_003FC1E8(s1, s0, D_L09_00256510 + i * 2 * 0x60, 0x80, 0x40, s3, i, -1);
        func_L09_003FC1E8(s1, s0, s2, 0x30, 0x10, s3, i, func_002A7820(1, 6));
    }
    func_L08_00389B68(2, 0x47, 0x5340B, 0x42, 0x8000000044UL);
}
