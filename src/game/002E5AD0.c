#include "common.h"
extern u8 g_sound_state[];
/* Adapted from RAC1 sound.c's func_0022EB08 (GPL-3.0). */
extern int snd_find_free_voice(int);
extern void vec_clear_128(void *);
extern int math_random_int_below(int);
extern int snd_compute_voice_volume_from_distance(char *, char *);
typedef struct { unsigned int handle; unsigned char state, flags; char pad6[2]; char *definition; short source, linked, volume, history; int pitch; char *owner; int reserved; float position[4], offset[4]; float distance; } Voice5;
typedef struct { char header[112]; Voice5 voice; } Window5;
typedef struct { char pad[16]; int min, max; unsigned char active; char pad19; unsigned short source; } Definition5;
/* Takes a free sound voice and sets it up to play the given sound, returning its number or -1. */
int AllocateSoundVoice(Definition5 *definition, int flags, char *moby, int position, int volume)
{
    int inactive, index, result, pitch, max, min;
    Window5 *slot, *committed, *pitch_slot;
    inactive = definition->active == 0;
    if (!(flags & 4)) {
        if ((inactive ^ 1) != 0) goto rejected;
        goto allocate;
    }
    if (inactive) goto rejected;
allocate:
    index = snd_find_free_voice((int)moby);
    if (index >= 52) goto failed;
    slot = (Window5 *)(g_sound_state + index * 112);
    slot->voice.definition = (char *)definition;
    slot->voice.source = definition->source;
    slot->voice.distance = -1.0f;
    slot->voice.linked = -1;
    slot->voice.owner = 0;
    slot->voice.reserved = 0;
    slot->voice.volume = volume;
    qzero_nc(&((Window5 *)(g_sound_state + index*112))->voice.offset);
    if (position) goto set_position;
    if (!moby) goto clear_position;
set_position:
    if (!moby) goto explicit_position;
    qcopy(g_sound_state+index*112+0x90,moby+0x10);
    ((Window5 *)(g_sound_state+index*112))->voice.position[2] += 1.0f;
    goto calculate;
explicit_position:
    qcopy(g_sound_state+index*112+0x90,(void *)position);
    goto calculate;
clear_position:
    flags |= 0x11;
    vec_clear_128(g_sound_state+index*112+0x90);
calculate:
    if (flags & 0x10) goto direct;
    result = snd_compute_voice_volume_from_distance((char *)g_sound_state+index*112+0x70,(char *)g_sound_state+index*112+0x90);
    goto check;
direct:
    result = volume;
check:
    if (result < 32) {result=-1; goto done;}
    committed = (Window5 *)(g_sound_state+index*112);
    committed->voice.flags=flags;
    committed->voice.state=7;
    committed->voice.history=0;
    max=definition->max;
    min=definition->min;
    if (max != min) pitch=math_random_int_below(max-min)+definition->min;
    else pitch=max;
    pitch_slot=(Window5 *)(g_sound_state+index*112);
    pitch_slot->voice.pitch=pitch;
    pitch_slot->voice.handle=0xFFFFFFFF;
    goto return_index;
failed:
    index=-1;
return_index:
    result=index;
done:
    return result;
rejected:
    return -1;
}
