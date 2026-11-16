#include "names.h"
/* func_PAL_00353D08, the PAL copy of func_00351B20: the same C, where rename func_0034FE18 becomes func_PAL_00352000; rename func_0012F950 becomes func_0012F948. */

typedef int s32;

typedef unsigned char u8;

/* func_003512B8 : rounds a field to a multiple of 2048 under a semaphore */
extern s32 WaitSema(s32);

extern void SignalSema(s32);

/* func_00351268 : waits, then combines two fields shifted by 11 */
extern s32 WaitSema(s32 a0);

extern void SignalSema(s32 a0);

typedef unsigned int u32;

extern int voBufIsFull(unsigned char *);

/* func_00351578 is matched in 00351578.c. */

typedef struct { unsigned long long first, second; int offset, count; } Transfer_3518F0;

extern int viBufModifyPts(void *, Transfer_3518F0 *);

/* a % b as a helper: once inlined, its zero-divisor check is tested against $0 */

/* func_00351310 : walks the transfer ring, trimming one message out of the slots */
int viBufModifyPts(void *owner, Transfer_3518F0 *message);

int mpeg_vibuf_add_timestamp(void *owner, Transfer_3518F0 *message, int unused);

/* func_00351720 is matched in 00351720.c. */

/* Forwards the byte count to the object's transfer buffer. */
/* Measured target: byte-identical across all 27 levels. */
/* Measured target: byte-identical across all 27 levels. */
s32 videoDecGetState(u8 *a0);

extern char *g_movie_player_state[] __attribute__((sda));
extern int mpeg_vibuf_add_timestamp(void *, Transfer_3518F0 *, int);

/* func_00351960 : builds a 16-byte packet (a 4-byte header copied from D_001AE860 and a
   12-byte body), asks the object for the two memory ranges it holds, and moves them into
   the packet.  The two addresses are turned into 32-bit engine addresses. */
typedef struct { char tag[4]; } Header_351960;

extern Header_351960 g_mpeg_packet_header;

/* These wrappers have different targets in the level programs. */
extern void mpeg_vobuf_reset(u8 *);
extern int mpeg_dec_run_loop_pal(void *);
extern void STUB_printf();
extern char g_str_mpeg_dec_loop_message[];
extern char g_str_mpeg_dec_loop_debug[];
extern int mpeg_read_indirect_word(void *);
extern void sceMpegReset(void *);
extern int mpeg_set_output_buffer(void *, void *, int);
extern void mpeg_start_decoder_dma(void);
extern void mpeg_set_debug_value(char *);
extern void *mpeg_vobuf_get_next_frame(char *);
extern void mpeg_vobuf_advance_write(u8 *);
extern void mpeg_build_frame_packet_pal(void *, void *, int, int, int);

/* Main video decode loop: waits for a free output frame, decodes into it, and passes it on until stopped (PAL). */
int mpeg_dec_run_loop_pal(void *decoder)
{
    int *object = decoder;
    int result = 1;
    void *packet;
    int i;

    while (mpeg_read_indirect_word(object) == 0) {
        if (videoDecGetState((u8 *)object) == 1) {
            result = -1;
            STUB_printf(g_str_mpeg_dec_loop_message);
            break;
        }
        while ((packet = mpeg_vobuf_get_next_frame(g_movie_player_state[0] + 0xD9168)) == 0)
            mpeg_start_decoder_dma();
        if (mpeg_set_output_buffer(object, packet, 0x340) < 0)
            mpeg_set_debug_value(g_str_mpeg_dec_loop_debug);
        if (object[2] == 0) {
            int a = object[0];
            int b = object[1];
            for (i = 0; i < *(int *)(g_movie_player_state[0] + 0xD9178); i++)
                mpeg_build_frame_packet_pal(*(char **)(g_movie_player_state[0] + 0xD916C) + i * 0x138C0 + 0x40,
                              *(char **)(g_movie_player_state[0] + 0xD9168) + i * 0xD0000, a, b, i);
        }
        mpeg_vobuf_advance_write((u8 *)(g_movie_player_state[0] + 0xD9168));
        mpeg_start_decoder_dma();
    }
    sceMpegReset(object);
    return result;
}

extern void STUB_printf(void *, int);

extern char *g_movie_player_state[] __attribute__((sda));
extern char *g_movie_player_state[] __attribute__((sda));
extern char *g_movie_player_state[] __attribute__((sda));
void mpeg_vobuf_reset(u8 *a0);

/* lot13 -- measured bodies with sizes recorded in the catalogue. */
s32 voBufIsFull(u8 *a0);

void mpeg_vobuf_advance_write(u8 *a0);
