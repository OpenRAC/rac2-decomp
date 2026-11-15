#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef struct {
    u8 pad0[0x20];
    u8 state;
    u8 pad21[0x21];
    u8 primary, secondary;
    u8 pad44[0x1c];
    u8 flags;
    u8 pad61[0x5b];
    u8 counter;
} AnimationMoby;
typedef struct {
    u8 pad0[0x34];
    int state, reserved;
    u8 *buffer;
    int offset;
    AnimationMoby *moby;
} AnimationStream;
typedef struct { u8 pad[0x48]; u8 *tables[4]; } AnimationClass;
extern short D_001A63AC;
extern u8 D_001F291B;
extern u8 D_001CEC85;
extern AnimationClass *D_001CDB80[];
extern u8 D_001A7A0A[] __attribute__((sda));
typedef struct { u8 pad[0x6c]; short count; u8 pad6e[4]; short phase; } Dialogue;
extern Dialogue g_music_state;
extern void fast_decompress(void *, void *);
extern void relocate_asset_entry_pointers(AnimationClass *, int);
extern int snd_resume_music_stream(void);
extern void anim_start_blended(AnimationMoby *, int, int, int);

/* Corresponds to RAC1 update_streamed_moby_animation. */
/* Updates the streamed animation of a talking character: waits for the animation data to load, then plays idle and talking animations in turn. */
int update_streamed_moby_animation(AnimationStream *stream)
{
    AnimationMoby *moby;
    u8 *header;
    AnimationClass **resource;
    int i, animation;
    u8 *table;
    Dialogue *dialogue;
    switch (stream->state) {
    case 0:
        if (D_001A63AC != 0) break;
        stream->state = 3;
        break;
    case 1:
        if (D_001A63AC != 0) break;
        D_001F291B = 0;
        fast_decompress(stream->buffer + stream->offset, stream->buffer);
        resource = &D_001CDB80[D_001CEC85];
        header = stream->buffer;
        for (i = 0; i < 3; i++) {
            table = stream->buffer + *(int *)(header + (i << 3));
            (*resource)->tables[i + 1] = table;
            relocate_asset_entry_pointers(*resource, i + 1);
        }
        stream->state = 2;
        if (D_001A7A0A[0] == 0) stream->moby->state = 0;
        else stream->moby->state = 4;
        stream->moby->counter = 0;
        break;
    case 2:
        moby = stream->moby;
        switch (moby->state) {
        case 0: case 2: case 4:
            animation = moby->state >> 1;
            moby->counter++;
            if (moby->counter > 120) moby->counter = 120;
            if (moby->counter < 120) return 0;
            dialogue = &g_music_state;
            if (dialogue->phase != 3) return 0;
            if (dialogue->count >= 6000) return 0;
            moby->counter = 0;
            moby->state++;
            anim_start_blended(moby, animation + 1, 0, 24);
            break;
        case 1: case 3: case 5:
            if (moby->counter == 0 && moby->primary == moby->secondary) {
                snd_resume_music_stream();
                moby->counter = 1;
            }
            if (moby->flags & 2) {
                if (moby->state == 1) moby->state = moby->state + 1;
                else moby->state = 6;
                moby->counter = 0;
                anim_start_blended(moby, 0, 0, 24);
            }
            break;
        case 6:
            moby->counter++;
            if (moby->counter > 240) moby->counter = 240;
            if (moby->counter < 240) return 0;
            if (D_001A7A0A[0] == 0) moby->state = 0;
            else moby->state = 4;
            moby->counter = 0;
            break;
        }
        break;
    }
    return 0;
}
