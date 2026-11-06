#include "include_asm.h"

typedef struct { int ids[2]; } SolTextPair2;
extern SolTextPair2 D_L00_001AE110;
extern char D_L00_001AE118[];
extern unsigned char D_001A7B94 __attribute__((sda));
extern unsigned char D_001A7B95 __attribute__((sda));
extern void func_US2_0033BF90(void *);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern int func_0027FAA8(int, int, unsigned long, char *, int);

void func_US2_0033DC68(char *object)
{
    char buffer[128];
    SolTextPair2 pair;
    char *first;
    char *label;
    char *second;
    char *format;
    int color;

    func_US2_0033BF90(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = func_00288FB8(0x2C75);
    second = func_00288FB8(pair.ids[D_001A7B95 != 0]);
    func_00115DA8(buffer, format, first, second);
    func_0027FAA8(0x100, 0x96, color, buffer, -1);

    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = func_00288FB8(0x2C74);
    second = func_00288FB8(pair.ids[D_001A7B94 != 0]);
    func_00115DA8(buffer, format, label, second);
    func_0027FAA8(0x100, 0xBE, color, buffer, -1);
}

extern unsigned char D_001A7BB3 __attribute__((sda));
extern unsigned char D_001A7BB2 __attribute__((sda));
extern void func_0027F110(void);
extern void func_0027F120(void);

/* func_US2_0033E9B8, the v2.00 copy of func_0033D970: the same C with func_0027F120 before the text and
 * func_0027F110 after it. func_0027FAA8 must be declared int here (as in this unit), not void: the ignored
 * call value is what leaves the second test in $v1, so this cannot live in 0033C958.c, which declares it void. */
void func_US2_0033E9B8(char *object)
{
    char buffer[128];
    SolTextPair2 pair;
    char *first;
    char *label;
    char *second;
    char *format;
    int color;

    func_US2_0033BF90(object + 8);
    func_0027F120();
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = func_00288FB8(0x2C30);
    second = func_00288FB8(pair.ids[D_001A7BB2 != 0]);
    func_00115DA8(buffer, format, first, second);
    func_0027FAA8(0x100, 0x96, color, buffer, -1);

    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = func_00288FB8(0x3079);
    second = func_00288FB8(pair.ids[D_001A7BB3 != 0]);
    func_00115DA8(buffer, format, label, second);
    func_0027FAA8(0x100, 0xBE, color, buffer, -1);
    func_0027F110();
}

extern void func_US2_0033BF90();
extern void func_002DAF68();
extern void func_US2_003378A0();
extern void func_00336828();
extern void func_00336320();
extern void func_US2_0033FDD8();

/* Forwards one object pointer, eight pointer-plus-constant arguments and a null to ten calls in a fixed order. */
void func_US2_0033FEF8(char *p)
{
    func_US2_0033BF90(p + 8);
    func_002DAF68(0);
    func_US2_003378A0(p + 792);
    func_US2_003378A0(p + 880);
    func_US2_003378A0(p + 968);
    func_00336828(p + 732);
    func_00336320(p + 1056);
    func_US2_003378A0(p + 1576);
    func_US2_003378A0(p + 1488);
    func_US2_0033FDD8(p);
}
