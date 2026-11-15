#include "include_asm.h"
#include "names.h"

typedef struct MovieAdpcmDecoder {
    int mode;           /* 0x0 */
    char pad4[0x14];
    int nch;            /* 0x18 */
    int chunk;          /* 0x1C */
    char pad20[0x14];
    unsigned char *buf; /* 0x34 */
    int rd;             /* 0x38 */
    int cnt;            /* 0x3C */
    int size;           /* 0x40 */
    char pad44[0xC];
    int bytes;          /* 0x50 */
    char pad54[0xC];
    int pos;            /* 0x60 */
} MovieAdpcmDecoder;


extern void func_L00_0042BCF8_1(void *p);

extern void hud_construct(void *p);

extern void func_L00_0042BFF8_7(void *p);

extern void text_panel_shutdown(void *p);

extern char *F476e86a4_FUN_00335E10(char *p);

extern void F476e86a4_FUN_003364C8(char *p, int a, int b);

extern void F476e86a4_FUN_00336508(char *p, int a, int b);

extern void F476e86a4_FUN_00336CE0(char *p, int a);

/* Qwen draft (branch qwen/autonomy, 56f9a59b), checked by tools/check.py */
void text_panel_update_mode(int);

/* Qwen draft (branch qwen/autonomy, 576906e6), checked by tools/check.py */
void text_panel_draw_scaled(int);

extern char F45821cfb_D_001C2740[];

extern void F45821cfb_FUN_00282C88(char *);

extern char F0a76d85b_D_001B5200[];

extern void F0a76d85b_FUN_00283360(char *p);

extern void F0a76d85b_FUN_00279D18(void);

extern void UpdateItemStatusHud(void *);
extern void hud_update_subobject_primary(int);
extern void func_0029CB58(void);

typedef int s32;

/* lot15 -- first CALL-BEARING body: the call family is now open. */
extern void RotateThreadReadyQueue(s32);

/* lot15 -- two twins of the first call-bearing body (same form, 32 bytes).
   The matched wrappers use a `nop` delay slot and return 1; the slot alone does not establish the callee parameter list. */
extern void snd_send_cmd3c();

typedef unsigned char u8;

extern void snd_send_cmd3e(s32, s32, s32, s32, s32);

extern s32 snd_send_cmd3d(void);

extern s32 FlushCache(s32);

extern s32 sceSifSetDma(s32 *, s32);

extern s32 sceSifDmaStat(s32);

extern s32 snd_send_cmd5a(s32, s32);

extern volatile unsigned int D_L00_001AEB10 __attribute__((sda));

typedef struct { int pos; int used; int size; } Ring;

extern void ui_return_self(void *);
extern void table_relocate_entries(void *);
extern void pool_init_cells(void *, int, void *, int);
extern void load_read_disc_with_pause(void *, void *, int);
extern void memset(void *, int, int);
extern char *D_001A8CFC[] __attribute__((sda));
typedef struct { char pad0[0x36C]; int offset; char pad370[0x1348]; char *data; int size; } InitData;
extern InitData g_copy_setup_data;
extern void menu_init_seven_labels(void *);
extern void menu_screen_large_init_parts(void *);
extern void menu_screen_init_parts(void *);
extern void grid_menu_init_widgets(void *);
extern void radial_menu_construct(void *);
extern void list_screen_destroy(void *);
extern void mission_screen_init_parts(void *);
extern void map_screen_destroy(void *);
extern void frame_text_page_destroy(void *);
extern void tab_menu_construct(void *);
extern void menu_init_widgets(void *);
extern void simple_list_page_destroy(void *);
extern void small_menu_construct(void *);
extern void menu_return_object(void *);
extern void mission_screen_shutdown(void *);
extern void single_toggle_b_destroy(void *);
extern void onoff_menu_destroy(void *);
extern void four_option_menu_destroy(void *);
extern void two_toggle_a_destroy(void *);
extern void single_toggle_a_destroy(void *);
extern void map_screen_destroy_prompt_bar(void *);
extern void screen_adjust_menu_destroy(void *);
extern void menu_pass_through_handle(void *);
extern void list_menu_construct_parts(void *);
extern void small_list_menu_construct(void *);
extern void two_toggle_b_destroy(void *);
extern void single_toggle_c_destroy(void *);
extern void single_toggle_d_destroy(void *);
extern void list_page_destroy(void *);
extern void title_screen_destroy(void *);
extern void records_screen_init(void *, void *, void *);
extern void menu_page_construct_with_rows(void *, void *);
extern void item_grid_menu_init(void *, void *);
extern void selection_menu_init(void *, void *);
extern void grid_menu_construct(void *, void *);
extern void InitRadialMenu(void *, void *);
extern void list_screen_init(void *, void *);
extern void grid_menu_init(void *, void *);
extern void mission_screen_init(void *, void *);
extern void tab_menu_init(void *, void *);
extern void item_menu_construct(void *, void *);
extern void map_screen_init(void *, void *);
extern void info_panel_init(void *, void *);
extern void simple_page_init(void *, void *);
extern void menu_clear_entries(void *);
extern void title_screen_init_labels(void *, void *);
extern void two_toggle_b_init(void *, void *);
extern void four_option_menu_init(void *, void *);
extern void popup_init(void *, void *);
extern void prompt_menu_init(void *, void *);
extern void audio_menu_init(void *, void *);
extern void single_toggle_a_init(void *, void *);
extern void screen_adjust_menu_init(void *, void *);
extern void onoff_menu_init(void *, void *);
extern void list_menu_reset_attach_items(void *, void *);
extern void small_list_menu_init(void *, void *);
extern void list_menu_init(void *, void *);
extern void single_toggle_c_init(void *, void *);
extern void single_toggle_d_init(void *, void *);
extern void single_toggle_e_init(void *, void *);
extern void list_page_init(void *, void *);


/* func_0034CEA0 is defined in 0034CEA0-menu-g8.c. */

/* func_0034DB98 is in 0034CEA0-g8.c. */


/* walks 26 consecutive 72-byte records calling one leaf per record, then calls four more leaves on fixed offsets of the same object and returns the object pointer */
/* Sets up the menu part objects: 26 item records and four extra pieces. */
unsigned char *menu_init_level_parts(unsigned char *a0)
{
    unsigned char *p;
    int i;

    for (i = 25, p = a0; i != -1; i--) {
        func_L00_0042BCF8_1(p);
        p += 72;
    }
    func_L00_0042BCF8_1(a0 + 1872);
    hud_construct(a0 + 1952);
    func_L00_0042BFF8_7(a0 + 7472);
    text_panel_shutdown(a0 + 7532);
    text_panel_shutdown(a0 + 8124);
    return a0;
}


/* Does nothing. */
void menu_noop_hook(void)
{
}

/* Moves one radial menu item to a screen position and draws it. */
void radial_menu_place_item(char *a0, int a1, int a2, int a3, int t0)
{
    char *base = a0 + a1 * 72;
    float *p;
    char *vt;

    p = (float *)F476e86a4_FUN_00335E10(base);
    p[0] = (float)a2;
    p = (float *)F476e86a4_FUN_00335E10(base);
    p[1] = (float)a3;
    F476e86a4_FUN_003364C8(base, t0, t0);
    F476e86a4_FUN_00336508(base, t0, t0);
    F476e86a4_FUN_00336CE0(base, t0 << 24);
    vt = *(char **)(base + 48);
    (*(void (**)(char *))(vt + 12))(base + *(short *)(vt + 8));
}




/* Updates a part of the HUD stored inside this object. */
void hud_update_subobject_primary(int param_1)
{
  text_panel_update_mode(param_1 + 0x1d6c);
}

/* Updates another part of the HUD stored inside this object. */
void hud_update_subobject_alt(int param_1)
{
  text_panel_draw_scaled(param_1 + 0x1d6c);
  return;
}



/* Returns the object it was given, unchanged. */
void *menu_return_object_unchanged(void *object) {
    return object;
}

/* Clears the menu memory block and sets up every menu screen inside it. */
char *menu_system_init(char *object)
{
    int i;
    int size;
    char *end;
    int *clear = (int *)(object + 4);
    char *root;
    char *part0;
    char *part1;
    char *part2;
    char *part3;
    char *part4;
    char *part5;
    char *part6;
    char *part7;
    char *part8;
    char *part9;
    char *part10;
    char *part11;
    char *part12;
    char *part13;
    char *part14;
    char *part15;
    char *part16;
    char *part17;
    char *part18;
    char *part19;
    char *part20;
    char *part21;
    char *part22;
    char *part23;
    char *part24;
    char *part25;
    char *part26;
    char *part27;
    char *part28;
    char *part29;
    char *part30;
    for (i = 0x86F; i != -1; i--) {
        clear[0] = 0; clear[1] = 0; clear[2] = 0; clear[3] = 0;
        clear += 4;
    }
    root = object + 0x36F10;
    ui_return_self(root);
    part0 = object + 0x36F28;
    menu_init_level_parts(part0);
    part1 = object + 0x39140;
    menu_init_seven_labels(part1);
    part2 = object + 0x39590;
    menu_screen_large_init_parts(part2);
    part3 = object + 0x39A98;
    menu_screen_init_parts(part3);
    part4 = object + 0x39F38;
    grid_menu_init_widgets(part4);
    part5 = object + 0x3A388;
    radial_menu_construct(part5);
    part6 = object + 0x3ADE8;
    list_screen_destroy(part6);
    part7 = object + 0x3B1F0;
    mission_screen_init_parts(part7);
    part8 = object + 0x3B490;
    map_screen_destroy(part8);
    part9 = object + 0x3B7C0;
    frame_text_page_destroy(part9);
    part10 = object + 0x3BE08;
    tab_menu_construct(part10);
    part11 = object + 0x3C108;
    menu_init_widgets(part11);
    part12 = object + 0x3C440;
    simple_list_page_destroy(part12);
    part13 = object + 0x3C738;
    small_menu_construct(part13);
    part14 = object + 0x3C950;
    menu_return_object(part14);
    part15 = object + 0x3CAA8;
    mission_screen_shutdown(part15);
    part16 = object + 0x3CDB0;
    single_toggle_b_destroy(part16);
    part17 = object + 0x3D060;
    onoff_menu_destroy(part17);
    part18 = object + 0x3D310;
    four_option_menu_destroy(part18);
    part19 = object + 0x3D5C0;
    two_toggle_a_destroy(part19);
    part20 = object + 0x3D900;
    single_toggle_a_destroy(part20);
    part21 = object + 0x3DBB0;
    map_screen_destroy_prompt_bar(part21);
    part22 = object + 0x3DE60;
    screen_adjust_menu_destroy(part22);
    part23 = object + 0x3E110;
    menu_pass_through_handle(part23);
    part24 = object + 0x3E1D8;
    list_menu_construct_parts(part24);
    part25 = object + 0x3E430;
    small_list_menu_construct(part25);
    part26 = object + 0x3E5A8;
    two_toggle_b_destroy(part26);
    part27 = object + 0x3E858;
    single_toggle_c_destroy(part27);
    part28 = object + 0x3EB08;
    single_toggle_d_destroy(part28);
    part29 = object + 0x3EDB8;
    list_page_destroy(part29);
    part30 = object + 0x3F138;
    title_screen_destroy(part30);
    size = 0x3F490;
    end = object + size;
    D_001A8CFC[0] = object;
    *(char **)object = (char *)(((int)end + 3) & -4);
    *(int *)(object + 0x3F348) = size;
    load_read_disc_with_pause(object + 0x8710, g_copy_setup_data.data + g_copy_setup_data.offset, g_copy_setup_data.size);
    table_relocate_entries(object + 0x8710);
    pool_init_cells(root, 16, object + 4, 0x8700);
    records_screen_init(part0, object, root);
    *(int *)(object + 0x3F34C) = 0;
    *(int *)(object + 0x3F350) = 0;
    *(int *)(object + 0x3F354) = 0;
    *(int *)(object + 0x3F358) = 0;
    menu_page_construct_with_rows(part1, root);
    item_grid_menu_init(part2, root);
    selection_menu_init(part3, root);
    grid_menu_construct(part4, root);
    InitRadialMenu(part5, root);
    list_screen_init(part6, root);
    grid_menu_init(part13, root);
    mission_screen_init(part7, root);
    tab_menu_init(part10, root);
    item_menu_construct(part11, root);
    map_screen_init(part8, root);
    info_panel_init(part9, root);
    simple_page_init(part12, root);
    menu_clear_entries(part14);
    title_screen_init_labels(part30, root);
    two_toggle_b_init(part16, root);
    four_option_menu_init(part17, root);
    popup_init(part15, root);
    two_toggle_b_init(part16, root);
    four_option_menu_init(part17, root);
    prompt_menu_init(part18, root);
    audio_menu_init(part19, root);
    single_toggle_a_init(part20, root);
    screen_adjust_menu_init(part21, root);
    onoff_menu_init(part22, root);
    list_menu_reset_attach_items(part23, root);
    small_list_menu_init(part25, root);
    list_menu_init(part24, root);
    single_toggle_c_init(part26, root);
    single_toggle_d_init(part27, root);
    single_toggle_e_init(part28, root);
    list_page_init(part29, root);
    *(int *)(object + 0x3F364) = 0;
    *(int *)(object + 0x3F368) = 0;
    *(int *)(object + 0x3F36C) = 0;
    memset(object + 0x3F370, 0, 32);
    memset(object + 0x3F390, 0, 256);
    return object;
}

/* The retail caller passes an owner to both setup helpers; these bodies use resident state. */
/* Sets the light directions and colors used by the menus. */
void hud_init_lighting_colors(void *owner)
{
    float *p = (float *)F45821cfb_D_001C2740;

    p[224] = 0.4f;
    p[225] = 0.8f;
    p[226] = 1.2f;
    *(int *)&p[227] = 0;
    p[228] = 0.577f;
    p[229] = 0.577f;
    p[230] = -0.577f;
    *(int *)&p[231] = 0;
    F45821cfb_FUN_00282C88((char *)&p[232]);
    F45821cfb_FUN_00282C88((char *)&p[236]);
}

/* Resets some menu drawing values to zero. */
void hud_reset_render_state(void *owner)
{
    char *p = F0a76d85b_D_001B5200;

    *(int *)(p + 320) = 0;
    *(int *)(p + 324) = 0;
    *(int *)(p + 328) = 0;
    F0a76d85b_FUN_00283360(p + 880);
    F0a76d85b_FUN_00279D18();
}


/* The two "slot" sub-objects of a level object: each holds an index into the
   entry table, and the entry gives the packet the slot writes to. */
typedef unsigned int u32;

typedef struct {
    u8 pad00[8];
    u8 f08;
    u8 pad09[0x3f];
    u32 *f48[8];
} EntryTable;

typedef struct {
    u8 pad00[0x10];
    u8 f10;
    u8 pad11[2];
    u8 f13;
    u8 pad14[8];
    u32 f1c[8];
} Entry;

typedef struct {
    u8 pad00[0x24];
    EntryTable *f24;
    u8 pad28[0x18];
    u8 f40;
    u8 f41;
    u8 f42;
    u8 f43;
    u8 pad44[0x14];
    char *f58;
    char *f5c;
} SlotObject;

extern void stub_empty_16(char *, long long);
extern void func_002A05A8(char *);
extern void func_002A1130(u32 *, u32, long long, u32);
extern void func_002A0F48(char *);

/* Links two menu slots to their picture data so they can be drawn. */
void menu_attach_slot_packets(char *obj)
{
    char *sub = obj + 0xC00;
    SlotObject *s = (SlotObject *)sub;

    stub_empty_16(sub, 0);
    func_002A05A8(sub);
    if (s->f42 != 0xFF) {
        EntryTable *table = s->f24;
        Entry *entry = table->f48[s->f42];
        u32 *target = (u32 *)((char *)&entry->f1c[entry->f10] + entry->f13 * 4);
        func_002A1130(target, entry->f1c[s->f40], (long long)obj, table->f08);
        s->f58 = obj;
    }
    if (s->f43 != 0xFF) {
        EntryTable *table = s->f24;
        Entry *entry = table->f48[s->f43];
        u32 *target = (u32 *)((char *)&entry->f1c[entry->f10] + entry->f13 * 4);
        func_002A1130(target, entry->f1c[s->f41], (long long)(obj + 0x600), table->f08);
        s->f5c = obj + 0x600;
    }
    func_002A0F48(sub);
}

extern volatile int g_screen_offset_x __attribute__((sda));
extern volatile int g_screen_offset_y __attribute__((sda));
extern char D_L00_001AC820[];
extern char *D_L00_001B2608[] __attribute__((sda));
extern void mem_fast_helper_c(void *, void *, int);
extern void tex_upload_object_textures(void *, int);
/* Draws a menu sprite twice, first shifted for a shadow, then in place. */
void gfx_draw_shadowed_sprite(void *unused, char *object)
{
    char *packet = D_L00_001AC820;
    *(int *)(packet + 0x20) = g_screen_offset_x + *(short *)(object + 0xB4);
    *(int *)(packet + 0x24) = g_screen_offset_y + *(short *)(object + 0xB6);
    mem_fast_helper_c(D_L00_001B2608[0], packet, 48);
    D_L00_001B2608[0] += 48;
    tex_upload_object_textures(object, 1);
    *(int *)(packet + 0x20) = g_screen_offset_x;
    *(int *)(packet + 0x24) = g_screen_offset_y;
    mem_fast_helper_c(D_L00_001B2608[0], packet, 48);
    D_L00_001B2608[0] += 48;
}




/* func_0034F048 is in 0034CEA0-read-mpeg.c. */

/* Starts the movie sound transfer. */
void mpeg_start_decoder_dma(void) {
    RotateThreadReadyQueue(1);
}

extern char *g_movie_player_state[] __attribute__((sda));
extern int mpeg_is_audio_primed(u8 *);

/* Tells whether the movie sound buffer has filled up enough. */
int mpeg_is_audio_buffer_full(void) {
    return mpeg_is_audio_primed((u8 *)(g_movie_player_state[0] + 0xD9100));
}

/* func_0034F408 is in 0034CEA0-movie-init.c. */

extern char D_001AE820[];
extern void STUB_printf(void *, int);

/* Passes a number on to a debug print helper. */
void mpeg_set_debug_value(int value) {
    STUB_printf(D_001AE820, value);
}

extern char *g_movie_player_state[] __attribute__((sda));
extern void mpeg_update_audio_if_active(int *);

/* Keeps the movie sound playing if it is active. */
void proceedAudio(void) {
    mpeg_update_audio_if_active((int *)(g_movie_player_state[0] + 0xD9100));
}


/* Resets the movie sound transfer and reports success. */
s32 mpeg_reset_audio_dma(void) {
    snd_send_cmd3c();
    return 1;
}


/* Starts playing the movie sound. */
void mpeg_start_audio_playback(u8 *decoder) {
    snd_send_cmd3e(*(s32 *)(decoder+0x48), *(s32 *)(decoder+0x4c) / 1024 * 1024,
                *(s32 *)(decoder+0x5c), *(s32 *)(decoder+0x14), *(s32 *)(decoder+0x18));
    *(s32 *)decoder = 2;
}

/* Stops the movie sound and clears its counters. */
void mpeg_stop_audio_playback(u8 *decoder) {
    snd_send_cmd3d();
    *(volatile s32 *)(decoder + 0x5c) = 0;
    *(volatile s32 *)(decoder + 0x00) = 0;
    *(volatile s32 *)(decoder + 0x30) = 0;
    *(volatile s32 *)(decoder + 0x38) = 0;
    *(volatile s32 *)(decoder + 0x3c) = 0;
    *(volatile s32 *)(decoder + 0x44) = 0;
    *(volatile s32 *)(decoder + 0x50) = 0;
    *(volatile s32 *)(decoder + 0x58) = 0;
}

/* Works out where new movie sound data can be written in the ring buffer. */
void mpeg_get_audio_write_pointers(s32 *state,s32 *outPtr1,s32 *outLen1,s32 *outPtr2,s32 *outLen2) {
 s32 offset,wanted;
 if(state[0]==0) {
  if(state[1]!=4) {
   *outPtr1=(s32)((u8 *)state+(state[12]+8));
   *outLen1=0x28-state[12]; *outPtr2=state[13]; *outLen2=state[16];
   return;
  }
  *outPtr1=state[13]; *outLen1=state[16];
  clear: *outPtr2=0; *outLen2=0; return;
 }
 wanted=state[16]-state[15];offset=state[14];
 if(state[16]-offset>=wanted) {
  *outPtr1=state[13]+offset; *outLen1=wanted; goto clear;
 }
 *outPtr1=state[13]+offset;
 *outLen1=state[16]-state[14]; *outPtr2=state[13];
 *outLen2=wanted-(state[16]-state[14]);
}

int audioDecEndPut(s32 *state,s32 amount) {
    if(state[0]==0) {
        if(state[1]!=4) {
            s32 room=40-state[12];
            s32 taken=amount;
            if(room<amount) taken=room;
            state[12]+=taken;
            if(state[12]>39) state[0]=1;
            amount-=taken;
        } else state[0]=1;
    }
    state[16]=state[16]/1024*1024;
    state[14]=(state[14]+amount)%state[16];
    state[15]+=amount;
    state[17]+=amount;
    return state[17];
}

/* true when the counter has reached 0x1000; byte-identical across all 27 levels. */
s32 mpeg_is_audio_primed(u8 *a0) { return *(s32 *)(a0 + 0x50) >= 0x1000; }

extern void mpeg_send_audio_blocks(void *);

/* Sends movie sound data if the player is running. */
void mpeg_update_audio_if_active(int *object) {
    if (object[0] != 0)
        mpeg_send_audio_blocks(object);
}

/* Sends one block of sound data to the sound chip and waits until it is done. */
void mpeg_send_audio_block_to_spu(u8 *a0, s32 a1, s32 a2, s32 a3) {
    s32 dma[4], id;
    ((void (*)(s32))FlushCache)(0);
    dma[0] = a1; dma[1] = *(s32 *)(a0+0x48); dma[2] = a2; dma[3] = 0;
    do { id = sceSifSetDma(dma,1); } while (id == 0);
    while (sceSifDmaStat(id) >= 0) {}
    snd_send_cmd5a(a2,a3);
}

/* sendADPCM(_AudioDec *) */
extern s32 D_001B23D4 __attribute__((section(".sdata")));
extern s32 snd_send_cmd5b(void);

/* Feeds the movie sound data to the sound chip in blocks, one per channel. */
void mpeg_send_audio_blocks(void *object) {
    s32 *o = object;
    s32 t = 0;
    s32 next, i, count;
    u8 *src;
    u8 *dst;

    switch (o[0]) {
    case 1:
        if (o[15] < 0x1000)
            return;
        t = 0x1000 - o[20];
        break;
    case 2:
        t = (snd_send_cmd5b() - o[24]) & 0xFFF;
        break;
    case 3:
        return;
    default:
        break;
    }
    while (t >= 0x400 && o[15] >= o[6] * 1024) {
        next = t - 0x400;
        for (i = 0; i < o[6]; i++) {
            count = 0;
            src = (u8 *)o[13] + (o[14] - o[15] + o[16]) % o[16];
            src += i * o[7];
            dst = (u8 *)D_001B23D4;
            do {
                s32 k;
                for (k = 0; k < o[7]; k++) {
                    *dst++ = *src++;
                    count++;
                }
                src += o[7] * (o[6] - 1);
            } while (count < 0x400);
            if (o[24] + 0x400 == 0x1000)
                ((u8 *)D_001B23D4)[0x3F1] = 3;
            if (o[24] == 0) {
                u8 *p = (u8 *)D_001B23D4;
                p[1] = 6;
                p[0x11] = 2;
            }
            mpeg_send_audio_block_to_spu((u8 *)o, D_001B23D4, 0x400, (i << 12) + o[24]);
        }
        t = next;
        o[15] -= o[6] * 1024;
        o[24] = (o[24] + 0x400) % 0x1000;
        o[20] += 0x400;
    }
}

/* func_0034FE18 is in 0034CEA0-g8.c. */

/* func_0034FFC0 is defined in 0034FFC0.c. */

/* func_00350190 is defined in 00350190.c. */

extern int sceGsSyncV(int);
extern int g_widescreen_flag __attribute__((sda));
extern volatile int D_001AE7D0[] __attribute__((sda));
extern volatile int D_001AE7D4[] __attribute__((sda));

/* Waits for the right screen field, then lets the movie start showing frames. */
void mpeg_wait_for_field_start(int value)
{
    while (sceGsSyncV(0) == value && g_widescreen_flag == 0) {}
    D_001AE7D0[0] = 1;
    D_001AE7D4[0] = 0;
}

/* A19-sda-scalar-store-16 freshly exact-verified under family reservation */
/* Clears a movie flag. */
void mpeg_clear_flag(void) { D_L00_001AEB10 = 0; }

/* func_00350240 is in 0034CEA0-g8.c. */

extern int mpeg_copy_split_buffer(char *, int, char *, int, char *, int, char *, int);

/* Copies a chunk of movie sound data into the sound buffer. */
int mpeg_copy_packet_to_audio_buffer(void *unused, int *packet, char *buf)
{
    char *first_address;
    int first_count;
    char *second_address;
    int second_count;
    Ring *r = (Ring *)(buf + 0x50000);
    char *src = (char *)packet[2] + 4;
    char *end = buf + r->size;
    int len = packet[3] - 4;
    int first, second, result;

    if (src >= end)
        src -= r->size;
    first = end - src;
    if (len < first)
        first = len;
    second = len - first;
    mpeg_get_audio_write_pointers((s32 *)(g_movie_player_state[0] + 0xD9100), (s32 *)&first_address, &first_count, (s32 *)&second_address, &second_count);
    result = mpeg_copy_split_buffer(first_address, first_count, second_address, second_count, src, first, buf, second);
    audioDecEndPut((s32 *)(g_movie_player_state[0] + 0xD9100), result);
    return result > 0;
}


/* Sets up an empty read buffer. */
void readBufCreate(u8 *ring) {
 ring+=0x50000;
 *(s32 *)(ring+8)=0x50000;
 *(s32 *)ring=0;
 *(s32 *)(ring+4)=0;
}

/* Does nothing. */
void mpeg_noop_read_buffer_hook(void)
{
}

s32 readBufBeginPut(u8 *buf,u8 **outPtr) {
 s32 *ring=(s32 *)(buf+0x50000);
 s32 freeBytes=ring[2]-ring[1];
 if(freeBytes!=0) *outPtr=buf+ring[0];
 return freeBytes;
}

void readBufEndPut(char *base, int n) {
    Ring *r = (Ring *)(base + 0x50000);
    int avail = r->size - r->used;
    if (n < avail) avail = n;
    r->pos = (r->pos + avail) % r->size;
    r->used += avail;
}

s32 readBufBeginGet(u8 *buf,s32 *outPtr) {
    u8 *ring=buf+0x50000;
    s32 usedBytes=*(s32 *)(ring+4);
    if(usedBytes!=0) {
        s32 size=*(s32 *)(ring+8);
        *outPtr=(s32)buf+((*(s32 *)ring-usedBytes)+size)%size;
    }
    return *(s32 *)(ring+4);
}

s32 readBufEndGet(u8 *ring,s32 amount) {
 s32 before,taken;
 ring+=0x50000;
 taken=*(s32 *)(ring+4);before=taken;
 if(amount<taken) taken=amount;
 *(s32 *)(ring+4)=before-taken;
 return taken;
}

/* stores two words and returns 1; byte-identical across all 27 levels. */
s32 mpeg_set_read_buffer_range(u8 *a0, s32 a1, s32 a2) { *(s32 *)(a0 + 0x4) = a1; *(s32 *)a0 = a2; return 1; }
