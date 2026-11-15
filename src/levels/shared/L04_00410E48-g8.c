#include "common.h"

/* A -G8 unit (the profile from the file's name): a plain extern of at most eight bytes is then
   one assembler operand, and with its .extern only at the end of the file the assembler
   expands it to the retail's absolute lui + load through the destination register. -G0
   splits the address into a high-part register of its own. */

extern s32 g_current_map_index;

/* shared native body of family 8c88be3bc489ab9e */
/* Tells whether a racer is in the right animation window for a certain jump on level 11 and is still below a height limit. */
int racer_is_in_jump_window(int anim_id, int anim_frame, float limit)
{
    int result = 0;

    if (g_current_map_index != 11) goto end;

    if (anim_id == -1) {
        if (anim_frame >= 166) {
            if (anim_frame < 187) {
                if (limit < 520.2f) {
                    result = 1;
                    goto end;
                }
            }
        }
    }

    if (anim_id == 2) {
        if ((unsigned)(anim_frame - 1) < 6) {
            if (limit < 537.0f) {
                result = 1;
                goto end;
            }
        }
        if ((unsigned)(anim_frame - 35) < 13) {
            if (limit < 534.0f) {
                result = 1;
                goto end;
            }
        }
    }

end:
    return result;
}
