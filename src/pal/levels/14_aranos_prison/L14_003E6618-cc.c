/* func_PAL_L14_003E6618, the PAL copy of func_L14_003E22A8: the same C, where scale *(int *)(v + 0x78); scale *(int *)(v + 0x70). */
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern Collision D_L14_001BF940;
extern Material D_L14_002686F0[];
extern float func_002A7878(float, float);
extern void func_00282CC0(void *dst, void *a, void *b);
/* func_L14_00304190 is defined in L14_00304190-zp.c (it clears a stack vector with por, which needs -frac2-zero-ti-por). */

/* func_L14_00304280 lives in the -g8 sibling file (it reaches a global through $gp). */

typedef struct {
    unsigned char pad00[0x34];
    unsigned short flags;
    unsigned char pad36[0x68 - 0x36];
    unsigned int p68;
    unsigned char pad6C[0xAA - 0x6C];
    short type;
} Mob_L14_00304588;

typedef struct {
    unsigned char pad00[0x30];
    int mode;
    unsigned char pad34[0x44 - 0x34];
    short count;
    unsigned char pad46[0x18C - 0x46];
    Mob_L14_00304588 *mobs[1];
} MobList_L14_00304588;

extern MobList_L14_00304588 ref_L14_00304588_00;
/* Walks the level's list of mobs like func_L02_00300CE8; when the game state is 0xE and the
   list's word at +0x30 is zero it then runs two more calls, the second with the list's word at +0x194. */
/* func_L14_00328E70 is matched in its own unit, src/levels/14_aranos_prison/L14_00328E70-qcopy.c (-frac2-qcopy). */

/* func_L14_0035F510 is defined in L14_0035F510-g8.c (it reads its list through $gp). */

/* func_L14_00390DF8 is defined in L14_00390DF8-helpers.c. */

/* func_L14_00390EC0 is defined in L14_00304190-zp.c (it clears a stack vector with por, which needs -frac2-zero-ti-por). */

/* func_L14_003CB258 is defined in L14_003CB258-g8.c (it reads its tuning through $gp). */

/* func_L14_003CB4D8 is defined in L14_003CB4D8-g8.c. */

extern void func_00283698(void *dst, void *src);

extern void func_00282CF0(void *dst, void *a, void *b);

extern void func_002AFDD8(void *a, void *b, void *c, void *d);

extern float func_00282C48(float a);

extern void func_00283098(void *dst, void *a, void *mtx);

extern void func_00282CC0(void *dst, void *a, void *b);

extern void func_L14_003C9658(char *e, void *v);

extern unsigned short *D_L14_001FB060[];

extern unsigned char *D_L14_001B259C __attribute__((sda));

extern int D_L14_001B25B8 __attribute__((sda));

/* The twin of func_L14_003DF200 for the group word at +0x64: the same pass over the entities
   of the owner's group (not the states 0xFE and 0xFD, not the class 0xA59, accepted by
   func_L14_003C9548), with the box centred at -2.0 on the first axis: beyond 0.8 of it the
   offset is pulled back to -1.5 or -2.5, beyond 0.8 on the second axis to +-0.5, and the entity
   is handed the corrected world position (func_L14_003C9658). */
/* func_L14_003CB868 is defined in L14_003CB868.c. */

/* func_L14_003D18C8 is defined in L14_003D18C8.c. */

/* func_L14_003DDD38 is defined in L14_00304190-g8.c (it reaches D_L14_001B259C through $gp). */

/* The object is placed in the world: the group's two matrices are copied and turned by the
   angle, the object's own matrix is rebuilt from them, and the three floats it keeps are
   cleared. The first call takes the object's own matrix as its second argument, but the
   compiler overwrites it with the local buffer before the call, so the callee sees the
   buffer (as retail does). */
typedef struct {
    char pad0000[0x80];
    Vec position;               /* 0x80 */
    char pad0090[0x22B4 - 0x90];
    unsigned char mode;         /* 0x22B4 */
} PrisonLiftHero;
extern PrisonLiftHero D_00189E20;
extern char D_00188660[];
extern int func_002B3868(char *self);
/* A lift that travels between its start height (0x68) and its target (0x64): state 0 sets it
   up, state 1 waits for the hero (or a trigger) and starts it with its travel sound, states 2
   and 3 ease it up and down and stop the sound on arrival. Riders follow its movement. */
/* func_L14_003DE9B0 is in its -g8 unit. */

/* func_L14_003DECE0 is defined in L14_003DECE0.c. */

/* func_L14_003DF100 lives in the -g8 sibling file (its calls pass floats, so it needs real prototypes). */

extern float func_00282C48(float a);

extern void func_00283698(void *dst, void *src);

extern void func_00282CF0(void *dst, void *a, void *b);

extern void func_002AFDD8(void *a, void *b, void *c, void *d);

extern void func_00283098(void *dst, void *a, void *mtx);

extern void func_00282CC0(void *dst, void *a, void *b);

extern void func_L14_003C9658(char *e, void *v);

extern unsigned short *D_L14_001FB060[];

extern unsigned char *D_L14_001B259C __attribute__((sda));

extern int D_L14_001B25B8 __attribute__((sda));

/* For every entity of the owner's group (state word 0x68), other than the two states 0xFE and
   0xFD, that func_L14_003C9548 accepts: takes its offset from the owner in the owner's frame;
   when that is beyond 1.0 on the first axis or 1.5 on the second it is pulled back to +-0.5 or
   +-1.25, and the entity is handed the corrected world position (func_L14_003C9658). */
/* func_L14_003DF440 lives in the -g8 sibling file (it reads a count through $gp). */

/* func_L14_003DF540 lives in the -g8 sibling file (it reads a count through $gp). */

/* func_L14_003DF6A0 is defined in L14_003DF6A0-g8.c. */

/* func_L14_003DF7F8 is defined in L14_00304190-g8.c (this unit has no $gp access for it). */

/* func_L14_003E1E78 is in its -g8 unit. */

float func_PAL_L14_003E6618(char *arg0) {
    char *v = *(char **)(arg0 + 0x68);
    unsigned int s = *(unsigned char *)(arg0 + 0x20);

    if (s == 4) {
        return (float)*(int *)(v + 0x7C) / (float)(((int)(*(int *)(v + 0x78)) * 5 + 2) / 6);
    }
    if (s == 2) {
        return 1.0f - (float)*(int *)(v + 0x7C) / (float)(((int)(*(int *)(v + 0x70)) * 5 + 2) / 6);
    }
    if (s == 1) {
        return 0.0f;
    }
    return 1.0f;
}

/* func_L14_003E2328 is defined in L14_003E2328-g8.c. */

/* func_L14_003E2688 is defined in L14_00304190-g8.c. */

/* func_L14_003E2980 is defined in L14_00304190-g8.c (it reads its tuning through $gp). */

/* func_L14_003E4208 is defined in L14_003E4208-g.c (it needs -g for retail's line-note nops). */

extern char D_00188660[];
/* The object steers a group of entities: by its state byte it either leaves the group
   (state 0), asks whether the group is free and hands itself over if it is (state 1) or
   turns (state 2).  In the turning state it takes an entry from the ring of the group's own
   entries (D_00188660, 0x70 bytes each) - a new one when the entry it holds is not its
   own or is free - and turns half a degree; at the end it releases the entry it holds
   when the entry is its own and in use, and forgets it either way. */
extern int func_002B3868(char *self);
extern void func_L14_003E50B8(char *self);
extern void func_L14_003E5190(char *self);
extern void func_L14_003E51B0(char *self);
extern void func_L14_003E5218(char *self);

/* The key state of an object that steers a group (+0x14 the current key, +0x16 the key index,
   +0x34 the key word). The last walk stores through this struct: cc1 then knows the store does
   not touch the two level globals (a store through a cast pointer might), so loop.c moves their
   loads and the constants out of the loop. That walk is spelled like the other two, with the
   second `p != 0`: its test is too long for the first jump pass to copy in front of the loop,
   and after loop.c has hoisted the invariants it is short enough for the second pass, which
   copies it (retail's entry test ahead of the loop, the hoisted values before it). A cast store
   instead leaves nothing to hoist and the walk stays in the `b test` form. */
/* Steps the object by its state byte: 0 copies the six halfwords at +0x40 of its state into the
   state of every class-0xB19 entity of its group and calls func_L14_003E5030; 1 and 2 test
   func_002B3868 and call their handlers (the cases are in retail's block order, 0, 2, 1). Then,
   while the key word (+0x34) is set: when func_00282978 has run down the key counter (+0x14)
   the current key is reloaded from the key word and the key index of every class-0xB19 entity
   of the group is cleared; finally the current key is copied into each of them. Two pointers:
   the third walk has its own (one shared variable gives the other loops different registers). */
/* func_L14_003E4EA0 is matched in L14_003E4EA0-g8.c (built with -g). */

/* func_L14_003E5030 lives in the -g8 sibling file (it reaches a global through $gp). */

void func_L14_003E50B8(char *object);

void func_L14_003E5190(char *arg0);

void func_L14_003E51B0(char *arg0);

void func_L14_003E5218(char *self);

extern float func_002A7878(float, float);
/* Resets the record: the four axis pairs, the flags and the packed word. */
/* func_L14_003F0F38 lives in the -g8 sibling file (it reaches a global through $gp). */
