/* func_PAL_L02_003D8D80, the PAL copy of func_L02_003D4D00: the same C, where scale 0x1F4 - *(short *)(state + 0x32A). */

extern int func_002A77E0(int);

extern void func_L02_003D5C20(char *);

extern void func_L02_003D5DF8(char *);

extern void func_L02_003D62F0(char *);

extern void func_L02_003D6348(char *);

extern void func_L02_003D6538(char *);

/* func_L02_003D26B0 is defined in L02_003D26B0-aim-g8.c. */

/* func_L02_003D2DE0 is defined in L02_003D2DE0-g16.c. */

/* func_L02_003D4308 is defined in L02_003D4308-g8.c. */

/* func_L02_003D47B0 is matched in L02_003D47B0-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* Advances the actor's step counter until the float at +0x20 no longer lies below the share
   (3 - step) / 3 of the count at +0x24, then latches the done flag; once only. */
int func_PAL_L02_003D8D80(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    short timer = *(short *)(state + 0x32E);
    int delta;

    if (timer < 0x12C) {
        return 0;
    }
    if (timer < 0x1F5) {
        delta = (((int)(0x1F4 - *(short *)(state + 0x32A)) * 5 + 2) / 6);
        if (delta > 0) {
            if (func_002A77E0(delta) != 0) {
                return 0;
            }
        }
    }
    *(short *)(state + 0x32A) = 0;
    *(short *)(state + 0x32E) = 0;
    return 1;
}

/* func_L02_003D4E00 is matched in L02_003D4E00-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003D4ED0 is matched in L02_003D4ED0.c (built with -frac2-qcopy). */

/* func_L02_003D5118 is matched in L02_003D5118.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003D5748 is defined in L02_003D5748-g8-dbg.c. */

void func_L02_003D5C20(char *arg0);

/* func_L02_003D5CF0 is matched in L02_003D5CF0.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

void func_L02_003D5DF8(char *arg0);

/* func_L02_003D5E40 is matched in L02_003D5E40-g8.c. */

/* func_L02_003D5F50 is defined in L02_003D26B0-g8.c. */

void func_L02_003D62F0(char *arg0);

void func_L02_003D6348(char *arg0);

/* func_L02_003D6388 is matched in L02_003D6388-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

void func_L02_003D6538(char *arg0);

/* func_L02_003D6570 is matched in L02_003D6570-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003D6690 is defined in L02_003D6690-helpers-g8.c. */

/* func_L02_003D6A20 is matched in L02_003D6A20-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier -g). */

/* Whether the object's variant byte is one of the later ones. */
/* func_L02_003D7330 is defined in L02_003D7330-g8.c. */

typedef struct {
    char pad0[0x80];
    float x;
    float y;
} L02_003D7900_Hero;

extern L02_003D7900_Hero D_00189E20;

/* Builds a four-float vector and hands it to the two vector helpers, tints the three colour
   records of the actor's state from it, then walks the three actors the state points at:
   each gets the angle to the hero written at 0xF8 and the behaviour its type selects. */
/* func_L02_003D91A0 is defined in L02_003D91A0.c. */

/* Runs only while the state's target pointer (+0x240) is set.  The word at +0x98 of the object
   table entry the state selects (+0x244) is zeroed for the duration and put back at the end.
   Four rounds, for the joint pairs (1, 2), (3, 4), (5, 6) and (7, 8): the two joint positions
   (func_0029FCC0), func_L00_0031BDC0 on them and the target's position, the offset from the
   actor's position to its result, a vector made of the offset's first two floats turned a
   quarter turn, scaled by func_00282D30 (2.0) and completed with 1.0 and 5627.925, an effect
   record started from it (func_002A8C00), and two func_00277F48 calls on that record (0.65 and
   0.95). */
/* func_L02_003DAE60 is matched in L02_003DAE60-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003DAF90 uses its dedicated G16 vector unit. */

/* func_L02_003DB030 is matched in L02_003DB030-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003DB158 is matched in L02_003DB158-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003DB200 is matched in L02_003DB200-g8.c (built with -frac2-zero-ti-por). */

