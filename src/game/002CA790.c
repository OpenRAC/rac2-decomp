#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

/* The game's global state at 0x1F2840: the mode word, the reset counters, the
   spawn table and the flags the reset touches. */
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
} GameState_2CA790;

extern char g_pause_menu_state[];
extern char g_camera_eye_state[];
extern float D_001B90F0[];

extern void gfx_select_packet_buffer_setup(void);
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

/* Leaves the pause screen: restores the saved camera and display values and lets the game run normally again. */
void RestoreMenuDisplayState(void)
{
    GameState_2CA790 *pauseState = (GameState_2CA790 *)(void *)g_pause_menu_state;
    TI128 *dst;
    TI128 *src = (TI128 *)((char *)pauseState + 0x50);
    int mode;

    *(int *)(void *)g_pause_menu_state = 0;
    gfx_select_packet_buffer_setup();
    dst = (TI128 *)g_camera_eye_state;
    qcopy(dst, src);
    src = (TI128 *)((char *)pauseState + 0x60);
    qcopy(dst + 1, src);
    *(float *)D_001B90F0 = pauseState->field_0F8;
    select_moby_context(0);
    gfx_apply_display_config();
    mode = pauseState->field_01C;
    pauseState->field_11C = 0;
    pauseState->field_114 = 0;
    pauseState->field_020 = 0;
    pauseState->field_118 = 0;
    if (mode == 3 || mode == 4 || mode == 6 || mode == 5) {
        FadeToBlack(0x10);
    }
    snd_send_cmd23(0x5D);
    if (((GameState_2CA790 *)(void *)g_pause_menu_state)->field_01C != 2 || flag_is_word_set() == 0)
        music_Unpause();
    snd_Pump();
    UpdateSoundVoices();
    mode = ((GameState_2CA790 *)(void *)g_pause_menu_state)->field_0DB;
    if (mode) {
        snd_pump_music_and_disc_read(1);
        ((GameState_2CA790 *)(void *)g_pause_menu_state)->field_0DB = 0;
    }
    pad_clear_port_state();
}
