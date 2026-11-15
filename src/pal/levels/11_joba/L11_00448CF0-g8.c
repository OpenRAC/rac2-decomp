#include "include_asm.h"

#include "common.h"
extern int mode_get_stack_top(void);
extern int flag_is_byte_set(void);
extern int arena_get_challenge_flag_index(unsigned int);
extern int func_PAL_L11_002D9038(int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern int FastDecTimer(short *);
extern void moby_set_state(u8 *, int, int);
extern void cam_set_mode_state(int);
extern void hero_start_loader_state(int);
extern int request_begin_slot(int, int, int, int, u8 *);
extern void func_PAL_L11_00447E20(u8 *);
extern void pad_clear_port_state(void);
extern int PadPressedWithin(unsigned int, int, int *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void func_PAL_L11_004495E8(void *);
extern int D_0018C0B4[3], D_L11_00200864[3];
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
extern unsigned char D_L11_00279BA0[];
#define MENU ((MenuRecord *)D_L11_00279BA0)
extern int g_arena_challenge_table __attribute__((sda));
#define TABLE ((int **)&D_L11_001B14F8)
#define H(o) (*(short *)(state+(o)))

void func_PAL_L11_00448CF0(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    int i, found;
    InputView *input;
    if (mode_get_stack_top()==5) return;
    if (D_0018C0B4[0]!=0x6f) func_PAL_L11_002D9038(0x6f,1);
    if (H(0x1ea)==0) {
        if ((((InputView *)g_pad_state)->field1c4&0x2000) && H(0x1e8)<12) {
            for (i=H(0x1e8)+1;i<13;i++) {
                if (!D_001395B8[arena_get_challenge_flag_index(TABLE[i][2])]) continue;
                if (i>=11 && !flag_is_byte_set()) continue;
                if (i==8) {
                    MenuRecord *choice = (MenuRecord *)(D_L11_00279BA0 + g_item_slot_to_record[0x1e] * 0xe0);
                    if (!choice->enabled) continue;
                }
                H(0x1e8)=i;
                H(0x1ea)=12;
                H(0x1f8)=12;
                snd_play_from_global_bank(3,0,0);
                break;
            }
        } else if ((((InputView *)g_pad_state)->field1c4&0x8000) && H(0x1e8)>0) {
            found=0;
            if (H(0x1e8)==1) {
                H(0x1e8)=0;
                found=1;
            } else for (i=H(0x1e8)-1;i>=0;i--) {
                if (!D_001395B8[arena_get_challenge_flag_index(TABLE[i][2])]) continue;
                if (i>=11 && !flag_is_byte_set()) continue;
                if (i==8) {
                    MenuRecord *choice = (MenuRecord *)(D_L11_00279BA0 + g_item_slot_to_record[0x1e] * 0xe0);
                    if (!choice->enabled) continue;
                }
                H(0x1e8)=i;
                found=1;
                break;
            }
            if (!found) H(0x1e8)=0;
            H(0x1ea)=12;
            H(0x1f6)=12;
            snd_play_from_global_bank(3,0,0);
        }
    } else FastDecTimer((short *)(state+0x1ea));
    input = (InputView *)g_pad_state;
    if (input->field1c4&0x40) {
        if (H(0x1e8)==0) {
            H(0x1f0)=*(unsigned short *)(state+0x1e8);
            H(0x1f2)=0;
            D_001395B8[0x49]=state[0x1e8];
            moby_set_state(object,8,-1);
            cam_set_mode_state(2);
            hero_start_loader_state(0);
            snd_play_from_global_bank(4,0,0);
            input->field1c4=0;
            goto clear_buttons;
        } else {
            if (!D_001395B8[arena_get_challenge_flag_index(TABLE[H(0x1e8)][2])]) return;
            if (H(0x1e8)>=11 && !flag_is_byte_set()) return;
            if (H(0x1e8)==8 && !MENU[g_item_slot_to_record[0x1e]].enabled) return;
        }
        H(0x1f0)=*(unsigned short *)(state+0x1e8);
        H(0x1f2)=0;
        D_001395B8[0x49]=state[0x1e8];
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
        func_PAL_L11_00447E20(object);
        input->field1c4=0;
clear_buttons:
        input->field1a0=0;
        input->field1c0=0;
        input->field1a4=0;
        pad_clear_port_state();
        return;
    } else if (D_L11_00200864[0] &&
               PadPressedWithin(1,50,0) && PadPressedWithin(2,50,0) &&
               PadPressedWithin(4,50,0) && PadPressedWithin(8,50,0)) {
        H(0x1f0)=*(unsigned short *)(state+0x1e8);
        moby_set_state(object,5,-1);
        return;
    }
    gfx_add_draw_callback_first(func_PAL_L11_004495E8,object);
}
