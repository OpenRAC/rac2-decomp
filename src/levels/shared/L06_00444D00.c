#include "common.h"

typedef int s128 __attribute__((mode(TI)));

extern const char ref_L06_00444D00_00[];
extern const char ref_L06_00444D00_01[];
extern s32 ref_L06_00444D00_02(void *, s32);
extern void ref_L06_00444D00_03(void *, void *, s32, s32);
extern void ref_L06_00444D00_04(s32, void *, s32);

/* Updates a switch moby (class 3546): works out if it is on, and when that changes it tells the linked objects. */
void switch_l06_update(char *object)
{
    char *state;
    s128 test_point;
    s32 is_on = 0;
    s32 i;
    s32 j;
    s32 k;
    s32 *second_list;
    s32 mode;

    state = *(char **)(object + 0x68);
    *(u8 *)(object + 0x30) = 0xFF;
    if (state[0x7E])
        qcopy(&test_point, ref_L06_00444D00_00);
    else
        qcopy(&test_point, ref_L06_00444D00_01);
    mode = *(u8 *)(object + 0x95);
    if (mode == 0) {
        for (i = 0; ; i++) {
            if (i >= 4) goto done;
            if (((s32 *)state)[i] == -1) continue;
            if (ref_L06_00444D00_02(&test_point, ((s32 *)state)[i])) break;
        }
        goto set;
    } else if (mode == 1) {
set:
        is_on = 1;
    } else {
        is_on = 0;
    }
done:
    if ((is_on && !*(u8 *)(object + 0xBC)) ||
        (!is_on && *(u8 *)(object + 0xBC)) ||
        !*(u8 *)(object + 0x20)) {
        if (is_on) *(u8 *)(object + 0xBC) = 1;
        else *(u8 *)(object + 0xBC) = 0;
        *(u8 *)(object + 0x20) = *(u8 *)(object + 0xBC) + 1;
        second_list = (s32 *)(state + 0x44);
        for (j = 0; j < 13; j++) {
            if (((s32 *)(state + 0x10))[j] != -1)
                ref_L06_00444D00_03(object, state, ((s32 *)(state + 0x10))[j], is_on);
        }
        for (k = 0; k < 14; k++) {
            if (second_list[k] != -1)
                ref_L06_00444D00_04(second_list[k], state, is_on);
        }
    }
}
