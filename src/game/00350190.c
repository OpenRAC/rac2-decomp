#include "common.h"
extern volatile int D_001AE7D8 __attribute__((sda));
extern char *g_movie_player_state[] __attribute__((sda));
extern void voBufDecCount(unsigned char *);

/* Releases the last movie video frame and syncs. */
int mpeg_release_video_frame(void)
{
    if (D_001AE7D8 != 0) {
        voBufDecCount(g_movie_player_state[0] + 0xD9168);
        D_001AE7D8 = 0;
    }
    CpuSync();
    CpuEnableInt();
    return 0;
}
