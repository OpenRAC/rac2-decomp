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
extern short g_sequence_active_flag;
extern u8 g_map_selection_flag;
extern u8 g_streamed_anim_slot;
extern AnimationClass *g_class_cache_objects[];
extern u8 g_extras_unlocked_flag[] __attribute__((sda));
typedef struct { u8 pad[0x6c]; short count; u8 pad6e[4]; short phase; } Dialogue;
extern Dialogue g_music_state;
extern int fast_decompress_pal(void *, void *);
extern void relocate_asset_entry_pointers(AnimationClass *, int);
extern int snd_resume_music_stream(void);
extern void func_PAL_002A7E68(AnimationMoby *, int, int, int);

/* Corresponds to RAC1 update_streamed_moby_animation. */
int func_PAL_002DEEA8(AnimationStream *stream)
{
    AnimationMoby *moby;
    u8 *header;
    AnimationClass **resource;
    int i, animation;
    u8 *table;
    Dialogue *dialogue;
    switch (stream->state) {
    case 0:
        if (g_sequence_active_flag != 0) break;
        stream->state = 3;
        break;
    case 1:
        if (g_sequence_active_flag != 0) break;
        g_map_selection_flag = 0;
        fast_decompress_pal(stream->buffer + stream->offset, stream->buffer);
        resource = &g_class_cache_objects[g_streamed_anim_slot];
        header = stream->buffer;
        for (i = 0; i < 3; i++) {
            table = stream->buffer + *(int *)(header + (i << 3));
            (*resource)->tables[i + 1] = table;
            relocate_asset_entry_pointers(*resource, i + 1);
        }
        stream->state = 2;
        if (g_extras_unlocked_flag[0] == 0) stream->moby->state = 0;
        else stream->moby->state = 4;
        stream->moby->counter = 0;
        break;
    case 2:
        moby = stream->moby;
        switch (moby->state) {
        case 0: case 2: case 4:
            animation = moby->state >> 1;
            moby->counter++;
            if (moby->counter > 100) moby->counter = 100;
            if (moby->counter < 100) return 0;
            dialogue = &g_music_state;
            if (dialogue->phase != 3) return 0;
            if (dialogue->count >= 6000) return 0;
            moby->counter = 0;
            moby->state++;
            func_PAL_002A7E68(moby, animation + 1, 0, 20);
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
                func_PAL_002A7E68(moby, 0, 0, 20);
            }
            break;
        case 6:
            moby->counter++;
            if (moby->counter > 200) moby->counter = 200;
            if (moby->counter < 200) return 0;
            if (g_extras_unlocked_flag[0] == 0) moby->state = 0;
            else moby->state = 4;
            moby->counter = 0;
            break;
        }
        break;
    }
    return 0;
}
