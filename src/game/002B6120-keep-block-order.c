#include "names.h"
/* music_Transition, apart from 002B6120.c for its flag: retail keeps the success
   path's `return 1` in a block of its own after the call, which needs
   -frac2-keep-block-order (no cygnus_merge_blocks). */
typedef unsigned char u8;

typedef struct { int offset, size; } SoundEntry;

typedef struct { char pad[0x52fc]; int base; SoundEntry entries[1]; } SoundTable;

typedef struct {
    unsigned int handle;
    short track, volume, flags, state, fade, unknown, crossfade, unknown2;
    int poll_interval, sample_rate;
    char tail[8];
} StreamChannel;

typedef struct { u8 pad[0x44]; StreamChannel channel[3]; } StreamState;

extern u8 g_music_state[];

extern int g_copy_setup_data[];

extern int func_00133350(int, int, int, int, int, int, int, int, int, int,
                         void (*)(int, long), unsigned long);

extern void request_store_result_move_to_done(int, long);

/* If the third stream channel is idle (handle 0) and table entry index is present, claim
   it (handle -1, state 1, crossfade 1, track, mode, 10 / 48000, volume) and start the
   entry (offset plus the table base) on it with flag 0x20; return 1 if it was started.
   The nested if/else with `return 1` after the join is RAC1's music_Transition: the
   success path ends in the call, so the call stays at the end of its block and the
   scheduler keeps retail's order. */
/* Starts a music track on the third stream channel if it is free and returns 1 when it started. */
int snd_start_music_transition(int track, int index, int mode, int volume)
{
    StreamState *s = (StreamState *)g_music_state;
    SoundTable *d;
    long first;
    int offset;

    if (s->channel[2].handle == 0) {
        d = (SoundTable *)g_copy_setup_data;
        offset = d->entries[index].offset;
        if (offset) {
            s->channel[2].flags = mode;
            s->channel[2].handle = 0xffffffffU;
            s->channel[2].track = track;
            s->channel[2].poll_interval = 10;
            s->channel[2].sample_rate = 48000;
            s->channel[2].state = 1;
            s->channel[2].crossfade = 1;
            s->channel[2].volume = volume;
            first = offset + d->base;
            func_00133350(first, 0, 0, 0, (short)volume, 0, 1, 0, 0, 32,
                          request_store_result_move_to_done, (unsigned int)&s->channel[2]);
        } else {
            return 0;
        }
    } else {
        return 0;
    }
    return 1;
}
