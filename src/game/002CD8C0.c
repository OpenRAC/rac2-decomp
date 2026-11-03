#include "include_asm.h"

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;

typedef struct {
    char reserved00[0x14F8];
    int first;
    int reserved14fc;
    int second;
} CallbackToggleState;

extern void func_0027C540(long);

extern void func_0027C660(void);

extern void func_0029C450(void);

extern void func_0027C540(long arg0);

extern void func_0027C540(long param_1);

extern int F750245c6_D_001A7340 __attribute__((sda));

extern void F750245c6_FUN_0028FC48(int a, int b, int c, int d, char *e, int f);

extern char *D_001A8CFC[] __attribute__((sda));

extern void func_00341550(void *, int);

extern void func_00341540(char *, char *, char *, char *);

extern void func_00341610(char *, int);

extern char D_002615F8[];

extern char D_00261698[];

extern char D_00261750[];

extern int D_001AB9B0 __attribute__((sda));

extern char *D_001A8CFC[] __attribute__((sda));

extern void *func_00341558(void *);

extern char *D_001A8CFC[] __attribute__((sda));

extern int D_0025CADC;

extern CallbackState D_001F2840;

extern int D_00138344;

extern int D_001A7908 __attribute__((sda));

extern CallbackToggleState D_00189E20;

extern float D_0018B300[];

extern int func_002E5E58(int, unsigned int, void *);

extern void func_00282F20(void *, void *, float);

extern int D_00138344;

extern void func_0029C640(int);

extern void func_0029C610(void);

extern void func_0029C6B0(int);

/*
 * Disassembled at 0x002cd220
 * Signature: int FUN_002cd220(void)
 * Behavior:
 *   - Saves RA on stack
 *   - Calls func_0027C540(0)
 *   - Calls func_0029C138()
 *   - Calls func_0027C660()
 *   - Restores RA from stack
 *   - Returns 0
 */

void func_0027C540(long);

void func_0027C660(void);

/*
 * Function: func_002D2EE0
 *
 * Disassembly summary:
 * - Saves return address on stack
 * - Calls func_0027C540(0) (with zero argument)
 * - Calls func_0029C7A0()
 * - Calls func_0027C660()
 * - Restores return address
 * - Returns 0
 *
 * Notes:
 * - The function follows standard MIPS ABI prologue/epilogue.
 * - Delay slots are filled with NOP or argument setup as seen in disassembly.
 * - No local variables used.
 * - All external function addresses come from the assigned externals list.
 */

/* External functions declared with exact aliases from task.externals */

long long func_002CD8C0(void)
{
    func_0027C540(0LL);
    func_0029C450();
    func_0027C660();
    return 0LL;
}

int func_002CD8F0(void *object) { char *root=D_001A8CFC[0]; if (root != 0) { func_00341550(root+0x3BE08,1); *(void **)((char *)object+0x34)=func_00341558(D_001A8CFC[0]+0x3BE08); } return 0; }

INCLUDE_ASM("asm/game", func_002CDA20);

int func_002CDAB0(void)
{
    if (D_001A8CFC[0] != 0) {
        func_00341550(D_001A8CFC[0] + 0x3BE08, 1);
        func_00341540(D_001A8CFC[0] + 0x3BE08, D_002615F8, D_00261698, D_00261750);
        func_00341610(D_001A8CFC[0] + 0x3BE08, 0);
    }
    return 0;
}

/* func_002CDB30 is built from 002CDB30-g8.c. */

/* func_002CDD88 is built from 002CDD88-g8.c. */

int func_002CE5B8(void) {
    D_001AB9B0 = 1;
    return 0;
}

int func_002CE5C8(void) {
    return 0;
}

/* func_002CE5D0 is built from 002CE5D0-g8.c. */

/* func_002CEBD0 is built from 002CEBD0-g8.c. */

void func_002CF0A0(int a0, char *a1)
{
    int h, k, p, m;
    k = a0 / 2 + 5;
    h = F750245c6_D_001A7340 / 2;
    m = h - k;
    p = h + k;
    F750245c6_FUN_0028FC48(m - 2, 312, p + 4, 314, a1, 0);
    F750245c6_FUN_0028FC48(m - 2, 333, p + 4, 335, a1, 0);
    F750245c6_FUN_0028FC48(m - 2, 313, m, 334, a1, 0);
    F750245c6_FUN_0028FC48(p + 2, 313, p + 4, 334, a1, 0);
}

int func_002CF188(char *object) {
    if (D_001A8CFC[0] != 0)
        *(void **)(object + 0x34) = func_00341558(D_001A8CFC[0] + 0x3BE08);
    return 0;
}

INCLUDE_ASM("asm/game", func_002CF2B8);

/* func_002CF340 is built from 002CF340-g8.c. */

INCLUDE_ASM("asm/game", func_002CF5B0);

/* func_002CF7F0 is built from 002CF7F0-g8.c. */

int func_002CFBE0(void) {
    return 0;
}


/* func_002CFDA8 is built from 002CFDA8-g8.c. */

int func_002D01C8(void) {
    return 0;
}


/* func_002D0568 is built from 002D0568-rc2.c. */




/* func_002D0B98 is built from 002D0B98-g8.c. */


/* func_002D0FA0 is built from 002CD8C0-g8.c for small-data accesses. */

/* func_002D1228 is built from 002D1228-g8.c. */

extern int D_001A7A00[] __attribute__((sda));
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern unsigned char D_001395E9;
extern unsigned char D_001395B8[];
extern int D_001AA438 __asm__("D_001AA438__gp") __attribute__((section(".sdata")));
extern unsigned char D_001ABA30 __asm__("D_001ABA30__gp") __attribute__((section(".sdata")));
extern unsigned char D_001ABA31[] __attribute__((sda));
extern unsigned char D_001ABA32[] __attribute__((sda));
extern unsigned char D_001ABA33[] __attribute__((sda));
extern unsigned char D_001ABA34[] __attribute__((sda));
extern unsigned char D_001ABA35[] __attribute__((sda));
extern unsigned char D_001ABA36[] __attribute__((sda));
extern unsigned char D_001ABA37[] __attribute__((sda));

int func_002D1590(void)
{
    if (D_001A8CFC[0] != 0 && ((unsigned char *)D_001A7A00)[0xA] != 0) {
        if (D_001A7BB0[0x3A] != 0 && D_001395E9 != 0)
            D_001ABA30 = 1;
        if (D_001A7BB0[0x3C] != 0 && (D_001395B8[0x4D] != 0 || D_001395B8[0x52] != 0))
            D_001ABA31[0] = 1;
        if (D_001A7BB0[0x43] != 0 && (D_001395B8[0x57] != 0 || D_001395B8[0x5C] != 0))
            D_001ABA32[0] = 1;
        if (D_001A7BB0[0x43] != 0 && D_001395B8[0x3D] != 0)
            D_001ABA33[0] = 1;
        if (D_001A7BB0[0x52] != 0)
            D_001ABA34[0] = 1;
        if (D_001A7BB0[0x4E] != 0)
            D_001ABA35[0] = 1;
        if (D_001A7BB0[0x4F] != 0)
            D_001ABA36[0] = 1;
        if (D_001AA438 != 0)
            D_001ABA37[0] = 1;
    }
    return 0;
}

/* func_002D16C8 is built from 002D16C8-g32.c. */

/* func_002D1970 is built from 002D1970-g8.c. */

/* func_002D1CB0 is built from 002CD8C0-g8.c for small-data accesses. */



int func_002D2010(void) {
    return 0;
}


INCLUDE_ASM("asm/game", func_002D2188);

int func_002D23D8(void) {
    if (D_001A8CFC[0] != 0) D_0025CADC = -300;
    return 0;
}




int func_002D2830(void) {
    return 0;
}

int func_002D2838(void)
{
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(D_001F2840.source + 0xE0);
        if (value != 0)
            D_001F2840.value = value;
        else if (D_001F2840.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else if (flags & 0x40) {
        func_002E5E58(4, 0, 0);
        switch (D_001A7908) {
        default:
            D_001A7908 = 0;
            D_00189E20.second = 0;
            D_00189E20.first = 0;
            break;
        case 0:
            D_001A7908 = 1;
            func_00282F20(D_0018B300, (char *)D_0018B300 - 0x14E0, 1.0f);
            break;
        }
    }
    return result;
}

/* func_002D2918 is built from 002D2918-g8.c. */

int func_002D2BD8(void) {
    func_0029C640(D_00138344);
    return 0;
}

int func_002D2C00(void) {
    func_0027C540(0);
    func_0029C610();
    func_0027C660();
    return 0;
}

int func_002D2C30(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(D_001F2840.source + 0xE0);
        if (value != 0)
            D_001F2840.value = value;
        else if (D_001F2840.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        func_0029C6B0(flags);
    return result;
}
