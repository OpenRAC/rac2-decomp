#include "include_asm.h"

INCLUDE_ASM("asm/us2/game", func_US2_002CB720);

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* func_US2_002CB720, the USA v2.00 copy of func_002CA790: the same C, with a
   0x30-byte copy, two more calls and a skip on field_1F4. */
typedef struct {
    char reserved_000[0x1C];
    int field_01C;
    int field_020;
    char reserved_024[0x2C];
    TI128 field_050;
    TI128 field_060;
    char reserved_070[0x60];
    int field_0D0;
    char reserved_0D4[0x7];
    unsigned char field_0DB;
    char reserved_0DC[0x1C];
    float field_0F8;
    char reserved_0FC[0x18];
    int field_114;
    int field_118;
    int field_11C;
    char reserved_120[0xD4];
    int field_1F4;
} GameState_2CB720;

extern char D_001F2840[];
extern char D_001B5340[];
extern float D_001B90F0[];

extern void func_002FC138(void);
extern void func_00282AB0(void *, void *, int);
extern void func_0027AB40(void);
extern void func_00279D18(void);
extern void func_0028B338(int);
extern void func_00279FF0(void);
extern void func_0027D330(int);
extern void func_00132B28(int);
extern int func_00288D30(void);
extern void func_002B7320(void);
extern int func_00132028(void);
extern void func_002E4AC8(void);
extern s16 func_002B7CE0(int);
extern void func_002B8518(void);
