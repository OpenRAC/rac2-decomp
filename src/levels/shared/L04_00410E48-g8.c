#include "common.h"

/* A -G8 unit (the profile from the file's name): a plain extern of at most eight bytes is then
   one assembler operand, and with its .extern only at the end of the file the assembler
   expands it to the retail's absolute lui + load through the destination register. -G0
   splits the address into a high-part register of its own. */

extern s32 D_001A79F0;

/* shared native body of family 8c88be3bc489ab9e */
/* Tells whether a racer is in the right animation window for a certain jump on level 11 and is still below a height limit. */
int func_L04_00410E48(int animId, int animFrame, float limit)
{
    int result = 0;

    if (gCurrentMapIndex != 11) goto end;

    if (animId == -1) {
        if (animFrame >= 166) {
            if (animFrame < 187) {
                if (limit < 520.2f) {
                    result = 1;
                    goto end;
                }
            }
        }
    }

    if (animId == 2) {
        if ((unsigned)(animFrame - 1) < 6) {
            if (limit < 537.0f) {
                result = 1;
                goto end;
            }
        }
        if ((unsigned)(animFrame - 35) < 13) {
            if (limit < 534.0f) {
                result = 1;
                goto end;
            }
        }
    }

end:
    return result;
}
