#include "include_asm.h"
#include "names.h"

extern int PadPressedWithin(int, int, int *);

extern int subtract_integer_with_clamp(int);

extern void func_00282CC0_2(char *dst, char *left, char *right);

extern void vec_transform_or_copy(char *dst, char *src);

extern int FloatToInt(float value);

extern void func_002B9180_2(char *object);

extern int func_00282978_11();

extern void func_002B9180_17();

typedef unsigned char u8;

extern void func_00282D30_2(void *, void *, float);

extern void func_00282CC0_3(void *, void *, void *);

extern void func_002B9180_1(void *);

/* Calls one routine twice with two different ids and a two-int scratch area, short-circuiting to a zero result if either fails, and otherwise returns whether a third routine's difference of the two ints is below a fourth incoming integer. */
/* Tells whether two pad buttons were pressed within a few frames of each other. */
int pad_presses_within_frames(int a0, int a1, int a2, int a3)
{
	int r = 0;
	int a;
	int b;

	if (PadPressedWithin(a0, a2, &a)) {
		if (PadPressedWithin(a1, a2, &b))
			r = subtract_integer_with_clamp(a - b) < a3;
	}
	return r;
}


typedef struct {
    char gap_L00_0032F038[0x18E];
    short head;
    int count;
    char gap2_L00_0032F038[0xC4];
    float v[30];
} Table_L00_0032F038;

extern Table_L00_0032F038 g_pad_state;

/* Returns the float n entries back from the head of a 30-entry history ring (n capped at the
   ring's count); RAC1's read_pad_float_history. */
float ReadPadFloatHistory(int n)
{
    if (g_pad_state.count < n)
        n = g_pad_state.count;
    return g_pad_state.v[(g_pad_state.head - n + 30) % 30];
}


/* Does nothing. */
void nop_l00_stub_2(void)
{
}

/* Does nothing. */
void nop_l00_stub_3(void) {
}

/* func_L00_00333F90 is in L00_00333F90.c. */

/* Calls a three-argument callee twice and a two-argument callee twice over fields of the first object, folds a float field through a float-to-int callee into an int field of the object, and calls a last callee when the updated field is negative. */
void part_l00_update_fading_effect(char *a)
{
    char *p1 = a + 16;
    char *p2 = a + 32;
    char *p3 = a + 48;
    int v;

    func_00282CC0_2(p1, p1, p3);
    func_00282CC0_2(p2, p2, p3);
    vec_transform_or_copy(p1, p1);
    vec_transform_or_copy(p2, p2);
    v = *(int *)(a + 4) - (FloatToInt(*(float *)(p3 + 12)) << 24);
    *(int *)(a + 4) = v;
    *(int *)(a + 12) = v;
    if (v < 0)
        func_002B9180_2(a);
}

/* func_L00_00335558 is in L00_00335558.c. */

/* Calls a routine on pointer-plus-10 and, when it returns non-zero, calls a second routine with the pointer itself. */
void part_free_effect_if_done(char *p)
{
    if (func_00282978_11(p + 10)) {
        func_002B9180_17(p);
    }
}


/* func_L00_00338D28 is matched in L00_00338D28.c (built with -frac2-qcopy). */

/* Updates a record: calls two helpers on the sub-object at +0x20 (float argument 0.975f), advances the float at +0x0C by 14700.0f, adds the byte at +0x30 into the byte at +0x08, then adds 0xFE000000 to the word at +0x04 and calls a third helper when the result is negative. */
void part_update_decaying_effect(char *a0)
{
    char *p = a0;
    char *q = p + 32;
    int v;

    func_00282D30_2(q, q, 0.975f);
    func_00282CC0_3(p + 16, p + 16, q);
    *(float *)(p + 12) = *(float *)(p + 12) + 14700.0f;
    *(u8 *)(p + 8) = *(u8 *)(p + 8) + *(u8 *)(q + 16);
    v = *(int *)(p + 4) + 0xFE000000;
    *(int *)(p + 4) = v;
    if (v < 0) {
        func_002B9180_1(p);
    }
}

/* func_L00_0033AA40 is in L00_0033AA40.c. */

/* func_L00_0033BA68 is matched in L00_0033BA68.c (built with -frac2-qcopy). */

/* func_L00_0033C238 is matched in L00_0033C238.c. */





/* func_L00_0033E3B8 is in L00_0033E3B8.c. */



/* func_L00_0033EA00 is matched in L00_0033EA00-g8.c. */


/* func_L00_0033EE38 is in L00_0033EE38.c (built with -g). */
