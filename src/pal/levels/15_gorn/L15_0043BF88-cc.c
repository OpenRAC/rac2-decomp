/* func_PAL_L15_0043BF88, the PAL copy of func_L15_00436298: the same C, where scale func_002A7820(0x14, 0x3C). */
#include "common.h"

/* Measured prefixes with integer/float views of the same game records. */
extern float func_00283198(float);
extern void func_L15_00436BA8(char *);
/* ---- shared declarations ---- */

extern int func_002ED688(unsigned char *owner);
/* Sets the level's four effect blocks up: the screen context first, then, when
   the level's own record says the object is idle, the four blocks of the
   effect data, each with its own size and colour. */
/* func_L15_00432A60 is in L15_00432A60-ribbon.c. */

extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern void func_L15_004353E8(char *);
extern void func_L15_00434D28(void *);
extern int func_002A77E0(int);
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);
extern s32 D_L15_001B1780[] SDATA(D_L15_001B1780);
extern s32 D_L15_001B17B0[] SDATA(D_L15_001B17B0);
extern s32 func_002E5CF8(s32 a, s32 b, void *c);
extern s32 func_002A77E0(s32 a);
extern f32 func_002A7878(f32 a, f32 b);
extern void func_0029FCC0(void *obj, s32 a, void *out);
extern s32 func_00283CF0(f32 a);
/* The particle helper has a different catalogue body in PAL. */
void func_L15_00434D28(void *object);

typedef struct GornEffectCamera {
    char pad00[0x140];
    float position[4];
} GornEffectCamera;
extern GornEffectCamera D_L15_001B9680;
extern void func_0029FCC0(void *, int, void *);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);

void func_L15_004353E8(char *object);

/* func_L15_00435E80 is in L15_00435E80.c. */

/* func_L15_004360D8 is in L15_004360D8.c. */

extern int func_002E5CF8(int, int, void *);
extern void func_L05_00379FA0(void *, int, int, float, int, float, float, float,
                              int, int, int);

/* The mover's own state decides whether the shot happens: the level's record
   must exist and be ready, and the mover's own counter must be idle.  The two
   shots take the slots after the counter, and the counter wraps at three. */
void func_PAL_L15_0043BF88(char *a0) {
    char *s1 = a0;
    char *s0;
    char *v0;
    int v1;

    s0 = *(char **)(s1 + 0x68);
    v0 = (char *)func_002ED688(a0);
    if (v0 == 0) {
        return;
    }
    if (*(int *)(v0 + 0x120) == 0) {
        return;
    }
    if (*(int *)(s0 + 0x450) != 0) {
        return;
    }
    func_002E5CF8(2, 0, s1);
    func_L05_00379FA0(s1, 0x600000CF, 1, 1.0f, 0, 2.0f, 1.5f, 1.5f, 0x1E,
                     *(int *)(s0 + 0x454) * 2 + 4, 0);
    func_L05_00379FA0(s1, 0x600000CF, 1, 1.0f, 0, 2.0f, 1.5f, 1.5f, 0x1E,
                     *(int *)(s0 + 0x454) * 2 + 5, 0);
    *(int *)(s0 + 0x450) = (((int)(func_002A7820(0x14, 0x3C)) * 5 + 2) / 6);
    v1 = *(int *)(s0 + 0x454) + 1;
    *(int *)(s0 + 0x454) = v1;
    if (v1 >= 3) {
        *(int *)(s0 + 0x454) = 0;
    }
}

/* func_L15_004363C8 is in L15_004363C8-g8.c. */

/* Advance through the path points, pausing when an odd encoded action supplies
   a duration in seconds. The path has a 16-byte header and 16-byte points. */
void func_L15_00436BA8(char *a0);

/* func_L15_00438260 is in L15_00438260-g8.c. */

/* func_L15_00438518 is in L15_00438518-g8.c. */

extern int func_002A77E0(int);
/* The level's id lists: the number of groups, the table of the groups' lists (a pointer, read
   through $gp in a branch delay slot and as a bare lui/lw elsewhere: `sda` arrays of unknown size
   give that), the base of the 64-byte records of the first walk, the base of the 32-byte records
   of the second, and the table that maps a record's byte at +0x1D to a class. */
extern float func_00283198(float);
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);

/* State 0 looks for the group of the level's id lists that holds the 64-byte record closest to
   the object (first walk, distances below 9999.0; the group index goes to the state's first word
   and the function ends when there is none), sets the object's aim from two random values
   (func_002A7878, func_002A7940) and the record list at state + 0x40, removes the object when the
   state's byte at +0x8A is zero, and otherwise walks the chosen group's 32-byte records
   (second walk): records of class 0xD34 and 0xD33 get their id written into the record list with
   the payload at state + 0x680 and state + 0x6A0 (func_L00_00323E48).  It then picks two random
   angular speeds (the second gets the sign opposite to the first) and goes to state 1, which
   keeps aiming and turns the two angles at +0x688 and +0x6A8.  Both walks keep the second
   `p != 0` guard before the `p[-1]` read and the second walk has a pointer variable of its own
   (one shared variable swaps two callee-saved registers).  Measured: a0 + 0xC0 and a0 + 0xF0
   formed in locals ahead of the second walk make loop.c hoist the two class constants out of it
   (two more saved registers); written at their use after the walk, as below, they stay in the
   loop.  The sign test is a store followed by a conditional store, which gives retail's
   `bc1f` with the first store in its slot and lets the constant 1 be shared by both stores. */
