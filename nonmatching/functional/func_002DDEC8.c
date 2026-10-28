/* functional: high. Cheat-code entry: records the pressed pad button, and once 20 are in, searches the 147-entry code table; the near-miss draft below is behaviourally identical to retail, only the compiled loop shape differs. */
/* M12, 2026-10-26: complete C, not linked. -O2 -G8. 532/520 bytes (us boot, 28 places).
 * The top level (if/else on the pad mode, the bit chain, the five unlock ranges) matches retail.
 * Residual: the code search loops. Retail does no strength reduction in the inner loop (mult
 * j*i and sll j,1 every pass, test at the top after j++), compares table[0] with codes[(u8)i]
 * before it, and keeps the outer bound 147 in a register (slt), so the bound is likely a
 * variable. A goto inner loop gets the mult but still walks the table pointer.
 */
#include "common.h"
typedef union { u8 b[0x200]; u32 u[0x80]; u64 d[0x40]; } Pad;
extern char D_00138180[];
extern int D_001ABCA0 __attribute__((sda));
extern short D_001B2028[];
extern u8 D_00261C08[];
extern u8 D_001A7B30[] MACRO_ADDR;
extern u8 D_001A7AF8[] MACRO_ADDR;
extern u8 D_001395B8[] MACRO_ADDR;
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_001A8CEC MACRO_ADDR;
extern void func_002AD7B8(int);
extern int func_002E5E58(int, unsigned int, void *);
extern void func_002B0A18(int, int);

/* Records the pressed button into the cheat buffer and, once it is full, unlocks the code it spells. */
void func_002DDEC8(void) {
    u32 buttons;
    int value, i, j, match, found;
    if ((((Pad *)D_00138180)->d[0x1C0 / 8] & 0xF) == 6) {
        buttons = ((Pad *)D_00138180)->u[0x1C4 / 4];
        if (!(buttons & 0xF0A0)) return;
        if (D_001ABCA0 >= 20) return;
        if (buttons & 0x1000) value = 0;
        else if (buttons & 0x4000) value = 1;
        else if (buttons & 0x8000) value = 2;
        else if (buttons & 0x2000) value = 3;
        else value = (buttons & 0x80) ? 4 : 5;
        D_001B2028[D_001ABCA0] = value;
        D_001ABCA0++;
        if (D_001ABCA0 != 20) return;
        found = -1;
        for (i = 2; i < 147; i++) {
            match = 1;
            if (D_001B2028[0] == D_00261C08[(u8)i]) {
                for (j = 1; j < 20; j++) {
                    if (D_001B2028[j] != D_00261C08[(u8)(j * i + i)]) { match = 0; break; }
                }
            } else match = 0;
            if (match) { found = i - 2; break; }
        }
        if (found == -1) return;
        if (found < 56) {
            D_001A7B30[found] = 1;
            D_001A7AF8[found] = 1;
        } else if ((unsigned)(found - 56) < 18) {
            func_002AD7B8(found - 55);
        } else if ((unsigned)(found - 74) < 6) {
            D_001395B8[found - 74] = 1;
        } else if ((unsigned)(found - 80) < 30) {
            if (!D_001A7A60[found - 80]) {
                D_001A7A60[found - 80] = 1;
                func_002E5E58(1, 0, 0);
                func_002B0A18(0x1233, -1);
                D_001A8CEC = 1;
            }
        }
    } else
        D_001ABCA0 = 0;
}
