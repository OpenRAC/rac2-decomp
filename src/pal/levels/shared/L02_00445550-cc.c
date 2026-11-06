/* func_PAL_L02_00445550, the PAL copy of func_L02_0043FA98: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; scale func_002F3158(func_0031E808(135.0f, 225.0f)); rename func_002F1BE0 becomes func_00282978; rename func_0031E808 becomes func_002A7878; rename func_0031E3C0 becomes func_PAL_002A7E68; rename func_002F3158 becomes func_00283CF0. */

typedef unsigned char u8;

extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_00282978(void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);

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
void func_PAL_L02_00445550(u8 *a0) {
    u8 *s0 = a0;
    u8 *s1 = *(u8 **)(s0 + 0x68);
    int m;

    if (func_00282978(s1 + 0x48) == 0)
        return;
    if (*(int *)(s1 + 0x44) != 0 || func_002A7878(0.0f, 1.0f) < 0.8f) {
        if (*(u8 *)(s0 + 0x42) != 1)
            m = 1;
        else
            m = 2;
        if (*(u8 *)(s0 + 0x43) != m)
            func_PAL_002A7E68(s0, m, 0, 0x19);
    } else {
        if (*(u8 *)(s0 + 0x43) != 0)
            func_PAL_002A7E68(s0, 0, 0, 0x19);
    }
    *(short *)(s1 + 0x48) = (((int)(func_00283CF0(func_002A7878(135.0f, 225.0f))) * 5 + 2) / 6);
}
