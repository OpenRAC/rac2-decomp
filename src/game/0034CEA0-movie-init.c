#include "ps2_hw.h"
#include "names.h"
typedef unsigned char u8;
extern char *D_001B23CC[] __attribute__((sda));
extern char *ref_L00_0034F408_00 __attribute__((sda));
extern int D_001B23C8 __attribute__((sda));
extern void func_0026FEB8(void *, ...);
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
extern void func_0012F690(void);
extern void func_00350590(u8 *);
extern int func_00351720(void *, int, int, void *, int, int, void *, int);
extern int func_0034F7D8(void *, void *, int, int);
extern int func_00351828(void *, int, int, void *, char *);
extern void func_00351DE8(void *, int, int, int);
extern int func_0011AA20(struct AudioDecoderThreadArgs *);
extern int func_0011AA40(int, void *);
extern int func_00350698(u8 *, int, int);
extern int func_00126DC0(void *);
extern int func_0011A930(int, void *, int);
extern int func_0011B6C0(int);
extern void func_0034FFC0();
extern void func_00350190();
extern void func_00351A80();
extern int func_00350240();
extern int func_00350378();
/* func_0034F408(int, int, int) */
/* Starts the movie player: sets up the buffers, decoder thread and handlers, and opens the stream. Returns 1 if it opened. */
int func_0034F408(int stream_source, int source_mode, int callback_context) {
    struct AudioDecoderThreadArgs decoder_thread;
    int thread_id;
    int opened;
    D_CTRL |= 3;
    D_STAT = 4;
    readBufCreate(ref_L00_0034F408_00);
    InitMpegLibrary();
    VideoDecInit(((char *)gMoviePlayerState[0]) + 0xD9048, D_001B23C8 + 0x1D05C0, 0xEB768,
                  ((char *)gMoviePlayerState[0]) + 0x52040, D_001B23C8 + 0x1C7180, 0x100,
                  ((char *)gMoviePlayerState[0]) + 0xD6040, 0x200);
    InitMovieAudioDecoder(((char *)gMoviePlayerState[0]) + 0xD9100, ((char *)gMoviePlayerState[0]) + 0x50040, 0x2000,
                  D_001B23C8 + 0x1D01C0);
    CallVideoHelperAndReturnOne(((char *)gMoviePlayerState[0]) + 0xD9048, 0, 0, FeedMovieDecoderCallback, gMoviePlayerState[0]);
    CallVideoHelperAndReturnOne(((char *)gMoviePlayerState[0]) + 0xD9048, 3, callback_context, CopyPacketToAudioBuffer, gMoviePlayerState[0]);
    VoBufInit(((char *)gMoviePlayerState[0]) + 0xD9168,
                  (D_001B23C8 & 0x0FFFFFFF) | 0x20000000,
                  D_001B23C8 + 0x1A0000, 2);
    decoder_thread.stack = ((char *)gMoviePlayerState[0]) + 0xD2040;
    decoder_thread.entry = VideoDecStart;
    decoder_thread.stack_size = 0x4000;
    decoder_thread.priority = 1;
    decoder_thread.gp = ref_L00_0034F408_02;
    decoder_thread.gs_tag = 0;
    thread_id = CreateThread(&decoder_thread);
    D_001B23D0 = thread_id;
    StartThread(thread_id, ((char *)gMoviePlayerState[0]) + 0xD9048);
    if (SetReadBufferRange(((char *)gMoviePlayerState[0]) + 0xD9040, stream_source, source_mode) == 0) {
        opened = 0;
        STUB_printf(ref_L00_0034F408_01);
    } else {
        opened = 1;
    }
    func_00126DC0(vblankHandler);
    ((struct AudioDecoderState *)gMoviePlayerState[0])->dmac_handler_id = AddDmacHandler(2, ReleaseMovieVideoFrame, 0);
    ProcessKernelQueueEntryD(2);
    return opened;
}
