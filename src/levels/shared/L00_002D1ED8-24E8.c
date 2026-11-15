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
#define HA ((HeroAnimation24E8 *)D_00189E20)

extern u8 g_sound_state[];
extern u8 D_L00_001B4400[];
extern u8 D_L00_001B4A00[];
extern float D_L00_0025DB20[][25];
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
void AdvanceHeroAnimation(void)
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
    HA->flags &= ~3;
    oldFrame = obj->frame;
    oldTime = obj->time;
    same = obj->seq == obj->nextSeq;
    if (obj->seq == obj->nextSeq) {
        obj->time = oldTime + HA->speed * HA->rate;
    } else if (HA->curve >= 0) {
        frame = HA->step;
        obj->time = D_L00_0025DB20[HA->curve][frame];
        HA->step = frame + 1;
    } else {
        obj->time = oldTime + HA->rate;
    }
    if (obj->time > 0.99f && obj->time < 1.01f)
        obj->time = 1.0f;
    if (obj->time > -0.01f && obj->time < 0.01f)
        obj->time = 0.0f;
    delta = obj->time - oldTime;
    if (obj->time >= 1.0f) {
        buffer = D_L00_001B4400;
        do {
            if (obj->seq != obj->nextSeq) {
                obj->seq = obj->nextSeq;
                obj->triggers = obj->model->seqs[obj->seq]->triggers;
            }
            HA->curve = -1;
            HA->flags |= 1;
            obj->current = buffer;
            obj->frame = obj->nextFrame;
            mem_copy_aligned(buffer, buffer + 0x600, 0x600);
            obj->nextFrame++;
            if (HA->request) {
                HA->request = 0;
                HA->rate = 1.0f / 0.0f; /* Retail uses a pooled positive infinity. */
                /* Convert the cleared request, retaining the shared floating zero. */
                obj->time = HA->request;
                obj->nextFrame = *(u8 *)(g_hero_state + 0xC44);
                obj->next = anim_copy_entry_data((char *)obj, obj->nextSeq, obj->nextFrame, (s32)(buffer + 0x600));
                hero_clear_queued_anim();
                anim_sync_second_to_main();
            } else if (HA->queued != -1 && HA->queuedFrame < obj->nextFrame) {
                HA->rate = 0.33333334f;
                obj->time = 0.0f;
                obj->nextFrame = *(u8 *)(g_hero_state + 0xC40);
                obj->next = anim_copy_entry_data((char *)obj, obj->nextSeq, obj->nextFrame, (s32)(buffer + 0x600));
                anim_sync_second_to_main();
            } else {
                entry = obj->model->seqs[obj->nextSeq];
                if ((u32)obj->nextFrame >= (u32)entry->count) {
                    obj->nextFrame = 0;
                    HA->flags |= 2;
                }
                obj->next = anim_copy_entry_data((char *)obj, obj->nextSeq, obj->nextFrame, (s32)D_L00_001B4A00);
                obj->time -= 1.0f;
                obj->time /= HA->rate;
                HA->rate = *(float *)obj->current;
                obj->time *= HA->rate;
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
    prior = HA->frame;
    time = moby_get_anim_value((char *)obj);
    HA->frame = time;
    if (time >= prior) HA->delta = time - prior;
    else HA->delta = delta;
    HA->changing = obj->seq != obj->nextSeq;
}
