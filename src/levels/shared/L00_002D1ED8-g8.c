/* func_L00_002D2168 (set_hero_animation) in its own unit: the curve frame table is read through
   $gp, so the unit needs -G8 (given by its name). */
#include "common.h"

typedef struct {
    u8 pad0[0x10]; u8 count; u8 sound; u8 triggers;
} AnimEntry;
typedef struct { u8 pad[0x48]; AnimEntry *seqs[1]; } AnimModel;
typedef struct {
    u8 pad0[0x24]; AnimModel *model; u8 pad1[0x40-0x28];
    u8 frame, nextFrame, seq, nextSeq; float time;
    u8 pad2[0x58-0x48]; s32 current; s32 next;
    u8 pad3[0x6C-0x60]; u8 sound; u8 voice; u8 triggers;
    u8 pad4[0xA9-0x6F]; u8 prevSeq;
} AnimObject;

typedef struct {
    u8 pad0[0xC20];
    float speed;
    float rate;
    s32 flags;
    s32 changing;
    s32 curve;
    s32 step;
    u8 pad1[0x2290 - 0xC38];
    AnimObject *object;
    u8 pad2[0x22B4 - 0x2294];
    u8 flag22b4;
    u8 pad3[3];
    u8 flag22b8;
    u8 pad4[1];
    u8 flag22ba;
    u8 pad5[0x2494 - 0x22BB];
    s32 slot;
    u8 pad6[0x24B0 - 0x2498];
    s32 mode;
} HeroAnimation2168;

/* The resident hero state; the fields are those AdvanceHeroAnimation (func_L00_002D24E8) uses. */
extern u8 D_00189E20[];
#define HA ((HeroAnimation2168 *)D_00189E20)

/* Mirror flag: swaps the two facing animations. Incomplete with sda: retail reads it through an
   absolute macro load that uses its destination as the address temporary. */
extern u8 D_001A7A45[] __attribute__((sda));
extern u8 D_L00_001B4400[];
extern u8 D_L00_001B4A00[];
/* One 16-byte record per animation id returned by func_0029FA88. */
extern u8 D_L00_001D98C0[];
/* Frame counts per animation curve (two entries, the next symbol is 8 bytes on). */
extern s32 D_L00_001A7DF8[2] __attribute__((sda));

extern s32 func_0029FA88(void *);
extern s32 func_002A2450(void *, s32);
extern void func_0011AEA0(s32);
extern void func_0029F390(void *);
extern s32 func_L00_002A4DB0(char *, s32, s32, s32);
extern s32 func_00283CF0(float);
extern void func_L00_002D24B8(void);
extern void func_L00_002D1C40(s32, s32, float);
extern void func_L00_002D1F60(void);
extern void func_L00_002D1FD8(s32, s32, float);

/* Starts hero animation sequence seq at frame: a positive speed plays it at rate 1/speed,
   otherwise -speed names a 1-based curve whose frame count is handed to the followers. */
void func_L00_002D2168(s32 seq, s32 frame, float speed)
{
    AnimObject *obj;
    s32 id;

    obj = HA->object;
    if (HA->flags & 2)
        obj->time = 0.0f;

    if (D_001A7A45[0] != 0) {
        if (seq == 0x31)
            seq = 0x32;
        else if (seq == 0x32)
            seq = 0x31;
    }

    id = AllocObjectSlot(obj);
    if (id >= 0) {
        func_002A2450(obj, id | 0x300);
        FlushCache(0);
        qcopy(D_L00_001D98C0 + id * 16, obj);
        if (obj->seq != 0xFF)
            obj->prevSeq = obj->seq;
        qcopy(D_L00_001D98C0 + id * 16, (u8 *)obj + 0x80);
        obj->seq = 0xFF;
        obj->frame = id;
    }
    obj->nextFrame = frame;
    obj->nextSeq = seq;
    update_moby_animation_state(obj);

    if (obj->seq != 0xFF)
        obj->current = CopyAnimationEntryData((char *)obj, obj->seq, obj->frame, (s32)D_L00_001B4400);
    obj->next = CopyAnimationEntryData((char *)obj, obj->nextSeq, obj->nextFrame, (s32)D_L00_001B4A00);

    HA->speed = 1.0f;
    if (speed > 0.0f) {
        HA->rate = 1.0f / speed;
        obj->time = 0.0f;
        HA->curve = -1;
    } else {
        HA->rate = 1.0f;
        HA->curve = FloatToInt(-speed) - 1;
        HA->step = 0;
        obj->time = 0.0f;
    }

    ClearHeroQueuedAnimation();

    obj->sound = obj->model->seqs[seq]->sound;
    HA->changing = 1;
    if (speed < 0.0f)
        speed = D_L00_001A7DF8[HA->curve];

    if (HA->flag22b4 == 0)
        SyncLinkedObjectAnimations(seq, frame, speed);
    if (HA->flag22b4 == 0 && HA->flag22ba == 0 && seq != HA->mode)
        HA->flag22b8 = 0;
    ClearHeroAnimFlags();
    if (HA->slot != 0)
        StartLinkedObjectAnimation(seq, frame, speed);
}
