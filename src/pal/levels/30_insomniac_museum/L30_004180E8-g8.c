#include "common.h"

/* func_PAL_L30_004180E8, the PAL copy of func_L12_00424078: the same C, where the period in word 8
   is scaled to 50 Hz and the frame counter is read with lui/lw instead of through $gp. The scale
   builds in the local's own register (retail's sll/addu/addiu/mflo all target it) only outside a
   loop's preserved subexpressions, so both loops call an inline helper that holds the colour.

   A unit of its own: -g (config/cflags.txt) gives the line label that
   puts retail's two-nop floor in front of each div.s (docs/COMPILER-NOTES.md, "Division/root
   scheduling and padding"), and -G8 is the template's flag. */

extern u8 *D_L12_001B2E9C[3] __attribute__((sda)); /* entity base, read bare (lui/lw) */
extern s16 *D_L12_001FB960[];
extern int D_L12_001B29C8;
extern char D_L12_001B2040[], D_L12_001B2070[];
extern void func_0026FEB8(void *, int);
extern void func_L12_0031E1D0(void *, int, int);
extern int func_002A8508(int, int);
extern float func_00283CE0(int);
extern int func_L01_0031BC68(int, int, float);

static inline int pulse_colour(int *vars) {
    int period = ((s32)(vars[8]) * 5 + 2) / 6;
    float phase = func_00283CE0(D_L12_001B29C8 % period) * 6.2831855f / func_00283CE0(period) - 3.1415927f;

    return func_L01_0031BC68(vars[10], vars[11], phase);
}

/* State 0 packs two colours from the byte values in words 0-3 and 4-7 into words 10 and 11
 * and counts the target ids in words 12-15 (up to four, ended by -1) into word 9; state 1,
 * once func_002A8508 reports two or more for its group (+0x21), sets the colour (+0x78) of each
 * group member whose +0x31 flag is set; states 1 and 2 set it on the counted targets. The colour
 * comes from func_L01_0031BC68 with words 10 and 11 and a phase angle of D_L12_001B29C8 modulo
 * the period in word 8. */
void func_PAL_L30_004180E8(u8 *obj) {
    int *vars = *(int **)(obj + 0x68);
    int i;
    int n;
    int first;
    int second;
    s16 *ids;
    u8 *member;

    switch (obj[0x20]) {
    case 0:
        n = 0;
        first = vars[3] << 24; first |= vars[2] << 16; first |= vars[1] << 8; first |= vars[0];
        vars[10] = first;
        second = vars[7] << 24; second |= vars[6] << 16; second |= vars[5] << 8; second |= vars[4];
        vars[11] = second;
        vars[9] = 0;
        if (vars[12] != -1) {
            vars[9] = 1;
            do {
                if (++n >= 4) break;
                if (vars[12 + n] == -1) break;
                vars[9]++;
            } while (1);
        }
        if (vars[9]) {
            func_0026FEB8(D_L12_001B2040, *(s16 *)(obj + 0xB2));
            func_L12_0031E1D0(obj, 2, -1);
        } else {
            func_0026FEB8(D_L12_001B2070, *(s16 *)(obj + 0xB2));
            func_L12_0031E1D0(obj, 1, -1);
        }
        break;
    case 1:
        if (func_002A8508(obj[0x21], -1) >= 2) {
            ids = D_L12_001FB960[obj[0x21]];
            do {
                member = D_L12_001B2E9C[0] + ((*(u16 *)ids & 0x7FFF) << 8);
                if (member[0x31]) {
                    *(int *)(member + 0x78) = pulse_colour(vars);
                }
            } while (*ids++ >= 0);
        }
    case 2:
        for (i = 0; i < vars[9]; i++) {
            u8 *target = D_L12_001B2E9C[0] + (vars[12 + i] << 8);
            if (target[0x31]) {
                *(int *)(target + 0x78) = pulse_colour(vars);
            }
        }
        break;
    }
}
