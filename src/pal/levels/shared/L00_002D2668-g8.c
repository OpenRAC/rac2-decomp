#include "include_asm.h"

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
extern u8 D_00189E20[];
#define HA ((HeroAnimation2168 *)D_00189E20)
extern u8 D_001A7A45[] __attribute__((sda));
extern u8 D_L00_001B4400[];
extern u8 D_L00_001B4A00[];
extern u8 D_L00_001D98C0[];
extern s32 D_L00_001A7DF8[2] __attribute__((sda));
extern s32 func_0029FA88(void *);
extern s32 func_PAL_002A2E30(void *, s32);
extern void func_0011AEA0(s32);
extern void func_0029F390(void *);
extern s32 func_L00_002A4DB0(char *, s32, s32, s32);
extern s32 func_00283CF0(float);
extern void func_L00_002D24B8(void);
extern void func_PAL_L00_002D2140(s32, s32, float);
extern void func_L00_002D1F60(void);
extern void func_PAL_L00_002D24D8(s32, s32, float);

/* Starts hero animation sequence seq at frame: a positive speed plays it at rate 1/speed,
   otherwise -speed names a 1-based curve whose frame count is handed to the followers. */
void func_PAL_L00_002D2668(s32 seq, s32 frame, float speed)
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

    id = func_0029FA88(obj);
    if (id >= 0) {
        func_PAL_002A2E30(obj, id | 0x300);
        func_0011AEA0(0);
        qcopy(D_L00_001D98C0 + id * 16, obj);
        if (obj->seq != 0xFF)
            obj->prevSeq = obj->seq;
        qcopy(D_L00_001D98C0 + id * 16, (u8 *)obj + 0x80);
        obj->seq = 0xFF;
        obj->frame = id;
    }
    obj->nextFrame = frame;
    obj->nextSeq = seq;
    func_0029F390(obj);

    if (obj->seq != 0xFF)
        obj->current = func_L00_002A4DB0((char *)obj, obj->seq, obj->frame, (s32)D_L00_001B4400);
    obj->next = func_L00_002A4DB0((char *)obj, obj->nextSeq, obj->nextFrame, (s32)D_L00_001B4A00);

    HA->speed = 1.0f;
    if (speed > 0.0f) {
        HA->rate = 1.0f / speed;
        obj->time = 0.0f;
        HA->curve = -1;
    } else {
        HA->rate = 1.0f;
        HA->curve = func_00283CF0(-speed) - 1;
        HA->step = 0;
        obj->time = 0.0f;
    }

    func_L00_002D24B8();

    obj->sound = obj->model->seqs[seq]->sound;
    HA->changing = 1;
    if (speed < 0.0f)
        speed = D_L00_001A7DF8[HA->curve];

    if (HA->flag22b4 == 0)
        func_PAL_L00_002D2140(seq, frame, speed);
    if (HA->flag22b4 == 0 && HA->flag22ba == 0 && seq != HA->mode)
        HA->flag22b8 = 0;
    func_L00_002D1F60();
    if (HA->slot != 0)
        func_PAL_L00_002D24D8(seq, frame, speed);
}
