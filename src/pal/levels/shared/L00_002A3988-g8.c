#include "names.h"
/* func_PAL_L00_002A3988, the PAL copy of func_L00_002A3B88 (RunLevelLoop): the same C, where the
 * release's own callees take their func_PAL_ names, the D_L00_001B1680 reload 30 becomes 25, and
 * D_001A7390 is scaled to 50 Hz, ((s32)(x) * 5 + 2) / 6, in both maximum tests and their stores.
 * Clears level state, restores its settings and services frames until loading ends. A -G8 unit of
 * its own. In the loop header the plain `sd` of D_001A7200 and then the volatile T1_COUNT
 * (0x10000800) clear come just before the first jal; the compiler's default set-side volatile rule
 * (GCC 2.95's) leaves that slot empty, as retail does, where the EE tree's rule fills it with the
 * clear of the frame accumulator (docs/COMPILER-NOTES.md).
 * T1_COUNT (include/common.h) is the EE timer 1 count register, 0x10000800. */
#include "common.h"

/* Partial views of the resident settings, weapon table and per-level statistics. */
typedef struct {
    char reserved00[0x18];
    int mode;
    char reserved1c[10];
    short pending, reset, ready, announce, reserved2e;
    int output;
} SoundSettings;
typedef struct {
    int active;
    unsigned char channel;
    char reserved05[15];
    int sound;
    char reserved18[200];
} WeaponResource __attribute__((aligned(16)));
typedef struct {
    unsigned short visits, reserved;
    unsigned int maximum, visited;
} LevelStatistics;

extern unsigned char g_level_bss_end_marker[];
extern const char g_str_l00_debug_message[];
extern int g_game_l00_mode[] __attribute__((sda));
extern int g_input_reset_value, g_input_lock_state;
extern int g_startup_wait_flag, g_call_counter;
extern int g_pad_hold_frame_count[] __attribute__((sda));
extern int g_packet_buffer_reset_flag[] __attribute__((sda));
extern int g_ring_animation_counter[] __attribute__((sda));
extern int g_memcard_input_latch[] __attribute__((sda));
extern int D_L00_001B1680_1 NOT_SDA;
extern int g_previous_l00_map_index;
extern float g_effect_fade_value_a;
extern short g_budget_blocked_flag NOT_SDA;
extern int g_iop_block_table, g_current_weapon_channel;
extern short g_current_texture_pack;
extern unsigned int g_equipment_bits;
extern unsigned char g_item_slot_to_record[];
typedef struct {
    unsigned char reserved0000[0x1248];
    int weapon;
    unsigned char reserved124c[0x22c1 - 0x124c];
    unsigned char flush;
} LevelLoopHero;
extern LevelLoopHero g_hero_state;
extern WeaponResource g_weapon_l00_table[];
extern SoundSettings g_hero_moby_default;
extern int g_arena_state_flag, g_current_map_index, g_menu_choice_table, g_current_item_slot;
extern unsigned char g_skill_point_zone_flag;
extern unsigned char g_map_unlocked_flags[] __attribute__((sda));
extern unsigned char g_level_event_flag_2 NOT_SDA;
extern unsigned char g_map_event_flag_a NOT_SDA, g_map_event_flag_b NOT_SDA, g_previous_map_index NOT_SDA;
extern unsigned int g_frame_counter;
extern LevelStatistics g_statistics_table[];
extern unsigned char g_gfx_rpc_client[] __attribute__((sda));
extern long g_timer_base_count MACRO_ADDR;
typedef struct {
    unsigned char reserved00[0x10];
    int held;
    unsigned char reserved14[0x15c-0x14];
    int pressed;
    int reserved160;
    int alternate;
    int reserved168;
    int transition;
    unsigned char reserved170[0x17c-0x170];
    int counter;
} LevelLoopInput;
extern LevelLoopInput g_memcard_state;
extern unsigned short g_hero_busy_flag_2 NOT_SDA;
extern struct { char reserved00[0x84]; unsigned short resume; } g_subtitle_history;
extern int g_save_menu_screen, g_save_menu_flags, g_is_pal_video;
extern int g_debug_state __attribute__((sda));
extern int g_debug_tick_counter __attribute__((sda));
extern unsigned char g_controller_level_state[];
extern short g_current_music_id NOT_SDA;
extern unsigned char g_map_occlusion_data[];

/* The callees' prototypes, as their definitions in src/ declare them. */
extern void mem_fast_helper_b(void *, int);
extern void STUB_printf(const char *, ...);
extern void gfx_reset_buffer_slot_table(void), level_init_systems(void);
extern void tex_load_pack_to_vram_pal(int), LoadPackSingleTexture_pal(int), LoadDiscTableTexture_pal(int), load_disc_table_entry_for_draw_pal(int);
extern int moby_handle_request_slot_state(int);
extern int LoadLevelArchiveResources_pal(int, int);
extern void map_setup_screen_pal(void), InitializeHudSlotsAndBuffers(void), level_init_callbacks_pal(void);
extern void menu_reset_slots(void);
extern int request_begin_slot(int, int, int, int, unsigned char *);
extern void FadeToBlack(int), snd_start_music_stream_no_loop(int, int, int), music_Pause(int);
extern void snd_set_current_buffer_flag(void);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern void mode_apply_pending_change_pal(void), music_Unpause(void);
extern short snd_pump_music_and_disc_read_pal(int);
extern void LoadClassIntoFreeCacheSlot(int);
extern void gfx_process_screen_copy_regions(void), SubmitBufferedDmaChain(void), gfx_swap_packet_buffer(void);
extern void PutDrawBufferSmall(void), gfx_append_gs_packet_tag_b(void), gfx_append_draw_list_header(void);
extern int snd_Pump(void);
extern void pad_poll_ports_pal(void), level_update_game_frame_input_pal(void), gfx_set_draw_mode_and_render_pal(void);
extern void moby_update_level_objects_pal(void), gfx_reset_screen_overlay_pal(void);
extern void level_run_frame_update_chain_pal(void), gfx_clear_screen_and_render_pal(void);
extern void mpeg_play_movie_pal(void), cutscene_update_frame_pal(void), gfx_render_frame_all_layers_pal(void), DrawLetterboxBars(void);
extern void menu_update_pause_pal(void), gfx_call_engine_routine_zero_pal(void), UpdateModalState_pal(void), gfx_render_frame_extra_layers_pal(void);
extern void update_purchase_menu_and_preview_pal(void), shop_draw_purchase_menu_scene_pal(void), transition_draw_background_pal(void);
extern int update_playback_scene_pal(void);
extern void level_call_seq_update_disc_player_pal(void), level_call_text_draw_screen_wipe_pal(void);
extern void math_trap_always(void), level_decrement_counter_clamped(void), actuator_update(void);
extern void mc_update_state_pal(void), map_update_state_machine(void), SetupGifPaging(int);
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern int GetIconFrame(int, int);
/* Retail returns the full 64-bit texture descriptor in v0. */
extern unsigned long long GetFrameTexture(int);
extern void hud_draw_sprite(int, int, int, int, int, int);
extern void DrawRotatedSprite(int, int, long long, float, float, float, float, float);
extern void DoGifPaging(void), gfx_wait_for_dma_status_bits(unsigned long);
extern float IntToFloat(int);
extern int sceGsSyncV(int);
extern void counter_count_calls_bump(void), ResetGsRegistersPr(void), gfx_reset_packet_buffer(void);
extern void snd_clear_flag_and_update(void), snd_clear_all_voices(void), snd_wait_for_music_idle(void), subtitle_clear_state(void);
extern void pad_reset_input_state(int), map_fill_buffer(void *), RunLevelTransition_pal(void);

/* Clears level state, restores its settings and services frames until loading ends. */
void RunLevelLoop_pal(void)
{
    int i, allowed, old_mode, flush, extra, limit, ticks, sound, period;
    float sprite_size;
    float elapsed, angle;
    if (!(((unsigned int)g_level_bss_end_marker - (unsigned int)&D_L00_001B1680_1) & 15) && !((unsigned int)&D_L00_001B1680_1 & 15)) {
        mem_fast_helper_b(&D_L00_001B1680_1, (unsigned int)g_level_bss_end_marker - (unsigned int)&D_L00_001B1680_1);
    } else {
        STUB_printf(g_str_l00_debug_message);
        for (i = 0; i < (int)((unsigned int)g_level_bss_end_marker - (unsigned int)&D_L00_001B1680_1); i++) ((unsigned char *)&D_L00_001B1680_1)[i] = 0;
    }
    gfx_reset_buffer_slot_table();
    g_game_l00_mode[0] = 0;
    g_input_lock_state = -2;
    g_input_reset_value = 0;
    g_pad_hold_frame_count[0] = 0;
    level_init_systems();
    if (g_iop_block_table != g_current_texture_pack) tex_load_pack_to_vram_pal(g_current_texture_pack);
    {
        int weapon = g_item_slot_to_record[10];
        if (g_current_weapon_channel != g_weapon_l00_table[weapon].channel)
            LoadPackSingleTexture_pal(g_weapon_l00_table[weapon].channel);
    }
    {
        int output = (g_equipment_bits >> 16) & 31;
        if (g_hero_moby_default.output != output) LoadDiscTableTexture_pal(output);
    }
    if (g_hero_moby_default.mode != (g_equipment_bits & 3)) load_disc_table_entry_for_draw_pal(g_equipment_bits & 3);
    if (!g_weapon_l00_table[g_item_slot_to_record[g_hero_state.weapon]].active) moby_handle_request_slot_state(10);
    LoadLevelArchiveResources_pal(1, 0);
    map_setup_screen_pal();
    InitializeHudSlotsAndBuffers();
    level_init_callbacks_pal();
    menu_reset_slots();
    g_hero_moby_default.ready = 1;
    if (g_hero_moby_default.reset) g_hero_moby_default.reset = 0;
    allowed = 1;
    if (g_hero_moby_default.pending || g_arena_state_flag
        || g_current_map_index == 0 || g_current_map_index == 5 || g_current_map_index == 10 || g_current_map_index == 15
        || (g_current_map_index > 20 && g_current_map_index != 24)
        || (g_current_map_index == 4 && g_skill_point_zone_flag && !g_map_event_flag_a)
        || (g_current_map_index == 9 && g_map_event_flag_b)
        || (g_current_map_index == 14 && !g_level_event_flag_2))
        allowed = 0;
    if (allowed && g_hero_moby_default.announce) request_begin_slot(6, 1, 6, 0, 0);
    g_hero_moby_default.pending = 0;
    g_arena_state_flag = 0;
    FadeToBlack(4);
    g_ring_animation_counter[0] = 0;
    snd_start_music_stream_no_loop(0, 1, 1024);
    music_Pause(0);
    if (g_current_map_index < 28 && !g_map_unlocked_flags[g_current_map_index]) g_map_unlocked_flags[g_current_map_index] = 1;
    if (g_statistics_table[g_current_map_index].visits < 65535) g_statistics_table[g_current_map_index].visits++;
    if (((int)g_frame_counter * 5 + 2) / 6 > g_statistics_table[g_current_map_index].maximum)
        g_statistics_table[g_current_map_index].maximum = ((int)g_frame_counter * 5 + 2) / 6;
    g_statistics_table[g_current_map_index].visited = g_statistics_table[g_current_map_index].visited | (1u << g_current_map_index) | 0x80000000u;
    snd_set_current_buffer_flag();
    sceSifCallRpc(g_gfx_rpc_client, 3, 0, 0, 0, 0, 0, 0, 0);
    mode_apply_pending_change_pal();
    if (!g_game_l00_mode[0]) music_Unpause();
    snd_pump_music_and_disc_read_pal(1);
    LoadClassIntoFreeCacheSlot(g_weapon_l00_table[g_item_slot_to_record[g_menu_choice_table]].sound);
    snd_pump_music_and_disc_read_pal(1);
    LoadClassIntoFreeCacheSlot(g_weapon_l00_table[g_item_slot_to_record[g_current_item_slot]].sound);
    snd_pump_music_and_disc_read_pal(1);
    while (!g_startup_wait_flag) {
        g_packet_buffer_reset_flag[0] = 0;
        flush = 0;
        extra = 0;
        g_timer_base_count += T1_COUNT;
        T1_COUNT = 0;
        gfx_process_screen_copy_regions();
        SubmitBufferedDmaChain();
        gfx_swap_packet_buffer();
        PutDrawBufferSmall();
        gfx_append_gs_packet_tag_b();
        gfx_append_draw_list_header();
        snd_Pump();
        old_mode = g_game_l00_mode[0];
        switch (old_mode) {
        case -1: case 0:
            pad_poll_ports_pal();
            level_update_game_frame_input_pal();
            if (g_debug_state == 1) {
                T1_COUNT = 0;
                pad_poll_ports_pal();
                level_update_game_frame_input_pal();
            }
            gfx_set_draw_mode_and_render_pal();
            break;
        case 8:
            pad_poll_ports_pal();
            moby_update_level_objects_pal();
            gfx_reset_screen_overlay_pal();
            break;
        case 7:
            pad_poll_ports_pal();
            level_run_frame_update_chain_pal();
            gfx_clear_screen_and_render_pal();
            break;
        case 1:
            mpeg_play_movie_pal();
            break;
        case 2:
            pad_poll_ports_pal();
            cutscene_update_frame_pal();
            gfx_render_frame_all_layers_pal();
            DrawLetterboxBars();
            break;
        case 3:
            pad_poll_ports_pal();
            menu_update_pause_pal();
            gfx_call_engine_routine_zero_pal();
            break;
        case 4:
            pad_poll_ports_pal();
            UpdateModalState_pal();
            gfx_render_frame_extra_layers_pal();
            break;
        case 5:
            pad_poll_ports_pal();
            update_purchase_menu_and_preview_pal();
            shop_draw_purchase_menu_scene_pal();
            break;
        case 6:
            pad_poll_ports_pal();
            update_playback_scene_pal();
            transition_draw_background_pal();
            break;
        case 9:
            pad_poll_ports_pal();
            level_call_seq_update_disc_player_pal();
            level_call_text_draw_screen_wipe_pal();
            break;
        case -2: case 10: default:
            math_trap_always();
            break;
        }
        g_pad_hold_frame_count[0]++;
        level_decrement_counter_clamped();
        if (!g_game_l00_mode[0]) actuator_update();
        mc_update_state_pal();
        map_update_state_machine();
        if ((unsigned)(g_memcard_state.pressed - 15) < 2 || g_memcard_state.alternate == 15 || g_memcard_input_latch[0]) {
            if (g_memcard_state.transition || g_memcard_state.held) {
                g_memcard_state.counter = 0;
                g_save_menu_screen = 21;
                g_save_menu_flags = 64;
                g_memcard_input_latch[0] = 0;
                if (!g_game_l00_mode[0])
                    request_begin_slot(4, 1, 1, 0, 0);
                else
                    request_begin_slot(4, 2, 1, 0, 0);
            } else if (g_memcard_input_latch[0] == -1) {
                if (!g_game_l00_mode[0]) {
                    if (!g_subtitle_history.resume) g_subtitle_history.resume = 1;
                    g_memcard_input_latch[0] = 0;
                }
            } else if (!g_game_l00_mode[0] && !g_hero_busy_flag_2) {
                request_begin_slot(4, 1, 2, 0, 0);
                g_memcard_input_latch[0] = -1;
            } else {
                if ((unsigned)(g_memcard_state.pressed - 15) < 2 || g_memcard_state.alternate == 15)
                    g_memcard_input_latch[0] = 25;
                else
                    g_memcard_input_latch[0] = g_memcard_input_latch[0] - 1;
                period = 55;
                SetupGifPaging(0);
                sprite_size = 272.0f;
                VU1_addGSregister(71, 0x2004bULL);
                hud_draw_sprite(GetIconFrame(0x755d, 0), 425, 250, 64, 64, 128);
                angle = ((float)(g_ring_animation_counter[0] % period) * -6.2831854820251465f) / (float)period;
                DrawRotatedSprite(64, 64, GetFrameTexture(GetIconFrame(0x755d, 1)), 7312.0f, 4512.0f, sprite_size, sprite_size, angle);
                DoGifPaging();
                if (g_save_menu_screen == 2) g_memcard_input_latch[0] = 0;
            }
        }
        gfx_wait_for_dma_status_bits(1);
        elapsed = IntToFloat(T1_COUNT);
        g_effect_fade_value_a = elapsed * (g_is_pal_video ? 0.00008680556f : 0.00010416667f);
        if (!g_hero_state.flush && !g_packet_buffer_reset_flag[0]) {
            if (!g_game_l00_mode[0]) {
                ticks = T1_COUNT;
                limit = g_is_pal_video ? 11520 : 9600;
                if (g_debug_state == 0) {
                    if (limit < ticks) {
                        g_debug_tick_counter = 0;
                        g_debug_state = 1;
                    }
                } else if (g_debug_state == 1) {
                    if (g_debug_tick_counter >= 2) {
                        g_debug_tick_counter = 0;
                        g_debug_state = 2;
                    }
                } else if (g_debug_state == 2) {
                    if (g_debug_tick_counter >= 4 && ticks <= limit) {
                        g_debug_tick_counter = 0;
                        g_debug_state = 3;
                    }
                } else if (g_debug_state == 3) {
                    g_debug_state = 0;
                    g_debug_tick_counter = 0;
                }
                g_debug_tick_counter++;
                if (g_debug_state == 0) {
                    sceGsSyncV(0);
                    g_ring_animation_counter[0]++;
                } else if (g_debug_state == 1) {
                    g_ring_animation_counter[0]++;
                } else if (g_debug_state == 2) {
                    if (limit < ticks) g_debug_tick_counter = 0;
                    if (!g_game_l00_mode[0]) {
                        pad_poll_ports_pal();
                        level_update_game_frame_input_pal();
                    } else if (g_game_l00_mode[0] == 2 && !g_budget_blocked_flag) {
                        pad_poll_ports_pal();
                        cutscene_update_frame_pal();
                    }
                    actuator_update();
                    sceGsSyncV(0);
                    g_ring_animation_counter[0]++;
                } else if (g_debug_state == 3) {
                    sceGsSyncV(0);
                    sceGsSyncV(0);
                    g_ring_animation_counter[0]++;
                }
                counter_count_calls_bump();
            } else if (g_game_l00_mode[0] == 2) {
                int now = T1_COUNT;
                int budget = g_is_pal_video ? 11520 : 9600;
                if (budget < now && !g_budget_blocked_flag) {
                    pad_poll_ports_pal();
                    cutscene_update_frame_pal();
                }
                actuator_update();
                counter_count_calls_bump();
                sceGsSyncV(0);
                g_ring_animation_counter[0]++;
            } else {
                sceGsSyncV(0);
                g_debug_state = 0;
                g_debug_tick_counter = 0;
                g_ring_animation_counter[0]++;
                counter_count_calls_bump();
            }
            g_call_counter = 0;
        }
        ResetGsRegistersPr();
        if (!g_game_l00_mode[0] && g_hero_state.flush) { flush = 1; extra = 1; }
        if (flush) {
            gfx_reset_packet_buffer();
            snd_clear_flag_and_update();
            snd_Pump();
            snd_clear_all_voices();
            snd_wait_for_music_idle();
            sound = g_current_music_id;
            if (*(int *)g_controller_level_state) sound = *(int *)(g_controller_level_state + 0xc64);
            subtitle_clear_state();
            LoadLevelArchiveResources_pal(0, extra);
            pad_reset_input_state(0);
            snd_start_music_stream_no_loop(sound, 1, 1024);
            InitializeHudSlotsAndBuffers();
        } else {
            mode_apply_pending_change_pal();
            if (g_game_l00_mode[0] != old_mode) g_pad_hold_frame_count[0] = 0;
            if (g_packet_buffer_reset_flag[0]) gfx_reset_packet_buffer();
        }
        if (((int)g_frame_counter * 5 + 2) / 6 > g_statistics_table[g_current_map_index].maximum)
        g_statistics_table[g_current_map_index].maximum = ((int)g_frame_counter * 5 + 2) / 6;
    }
    map_fill_buffer(g_map_occlusion_data + g_current_map_index * 2048);
    if (g_previous_l00_map_index != g_current_map_index) g_previous_map_index = g_current_map_index;
    RunLevelTransition_pal();
}
