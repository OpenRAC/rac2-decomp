#include "names.h"
extern int FastDecTimer(short *);
extern void FastVecAdd(char *, char *, char *);
extern void part_kill(void *);
extern unsigned char *g_part_tex_falling_drift_table[];
extern float g_falling_spin_param __attribute__((sda));

/* Updates a drifting particle that falls once its timer runs out, and removes it when it is too small. */
void part_update_falling_drift(char *self)
{
    char *state = self + 32;
    char *pos;

    if (FastDecTimer((short *)(self + 10)))
        *(float *)(state + 8) -= *(float *)(state + 24);
    pos = self + 16;
    FastVecAdd(pos, pos, state);
    FastVecAdd(pos, pos, *(char **)(state + 28));
    self[8] = (unsigned char)self[8] + *(unsigned char *)(state + 20);
    if ((unsigned char)self[2] == g_part_tex_falling_drift_table[0][0])
        *(float *)(self + 12) += g_falling_spin_param * 3500.000244140625f;
    if (*(float *)(self + 24) < *(float *)(state + 16))
        part_kill(self);
}

extern void FastVecScale(char *, char *, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float g_slow_fade_scale __attribute__((sda));

/* Updates a slowing particle that fades out and is removed when its timer ends. */
void part_update_slowing_fade_2(char *self)
{
    char *state = self + 32;
    float ratio;
    int colour;

    FastVecScale(state, state, g_slow_fade_scale);
    *(float *)(state + 8) -= *(float *)(state + 0x1C);
    FastVecAdd(self + 16, self + 16, state);
    if (*(short *)(self + 10) < *(int *)(state + 16)) {
        ratio = IntToFloat(*(short *)(self + 10));
        ratio = ratio / IntToFloat(*(int *)(state + 16));
        colour = (FloatToInt(ratio * 64.0f) << 24) | 0x808080;
        *(int *)(self + 4) = colour | 0x8080;
    } else {
        colour = 0x40800000;
        *(int *)(self + 4) = colour | 0x8080;
    }
    self[8] = (unsigned char)self[8] + *(unsigned char *)(state + 20);
    if (FastDecTimer((short *)(self + 10)))
        part_kill(self);
}

#include "include_asm.h"
#include "names.h"

/* The three handler slots and the string table are read through $gp, so this
 * function needs the -G8 profile of the sibling file. */
extern void (*g_menu_action_callback_a)(int) __attribute__((sda));
extern void (*g_menu_action_callback_b)(int) __attribute__((sda));
extern void (*g_menu_action_callback_c)(int) __attribute__((sda));
extern char g_menu_request_screen_data[];
extern int menu_send_request(int, char *);

#include "include_asm.h"

/*
 * The game's global state: the mode 0 case copies one of its fields into another.
 * The struct's own address is the one the retail code forms (lui/addiu) and the two
 * fields are the offsets it uses from it.
 */
typedef struct {
    char reserved_000[0x1248];
    int value_1248;
    char reserved_124C[0x107C];
    int value_22C8;
} GameState_189E20;

extern GameState_189E20 g_hero_state;

/* The menu entries the seven cases hand to func_002D5E70, in the small data area. */
extern int g_menu_action_target_0 __attribute__((sda));
extern int g_menu_action_target_1 __attribute__((sda));
extern int g_menu_action_target_2 __attribute__((sda));
extern int g_menu_action_target_3 __attribute__((sda));
extern int g_menu_action_target_4 __attribute__((sda));
extern int g_menu_action_target_5 __attribute__((sda));
extern int g_menu_action_target_6 __attribute__((sda));

extern int menu_process_entry_request(char *object, int *result);

/* Mode dispatcher: two handler slots are called, one mode names a string. */
/* Runs the action for a menu mode, such as calling a stored handler. */
int menu_handle_mode_action(int mode)
{
    int result = 0;

    switch (mode) {
    case 0:
        result = 1;
        break;
    case 1:
        if (g_menu_action_callback_a)
            g_menu_action_callback_a(0);
        result = 1;
        break;
    case 2:
        if (g_menu_action_callback_b)
            g_menu_action_callback_b(0);
        result = 1;
        break;
    case 3:
        result = menu_send_request(3, g_menu_request_screen_data);
        break;
    case 4:
        if (g_menu_action_callback_c)
            g_menu_action_callback_c(0);
        result = 1;
        break;
    }
    return result;
}

/* Dispatches on the current menu source. D_00138180's flags word is reached
 * absolutely (the object is large); D_001AB910 is small data and volatile:
 * retail rereads it for every test, including one whose value it discards. */
typedef struct {
    int mode, pad4, value;
    int padC[2];
    char *source;
    char *destination;
    int state;
} MenuState_2CBAE0;
typedef struct { char pad[0x1C4]; int flags; } InputState_2CBAE0;
extern MenuState_2CBAE0 g_pause_menu_state;
extern InputState_2CBAE0 g_pad_state;
extern char g_menu_page_pause[];
extern char g_pause_page_d[];
extern char g_pause_page_c[];
extern char g_pause_page_b[];
extern char g_pause_page_a[];
extern char g_menu_page_source_alt[];
extern volatile int g_pause_menu_busy_flag __attribute__((sda));
extern int (*g_menu_page_input_handlers[])(int);
extern void func_0029CE38(void);
extern int func_0029C290(int);
extern int DrawMapScreen(int);
extern int func_0029C300(int);

/* Checks the current menu page and reacts to button presses on it. */
int menu_update_page_input(void)
{
    int result = 0;

    if (g_pause_menu_state.source == g_menu_page_pause) {
        if (g_pad_state.flags & 0x910) {
            g_pause_menu_state.state = g_pause_menu_state.value == 4 ? 2 : 1;
            result = 1;
        } else if (g_menu_page_input_handlers[0](g_pad_state.flags) >= 0) {
            result = 1;
        }
    } else if (g_pause_menu_state.source == g_pause_page_d) {
        func_0029CE38();
    } else if (g_pause_menu_state.source == g_pause_page_c && !g_pause_menu_busy_flag) {
        func_0029C290(0);
    } else if (g_pause_menu_state.source == g_pause_page_b && !g_pause_menu_busy_flag) {
        if (DrawMapScreen(0))
            g_pause_menu_state.state = g_pause_menu_state.value == 4 ? 2 : 1;
        func_0029C300(g_pad_state.flags);
        result = g_pause_menu_state.destination != g_pause_page_c;
    } else if ((g_pause_menu_state.source == g_pause_page_a && !g_pause_menu_busy_flag)
               || (g_pause_menu_state.source == g_menu_page_source_alt && !g_pause_menu_busy_flag)) {
        /* nothing: only the tests remain */
    }
    return result;
}

/* Once the menu state has counted ten frames: the fourteen children of its object
 * get their callbacks, each changed choice is saved (0x77 for none), the value is
 * copied to D_001A72D4, texture group 0 is uploaded and groups 2, 3 and 4 (the
 * last two only when sized) are undone before the next state is set. */
typedef struct {
    int state;
    int field4;
    char pad08[0xC];
    char *object;
    char pad18[0xC];
    int mode;
    int value;
    char pad2C[0x14];
    int choices[4];
    char pad50[0xD0];
    int frames;
} MenuState_2CA5D0;
typedef struct { char pad[0x22C8]; int choices[4]; } SavedChoices_2CA5D0;
typedef struct { char pad[0x10]; unsigned int flags; } Flags_2CA5D0;
typedef struct { char pad[0xEC]; char *children[14]; } CallbackGroup_2CA5D0;
typedef struct {
    char pad[0x14];
    int a[8];
    int b[16];
    int c[8];
} GroupTable_2CA5D0;

extern char g_collision_hit[];
extern int g_menu_choice_table[] __attribute__((sda));
extern GroupTable_2CA5D0 *g_hud_group_size_table;
extern int g_vram_frame_base __attribute__((sda));
extern void gfx_wait_for_dma_status_bits(int);
extern void gfx_reset_packet_buffer(void);
extern void Hud_SendResidentBank(int, int, int);
extern void hud_unlink_bank_group(int);
extern void level_forward_value_b(int);
extern void level_forward_value(int);
extern void SubmitBufferedDmaChain(void);

/* Closes the menu after a short wait and saves any changed choices. */
void menu_close_and_save_choices(void)
{
    int i, j;

    if (((MenuState_2CA5D0 *)&g_pause_menu_state)->frames < 10)
        return;
    gfx_wait_for_dma_status_bits(1);
    gfx_reset_packet_buffer();
    if (((MenuState_2CA5D0 *)&g_pause_menu_state)->object) {
        for (i = 0; i < 14; i++) {
            char *obj = ((CallbackGroup_2CA5D0 *)((MenuState_2CA5D0 *)&g_pause_menu_state)->object)->children[i];
            if (obj && *(void (**)(char *, int))(obj + 12))
                (*(void (**)(char *, int))(obj + 12))(obj, 0);
        }
        ((MenuState_2CA5D0 *)&g_pause_menu_state)->object = 0;
    }
    for (j = 0; j < 4; j++) {
        int old = g_menu_choice_table[j];
        int selected = ((MenuState_2CA5D0 *)&g_pause_menu_state)->choices[j];
        if (old != selected)
            ((SavedChoices_2CA5D0 *)&g_hero_state)->choices[j] = selected ? selected : 0x77;
    }
    g_vram_frame_base = ((MenuState_2CA5D0 *)&g_pause_menu_state)->value;
    Hud_SendResidentBank(0, g_hud_group_size_table->c[0], 0);
    hud_unlink_bank_group(2);
    if (g_hud_group_size_table->c[3])
        hud_unlink_bank_group(3);
    if (g_hud_group_size_table->c[4])
        hud_unlink_bank_group(4);
    level_forward_value_b(360);
    level_forward_value(180);
    ((MenuState_2CA5D0 *)&g_pause_menu_state)->state = 5;
    ((MenuState_2CA5D0 *)&g_pause_menu_state)->field4 = 0;
    ((MenuState_2CA5D0 *)&g_pause_menu_state)->mode = 2;
    ((Flags_2CA5D0 *)g_collision_hit)->flags &= 0x7FFFFFFF;
    SubmitBufferedDmaChain();
    gfx_wait_for_dma_status_bits(1);
}
