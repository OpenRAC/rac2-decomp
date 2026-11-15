#include "common.h"

/* One frame of the level transition loop: it re-links the queued entries to
   their predecessor, runs the frame's call sequence, and repeats while the
   shared mode word says "running".  The three small-data words it counts live
   in the program's own small-data area, so the unit is built with -G8. */
typedef struct {
    char pad0[0x28]; void *previous;
} SceneEntry;
typedef struct {
    char pad0[0x44]; short count; char pad46[0x146]; SceneEntry *entries[17];
    char pad1D0[0x1A0]; int mode; char pad374[4]; int next_mode;
} SceneFrame;
extern SceneEntry *D_001B1B5C MACRO_ADDR;
extern SceneFrame g_scene_playback_state;
extern int g_current_game_mode;
extern int g_requested_game_mode;
extern int D_001B169C __attribute__((sda));
extern int D_001B1594 __attribute__((sda));
extern int D_001B1598;
extern int D_001B1598_GP SDATA(D_001B1598);
extern int D_001A8BB0_GP SDATA(D_001A8BB0);

extern void cutscene_start_scripted(void);
extern void SubmitBufferedDmaChain(void);
extern void gfx_swap_packet_buffer(void);
extern void PutDrawBufferSmall(void);
extern void gfx_queue_second_strip_packet(void);
extern void gfx_append_draw_list_header(void);
extern void mc_update_state(void);
extern void gfx_build_view_matrices(void);
extern void moby_update_watched_objects(void);
extern void gfx_write_clear_color_packets(void);
extern void pad_poll_ports(void);
extern int cutscene_update_scripted_actors(void);
extern void gfx_append_draw_list_buffer_tag(int);
extern void RenderFrame(void);
extern void gfx_wait_for_dma_status_bits(int);
extern int sceGsSyncV(int);
extern void cutscene_end_scripted(void);

int PlayBonusReelWithGameLoop(int unused)
{
    SceneEntry *prev;
    SceneEntry *entry;
    int i;
    int value;

    cutscene_start_scripted();
    prev = D_001B1B5C;
    i = 0;
    if (i < g_scene_playback_state.count) {
        do {
            do {
                entry = g_scene_playback_state.entries[i];
                if (entry != 0 && prev != entry) {
                    entry->previous = prev;
                    prev = entry;
                }
            } while (0);
            i++;
        } while (i < g_scene_playback_state.count);
    }
    g_current_game_mode = 2;
    do {
        SubmitBufferedDmaChain();
        gfx_swap_packet_buffer();
        PutDrawBufferSmall();
        gfx_queue_second_strip_packet();
        gfx_append_draw_list_header();
        mc_update_state();
        gfx_build_view_matrices();
        moby_update_watched_objects();
        gfx_write_clear_color_packets();
        D_001B169C = -1;
        pad_poll_ports();
        value = cutscene_update_scripted_actors();
        gfx_append_draw_list_buffer_tag(0);
        D_001B1594 = 0x131;
        RenderFrame();
        if (g_requested_game_mode != -2) {
            g_current_game_mode = g_requested_game_mode;
            g_requested_game_mode = -2;
        }
        gfx_wait_for_dma_status_bits(1);
        sceGsSyncV(0);
        D_001B1598_GP = D_001B1598 + 1;
    } while (g_current_game_mode == 2);
    D_001A8BB0_GP = 0;
    cutscene_end_scripted();
    return value;
}

