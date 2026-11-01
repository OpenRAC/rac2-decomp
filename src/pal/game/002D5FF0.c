#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_002D5FF0);

extern int D_00138344;
extern void func_0029CF08(int);
extern int D_00138344;
extern void func_0029CF08(int);

int func_PAL_002D60F0(void) {
    func_0029CF08(D_00138344);
    return 0;
}

#include "common.h"
extern void func_PAL_0029D870(void);

int func_PAL_002D6118(void)
{
  func_0027C540(0);
  func_PAL_0029D870();
  func_0027C660();
  return 0;
}





extern void func_PAL_0029D4B8(void);

int func_PAL_002D62F0(void)
{
  func_0027C540(0);
  func_PAL_0029D4B8();
  func_0027C660();
  return 0;
}


extern char *D_001A8CFC[] __attribute__((sda));
extern void func_00341CD8(char *, int);
extern void func_PAL_00343F18(char *, char *);
extern char D_00261540[];

int func_PAL_002D6320(void)
{
    if (D_001A8CFC[0] != 0) {
        func_00341CD8(D_001A8CFC[0] + 0x3EA78, 1);
        func_PAL_00343F18(D_001A8CFC[0] + 0x3EA78, D_00261540);
    }
    return 0;
}



extern void func_PAL_0029D448(void);

int func_PAL_002D6448(void)
{
  func_0027C540(0);
  func_PAL_0029D448();
  func_0027C660();
  return 0;
}


extern void func_003423A8(char *, int);
extern void func_PAL_003443E8(char *, char *);

extern char D_PAL_00261330[];

int func_PAL_002D6478(void)
{
    if (D_001A8CFC[0] != 0) {
        func_003423A8(D_001A8CFC[0] + 0x3E810, 1);
        func_PAL_003443E8(D_001A8CFC[0] + 0x3E810, D_PAL_00261330);
    }
    return 0;
}





extern void func_0027C540(long);
extern void func_0027C660(void);
void func_0027C540(long);
void func_0027C660(void);
extern void func_0027C540(long arg0);
extern void func_0027C540(long param_1);
extern void func_0029CED8(void);

long long func_PAL_002D64F8(void)
{
    func_0027C540(0);
    func_0029CED8();
    func_0027C660();
    return 0;
}

extern int D_001C51D4;

int func_PAL_002D6528(void) {
    D_001C51D4 = -1;
    return 0;
}



extern char D_001F2840[];
extern int D_001A79F0 __attribute__((sda));
extern volatile unsigned char D_001A7C01 __attribute__((sda));
extern int D_001C51D0;
extern int D_001C4FA0[];
extern void func_0027D330(int);
extern void func_002C9C60(float);
extern int func_002E5E58(int, unsigned int, void *);
extern int func_0026F7D8(void);
extern int func_0026F7D8(void);
extern void func_00288CB0(int, int);
extern void func_002B49E0(int, int, int, int, int);
extern int func_PAL_0029CDA8(int);
extern int func_0026F7D0(void);

int func_PAL_002D6548(void)
{
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        char *root;
        int value;
        func_0027D330(4);
        func_002C9C60(4.0f);
        root = D_001F2840;
        value = *(int *)(*(char **)(root + 0x14) + 0xE0);
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0:
                result = -1;
                goto finish;
            default:
                break;
            }
        }
        result = 0;
    } else if (flags & 0xD00) {
        result = 1;
        D_001C51D0 = D_001A79F0;
    } else if (flags & 0x40) {
        int *base = D_001C4FA0;
        if (D_001A79F0 != base[0x230 / 4]) {
            result = 1;
            func_002E5E58(4, 0, 0);
            if (base[0x230 / 4] != 0 && D_001A7C01 == 0 && base[0x230 / 4] == 2) {
                func_002B49E0(6, 2, 1, 0x19, 0);
            } else if (func_0026F7D0() && func_0026F7D8()) {
                func_00288CB0(D_001C4FA0[0x230 / 4], 1);
            } else {
                func_002B49E0(6, 2, 1, D_001C4FA0[0x230 / 4], 0);
            }
        } else {
            result = 1;
            func_002E5E58(4, 0, 0);
            func_0027D330(4);
        }
    } else {
        func_PAL_0029CDA8(flags);
    }
finish:
    return result;
}


extern void func_0029CB20(void);

int func_PAL_002D66E0(void) {
    func_0027C540(0);
    func_0029CB20();
    func_0027C660();
    return 0;
}

extern int func_PAL_002D6730(int, int, int *);

void func_PAL_002D6710(int first, int second) {
    int result[4];
    result[0] = 0;
    func_PAL_002D6730(first, second, result);
}


extern int func_002D5B58(int, int, int *);
typedef struct {
    char pad0[8];
    int f08;
    char pad1[8];
    int f14;
    int f18;
    int f1C;
    char pad2[0xF4 - 0x20];
    int fF4;
    int fF8;
    int fFC;
    int f100;
    int f104;
} Func002D5B58Root;
extern int D_001A7424 __attribute__((sda));
extern char D_001A7BB4 __attribute__((sda));
extern int D_001C1220[];
extern int D_001F29A0;
extern void *D_0026CD60[];
extern void func_00287EA8(void);
extern void func_00285828(int, int, int, int);
extern void func_00285788(int, int);
extern void func_002DF190(int, int);

/* Handles a request by type (0 and 1 do nothing): the others set a state code and its parameters in
   the block at D_001F2840, change the flags of D_001A7424 or call the helpers. Types 6 to 11 store 0
   through `result` and return 1 (type 7 falls through into type 8). The dispatch reads the table
   retail already has at D_0026CD60 (fourteen code addresses, one per type; types 0 and 1 go to the
   common return); `cases` only keeps the labels alive. */
int func_PAL_002D6730(int type, int value, int *result)
{
    static void *cases[12] = {&&L3, &&L4, &&L5, &&L6, &&L7, &&L8, &&L10, &&L11, &&L9, &&L2, &&L12, &&L13};
    int ret = 0;

    if ((unsigned)type >= 14)
        goto done;
    goto *D_0026CD60[type];
L3:
    ((Func002D5B58Root *)D_001F2840)->f18 = value;
    goto done;
L4:
    func_002E5E58(4, 0, 0);
    func_00287EA8();
    D_001A7424 = (D_001A7424 | 2) & ~4;
    D_001F29A0 = 0;
    func_002B49E0(4, 1, 1, value, 0);
    goto done;
L5:
    func_002E5E58(4, 0, 0);
    D_001A7424 = (D_001A7424 | 4) & ~2;
    func_002B49E0(4, 1, 1, value, 0);
    D_001F29A0 = 1;
    goto done;
L6: {
    Func002D5B58Root *root;
    int index = value >> 16;
    if (index != 0) {
        Func002D5B58Root *first = (Func002D5B58Root *)D_001F2840;
        first->fFC = D_001C1220[index];
    }
    root = (Func002D5B58Root *)D_001F2840;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 5;
    root->fF4 = value & 0xFFFF;
    ret = 1;
    func_002DF190(0, 0x11);
    *result = 0;
    goto done;
}
L7: {
    Func002D5B58Root *root = (Func002D5B58Root *)D_001F2840;
    root->fF4 = value;
    root->f100 = root->f14;
    root->f1C = 3;
    root->f104 = root->f08;
    func_002DF190(0, 0x11);
    *result = 0;
}
L8: {
    Func002D5B58Root *root = (Func002D5B58Root *)D_001F2840;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 4;
    root->fF4 = value;
    ret = 1;
    func_002DF190(0, 0x11);
    *result = 0;
    goto done;
}
L10: {
    Func002D5B58Root *root = (Func002D5B58Root *)D_001F2840;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 6;
    root->fF4 = value;
    ret = 1;
    func_002DF190(0, 0x11);
    *result = 0;
    goto done;
}
L11: {
    Func002D5B58Root *root = (Func002D5B58Root *)D_001F2840;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 7;
    ret = 1;
    func_002DF190(0, 0x11);
    *result = 0;
    goto done;
}
L9:
    D_001A7BB4 = value;
    ret = 1;
    *result = 0;
    goto done;
L2:
    func_002DF190(2, 0x11);
    goto done;
L12:
    func_002E5E58(4, 0, 0);
    func_00285828(0, 0, 0, 0);
    func_00285788(0, 0);
    func_002B49E0(4, 1, 9, ((Func002D5B58Root *)D_001F2840)->f14, 0);
    goto done;
L13:
    func_002B49E0(4, 1, 11, ((Func002D5B58Root *)D_001F2840)->f14, 0);
done:
    return ret;
}


int func_PAL_002D6A10(char *object, int arg, int *result)
{
    typedef struct { int first, value, third; } Func002D5E38Row;
    Func002D5E38Row *rows = *(Func002D5E38Row **)(object + 0x34);
    int index = *(int *)(object + 0x40);
    return func_PAL_002D6730(arg, rows[index].value, result);
}


void func_PAL_002D6A48(char *object, int *result) {
    func_PAL_002D6730(*(short *)(object + 2), *(int *)(object + 4), result);
}



INCLUDE_ASM("asm/pal/game", func_PAL_002D6A98);

INCLUDE_ASM("asm/pal/game", func_PAL_002D6E30);

INCLUDE_ASM("asm/pal/game", func_PAL_002D74D8);



INCLUDE_ASM("asm/pal/game", func_PAL_002D7B68);


INCLUDE_ASM("asm/pal/game", func_PAL_002D82D8);
