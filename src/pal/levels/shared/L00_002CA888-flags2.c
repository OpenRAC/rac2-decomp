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
extern void cancel_hero_item_animation_pal(void);
extern int hero_l00_set_move_state_pal(int a0, int a1);
extern void set_hero_animation_pal(void *, int, f32);
extern void vec_clamp_length(float *, float);

/* Tries to start the hero's grab onto the nearby object, and returns 1 when it started. */
int hero_try_start_grab_pal(void)
{
    Hero_2CAF20 *h = &g_hero_state;
    int idx;
    void *moby;

    if (h->b22B8 != 0 && h->b22BA != 0 && h->h24EC == 0) {
    idx = hero_slot_item_id(0);
    if (idx != h->f24B4) {
        cancel_hero_item_animation_pal();
        return 0;
    }
    moby = (g_weapon_l00_table + g_item_slot_to_record[idx])->moby;
    if (hero_l00_set_move_state_pal(0, 0) == 0)
        return 0;
    vec_clamp_length(h->v160, 0.030000001f);
    if (0.030000001f < h->f1B4)
        h->f1B4 = 0.030000001f;
    set_hero_animation_pal(moby, 0, 9.0f);
    if (h->fE98 != 0)
        h->fEA4 = 1;
    h->f24B0 = moby;
    return 1;
    }
    return 0;
}

extern char g_hero_button_hold_timers[];
extern char g_pad_state[];
extern int g_input_block_flag __attribute__((section(".sdata")));
extern s32 FastDecTimer(s32);
extern void level_set_flag_d_true(void);

/* Counts down the hero's button-hold timers and starts the special action when the button is pressed again in time. */
void hero_update_button_hold_timers_pal(void)
{
    char *b;
    char *o;
    u64 w;

    FastDecTimer(g_hero_button_hold_timers);
    FastDecTimer(g_hero_button_hold_timers + 2);
    b = g_hero_button_hold_timers - 0x24F8;
    if (0x37 == *(int *)(b + 0x2294))
        return;
    if (*(u8 *)(b + 0x22BC) != 0)
        return;
    if (g_input_block_flag != 0)
        return;
    o = g_pad_state;
    if (*(int *)(o + 0x1A4) & 0x10)
        *(short *)(b + 0x24F8) = 17;
    w = *(u32 *)(b + 0x24F8);
    if (w == 0)
        return;
    if (*(int *)(o + 0x1B8) & 0x10) {
        if (*(short *)(b + 0x24FA) == 0) {
            *(short *)(b + 0x24FA) = 17;
            return;
        }
        *(int *)(b + 0x2538) = 1;
        level_set_flag_d_true();
    }
}

extern int hero_pick_linked_anim_pair(int, void *, void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern char D_00189E20_36[];

/* func_L00_002CB3A8 is in the sibling file L00_002CB3A8-decider.c (its own profile). */

/* loads two object pointers from fixed data, bails out when either is null or when the first object's byte 67 differs from 1, fills two stack ints through a helper, then applies a four-argument operation to each object with those ints */
void hero_set_linked_objects_anim_pal(void)
{
    char *p = D_00189E20_36;
    void *s0;
    void *s1;
    int buf[2];

    s0 = *(void **)(p + 4880);
    s1 = *(void **)(p + 4884);

    if (s0 == 0)
        return;
    if (s1 == 0)
        return;

    if (*(unsigned char *)((char *)s0 + 67) != 1)
        return;

    if (hero_pick_linked_anim_pair(0, buf, buf + 1) == 0)
        return;

    anim_start_blended_pal(s0, buf[0], 0, 6);
    anim_start_blended_pal(s1, buf[1], 0, 6);
}
