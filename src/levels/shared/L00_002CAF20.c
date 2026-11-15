#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad0[0x160];
    f32 v160[4];
    u8 pad170[0x1B4 - 0x170];
    f32 f1B4;
    u8 pad1B8[0xE98 - 0x1B8];
    s32 fE98;
    u8 padE9C[0xEA4 - 0xE9C];
    s32 fEA4;
    u8 padEA8[0x22B8 - 0xEA8];
    u8 b22B8;
    u8 pad22B9;
    u8 b22BA;
    u8 pad22BB[0x24B0 - 0x22BB];
    void *f24B0;
    s32 f24B4;
    u8 pad24B8[0x24EC - 0x24B8];
    s16 h24EC;
} Hero_2CAF20;

typedef struct {
    u8 pad0[0x28];
    void *moby;
    u8 pad2C[0xE0 - 0x2C];
} Entry_2CAF20;

extern Hero_2CAF20 D_00189E20;
extern u8 D_00139568[];
extern Entry_2CAF20 D_L00_00262570[];
extern s32 func_L00_002ADEA0(s32);
extern void func_L00_002AF7D0(void);
extern int func_L00_002C42E0(int a0, int a1);
extern void func_L00_002D2168(void *, int, f32);
extern void func_002AC9F8(float *, float);

int func_L00_002CAF20(void)
{
    Hero_2CAF20 *h = &D_00189E20;
    int idx;
    void *moby;

    if (h->b22B8 != 0 && h->b22BA != 0 && h->h24EC == 0) {
    idx = hero_slot_item_id(0);
    if (idx != h->f24B4) {
        cancel_hero_item_animation();
        return 0;
    }
    moby = (D_L00_00262570 + D_00139568[idx])->moby;
    if (func_L00_002C42E0(0, 0) == 0)
        return 0;
    func_002AC9F8(h->v160, 0.0250000015f);
    if (0.0250000015f < h->f1B4)
        h->f1B4 = 0.0250000015f;
    set_hero_animation(moby, 0, 11.0f);
    if (h->fE98 != 0)
        h->fEA4 = 1;
    h->f24B0 = moby;
    return 1;
    }
    return 0;
}
