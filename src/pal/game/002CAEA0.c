#include "include_asm.h"
#include "common.h"



typedef int TI128 __attribute__((mode(TI)));

/* func_PAL_002CB5D0, the PAL copy of func_002CA790: the same C, where PAL adds a
   0x30-byte copy and two calls, tests field_1F4, and func_0027D330 takes 0xD. */
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
    char reserved_1F8[0x8];
    char field_200[0x30];
} GameState_PAL_2CB5D0;

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
extern void func_PAL_002E5898(void);
extern s16 func_PAL_002B8898(int);
extern void func_002B8518(void);

void func_PAL_002CB5D0(void)
{
    GameState_PAL_2CB5D0 *s = (GameState_PAL_2CB5D0 *)(void *)D_001F2840;
    TI128 *dst;
    int mode;

    *(int *)(void *)D_001F2840 = 0;
    func_002FC138();
    dst = (TI128 *)D_001B5340;
    qcopy(dst, &s->field_050);
    qcopy(dst + 1, &s->field_060);
    func_00282AB0((char *)dst + 0x230, s->field_200, 0x30);
    *(float *)D_001B90F0 = s->field_0F8;
    func_0027AB40();
    func_00279D18();
    func_0028B338(0);
    func_00279FF0();
    mode = s->field_01C;
    s->field_11C = 0;
    s->field_114 = 0;
    s->field_020 = 0;
    s->field_118 = 0;
    if (mode == 3 || mode == 4 || mode == 6 || mode == 5) {
        func_0027D330(0xD);
    }
    if (((GameState_PAL_2CB5D0 *)(void *)D_001F2840)->field_1F4 == 0) {
        func_00132B28(0x5D);
        if (((GameState_PAL_2CB5D0 *)(void *)D_001F2840)->field_01C != 2 || func_00288D30() == 0)
            func_002B7320();
        func_00132028();
    }
    func_PAL_002E5898();
    if (((GameState_PAL_2CB5D0 *)(void *)D_001F2840)->field_0DB) {
        func_PAL_002B8898(1);
        ((GameState_PAL_2CB5D0 *)(void *)D_001F2840)->field_0DB = 0;
    }
    func_002B8518();
}
