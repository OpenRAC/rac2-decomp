#include "include_asm.h"
#include "names.h"

typedef struct {
    char reserved_000[0x1248];
    int value_1248;
    char reserved_124C[0x107C];
    int value_22C8;
} GameState_189E20;
extern GameState_189E20 g_hero_state;
typedef struct {
    int mode, pad4, value;
    int padC[2];
    char *source;
    char *destination;
    int state;
} MenuState_2CBAE0;
extern MenuState_2CBAE0 g_pause_menu_state;
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
extern void level_forward_value_b_us2(int);
extern void level_forward_value(int);
extern void SubmitBufferedDmaChain(void);

void menu_close_and_save_choices_us2(void)
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
    level_forward_value_b_us2(360);
    level_forward_value(180);
    ((MenuState_2CA5D0 *)&g_pause_menu_state)->state = 5;
    ((MenuState_2CA5D0 *)&g_pause_menu_state)->field4 = 0;
    ((MenuState_2CA5D0 *)&g_pause_menu_state)->mode = 2;
    ((Flags_2CA5D0 *)g_collision_hit)->flags &= 0x7FFFFFFF;
    SubmitBufferedDmaChain();
    gfx_wait_for_dma_status_bits(1);
}
