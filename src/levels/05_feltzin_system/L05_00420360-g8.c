#include "common.h"

/* func_L05_00420360: draws a Feltzin System HUD panel: two sprites, the counter line, a wrapped text
   box, the count line (its own text when the count is zero) and two option labels. The same code as
   func_L10_004239A0 and func_L15_00430168, with this level's data.

   Every sprite and box label y goes through label_y, the HUD label idiom (see its comment). Its
   tests have no effect on the result and leave no instruction, but retail shows them: after each y
   conversion retail ends a block, and the display-mode compare holds the 1 that the next real
   screen_coord mode test reads. The box text goes to func_L05_00303000, which returns the height
   used. */

extern s32 g_screen_width MACRO_ADDR;
extern u8 g_extras_unlocked_flag MACRO_ADDR;
extern u8 *g_feltzin_mission_data MACRO_ADDR;
extern f32 g_screen_l05_scale;
extern s32 g_label_mode MACRO_ADDR;
extern s32 g_feltzin_mission MACRO_ADDR;
extern s32 g_feltzin_selected_entry __attribute__((sda));
extern s32 g_feltzin_challenge_data[] SDATA(D_L05_001B1350);
extern s32 g_feltzin_reward_table[][3] SDATA(D_L05_001B13F8);

extern f32 IntToFloat(s32);
extern s32 FloatToInt(f32);
extern void *table_find_by_id(void *, s32);
extern void gfx_draw_scaled_object(void *, f32, f32, s32, f32, f32);
extern char *GetLocalizedString(s32);
extern s32 sprintf(char *, char *, ...);
extern s32 func_001157AC(char *);
extern s32 text_draw_centered_medium(s32, s32, u64, char *, s32);
extern s32 text_print_wrapped_default(s32, s32, s32, s32, u64, u8 *, s32);
extern void text_draw_medium(s32, s32, u64, char *, s32);

/* The shape of scaled_screen_coord in src/game/002D3390.c, with this level's display scale. */
static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * g_screen_l05_scale + 0.5f;

    if (mode == 1)
        return (s32)(scaled + offset);
    return (s32)scaled;
}

/* label_y, the HUD label idiom for text and sprite label y coordinates (accepted 7 November 2026; one
   shared definition, `active` the literal 1 at every call). Its tests do not change the result: flow
   deletes their stores and jump2 their jumps, but only after allocation and both scheduling passes,
   which see the block they end. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_label_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

s32 hud_draw_feltzin_mission_reward(void) {
    char buf[128];
    f32 center = IntToFloat(g_screen_width) * 0.5f;
    void *sprite;
    char *text;
    s32 x, y, count, index;

    if (g_feltzin_mission_data != 0) {
        sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x45);
        gfx_draw_scaled_object(sprite, center, (f32)label_y(sprite, 200.0f, g_screen_l05_scale, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
        sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x44);
        gfx_draw_scaled_object(sprite, center, (f32)label_y(sprite, 200.0f, g_screen_l05_scale, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
        sprintf(buf, GetLocalizedString(0x2F72), g_feltzin_selected_entry + 1);
        text = GetLocalizedString(0x2F93);
        x = FloatToInt(center);
        y = screen_coord(g_label_mode, 46.0f, -2.0f);
        text_draw_centered_medium(x, y, 0x80F0F0F0, text, func_001157AC(text));
        text = GetLocalizedString(0x31CB);
        {
            s32 ty = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
            text_print_wrapped_default(117, ty, 280, 400, 0x80F0F0F0, (u8 *)text, func_001157AC(text));
        }
        index = g_feltzin_challenge_data[g_feltzin_mission] - 1;
        if (index >= 3)
            index = 2;
        count = g_feltzin_reward_table[g_feltzin_mission][index];
        if (g_extras_unlocked_flag != 0)
            count *= 10;
        text = buf;
        if (count == 0)
            sprintf(buf, GetLocalizedString(0x11F5));
        else
            sprintf(buf, GetLocalizedString(0x2FC6), count);
        {
            s32 ty = label_y(text, 210.0f, g_screen_l05_scale, 0.5f, 1);
            text_print_wrapped_default(117, ty, 280, 400, 0x80F0F0F0, (u8 *)text, func_001157AC(text));
        }
        y = screen_coord(g_label_mode, 294.0f, 3.0f);
        text_draw_medium(117, y, 0x80F0F0F0, GetLocalizedString(0x31CC), -1);
        y = screen_coord(g_label_mode, 294.0f, 3.0f);
        text_draw_medium(274, y, 0x80F0F0F0, GetLocalizedString(0x31CD), -1);
    }
    return 1;
}

/* Built with -G8: the level's reset flag is reached through $gp in retail (level 5's $gp
   base is 0x1AEFF0, so `sw $zero,0x23F4($gp)` is 0x001B13E4). */



extern s32 func_003062A0(u8 *a0);

extern void func_002FF9F8(s32 a0);

extern s32 func_0030CBA8(s32 a0);

extern void thrown_object_update(s32 a0, s32 a1);

extern void func_0037B210(void);

extern void feltzin_challenge_reset(u8 *a0);

extern s32 g_feltzin_failure_flag __attribute__((sda));

/* Either shuts the level's spawn state down and marks the reset flag, or asks the shared
   gadget lookup for one of the two fixed item strings and forwards it to the dispatcher. */
void feltzin_mission_handle_failure(u8 *actor, s32 mission)
{
    u8 *vars = *(u8 **)(actor + 0x68);

    if (func_003062A0(vars + 0x48) == 0) {
        if (mission == 1)
            thrown_object_update(func_0030CBA8(0x31C9), -1);
        else if (mission == 3)
            thrown_object_update(func_0030CBA8(0x31DE), -1);
    } else {
        /* The two stores are written against the retail order: 0x48 first. */
        *(s32 *)(vars + 0x48) = 0x96;
        *(s32 *)(vars + 0x44) = 0x1C20;
        func_002FF9F8(0x1E);
        feltzin_challenge_reset(actor);
        func_0037B210();
        g_feltzin_failure_flag = 0;
    }
}
