#include "common.h"

/* func_US2_002F6E10, the USA v2.00 copy of func_002F5FB8: the same C, where the display slot's
   width and height become bytes followed by a pixel format short at 0xE (passed to the upload
   and put in TEX0 in place of 0x13), the TEX0 word sets bit 62 instead of bit 63, and the
   queued dialog voice is cleared before waiting for the sound streams. */
typedef struct { int sector; int size; } TocFile_002F5D40;
typedef struct {
    int header;
    int base;
    TocFile_002F5D40 files[0];
} Toc_002F5D40;
extern char g_copy_setup_data[];
extern int cutscene_map_id_to_index(int);
extern void gfx_reset_packet_buffer(void);
/* The dialog voice block: v2.00 clears the queued voice id before the movie plays. */
typedef struct { char pad[0x24]; int pendingVoice; } Voice_6E10;
extern Voice_6E10 g_music_state;

/* Plays the current FMV (D_001B220C, set up by func_002F5E20). With no stream it shows the
   message and ends the movie state. Otherwise it uploads the two movie textures into display
   slot 2, sets the slot's TEX0 word, waits for the sound streams to idle, then decodes frames into
   the two 64-aligned buffers until the stream or the scripted frame list ends, loading each
   chunk's sector and size from the table of contents. Finally it restores the texture, clears
   the slot and either chains the next scene or returns to the game. */
typedef unsigned long long U64_5FB8;
typedef struct { U64_5FB8 packet; unsigned short tex0, tex1; unsigned char width, height; short psm; } Display_5FB8;
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
extern void func_US2_0029DAD0(int, int);
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
extern void func_US2_00299CF0(void);
extern int load_read_disc_with_pause(char *,int,int);
extern int mpeg_play_movie_2(void *,void *,char *,char *,int,int);
extern int req_pop_queue(void *,int *,int *);
extern void func_00126DC0(void *);
extern void gfx_reset_record_list(void);
extern int request_begin_slot(int,int,int,int,unsigned char *);
void func_US2_002F6E10(void)
{
    long packet[12] __attribute__((aligned(16)));
    long low, high;
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
        func_US2_0029DAD0((int)ref_L00_002F5FB8_04,-1);
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
    func_00126288(packet,(short)base,(short)((1 << display->width) >> 6),display->psm,0,0,(short)(1 << display->width),(short)(1 << display->height));
    FlushCache(0);
    sceGsExecLoadImage(packet,ref_L00_002F5FB8_08 + display->tex0 * 16);
    gfx_wait_paths_idle(0,0);
    func_00126288(packet,0x3F6C,1,0,0,0,16,16);
    FlushCache(0);
    sceGsExecLoadImage(packet,ref_L00_002F5FB8_08 + display->tex1 * 16);
    gfx_wait_paths_idle(0,0);
    highFlags = 0x7ED8400000000L;
    low = ((long)((1 << display->width) >> 6) << 14) | (long)base;
    low = low | ((long)display->psm << 20);
    low = low | ((long)display->width << 26);
    low = low | ((long)display->height << 30);
    high = low | highFlags;
    displays[textureIndex].packet = high | 0x4000000000000000ULL;
    FlushCache(0);
    snd_clear_all_voices();
    snd_wait_for_music_idle();
    snd_CheckLoadInProgress(0);
    g_music_state.pendingVoice = -1;
    while (g_memcard_state[0x15C/4] >= 3 || g_memcard_state[0x164/4] >= 0) func_US2_00299CF0();
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

