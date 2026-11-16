#include "include_asm.h"
#include "common.h"
extern s16 g_music_state[];
extern void snd_update_music_system(void);
extern void snd_clear_flag_and_update(void);
extern int snd_Pump(void);
extern void snd_set_current_buffer_flag(void);
extern void mem_fast_helper_a(s32);

/* Runs the music and disc read steps once, or repeatedly until the disc read is idle when asked. Returns the read state (PAL). */
s16 snd_pump_music_and_disc_read_pal(s32 wait_until_idle) {
    s16 *state;

    if (wait_until_idle != 0) {
        while (1) {
            snd_update_music_system();
            snd_clear_flag_and_update();
            snd_Pump();
            snd_set_current_buffer_flag();
            if (g_music_state[2] == 0) {
                break;
            }
            mem_fast_helper_a(10000);
            if (g_music_state[2] == 0) {
                break;
            }
        }
    } else {
        snd_update_music_system();
        snd_clear_flag_and_update();
        snd_Pump();
        snd_set_current_buffer_flag();
    }
    state = g_music_state;
    return state[2];
}
