#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;
extern u8 D_00189E20_1[];
typedef struct {
    u8 pad0[0x98];
    f32 f98;
    u8 pad1[0x1A0 - 0x9C];
    f32 f1A0;
    f32 f1A4;
    f32 f1A8;
    u8 pad2[0x1B0 - 0x1AC];
    f32 f1B0;
    f32 f1B4;
    u8 pad3[0x1FC - 0x1B8];
    short a;
    u8 pad4[0xA70 - 0x1FE];
    f32 fA70;
    f32 fA74;
    f32 fA78;
    u8 pad4b[0x1FB0 - 0xA7C];
    f32 f1FB0;
    f32 f1FB4;
    u8 pad5[0x22C3 - 0x1FB8];
    u8 flag;
    u8 pad6[0x24F4 - 0x22C4];
    short b;
} D00189E20_Overlay;
extern D00189E20_Overlay g_hero_state;
extern void *D_L00_002A00A0[31];

/* Dispatches on the argument through the level's table: the five listed cases write
 * 0x46 at +0x1FC and 3 at +0x24F4 of the resident block, the other twenty-six and every
 * argument out of the range only return. */
void hero_start_timed_state_for_mode_pal(int a0)
{
    /* Keeps the two arms alive: the addresses land in the discarded .data. */
    static void *cases[31] = {
        &&arm, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&arm, &&arm, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&ret, &&arm, &&arm
    };

    if ((unsigned int)(a0 - 14) < 31) {
        goto *D_L00_002A00A0[a0 - 14];
    } else {
        goto ret;
    }
arm:
    g_hero_state.b = 3;
    g_hero_state.a = 0x3A;
ret:
    return;
}

extern void UpdateHeroSlotCallbacks(void);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int g_ring_animation_counter[] __attribute__((sda)), g_frame_l00_counter[] __attribute__((sda));
extern void ApplyHeroEquipmentRequest_pal(int);
extern int g_ring_animation_counter[] __attribute__((sda));

/* Per-frame pass over the seven 80-byte slots at +0x1220: an empty slot is released; in
 * state 2 a slot counts a tick, is released and, for a flagged entry whose animation set
 * allows it, starts animation 1; in state 3 it counts a byte tick and slots 0 and 1 (or a
 * flagged entry) are reinstalled with the shared value plus 2.  The entry's update
 * callback then runs, except for slot 6, a 253/254 sentinel entry, or slot 0 while the
 * block's word at +0x1500 is set and its mode at +0x1248 is not 10. */
void UpdateHeroSlotCallbacks_pal(void)
{
    int i;

    for (i = 0; i < 7; i++) {
        u8 *base = D_00189E20_1;
        u8 *slot = base + i * 80;
        u8 *entry = *(u8 **)(slot + 0x1220);
        void (*callback)(char *);

        if (entry != 0) {
            switch (*(int *)(slot + 0x1244)) {
            case 2:
                ++*(int *)(slot + 0x1240);
                ApplyHeroEquipmentRequest_pal(i);
                if ((entry[0x60] & 2) && entry[0x43] == 0
                    && (*(u8 **)(entry + 0x24))[0xC] >= 2)
                    func_PAL_002A7E68(entry, 1, 0, 2);
                break;
            case 3:
                ++slot[0x123B];
                if ((entry[0x60] & 2) || i == 1 || i == 0)
                    hero_release_item_slot(i, g_ring_animation_counter[0] + 2);
                break;
            }
            {
                u8 *block = D_00189E20_1;

                if (*(int *)(block + 0x1500) != 0 && i == 0
                    && *(int *)(block + 0x1248) != 10)
                    continue;
            }
            if (entry != 0 && entry[0x20] != 254 && entry[0x20] != 253 && i != 6) {
                callback = *(void (**)(char *))(entry + 0x64);
                if (callback != 0)
                    callback((char *)entry);
            }
        } else {
            ApplyHeroEquipmentRequest_pal(i);
        }
    }
}

extern void cancel_hero_item_animation_pal(void);
extern void UpdateHeroSlotCallbacks_pal(void);
extern int hud_set_slot_contents(int, int, char *, char *, char *, int, int);
extern void level_release_slot_list(char *);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_tracked_slots(void);
extern void attachment_reset_all(void);
extern void func_PAL_L00_002B3210(void);
extern void hero_clear_queued_anim(void);
extern void func_002A677C(char *);
extern int func_PAL_L00_002C4480(int, int);
extern int level_run_slot_callback(int);
extern int g_pad_pressed_flags[];
extern char g_str_timed_state_text_a[];
extern char g_str_timed_state_text_b[];
extern char g_str_timed_state_text_c[];
extern int g_pad_pressed_flags[];

/* Reset the hero update state, install the requested mode and object, and update the mode-one counters. */
void SetHeroMode_pal(int mode, int value, char *object)
{
    char *p;
    char *current;
    int count;

    cancel_hero_item_animation_pal();
    p = (char *)D_00189E20_1;
    p[0x22B6] = 1;
    UpdateHeroSlotCallbacks_pal();
    *(int *)(p + 0x2290) = *(int *)(p + 0xC18);
    level_release_slot_list(p + 0x18E0);
    level_release_slot_list(p + 0x1A30);
    current = *(char **)(p + 0x2290);
    *(int *)(current + 0x9C) = -1;
    if (mode != 4 || (unsigned char)p[0x22B4] != mode)
        hero_set_objects_flag_bit();
    hero_clear_tracked_slots();
    attachment_reset_all();
    {
        char *q = (char *)D_00189E20_1;

        q[0x22B4] = (char)mode;
        *(int *)(q + 0xC14) = (int)object;
        *(int *)(q + 0x2290) = (int)object;
        if ((unsigned char)mode == 1 && (g_pad_pressed_flags[0] & 0x10) != 0) {
            hud_set_slot_contents(0x23, 0, g_str_timed_state_text_a,
                             g_str_timed_state_text_b, g_str_timed_state_text_c, 0, 0);
            level_run_slot_callback(3);
        }
        {
            char *r = (char *)D_00189E20_1;

            func_PAL_L00_002B3210();
            *(float *)(r + 0x250) = *(float *)(r + 0x258);
            *(float *)(r + 0x254) = *(float *)(r + 0x25C);
            *(unsigned short *)(*(char **)(r + 0x2290) + 0x34) |= 6;
            *(float *)(r + 0xC24) = *(float *)(r + 0xC20) = 1.0f;
            hero_clear_queued_anim();
            func_002A677C(*(char **)(r + 0x2290));
            *(short *)(r + 0x24F2) = (short)value;
            if (mode == 1) {
                *(short *)(r + 0x24D4) = *(short *)(r + 0x24CC);
                count = *(int *)(r + 0x24D0);
                *(int *)(r + 0x24CC) = count;
                if (count >= 5)
                    *(int *)(r + 0x24CC) = 4;
            }
            func_PAL_L00_002C4480(value, 2);
        }
    }
}
