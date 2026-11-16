#include "names.h"
/* func_PAL_00351230, the PAL copy of func_0034F048: the same C, where rename func_002B9000 becomes func_PAL_002B9BB8; rename func_0012EB30 becomes func_0012EB28. */
/* func_PAL_00351230, RAC1's read_mpeg. In its own unit because it is in the boot and the 27 levels,
 * and func_0034F3D8 and func_0034F7A8 (defined in 0034CEA0.c) are only in the boot's catalogue. */
#include "common.h"

extern char *g_movie_player_state[] __attribute__((sda));
extern int g_loader_state_word[] __attribute__((sda));
extern int g_player_stats[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
typedef struct { char pad[0x1a0]; union { unsigned long long held; int words[2]; } buttons; } MoviePad;
extern MoviePad g_pad_state;
typedef struct { char pad[0x5c]; int f5C; } MovieVoice;
extern MovieVoice g_sound_state;
extern void FlushCache(s32);
extern int sceGsSyncV(int);
extern void pad_poll_ports_pal(void);
extern void mpeg_dec_set_state_running(char *);
extern s32 readBufBeginPut(u8 *, u8 **);
extern int mpeg_read_disc_sectors(int *, u8 *, int, int);
extern void readBufEndPut(char *, int);
extern void proceedAudio(void);
extern void mpeg_start_decoder_dma(void);
extern s32 readBufBeginGet(u8 *, s32 *);
extern int sceMpegDemuxPssRing(char *, int, int, char *, int);
extern s32 readBufEndGet(u8 *, s32);
extern int voBufIsFull(char *);
extern void mpeg_wait_for_field_start(int);
extern void mpeg_start_audio_playback(u8 *);
extern int videoDecGetState(char *);
extern int mpeg_dec_send_packet(char *);
extern int func_00351A38(char *);
extern void mpeg_clear_flag(void);
extern void mpeg_stop_audio_playback(u8 *);
extern void snd_send_cmd9(int, int);
extern int snd_Pump(void);
extern int mpeg_is_audio_buffer_full(void);
extern int mpeg_vobuf_is_empty(char *);

/* Plays the movie stream: reads data, feeds the decoder, and stops early if the player presses the skip buttons. Returns 1 if skipped (PAL). */
int read_mpeg_pal(char *video_dec, char *read_buf, int *file_info) {
    int pad_released = 0;
    int aborted = 0;
    int started = 0;
    int bytes_left = *file_info;
    int bytes_to_read;
    int count;
    int bytes_read;
    int bytes_avail;
    int used;
    u8 *put;
    s32 get;

    FlushCache(0);
    bytes_to_read = bytes_left;
    FlushCache(2);
    sceGsSyncV(0);

    while (bytes_left >= 5 && videoDecGetState(video_dec) != 3) {
        int hit = 0;

        pad_poll_ports_pal();
        if (g_pad_state.buttons.words[0] == 0) pad_released = 1;
        if (pad_released && (count = g_loader_state_word[0]) != 3) {
            if (count == 2 && g_pad_state.buttons.words[0] != 0 &&
                g_pad_state.buttons.words[1] == 0) {
                hit = 1;
            } else if (((g_player_stats[2] & 0xffff0000) || g_loader_state_word[0] != 0 ||
                        g_current_map_index[0] <= 0) && (g_pad_state.buttons.words[1] & 0x800)) {
                hit = 1;
            } else if ((g_pad_state.buttons.held & 0x8000000000FULL) == 0x8000000000FULL) {
                hit = 1;
            } else {
                hit = 0;
            }
        }
        if (hit && !aborted) {
            aborted = 1;
            mpeg_dec_set_state_running(g_movie_player_state[0] + 0xD9048);
        }
        count = readBufBeginPut((u8 *)read_buf, &put);
        if (bytes_to_read > 0 && count > 0xFFFF) {
            bytes_read = mpeg_read_disc_sectors(file_info, put, 0x10000, 0);
            readBufEndPut(read_buf, bytes_read);
            bytes_to_read -= bytes_read;
        }
        proceedAudio();
        mpeg_start_decoder_dma();
        bytes_avail = readBufBeginGet((u8 *)read_buf, &get);
        if (bytes_avail > 0) {
            int size = *(int *)(read_buf + 0x50008);

            used = sceMpegDemuxPssRing(video_dec, get, bytes_avail, read_buf, size);
            readBufEndGet((u8 *)read_buf, used);
            bytes_left -= used;
        }
        proceedAudio();
        if (!started && voBufIsFull(g_movie_player_state[0] + 0xD9168) && mpeg_is_audio_buffer_full()) {
            started = 1;
            mpeg_wait_for_field_start(1);
            mpeg_start_audio_playback((u8 *)(g_movie_player_state[0] + 0xD9100));
        }
    }

    snd_send_cmd9(5, 0);
    snd_Pump();
    while (!mpeg_dec_send_packet(video_dec)) {
        proceedAudio();
        mpeg_start_decoder_dma();
    }
    while (!func_00351A38(video_dec) && videoDecGetState(video_dec) != 3 && !mpeg_vobuf_is_empty(g_movie_player_state[0] + 0xD9168)) {
        mpeg_start_decoder_dma();
    }
    mpeg_clear_flag();
    mpeg_stop_audio_playback((u8 *)(g_movie_player_state[0] + 0xD9100));
    snd_send_cmd9(5, g_sound_state.f5C);
    snd_Pump();
    return aborted;
}
