#include "common.h"

typedef struct {
    unsigned char pad[12];
    unsigned char flag;
    unsigned char padD[3];
    float values[4];
} CutsceneCamKey_002F5AF8;
typedef struct {
    char pad[0x38];
    int index;
    char pad3C[0x2C];
    CutsceneCamKey_002F5AF8 *keys;
} CutsceneCamCtl_002F5AF8;
typedef struct { char pad[0xB0]; float fov; } CutsceneCamVars_002F5AF8;
typedef struct { float x, y, z, w; } CameraVec_002F5AF8;
typedef struct { char pad[0x370]; CameraVec_002F5AF8 rows[3]; } CameraBlock_002F5AF8;
extern void UpdateViewContext(void);

extern int D_L05_001B1FC8;

extern int D_L05_001B1FD0;

extern int D_L05_001B1FD4;

extern int D_L05_001B1FCC;

extern int D_L05_001B1FF8;

extern int D_L05_001B1FFC;

extern int D_L05_001A8F00;

extern int D_L05_001A8F08;

extern unsigned char D_0018C0D4[];

extern int D_00138320[];

extern short D_L05_001B225C;

extern short D_L05_001B225E;

extern short D_L05_001B2260;

extern short D_L05_001B2262;

extern short D_L05_001B2264;

#ifndef RAC2_T_F32_F2144BF3D
#define RAC2_T_F32_F2144BF3D
typedef float f32_F2144bf3d;
#endif

#ifndef RAC2_T_S32_F2144BF3D
#define RAC2_T_S32_F2144BF3D
typedef int s32_F2144bf3d;
#endif

/* Resident record reached through a fixed core symbol: the retail body keeps
   the base in a register and addresses every field by displacement. */
#ifndef RAC2_T_RESIDENT138180_F2144BF3D
#define RAC2_T_RESIDENT138180_F2144BF3D
typedef struct {
    char  pad0[0x100];
    f32_F2144bf3d   f100;                 /* 0x100 */
    f32_F2144bf3d   f104;                 /* 0x104 */
    f32_F2144bf3d   f108;                 /* 0x108 */
    f32_F2144bf3d   f10C;                 /* 0x10C */
    char  pad1[0x1A0 - 0x110];
    s32_F2144bf3d   i1A0;                 /* 0x1A0 */
} Resident138180_F2144bf3d;
#endif

extern char g_pad_state[];

extern s32_F2144bf3d D_0018D198[];

extern s32_F2144bf3d D_L06_001AD3A0 __attribute__((sda));

extern s32_F2144bf3d D_001A7390;

extern s32_F2144bf3d g_current_map_index;

extern s32_F2144bf3d D_L06_001B2348;

extern s32_F2144bf3d D_L06_001A8FC0;

extern s32_F2144bf3d D_L06_001B2900;

extern s32_F2144bf3d D_L06_001AA0F0;

/* Clears a group of counters and, in one game mode while nothing else is going on, also clears
   five saved values. */
void game_reset_frame_counters(void)
{
    unsigned char mode;

    D_L05_001B1FC8 = 0;
    mode = D_0018C0D4[0];
    D_L05_001B1FD0 = 0;
    D_L05_001B1FD4 = 0;
    D_L05_001B1FCC = 0;
    D_L05_001B1FF8 = 0;
    D_L05_001B1FFC = 0;

    if (mode == 1)
    {
        if ((D_00138320[0] & 0x10) == 0)
        {
            if (D_L05_001A8F00 != 4 && D_L05_001A8F08 != 4)
            {
                D_L05_001B225C = 0;
                D_L05_001B225E = 0;
                D_L05_001B2260 = 0;
                D_L05_001B2262 = 0;
                D_L05_001B2264 = 0;
            }
        }
    }
}

/* Counts how many frames in a row the controller has had no input, and counts every frame played.
   While the pause is shorter than 900 frames it also adds the frame to the current slot's total. */
void game_update_idle_frame_counters(void)
{
    Resident138180_F2144bf3d *pad = (Resident138180_F2144bf3d *)g_pad_state;

    if (pad->i1A0 != 0) goto mismatch;
    if (pad->f108 != 0.0f) goto mismatch;
    if (pad->f10C != 0.0f) goto mismatch;
    if (pad->f100 != 0.0f) goto mismatch;
    if (pad->f104 == 0.0f) goto match;
mismatch:
    D_L06_001AD3A0 = 0;
    goto gated;
match:
    D_L06_001AD3A0 = D_L06_001AD3A0 + 1;
gated:
    D_L06_001B2348 = D_L06_001B2348 + 1;
    D_001A7390 = D_001A7390 + 1;

    if (D_L06_001A8FC0 != 0) {
        if (D_L06_001AD3A0 < 900) {
            D_0018D198[g_current_map_index] = D_0018D198[g_current_map_index] + 1;
        }
    }

    if (D_L06_001B2900 != D_001A7390 - 1) {
        D_L06_001AA0F0 = -1;
    }
}


/* Applies the current cutscene camera key and returns its flag byte. */
#include "common.h"

typedef struct { u8 pad00[0xC]; u8 kind; u8 pad0D[3]; f32 w0[4]; } CamRec_2F5AF8;
typedef struct { u8 pad00[0x38]; s32 index; u8 pad3C[0x68 - 0x3C]; CamRec_2F5AF8 *recs; } CamList_2F5AF8;
typedef struct { u8 pad[0xB0]; f32 scale; } CamView_2F5AF8;
typedef struct {
    u8 pad000[0x140];
    f32 pos[4];
    u8 pad150[0x370 - 0x150];
    f32 row0[3];
    f32 pad37C;
    f32 row1[3];
    f32 pad38C;
    f32 row2[3];
} Cam_2F5AF8;

extern CamList_2F5AF8 g_scene_playback_state;
extern CamView_2F5AF8 D_001B9040;
extern Cam_2F5AF8 g_active_camera;
extern u8 D_001A7A40;
extern f32 D_001A8C74;
extern f32 D_001A8C78;
extern f32 D_001B5360[12];
extern void UpdateViewContext(void);
extern void func_00129178(f32 *);
extern void pad_vib_routine_f(f32 *, f32 *, f32);
extern void pad_vib_routine_g(f32 *, f32 *, f32);
extern void pad_vib_routine_e(f32 *, f32 *, f32);
extern void vec_scale_to_length(f32 *, f32 *, f32);
extern void FastVecSub(f32 *, f32 *, f32 *);
extern void cam_update_shake(f32 *, int);

/* Sets the camera to the current cutscene camera key: position, turn and zoom. */
u8 cutscene_apply_camera_key(void)
{
    f32 m[16] __attribute__((aligned(16)));
    f32 t[4] __attribute__((aligned(16)));
    CamRec_2F5AF8 *rec;
    f32 *w;
    f32 scale;
    f32 k;
    u8 kind;

    rec = &g_scene_playback_state.recs[g_scene_playback_state.index];
    w = rec->w0;
    kind = rec->kind;
    scale = w[3];
    D_001B9040.scale = scale;
    if (D_001A7A40 != 0)
        D_001B9040.scale = scale * D_001A8C74;
    UpdateViewContext();
    qcopy(g_active_camera.pos, rec);
    func_00129178(m);
    pad_vib_routine_f(m, m, w[0]);
    pad_vib_routine_g(m, m, w[1]);
    pad_vib_routine_e(m, m, w[2]);
    g_active_camera.row0[0] = -m[8];
    g_active_camera.row1[0] = -m[0];
    g_active_camera.row2[0] = m[4];
    g_active_camera.row0[1] = -m[9];
    g_active_camera.row1[1] = -m[1];
    g_active_camera.row2[1] = m[5];
    g_active_camera.row0[2] = -m[10];
    g_active_camera.row1[2] = -m[2];
    g_active_camera.row2[2] = m[6];
    if (D_001A7A40 != 0 && (k = D_001A8C78) != 0.0f) {
        qcopy(t, g_active_camera.row0);
        vec_scale_to_length(t, t, k);
        FastVecSub(g_active_camera.pos, g_active_camera.pos, t);
    }
    cam_update_shake(&D_001B5360[0], 0);
    cam_update_shake(&D_001B5360[4], 1);
    cam_update_shake(&D_001B5360[8], 2);
    return kind;
}

extern int D_001A8C80[] __attribute__((sda));
extern int D_001A8C84 __attribute__((sda));

/* Stores two values for later use. */
void game_set_stored_value_pair(int first, int second) {
    D_001A8C80[0] = first;
    D_001A8C84 = second;
}

extern float D_001A8C7C __attribute__((sda));
extern float g_screen_fade;
extern void FadeToBlack(int);

/* Publishes the slow-down factor and, while the frame rate is below one, asks
   for the six-frame path. */
void game_set_slowdown_factor(void)
{
    D_001A8C7C = 1.2f;
    if (g_screen_fade < 1.0f)
        FadeToBlack(6);
}

/* Returns true when either of the two mode variables is 2. */
int game_is_either_mode_two(void)
{
    return D_L05_001A8F08 == 2 || D_L05_001A8F00 == 2;
}

extern void mpeg_begin_movie_playback(int sector, int size, int file, int mode, int flag);
extern int D_001B220C;
extern int D_001BAD40[];
extern unsigned char D_001A7BB4[] __attribute__((sda));
/* The table of contents read into 0x14B540: a base sector, then sector/size pairs, two per
   entry. The extent of the pairs is not known, so the buffer stays incomplete. */
typedef struct { int sector; int size; } TocFile_002F5D40;
typedef struct {
    int header;
    int base;
    TocFile_002F5D40 files[0];
} Toc_002F5D40;
extern char g_copy_setup_data[];
#define TOC_002F5D40 ((Toc_002F5D40 *)D_0014B540)

/* Hands entry n of the table of contents to func_002F5E20; n < 0 only clears D_001B220C.
   Marks n in the shared flag table (bit n & 0x1F of the word at n >> 2, below 0xB1) and
   passes the entry's second file (sector relative to the base, size), the entry itself,
   D_001A7BB4 or 0 when D_001BAD40[0] is set, and whether n is 0xBF. */
extern int D_00139768[];
extern int cutscene_map_id_to_index(int);
extern void req_mark_queued_in_flag_table(void *);

void mpeg_start_movie_from_toc(int n)
{
    int index;
    int flag;

    if (n < 0) {
        D_001B220C = 0;
        return;
    }
    index = cutscene_map_id_to_index(n);
    flag = 0;
    if (n == 0xBF)
        flag = 1;
    if ((unsigned)n < 0xB1) {
        int mask = 1 << (n & 31);
        D_00139768[(unsigned)n >> 2] |= mask;
    }
    req_mark_queued_in_flag_table(D_001BAD40);
    mpeg_begin_movie_playback(TOC_002F5D40->files[index * 2 + 1].sector + TOC_002F5D40->base,
                  TOC_002F5D40->files[index * 2 + 1].size,
                  (int)&TOC_002F5D40->files[index * 2],
                  D_001BAD40[0] ? 0 : D_001A7BB4[0], flag);
}
#undef TOC_002F5D40


extern int D_001A7478;
extern int D_001B221C;
extern unsigned char g_sound_state[];
extern int D_001BAD78[];
extern int g_requested_game_mode;
extern void (*ref_L00_002F5EF8_00)(int);
extern int ref_L00_002F5EF8_01;
extern void snd_start_music_stream_no_loop(int, int, int);
extern void music_Unpause(void);
extern void gfx_reset_packet_buffer(void);

/* Runs when a movie ends: brings back the music and screen, then calls the waiting callback. */
void mpeg_resume_after_movie(void)
{
    if (D_001A7478 == 2)
        *(volatile int *)&D_001A7478 = 0;
    FadeToBlack(4);
    snd_start_music_stream_no_loop(D_001B221C, 1, 0x400);
    music_Unpause();
    g_sound_state[0x6B] |= 0x10;
    gfx_reset_packet_buffer();
    if (ref_L00_002F5EF8_00 != 0 && D_001BAD78[0] == 0) {
        if (g_requested_game_mode == 2)
            goto done;
        if (g_requested_game_mode == 1)
            goto done;
        {
            ref_L00_002F5EF8_00(D_001A8C84);
            *(void (*volatile *)(int))&ref_L00_002F5EF8_00 = 0;
            *(volatile int *)&ref_L00_002F5EF8_01 = 0;
        }
    }
done:
    ;
}

/* Plays the current FMV (D_001B220C, set up by func_002F5E20). With no stream it shows the
   message and ends the movie state. Otherwise it uploads the two movie textures into display
   slot 2, sets the slot's TEX0 word, waits for the sound streams to idle, then decodes frames into
   the two 64-aligned buffers until the stream or the scripted frame list ends, loading each
   chunk's sector and size from the table of contents. Finally it restores the texture, clears
   the slot and either chains the next scene or returns to the game. */
typedef unsigned long long U64_5FB8;
typedef struct { U64_5FB8 packet; unsigned short tex0, tex1; short width, height; } Display_5FB8;
typedef struct { int frame; short *frames; char pad[0x2C]; int field34, active, mode; } Stream_5FB8;
extern int ref_L00_002F5FB8_00, ref_L00_002F5FB8_01;
extern char ref_L00_002F5FB8_04[];
extern int ref_L00_002F5FB8_05[];
extern int ref_L00_002F5FB8_06[];
extern Display_5FB8 ref_L00_002F5FB8_07[];
extern char *ref_L00_002F5FB8_08;
extern int *ref_L00_002F5FB8_10;
extern int ref_L00_002F5FB8_12;
extern int ref_L00_002F5FB8_13 __attribute__((sda));
extern int ref_L00_002F5FB8_14 __attribute__((sda));
extern int ref_L00_002F5FB8_16[];
extern int g_memcard_state[];
extern char D_001339B0[];
extern void func_0029CC98(int, int);
extern void req_flush_queue(void *);
extern int request_end_slot(int,int);
extern void gfx_wait_for_dma_status_bits(int);
extern int func_00126288(void *,short,short,short,short,short,short,short);
extern void FlushCache(int);
extern int sceGsExecLoadImage(void *,void *);
extern int gfx_wait_paths_idle(int,int);
extern void snd_clear_all_voices(void);
extern void snd_wait_for_music_idle(void);
extern int snd_CheckLoadInProgress(int);
extern void mc_update_state(void);
extern int load_read_disc_with_pause(char *,int,int);
extern int mpeg_play_movie_2(void *,void *,char *,char *,int,int);
extern int req_pop_queue(void *,int *,int *);
extern void func_00126DC0(void *);
extern void gfx_reset_record_list(void);
extern int request_begin_slot(int,int,int,int,unsigned char *);
void mpeg_play_movie(void)
{
    long packet[12] __attribute__((aligned(16)));
    long low, dimensions, high;
    long base;
    long highFlags;
    int textureIndex;
    int frame, status, done, result;
    int first, second, index;
    Display_5FB8 *displays;
    char *destination;
    Display_5FB8 *display;
    Stream_5FB8 *stream;
    Display_5FB8 *slot;
    if (ref_L00_002F5FB8_00 == 0) {
        func_0029CC98((int)ref_L00_002F5FB8_04,-1);
        req_flush_queue(ref_L00_002F5FB8_05);
        request_end_slot(0,0);
        return;
    }
    first = ref_L00_002F5FB8_06[3];
    second = ref_L00_002F5FB8_06[5];
    destination = (char *)(second + 0xE0000);
    gfx_wait_for_dma_status_bits(1);
    textureIndex = 2;
    displays = ref_L00_002F5FB8_07;
    display = &displays[textureIndex];
    base = 0x3F70;
    func_00126288(packet,(short)base,(short)((1 << display->width) >> 6),0x13,0,0,(short)(1 << display->width),(short)(1 << display->height));
    FlushCache(0);
    sceGsExecLoadImage(packet,ref_L00_002F5FB8_08 + display->tex0 * 16);
    gfx_wait_paths_idle(0,0);
    func_00126288(packet,0x3F6C,1,0,0,0,16,16);
    FlushCache(0);
    sceGsExecLoadImage(packet,ref_L00_002F5FB8_08 + display->tex1 * 16);
    gfx_wait_paths_idle(0,0);
    highFlags = 0x7ED8400000000L;
    low = ((long)((1 << display->width) >> 6) << 14) | (long)base;
    dimensions = ((long)display->width << 26) | 0x1300000L;
    low = low | dimensions;
    low = low | ((long)display->height << 30);
    high = low | highFlags;
    displays[textureIndex].packet = high | 0x8000000000000000ULL;
    FlushCache(0);
    snd_clear_all_voices();
    snd_wait_for_music_idle();
    snd_CheckLoadInProgress(0);
    while (g_memcard_state[0x15C/4] >= 3 || g_memcard_state[0x164/4] >= 0) mc_update_state();
    frame = 0;
    status = -1;
    done = 0;
    for (;;) {
        int *descriptor;
        descriptor = ref_L00_002F5FB8_10;
        if (descriptor != 0 && descriptor[0] != 0) {
            load_read_disc_with_pause(destination,descriptor[0] + ((Toc_002F5D40 *)g_copy_setup_data)->base,(descriptor[1] + 2047)/2048);
            ref_L00_002F5FB8_16[0x4C/4] = (int)destination;
            ref_L00_002F5FB8_16[0x34/4] = 0;
        } else {
            ref_L00_002F5FB8_16[0x4C/4] = 0;
            ref_L00_002F5FB8_16[0x34/4] = 0;
        }
        stream = (Stream_5FB8 *)ref_L00_002F5FB8_05;
        result = mpeg_play_movie_2((void *)ref_L00_002F5FB8_01,(void *)ref_L00_002F5FB8_00,(char *)((first + 63) & -64),(char *)((second + 63) & -64),ref_L00_002F5FB8_13,ref_L00_002F5FB8_12 != 0);
        stream->mode = (result ^ 1) == 0 ? 1 : stream->mode;
        if (result != 0) { stream->mode = 1; req_flush_queue(stream); }
        if (ref_L00_002F5FB8_05[0] != 0) {
            ref_L00_002F5FB8_05[0]++;
            if (ref_L00_002F5FB8_05[0] >= 25) ref_L00_002F5FB8_05[0] = 1;
            index = cutscene_map_id_to_index(stream->frames[ref_L00_002F5FB8_05[0]]);
            ref_L00_002F5FB8_01 = ((Toc_002F5D40 *)g_copy_setup_data)->files[index * 2 + 1].sector + ((Toc_002F5D40 *)g_copy_setup_data)->base;
            ref_L00_002F5FB8_14 = ((Toc_002F5D40 *)g_copy_setup_data)->files[index * 2 + 1].size;
        } else if (stream->active == 0) {
            done = 1;
        } else {
            req_pop_queue(stream,&frame,&status);
            if (status == 0) {
                index = cutscene_map_id_to_index(frame);
                ref_L00_002F5FB8_01 = ((Toc_002F5D40 *)g_copy_setup_data)->files[index * 2 + 1].sector + ((Toc_002F5D40 *)g_copy_setup_data)->base;
                ref_L00_002F5FB8_14 = ((Toc_002F5D40 *)g_copy_setup_data)->files[index * 2 + 1].size;
            } else if (status == 1) {
                done = 1;
            }
        }
        if (done) break;
    }
    snd_CheckLoadInProgress(0);
    func_00126DC0(D_001339B0);
    gfx_wait_paths_idle(0,0);
    slot = &ref_L00_002F5FB8_07[textureIndex];
    sceGsExecLoadImage(packet,ref_L00_002F5FB8_08 + slot->tex1 * 16);
    gfx_wait_paths_idle(0,0);
    gfx_reset_record_list();
    slot->packet = 0;
    gfx_reset_packet_buffer();
    if (result == 0 && status == 1) request_begin_slot(2,2,frame,0,0);
    else request_end_slot(0,0);
}


extern void func_288CB0(int, int);
/* Flags the current menu entry when it is valid, then calls a follow-up routine. */
void menu_flag_current_entry(void) { char *base = g_pad_state + 0x1260; int index = *(int *)(base + 0x148); if (index != -1) { if (*(short *)(base + index * 0xA0 + 0x18) >= 0) *(int *)(base + 0x17C) = 1; } func_288CB0(0, 0); }



/* func_002F6510: the copied records have the measured 0xE0-byte extent. */
typedef int F6510Quad __attribute__((mode(TI)));
typedef union {
    F6510Quad raw[14];
    struct { char prefix[0x80]; int value; char tail[0x5C]; } fields;
} F6510Record;
typedef struct { int type; char pad[12]; int locked; int active; } F6510Row;
typedef struct { char pad[0x80]; int selected; char pad84[0xBC]; F6510Row rows[1]; } F6510State;
extern F6510State g_purchase_menu_model;
extern unsigned char g_item_slot_to_record[];
extern F6510Record g_weapon_l00_table[];
extern int help_copy_record_at_depth(void *, int, int);

/* Returns the price of the selected shop entry: a weapon upgrade's cost, or a table price. */
int GetSelectedShopItemPrice(void)
{
    F6510Record local;
    int offset = g_purchase_menu_model.selected * 24;
    int result = 0;

    if (*(int *)((char *)&g_purchase_menu_model + offset + 0x154) != 0) {
        int isSpecial = 0;
        switch (*(int *)((char *)&g_purchase_menu_model + offset + 0x140)) {
        case 12:
        case 14:
        case 17:
        case 18:
        case 53:
            isSpecial = 1;
            break;
        default:
            break;
        }
        if (isSpecial) {
            if (help_copy_record_at_depth(&local, *(int *)((char *)&g_purchase_menu_model + g_purchase_menu_model.selected * 24 + 0x140), 1))
                result = local.fields.value;
        } else {
            if (help_copy_record_at_depth(&local, *(int *)((char *)&g_purchase_menu_model + g_purchase_menu_model.selected * 24 + 0x140), 2))
                result = local.fields.value;
        }
    } else if (*(int *)((char *)&g_purchase_menu_model + offset + 0x150) == 0) {
        result = g_weapon_l00_table[g_item_slot_to_record[*(int *)((char *)&g_purchase_menu_model + offset + 0x140)]].fields.value;
    }
    return result;
}


extern unsigned char D_001A7AB8[] MACRO_ADDR;
extern unsigned char g_item_owned_flags[] MACRO_ADDR;
extern unsigned char D_001A7A80[] MACRO_ADDR;
typedef struct { int active; char pad4[0x10]; int info; char pad18[0x80]; int channels[3]; char padA4[0x3C]; } F73Record;
extern F73Record g_weapon_table[];
typedef struct { char pad[0x140]; int rows[96][4]; int count; } F73StateType;
extern F73StateType D_0021F240_rows __asm__("D_0021F240");
extern int shop_row_field_matches_value(int owner, int key, int channel);
extern int flag_is_byte_set(void);
extern int D_L00_0022FF00[];

/* Works out which weapon upgrades can be bought and adds a row to the shop list for each one. */
void BuildShopChannelList(void)
{
    D_L00_0022FF00[0] = 0;
    {
        int key, channel, available;
        for (key = 0; key < 56; key++) {
            int offset = g_item_slot_to_record[key] * 224;
            if (((F73Record *)((char *)g_weapon_table + offset))->active != 0) {
                for (channel = 0; channel < 3; channel++) {
                    if (shop_row_field_matches_value(g_current_map_index, key, channel) != 0)
                        goto mark_available;
                    switch (channel) {
                    case 0: available = ((F73Record *)((char *)g_weapon_table + g_item_slot_to_record[key] * 224))->channels[0]; break;
                    case 1: available = ((F73Record *)((char *)g_weapon_table + g_item_slot_to_record[key] * 224))->channels[1]; break;
                    case 2: available = ((F73Record *)((char *)g_weapon_table + g_item_slot_to_record[key] * 224))->channels[2]; break;
                    default: available = 0; break;
                    }
                    if (!available) continue;
                    if (!flag_is_byte_set()) continue;
mark_available:
                    D_001A7AB8[key] |= 1 << channel;
                }
            }
        }
    }
    {
        int key, channel, available;
        char *entry;
        for (key = 0; key < 56; key++) {
            if (key == 0) continue;
            if (g_weapon_table[g_item_slot_to_record[key]].active == 0) continue;
            if (g_item_owned_flags[key] == 0) continue;
            for (channel = 0; channel < 3; channel++) {
                {
                    unsigned int mask = 1U << channel;
                    if (!(D_001A7AB8[key] & mask)) continue;
                }
                switch (channel) {
                case 0: available = ((F73Record *)((char *)g_weapon_table + g_item_slot_to_record[key] * 224))->channels[0]; break;
                case 1: available = ((F73Record *)((char *)g_weapon_table + g_item_slot_to_record[key] * 224))->channels[1]; break;
                case 2: available = ((F73Record *)((char *)g_weapon_table + g_item_slot_to_record[key] * 224))->channels[2]; break;
                default: available = 0; break;
                }
                if (!available) continue;
                {
                    unsigned char mask = 1 << (channel * 2);
                    if (D_001A7A80[key] & mask) continue;
                }
                D_0021F240_rows.rows[D_0021F240_rows.count][0] = channel;
                {
                    int stored_value;
                    switch (channel) {
                    case 0: stored_value = ((F73Record *)((char *)g_weapon_table + g_item_slot_to_record[key] * 224))->channels[0]; break;
                    case 1: stored_value = ((F73Record *)((char *)g_weapon_table + g_item_slot_to_record[key] * 224))->channels[1]; break;
                    case 2: stored_value = ((F73Record *)((char *)g_weapon_table + g_item_slot_to_record[key] * 224))->channels[2]; break;
                    default: stored_value = 0; break;
                    }
                    D_0021F240_rows.rows[D_0021F240_rows.count][2] = stored_value;
                }
                entry = (char *)g_weapon_table + g_item_slot_to_record[key] * 224;
                D_0021F240_rows.rows[D_0021F240_rows.count][1] = key;
                D_0021F240_rows.rows[D_0021F240_rows.count][3] = *(int *)(entry + 0x14);
                ++D_0021F240_rows.count;
            }
        }
    }
}
typedef struct { unsigned char pad0[0x3C]; char *destination; unsigned char pad1[0x24]; int clear; } Func_002F88D8State;
extern Func_002F88D8State ref_L00_002F88D8_00;
extern void sprintf(char *, const char *, ...);
extern const char D_001AD2B8[];

/* Puts a line of text into the shop's message box. */
void shop_set_message_text(void *text) { sprintf(ref_L00_002F88D8_00.destination, D_001AD2B8, text); ref_L00_002F88D8_00.clear = 0; }


typedef unsigned int Quad_002F9198 __attribute__((mode(TI), aligned(16)));
typedef struct { Quad_002F9198 a, b, c; } Three_002F9198;
typedef struct { int words[5]; } Five_002F9198;
typedef struct { int state; char pad4[0x24]; char *moby; char pad2C[0x24]; int mode; char pad54[0xC]; int restore; char pad64[0x7C]; Quad_002F9198 saved; } Shop_002F9198;
typedef struct { char *moby; char pad4[0x14]; int a; char pad1C[0x14]; int b; } HeroMenu_002F9198;
extern Shop_002F9198 g_vendor_menu_state;
extern char D_001B5350[];
/* Its address is one `la` (assembler lui/addiu pair), not a split %hi/%lo: retail
   schedules the pair as one insn ahead of dst + 0x220. */
extern Three_002F9198 D_001B2250 MACRO_ADDR;
extern float D_001AD234 __attribute__((sda));
extern float D_001AD238 __attribute__((sda));
extern int D_001B2284, D_001B2288, D_001B228C, D_001B2290, D_001B2294, D_001B2298;
extern int D_001AD230 __attribute__((sda));
extern int D_001AD1B8 __attribute__((sda));
extern unsigned short D_001AD1BC __attribute__((sda)), D_001AD1C0 __attribute__((sda));
/* 0x40-byte block that func_002DE990 saves and restores whole. */
typedef struct { char pad0[0x20]; short level; char pad22[0x1E]; } Settings_002F9198;
extern Settings_002F9198 g_player_bolts MACRO_ADDR;
extern Five_002F9198 D_001AD308;
extern HeroMenu_002F9198 g_hero_moby_default;
extern int g_equipment_bits;
extern unsigned short D_001A7AF2;
extern void gfx_select_packet_buffer_setup(void);
extern int PlayMobySound(int, int, void *);
extern void tex_load_level_pack(int);
extern int GetLocalizedString(int);
extern void func_0029CC98(int, int);
extern void load_disc_table_entry_for_draw(int);
extern void LoadDiscTableTexture(int);
extern void SpawnEquipmentPieces(int);

/* Closes the current shop screen: plays a sound, restores the saved camera and resets the preview
   for armor or equipment. */
void shop_close_sub_menu(void)
{
    Shop_002F9198 *s = &g_vendor_menu_state;
    Five_002F9198 table;
    gfx_select_packet_buffer_setup();
    PlayMobySound(5, 17, s->moby);
    if (s->restore) {
        qcopy(D_001B5350, &s->saved);
        { Quad_002F9198 *dst = (Quad_002F9198 *)(D_001B5350 + 0x220);
          Three_002F9198 *src = &D_001B2250;
          dst[0] = src->a; dst[1] = src->b; dst[2] = src->c; }
    }
    *(unsigned short *)(s->moby + 0x34) |= 0x100;
    g_vendor_menu_state.state = 2;
    D_001AD234 = 1.0f;
    D_001AD238 = 1.1f;
    D_001AD230 = 0;
    D_001B2290 = 0; D_001B2294 = 0; D_001B2298 = 0;
    D_001B2284 = 96;
    D_001B2288 = 96;
    D_001B228C = 85;
    if (g_vendor_menu_state.mode == 3) {
        if (D_001AD1B8) g_player_bolts.level = D_001AD1BC; else g_player_bolts.level = D_001AD1C0;
        tex_load_level_pack(g_player_bolts.level);
        table = D_001AD308;
        if (D_001AD1B8) func_0029CC98(GetLocalizedString(table.words[g_player_bolts.level]), -1);
    }
    if (g_vendor_menu_state.mode == 2) {
        if (g_hero_moby_default.a != g_equipment_bits) {
            char *m;
            load_disc_table_entry_for_draw(g_equipment_bits & 3);
            m = g_hero_moby_default.moby;
            if (m && *(int *)(m + 0x98)) *(int *)(m + 0x98) = *(int *)(*(char **)(m + 0x24) + 0x10);
        }
        if (g_hero_moby_default.b != (D_001A7AF2 & 31)) LoadDiscTableTexture(D_001A7AF2 & 31);
        SpawnEquipmentPieces(0);
    }
}


extern int D_001B2240, D_001B223C;
extern int D_001B2244 __attribute__((sda));
extern int g_item_ammo_counts[];
extern void set_animation_parameter(int, unsigned int);
extern int GetSelectedShopItemPrice(void);
extern void shop_close_sub_menu(void);

typedef struct { int id, kind; int fields[4]; } ShopRow_93;
typedef struct {
    char pad0[0x28]; char *moby; char pad2C[0x24];
    int mode; char pad54[0x18]; int scroll;
    char pad70[8]; int handle; char pad7C[4]; int selected;
    int busy; int animated; char pad8C[4]; int animation;
    char pad94[0xAC]; ShopRow_93 rows[64]; int count;
} ShopInput_93;
extern ShopInput_93 F93State __asm__("D_0021F240");
typedef struct { char pad[0x1C4]; int buttons; } Input_93;
/* Handles the shop menu buttons: scroll up and down, buy or select, and leave. */
void UpdateShopMenuInput(void)
{
    ShopInput_93 *state = &F93State;
    int cost;
    char *record;
    if (state->busy) return;
    {
        Input_93 *input = (Input_93 *)g_pad_state;
        if ((input->buttons & 0x2000) ||
                (D_001B2240 >= 16 && D_001B2240 % 10 == 1)) {
            if (state->scroll < 57) {
                int moved = 0;
                if (state->selected < state->count - 1) {
                    ++state->selected;
                    moved = 1;
                }
                if (moved) {
                    if (state->animated) {
                        int animation = 3;
                        if (state->mode != 2) animation = 1;
                        state->animation = animation;
                    }
                    state->scroll += 56;
                    PlayMobySound(1, 17, state->moby);
                    if (state->handle != -1) {
                        if (state->mode == 0)
                            set_animation_parameter(state->handle, 0);
                    }
                    F93State.handle = -1;
                }
            }
        }
    }
    {
        Input_93 *input = (Input_93 *)g_pad_state;
        ShopInput_93 *state;
        if ((input->buttons & 0x8000) ||
                (D_001B223C >= 16 && D_001B223C % 10 == 1)) {
            state = &F93State;
            if (state->scroll >= -56) {
                int moved = 0;
                if (state->selected > 0) {
                    --state->selected;
                    moved = 1;
                }
                if (moved) {
                    if (state->animated) {
                        int animation = 3;
                        if (state->mode != 2) animation = 1;
                        state->animation = animation;
                    }
                    state->scroll -= 56;
                    PlayMobySound(1, 17, state->moby);
                    if (state->handle != -1) {
                        if (state->mode == 0)
                            set_animation_parameter(state->handle, 0);
                    }
                    F93State.handle = -1;
                }
            }
        }
    }
    {
        Input_93 *input = (Input_93 *)g_pad_state;
        ShopInput_93 *state;
        if (((input->buttons & 0x40) && !(D_001B2244 & 0x40) && F93State.mode != 3) ||
            ((input->buttons & 0x40) && !(D_001B2244 & 0x40) && F93State.mode == 3 &&
             *(int *)((char *)&F93State + 0x144 + F93State.selected * 12) != 0)) {
                state = &F93State;
                if (state->mode == 0) {
                    int stride = sizeof(ShopRow_93);
                    int *kinds = &state->rows[0].kind;
                    if (*(int *)((char *)kinds + state->selected * stride) == 0) {
                        cost = GetSelectedShopItemPrice();
                        if ((*(int *)&g_player_bolts) >= cost) goto activate;
                    }
                    if (*(int *)((char *)kinds + state->selected * stride) != 1) goto rejected;
                    {
                        int id = state->rows[state->selected].id;
                        int owned = g_item_ammo_counts[id];
                        record = (char *)g_weapon_table + g_item_slot_to_record[id] * 224;
                        if (owned >= *(unsigned short *)(record + 0x8E)) goto rejected;
                    }
                    if ((*(int *)&g_player_bolts) < *(unsigned short *)(record + 0x88)) goto rejected;
                }
activate:
                {
                    ShopInput_93 *active = &F93State;
                    if (active->animated) active->animation = 1;
                    active->busy = 1;
                    PlayMobySound(0, 17, active->moby);
                    goto finish;
                }
rejected:
                PlayMobySound(2, 17, F93State.moby);
        }
    }
finish:
    if (((Input_93 *)g_pad_state)->buttons & 0x10) shop_close_sub_menu();
}

extern void UpdateShopMenuInput(void);

/* Runs the shop menu input handler. */
void shop_run_menu_input(void)
{
    UpdateShopMenuInput();
}


/* One font glyph: its texture cell, its top offset and its advance. */
typedef struct { u8 u, v; signed char top, adv; } Glyph_002F97A0;

extern Glyph_002F97A0 D_00263EF0[];
extern u64 GetEffectTextureDescriptor(int);
extern float IntToFloat(int);
extern void EmitTexturedRectangle(float, float, float, float, int, int, int, int, u32 *, u64);

/* Prints up to `limit` characters of `text` from (x, y) at `scale`, in the large font, fading
   each glyph's left and right edges out with their distance from the screen centre (215 on
   the second screen layout, 256 elsewhere, three quarters as fast). Characters 0x80..0xa7
   draw their entry 0x40 later; control characters below 0x20 draw a grey 24-pixel sprite. */
void draw_large_text_edge_faded(u64 color, u8 *text, int limit, float x, float y, float scale)
{
    u32 colors[4];
    u32 gray[4];
    Glyph_002F97A0 *glyphs;
    Shop_002F9198 *shop = &g_vendor_menu_state;
    Glyph_002F97A0 *g;
    u64 texture;
    int count = 0;
    float size;
    float top;
    float dx;
    float dy;
    double distance;
    int left;
    int right;
    int shade;
    int tint;
    u8 *cursor;
    u32 argb;

    texture = GetEffectTextureDescriptor(2);
    size = scale * 16.0f;
    glyphs = D_00263EF0;
    color &= 0xFFFFFF;
    if (limit == 0 || *text == 0)
        return;
    cursor = text;
    do {
        if (glyphs[*cursor].adv != 0) {
            top = IntToFloat(glyphs[*cursor].top) * scale;
            if (shop->mode == 2) {
                distance = 215.0f - x;
                if (distance < 0)
                    distance = -distance;
                left = 0x80 - (int)distance;
                distance = 215.0f - (x + size);
                if (distance < 0)
                    distance = -distance;
                right = 0x80 - (int)distance;
            } else {
                distance = 256.0f - x;
                if (distance < 0)
                    distance = -distance;
                left = 0x80 - (int)(distance * 0.75);
                distance = 256.0f - (x + size);
                if (distance < 0)
                    distance = -distance;
                right = 0x80 - (int)(distance * 0.75);
            }
            if (left < 0)
                left = 0;
            argb = color;
            if (right < 0)
                right = 0;
            left <<= 24;
            right <<= 24;
            colors[0] = left | argb;
            colors[1] = right | argb;
            colors[2] = left | argb;
            colors[3] = right | argb;
            if (*cursor < 0x20) {
                argb = colors[0];
                shade = (argb & 0xFF) + ((argb >> 8) & 0xFF) + ((argb >> 16) & 0xFF);
                shade /= 3;
                tint = (int)(argb & 0xFF000000);
                tint += shade << 16;
                tint += shade << 8;
                shade += tint;
                gray[0] = shade;
                gray[1] = shade;
                gray[2] = shade;
                gray[3] = shade;
                EmitTexturedRectangle(x, y + top, scale * 24.0f, scale * 16.0f, glyphs[*cursor].u,
                              glyphs[*cursor].v, 24, 16, gray, texture);
            }
            if ((u8)(*cursor + 0x80) < 0x28) {
                g = (Glyph_002F97A0 *)((((u8)*cursor + 0x40) << 2) + (int)glyphs);
                dx = IntToFloat(g->adv) * scale;
                dy = IntToFloat(g->top) * scale;
                EmitTexturedRectangle(x + dx, y + dy, size, size, g->u, g->v, 16, 16, colors, texture);
            } else if ((u8)*cursor > 0x20) {
                EmitTexturedRectangle(x, y + top, size, size, glyphs[*cursor].u, glyphs[*cursor].v, 16, 16,
                              colors, texture);
            }
            x += IntToFloat(glyphs[*cursor].adv) * scale;
        }
        count++;
        if (count == limit)
            break;
        cursor++;
    } while (*cursor != 0);
}
