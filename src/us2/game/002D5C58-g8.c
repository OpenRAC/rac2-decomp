#include "common.h"

/* func_US2_002D5C58, the v2.00 copy of func_002D5048. */
typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
typedef struct { char reserved00[0x1C4]; int flags; } MenuGameState;
extern MenuGameState D_00138180;
extern CallbackState D_001F2840;
extern unsigned char D_001A7BB4;
extern int D_0025E0B0 __attribute__((nosda));
extern int D_US2_001ABAF0[2] __attribute__((sda));
int func_US2_002D5C58(int selection)
{
    CallbackState *state = &D_001F2840;
    D_0025E0B0 = D_US2_001ABAF0[D_001A7BB4];
    if (*(int *)(state->source + 0xE8) != selection)
        return 0;
    if ((D_00138180.flags & 0x900) && state->fallback == 0)
        return 1;
    if (D_00138180.flags & 0x10) {
        CallbackState *update = &D_001F2840;
        int value = *(int *)(update->source + 0xE0);
        int result;
        if (value != 0)
            update->value = value;
        else if (update->fallback == 0) {
            result = -1;
            goto return_value;
        }
        result = 0;
return_value:
        return result;
    }
    return 0;
}
