#include "names.h"
typedef unsigned char u8;
extern int func_00351CD8(void *, int *);
extern int func_00351D00(void);
extern int func_00351D38(void);
extern int func_00351D68(void);
extern int func_00351D98(void *, void *);
extern void func_00351888(u8 *);
extern void func_0012F738(void *);
extern void func_0012FA70(void *, int, void *, int);
extern void func_003508A0(void *, int, int, int, int, int);

/* Sets up the video decoder, registers its callbacks and initialises its input buffer. */
int func_00351720(char *decoder, int unused1, int unused2, int a, int b, int c, int d, int e)
{
    CreateMpegDecoder(decoder);
    SetMpegCallback(decoder, 0, VideoDecPrintMessage, 0);
    SetMpegCallback(decoder, 1, VideoDecCallbackAddDma, 0);
    SetMpegCallback(decoder, 2, VideoDecCallbackSaveState, 0);
    SetMpegCallback(decoder, 3, VideoDecCallbackRestoreState, 0);
    SetMpegCallback(decoder, 5, VideoDecCallbackGetTimestamp, 0);
    VideoDecResetState((u8 *)decoder);
    ViBufInit(decoder + 0x48, a, b, c, d, e);
    return 1;
}
