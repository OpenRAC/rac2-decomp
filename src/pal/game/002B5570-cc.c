/* func_PAL_002B5570, the PAL copy of func_002B49C0: the same C. */

typedef int s32;

typedef unsigned char u8;

/* Sets the second pending flag and reports whether it was newly set. */
/* func_002B39A0 is matched in 002B39A0-g8.c. */

/* Calls a callee on (second pointer, first pointer + 16); if the result is not below the first float argument it returns 0, otherwise it evaluates a second callee on (a float at second+8 minus a float at first+24) and returns 1 when that is below the second float argument, else 0. */
typedef struct {
    int reserved;
    int value;
    char remainder[0xA428];
} Record_2B4038;
extern Record_2B4038 D_00240450[];

/* func_002B41A8 is matched in 002B41A8.c. */

extern int D_001AA0F4 __attribute__((sda));

void func_PAL_002B5570(int value) {
    D_001AA0F4 = value;
}

/* func_002B49E0 is matched in 002B49E0-g8.c. */

/* func_002B4B70 is matched in 002B4B70-g8.c. */

/* func_002B4C18 is matched in 002B3868-g8.c (small data through $gp). */

extern int func_002B50E0(void *, void *, float);

/* func_002B50E0 is matched in 002B50E0.c. */

extern int func_002B50E0(void *, void *, float);

