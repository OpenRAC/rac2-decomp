#include "names.h"
/* func_US2_L00_0042EF90, the USA v2.00 copy of func_L00_0042D9D0: the same C. */

/* Clears the pending pointer the level keeps at +0x1FC0. */
void level_clear_pending_pointer_us2(void *level) {
    int *pending = *(int **)((char *)level + 0x1fe0);
    *pending = 0;
}
