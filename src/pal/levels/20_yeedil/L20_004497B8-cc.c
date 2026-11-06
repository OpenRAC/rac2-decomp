/* func_PAL_L20_004497B8, the PAL copy of func_L20_00443D58: the same C, where rename func_L20_00443B60 becomes func_PAL_L20_004495C0; rename func_L20_00449FD0 becomes func_PAL_L20_0044FC48; scale func_002A7820(0x12C, 0x258). */
#include "common.h"

/* func_L20_0043F318 defined in L20_0043F318-g8.c. */

/* func_L20_0043F460 is defined in L20_0043ECB0-g8.c (it reaches a global through $gp). */

/* func_L20_0043F570 is defined in L20_0043F570-g8.c. */

/* func_L20_0043FC70 is defined in L20_0043F570-g8.c (it reaches data through $gp). */

/* func_L20_0043FFF0 is defined in L20_0043F570-g8.c (it reaches globals through $gp). */

/* func_L20_00440198 is defined in L20_00440198.c (its slot-table and func_002A7750 declarations conflict with this unit's). */

extern unsigned int D_L20_001B2F9C __attribute__((sda));

/* Counts the objects of a group whose state byte (object + 0x20) is neither 6 nor negative.
   D_L20_001FBB20 holds a list of 16-bit object ids per group; the low 15 bits of an id index
   the 0x100-byte object records at D_L20_001B2F9C, and the last id of a list has its top bit
   set. The guards on the group and its list come before the walk and again after each record,
   as in func_L20_0039E0A0. The bound D_L20_001B2FB8 does not change in the loop, so cc1 hoists
   its repeated test into a register known to be zero, which the loop still tests (retail's
   `daddu $t0,$zero,$zero` and `bnez $t0`). */
extern void func_002A8C28(char *, char *, int, int, float, float, float, int,
                          int);
/* func_L20_00440598 is defined in L20_00440598-g8.c (it reaches data through $gp and needs -frac2-hazard-labels). */

/* func_L20_00441CB8 is defined in L20_00441CB8-g8.c. */

/* func_L20_004421A8 is defined in L20_004421A8-g8.c. */

/* func_L20_004424A0 is defined in L20_004424A0-helpers-g8.c. */
/* func_L20_004424A0 reads four constants through $gp: its near miss is in
   nonmatching/levels/func_L20_004424A0.c and belongs in the -G8 sibling. */

/* func_L20_00442550 is defined in L20_00442550-g8.c. */

extern void func_002A8C28(char *, char *, int, int, float, float, float, int,
                          int);

/* func_L20_004429F0 is defined in L20_004429F0-g8.c. */

extern int func_002A7820(int, int);

/* func_L20_00442CD8 is defined in L20_00442CD8-g8.c. */

/* func_L20_00442E68 is defined in L20_00442E68-g8.c (it reaches data through $gp). */

/* func_L20_00442F80 is defined in L20_00442F80-g8.c. */

/* func_L20_004431E0 is defined in L20_004431E0-g8.c (it reads D_L20_001B2FB8 through $gp and needs -frac2-keep-block-order). */
/* func_L20_004431E0 reads a global through $gp: its near miss is in
   nonmatching/levels/func_L20_004431E0.c and belongs in the -G8 sibling. */

extern unsigned int D_L20_001B2F9C __attribute__((sda));
/* func_L20_004499E8 is defined in L20_004499E8-g8.c. */
/* func_L20_004433B0 is defined in L20_004433B0-g8.c (it reaches a global through $gp). */

/* func_L20_004435A0 is in L20_004435A0-g8.c. */

/* func_L20_00443790 is defined in L20_00443790-helpers-g8.c. */

typedef int TI128 __attribute__((mode(TI)));
/* func_L20_00443A10 lives in L20_00443A10-g8.c. */

/* func_PAL_L20_004495C0 is defined in L20_00443B60-helpers.c. */

extern void func_PAL_L20_004495C0(char *, char *, char *, float *);
extern char *func_PAL_L20_0044FC48(char *, char *, char *, float, int, float);

char *func_PAL_L20_004497B8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    TI128 a;
    TI128 b;
    float f;
    float g;
    int r;

    f = 1.0471977f;
    func_PAL_L20_004495C0(arg0, (char *)&a, (char *)&b, &f);
    g = f;
    r = (((int)(func_002A7820(0x12C, 0x258)) * 5 + 2) / 6);
    return func_PAL_L20_0044FC48(arg0, (char *)&a, (char *)&b, g, r, (float)*(unsigned char *)(state + 0x36));
}

/* func_L20_00443DF0 is defined in L20_00443DF0.c (it needs -frac2-hazard-labels). */

/* func_L20_00444018 is defined in L20_00444088-g8.c (it needs this unit's -fno-schedule-insns). */

/* func_L20_00444088 is defined in L20_00444088-g8.c (it reaches a global through
   $gp and needs its own -fno-schedule-insns). */

/* func_L20_00444138 is defined in L20_00444138-g8.c (it reads a global through $gp and
   needs its own -mno-split-addresses). */

/* func_L20_004448A8 is defined in L20_004448A8-g8.c (it needs the -G8 profile with split addresses). */

/* func_L20_00444B48 is defined in L20_00444B48-g8.c. */

/* func_L20_00444CA8 is defined in L20_00444CA8.c. */

/* func_L20_004450D8 is defined in L20_004450D8-g8.c (it reads a global through $gp). */

/* func_L20_004451C0 is defined in L20_004451C0-g16.c (it reaches two 16-byte vectors through $gp). */

/* The level's own jump table (the label of the data blob at 0x002B5960). */
extern int func_002B3868(char *);

extern int func_002B38B8(char *);

extern void func_002AA548(char *, char *, float, float, float, float);

extern int func_002E5CF8(int, int, char *);

extern unsigned char D_0019B2E8[];
/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
/* func_L20_00445890 is defined in L20_00445890-g8.c. */

/* The level's own jump table (the label of the data blob at 0x002B5980). */
extern int func_002B3868(char *);

extern int func_002B38B8(char *);

extern void func_002AA548(char *, char *, float, float, float, float);

extern unsigned char D_0019B2E8[];

/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
extern int func_002E5CF8(int, int, char *);
typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } SoundSlot;
extern SoundSlot D_00188660[];
/* func_L20_00447640 is defined in L20_00447640-g8.c (it reads D_L20_001B2FB8 through $gp). */

/* func_L20_00447748 is defined in L20_00447748-g8.c. */

/* func_L20_00447930 is defined in L20_00447930-g8.c (it reaches data through $gp). */

/* func_L20_00448A18 is defined in L20_00448A18-helpers-g8.c. */
/* func_L20_00448A18 reaches four globals through $gp: its near miss is in
   nonmatching/levels/func_L20_00448A18.c and belongs in the -G8 sibling. */
