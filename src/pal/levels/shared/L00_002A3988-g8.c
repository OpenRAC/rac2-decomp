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
extern void func_PAL_00292988(int), func_PAL_00292D18(int), func_PAL_00292FC8(int), func_PAL_00292F00(int);
extern int moby_handle_request_slot_state(int);
extern int func_PAL_L00_00305570(int, int);
extern void func_PAL_00295820(void), InitializeHudSlotsAndBuffers(void), func_PAL_0029D6E0(void);
extern void menu_reset_slots(void);
extern int request_begin_slot(int, int, int, int, unsigned char *);
extern void FadeToBlack(int), snd_start_music_stream_no_loop(int, int, int), music_Pause(int);
extern void snd_set_current_buffer_flag(void);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern void func_PAL_002B57D0(void), music_Unpause(void);
extern short func_PAL_002B8898(int);
extern void LoadClassIntoFreeCacheSlot(int);
extern void gfx_process_screen_copy_regions(void), SubmitBufferedDmaChain(void), gfx_swap_packet_buffer(void);
extern void PutDrawBufferSmall(void), gfx_append_gs_packet_tag_b(void), gfx_append_draw_list_header(void);
extern int snd_Pump(void);
extern void func_PAL_002B9BB8(void), func_PAL_L00_00371E28(void), func_PAL_L00_002E7510(void);
extern void func_PAL_L00_00382620(void), func_PAL_L00_003825C8(void);
extern void func_PAL_L00_00372508(void), func_PAL_L00_002E75C8(void);
extern void func_PAL_002F6F08(void), func_PAL_L00_00372EA8(void), func_PAL_0027C968(void), DrawLetterboxBars(void);
extern void func_PAL_002CB710(void), func_PAL_L00_002E7610(void), func_PAL_00287018(void), func_PAL_0027C990(void);
extern void func_PAL_L00_003776E8(void), func_PAL_L00_0037D348(void), func_PAL_002EB800(void);
extern int func_PAL_002EA0B0(void);
extern int func_PAL_L00_002FE148(void), func_PAL_L00_002FE168(void);
extern void math_trap_always(void), level_decrement_counter_clamped(void), math_add_wrapping_counter(void);
extern void func_PAL_00299898(void), map_update_state_machine(void), SetupGifPaging(int);
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
extern void pad_reset_input_state(int), map_fill_buffer(void *), func_PAL_002ED320(void);

/* Clears level state, restores its settings and services frames until loading ends. */
void func_PAL_L00_002A3988(void)
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
    if (D_001A7290 != D_001A7A18) func_PAL_00292988(D_001A7A18);
    {
        int weapon = g_item_slot_to_record[10];
        if (D_001A72C0 != g_weapon_l00_table[weapon].channel)
            func_PAL_00292D18(g_weapon_l00_table[weapon].channel);
    }
    {
        int output = (g_equipment_bits >> 16) & 31;
        if (g_hero_moby_default.output != output) func_PAL_00292FC8(output);
    }
    if (g_hero_moby_default.mode != (g_equipment_bits & 3)) func_PAL_00292F00(g_equipment_bits & 3);
    if (!g_weapon_l00_table[g_item_slot_to_record[g_hero_state.weapon]].active) moby_handle_request_slot_state(10);
    func_PAL_L00_00305570(1, 0);
    func_PAL_00295820();
    InitializeHudSlotsAndBuffers();
    func_PAL_0029D6E0();
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
    if (((int)D_001A7390 * 5 + 2) / 6 > D_0018C360[g_current_map_index].maximum)
        D_0018C360[g_current_map_index].maximum = ((int)D_001A7390 * 5 + 2) / 6;
    D_0018C360[g_current_map_index].visited = D_0018C360[g_current_map_index].visited | (1u << g_current_map_index) | 0x80000000u;
    snd_set_current_buffer_flag();
    sceSifCallRpc(D_001A7248, 3, 0, 0, 0, 0, 0, 0, 0);
    func_PAL_002B57D0();
    if (!D_L00_001A8F00[0]) music_Unpause();
    func_PAL_002B8898(1);
    LoadClassIntoFreeCacheSlot(g_weapon_l00_table[g_item_slot_to_record[D_001A7398]].sound);
    func_PAL_002B8898(1);
    LoadClassIntoFreeCacheSlot(g_weapon_l00_table[g_item_slot_to_record[D_001A7A04]].sound);
    func_PAL_002B8898(1);
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
            func_PAL_002B9BB8();
            func_PAL_L00_00371E28();
            if (D_L00_001A7C80 == 1) {
                T1_COUNT = 0;
                func_PAL_002B9BB8();
                func_PAL_L00_00371E28();
            }
            func_PAL_L00_002E7510();
            break;
        case 8:
            func_PAL_002B9BB8();
            func_PAL_L00_00382620();
            func_PAL_L00_003825C8();
            break;
        case 7:
            func_PAL_002B9BB8();
            func_PAL_L00_00372508();
            func_PAL_L00_002E75C8();
            break;
        case 1:
            func_PAL_002F6F08();
            break;
        case 2:
            func_PAL_002B9BB8();
            func_PAL_L00_00372EA8();
            func_PAL_0027C968();
            DrawLetterboxBars();
            break;
        case 3:
            func_PAL_002B9BB8();
            func_PAL_002CB710();
            func_PAL_L00_002E7610();
            break;
        case 4:
            func_PAL_002B9BB8();
            func_PAL_00287018();
            func_PAL_0027C990();
            break;
        case 5:
            func_PAL_002B9BB8();
            func_PAL_L00_003776E8();
            func_PAL_L00_0037D348();
            break;
        case 6:
            func_PAL_002B9BB8();
            func_PAL_002EA0B0();
            func_PAL_002EB800();
            break;
        case 9:
            func_PAL_002B9BB8();
            func_PAL_L00_002FE148();
            func_PAL_L00_002FE168();
            break;
        case -2: case 10: default:
            math_trap_always();
            break;
        }
        D_L00_001B19C4[0]++;
        level_decrement_counter_clamped();
        if (!D_L00_001A8F00[0]) math_add_wrapping_counter();
        func_PAL_00299898();
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
                    D_L00_001B1680[0] = 25;
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
                        func_PAL_002B9BB8();
                        func_PAL_L00_00371E28();
                    } else if (D_L00_001A8F00[0] == 2 && !D_L00_001BCB24) {
                        func_PAL_002B9BB8();
                        func_PAL_L00_00372EA8();
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
                    func_PAL_002B9BB8();
                    func_PAL_L00_00372EA8();
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
            func_PAL_L00_00305570(0, extra);
            pad_reset_input_state(0);
            snd_start_music_stream_no_loop(sound, 1, 1024);
            InitializeHudSlotsAndBuffers();
        } else {
            func_PAL_002B57D0();
            if (D_L00_001A8F00[0] != oldMode) D_L00_001B19C4[0] = 0;
            if (D_L00_001B19D4[0]) gfx_reset_packet_buffer();
        }
        if (((int)D_001A7390 * 5 + 2) / 6 > D_0018C360[g_current_map_index].maximum)
        D_0018C360[g_current_map_index].maximum = ((int)D_001A7390 * 5 + 2) / 6;
    }
    map_fill_buffer(D_0018D278 + g_current_map_index * 2048);
    if (D_L00_001B19C0 != g_current_map_index) D_00139629 = g_current_map_index;
    func_PAL_002ED320();
}
