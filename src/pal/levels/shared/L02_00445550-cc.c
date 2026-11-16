#include "names.h"
/* func_PAL_L02_00445550, the PAL copy of func_L02_0043FA98: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; scale func_002F3158(func_0031E808(135.0f, 225.0f)); rename func_002F1BE0 becomes func_00282978; rename func_0031E808 becomes func_002A7878; rename func_0031E3C0 becomes func_PAL_002A7E68; rename func_002F3158 becomes func_00283CF0. */

typedef unsigned char u8;

extern void anim_start_blended_pal(void *, int, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern int FastDecTimer(void *);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);

/* func_L02_00410450 is defined in L02_00410450-controller-g8.c. */

/* func_L02_00410D00 is defined in L02_00410D00-g8.c. */

/* func_L02_00410E58 is defined in L02_00410E58.c. */

/* func_L02_00410F68 is defined in L02_00410F68-g8.c. */

/* Plays one of nine resident messages, chosen by the sub-object's state word. */
/* func_L02_004114A0 is defined in L02_004114A0.c. */

/* func_L02_00411530 is matched in L02_00411530.c (built with -frac2-hazard-labels). */

/* True while the record's state byte still says 2. */
/* Copies the sub-object's byte 0x40 down to its byte 0x25. */
/* Advance the captured child's rising and settling states. */
/* func_L02_00416720 is defined in L02_00410450-qcopy.c. */

/* True when the record is in state 1 and its sub-object holds a cleared origin. */
/* func_L02_00421860 is defined in L02_00421860-g8.c. */

/* func_L02_00422270 is defined in L02_00422270-g8.c. */

/* Rebuilds the sub-object's frame from the record's own transform. */
/* func_L02_00422538 is defined in L02_00410450-g8.c (this unit has no $gp access for it). */

/* One setup pass, then the five body passes of the resident effect. */
/* func_L02_00422720 is defined in L02_00422720-g8.c. */

/* func_L02_00422BB8 is defined in L02_00422BB8-g8.c. */

/* func_L02_00422D68 is defined in L02_00422D68-g8.c. */

/* Restarts the record's resident effect once it has settled, picking the
   variant by the resident query and the record's own byte 0x43. */
/* func_L02_0042EDD0 is matched in L02_0042EDD0-g8.c (built with -frac2-no-annulled-wide-stores -frac2-zero-ti-barrier). */

/* Picks the evasive state the object should take while the resident timer runs. */
void moby_pick_evasive_anim_state_pal(u8 *moby) {
    u8 *self = moby;
    u8 *effect = *(u8 **)(self + 0x68);
    int state;

    if (FastDecTimer(effect + 0x48) == 0)
        return;
    if (*(int *)(effect + 0x44) != 0 || math_random_float_range(0.0f, 1.0f) < 0.8f) {
        if (*(u8 *)(self + 0x42) != 1)
            state = 1;
        else
            state = 2;
        if (*(u8 *)(self + 0x43) != state)
            anim_start_blended_pal(self, state, 0, 0x19);
    } else {
        if (*(u8 *)(self + 0x43) != 0)
            anim_start_blended_pal(self, 0, 0, 0x19);
    }
    *(short *)(effect + 0x48) = (((int)(FloatToInt(math_random_float_range(135.0f, 225.0f))) * 5 + 2) / 6);
}
