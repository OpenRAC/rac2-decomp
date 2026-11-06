/* func_US2_L02_003FF768, the USA v2.00 copy of func_L02_003FE1B0: the same C. */

typedef unsigned char u8;

typedef unsigned short u16;

typedef unsigned int u32;

typedef short s16;

typedef int s32;

extern char *D_L02_001B359C __attribute__((sda));

extern u32 D_L02_001FC060[];

extern void func_L02_003D2390(char *);

extern void func_L02_003D4900(char *);

extern void func_L02_003DB6D8(char *);

extern void func_L02_003F18E8(char *);

extern void func_L02_0040B980(char *);

extern void func_L02_0040D180(char *);

extern s32 func_L02_00400650(char *, s32);

extern int D_L02_002A5600[];

/* Runs func_L02_003F5430 first when bit 0 of D_L02_001B30C8 is set. The angle at +0x88 is stepped
   (func_002AA2E8, 0.05 degree) towards the target at +0x8C when func_00282948 reports the timer at
   +0x90 idle or just run out, and towards zero while it is still counting down. When the target lies
   between zero and the angle, the timer gets a random 30..90 and the target a random size with the
   opposite sign. The angle is then the third word of a vector func_002833F0 turns into a matrix,
   which multiplies the 64-byte records of D_L02_001B3B00 that the entries of the list at +0x40 name,
   for each bit set in the mask at +0x84. */
/* func_L02_003F5710 is defined in L02_003F5430-g8.c (three $gp accesses). */

/* Maps the values 0, 1, 3, 5, 6, 7, 8, 10, 11 and 13 to 0..9 (in no regular order) and any other
   value to -1. The dispatch reads the level's own jump table (fourteen words in the level's data
   at 0x2A5520, one per value); `cases` only keeps the labels alive, and each label is named after
   the value that reaches it. */
/* Maps a value below 14 to an id (0x31 to 0x3B and 0x91 to 0x93, in no regular order) and any
   other value to -1. The dispatch reads the level's own jump table (fourteen words in the level's
   data at 0x2A5560, one per value); `cases` only keeps the labels alive, and each label is named
   after the value that reaches it. */
s32 func_L02_003F9B70(s32 a0);

/* func_L02_003FB000 is defined in L02_003FB000-g8.c. */

/* func_L02_003FB120 is matched in L02_003FB120-g8.c (built with -g). */

extern s32 func_L02_003FB6C0(char *, char *);

/* Looks through the entity list the object's state names for one of kind A1 whose byte at +0x20
   is 1; records A0 as that entity's owner and returns func_L02_003FB6C0's result for it.
   The walk is func_L02_003FB5A0's `do { ... } while ((s16)*p++ >= 0);`: a `for (;;)` with the
   test and the increment in the body makes this cc1 annul the loop-bottom slot (`bgezl`). */
extern char *D_L02_001B359C __attribute__((sda));
extern u32 D_L02_001FC060[];
/* Looks through the entity list the object's state names for one of kind A1 whose byte at +0x20
   is 1; for the kinds 0x9F8 and 0xA44 it records A0 as that entity's owner, runs the kind's start
   function, counts it in the state and returns it. */
/* Counts the kind of A1 in the state and sets its scale to one. */
s32 func_L02_003FB6C0(char *a0, char *a1);

/* func_L02_003FB7E0 is defined in L02_003F5430-g8.c ($gp accesses). */

/* True when every occupied slot of the list at +0xA8 has content; then the list is cleared. */
extern char *D_L02_001B359C __attribute__((sda));
extern u32 D_L02_001FC060[];
extern void func_L02_003D2390(char *);
extern void func_L02_003D4900(char *);
extern void func_L02_003DB6D8(char *);
extern void func_L02_003F18E8(char *);
extern void func_L02_0040B980(char *);
extern void func_L02_0040D180(char *);

/* Walks the 16-bit stream the object's table entry points at and calls the handler of the
   entity type each word names; a negative word ends the stream. */
extern s32 D_L02_001B35B8[] __attribute__((sda));
extern void func_L02_003FC1B0(char *, s32);

/* The test of the entity walks below: the group word at +0x40 is read again for every condition,
   as the handlers may change it. */
/* Clears the flag (+0x2F6 of a 0x9CA entity's block, +0x4EA of a 0xB22 one) of every entity of
   the group that has it set and passes the entity's kind to func_L02_003FC1B0; then, twice, picks
   among the group's entities of those two kinds that are not 0xFE/0xFD, have a state byte (+0x20)
   of 4 or more and the flag not set, the one nearest to D_00189EA0, sets its flag and takes one
   off its kind's count (+0x50, +0x54). */
/* Counts down one of the four timers named by a1; true when it was still running. */
void func_L02_003FC1B0(char *a0, s32 a1);

extern char *D_L02_001B359C __attribute__((section(".sdata")));
extern s32 D_L02_001B35B8[] __attribute__((sda));
/* Counts the entities of the object's group (state word 0x48) for which func_L02_004024A0 holds, then
   sets (func_L02_004024B0) or clears (func_L02_004024C0) entities until the count equals A1. */
/* Counts the entities of the object's group (state word 0x4C) for which func_L02_003D7300 holds, then
   sets (func_L02_003D7310) or clears (func_L02_003D7320) entities until the count equals A1. */
/* Walks the entities of the group the object names (the group word is re-read for every
   test: the handlers may change it).  Each live, unflagged one that passes the screen
   against the two bounds is handed to the handler of its type.  Afterwards the follow-up is
   called unless the resident record passes the screen. */
/* func_L02_003FC9C0 is matched in L02_003F5430-g8.c. */

extern int func_L02_003F9B70(int);
/* Starts the actor: calls func_L02_00400650 with 0x25 plus a random pick below 2, sets state 1,
   releases the object held at +0xC0 and, by a per-slot flag, hands a vector whose third float
   is -1.59 or 2.16, with the matching 128-byte record, to func_L00_002B9D60; ends by setting
   D_L02_001AA1B0 to -1. */
/* func_L02_003FCBF0 is defined in L02_003F5430-g8.c (this unit has no $gp access for it). */

/* func_L02_003FCCA0 is defined in L02_003F5430-g8.c (D_001A79F8 is a $gp access in a delay slot). */

/* Runs func_L02_003A6F78 on every entity of the object's two groups (state words 0xC8 and
   0xC4); an empty group, or a group word of 0xFF, ends the function. */
/* func_L02_003FD228 is defined in L02_003F5430-g8.c (it reads its globals through $gp). */

/* func_L02_003FD7C8 is defined in L02_003F5430-g8.c ($gp accesses). */

/* Maps a value below 14 to an id (0x2F48 to 0x2F51, 0x2F6E and 0x3240 to 0x3242, in no regular
   order); any other value gives 0x2F48. The dispatch reads the level's own jump table (fourteen
   words in the level's data at 0x2A5600, one per value); `cases` only keeps the labels alive, and
   each label is named after the value that reaches it. */
s32 func_US2_L02_003FF768(u32 a0) {
    static void *cases[14] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7, &&c8, &&c9, &&c10,
                              &&c11, &&c12, &&c13};
    if (a0 < 14)
        goto *D_L02_002A5600[a0];
    goto dflt;
c0:
    return 0x2dde;
c2:
    return 0x2ddf;
c4:
    return 0x2de0;
c9:
    return 0x2de1;
c6:
    return 0x2de2;
c3:
    return 0x2de3;
c1:
    return 0x2de4;
c5:
    return 0x2de5;
c7:
    return 0x2e04;
c10:
    return 0x2de6;
c11:
    return 0x2de7;
c8:
    return 0x30d6;
c12:
    return 0x30d7;
c13:
    return 0x30d8;
dflt:
    return 0x2dde;
}

/* func_L02_003FF9A0 is defined in L02_003F5430-g8.c ($gp accesses). */

/* func_L02_003FFDB0 is defined in L02_003FFDB0-g8.c ($gp accesses). */

/* func_L02_004002E0 is matched in L02_004002E0-g8.c (built with -g). */

/* func_L02_004004D0 is matched in its own unit, src/levels/shared/L02_004004D0-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* Timer for one of the thirty-nine messages, refused while one is running. */
s32 func_L02_00400650(char *a0, s32 a1);

/* func_L02_00400720 is defined in L02_003F5430-g8.c ($gp accesses). */

/* func_L02_00400948 is defined in L02_003F5430-g8.c ($gp accesses). */

/* Walks the list of objects at D_L02_001B35A8 (linked through +0x28) and hands each one to the
   handler of its kind, the half-word at +0xAA. */
/* True when the field at +0xAA is 0xB59, the global at D_0017A80 is 1 and bit 3 of the
   byte at +0x20 is clear. */
/* func_L02_00401BF8 is matched in L02_00401BF8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_00401D38 is defined in L02_003F5430-g8.c ($gp accesses). */

