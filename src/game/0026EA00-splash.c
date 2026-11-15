#include "include_asm.h"
#include "names.h"

typedef struct { char prefix[20]; int *data; } SplashState;
extern SplashState D_001BAEC0;
extern int D_001A72DC[] __attribute__((sda));
extern void func_0029D4D0(int, void *);
extern int func_0011AEA0(int);
extern void func_002FC1D8(void);
extern void func_002FCB00(void *, int, int, int);
extern void func_0027B858(void);
extern void func_0027DDC0(int, int, int, int);
extern void func_00284FC0(void);
extern void func_00285338(void);
extern void func_002FC280(void);
extern void func_002FC3C0(int);
extern int func_001244B8(int, int);
extern int func_001261F0(int);

/* Draw the loaded splash image over 65 frames, fading its alpha from 128 to 0. */
void func_0026EA00(int arg)
{
    int *data;
    int count;

    fast_decompress(arg, D_001BAEC0.data);
    FlushCache(0);
    for (count = 0x80; count >= 0; count -= 2) {
        ResetPacketBuffer();
        data = D_001BAEC0.data;
        UploadTextureBlocksReturnTex0(data + 4, D_001A72DC[0], data[0], data[1]);
        WriteClearColorPackets();
        SetClearColorPacket(0, 0, 0, count);
        PutDrawBufferSmall();
        QueueSecondStripPacket();
        FlushCache(0);
        SubmitBufferedDmaChain();
        WaitForDmaStatusBits(1);
        WaitGsPathsIdle(0, 0);
        GetGsCurrentField(0);
    }
}
