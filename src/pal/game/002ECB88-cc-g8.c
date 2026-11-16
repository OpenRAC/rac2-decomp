#include "names.h"
/* func_PAL_002ECB88, the PAL copy of func_002EBC70: the same C, where rename func_002EB7E8 becomes func_PAL_002EC700; rename func_00298F00 becomes func_PAL_00299898; rename func_002B9000 becomes func_PAL_002B9BB8; rename func_002EB1E0 becomes func_PAL_002EC0F8; rename func_0027BD70 becomes func_PAL_0027C258; rename func_002EBAA8 becomes func_PAL_002EC9C0. */
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
extern SceneEntry *g_moby_pool_start MACRO_ADDR;
extern SceneFrame g_scene_playback_state;
extern int g_current_game_mode;
extern int g_requested_game_mode;
extern int g_gfx_pass_mode __attribute__((sda));
extern int g_render_layer_flags __attribute__((sda));
extern int g_frame_counter_3;
extern int D_001B1598_GP SDATA(D_001B1598);
extern int D_001A8BB0_GP SDATA(D_001A8BB0);

extern void cutscene_start_scripted_pal(void);
extern void SubmitBufferedDmaChain(void);
extern void gfx_swap_packet_buffer(void);
extern void PutDrawBufferSmall(void);
extern void gfx_queue_second_strip_packet(void);
extern void gfx_append_draw_list_header(void);
extern void mc_update_state_pal(void);
extern void gfx_build_view_matrices(void);
extern void moby_update_watched_objects(void);
extern void gfx_write_clear_color_packets(void);
extern void pad_poll_ports_pal(void);
extern int cutscene_update_scripted_actors_pal(void);
extern void gfx_append_draw_list_buffer_tag(int);
extern void RenderFrame_pal(void);
extern void gfx_wait_for_dma_status_bits(int);
extern int sceGsSyncV(int);
extern void cutscene_end_scripted_pal(void);

/* Plays a bonus reel scene: starts it, runs the frame loop while the scene is active, then ends it. Returns whether the player skipped it. */
int PlayBonusReelWithGameLoop_pal(int unused)
{
    SceneEntry *previous_entry;
    SceneEntry *entry;
    int i;
    int skipped;

    cutscene_start_scripted_pal();
    previous_entry = g_moby_pool_start;
    i = 0;
    if (i < g_scene_playback_state.count) {
        do {
            do {
                entry = g_scene_playback_state.entries[i];
                if (entry != 0 && previous_entry != entry) {
                    entry->previous = previous_entry;
                    previous_entry = entry;
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
        mc_update_state_pal();
        gfx_build_view_matrices();
        moby_update_watched_objects();
        gfx_write_clear_color_packets();
        g_gfx_pass_mode = -1;
        pad_poll_ports_pal();
        skipped = cutscene_update_scripted_actors_pal();
        gfx_append_draw_list_buffer_tag(0);
        g_render_layer_flags = 0x131;
        RenderFrame_pal();
        if (g_requested_game_mode != -2) {
            g_current_game_mode = g_requested_game_mode;
            g_requested_game_mode = -2;
        }
        gfx_wait_for_dma_status_bits(1);
        sceGsSyncV(0);
        D_001B1598_GP = g_frame_counter_3 + 1;
    } while (g_current_game_mode == 2);
    D_001A8BB0_GP = 0;
    cutscene_end_scripted_pal();
    return skipped;
}

