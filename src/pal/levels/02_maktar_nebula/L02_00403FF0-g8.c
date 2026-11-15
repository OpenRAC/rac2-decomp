#include "include_asm.h"
#include "names.h"

extern void arena_draw_menu_help_prompts(char *, int);
extern int GetLocalizedString(int);
extern long long GetEffectTextureDescriptor(int);
extern void FontPrintScaled(float, float, long long, char *, float, int, long long, char *);
extern void FontSetWindow(char *, int, int, int, int, int, int, int, int);
extern unsigned int func_001157AC(char *);
extern void text_draw_window_large(char *, long long, char *, int);
extern void text_draw_window_small(char *, long long, char *, int);
extern int sprintf(char *, char *, ...);
extern int arena_get_challenge_save_index(int);
extern unsigned char D_001395B8[0x100];
extern unsigned char D_PAL_001A7C3C;
extern int D_PAL_L02_001B14D0[2] __attribute__((sda));
extern float D_PAL_L02_001B14C8 __attribute__((sda));
extern int D_PAL_L02_001B14CC __attribute__((sda));
extern int D_PAL_L02_001B14E8 __attribute__((sda));
extern int D_PAL_L02_001B14EC __attribute__((sda));
extern int D_PAL_L02_001B14F0 __attribute__((sda));
extern int D_PAL_L02_001B14F4 __attribute__((sda));
extern int D_PAL_L02_001B14F8 __attribute__((sda));
extern int D_PAL_L02_001B14FC __attribute__((sda));
extern int D_PAL_L02_001B1500 __attribute__((sda));
extern int D_PAL_L02_001B1508 __attribute__((sda));
extern int D_PAL_L02_001B1518 __attribute__((sda));
extern int D_PAL_L02_001B150C;
extern int D_PAL_L02_001B1510;
extern int D_PAL_L02_001B1514;
extern float D_PAL_L02_001B3EA4;
extern int D_PAL_L02_001B3EA0;
extern char D_PAL_L02_001B1258[];
extern char D_PAL_L02_0028E790[];

static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_PAL_L02_001B3EA0;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* func_PAL_L02_00403FF0, the PAL copy of func_L02_003FF6E8 (src/levels/02_maktar_nebula/
   L02_003FF6E8-g8.c) with this release's data and text ids; the first x is taken per language
   from D_PAL_L02_001B14D0. Its data is named D_PAL_L02_<PAL address>: several D_L02_ spellings
   of these addresses already name other data in functions linked into this level. */
void func_PAL_L02_00403FF0(char *a0) {
    char buf1[0x20];
    char buf2[0x70];
    char *state;
    char *text;
    char *msg;
    float x, s, half;
    int r0, r1, r2, r3, one;

    arena_draw_menu_help_prompts(a0, 0);
    half = 0.5f;
    state = *(char **)(a0 + 0x68);
    text = (char *)GetLocalizedString(0xE6A);
    one = 1;
    s = D_PAL_L02_001B3EA4;
    x = (float)D_PAL_L02_001B14D0[D_PAL_001A7C3C];
    r0 = scaled_coord(D_PAL_L02_001B14E8, s, half, one);
    FontPrintScaled(x, (float)r0, D_PAL_L02_001B14CC, text, D_PAL_L02_001B14C8, -1,
                  GetEffectTextureDescriptor(1), D_PAL_L02_0028E790);
    s = D_PAL_L02_001B3EA4;
    r1 = scaled_coord(D_PAL_L02_001B1508, s, half, one);
    r2 = scaled_coord(D_PAL_L02_001B150C, s, half, one);
    r3 = scaled_coord(D_PAL_L02_001B14F4, s, half, one);
    FontSetWindow(buf1, r1, r2, D_PAL_L02_001B1510, D_PAL_L02_001B1514, D_PAL_L02_001B14F0, r3,
                  D_PAL_L02_001B1518, 3);
    if (*(short *)(state + 0x118) == 0 && D_001395B8[arena_get_challenge_save_index(0)] < 2) {
        text = (char *)GetLocalizedString(0xE6B);
        text_draw_window_large(buf1, D_PAL_L02_001B14EC, text, func_001157AC(text));
    } else {
        text = (char *)GetLocalizedString(0xE87);
        msg = (char *)GetLocalizedString(0xE83);
        sprintf(buf2, D_PAL_L02_001B1258, text, *(int *)(state + 0x110), msg);
        text_draw_window_large(buf1, D_PAL_L02_001B14EC, buf2, func_001157AC(buf2));
    }
    text = (char *)GetLocalizedString(0xE6C);
    {
        float half = 0.5f;
        int one = 1;

        s = D_PAL_L02_001B3EA4;
        r1 = scaled_coord(D_PAL_L02_001B1508, s, half, one);
        r2 = scaled_coord(D_PAL_L02_001B150C, s, half, one);
        r3 = scaled_coord(D_PAL_L02_001B1500, s, half, one);
        FontSetWindow(buf1, r1, r2, D_PAL_L02_001B1510, D_PAL_L02_001B1514, D_PAL_L02_001B14FC, r3,
                      D_PAL_L02_001B1518, 3);
    }
    text_draw_window_small(buf1, D_PAL_L02_001B14F8, text, func_001157AC(text));
}

extern void moby_set_state(char *, int, int);
extern char *D_L02_001B1190[] __attribute__((sda));
typedef unsigned char u8;
typedef short s16;
typedef int s32;
extern char *D_L02_001B1190[2] __attribute__((sda));
extern s32 D_L02_001B35B8[] __attribute__((sda));
extern s32 moby_is_state_six(char *);
extern s32 moby_is_state_one_cleared_vars(char *);
extern s32 math_random_int_below(s32);
extern s32 moby_has_free_child_slot_state2(char *);
extern s32 arena_is_entity_far_from_hero(char *);
extern unsigned char D_001395B8[0x100];
extern int arena_get_challenge_save_index(int);
extern int arena_start_announcer_message(char *, int);
extern s32 g_frame_l02_counter;
extern s32 math_random_int_range(s32, s32);
extern s32 D_0018C2EC __attribute__((nosda));
extern s32 arena_start_announcer_message(char *, s32);
extern s32 D_0018C0B4 __attribute__((nosda));
extern u8 D_001395B8[];
extern u8 g_item_slot_to_record[];
typedef struct {
    char pad0[4];
    u8 f4;
    char pad1[0xDB];
} L02_003FF9A0_Rec;
extern L02_003FF9A0_Rec D_L02_00264A70[];
extern void func_PAL_L00_002C4480(s32, s32);
extern s32 PadPressedWithin(s32, s32, s32 *);
extern s32 arena_get_challenge_save_index(s32);
extern s32 flag_is_byte_set(void);
extern void func_PAL_L02_004011D8(char *);
extern void func_PAL_L02_00403FF0(char *);
extern void gfx_add_draw_callback_first(void *, void *);
extern const s32 D_L02_001B1524 __attribute__((sda));
extern s32 D_L02_001B1530 __attribute__((sda));
extern s32 D_001A7A00;
extern s32 math_fast_float_d(void *);

/* Calls func_PAL_L00_002C4480(0x6F, 1) unless D_0018C0B4 already is 0x6F.  When the input test
   func_L00_0032EF10(0x40, 0x3C, 0) holds, the object changes state to 7 and its selection (state
   half-word 0x118) moves to the next entry of the table at D_L02_001B1190 that is usable: the flag
   of D_001395B8 at the index func_L02_003F9B70 gives for the entry's word at +8 is set, entries from
   12 on also pass func_00288D58, and entries 7 and 8 need the byte at +4 of the record of
   D_L02_00264A70 that D_00139568[0x1E] (0x2A) names.  The pick is kept in the state and in
   D_001395B8[0x3C].  Otherwise, when func_L00_0032EF10(0x10, 0x3C, 0) holds, func_PAL_L02_004011D8
   runs; if neither test holds the callback func_PAL_L02_00403FF0 is registered for the object. */
void func_PAL_L02_004042C0(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    s32 i;
    L02_003FF9A0_Rec *r;

    if (D_0018C0B4 != 0x6F)
        func_PAL_L00_002C4480(0x6F, 1);
    if (PadPressedWithin(0x40, 0x32, 0) != 0) {
        moby_set_state(a0, 7, -1);
        for (i = *(s16 *)(state + 0x118) + 1; i < 0xE; i++) {
            if (D_001395B8[arena_get_challenge_save_index(*(s32 *)(D_L02_001B1190[i] + 8))] == 0)
                continue;
            if (i >= 0xC && flag_is_byte_set() == 0)
                continue;
            if (i == 7) {
                r = &D_L02_00264A70[g_item_slot_to_record[0x1E]];
                if (r->f4 == 0)
                    continue;
            }
            if (i == 8) {
                r = &D_L02_00264A70[g_item_slot_to_record[0x2A]];
                if (r->f4 == 0)
                    continue;
            }
            *(s16 *)(state + 0x118) = i;
            D_001395B8[0x3C] = *(u8 *)(state + 0x118);
            return;
        }
    } else if (PadPressedWithin(0x10, 0x32, 0) != 0) {
        func_PAL_L02_004011D8(a0);
    } else {
        gfx_add_draw_callback_first(func_PAL_L02_00403FF0, a0);
    }
}
