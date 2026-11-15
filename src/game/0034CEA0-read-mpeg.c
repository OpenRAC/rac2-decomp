/* func_0034F048, RAC1's read_mpeg. In its own unit because it is in the boot and the 27 levels,
 * and func_0034F3D8 and func_0034F7A8 (defined in 0034CEA0.c) are only in the boot's catalogue. */
#include "common.h"

extern char *D_001B23CC[] __attribute__((sda));
extern int D_001A7478[] __attribute__((sda));
extern int D_001A7A00[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
typedef struct { char pad[0x1a0]; union { unsigned long long held; int words[2]; } buttons; } MoviePad;
extern MoviePad D_00138180;
typedef struct { char pad[0x5c]; int f5C; } MovieVoice;
extern MovieVoice D_00188660;
extern s32 func_0011AEA0(s32);
extern int func_001261F0(int);
extern void func_002B9000(void);
extern void func_003518C8(char *);
extern s32 func_003505B0(u8 *, u8 **);
extern int func_003506B0(int *, u8 *, int, int);
extern void func_003505E0(char *, int);
extern void func_0034F7A8(void);
extern void func_0034F3B8(void);
extern s32 func_00350628(u8 *, s32 *);
extern int func_0012EB30(char *, int, int, char *, int);
extern s32 func_00350670(u8 *, s32);
extern int func_00351E58(char *);
extern void func_003501E0(int);
extern void func_0034F8C0(u8 *);
extern int func_003518D8(char *);
extern int func_00351960(char *);
extern int func_00351A38(char *);
extern void func_00350230(void);
extern void func_0034F918(u8 *);
extern void func_00132888(int, int);
extern void func_00132028(void);
extern int func_0034F3D8(void);
extern int func_00351F28(char *);

/* Plays the movie stream: reads data, feeds the decoder, and stops early if the player presses the skip buttons. Returns 1 if skipped. */
int func_0034F048(char *vd, char *rb, int *file) {
    int armed = 0;
    int aborted = 0;
    int started = 0;
    int left = *file;
    int toread;
    int n;
    int got;
    int avail;
    int used;
    u8 *put;
    s32 get;

    FlushCache(0);
    toread = left;
    FlushCache(2);
    GetGsCurrentField(0);

    while (left >= 5 && videoDecGetState(vd) != 3) {
        int hit = 0;

        PollPadPorts();
        if (gPadState.buttons.words[0] == 0) armed = 1;
        if (armed && (n = D_001A7478[0]) != 3) {
            if (n == 2 && gPadState.buttons.words[0] != 0 &&
                gPadState.buttons.words[1] == 0) {
                hit = 1;
            } else if (((D_001A7A00[2] & 0xffff0000) || D_001A7478[0] != 0 ||
                        gCurrentMapIndex[0] <= 0) && (gPadState.buttons.words[1] & 0x800)) {
                hit = 1;
            } else if ((gPadState.buttons.held & 0x8000000000FULL) == 0x8000000000FULL) {
                hit = 1;
            } else {
                hit = 0;
            }
        }
        if (hit && !aborted) {
            aborted = 1;
            VideoDecSetStateRunning(gMoviePlayerState[0] + 0xD9048);
        }
        n = readBufBeginPut((u8 *)rb, &put);
        if (toread > 0 && n > 0xFFFF) {
            got = ReadDiscSectorsToBuffer(file, put, 0x10000, 0);
            readBufEndPut(rb, got);
            toread -= got;
        }
        proceedAudio();
        StartMovieDecoderDma();
        avail = readBufBeginGet((u8 *)rb, &get);
        if (avail > 0) {
            int size = *(int *)(rb + 0x50008);

            used = func_0012EB30(vd, get, avail, rb, size);
            readBufEndGet((u8 *)rb, used);
            left -= used;
        }
        proceedAudio();
        if (!started && voBufIsFull(gMoviePlayerState[0] + 0xD9168) && IsMovieAudioBufferFull()) {
            started = 1;
            WaitForMovieFieldStart(1);
            StartMovieAudioPlayback((u8 *)(gMoviePlayerState[0] + 0xD9100));
        }
    }

    SendSoundCommand9(5, 0);
    snd_Pump();
    while (!VideoDecSendPacket(vd)) {
        proceedAudio();
        StartMovieDecoderDma();
    }
    while (!func_00351A38(vd) && videoDecGetState(vd) != 3 && !VoBufIsEmpty(gMoviePlayerState[0] + 0xD9168)) {
        StartMovieDecoderDma();
    }
    ClearMovieFlag();
    StopMovieAudioPlayback((u8 *)(gMoviePlayerState[0] + 0xD9100));
    SendSoundCommand9(5, gSoundState.f5C);
    snd_Pump();
    return aborted;
}
