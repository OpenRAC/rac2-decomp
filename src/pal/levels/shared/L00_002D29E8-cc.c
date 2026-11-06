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
extern u8 D_00189E20[];
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

extern u8 D_00188660[];
extern u8 D_L00_001B4400[];
extern u8 D_L00_001B4A00[];
extern float D_L00_0025DB20[][25];
extern void func_L00_002D1F60(void);
extern void func_00282AB0(void *, void *, s32);
extern s32 func_L00_002A4DB0(char *, s32, s32, s32);
extern void func_L00_002D24B8(void);
extern void func_L00_002D20D0(void);
extern s32 func_00283CF0(float);
extern s32 func_002E5CF8(s32, s32, char *);
extern void func_002E59F8(s32);
extern void func_L00_002D1ED8(void);
extern void func_L00_002D2070(void);
extern float func_0029F530(char *);

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

    base = D_00189E20;
    obj = *(AnimObject **)(base + 0x2290);
    func_L00_002D1F60();
    ((HeroAnimation24E8 *)D_00189E20)->flags &= ~3;
    oldFrame = obj->frame;
    oldTime = obj->time;
    same = obj->seq == obj->nextSeq;
    if (obj->seq == obj->nextSeq) {
        obj->time = oldTime + ((((HeroAnimation24E8 *)D_00189E20)->speed) * 1.2f) * ((HeroAnimation24E8 *)D_00189E20)->rate;
    } else if (((HeroAnimation24E8 *)D_00189E20)->curve >= 0) {
        frame = ((HeroAnimation24E8 *)D_00189E20)->step;
        obj->time = D_L00_0025DB20[((HeroAnimation24E8 *)D_00189E20)->curve][frame];
        ((HeroAnimation24E8 *)D_00189E20)->step = frame + 1;
    } else {
        obj->time = oldTime + ((((HeroAnimation24E8 *)D_00189E20)->rate) * 1.2f);
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
            ((HeroAnimation24E8 *)D_00189E20)->curve = -1;
            ((HeroAnimation24E8 *)D_00189E20)->flags |= 1;
            obj->current = buffer;
            obj->frame = obj->nextFrame;
            func_00282AB0(buffer, buffer + 0x600, 0x600);
            obj->nextFrame++;
            if (((HeroAnimation24E8 *)D_00189E20)->request) {
                ((HeroAnimation24E8 *)D_00189E20)->request = 0;
                ((HeroAnimation24E8 *)D_00189E20)->rate = 1.0f / 0.0f; /* Retail uses a pooled positive infinity. */
                /* Convert the cleared request, retaining the shared floating zero. */
                obj->time = ((HeroAnimation24E8 *)D_00189E20)->request;
                obj->nextFrame = *(u8 *)(D_00189E20 + 0xC44);
                obj->next = func_L00_002A4DB0((char *)obj, obj->nextSeq, obj->nextFrame, (s32)(buffer + 0x600));
                func_L00_002D24B8();
                func_L00_002D20D0();
            } else if (((HeroAnimation24E8 *)D_00189E20)->queued != -1 && ((HeroAnimation24E8 *)D_00189E20)->queuedFrame < obj->nextFrame) {
                ((HeroAnimation24E8 *)D_00189E20)->rate = 0.33333334f;
                obj->time = 0.0f;
                obj->nextFrame = *(u8 *)(D_00189E20 + 0xC40);
                obj->next = func_L00_002A4DB0((char *)obj, obj->nextSeq, obj->nextFrame, (s32)(buffer + 0x600));
                func_L00_002D20D0();
            } else {
                entry = obj->model->seqs[obj->nextSeq];
                if ((u32)obj->nextFrame >= (u32)entry->count) {
                    obj->nextFrame = 0;
                    ((HeroAnimation24E8 *)D_00189E20)->flags |= 2;
                }
                obj->next = func_L00_002A4DB0((char *)obj, obj->nextSeq, obj->nextFrame, (s32)D_L00_001B4A00);
                obj->time -= 1.0f;
                obj->time /= ((HeroAnimation24E8 *)D_00189E20)->rate;
                ((HeroAnimation24E8 *)D_00189E20)->rate = *(float *)obj->current;
                obj->time *= ((HeroAnimation24E8 *)D_00189E20)->rate;
            }
        } while (obj->time >= 1.0f);
    }
    if (same && obj->triggers) {
        AnimEntry *sequence;
        s32 frame;
        s32 event;
        s32 i;
        s32 *events;
        upper = obj->frame * 16 + func_00283CF0(obj->time * 16.0f);
        lower = oldFrame * 16 + func_00283CF0(oldTime * 16.0f);
        sequence = obj->model->seqs[obj->seq];
        events = &sequence->frames[sequence->count];
        for (i = 0; i < sequence->triggers; i++, events++) {
            event = *events;
            frame = event >> 16;
            if (lower < frame && upper >= frame) {
                func_002E5CF8(event & 0xFFFF, 0, (char *)obj);
                break;
            }
        }
    }
    if (obj->voice != 255) {
        sound = D_00188660 + obj->voice * 0x70;
        if (*(void **)(sound + 0x88) != obj)
            obj->voice = 255;
        else if (*(s16 *)(sound + 0x7E) != obj->sound) {
            func_002E59F8(obj->voice);
            obj->voice = 255;
        }
    } else if (obj->sound != 255) {
        obj->voice = func_002E5CF8(obj->sound, 4, (char *)obj);
    }
    func_L00_002D1ED8();
    func_L00_002D2070();
    prior = ((HeroAnimation24E8 *)D_00189E20)->frame;
    time = func_0029F530((char *)obj);
    ((HeroAnimation24E8 *)D_00189E20)->frame = time;
    if (time >= prior) ((HeroAnimation24E8 *)D_00189E20)->delta = time - prior;
    else ((HeroAnimation24E8 *)D_00189E20)->delta = delta;
    ((HeroAnimation24E8 *)D_00189E20)->changing = obj->seq != obj->nextSeq;
}
