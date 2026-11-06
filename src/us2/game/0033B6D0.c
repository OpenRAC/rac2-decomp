#include "include_asm.h"

typedef float f32;
typedef unsigned char u8;

/* func_0033A688 is matched in 003399B0-g8.c (-G8 small data). */

/* func_0033A6D8 is matched in 003399B0-g8.c (-G8 small data). */

/* Measured target: byte-identical across all 27 levels. */
void func_US2_0033BA10(u8 *a0, f32 a1) { *(f32 *)(a0 + 0x214) = a1; }

typedef int s32;

/* lot6 -- measured bodies with sizes recorded in the catalogue. */
void func_US2_0033BA18(u8 *a0, s32 a1, s32 a2) { a0 += a1 * 4; *(s32 *)(a0 + 0x1C8) = a2; }

/* writes the value if it is below the maximum; byte-identical across all 27 levels. */
void func_US2_0033BA28(u8 *a0, s32 a1) { if (a1 < *(s32 *)(a0 + 0x208)) *(s32 *)(a0 + 0x218) = a1; }

/* Measured target: byte-identical across all 27 levels. */
void func_US2_0033BA40(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x21C) = a1; }

extern int func_0033AB50(int);
extern void F7d9c8805_FUN_003361A8(int);
extern void F7d9c8805_FUN_00336968(int);

int func_US2_0033BB98(int a0)
{
	char *p = (char *)a0 + 12;
	int i;

	for (i = 4; i != -1; i--) {
		F7d9c8805_FUN_003361A8(p);
		p += 76;
	}
	F7d9c8805_FUN_00336968(a0 + 408);
	F7d9c8805_FUN_00336968(a0 + 496);
	F7d9c8805_FUN_00336968(a0 + 584);
	return a0;
}


extern void func_0033AE18(unsigned char *owner, int value);

/* func_0033ABD8 is matched in 003399B0-g8.c (-G8 small data). */

/* Measured target: byte-identical across all 27 levels. */
void func_US2_0033BE60(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x2C0) = a1; }

/* Measured target: byte-identical across all 27 levels. */
void func_US2_0033BE68(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x2C4) = a1; }

extern void func_00335E38(void *, float, float, float, float);
extern void func_003363C0(void *, float);

void func_US2_0033BE70(char *object) {
    char *r = object + 12;
    char *q = object + 0x188;
    int i;
    for (i = 4; i >= 0; i--) {
        if (*(short *)q != 0) {
            float *position = *(float **)object;
            func_00335E38(r, position[0], position[1], 0.0f, 0.0f);
            func_003363C0(r, *(float *)(object + 0x2A4));
        }
        r += 76;
        q += 2;
    }
    if (*(int *)(object + 0x2C0) != 0) {
        func_00335E38(object + 0x198, (*(float **)object)[0] + *(float *)(object + 0x2A8), (*(float **)object)[1] + *(float *)(object + 0x2AC), 0.0f, 0.0f);
        func_00335E38(object + 0x248, (*(float **)object)[0] + *(float *)(object + 0x2B8), (*(float **)object)[1] + *(float *)(object + 0x2BC), 0.0f, 0.0f);
        func_00335E38(object + 0x1F0, (*(float **)object)[0] + *(float *)(object + 0x2B0), (*(float **)object)[1] + *(float *)(object + 0x2B4), 0.0f, 0.0f);
    }
}

extern void F624a0727_FUN_00336A78(char *target);
typedef struct { char pad[8]; short n; void (*fn)(char *); } ENTRY_F624a0727;

void func_US2_0033BF90(char *object)
{
    char *r = object + 12;
    char *q = object + 60;
    char *p = object + 392;
    int i;

    for (i = 4; i >= 0; i--) {
        if (*(short *)p != 0) {
            ENTRY_F624a0727 *t = *(ENTRY_F624a0727 **)q;
            t->fn(r + t->n);
        }
        r += 76;
        q += 76;
        p += 2;
    }
    if (*(int *)(object + 704) != 0) {
        F624a0727_FUN_00336A78(object + 408);
        if (*(int *)(object + 708) != 0) {
            if (*(int *)(object + 716) != 0)
                F624a0727_FUN_00336A78(object + 584);
            if (*(int *)(object + 712) != 0)
                F624a0727_FUN_00336A78(object + 496);
        }
    }
}

