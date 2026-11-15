#include "names.h"
/* Handles Joba class selection, confirmation, cancel and repeated directional input. */
#include "common.h"

extern int mode_get_stack_top(void);
extern int flag_is_byte_set(void);
extern int arena_get_challenge_save_index(unsigned int);
extern int hero_l00_set_action(int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern int FastDecTimer(short *);
extern void moby_set_state(u8 *, int, int);
extern void cam_set_mode_state(int);
extern void hero_start_loader_state(int);
extern int request_begin_slot(int, int, int, int, u8 *);
extern void arena_cancel_challenge_menu(u8 *);
extern void pad_clear_port_state(void);
extern int PadPressedWithin(unsigned int, int, int *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void arena_draw_menu_panel(void *);
extern int D_0018C0B4[3], D_L02_002004A4[3];

typedef struct {
    u8 pad[0x1a0];
    int field1a0, field1a4;
    u8 gap[24];
    int field1c0, field1c4;
} InputView;
extern unsigned char g_pad_state[];
extern unsigned char g_item_slot_to_record[], D_001395B8[];
typedef struct {
    u8 pad[4];
    u8 enabled;
    u8 rest[0xdb];
} MenuRecord;
extern unsigned char D_L02_00264A70[];
#define MENU ((MenuRecord *)D_L02_00264A70)
/* The class pointer table is addressed through gp. */
extern int D_L02_001B1190 __attribute__((sda));
#define TABLE ((int **)&D_L02_001B1190)
#define H(o) (*(short *)(state+(o)))

/* Handles the challenge menu: moving up and down the list, picking a challenge, and cancelling. */
void arena_update_challenge_menu(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    int i, found;
    InputView *input;
    if (mode_get_stack_top()==5) return;
    if (D_0018C0B4[0]!=0x6f) hero_l00_set_action(0x6f,1);
    if (H(0x11a)==0) {
        if ((((InputView *)g_pad_state)->field1c4&0x2000) && H(0x118)<13) {
            for (i=H(0x118)+1;i<14;i++) {
                if (!D_001395B8[arena_get_challenge_save_index(TABLE[i][2])]) continue;
                if (i>=12 && !flag_is_byte_set()) continue;
                if (i==7) {
                    MenuRecord *choice = (MenuRecord *)(D_L02_00264A70 + g_item_slot_to_record[0x1e] * 0xe0);
                    if (!choice->enabled) continue;
                }
                if (i==8) {
                    MenuRecord *choice = (MenuRecord *)(D_L02_00264A70 + g_item_slot_to_record[0x2a] * 0xe0);
                    if (!choice->enabled) continue;
                }
                H(0x118)=i;
                H(0x11a)=15;
                H(0x128)=15;
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
                if (!D_001395B8[arena_get_challenge_save_index(TABLE[i][2])]) continue;
                if (i>=12 && !flag_is_byte_set()) continue;
                if (i==7) {
                    MenuRecord *choice = (MenuRecord *)(D_L02_00264A70 + g_item_slot_to_record[0x1e] * 0xe0);
                    if (!choice->enabled) continue;
                }
                if (i==8) {
                    MenuRecord *choice = (MenuRecord *)(D_L02_00264A70 + g_item_slot_to_record[0x2a] * 0xe0);
                    if (!choice->enabled) continue;
                }
                H(0x118)=i;
                found=1;
                break;
            }
            if (!found) H(0x118)=0;
            H(0x11a)=15;
            H(0x126)=15;
            snd_play_from_global_bank(3,0,0);
        }
    } else FastDecTimer((short *)(state+0x11a));
    input = (InputView *)g_pad_state;
    if (input->field1c4&0x40) {
        if (H(0x118)==0) {
            H(0x120)=*(unsigned short *)(state+0x118);
            H(0x122)=0;
            D_001395B8[0x3c]=state[0x118];
            moby_set_state(object,8,-1);
            cam_set_mode_state(2);
            hero_start_loader_state(0);
            snd_play_from_global_bank(4,0,0);
            input->field1c4=0;
            goto clear_buttons;
        } else {
            if (!D_001395B8[arena_get_challenge_save_index(TABLE[H(0x118)][2])]) return;
            if (H(0x118)>=12 && !flag_is_byte_set()) return;
            if (H(0x118)==7 && !MENU[g_item_slot_to_record[0x1e]].enabled) return;
            if (H(0x118)==8 && !MENU[g_item_slot_to_record[0x2a]].enabled) return;
        }
        H(0x120)=*(unsigned short *)(state+0x118);
        H(0x122)=0;
        D_001395B8[0x3c]=state[0x118];
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
        arena_cancel_challenge_menu(object);
        input->field1c4=0;
clear_buttons:
        input->field1a0=0;
        input->field1c0=0;
        input->field1a4=0;
        pad_clear_port_state();
        return;
    } else if (D_L02_002004A4[0] &&
               PadPressedWithin(1,60,0) && PadPressedWithin(2,60,0) &&
               PadPressedWithin(4,60,0) && PadPressedWithin(8,60,0)) {
        H(0x120)=*(unsigned short *)(state+0x118);
        moby_set_state(object,5,-1);
        return;
    }
    gfx_add_draw_callback_first(arena_draw_menu_panel,object);
}
