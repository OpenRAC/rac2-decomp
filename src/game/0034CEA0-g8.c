#include "ps2_hw.h"
#include "names.h"
extern char g_hud_float_params[];
extern int g_input_block_flag;
extern char *g_bolt_counter_base;
extern int g_radial_menu_layout_x __attribute__((sda));
extern int g_radial_menu_layout_y __attribute__((sda));
extern void UpdateViewContext(void);
extern unsigned int menu_get_label_color_alpha(void *);
extern void radial_menu_layout_items(void *, int, int, int);
extern void menu_noop_hook(void *);
extern void DrawBoltCounterPanel(void *);
extern void text_panel_draw_scaled(void *);
extern void func_0029CB80(void);
/* Draws the item and bolt HUD once, using a temporary setting that is put back afterwards. */
void hud_item_bolt_draw(char *object)
{
    float saved;
    char *camera;
    char *state = g_hud_float_params;
    saved = *(float *)(state + 0xB0);
    *(float *)(state + 0xB0) = 0.62f;
    UpdateViewContext();
    if (g_input_block_flag == 0)
        radial_menu_layout_items(object, g_radial_menu_layout_x, g_radial_menu_layout_y, menu_get_label_color_alpha(object + 0x7A0) >> 24);
    menu_noop_hook(object);
    DrawBoltCounterPanel(object + 0x7A0);
    camera = g_bolt_counter_base + 0x38000;
    *(int *)(camera + 0x7354) = 0;
    *(int *)(camera + 0x7358) = 0;
    text_panel_draw_scaled(object + 0x1FBC);
    func_0029CB80();
    *(float *)(state + 0xB0) = saved;
    UpdateViewContext();
}

extern char *g_movie_player_state[] __attribute__((sda));
extern int ref_L00_0034F690_00 __attribute__((sda));
typedef int (*CleanupCallback)(void);
extern int timer_update_vsync_counters(void);
extern int sceCdSyncS(int);
extern void mpeg_noop_read_buffer_hook(void *);
extern void mpeg_noop(void *);
extern void TerminateThread(int);
extern void DeleteThread(int);
extern void kernel_process_queue_entry_c(int);
extern void RemoveDmacHandler(int, int);
extern int func_00126DC0(CleanupCallback);
extern int mpeg_dec_shutdown(void *);
extern int mpeg_reset_audio_dma(void *);
extern int mpeg_return_true(void *);

/* Shuts down the movie player: stops the decoder, removes its handlers and turns the DMA channel off. */
void mpeg_shutdown_player(void)
{
    sceCdSyncS(0);
    mpeg_noop_read_buffer_hook(g_movie_player_state[0]);
    mpeg_noop(g_movie_player_state[0] + 0xd9168);
    TerminateThread(ref_L00_0034F690_00);
    DeleteThread(ref_L00_0034F690_00);
    kernel_process_queue_entry_c(2);
    RemoveDmacHandler(2, *(int *)(g_movie_player_state[0] + 0xd8000 + 0x10f8));
    func_00126DC0(timer_update_vsync_counters);
    mpeg_dec_shutdown(g_movie_player_state[0] + 0xd9048);
    mpeg_reset_audio_dma(g_movie_player_state[0] + 0xd9100);
    mpeg_return_true(g_movie_player_state[0] + 0xd9040);
    sceCdSyncS(0);
    D_CTRL &= ~2u;
}

extern char *ref_L00_0034EF58_01[] __attribute__((sda));
extern char ref_L00_0034EF58_00[];
extern void STUB_printf(void *, ...);
extern void BuildAspectBlitStrips(int, int);
extern int GetThreadId(void);
extern void ChangeThreadPriority(int, int);
extern int mpeg_start_player(void *, void *, int);
extern int read_mpeg(void *, void *, void *);

/* Plays a full-motion video: sets up the player, plays the stream until it ends or is skipped, then cleans up. Returns 1 if the player skipped it. */
int mpeg_play_movie_2(void *streamSource, void *sourceMode, char *pool, char *state, int mode, int volume)
{
    int result = 0;
    ref_L00_0034EF58_01[0] = pool;
    g_movie_player_state[0] = state;
    STUB_printf(ref_L00_0034EF58_00, 0x38cac0);
    BuildAspectBlitStrips(volume, volume);
    ChangeThreadPriority(GetThreadId(), 1);
    if (mpeg_start_player(streamSource, sourceMode, mode)) {
        result = read_mpeg(g_movie_player_state[0] + 0xd9048, g_movie_player_state[0], g_movie_player_state[0] + 0xd9040);
    }
    mpeg_shutdown_player();
    ref_L00_0034EF58_01[0] = 0;
    g_movie_player_state[0] = 0;
    return result;
}

typedef unsigned long long u64;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned char u8;

extern int g_vram_display_address;
extern int g_movie_buffer_base;
extern void BuildFrameDmaChain(void *, int);

/* FMV GS packet builder: one 0x40-byte header record, then a 0x60-byte record per
   (row, column), then the closing A_B word pair at the end of the run. */
void mpeg_build_frame_packet(void *packet, int textureAddress, int height, int width, int bufferIndex)
{
    u8 *cursor = (u8 *)packet;
    int rows = height >> 4;
    int cols = width >> 4;
    int i, j;
    u64 c00, c10, c18, c28, c38, c40;
    u32 off, addr;

    *(u64 *)(cursor + 0x00) = 0x10000003;
    *(u64 *)(cursor + 0x08) = 0;
    *(u64 *)(cursor + 0x10) = 0x1000000000000002ULL;
    *(u64 *)(cursor + 0x18) = 0xE;
    *(u64 *)(cursor + 0x20) = ((ll)g_vram_display_address >> 8) << 32 | 0x8000000000000LL;
    *(u64 *)(cursor + 0x28) = 0x50;
    *(u64 *)(cursor + 0x30) = 0x1000000010ULL;
    *(u64 *)(cursor + 0x38) = 0x52;

    cursor += 0x40;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            c00 = 0x10000004;
            c10 = 0x1000000000000002ULL;
            c18 = 0xE;
            c28 = 0x51;
            c38 = 0x53;
            c40 = 0x0800000000000040ULL;
            *(u64 *)(cursor + 0x00) = c00;
            *(u64 *)(cursor + 0x08) = 0;
            *(u64 *)(cursor + 0x10) = c10;
            *(u64 *)(cursor + 0x18) = c18;
            *(u64 *)(cursor + 0x20) = (((u64)(i << 4)) << 32) | (((u64)(j << 4)) << 48);
            *(u64 *)(cursor + 0x28) = c28;
            *(u64 *)(cursor + 0x30) = 0;
            *(u64 *)(cursor + 0x38) = c38;
            *(u64 *)(cursor + 0x40) = c40;
            *(u64 *)(cursor + 0x48) = 0;
            *(u32 *)(cursor + 0x50) = 0x30000040;
            *(u32 *)(cursor + 0x54) = textureAddress & 0x0FFFFFFF;
            *(u64 *)(cursor + 0x58) = 0;
            textureAddress += 0x400;
            cursor += 0x60;
        }
    }

    *(u32 *)(cursor + 0x00) = 0x20000000;
    off = (bufferIndex << 14) + 0x1C81C0;
    addr = g_movie_buffer_base + off;
    *(u32 *)(cursor + 0x0C) = 0;
    *(u32 *)(cursor + 0x08) = 0;
    *(u32 *)(cursor + 0x04) = addr;
    BuildFrameDmaChain((void *)(u32)(g_movie_buffer_base + off), 1);
}

extern char g_str_mpeg_feed_callback[];
extern void mpeg_dec_get_free_regions(unsigned char *, int *, int *, int *, int *);
extern int mpeg_dec_add_timestamp(char *, unsigned long long, unsigned long long, int, int);
extern void mpeg_dec_add_pending_bytes(char *, int);
extern void mpeg_set_debug_value(int);
extern int mpeg_copy_split_buffer(u32, int, u32, int, u32, int, int, int);

/* Callback that hands the next piece of movie data to the decoder and reports whether any data was taken. */
int mpeg_feed_decoder_callback(u8 *unused, char *src, char *dst)
{
    int first_address, first_count, second_address, second_count;
    int used = *(int *)(src + 8);
    int remain = *(int *)(src + 0xC);
    int size;
    int second;
    int result;

    size = (int)dst + *(int *)(dst + 0x50008);
    size -= used;
    if (remain < size)
        size = remain;
    second = remain - size;
    mpeg_dec_get_free_regions((unsigned char *)(g_movie_player_state[0] + 0xD9048),
                  &first_address, &first_count, &second_address, &second_count);
    result = mpeg_copy_split_buffer((first_address & 0x0FFFFFFF) | 0x20000000, first_count,
                           (second_address & 0x0FFFFFFF) | 0x20000000, second_count,
                           used, size, (int)dst, second);
    if (result > 0) {
        if (mpeg_dec_add_timestamp(g_movie_player_state[0] + 0xD9048,
                          *(unsigned long long *)(src + 0x10),
                          *(unsigned long long *)(src + 0x18),
                          first_address, result) == 0)
            mpeg_set_debug_value((int)g_str_mpeg_feed_callback);
    }
    mpeg_dec_add_pending_bytes(g_movie_player_state[0] + 0xD9048, result);
    return result > 0;
}

extern void gfx_draw_screen_element_stored(void *);
extern void hud_draw_colored_quad_widget(void *);
extern void text_label_draw(void *);
extern float *object_get_second_field(void *);
extern float *object_get_first_field(void *);
extern unsigned int *object_get_fourth_field(void *);
extern void DrawSegmentedRingMeter(void *);
extern unsigned long GetEffectTextureDescriptor(int);
extern void FontPrintScaled(float, float, unsigned long, char *, int, float, unsigned long, unsigned char *);
extern int text_draw_centered_large(int, int, unsigned long, char *, int);
extern int sprintf(char *, char *, ...);
extern int g_notice_owner[] __attribute__((sda));
extern int g_player_bolts[] __attribute__((sda)); /* the player's bolts */
extern unsigned char g_language_settings[] __attribute__((sda));
extern unsigned char g_bolt_multiplier[] __attribute__((sda)); /* bolt multiplier */
extern char g_str_apostrophe[], g_str_period[], g_str_multiplier_format[]; /* "'", ".", "x%d" */
extern int g_movie_text_x __attribute__((sda));
extern int g_movie_text_y __attribute__((sda));
extern unsigned int g_mpeg_foreground_color __attribute__((sda));

/* A g++ 2.95 vtable entry: this-adjustment, index, function. */
typedef struct HudVEntry {
    short delta;
    short index;
    void (*fn)(void *);
} HudVEntry;

typedef struct HudElem4C {
    char pad0[0x30];
    HudVEntry *vtable; /* 0x30 */
    char pad34[0x18];
} HudElem4C;

typedef struct HudElem3C {
    char pad0[0x30];
    HudVEntry *vtable; /* 0x30 */
    char pad34[0x8];
} HudElem3C;

typedef struct HudText {
    char pad0[0x34];
    unsigned char *metrics; /* 0x34 */
    long long style;        /* 0x38 */
} HudText;

typedef struct HudOwner {
    HudElem4C top[3];       /* 0x0 */
    char pad0E4[0x1C];
    char panel100[0x48];    /* 0x100 */
    char panel148[0x3C];    /* 0x148 */
    HudElem4C mid[2];       /* 0x184 */
    char pad21C[0x1C];
    HudText text;           /* 0x238 */
    char pad240[0x280 - 0x238 - sizeof(HudText)];
    char panel280[0x40];    /* 0x280 */
    HudElem4C side[2];      /* 0x2C0 */
    HudElem4C a[8];         /* 0x358 */
    HudElem4C b;            /* 0x5B8 */
    HudElem3C c[8];         /* 0x604 */
    char pad7E4[4];
    char final[4];          /* 0x7E8 */
} HudOwner;

/* Draws the bolt counter panel: thousands separators by language (as RAC1's
 * bolt counter) and the "x%d" multiplier. The vtable pointers are read through
 * &a[i] + 0x30 so that every induction value is object-relative, and each
 * loop keeps its own vtable local, as in RAC2's DRAW idiom (00337210.c). */
void DrawBoltCounterPanel(void *arg)
{
    HudOwner *object = arg;
    char separator[32];
    char multiplierText[16];
    float *scale;
    float x, y, step;
    unsigned int color;
    int foreground, shadow;
    int i, j, digits, n, apostrophe, yoffset, xoffset;

    gfx_draw_screen_element_stored(&object->top[0]);
    gfx_draw_screen_element_stored(&object->top[1]);
    gfx_draw_screen_element_stored(&object->top[2]);
    hud_draw_colored_quad_widget(object->panel148);
    text_label_draw(object->panel100);
    if (!g_notice_owner[0]) {
        HudElem4C *left = &object->side[0];
        HudElem4C *right = &object->side[1];
        gfx_draw_screen_element_stored(left);
        gfx_draw_screen_element_stored(right);
        { float *value = object_get_second_field(left); *value = -*value; }
        { float *value = object_get_second_field(right); *value = -*value; }
        gfx_draw_screen_element_stored(left);
        gfx_draw_screen_element_stored(right);
        { float *value = object_get_second_field(left); *value = -*value; }
        { float *value = object_get_second_field(right); *value = -*value; }
        for (i = 0; i < 8; i++) {
            HudVEntry *vt = *(HudVEntry **)((char *)&object->a[i] + 0x30);
            vt[1].fn((char *)&object->a[i] + vt[1].delta);
        }
        for (j = 0; j < 8; j++) {
            HudVEntry *vt = *(HudVEntry **)((char *)&object->c[j] + 0x30);
            vt[1].fn((char *)&object->c[j] + vt[1].delta);
        }
        gfx_draw_screen_element_stored(&object->b);
        *object_get_fourth_field(&object->b) = 0x70FFFEED;
    }
    gfx_draw_screen_element_stored(&object->mid[0]);
    gfx_draw_screen_element_stored(&object->mid[1]);
    text_label_draw(&object->text);
    hud_draw_colored_quad_widget(object->panel280);
    x = object_get_first_field(&object->text)[0];
    y = object_get_first_field(&object->text)[1];
    x += 32.0f;
    y += -10.0f;
    color = *object_get_fourth_field(&object->text);
    digits = 1;
    n = g_player_bolts[0];
    while (n >= 10) { n /= 10; digits++; }
    apostrophe = g_language_settings[4] != 3 && g_language_settings[4] != 5;
    sprintf(separator, apostrophe ? g_str_apostrophe : g_str_period);
    yoffset = apostrophe ? 21 : 10;
    xoffset = apostrophe ? -34 : -29;
    step = 3.0f;
    if (step < (float)digits) {
        float start = x + (float)xoffset;
        do {
            HudText *t = &object->text;
            float drawX = start - (float)(int)(step * 11.6f);
            long long style;
            unsigned long texture;
            step += 3.0f;
            scale = object_get_second_field(t);
            style = t->style;
            texture = GetEffectTextureDescriptor((int)style);
            FontPrintScaled(drawX, y + (float)yoffset, color, separator, -1, *scale, texture, t->metrics);
        } while (step < (float)digits);
    }
    if (g_bolt_multiplier[0] >= 2) {
        sprintf(multiplierText, g_str_multiplier_format, g_bolt_multiplier[0]);
        foreground = (g_mpeg_foreground_color & 0xFFFFFF) | (color & 0xFF000000);
        shadow = color & 0xFF000000;
        text_draw_centered_large(g_movie_text_x, g_movie_text_y + 2, shadow, multiplierText, -1);
        text_draw_centered_large(g_movie_text_x + 2, g_movie_text_y, shadow, multiplierText, -1);
        text_draw_centered_large(g_movie_text_x + 2, g_movie_text_y + 2, shadow, multiplierText, -1);
        text_draw_centered_large(g_movie_text_x, g_movie_text_y, foreground, multiplierText, -1);
    }
    DrawSegmentedRingMeter(object->final);
}
