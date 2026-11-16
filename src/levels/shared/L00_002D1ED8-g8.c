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
extern u8 g_hero_state[];
#define HA ((HeroAnimation2168 *)D_00189E20)

/* Mirror flag: swaps the two facing animations. Incomplete with sda: retail reads it through an
   absolute macro load that uses its destination as the address temporary. */
extern u8 g_state_flag_c[] __attribute__((sda));
extern u8 g_hero_current_anim_buffer[];
extern u8 g_hero_next_anim_buffer[];
/* One 16-byte record per animation id returned by func_0029FA88. */
extern u8 g_hero_l00_animation_table[];
/* Frame counts per animation curve (two entries, the next symbol is 8 bytes on). */
extern s32 g_hero_anim_speed_table[2] __attribute__((sda));

extern s32 moby_alloc_object_slot(void *);
extern void func_002A2450(void *, s32);
extern void FlushCache(s32);
extern void update_moby_animation_state(void *);
extern s32 anim_copy_entry_data(char *, s32, s32, s32);
extern s32 FloatToInt(float);
extern void hero_clear_queued_anim(void);
extern void hero_sync_linked_object_anims(s32, s32, float);
extern void hero_clear_anim_flags(void);
extern void hero_start_linked_object_anim(s32, s32, float);

/* Starts hero animation sequence seq at frame: a positive speed plays it at rate 1/speed,
   otherwise -speed names a 1-based curve whose frame count is handed to the followers. */
void set_hero_animation(s32 seq, s32 frame, float speed)
{
    AnimObject *obj;
    s32 id;

    obj = HA->object;
    if (HA->flags & 2)
        obj->time = 0.0f;

    if (g_state_flag_c[0] != 0) {
        if (seq == 0x31)
            seq = 0x32;
        else if (seq == 0x32)
            seq = 0x31;
    }

    id = moby_alloc_object_slot(obj);
    if (id >= 0) {
        func_002A2450(obj, id | 0x300);
        FlushCache(0);
        qcopy(g_hero_l00_animation_table + id * 16, obj);
        if (obj->seq != 0xFF)
            obj->prevSeq = obj->seq;
        qcopy(g_hero_l00_animation_table + id * 16, (u8 *)obj + 0x80);
        obj->seq = 0xFF;
        obj->frame = id;
    }
    obj->nextFrame = frame;
    obj->nextSeq = seq;
    update_moby_animation_state(obj);

    if (obj->seq != 0xFF)
        obj->current = anim_copy_entry_data((char *)obj, obj->seq, obj->frame, (s32)g_hero_current_anim_buffer);
    obj->next = anim_copy_entry_data((char *)obj, obj->nextSeq, obj->nextFrame, (s32)g_hero_next_anim_buffer);

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

    hero_clear_queued_anim();

    obj->sound = obj->model->seqs[seq]->sound;
    HA->changing = 1;
    if (speed < 0.0f)
        speed = g_hero_anim_speed_table[HA->curve];

    if (HA->flag22b4 == 0)
        hero_sync_linked_object_anims(seq, frame, speed);
    if (HA->flag22b4 == 0 && HA->flag22ba == 0 && seq != HA->mode)
        HA->flag22b8 = 0;
    hero_clear_anim_flags();
    if (HA->slot != 0)
        hero_start_linked_object_anim(seq, frame, speed);
}
