#include "names.h"
/* func_002ED948 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */
#include "common.h"


typedef int TI128 __attribute__((mode(TI)));

extern TI128 D_001BFFAFA0;

extern s32 coll_test_point(void *, s32, void *, float);

/* Checks if the owner can be placed at its spot; if so, copies the saved position into it and returns 1, else returns 0. */
s64 follower_try_place_at_saved_spot(s32 owner)
{
    s64 result = 0;
    s32 pos = owner + 0x10;

    if (coll_test_point(pos, 2, owner, 1.5f) != 0) {
        *(TI128 *)pos = D_001BFFAFA0;
        result = 1;
    }
    return result;
}
