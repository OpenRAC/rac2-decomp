#include "include_asm.h"
#include "names.h"
extern char *g_movie_player_state[] __attribute__((sda));
extern char *ref_L00_0034EF58_01[] __attribute__((sda));
extern char ref_L00_0034EF58_00[];
extern void STUB_printf(void *, ...);
extern void BuildAspectBlitStrips(int, int);
extern int GetThreadId(void);
extern void ChangeThreadPriority(int, int);
extern int mpeg_start_player(void *, void *, int);
extern int read_mpeg(void *, void *, void *);

int mpeg_play_movie_2_pal(void *first, void *second, char *pool, char *state, int mode, int volume)
{
    int result = 0;
    ref_L00_0034EF58_01[0] = pool;
    g_movie_player_state[0] = state;
    STUB_printf(ref_L00_0034EF58_00, 0x38cac0);
    BuildAspectBlitStrips(volume, volume);
    ChangeThreadPriority(GetThreadId(), 1);
    if (mpeg_start_player(first, second, mode)) {
        result = read_mpeg(g_movie_player_state[0] + 0xd9048, g_movie_player_state[0], g_movie_player_state[0] + 0xd9040);
    }
    mpeg_shutdown_player();
    ref_L00_0034EF58_01[0] = 0;
    g_movie_player_state[0] = 0;
    return result;
}
