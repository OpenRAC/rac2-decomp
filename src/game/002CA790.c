#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

/* The game's global state at 0x1F2840: the mode word, the reset counters, the
   spawn table and the flags the reset touches. */
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
} GameState_2CA790;

extern char D_001F2840[];
extern char D_001B5340[];
extern float D_001B90F0[];

extern void func_002FC138(void);
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

void func_002CA790(void)
{
    GameState_2CA790 *s = (GameState_2CA790 *)(void *)D_001F2840;
    TI128 *dst;
    TI128 *src = (TI128 *)((char *)s + 0x50);
    int mode;

    *(int *)(void *)D_001F2840 = 0;
    func_002FC138();
    dst = (TI128 *)D_001B5340;
    qcopy(dst, src);
    src = (TI128 *)((char *)s + 0x60);
    qcopy(dst + 1, src);
    *(float *)D_001B90F0 = s->field_0F8;
    select_moby_context(0);
    func_00279FF0();
    mode = s->field_01C;
    s->field_11C = 0;
    s->field_114 = 0;
    s->field_020 = 0;
    s->field_118 = 0;
    if (mode == 3 || mode == 4 || mode == 6 || mode == 5) {
        FadeToBlack(0x10);
    }
    func_00132B28(0x5D);
    if (((GameState_2CA790 *)(void *)D_001F2840)->field_01C != 2 || func_00288D30() == 0)
        music_Unpause();
    snd_Pump();
    UpdateSoundVoices();
    mode = ((GameState_2CA790 *)(void *)D_001F2840)->field_0DB;
    if (mode) {
        func_002B7CE0(1);
        ((GameState_2CA790 *)(void *)D_001F2840)->field_0DB = 0;
    }
    func_002B8518();
}
