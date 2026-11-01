#include "include_asm.h"

#include "common.h"
extern void func_002E5E58(int, int, int);
extern char D_00138180[];
extern int D_001ABCA0 __attribute__((sda));
extern short D_001B2028[] MACRO_ADDR;
extern u8 D_00261C08[];
extern u8 D_001A7B30[] MACRO_ADDR;
extern u8 D_001A7AF8[] MACRO_ADDR;
extern u8 D_001395B8[];
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_001A8CEC MACRO_ADDR;
extern void func_002AD7B8(int);
extern void func_PAL_002B1588(int, int);

/* Corresponds to RAC1 process_unlock_code_input. */
void func_PAL_002DECA0(void) {
    char *pad = D_00138180;
    int lim0, lim;
    int va, vb, vc;
    int pressed, direction, j, code, index, matched;
    if ((*(long *)(pad + 0x1C0) & 0xF) == 6) {
        pressed = *(int *)(pad + 0x1C4);
        if (!(pressed & 0xF0A0)) return;

        if (D_001ABCA0 >= 20) return;
        if (pressed & 0x1000) direction = 0;
        else if (pressed & 0x4000) direction = 1;
        else if (pressed & 0x8000) direction = 2;
        else if (pressed & 0x2000) direction = 3;
        else direction = (pressed & 0x80) ? 4 : 5;
        D_001B2028[D_001ABCA0] = direction;
        D_001ABCA0 += 1;
        if (D_001ABCA0 != 20) return;
        code = -1;
        index = 2;
        lim0 = 0x93;
        lim = *(int *)&lim0;
        for (; index < lim; index++) {
            matched = 1;
            for (j = 0; j < 20; j++) {
                if (D_001B2028[j] != D_00261C08[(j * index + index) & 0xff]) {
                    matched = 0;
                    break;
                }
            }
            if (matched) {
                code = index - 2;
                break;
            }
        }
        if (code == -1) return;
        va = code - 55;
        vb = code - 74;
        vc = code - 80;
        if (code < 56) {
            D_001A7AF8[code] = 1;
            D_001A7B30[code] = 1;
        } else if ((unsigned)(code - 56) < 18) {
            func_002AD7B8(va);
        } else if ((unsigned)vb < 6) {
            D_001395B8[vb] = 1;
        } else if ((unsigned)vc < 30) {
            if (!D_001A7A60[vc]) {
                D_001A7A60[vc] = 1;
                func_002E5E58(1, 0, 0);
                func_PAL_002B1588(0x1233, -1);
                D_001A8CEC = 1;
            }
        }
    } else {
        D_001ABCA0 = 0;
    }
}
