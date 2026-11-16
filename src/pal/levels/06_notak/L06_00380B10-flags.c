#include "common.h"

typedef int L06Quad __attribute__((mode(TI)));

/* The spawner record of func_L04_00362768: flag bytes, a colour word, a halfword, a
   float, two sixteen-byte blocks and the fields after them. */
typedef struct {
    u8  field00;
    u8  field01;
    u8  field02;
    u8  field03;
    u32 field04;
    u8  field08;
    u8  field09;
    u16 field0A;
    f32 field0C;
    L06Quad field10;
    L06Quad field20;
} L06Record;

/* the second half of the record, at +0x20 */
typedef struct {
    u8  pad00[0xC];
    f32 field0C;
    f32 field10;
    f32 field14;
    s16 field18;
    s16 field1A;
    f32 field1C;
} L06RecordTail;

extern void *part_alloc(s32 kind);
extern s32 FloatToInt(f32 value);
extern f32 IntToFloat(s32 value);
extern s32 math_random_int_below(s32 limit);

/* the level's pointer to the byte the record carries in its second flag byte */
extern u8 *g_particle_record_byte_ptr;

/* func_PAL_L06_00380B10, the PAL copy of func_L06_0037E6B0: the same C, where the
   spin halfword spin_rate is scaled for 50 Hz once before its two uses. */
void part_spawn_spinning_effect_record_pal(void *start, void *end, u32 spin_rate, f32 size, f32 speed) {
    L06Record *particle = (L06Record *)(u32)part_alloc(0x53);
    L06RecordTail *tail;
    L06Quad end_copy;

    if ((u32)particle != 0) {
        particle->field10 = *(L06Quad *)start;
        tail = (L06RecordTail *)((u8 *)particle + 0x20);
        particle->field04 = 0x50502010;
        particle->field09 = (u8)(FloatToInt(2.0f) + 0x40);
        particle->field03 = 0x48;
        particle->field01 = 0;
        particle->field02 = *g_particle_record_byte_ptr;
        particle->field0C = size * 105000.0f;
        particle->field08 = (u8)math_random_int_below(0xFF);
        spin_rate = ((s32)spin_rate * 5 + 2) / 6;
        particle->field0A = (u16)spin_rate;
        end_copy = *(L06Quad *)end;
        particle->field20 = end_copy;
        tail->field0C = IntToFloat((s16)spin_rate);
        tail->field10 = 0.5f;
        tail->field14 = size;
        tail->field18 = 0;
        tail->field1C = speed;
        tail->field1A = (s16)(math_random_int_below(6) - 3);
    }
}
