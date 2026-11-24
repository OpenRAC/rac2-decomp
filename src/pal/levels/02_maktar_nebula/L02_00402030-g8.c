#include "names.h"
/* func_PAL_L02_00402030, the PAL copy of func_L02_003FD8B8: the same C, where func_L00_002C42E0
   becomes func_PAL_L00_002C4480; 15 becomes 12; func_L02_003FCA80 becomes func_PAL_L02_004011D8;
   60 becomes 50. */
#include "common.h"

extern int mode_get_stack_top(void);
extern int flag_is_byte_set(void);
extern int arena_get_challenge_save_index(unsigned int);
extern int hero_l00_set_move_state_pal(int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern int FastDecTimer(short *);
extern void moby_set_state(u8 *, int, int);
extern void cam_set_mode_state(int);
extern void hero_start_loader_state(int);
extern int request_begin_slot(int, int, int, int, u8 *);
extern void arena_cancel_challenge_menu_pal(u8 *);
extern void pad_clear_port_state(void);
extern int PadPressedWithin(unsigned int, int, int *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void arena_draw_menu_panel(void *);
extern int g_game_mode[3], g_challenge_pad_flags[3];

typedef struct {
    u8 pad[0x1a0];
    int field1a0, field1a4;
    u8 gap[24];
    int field1c0, field1c4;
} InputView;
extern unsigned char g_pad_state[];
extern unsigned char g_item_slot_to_record[], g_game_flag_table[];
typedef struct {
    u8 pad[4];
    u8 enabled;
    u8 rest[0xdb];
} MenuRecord;
extern unsigned char g_material_l02_table[];
#define MENU ((MenuRecord *)D_L02_00264A70)
extern int g_arena_challenge_table_2 __attribute__((sda));
#define TABLE ((int **)&D_L02_001B1190)
#define H(o) (*(short *)(state+(o)))

/* Handles the challenge menu input: up/down moves the selection to the next usable entry, cross
   starts the challenge, triangle cancels, and the four-button cheat combination switches state.
   Otherwise draws the menu panel (PAL: 50 Hz timings). */
void arena_update_challenge_menu_pal(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    int i, found;
    InputView *input;
    if (mode_get_stack_top()==5) return;
    if (g_game_mode[0]!=0x6f) hero_l00_set_move_state_pal(0x6f,1);
    if (H(0x11a)==0) {
        if ((((InputView *)g_pad_state)->field1c4&0x2000) && H(0x118)<13) {
            for (i=H(0x118)+1;i<14;i++) {
                if (!g_game_flag_table[arena_get_challenge_save_index(TABLE[i][2])]) continue;
                if (i>=12 && !flag_is_byte_set()) continue;
                if (i==7) {
                    MenuRecord *choice = (MenuRecord *)(g_material_l02_table + g_item_slot_to_record[0x1e] * 0xe0);
                    if (!choice->enabled) continue;
                }
                if (i==8) {
                    MenuRecord *choice = (MenuRecord *)(g_material_l02_table + g_item_slot_to_record[0x2a] * 0xe0);
                    if (!choice->enabled) continue;
                }
                H(0x118)=i;
                H(0x11a)=12;
                H(0x128)=12;
                snd_play_from_global_bank(3,0,0);
                break;
            }
        } else if ((((InputView *)g_pad_state)->field1c4&0x8000) && H(0x118)>0) {
            found=0;
            if (H(0x118)==1) {
                H(0x118)=0;
                found=1;
                snd_play_from_global_bank(3,0,0);
            } else for (i=H(0x118)-1;i>=0;i--) {
                if (!g_game_flag_table[arena_get_challenge_save_index(TABLE[i][2])]) continue;
                if (i>=12 && !flag_is_byte_set()) continue;
                if (i==7) {
                    MenuRecord *choice = (MenuRecord *)(g_material_l02_table + g_item_slot_to_record[0x1e] * 0xe0);
                    if (!choice->enabled) continue;
                }
                if (i==8) {
                    MenuRecord *choice = (MenuRecord *)(g_material_l02_table + g_item_slot_to_record[0x2a] * 0xe0);
                    if (!choice->enabled) continue;
                }
                H(0x118)=i;
                found=1;
                break;
            }
            if (!found) H(0x118)=0;
            H(0x11a)=12;
            H(0x126)=12;
            snd_play_from_global_bank(3,0,0);
        }
    } else FastDecTimer((short *)(state+0x11a));
    input = (InputView *)g_pad_state;
    if (input->field1c4&0x40) {
        if (H(0x118)==0) {
            H(0x120)=*(unsigned short *)(state+0x118);
            H(0x122)=0;
            g_game_flag_table[0x3c]=state[0x118];
            moby_set_state(object,8,-1);
            cam_set_mode_state(2);
            hero_start_loader_state(0);
            snd_play_from_global_bank(4,0,0);
            input->field1c4=0;
            goto clear_buttons;
        } else {
            if (!g_game_flag_table[arena_get_challenge_save_index(TABLE[H(0x118)][2])]) return;
            if (H(0x118)>=12 && !flag_is_byte_set()) return;
            if (H(0x118)==7 && !MENU[g_item_slot_to_record[0x1e]].enabled) return;
            if (H(0x118)==8 && !MENU[g_item_slot_to_record[0x2a]].enabled) return;
        }
        H(0x120)=*(unsigned short *)(state+0x118);
        H(0x122)=0;
        g_game_flag_table[0x3c]=state[0x118];
        moby_set_state(object,8,-1);
        cam_set_mode_state(2);
        hero_start_loader_state(0);
        snd_play_from_global_bank(4,0,0);
        input->field1c4=0;
        goto clear_buttons;
    } else if (input->field1c4&0x80) {
        request_begin_slot(5,1,0,0,0);
        return;
    } else if (input->field1c4&0x10) {
        arena_cancel_challenge_menu_pal(object);
        input->field1c4=0;
clear_buttons:
        input->field1a0=0;
        input->field1c0=0;
        input->field1a4=0;
        pad_clear_port_state();
        return;
    } else if (g_challenge_pad_flags[0] &&
               PadPressedWithin(1,50,0) && PadPressedWithin(2,50,0) &&
               PadPressedWithin(4,50,0) && PadPressedWithin(8,50,0)) {
        H(0x120)=*(unsigned short *)(state+0x118);
        moby_set_state(object,5,-1);
        return;
    }
    gfx_add_draw_callback_first(arena_draw_menu_panel,object);
}
