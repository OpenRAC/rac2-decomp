#include "names.h"
typedef unsigned char u8;
extern int mpeg_dec_print_message(void *, int *);
extern int mpeg_dec_callback_add_dma(void);
extern int mpeg_dec_callback_save_state(void);
extern int mpeg_dec_callback_restore_state(void);
extern int mpeg_dec_callback_get_timestamp(void *, void *);
extern void mpeg_dec_reset_state(u8 *);
extern int sceMpegCreate(void *);
extern int sceMpegAddCallback(void *, int, void *, int);
extern int mpeg_vibuf_init(void *, int, int, int, int, int);

/* Sets up the video decoder, registers its callbacks and initialises its input buffer. */
int mpeg_dec_init(char *decoder, int unused1, int unused2, int a, int b, int c, int d, int e)
{
    sceMpegCreate(decoder);
    sceMpegAddCallback(decoder, 0, mpeg_dec_print_message, 0);
    sceMpegAddCallback(decoder, 1, mpeg_dec_callback_add_dma, 0);
    sceMpegAddCallback(decoder, 2, mpeg_dec_callback_save_state, 0);
    sceMpegAddCallback(decoder, 3, mpeg_dec_callback_restore_state, 0);
    sceMpegAddCallback(decoder, 5, mpeg_dec_callback_get_timestamp, 0);
    mpeg_dec_reset_state((u8 *)decoder);
    mpeg_vibuf_init(decoder + 0x48, a, b, c, d, e);
    return 1;
}
