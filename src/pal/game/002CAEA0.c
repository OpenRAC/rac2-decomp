#include "include_asm.h"
#include "common.h"



typedef int TI128 __attribute__((mode(TI)));

/* func_PAL_002CB5D0, the PAL copy of func_002CA790: the same C, where PAL adds a
   0x30-byte copy and two calls, tests field_1F4, and func_0027D330 takes 0xD. */
typedef struct {
    char reserved_000[0x1C];
    int field_01C;
    int field_020;
    char reserved_024[0x2C];
    TI128 field_050;
    TI128 field_060;
    char reserved_070[0x60];
    int field_0D0;
    char reserved_0D4[0x7];
    unsigned char field_0DB;
    char reserved_0DC[0x1C];
    float field_0F8;
    char reserved_0FC[0x18];
    int field_114;
    int field_118;
    int field_11C;
    char reserved_120[0xD4];
    int field_1F4;
    char reserved_1F8[0x8];
    char field_200[0x30];
} GameState_PAL_2CB5D0;

extern char g_pause_menu_state[];
extern char g_camera_eye_state[];
extern float D_001B90F0[];

extern void gfx_select_packet_buffer_setup(void);
extern void mem_copy_aligned(void *, void *, int);
extern void UpdateViewContext(void);
extern void gfx_build_view_matrices(void);
extern void select_moby_context(int);
extern void gfx_apply_display_config(void);
extern void FadeToBlack(int);
extern void snd_send_cmd23(int);
extern int flag_is_word_set(void);
extern void music_Unpause(void);
extern int snd_Pump(void);
extern s32 func_PAL_002E5898(void);
extern s16 func_PAL_002B8898(int);
extern void pad_clear_port_state(void);

void func_PAL_002CB5D0(void)
{
    GameState_PAL_2CB5D0 *s = (GameState_PAL_2CB5D0 *)(void *)g_pause_menu_state;
    TI128 *dst;
    int mode;

    *(int *)(void *)g_pause_menu_state = 0;
    gfx_select_packet_buffer_setup();
    dst = (TI128 *)g_camera_eye_state;
    qcopy(dst, &s->field_050);
    qcopy(dst + 1, &s->field_060);
    mem_copy_aligned((char *)dst + 0x230, s->field_200, 0x30);
    *(float *)D_001B90F0 = s->field_0F8;
    UpdateViewContext();
    gfx_build_view_matrices();
    select_moby_context(0);
    gfx_apply_display_config();
    mode = s->field_01C;
    s->field_11C = 0;
    s->field_114 = 0;
    s->field_020 = 0;
    s->field_118 = 0;
    if (mode == 3 || mode == 4 || mode == 6 || mode == 5) {
        FadeToBlack(0xD);
    }
    if (((GameState_PAL_2CB5D0 *)(void *)g_pause_menu_state)->field_1F4 == 0) {
        snd_send_cmd23(0x5D);
        if (((GameState_PAL_2CB5D0 *)(void *)g_pause_menu_state)->field_01C != 2 || flag_is_word_set() == 0)
            music_Unpause();
        snd_Pump();
    }
    func_PAL_002E5898();
    if (((GameState_PAL_2CB5D0 *)(void *)g_pause_menu_state)->field_0DB) {
        func_PAL_002B8898(1);
        ((GameState_PAL_2CB5D0 *)(void *)g_pause_menu_state)->field_0DB = 0;
    }
    pad_clear_port_state();
}
