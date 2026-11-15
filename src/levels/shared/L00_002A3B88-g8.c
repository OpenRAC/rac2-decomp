/* func_L00_002A3B88 (RunLevelLoop): clears level state, restores its settings and services frames
 * until loading ends. A -G8 unit of its own. In the loop header the plain `sd` of D_001A7200 and
 * then the volatile T1_COUNT (0x10000800) clear come just before the first jal; the compiler's
 * default set-side volatile rule (GCC 2.95's) leaves that slot empty, as retail does, where the
 * EE tree's rule fills it with the clear of the frame accumulator (docs/build/compiler-notes.md).
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

extern unsigned char D_L00_0025BBA0[];
extern const char D_L00_001A7C88[];
extern int D_L00_001A8F00[] __attribute__((sda));
extern int D_L00_001A8F04, D_L00_001A8F08;
extern int D_L00_001A8ED4, D_L00_001A8FE0;
extern int D_L00_001B19C4[] __attribute__((sda));
extern int D_L00_001B19D4[] __attribute__((sda));
extern int D_L00_001B18D8[] __attribute__((sda));
extern int D_L00_001B1680[] __attribute__((sda));
extern int D_L00_001B1680_1 NOT_SDA;
extern int D_L00_001B19C0;
extern float D_L00_001B19CC;
extern short D_L00_001BCB24 NOT_SDA;
extern int D_001A7290, D_001A72C0;
extern short D_001A7A18;
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
extern int D_001A7904, g_current_map_index, D_001A7398, D_001A7A04;
extern unsigned char D_001A7B1F;
extern unsigned char D_001A7BE8[] __attribute__((sda));
extern unsigned char D_0019B3D2 NOT_SDA;
extern unsigned char D_001395CA NOT_SDA, D_001395E5 NOT_SDA, D_00139629 NOT_SDA;
extern unsigned int D_001A7390;
extern LevelStatistics D_0018C360[];
extern unsigned char D_001A7248[] __attribute__((sda));
extern long D_001A7200 MACRO_ADDR;
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
extern unsigned short D_0018C9DC NOT_SDA;
extern struct { char reserved00[0x84]; unsigned short resume; } g_subtitle_history;
extern int g_save_menu_screen, g_save_menu_flags, g_is_pal_video;
extern int D_L00_001A7C80 __attribute__((sda));
extern int D_L00_001A7C84 __attribute__((sda));
extern unsigned char D_L00_0021DDB0[];
extern short D_001A63F0 NOT_SDA;
extern unsigned char D_0018D278[];

/* The callees' prototypes, as their definitions in src/ declare them. */
extern void mem_fast_helper_b(void *, int);
extern void STUB_printf(const char *, ...);
extern void gfx_reset_buffer_slot_table(void), level_init_systems(void);
extern void tex_load_pack_to_vram(int), LoadPackSingleTexture(int), LoadDiscTableTexture(int), load_disc_table_entry_for_draw(int);
extern int moby_handle_request_slot_state(int);
extern int LoadLevelArchiveResources(int, int);
extern void map_setup_screen(void), InitializeHudSlotsAndBuffers(void), level_init_callbacks(void);
extern void menu_reset_slots(void);
extern int request_begin_slot(int, int, int, int, unsigned char *);
extern void FadeToBlack(int), snd_start_music_stream_no_loop(int, int, int), music_Pause(int);
extern void snd_set_current_buffer_flag(void);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern void mode_apply_pending_change(void), music_Unpause(void);
extern short snd_pump_music_and_disc_read(int);
extern void LoadClassIntoFreeCacheSlot(int);
extern void gfx_process_screen_copy_regions(void), SubmitBufferedDmaChain(void), gfx_swap_packet_buffer(void);
extern void PutDrawBufferSmall(void), gfx_append_gs_packet_tag_b(void), gfx_append_draw_list_header(void);
extern int snd_Pump(void);
extern void pad_poll_ports(void), level_update_game_frame_input(void), gfx_set_draw_mode_and_render(void);
extern void moby_update_level_objects(void), gfx_reset_screen_overlay(void);
extern void level_run_frame_update_chain(void), gfx_clear_screen_and_render(void);
extern void mpeg_play_movie(void), cutscene_update_frame(void), gfx_render_frame_all_layers(void), DrawLetterboxBars(void);
extern void menu_update_pause(void), gfx_call_engine_routine_zero(void), UpdateModalState(void), gfx_render_frame_extra_layers(void);
extern void UpdatePurchaseMenuAndPreview(void), shop_draw_purchase_menu_scene(void), transition_draw_background(void);
extern int UpdatePlaybackScene(void);
extern int level_call_helper_d(void), level_call_helper_e(void);
extern void math_trap_always(void), level_decrement_counter_clamped(void), math_add_wrapping_counter(void);
extern void mc_update_state(void), map_update_state_machine(void), SetupGifPaging(int);
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
extern void pad_reset_input_state(int), map_fill_buffer(void *), RunLevelTransition(void);

/* Clears level state, restores its settings and services frames until loading ends. */
void RunLevelLoop(void)
{
    int i, allowed, oldMode, flush, extra, limit, ticks, sound, period;
    float spriteSize;
    float elapsed, angle;
    if (!(((unsigned int)D_L00_0025BBA0 - (unsigned int)&D_L00_001B1680_1) & 15) && !((unsigned int)&D_L00_001B1680_1 & 15)) {
        mem_fast_helper_b(&D_L00_001B1680_1, (unsigned int)D_L00_0025BBA0 - (unsigned int)&D_L00_001B1680_1);
    } else {
        STUB_printf(D_L00_001A7C88);
        for (i = 0; i < (int)((unsigned int)D_L00_0025BBA0 - (unsigned int)&D_L00_001B1680_1); i++) ((unsigned char *)&D_L00_001B1680_1)[i] = 0;
    }
    gfx_reset_buffer_slot_table();
    D_L00_001A8F00[0] = 0;
    D_L00_001A8F08 = -2;
    D_L00_001A8F04 = 0;
    D_L00_001B19C4[0] = 0;
    level_init_systems();
    if (D_001A7290 != D_001A7A18) tex_load_pack_to_vram(D_001A7A18);
    {
        int weapon = g_item_slot_to_record[10];
        if (D_001A72C0 != g_weapon_l00_table[weapon].channel)
            LoadPackSingleTexture(g_weapon_l00_table[weapon].channel);
    }
    {
        int output = (g_equipment_bits >> 16) & 31;
        if (g_hero_moby_default.output != output) LoadDiscTableTexture(output);
    }
    if (g_hero_moby_default.mode != (g_equipment_bits & 3)) load_disc_table_entry_for_draw(g_equipment_bits & 3);
    if (!g_weapon_l00_table[g_item_slot_to_record[g_hero_state.weapon]].active) moby_handle_request_slot_state(10);
    LoadLevelArchiveResources(1, 0);
    map_setup_screen();
    InitializeHudSlotsAndBuffers();
    level_init_callbacks();
    menu_reset_slots();
    g_hero_moby_default.ready = 1;
    if (g_hero_moby_default.reset) g_hero_moby_default.reset = 0;
    allowed = 1;
    if (g_hero_moby_default.pending || D_001A7904
        || g_current_map_index == 0 || g_current_map_index == 5 || g_current_map_index == 10 || g_current_map_index == 15
        || (g_current_map_index > 20 && g_current_map_index != 24)
        || (g_current_map_index == 4 && D_001A7B1F && !D_001395CA)
        || (g_current_map_index == 9 && D_001395E5)
        || (g_current_map_index == 14 && !D_0019B3D2))
        allowed = 0;
    if (allowed && g_hero_moby_default.announce) request_begin_slot(6, 1, 6, 0, 0);
    g_hero_moby_default.pending = 0;
    D_001A7904 = 0;
    FadeToBlack(4);
    D_L00_001B18D8[0] = 0;
    snd_start_music_stream_no_loop(0, 1, 1024);
    music_Pause(0);
    if (g_current_map_index < 28 && !D_001A7BE8[g_current_map_index]) D_001A7BE8[g_current_map_index] = 1;
    if (D_0018C360[g_current_map_index].visits < 65535) D_0018C360[g_current_map_index].visits++;
    if (D_0018C360[g_current_map_index].maximum < D_001A7390) D_0018C360[g_current_map_index].maximum = D_001A7390;
    D_0018C360[g_current_map_index].visited = D_0018C360[g_current_map_index].visited | (1u << g_current_map_index) | 0x80000000u;
    snd_set_current_buffer_flag();
    sceSifCallRpc(D_001A7248, 3, 0, 0, 0, 0, 0, 0, 0);
    mode_apply_pending_change();
    if (!D_L00_001A8F00[0]) music_Unpause();
    snd_pump_music_and_disc_read(1);
    LoadClassIntoFreeCacheSlot(g_weapon_l00_table[g_item_slot_to_record[D_001A7398]].sound);
    snd_pump_music_and_disc_read(1);
    LoadClassIntoFreeCacheSlot(g_weapon_l00_table[g_item_slot_to_record[D_001A7A04]].sound);
    snd_pump_music_and_disc_read(1);
    while (!D_L00_001A8ED4) {
        D_L00_001B19D4[0] = 0;
        flush = 0;
        extra = 0;
        D_001A7200 += T1_COUNT;
        T1_COUNT = 0;
        gfx_process_screen_copy_regions();
        SubmitBufferedDmaChain();
        gfx_swap_packet_buffer();
        PutDrawBufferSmall();
        gfx_append_gs_packet_tag_b();
        gfx_append_draw_list_header();
        snd_Pump();
        oldMode = D_L00_001A8F00[0];
        switch (oldMode) {
        case -1: case 0:
            pad_poll_ports();
            level_update_game_frame_input();
            if (D_L00_001A7C80 == 1) {
                T1_COUNT = 0;
                pad_poll_ports();
                level_update_game_frame_input();
            }
            gfx_set_draw_mode_and_render();
            break;
        case 8:
            pad_poll_ports();
            moby_update_level_objects();
            gfx_reset_screen_overlay();
            break;
        case 7:
            pad_poll_ports();
            level_run_frame_update_chain();
            gfx_clear_screen_and_render();
            break;
        case 1:
            mpeg_play_movie();
            break;
        case 2:
            pad_poll_ports();
            cutscene_update_frame();
            gfx_render_frame_all_layers();
            DrawLetterboxBars();
            break;
        case 3:
            pad_poll_ports();
            menu_update_pause();
            gfx_call_engine_routine_zero();
            break;
        case 4:
            pad_poll_ports();
            UpdateModalState();
            gfx_render_frame_extra_layers();
            break;
        case 5:
            pad_poll_ports();
            UpdatePurchaseMenuAndPreview();
            shop_draw_purchase_menu_scene();
            break;
        case 6:
            pad_poll_ports();
            UpdatePlaybackScene();
            transition_draw_background();
            break;
        case 9:
            pad_poll_ports();
            level_call_helper_d();
            level_call_helper_e();
            break;
        case -2: case 10: default:
            math_trap_always();
            break;
        }
        D_L00_001B19C4[0]++;
        level_decrement_counter_clamped();
        if (!D_L00_001A8F00[0]) math_add_wrapping_counter();
        mc_update_state();
        map_update_state_machine();
        if ((unsigned)(g_memcard_state.pressed - 15) < 2 || g_memcard_state.alternate == 15 || D_L00_001B1680[0]) {
            if (g_memcard_state.transition || g_memcard_state.held) {
                g_memcard_state.counter = 0;
                g_save_menu_screen = 21;
                g_save_menu_flags = 64;
                D_L00_001B1680[0] = 0;
                if (!D_L00_001A8F00[0])
                    request_begin_slot(4, 1, 1, 0, 0);
                else
                    request_begin_slot(4, 2, 1, 0, 0);
            } else if (D_L00_001B1680[0] == -1) {
                if (!D_L00_001A8F00[0]) {
                    if (!g_subtitle_history.resume) g_subtitle_history.resume = 1;
                    D_L00_001B1680[0] = 0;
                }
            } else if (!D_L00_001A8F00[0] && !D_0018C9DC) {
                request_begin_slot(4, 1, 2, 0, 0);
                D_L00_001B1680[0] = -1;
            } else {
                if ((unsigned)(g_memcard_state.pressed - 15) < 2 || g_memcard_state.alternate == 15)
                    D_L00_001B1680[0] = 30;
                else
                    D_L00_001B1680[0] = D_L00_001B1680[0] - 1;
                period = 55;
                SetupGifPaging(0);
                spriteSize = 272.0f;
                VU1_addGSregister(71, 0x2004bULL);
                hud_draw_sprite(GetIconFrame(0x755d, 0), 425, 250, 64, 64, 128);
                angle = ((float)(D_L00_001B18D8[0] % period) * -6.2831854820251465f) / (float)period;
                DrawRotatedSprite(64, 64, GetFrameTexture(GetIconFrame(0x755d, 1)), 7312.0f, 4512.0f, spriteSize, spriteSize, angle);
                DoGifPaging();
                if (g_save_menu_screen == 2) D_L00_001B1680[0] = 0;
            }
        }
        gfx_wait_for_dma_status_bits(1);
        elapsed = IntToFloat(T1_COUNT);
        D_L00_001B19CC = elapsed * (g_is_pal_video ? 0.00008680556f : 0.00010416667f);
        if (!g_hero_state.flush && !D_L00_001B19D4[0]) {
            if (!D_L00_001A8F00[0]) {
                ticks = T1_COUNT;
                limit = g_is_pal_video ? 11520 : 9600;
                if (D_L00_001A7C80 == 0) {
                    if (limit < ticks) {
                        D_L00_001A7C84 = 0;
                        D_L00_001A7C80 = 1;
                    }
                } else if (D_L00_001A7C80 == 1) {
                    if (D_L00_001A7C84 >= 2) {
                        D_L00_001A7C84 = 0;
                        D_L00_001A7C80 = 2;
                    }
                } else if (D_L00_001A7C80 == 2) {
                    if (D_L00_001A7C84 >= 4 && ticks <= limit) {
                        D_L00_001A7C84 = 0;
                        D_L00_001A7C80 = 3;
                    }
                } else if (D_L00_001A7C80 == 3) {
                    D_L00_001A7C80 = 0;
                    D_L00_001A7C84 = 0;
                }
                D_L00_001A7C84++;
                if (D_L00_001A7C80 == 0) {
                    sceGsSyncV(0);
                    D_L00_001B18D8[0]++;
                } else if (D_L00_001A7C80 == 1) {
                    D_L00_001B18D8[0]++;
                } else if (D_L00_001A7C80 == 2) {
                    if (limit < ticks) D_L00_001A7C84 = 0;
                    if (!D_L00_001A8F00[0]) {
                        pad_poll_ports();
                        level_update_game_frame_input();
                    } else if (D_L00_001A8F00[0] == 2 && !D_L00_001BCB24) {
                        pad_poll_ports();
                        cutscene_update_frame();
                    }
                    math_add_wrapping_counter();
                    sceGsSyncV(0);
                    D_L00_001B18D8[0]++;
                } else if (D_L00_001A7C80 == 3) {
                    sceGsSyncV(0);
                    sceGsSyncV(0);
                    D_L00_001B18D8[0]++;
                }
                counter_count_calls_bump();
            } else if (D_L00_001A8F00[0] == 2) {
                int now = T1_COUNT;
                int budget = g_is_pal_video ? 11520 : 9600;
                if (budget < now && !D_L00_001BCB24) {
                    pad_poll_ports();
                    cutscene_update_frame();
                }
                math_add_wrapping_counter();
                counter_count_calls_bump();
                sceGsSyncV(0);
                D_L00_001B18D8[0]++;
            } else {
                sceGsSyncV(0);
                D_L00_001A7C80 = 0;
                D_L00_001A7C84 = 0;
                D_L00_001B18D8[0]++;
                counter_count_calls_bump();
            }
            D_L00_001A8FE0 = 0;
        }
        ResetGsRegistersPr();
        if (!D_L00_001A8F00[0] && g_hero_state.flush) { flush = 1; extra = 1; }
        if (flush) {
            gfx_reset_packet_buffer();
            snd_clear_flag_and_update();
            snd_Pump();
            snd_clear_all_voices();
            snd_wait_for_music_idle();
            sound = D_001A63F0;
            if (*(int *)D_L00_0021DDB0) sound = *(int *)(D_L00_0021DDB0 + 0xc64);
            subtitle_clear_state();
            LoadLevelArchiveResources(0, extra);
            pad_reset_input_state(0);
            snd_start_music_stream_no_loop(sound, 1, 1024);
            InitializeHudSlotsAndBuffers();
        } else {
            mode_apply_pending_change();
            if (D_L00_001A8F00[0] != oldMode) D_L00_001B19C4[0] = 0;
            if (D_L00_001B19D4[0]) gfx_reset_packet_buffer();
        }
        if (D_0018C360[g_current_map_index].maximum < D_001A7390) D_0018C360[g_current_map_index].maximum = D_001A7390;
    }
    map_fill_buffer(D_0018D278 + g_current_map_index * 2048);
    if (D_L00_001B19C0 != g_current_map_index) D_00139629 = g_current_map_index;
    RunLevelTransition();
}
