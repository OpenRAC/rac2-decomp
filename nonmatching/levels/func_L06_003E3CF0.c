/* Nonmatching C reconstruction.
 * Profile: -O2 -G0 -ffunction-sections -frac2-keep-block-order.
 * Emitted/retail size: 444/476 bytes.
 * us: 0 of 5 places match.
 * pal: ABSENT.
 * us2: ABSENT.
 * No strict linked build was run for this draft.
 * Equivalent message-call tails are merged more aggressively than retail. The default profile and keep-block-order control tie. Reopen with measured source block boundaries or jump-pass evidence; do not add dead branches.
 */
#include "common.h"
extern int D_001A79F0[] __attribute__((sda));
extern int func_002B0C28(int, int, int);
void func_L06_003E3CF0(char *object, int event)
{
    char *state = *(char **)(object + 0x68);
    switch (event) {
    case 0:
        if (D_001A79F0[0] == 13) {
            if (*(int *)(state + 0x100) == 0)
                func_002B0C28(8, 0x27e4, 1);
            else
                func_002B0C28(8, 0x2793, 1);
        } else if (D_001A79F0[0] == 18) {
            if (*(int *)(state + 0x100) != 0)
                func_002B0C28(8, 0x2793, 1);
            else
                func_002B0C28(8, 0x27e7, 1);
        } else {
            func_002B0C28(8, 0x2793, 1);
        }
        break;
    case 1:
        if (D_001A79F0[0] == 9)
            func_002B0C28(8, 0x27ca, 1);
        else if (D_001A79F0[0] == 18) {
            if (*(int *)(state + 0x100) == 0)
                func_002B0C28(8, 0x27e7, 1);
            else
                func_002B0C28(8, 0x27fd, 1);
        } else if (D_001A79F0[0] == 12)
            func_002B0C28(8, 0x279c, 1);
        else if (D_001A79F0[0] == 13) {
            if (*(int *)(state + 0x100) == 0)
                func_002B0C28(8, 0x2793, 1);
            else
                func_002B0C28(8, 0x27e5, 1);
        } else if (D_001A79F0[0] == 11) {
            if (*(int *)(state + 0x100) != 0)
                func_002B0C28(8, 0x27c2, 1);
            else
                func_002B0C28(8, 0x27c3, 1);
        } else
            func_002B0C28(8, 0x27ba, 1);
        break;
    case 2:
        if (D_001A79F0[0] == 11)
            func_002B0C28(8, 0x2793, 1);
        else if (D_001A79F0[0] == 18) {
            if (*(int *)(state + 0x100) != 0)
                func_002B0C28(8, 0x27e7, 1);
            else
                func_002B0C28(8, 0x2793, 1);
        }
        break;
    case 3:
        if (D_001A79F0[0] == 18) {
            if (*(int *)(state + 0x100) == 0)
                func_002B0C28(8, 0x27e7, 1);
            else
                func_002B0C28(8, 0x2793, 1);
        }
        break;
    case 4:
        if (D_001A79F0[0] == 18 && *(int *)(state + 0x100) == 1)
            func_002B0C28(8, 0x27e7, 1);
        break;
    }
}
