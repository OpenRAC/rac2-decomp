/* func_US2_L18_00304470, the USA v2.00 copy of func_L18_00303A58: the same C. */
#include "common.h"

/* Frozen Batch A A18-void-store-16; acknowledged claim 4cf4f8b91176606a7af1fd853f7ccd89fa63964199d0883686e46fb6a47255a8. */
typedef unsigned char BatchA_A18_u8;

typedef int BatchA_A18_s32;

/* Frozen Batch A A09-cond-select-36; acknowledged claim 3dadb64036892dfb357f8b3f0f7b47fc608b60613dcd8c823ef8df1bc26f7e5b. */
typedef unsigned char BatchA_A09_u8;

typedef int BatchA_A09_s32;

extern BatchA_A18_u8 D_0018C0D4;

/* func_L18_002D0C00 */
/* Partial input record: only the observed axes and button words are modeled. */
typedef struct {
    u8 reserved000[0x108];
    float horizontal, vertical;
    u8 reserved110[0x90];
    s32 held;
    u8 reserved1A4[12];
    s32 pressed;
} InputRecordPrefix;
extern InputRecordPrefix D_00138180;
/* func_L18_002D1998 */
/* Partial probe-collision record: only the hit object, hit count and surface normal are modeled. */
typedef struct { u8 prefix[0x18]; s32 object; s32 count; u8 gap[0x20]; float normal[4]; } MotionCollision;
extern MotionCollision D_L18_001BFC00;
/* func_L00_002D36E0(float *out, s32 flag, float x, float y, float z) elsewhere: this typed
   interleaving keeps both EE argument banks unchanged and gives retail's argument setup order. */
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
/* func_L18_002C4000 is defined in L18_002C4000-hero.c. */

/* func_L18_002C41F0 is defined in L18_002C4000-g8.c (this unit has $gp access for it). */

/* func_L18_002CFD68 is defined in L18_002CFD68-qcopy.c. */

/* func_L18_002CFF48 is defined in L18_002CFD68-qcopy.c. */

extern BatchA_A18_s32 ref_L18_002E4090_00(BatchA_A18_s32 a0, BatchA_A18_s32 a1);

/* func_L18_002E42F8 is defined in L18_002E42F8-flags-g8.c. */

/* func_L18_002F1098 is matched in its own unit, L18_002F1098-g8.c. */

extern void func_0027F1D8(void *a0, void *a1, const char *a2);
extern char D_L18_00296510[];

void func_US2_L18_00304470(void *a0, void *a1) {
    func_0027F1D8(a0, a1, D_L18_00296510);
}

/* func_L18_003044B8 is defined in L18_003044B8.c. */

/* func_L18_00307C60 is defined in L18_002C4000-quad.c. */

BatchA_A18_s32 func_L18_0032B768(BatchA_A18_u8 *s, BatchA_A18_s32 a1, BatchA_A18_s32 a2);

extern BatchA_A18_s32 func_002A8AF0(BatchA_A18_s32 a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2);
extern BatchA_A18_s32 D_001FE480[];

/* hands the slot's payload to its handler; the slot table entry holds count then payload */
BatchA_A18_s32 func_L18_0033B628(BatchA_A18_s32 a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2);

/* func_L18_0035D238 is defined in L18_0035D238.c. */

extern float func_L18_0035D5F8(void *a0, void *a1, void *a2, char *a3, float f12);
extern BatchA_A18_s32 D_001FE480[];

/* GCC 2.9's zero-length trailing array describes the variable point payload. */
/* Finds the best projected point on the path, breaking near ties by distance. */
f32 func_L18_0035D5F8(void *out, void *origin, void *direction, char *path, float scale);

/* func_L18_003F50D8 is matched in L18_003F50D8.c (built with -mno-split-addresses). */

/* func_L18_003F5650 is matched in L18_003F5650-g16.c (built with -G16). */

/* func_L18_003F6CA8 is matched in L18_002C4000-move.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

extern void func_L18_003F74B8(void *a0, void *a1);
/* Advances the object's step counter, refreshes the emitter and asks the particle
   system for the new position; the distance test only runs when the flag is set. */
extern float func_00283248(float a, float b);

extern BatchA_A18_s32 func_L18_003F8E40(BatchA_A18_u8 *s);

BatchA_A18_s32 func_L18_003F7358(BatchA_A18_u8 *a0, BatchA_A18_u8 *a1);

/* func_L18_003F73B8 */
extern float func_00283248(float, float);
/* The 1.5707964 spelling is load-bearing: this assembler under-rounds by an ulp
   (1.5707964f, 1.57079637f and even 1.5707963705062866f all encode 0x3FC90FDB,
   retail holds 0x3FC90FDC).  Measured by sweeping spellings, COMPILER-NOTES. */
extern BatchA_A18_s32 func_002A77E0(BatchA_A18_s32 a0);

extern BatchA_A18_s32 func_L18_003F75E8(BatchA_A18_s32 a0, BatchA_A18_u8 *a1);

/* runs the 0x1E gate and, when it clears, the record query into a local buffer;
   answers whether the query found anything */
BatchA_A18_s32 func_L18_003F7470(BatchA_A18_u8 *a0);

extern void func_L18_003F7590(BatchA_A18_u8 *a0);

void func_L18_003F74B8(void *a0, void *a1);

void func_L18_003F7590(BatchA_A18_u8 *a0);

/* The group id lists, the entity bank base and the resident group count. The two scalars are
   `sda` arrays of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui`/`lw`) as retail has it in this -G0 unit. */
extern unsigned short *D_L18_001FB320[];
extern char *D_L18_001B281C[] __attribute__((sda));
extern int D_L18_001B2838[] __attribute__((sda));

/* Counts the entities of kind 0xB69 in state 1 that the group's id list names, stores the count
   through a1 and returns the last of them (0 when there is none). Retail compares the state with
   0xFE and 0xFD before testing it for 1. */
BatchA_A18_s32 func_L18_003F75E8(BatchA_A18_s32 a0, BatchA_A18_u8 *a1);

/* func_L18_003F76F0 lives in L18_003F76F0-copy.c. */

extern void func_00282F20(void *a0, void *a1, float f12);
extern void func_00282CC0(void *a0, void *a1, void *a2);

/* the object's state flags and aim angle are set, then the target is handed
   over to the object's controller */
/* func_L18_003F7988 lives in L18_003F7988-copy.c. */

void func_L18_003F7A08(BatchA_A18_u8 *a0);

extern void func_L18_003F7A08(BatchA_A18_u8 *a0);
/* func_L18_003F7AB8 is defined in L18_002C4000-g8.c (this unit has $gp access for it). */

extern void func_00282F20(void *a0, void *a1, float f12);
extern void func_00282CC0(void *a0, void *a1, void *a2);
/* Moves the object's state word, refreshes the two transform matrices through the
   shared helpers and writes the measured distance back into the object. */
/* A18-void-store-16 freshly exact-verified under family reservation */
/* A18-cond-select twin of 003F8E80: two independent state gates */
BatchA_A18_s32 func_L18_003F8E40(BatchA_A18_u8 *s);

/* A09-cond-select-36 freshly exact-verified under family reservation */
BatchA_A09_s32 func_L18_003F8E80(BatchA_A09_u8 *s);

/* func_L18_003F8EA8 is defined in L18_003F8EA8-qcopy.c. */

/* func_L18_003F9DA0 is defined in L18_002C4000-switch-g8.c. */

/* Slot i of the object's eight group ids (the words at +0x60). Retail rebuilds the slot address
   at every test of the walk, which is what an inline helper expanded in place does. */

/* Walks the id list of each of the object's eight groups and, for every entity in it, calls the
   handler of its kind (0xD5C, 0x11CC, 0xD9B, 0x11CF or 0xB69), clears the entity's word at +0x98
   and sets bits 0 and 1 of its flags at +0x34; then stores -1 at +0x88 of the object. */
/* Slot i of the state block's eight group ids (the words at +0x60). */
#define L18_GROUP_ID(i) (*(int *)(state + 0x60 + (i) * 4))

/* The engine's walk over a group's terminated stream of 15-bit actor indices, written as in
   the other matched walks (FOR_EACH_ID in L06_0033BDC0-g8.c). Its repeated `entry != 0` adds a
   label to the exit test that jump.c cannot thread before cse, so the rolled test is not copied
   in front of the loop; the PRE copies then land behind NOTE_INSN_LOOP_BEG, last in the init. */
#define L18_FOR_EACH_ID(entry, i) \
    for (entry = D_L18_001FB320[L18_GROUP_ID(i)]; \
         (L18_GROUP_ID(i) & 0xFF) != 0xFF && L18_GROUP_ID(i) <= D_L18_001B2838[0] && entry != 0 && \
         ((entry != 0 && (short)entry[-1] >= 0) || entry == D_L18_001FB320[L18_GROUP_ID(i)]); \
         entry++)

/* Disables every actor of group i: clears flag bits 0, 1 and 6 and sets bit 12 at +0x34,
   copies the word at +0x10 of the actor's +0x24 block to +0x98 and, unless the owner is of
   kind 0xB69, also clears the byte at +0x31 and sets bit 0 again. */
#define L18_DISABLE_GROUP(i) \
    L18_FOR_EACH_ID(entry, i) { \
        member = D_L18_001B281C[0] + (*entry & 0x7fff) * 0x100; \
        if (member == 0) \
            break; \
        flags = *(unsigned short *)(member + 0x34) & 0xffbc; \
        *(unsigned short *)(member + 0x34) = flags | 0x1000; \
        *(int *)(member + 0x98) = *(int *)(*(char **)(member + 0x24) + 0x10); \
        if (*(short *)(owner + 0xaa) != 0xb69) { \
            member[0x31] = 0; \
            *(unsigned short *)(member + 0x34) = flags | 0x1001; \
        } \
    }

/* Disables the actor groups that belong to mode 0-4 of the owner's state block. */
#undef L18_DISABLE_GROUP
#undef L18_FOR_EACH_ID
#undef L18_GROUP_ID

/* The bank base and group count again, read-only here: this walk calls nothing, and retail loads
   both once before the walk of each group (the count also once for the whole function) instead of
   rereading them after the stores, as const data lets loop.c hoist them. */
/* Walks the id list of each of the object's eight groups like func_L18_003F9FB0 and, for every
   entity in it, clears its word at +0x98 and sets bits 0, 1 and 6 of its flags at +0x34 while
   clearing bit 12. */
BatchA_A18_s32 func_L18_003FA8E0(BatchA_A18_u8 *s);

/* Each scan reads the current slot id again when advancing its group iterator. */

/* Selects the source, secondary member and target from the owner's three group
   lists. The first target scan prefers entries passing the flag and distance tests. */
/* func_L18_003FAE50 lives in L18_003FAE50-beam.c. */

/* func_L18_003FB500 lives in L18_003FB500.c. */

/* func_L18_003FB5E8 is matched in its own unit, src/levels/shared/L18_003FB5E8-qcopy.c (-frac2-qcopy). */

/* func_L18_003FC9B8 lives in L18_003F7988-copy.c. */

/* func_L18_003FCA38 is defined in L18_003FCA38-g8.c. */

/* func_L18_003FCC48 lives in L18_003FCC48-particles.c. */

/* func_L18_003FCD70 lives in L18_003FCD70-particles.c. */

/* store -1 into field 0x74 of the object at s[0x68] */
/* func_L18_00426E48 lives in L18_00426E48-g8.c. */

extern void func_00282948(void *a0);

/* the object's scale angles are re-submitted in degrees, then the matrix is rebuilt */
extern void func_00282948(void *a0);

extern BatchA_A18_s32 func_L09_0033E690(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, float f12);
extern BatchA_A18_s32 func_L09_00329178(BatchA_A18_u8 *a0, BatchA_A18_s32 a1,
                                        BatchA_A18_s32 a2, BatchA_A18_s32 a3);

/* re-seats the object on a new animation; -1 means "leave it to the level" */
BatchA_A18_s32 func_L18_00427130(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2);

extern BatchA_A18_s32 func_L09_0033E658(void *a0);

BatchA_A18_s32 func_L18_004271C0(BatchA_A18_u8 *a0);

/* func_L18_00427208 is defined in L18_00427208-qcopy.c. */

/* func_L18_004273F0 is matched in L18_004273F0-g8.c (built with -frac2-qcopy). */

/* func_L18_00427688 lives in L18_00427688-g32.c. */

/* func_L18_00427B48: 144 bytes against retail's 148; the chain pointer and the
   stored 1 take each other's register. Deposited in nonmatching/levels/. */
