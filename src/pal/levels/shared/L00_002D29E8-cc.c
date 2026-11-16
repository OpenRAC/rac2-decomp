/* func_PAL_L00_002D29E8, the PAL copy of func_L00_002D24E8: the same C, where wrap HA- becomes speed (({e}) * 1.2f); wrap HA- becomes rate (({e}) * 1.2f). */
#include "common.h"

typedef struct {
    u8 pad0[0x10]; u8 count; u8 sound; u8 triggers; u8 pad1[9]; s32 frames[1];
} AnimEntry;
typedef struct { u8 pad[0x48]; AnimEntry *seqs[1]; } AnimModel;
typedef struct {
    u8 pad0[0x24]; AnimModel *model; u8 pad1[0x40-0x28];
    u8 frame, nextFrame, seq, nextSeq; float time;
    u8 pad2[0x58-0x48]; u8 *current; s32 next;
    u8 pad3[0x6C-0x60]; u8 sound, voice, triggers;
} AnimObject;
extern u8 g_hero_state[];
typedef struct {
    u8 pad0[0xC20];
    float speed;
    float rate;
    s32 flags;
    s32 changing;
    s32 curve;
    s32 step;
    float frame;
    float delta;
    s32 queued;
    s32 queuedFrame;
    s32 request;
    u8 pad1[0x2290 - 0xC4C];
    u8 *object;
} HeroAnimation24E8;

extern u8 g_sound_state[];
extern u8 g_hero_current_anim_buffer[];
extern u8 g_hero_next_anim_buffer[];
extern float g_hero_action_curve_table[][25];
extern void hero_clear_anim_flags(void);
extern void mem_copy_aligned(void *, void *, s32);
extern s32 anim_copy_entry_data(char *, s32, s32, s32);
extern void hero_clear_queued_anim(void);
extern void anim_sync_second_to_main(void);
extern s32 FloatToInt(float);
extern s32 PlayMobySound(s32, s32, char *);
extern void snd_stop_voice(s32);
extern void hero_update_linked_object_clock(void);
extern void hero_sync_linked_object_clock(void);
extern float moby_get_anim_value(char *);

/* Advances the hero animation, applies queued frames and sound triggers, and
   records the animation frame delta. */
void func_PAL_L00_002D29E8(void)
{
    u8 *base;
    AnimObject *obj;
    AnimEntry *entry;
    u8 *sound;
    u8 *buffer;
    u8 oldFrame;
    s32 same;
    s32 lower;
    s32 upper;
    s32 frame;
    float oldTime;
    float delta;
    float time;
    float prior;

    base = g_hero_state;
    obj = *(AnimObject **)(base + 0x2290);
    hero_clear_anim_flags();
    ((HeroAnimation24E8 *)g_hero_state)->flags &= ~3;
    oldFrame = obj->frame;
    oldTime = obj->time;
    same = obj->seq == obj->nextSeq;
    if (obj->seq == obj->nextSeq) {
        obj->time = oldTime + ((((HeroAnimation24E8 *)g_hero_state)->speed) * 1.2f) * ((HeroAnimation24E8 *)g_hero_state)->rate;
    } else if (((HeroAnimation24E8 *)g_hero_state)->curve >= 0) {
        frame = ((HeroAnimation24E8 *)g_hero_state)->step;
        obj->time = g_hero_action_curve_table[((HeroAnimation24E8 *)g_hero_state)->curve][frame];
        ((HeroAnimation24E8 *)g_hero_state)->step = frame + 1;
    } else {
        obj->time = oldTime + ((((HeroAnimation24E8 *)g_hero_state)->rate) * 1.2f);
    }
    if (obj->time > 0.99f && obj->time < 1.01f)
        obj->time = 1.0f;
    if (obj->time > -0.01f && obj->time < 0.01f)
        obj->time = 0.0f;
    delta = obj->time - oldTime;
    if (obj->time >= 1.0f) {
        buffer = g_hero_current_anim_buffer;
        do {
            if (obj->seq != obj->nextSeq) {
                obj->seq = obj->nextSeq;
                obj->triggers = obj->model->seqs[obj->seq]->triggers;
            }
            ((HeroAnimation24E8 *)g_hero_state)->curve = -1;
            ((HeroAnimation24E8 *)g_hero_state)->flags |= 1;
            obj->current = buffer;
            obj->frame = obj->nextFrame;
            mem_copy_aligned(buffer, buffer + 0x600, 0x600);
            obj->nextFrame++;
            if (((HeroAnimation24E8 *)g_hero_state)->request) {
                ((HeroAnimation24E8 *)g_hero_state)->request = 0;
                ((HeroAnimation24E8 *)g_hero_state)->rate = 1.0f / 0.0f; /* Retail uses a pooled positive infinity. */
                /* Convert the cleared request, retaining the shared floating zero. */
                obj->time = ((HeroAnimation24E8 *)g_hero_state)->request;
                obj->nextFrame = *(u8 *)(g_hero_state + 0xC44);
                obj->next = anim_copy_entry_data((char *)obj, obj->nextSeq, obj->nextFrame, (s32)(buffer + 0x600));
                hero_clear_queued_anim();
                anim_sync_second_to_main();
            } else if (((HeroAnimation24E8 *)g_hero_state)->queued != -1 && ((HeroAnimation24E8 *)g_hero_state)->queuedFrame < obj->nextFrame) {
                ((HeroAnimation24E8 *)g_hero_state)->rate = 0.33333334f;
                obj->time = 0.0f;
                obj->nextFrame = *(u8 *)(g_hero_state + 0xC40);
                obj->next = anim_copy_entry_data((char *)obj, obj->nextSeq, obj->nextFrame, (s32)(buffer + 0x600));
                anim_sync_second_to_main();
            } else {
                entry = obj->model->seqs[obj->nextSeq];
                if ((u32)obj->nextFrame >= (u32)entry->count) {
                    obj->nextFrame = 0;
                    ((HeroAnimation24E8 *)g_hero_state)->flags |= 2;
                }
                obj->next = anim_copy_entry_data((char *)obj, obj->nextSeq, obj->nextFrame, (s32)g_hero_next_anim_buffer);
                obj->time -= 1.0f;
                obj->time /= ((HeroAnimation24E8 *)g_hero_state)->rate;
                ((HeroAnimation24E8 *)g_hero_state)->rate = *(float *)obj->current;
                obj->time *= ((HeroAnimation24E8 *)g_hero_state)->rate;
            }
        } while (obj->time >= 1.0f);
    }
    if (same && obj->triggers) {
        AnimEntry *sequence;
        s32 frame;
        s32 event;
        s32 i;
        s32 *events;
        upper = obj->frame * 16 + FloatToInt(obj->time * 16.0f);
        lower = oldFrame * 16 + FloatToInt(oldTime * 16.0f);
        sequence = obj->model->seqs[obj->seq];
        events = &sequence->frames[sequence->count];
        for (i = 0; i < sequence->triggers; i++, events++) {
            event = *events;
            frame = event >> 16;
            if (lower < frame && upper >= frame) {
                PlayMobySound(event & 0xFFFF, 0, (char *)obj);
                break;
            }
        }
    }
    if (obj->voice != 255) {
        sound = g_sound_state + obj->voice * 0x70;
        if (*(void **)(sound + 0x88) != obj)
            obj->voice = 255;
        else if (*(s16 *)(sound + 0x7E) != obj->sound) {
            snd_stop_voice(obj->voice);
            obj->voice = 255;
        }
    } else if (obj->sound != 255) {
        obj->voice = PlayMobySound(obj->sound, 4, (char *)obj);
    }
    hero_update_linked_object_clock();
    hero_sync_linked_object_clock();
    prior = ((HeroAnimation24E8 *)g_hero_state)->frame;
    time = moby_get_anim_value((char *)obj);
    ((HeroAnimation24E8 *)g_hero_state)->frame = time;
    if (time >= prior) ((HeroAnimation24E8 *)g_hero_state)->delta = time - prior;
    else ((HeroAnimation24E8 *)g_hero_state)->delta = delta;
    ((HeroAnimation24E8 *)g_hero_state)->changing = obj->seq != obj->nextSeq;
}
