#include "include_asm.h"

extern int func_00282978_5(char *handle);

extern void func_0029F338_2(char *object);

#ifndef RAC2_T_NODE16_F23626AD8
#define RAC2_T_NODE16_F23626AD8
typedef struct Node16_F23626ad8 Node16_F23626ad8;
#endif

#ifndef RAC2_T_NODE104_F23626AD8
#define RAC2_T_NODE104_F23626AD8
typedef struct Node104_F23626ad8 Node104_F23626ad8;
#endif

#ifndef RAC2_T_NODE24_F23626AD8
#define RAC2_T_NODE24_F23626AD8
typedef struct Node24_F23626ad8 Node24_F23626ad8;
#endif

struct Node16_F23626ad8 {
    short h0;
    unsigned char pad2[2];
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
};

struct Node104_F23626ad8 {
    unsigned char pad0[16];
    Node16_F23626ad8 *p16;
};

struct Node24_F23626ad8 {
    unsigned char pad0[52];
    unsigned short h52;
    unsigned char pad54[50];
    Node104_F23626ad8 *p104;
};

#ifndef RAC2_T_OBJ_F23626AD8
#define RAC2_T_OBJ_F23626AD8
typedef struct Obj_F23626ad8 {
    unsigned char pad0[4];
    union {
        int f4;
        struct {
            unsigned char b4;
            unsigned char b5;
            short h6;
        } b;
    } u;
    unsigned char pad8[16];
    Node24_F23626ad8 *f24;
} Obj_F23626ad8;
#endif

extern void func_002A0488(Node24_F23626ad8 *a, unsigned char b, unsigned char c, unsigned char d);

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

extern void func_002AFFD8(char *a0, void *a1, int a2);

extern void func_00282D30(void *a0, void *a1, float f12);

extern void func_L00_00411F48(char *a0);

extern char ref_L00_004117B8_00[];

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

INCLUDE_ASM("asm/levels", func_L00_004096B0);

INCLUDE_ASM("asm/levels", func_L00_00409E48);

INCLUDE_ASM("asm/levels", func_L00_0040A4A8);


INCLUDE_ASM("asm/levels", func_L00_0040B098);

/* func_L00_0040B2C0 is defined in L00_0040B2C0-flags-g8.c. */


INCLUDE_ASM("asm/levels", func_L00_0040B398);


INCLUDE_ASM("asm/levels", func_L00_0040BA30);

INCLUDE_ASM("asm/levels", func_L00_0040C7D8);

/* func_L00_0040CCA0 is in L00_0040CCA0.c. */

INCLUDE_ASM("asm/levels", func_L00_0040D058);

INCLUDE_ASM("asm/levels", func_L00_0040DC08);

/* Tests the handle cached in the object and, while the handle reports itself already released, drops the next sub-handle, otherwise runs the object's destroy helper. */
void func_L00_0040DF00(char *object)
{
    char *handle = *(char **)(object + 104);

    if (func_00282978_5(handle) == 0)
        func_00282978_5(handle + 4);
    else
        func_0029F338_2(object);
}

INCLUDE_ASM("asm/levels", func_L00_0040DF58);

/* func_L00_0040F6A0 is in L00_0040F6A0-g16.c. */

INCLUDE_ASM("asm/levels", func_L00_00410178);



INCLUDE_ASM("asm/levels", func_L00_00410690);

/* Reads the halfword at +0x1A of the object's node and grades it: 4 at or above 90, 3 above 60,
   2 above 30, else 1. The two lower bounds stay in variables, which is what keeps them in
   registers instead of an immediate compare. */
int func_L00_00410840(char *object)
{
    int value = *(short *)(*(int *)(object + 0x68) + 0x1A);
    int upper = 0x3C;
    int lower = 0x1E;
    int result = 1;

    if (value >= 0x5A)
        result = 4;
    else if (upper < value)
        result = 3;
    else if (lower < value)
        result = 2;
    return result;
}

INCLUDE_ASM("asm/levels", func_L00_00410888);

void func_L00_00410D18(void)
{
}

INCLUDE_ASM("asm/levels", func_L00_00410D20);

/* Calls a helper with a referenced node and three identity bytes of the object, then copies those bytes into a linked record when a node flag bit is set and the record exists with a non-zero leading short. */
void func_L00_004110D8(Obj_F23626ad8 *p)
{
    Node24_F23626ad8 *s;
    Node16_F23626ad8 *d;
    int v;

    func_002A0488(p->f24, p->u.b.b4, p->u.b.b5, p->u.b.h6);
    s = p->f24;
    if ((s->h52 & 0x20) == 0)
        return;
    d = ((Node104_F23626ad8 *)s->p104)->p16;
    if (d == 0)
        return;
    if (d->h0 == 0)
        return;
    d->b4 = p->u.b.b4;
    d->b5 = p->u.f4 >> 8;
    v = p->u.b.h6;
    d->b6 = v;
}



/* func_L00_004115E8 is defined in L00_004096B0-g8.c. */

/* Walks the thirty records of the level's block and, for every record whose +0x18 pointer is
   set, folds it into a sixteen-byte buffer: the record's own transform, then the scale of its
   +0x0C word, then its first three words added to the buffer. The block's address differs
   from level to level, so it takes a per-level name. */
void func_L00_004117B8(char *a0)
{
    char *s0 = ref_L00_004117B8_00;
    char *s2 = a0;
    char *p;
    float buf[4];
    int i;

    for (i = 0x1D; i >= 0; i--) {
        if (*(char **)(s0 + 0x18) != 0) {
            p = *(char **)(s0 + 0x18);
            func_002AFFD8(p + 0x10, buf, 1);
            p = *(char **)(s0 + 0x18);
            func_00282D30(buf, buf, *(float *)(p + 0xC) * 0.0008300250046886504f);
            p = *(char **)(s0 + 0x18);
            buf[0] += *(float *)(p + 0) * 0.0009764999849721789f;
            buf[1] += *(float *)(p + 4) * 0.0009764999849721789f;
            buf[2] += *(float *)(p + 8) * 0.0009764999849721789f;
        }
        s0 = s0 + 0x30;
    }
    func_L00_00411F48(s2);
}


INCLUDE_ASM("asm/levels", func_L00_00411B30);


/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_00412088(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

INCLUDE_ASM("asm/levels", func_L00_00412110);

/* func_L00_00412230 is defined in x-qcopy.c. */

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void func_L00_00412408(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

INCLUDE_ASM("asm/levels", func_L00_00412470);
