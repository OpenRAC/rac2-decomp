/* Retained reconstruction, USA v1.01, game -O2 -G0 -ffunction-sections.
 * 568/572 bytes; the object loop, real 64-bit renderer fields and color
 * interpolation ABI are reconstructed. The 16-bit kind snapshot bypasses
 * retail's V0-to-A1 copy, with two remaining render-argument move-order ties.
 * Two unsigned local widths tie; a signed header view contracts to552 bytes.
 * The child pointer is read after interpolation, matching the actual access.
 * No forced reads, raw aliases or fabricated return/parameter types.
 * No strict linked match. Next: grounded kind-value/lifetime evidence.
 */
#include "common.h"

extern u16 *D_L02_001FC060[];
extern unsigned char *D_L02_001B359C __attribute__((sda));
extern int func_002A8508(int, int);
extern float func_00283B98(float, float);
/* Two 32-bit color words and one FP phase; bank order and return stay canonical. */
extern int func_L01_0031BC68(float, int, int);
/* Canonical renderer helper: all four packed fields are full EE 64-bit words. */
extern void func_002A0468(u64 *, u64, u64, u64, u64);

void func_L02_003C51F8(unsigned char *self, int first_color, int second_color)
{
    unsigned char *state = *(unsigned char **)(self + 0x68);
    unsigned char *actor, *child_state, *child;
    u16 *entry;
    unsigned int kind;
    if (func_002A8508(self[0x21], -1) < 2)
        return;
    entry = D_L02_001FC060[self[0x21]];
    *(float *)(state + 0x128) = func_00283B98(*(float *)(state + 0x128), 0.10471977293491364f);
    do {
        actor = D_L02_001B359C + (*entry & 0x7FFF) * 0x100;
        if (self[0x20] == 7) {
            if (*(s16 *)(actor + 0xAA) != 0x896) {
                func_002A0468((u64 *)actor,
                    func_L01_0031BC68(*(float *)(state + 0x128), 0x5050DD, 0x505050),
                    14, 14, 14);
                if (*(s16 *)(actor + 0xAA) == 0x873) {
                    child_state = *(unsigned char **)(actor + 0x68);
                    func_002A0468(*(u64 **)(child_state + 0x1C),
                        func_L01_0031BC68(*(float *)(state + 0x128), 0x5050DD, 0x505050),
                        14, 14, 14);
                }
            }
        } else {
            if (*(s16 *)(actor + 0xAA) != 0x896) {
                func_002A0468((u64 *)actor, 0x505010, 14, 14, 14);
                if (*(s16 *)(actor + 0xAA) == 0x873) {
                    func_002A0468(*(u64 **)(*(unsigned char **)(actor + 0x68) + 0x1C),
                                   0x505010, 14, 14, 14);
                }
            }
        }
        kind = *(u16 *)(actor + 0xAA);
        if ((u16)(kind - 0xAF9) < 3 || (s16)kind == 0xAFD ||
            (s16)kind == 0xAFC || (s16)kind == 0xB03 || (s16)kind == 0x873) {
            if ((s16)kind == 0x873) {
                int interpolated;
                child_state = *(unsigned char **)(actor + 0x68);
                interpolated = func_L01_0031BC68(*(float *)(state + 0x128),
                                                 first_color, second_color);
                child = *(unsigned char **)(child_state + 0x1C);
                *(int *)(child + 0x78) = interpolated;
            } else {
                *(int *)(actor + 0x78) = func_L01_0031BC68(*(float *)(state + 0x128), first_color, second_color);
            }
        }
    } while ((s16)*entry++ >= 0);
}
