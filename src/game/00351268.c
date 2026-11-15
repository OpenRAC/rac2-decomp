#include "names.h"


typedef int s32;

typedef unsigned char u8;

/* func_003512B8 : rounds a field to a multiple of 2048 under a semaphore */
extern s32 WaitSema(s32);

extern s32 SignalSema(s32);

/* func_00351268 : waits, then combines two fields shifted by 11 */
extern s32 WaitSema(s32 a0);

extern s32 SignalSema(s32 a0);

extern int mpeg_vibuf_get_queued_bytes(unsigned char *owner);

/* Returns how many bytes are waiting in the video buffer. */
s32 mpeg_vibuf_get_queued_bytes(u8 *buf) {
    s32 bytes;
    WaitSema(*(s32 *)(buf + 0x40));
    bytes = (*(s32 *)(buf + 0x10) << 11) + *(s32 *)(buf + 0x14);
    SignalSema(*(s32 *)(buf + 0x40));
    return bytes;
}
