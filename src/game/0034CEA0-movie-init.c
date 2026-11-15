#include "ps2_hw.h"
#include "names.h"
typedef unsigned char u8;
extern char *g_movie_player_state[] __attribute__((sda));
extern char *ref_L00_0034F408_00 __attribute__((sda));
extern int D_001B23C8 __attribute__((sda));
extern void STUB_printf(void *, ...);
struct AudioDecoderState {
    char pad0[0xD90F8];
    int dmac_handler_id;
    int intc_handler_id;
};
struct AudioDecoderThreadArgs {
    char pad0[4];
    void (*entry)();
    void *stack;
    int stack_size;
    void *gp;
    int priority;
    char pad18[8];
    int gs_tag;
    char pad24[0xC];
};
extern int D_001B23D0 __attribute__((sda));
extern char ref_L00_0034F408_01[];
extern char ref_L00_0034F408_02[] __attribute__((sda));
extern void sceMpegInit(void);
extern void readBufCreate(u8 *);
extern int mpeg_dec_init(void *, int, int, void *, int, int, void *, int);
extern int mpeg_audio_init(void *, void *, int, int);
extern int mpeg_call_helper_return_one(void *, int, int, void *, char *);
extern void mpeg_vobuf_init(void *, int, int, int);
extern int CreateThread(struct AudioDecoderThreadArgs *);
extern int StartThread(int, void *);
extern int mpeg_set_read_buffer_range(u8 *, int, int);
extern int func_00126DC0(void *);
extern int AddDmacHandler(int, void *, int);
extern void kernel_process_queue_entry_d(int);
extern int vblankHandler();
extern int mpeg_release_video_frame();
extern void mpeg_dec_start();
extern int mpeg_feed_decoder_callback();
extern int mpeg_copy_packet_to_audio_buffer();
/* func_0034F408(int, int, int) */
/* Starts the movie player: sets up the buffers, decoder thread and handlers, and opens the stream. Returns 1 if it opened. */
int mpeg_start_player(int stream_source, int source_mode, int callback_context) {
    struct AudioDecoderThreadArgs decoder_thread;
    int thread_id;
    int opened;
    D_CTRL |= 3;
    D_STAT = 4;
    readBufCreate(ref_L00_0034F408_00);
    sceMpegInit();
    mpeg_dec_init(((char *)g_movie_player_state[0]) + 0xD9048, D_001B23C8 + 0x1D05C0, 0xEB768,
                  ((char *)g_movie_player_state[0]) + 0x52040, D_001B23C8 + 0x1C7180, 0x100,
                  ((char *)g_movie_player_state[0]) + 0xD6040, 0x200);
    mpeg_audio_init(((char *)g_movie_player_state[0]) + 0xD9100, ((char *)g_movie_player_state[0]) + 0x50040, 0x2000,
                  D_001B23C8 + 0x1D01C0);
    mpeg_call_helper_return_one(((char *)g_movie_player_state[0]) + 0xD9048, 0, 0, mpeg_feed_decoder_callback, g_movie_player_state[0]);
    mpeg_call_helper_return_one(((char *)g_movie_player_state[0]) + 0xD9048, 3, callback_context, mpeg_copy_packet_to_audio_buffer, g_movie_player_state[0]);
    mpeg_vobuf_init(((char *)g_movie_player_state[0]) + 0xD9168,
                  (D_001B23C8 & 0x0FFFFFFF) | 0x20000000,
                  D_001B23C8 + 0x1A0000, 2);
    decoder_thread.stack = ((char *)g_movie_player_state[0]) + 0xD2040;
    decoder_thread.entry = mpeg_dec_start;
    decoder_thread.stack_size = 0x4000;
    decoder_thread.priority = 1;
    decoder_thread.gp = ref_L00_0034F408_02;
    decoder_thread.gs_tag = 0;
    thread_id = CreateThread(&decoder_thread);
    D_001B23D0 = thread_id;
    StartThread(thread_id, ((char *)g_movie_player_state[0]) + 0xD9048);
    if (mpeg_set_read_buffer_range(((char *)g_movie_player_state[0]) + 0xD9040, stream_source, source_mode) == 0) {
        opened = 0;
        STUB_printf(ref_L00_0034F408_01);
    } else {
        opened = 1;
    }
    func_00126DC0(vblankHandler);
    ((struct AudioDecoderState *)g_movie_player_state[0])->dmac_handler_id = AddDmacHandler(2, mpeg_release_video_frame, 0);
    kernel_process_queue_entry_d(2);
    return opened;
}
