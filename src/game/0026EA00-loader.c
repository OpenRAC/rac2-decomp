#include "names.h"
/* func_0026EDE8 (boot only), the boot title loop: it reads the boot archive from disc, waits on
 * the memory-card state machine while the loading screens show, unpacks the archive tables, then
 * runs front-end frames by state D_001A8BB0 until D_001A8B84 is set.
 *
 * A unit of its own for -fcall-used-hi1 -fcall-used-lo1 -fcall-used-accum1 (config/cflags.txt),
 * allowed for this function by the lead maintainer (2026-11-07). Patch 0055 (r5900-no-second-hilo)
 * fixes HI1/LO1/ACCUM1, which lowers loop.c's hoisting threshold from 64 to 61; with 61 the
 * memory-card wait loop cannot hoist -4, %hi(D_0180DA80) and 7 into $fp, $s7 and $s6 as retail
 * does. The three flags restore the unpatched register count for this unit only.
 *
 * What else it takes:
 *   - Memcard() keeps its pointer in a local: without it the wait loop's exit test is at most
 *     LOOP_TEST_THRESHOLD (30) insns at jump1, jump.c copies it in front of the loop, the copy
 *     jumps into the body and loop.c ignores the loop (multiple entry points). Retail enters the
 *     loop with `b` to its test at the bottom.
 *   - func_00288AA0 and func_00288BE8 return values (as their definitions do): the call_value
 *     ends $v0's life, so the D_001A7478 store has fewer sched2 dependents than the a0 move and
 *     reorg puts it into the jal slot ($gp form).
 *   - D_001B1840 and D_001A7200 are scalars: a fixed scalar does not conflict with a varying
 *     struct reference, so the table index chains and the T1 tick accumulation schedule as
 *     retail; the archive offsets are read as members for the same reason.
 *   - `sound = &D_001A63A8` after the D_00189E20 store: sched1 then forms that address before
 *     D_00238C80's, so reload rebuilds the two %hi values in $v1 and $a0 as retail does, while
 *     the stores keep their order (D_001A8BBC = 20 before D_001B16A8 = 20 puts the constant's
 *     last use on D_001B16A8).
 */
#include "common.h"

typedef struct { char *data; int words[3]; } LoaderResource;
typedef struct { int code, count, data, size; } LoaderBank;
typedef struct { int offsets[0x64 / 4]; } LoaderArchive;
typedef struct { char pad[0x18]; LoaderArchive *archive; } LoaderMemory;
typedef struct { char pad[0x32C]; int base; char pad330[0x20]; int offset, count; } LoaderDisc;

/* The memory-card state at D_001393E0 (McState_298F00 in src/game/00298F00.c). */
typedef struct {
    int port, slot, type, free, result, format;
    short status, tries;
    char pad1C[0xA0 - 0x1C];
} BootCard;
typedef struct {
    BootCard card[2];
    char pad140[0x15C - 0x140];
    int state, sub, next_state, next_card;
} BootMemcard;

typedef struct { char pad[0x1A0]; unsigned int pressed; } LoaderPad;
typedef struct { char pad[0x2C]; int count; } LoaderTables;
typedef struct { char pad[0x24CC]; int enabled; } LoaderGame;
typedef struct { char pad[7]; char flag; } LoaderSound;
typedef struct { int active; short *sequence; } LoaderMovie;
typedef struct { char pad[10]; unsigned char index; } LoaderSelection;
typedef struct { char pad[4]; unsigned char mode; char rest[219]; } LoaderOption;
typedef struct { char pad[0x18]; int format; char pad1c[0x14]; int audio; } LoaderSettings;

extern LoaderMemory D_001BAEC0;
extern LoaderDisc g_copy_setup_data;
extern BootMemcard g_memcard_state[];
extern LoaderPad g_pad_state;
extern LoaderTables g_subtitle_state;
extern LoaderGame g_hero_state;
extern LoaderSound g_music_state;
extern LoaderMovie D_001BAD40;
extern LoaderSelection g_item_slot_to_record;
extern LoaderOption g_weapon_table[];
extern LoaderSettings g_hero_moby_default;
extern char D_00238C80[], D_01806380[], D_0180DA80[];
extern int D_00138320[];
extern char *D_001B1604 __attribute__((sda));
extern LoaderResource *g_subtitle_entries __attribute__((sda));
extern LoaderArchive *D_001A7280[] __attribute__((sda));
extern unsigned long long D_001A7200 __attribute__((sda));
extern int D_001A8C88[] __attribute__((sda));
extern int D_001B16A8[] __attribute__((sda)), D_001B16AC[] __attribute__((sda));
extern int g_current_game_mode[] __attribute__((sda)), g_previous_game_mode[] __attribute__((sda));
extern int g_requested_game_mode[] __attribute__((sda)), D_001A8BBC[] __attribute__((sda));
extern int D_001A8B84[] __attribute__((sda)), D_001B1684[] __attribute__((sda)), D_001B1598[] __attribute__((sda));
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern short D_001A7A10[] __attribute__((sda));
extern int D_001A7290[] __attribute__((sda)), D_001A72C0[] __attribute__((sda));
extern int g_equipment_bits[] __attribute__((sda)), g_is_pal_video[] __attribute__((sda)), D_001A72D0[] __attribute__((sda));
extern unsigned short D_001A7AF2[] __attribute__((sda));
extern int D_001A7478 MACRO_ADDR;
extern float D_001B168C MACRO_ADDR;

extern void FlushCache(int);
extern int sceGsSyncV(int);
extern int snd_Pump(void);
extern void snd_set_current_buffer_flag(void);
extern void ShowSplashImage(int);
extern void gfx_draw_splash_screen_frame(int);
extern void menu_fill_shuffled_tile_table(unsigned short *);
extern void ResetGsRegistersPr(void), gfx_render_frame_extra_layers(void), gfx_call_frame_helper_zero(void);
extern void FadeToBlack(int);
extern void gfx_process_screen_copy_regions(void);
extern void math_trap_always(void);
extern float IntToFloat(int);
extern int gfx_query_display_buffer(void);
extern void gfx_append_draw_list_header(void), PutDrawBufferSmall(void), gfx_queue_second_strip_packet(void), UpdateModalState(void);
extern int req_push_queue(unsigned char *, int);
extern int req_launch_queued(void *);
extern void InitializeHudSlotsAndBuffers(void);
extern void level_init_systems(void), InitOnce(void);
extern void func_00291DE0(int *, int);
extern void tex_load_pack_to_vram(int), LoadPackSingleTexture(int), load_disc_table_entry_for_draw(int), LoadDiscTableTexture(int);
extern void hud_load_banks(void);
extern void map_setup_screen(void);
extern void map_update_state_machine(void), mc_update_state(void);
extern void level_init_callbacks(void);
extern int fast_decompress(int, int);
extern int request_begin_slot(int, int, int, int, unsigned char *);
extern int request_end_slot(int, int);
extern void mode_apply_pending_change(void);
extern void snd_start_bank_load(int, int);
extern int load_start_disc_read(int, int, int);
extern short snd_pump_music_and_disc_read(int);
extern void pad_poll_ports(void);
extern void menu_reset_slots(void);
extern void menu_update_pause(void);
extern int UpdatePlaybackScene(void);
extern void transition_draw_background(void);
extern void RunLevelTransition(void);
extern void gfx_reset_buffer_slot_table(void);
extern void mpeg_play_movie(void);
extern void gfx_swap_packet_buffer(void), SubmitBufferedDmaChain(void);
extern void gfx_wait_for_dma_status_bits(unsigned long long);
extern long long tex_upload_blocks_return_setup(int, int, int, int);

static inline BootMemcard *Memcard(void) { BootMemcard *mc = g_memcard_state; return mc; }
static inline int CardType(BootMemcard *mc) { return mc->card[0].type; }
static inline int CardFormat(BootMemcard *mc) { return mc->card[0].format; }
static inline int CardStatus(BootMemcard *mc) { return mc->card[0].status; }
static inline int CardFree(BootMemcard *mc) { return mc->card[0].free; }

void RunBootTitleLoop(void)
{
    LoaderResource *tables[8];
    int counts[8];
    short sequence[32];
    int frames = 0, loaded = 0, state;
    LoaderArchive *archive;
    char *image, *extra;
    float time;

    D_001A8C88[0] = 1;
    InitOnce();
    {
        LoaderMemory *memory = &D_001BAEC0;
        LoaderDisc *disc = &g_copy_setup_data;
        load_start_disc_read((int)memory->archive + 0x400000, disc->offset + disc->base, disc->count);
    }
    while (g_memcard_state->state == 2 && g_memcard_state->next_state < 0) {
        mc_update_state();
        map_update_state_machine();
        sceGsSyncV(0);
    }
    while (g_memcard_state->state != 2 || g_memcard_state->next_state >= 0) {
        mc_update_state();
        map_update_state_machine();
        sceGsSyncV(0);
    }
    for (;;) {
        if (!(CardType(Memcard()) != 2
              || (CardFormat(Memcard()) != 0 && CardStatus(Memcard()) < -1 && CardFree(Memcard()) < 475)))
            break;
        loaded = 1;
        if (g_memcard_state->state < 3 && g_memcard_state->next_state < 0) {
            if (g_memcard_state->card[0].type != 2)
                gfx_draw_splash_screen_frame((int)D_01806380);
            else if (g_memcard_state->card[0].status != -4)
                gfx_draw_splash_screen_frame((int)D_0180DA80);
            if (g_memcard_state->next_state < 0) {
                g_memcard_state->next_state = 7;
                g_memcard_state->next_card = 0;
            }
        }
        pad_poll_ports();
        mc_update_state();
        map_update_state_machine();
        if (frames <= 119)
            frames++;
        sceGsSyncV(0);
        if (frames >= 61) {
            if (g_pad_state.pressed & 0xFFFF0FFF)
                break;
        }
    }
    level_init_systems();
    if (loaded) {
        int i;
        FadeToBlack(5);
        for (i = 29; i >= 0; i--)
            sceGsSyncV(0);
    }
    {
        LoaderMemory *memory = &D_001BAEC0;
        snd_pump_music_and_disc_read(1);
        FlushCache(0);
        fast_decompress((int)memory->archive + 0x400000, (int)memory->archive);
        FlushCache(0);
        gfx_reset_buffer_slot_table();
        archive = memory->archive;
        ShowSplashImage(archive->offsets[0x50 / 4] + (int)archive);
        D_001A7280[2] = memory->archive;
        hud_load_banks();
        snd_start_bank_load(archive->offsets[8 / 4] + (int)archive, 0);
        {
            LoaderBank *bank = (LoaderBank *)(archive->offsets[0] + (int)archive);
            D_001B1604 = (char *)bank + bank->code + bank->size;
            func_00291DE0((int *)((char *)bank + bank->data), bank->count);
        }
    }
    {
        int i, j;
        for (i = 0; i < 6; i++) {
            int *table = (int *)(archive->offsets[0x48 / 4] + (int)archive);
            int *part = (int *)((int)table + table[i]);
            int count = part[0];
            part += 2;
            tables[i] = (LoaderResource *)part;
            counts[i] = count;
            for (j = 0; j < counts[i]; j++)
                tables[i][j].data += (int)tables[i] - 8;
        }
    }
    g_subtitle_state.count = counts[D_001A7BB0[4]];
    g_subtitle_entries = tables[D_001A7BB0[4]];
    image = (char *)(archive->offsets[0x10 / 4] + (int)archive);
    extra = (char *)(archive->offsets[0x60 / 4] + (int)archive);
    {
        int i;
        for (i = 44; i >= 0; i--)
            sceGsSyncV(0);
    }
    FadeToBlack(30);
    {
        int i;
        for (i = 29; i >= 0; i--)
            sceGsSyncV(0);
    }
    ShowSplashImage(archive->offsets[0x58 / 4] + (int)archive);
    {
        LoaderSound *sound;
        g_hero_state.enabled = 1;
        sound = &g_music_state;
        D_001A8BBC[0] = 20;
        D_001B16A8[0] = 20;
        D_001B16AC[0] = (int)D_00238C80;
        sound->flag = 0;
        g_requested_game_mode[0] = -2;
        g_current_game_mode[0] = 0;
        g_previous_game_mode[0] = 0;
        D_001B1684[0] = 0;
    }
    map_setup_screen();
    InitializeHudSlotsAndBuffers();
    level_init_callbacks();
    menu_reset_slots();
    {
        int i;
        for (i = 24; i >= 0; i--)
            sceGsSyncV(0);
    }
    FadeToBlack(30);
    frames = 1800;
    D_001B1598[0] = 0;
    sceGsSyncV(0);
    gfx_query_display_buffer();
    snd_set_current_buffer_flag();
    D_001A7478 = 3;
    req_push_queue((unsigned char *)&D_001BAD40, 0xB2);
    req_launch_queued(&D_001BAD40);
    mode_apply_pending_change();
    while (!D_001A8B84[0]) {
        g_subtitle_entries = tables[D_001A7BB0[4]];
        g_subtitle_state.count = counts[D_001A7BB0[4]];
        /* T1_COUNT, the timer-1 counter register. */
        D_001A7200 += T1_COUNT;
        T1_COUNT = 0;
        gfx_process_screen_copy_regions();
        SubmitBufferedDmaChain();
        gfx_swap_packet_buffer();
        PutDrawBufferSmall();
        gfx_queue_second_strip_packet();
        gfx_append_draw_list_header();
        snd_Pump();
        state = g_current_game_mode[0];
        switch (state) {
        case -1:
        case 0:
            if (g_previous_game_mode[0] == 3 || frames >= 1800) {
                frames = 0;
                menu_fill_shuffled_tile_table((unsigned short *)sequence);
                D_001BAD40.active = 1;
                D_001A7478 = 2;
                D_001BAD40.sequence = sequence;
                req_push_queue((unsigned char *)&D_001BAD40, sequence[1]);
                req_launch_queued(&D_001BAD40);
            } else {
                tex_upload_blocks_return_setup((int)(image + 0x10), D_001A72D0[3], 512, 416);
                request_begin_slot(3, 1, 6, 0, 0);
            }
            break;
        case 1:
            mpeg_play_movie();
            if (extra) {
                int i;
                ShowSplashImage((int)extra);
                for (i = 29; i >= 0; i--)
                    sceGsSyncV(0);
                FadeToBlack(30);
                extra = 0;
            }
            break;
        case 3:
            frames++;
            pad_poll_ports();
            if (D_00138320[0])
                frames = 0;
            menu_update_pause();
            gfx_call_frame_helper_zero();
            if (frames >= 1800) {
                frames = 0;
                request_end_slot(0, 0);
            }
            break;
        case 4:
            pad_poll_ports();
            UpdateModalState();
            gfx_render_frame_extra_layers();
            break;
        case 6:
            pad_poll_ports();
            UpdatePlaybackScene();
            transition_draw_background();
            break;
        default:
            math_trap_always();
            break;
        }
        if (g_current_game_mode[0] != state)
            D_001B1684[0] = 0;
        else
            D_001B1684[0]++;
        mc_update_state();
        map_update_state_machine();
        gfx_wait_for_dma_status_bits(1);
        time = IntToFloat(T1_COUNT);
        D_001B168C = time * (g_is_pal_video[0] ? 0.0000868055578f : 0.000104166669f);
        ResetGsRegistersPr();
        mode_apply_pending_change();
        D_001B1598[0]++;
        sceGsSyncV(0);
    }
    if (D_001A7290[0] != D_001A7A10[4])
        tex_load_pack_to_vram(D_001A7A10[4]);
    if (D_001A72C0[0] != (g_weapon_table + g_item_slot_to_record.index)->mode)
        LoadPackSingleTexture((g_weapon_table + g_item_slot_to_record.index)->mode);
    if (g_hero_moby_default.audio != (D_001A7AF2[0] & 31))
        LoadDiscTableTexture(D_001A7AF2[0] & 31);
    if (g_hero_moby_default.format != (g_equipment_bits[0] & 3))
        load_disc_table_entry_for_draw(g_equipment_bits[0] & 3);
    RunLevelTransition();
}
