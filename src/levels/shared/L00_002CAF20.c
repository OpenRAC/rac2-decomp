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

extern Hero_2CAF20 g_hero_state;
extern u8 g_item_slot_to_record[];
extern Entry_2CAF20 g_weapon_l00_table[];
extern s32 hero_slot_item_id(s32);
extern void cancel_hero_item_animation(void);
extern int hero_l00_set_move_state(int a0, int a1);
extern void set_hero_animation(void *, int, f32);
extern void vec_clamp_length(float *, float);

/* Tries to start the hero's grab onto the nearby object, and returns 1 when it started. */
int hero_try_start_grab(void)
{
    Hero_2CAF20 *h = &g_hero_state;
    int idx;
    void *moby;

    if (h->b22B8 != 0 && h->b22BA != 0 && h->h24EC == 0) {
    idx = hero_slot_item_id(0);
    if (idx != h->f24B4) {
        cancel_hero_item_animation();
        return 0;
    }
    moby = (g_weapon_l00_table + g_item_slot_to_record[idx])->moby;
    if (hero_l00_set_move_state(0, 0) == 0)
        return 0;
    vec_clamp_length(h->v160, 0.0250000015f);
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
