/* func_002B6958 in its own unit: D_001AA170 is a 32-byte small-data record (its address comes
   from $gp and its flags are read with lhu 0x1A), so the file is built with -G8 and the
   assembler with -G32 (config/cflags.txt). */
#include "common.h"

typedef struct { int offset, size; } SoundEntry;

/* The sound table of contents at D_0014B540, as far as this function shows it. */
typedef struct {
    u8 pad0[0x2624];
    int base1;                  /* 0x2624: base of the 1000 and 6000 ranges */
    int ids1000[254];           /* 0x2628 */
    int ids6000[5][256];        /* 0x2A20: per language */
    int pad3E20;
    int base4;                  /* 0x3E24: base of the 4000 and 5000 ranges */
    u8 pad3E28[0x50];
    int ids4000[8][83];         /* 0x3E78: a pair per language */
    u8 pad48D8[0xB8];
    SoundEntry ids5000[301];    /* 0x4990 */
    int pad52F8;
    int base2;                  /* 0x52FC: base of the 2000 and 3000 ranges */
    SoundEntry ids2000[1];      /* 0x5300 */
} SoundToc;

typedef struct {
    unsigned int handle;
    short track, volume, flags, state, fade, unknown, crossfade, unknown2;
    int poll_interval, sample_rate;
    void *object;
    int slot;
} StreamChannel;

typedef struct { u8 pad[0x44]; StreamChannel channel[3]; } StreamState;

typedef struct { u8 pad[0x1a]; unsigned short flags; u8 rest[4]; } StreamSoundDef;

typedef struct {
    u8 pad[0x70];
    u32 handle;
    u8 active, bits;
    short unk;
    void *def;
    unsigned short defFlags;
    short sentinel, volume, zero;
    int zero2;
    void *object;
    int zero3;
    float position[4];
    u8 clear[16];
} SoundAnchor;

extern u8 g_music_state[];
extern SoundToc g_copy_setup_data;
extern u8 g_stream_sound_table[];
extern u8 g_sound_state[];
extern u8 g_language[] __attribute__((sda));
extern u8 g_stream_sound_def[32] __attribute__((sda));
extern int snd_find_free_voice(void *);
extern void vec_clear_128(void *);
extern void request_store_result_and_advance(int, long);
extern int func_00133350(int, int, int, int, int, int, int, int, int, int,
                         void (*)(int, long), unsigned long);

#define STATE ((StreamState *)D_001A63A8)

/* Starts a sound on the second stream channel by id, picking the right language, and attaches it to an object if given. */
void snd_play_stream_by_id(int id, int mode, void *object, int volume)
{
    int first, second, flags = 2, slot, bits;
    SoundAnchor *sound;

    if (STATE->channel[1].handle) return;
    first = 0;
    second = 0;
    if (id >= 6000) {
        int lang, offset;
        lang = g_language[0];
        if (lang) lang--;
        offset = ((int (*)[256])g_copy_setup_data.ids6000)[lang][id - 6000];
        if (offset) first = offset + g_copy_setup_data.base1;
        flags = 6;
    } else if (id >= 5000) {
        int offset = g_copy_setup_data.ids5000[id - 5000].offset;
        if (offset) first = g_copy_setup_data.base4 + offset;
    } else if (id >= 4000) {
        if (((int (*)[83])g_copy_setup_data.ids4000)[id - 4000][g_language[0] * 2]) {
            int offset2;
            /* base4 through the struct puts the table's own address in a register before the
               second entry is read, so cse builds that entry's address in full, as retail does,
               instead of as the first entry's address plus 4. */
            first = g_copy_setup_data.base4
                + ((int (*)[83])g_copy_setup_data.ids4000)[id - 4000][g_language[0] * 2];
            offset2 = ((int (*)[83])g_copy_setup_data.ids4000)[id - 4000][g_language[0] * 2 + 1];
            second = offset2 ? g_copy_setup_data.base4 + offset2 : 0;
        }
    } else if (id >= 3000) {
        int offset = g_copy_setup_data.ids2000[id - 3000].offset;
        if (offset) first = g_copy_setup_data.base2 + offset;
    } else if (id >= 2000) {
        int lang, offset;
        lang = g_language[0];
        if (lang) lang--;
        offset = g_copy_setup_data.ids2000[id - 2000 + lang].offset;
        if (offset) first = g_copy_setup_data.base2 + offset;
    } else if (id >= 1000) {
        int lang, offset;
        lang = g_language[0];
        if (lang) lang--;
        offset = g_copy_setup_data.ids1000[id - 1000 + lang];
        if (offset) first = g_copy_setup_data.base1 + offset;
    } else {
        if (((int (*)[83])g_stream_sound_table)[id][g_language[0] * 2]) {
            int offset2 = ((int (*)[83])g_stream_sound_table)[id][g_language[0] * 2 + 1];
            first = *(int *)(g_stream_sound_table - 4) + ((int (*)[83])g_stream_sound_table)[id][g_language[0] * 2];
            second = offset2 ? *(int *)(g_stream_sound_table - 4) + offset2 : 0;
        }
    }
    if (!first) return;
    STATE->channel[1].handle = 0xffffffff;
    STATE->channel[1].state = 1;
    STATE->channel[1].track = id;
    STATE->channel[1].flags = mode;
    STATE->channel[1].poll_interval = 10;
    STATE->channel[1].sample_rate = 48000;
    STATE->channel[1].volume = volume;
    STATE->channel[1].crossfade = 0;
    STATE->channel[1].object = object;
    STATE->channel[1].slot = snd_find_free_voice(object);
#ifdef OPENRAC_HOSTGEN
    /* OpenRAC: func_002E5A50 returns 52 when no slot is free; retail then writes past the
       52 rows. The port takes it as no slot. */
    if (STATE->channel[1].slot >= 52)
        STATE->channel[1].slot = -1;
#endif
    if (STATE->channel[1].slot >= 0) {
        slot = STATE->channel[1].slot;
        sound = (SoundAnchor *)(g_sound_state + slot * 0x70);
        sound->def = g_stream_sound_def;
        sound->defFlags = ((StreamSoundDef *)g_stream_sound_def)->flags;
        sound->sentinel = -1;
        sound->volume = volume;
        sound->object = object;
        sound->zero3 = 0;
        bits = 0;
        qzero_nc(g_sound_state + slot * 0x70 + 0xA0);
        if (object) {
            qcopy_nc(g_sound_state + slot * 0x70 + 0x90, (u8 *)object + 0x10);
            ((SoundAnchor *)(g_sound_state + slot * 0x70))->position[2] += 1.0f;
        } else {
            bits = 0x11;
            vec_clear_128(g_sound_state + slot * 0x70 + 0x90);
        }
        {
            SoundAnchor *anchor = (SoundAnchor *)(g_sound_state + slot * 0x70);
            anchor->handle = 0xffffffff;
            anchor->bits = bits;
            anchor->active = 8;
            anchor->zero2 = 0;
            anchor->zero = 0;
        }
    }
    func_00133350(first, second, 0, 0, STATE->channel[1].volume, 0, flags, 0, 0, 1,
                  request_store_result_and_advance, (unsigned int)&STATE->channel[1]);
}
