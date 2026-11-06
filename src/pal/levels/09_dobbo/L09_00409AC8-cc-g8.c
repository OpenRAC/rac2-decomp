/* func_PAL_L09_00409AC8, the PAL copy of func_L09_00404BF0: the same C, where rename-macro func_002A7470 becomes func_PAL_002A7E68; scale a1; rename func_L08_00316678 becomes func_PAL_002A7E68; rename D_L09_001B13F4 becomes D_PAL_001B1420. */
#include "common.h"

extern f32 D_PAL_001B1420 __attribute__((sda));
extern void func_PAL_002A7E68(char *a, s32 b, s32 c, s32 d);

typedef union {
    u16 h;
    s32 w;
} U16S32;

extern U16S32 D_L09_001B13C0 __attribute__((sda));
void func_PAL_L09_00409AC8(char *a0, s32 a1) {
    char *v = a0;
    f32 f = D_PAL_001B1420 * 0.020000001f;
    char *p = *(char **)(v + 0x68);
    *(f32 *)(p + 0x1D4) = 3.0f;
    *(f32 *)(p + 0x1D0) = f;
    if (*(u8 *)(v + 0x43) == 7) {
        return;
    }
    func_PAL_002A7E68(a0, 7, 0, (((int)(a1) * 5 + 2) / 6));
}

/* Small-data handles: the resident mode word (-0x7600 -> 0x001A79F0), the resident
   release word (-0x5FB0 -> 0x001A9040) and the level's record table (0x386C ->
   0x001B285C), all read with $gp pinned at 0x001AEFF0. */
/* Drops the record the sub-object points at, once, when the resident mode word says 9,
   then rebuilds the sub-object's effect with both blend weights at zero. */
/* The same resident mode word, read here as an ordinary global (lui + lw) rather than
   through $gp: the two references name the same word, one small and one not. */
/* Releases the record the sub-object holds once the resident mode word says 9, then
   rebuilds the sub-object's effect. */
/* The same release as func_L09_00404E58, with this level's own calls: when the
   resident mode word says 9 the record the sub-object holds is released, then the
   record's update runs with the value func_002B0ED8 returned, and the sub-object's
   effect is rebuilt from the sub-object's own index and position. */
/* The walks below read the group table of id lists absolute. The group count and the entity base
   are plain externs here, which come out as bare `lui`/`lw` pairs in ordinary flow and as $gp
   loads in a branch delay slot; the base takes a second name because D_L09_001B285C above is the
   $gp form. */
/* The vector the scaled copy starts from: small data, so its address is a $gp offset. */
/* The colour pair func_00283D38 blends. */
typedef struct {
    s32 a, b;
} ColorPair;

/* The object's blended colour word: a member store, which the scheduler knows cannot alias the
   scalar global D_L09_001B2388 (a plain cast store it must keep in front of that load). */
extern ColorPair D_L09_001B1400[2];

void func_L09_00405490(u8 *a0);

/* Steps the object's pulse: the angle at +0x348 advances by 2*pi/30 through the resident angle
   blend, its sine is mapped to 0..1 and kept at +0x34C, and the colour pair D_L09_001B1400 is
   blended by it into the object's word at +0x78. When the state's stamp (+0x350) differs from
   D_L09_001B2388, every visible class-0xD90 entity of the object's group that is not in state
   0xFE or 0xFD gets its point refreshed (func_0029FC20, selector 0) into its vector at +0x240
   and the same stamp; then func_L09_00405490 is registered as the object's callback. */
/* Callback of func_L09_004052F8 for every class-0xD90 entity of the object's group that is not
   hidden (byte 0x31) or in state 0xFE or 0xFD: scales the sub-object's vector by its float at
   +0x344, transforms it by the matrix at +0x240, blends the colour pair by the float at +0x34C
   and hands the result to func_L00_00325AE8 with the +0x344 float scaled by 0.2. */
void func_L09_00405490(u8 *a0);

typedef struct { u8 pad[0x464]; u8 spent[1]; } L09_CellFlags;
extern L09_CellFlags D_L09_0021E9F0;
