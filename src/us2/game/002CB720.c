#include "include_asm.h"

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* func_US2_002CB720, the USA v2.00 copy of func_002CA790: the same C, with a
   0x30-byte copy, two more calls and a skip on field_1F4. */
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
} GameState_2CB720;

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
extern void UpdateSoundVoices(void);
extern s16 snd_pump_music_and_disc_read(int);
extern void pad_clear_port_state(void);

void func_US2_002CB720(void)
{
    GameState_2CB720 *s = (GameState_2CB720 *)(void *)g_pause_menu_state;
    TI128 *dst;
    int mode;

    *(int *)(void *)g_pause_menu_state = 0;
    gfx_select_packet_buffer_setup();
    dst = (TI128 *)g_camera_eye_state;
    qcopy(dst, &s->field_050);
    qcopy(dst + 1, &s->field_060);
    mem_copy_aligned((char *)dst + 0x230, (char *)s + 0x200, 0x30);
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
        FadeToBlack(0x10);
    }
    if (((GameState_2CB720 *)(void *)g_pause_menu_state)->field_1F4 == 0) {
        snd_send_cmd23(0x5D);
        if (((GameState_2CB720 *)(void *)g_pause_menu_state)->field_01C != 2 || flag_is_word_set() == 0)
            music_Unpause();
        snd_Pump();
    }
    UpdateSoundVoices();
    if (((GameState_2CB720 *)(void *)g_pause_menu_state)->field_0DB) {
        snd_pump_music_and_disc_read(1);
        ((GameState_2CB720 *)(void *)g_pause_menu_state)->field_0DB = 0;
    }
    pad_clear_port_state();
}

