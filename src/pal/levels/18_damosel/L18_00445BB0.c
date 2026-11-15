#include "include_asm.h"



#include "common.h"
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern s32 snd_is_voice_playing_for_owner(void *, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern float func_PAL_002AA108(void *, void *);
extern void moby_set_state(void *, int, int);
extern int FloatToInt(float);
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern void moby_mark_spawned(void *);
extern void cam_mode_noop(void *);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern void func_PAL_002A7650(void *, int, int);
extern char g_sound_state[], g_hero_position[];
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern char g_sound_state[];
extern int snd_is_voice_playing_for_owner(void *,int),PlayMobySound(int,int,void *);
extern void snd_stop_voice(int);
extern s32 snd_is_voice_playing_for_owner(void *, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern float func_PAL_002AA108(void *, void *);
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } DamoselSoundAnchor;
extern char g_sound_state[];
extern char g_hero_position[];
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void vec_transform_and_set_height(void *, void *, void *, void *, float);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern void func_PAL_002A7650(void *, int, int), moby_mark_spawned(void *);
extern void cam_mode_noop(void *);

void func_PAL_L18_00446940(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    char *hit;
    char *owner;
    int excluded;
    float zero, damage;
    float direction[4];
    switch (object[0x20]) {
    case 0:
        *(int *)(state + 0x100) = -1;
        *(unsigned short *)(object + 0x34) |= 0x1000;
        state[0x48] = FloatToInt(15.0f);
        state[0x4a] = FloatToInt(6.0f);
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (flag_set_first_pending(object)) {
            if (*(int *)(state + 0x100) != -1 && ((DamoselSoundAnchor *)(g_sound_state + *(int *)(state + 0x100) * 112))->owner == object && ((DamoselSoundAnchor *)(g_sound_state + *(int *)(state + 0x100) * 112))->active)
                snd_stop_voice(*(int *)(state + 0x100));
            *(int *)(state + 0x100) = -1;
        }
        hit = part_find_owned_effect_slot(object, 0x10000, 0);
        if (!hit) goto intact;
        owner = *(char **)(hit + 0x20);
        excluded = 0;
        if (owner && (*(short *)(owner + 0xaa) == 0xb69 || *(short *)(owner + 0xaa) == 0xf9e)) excluded = 1;
        if (excluded) break;
        zero = 0.0f;
        damage = func_PAL_002AA108(object, hit);
        object[0xa8] = 255;
        *(float *)(state + 0x20) -= damage;
        if (*(float *)(state + 0x20) <= zero) {
            func_PAL_002AC718(object, object + 0x10, 0, zero, zero, 10, 3, 9,
                         4.0f, 2.0f, 9.0f, zero, -1, 15.0f, 1, 1, -1, 0, 0x810001);
            PlayMobySound(0, 0, object);
            FastVecSub(direction, (float *)(object + 0x10), (float *)g_hero_position);
            vec_transform_and_set_height(object, direction, direction, 0, zero);
            vec_scale_to_length((char *)direction, (char *)direction, 0.120000005f);
            func_PAL_002B15D8(object, 0x1fff, direction, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            func_PAL_002A7650(object, 0, 3);
            moby_mark_spawned(object);
        }
        break;
intact:
        cam_mode_noop(object);
        break;
    }
}


