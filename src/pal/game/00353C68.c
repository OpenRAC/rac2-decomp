#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern char *g_movie_player_state[] __attribute__((sda));
extern int mpeg_vibuf_reset(void *);
extern void mpeg_vobuf_reset(u8 *);
extern int mpeg_dec_run_loop(void *);
extern char *g_movie_player_state[] __attribute__((sda));
extern char *g_movie_player_state[] __attribute__((sda));
extern char *g_movie_player_state[] __attribute__((sda));

/* Starts the video decoder: resets its buffers, runs the decode loop, and waits until it is told to stop (PAL). */
void mpeg_dec_start_pal(unsigned char *object)
{
    char *player_state;
    mpeg_vibuf_reset(object + 0x48);
    mpeg_vobuf_reset(g_movie_player_state[0] + 0xD9168);
    mpeg_dec_run_loop(object);
    player_state = g_movie_player_state[0];
    while (*(int *)(player_state + 0xD9174)) {
        if (videoDecGetState(object) == 1) break;
        player_state = g_movie_player_state[0];
    }
    mpeg_dec_swap_state(object, 3);
}

