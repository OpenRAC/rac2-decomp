#include "include_asm.h"
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

/* The func_L04_00362768 spawner with a colour word, a second size and a random
   spin halfword. */
/* Spawns a spinning effect record at a position, with a colour, a size and a random spin speed. */
void part_spawn_spinning_effect_record(void *position, void *direction, u32 angle, f32 size, f32 second_size) {
    L06Record *record = (L06Record *)(u32)part_alloc(0x53);
    L06RecordTail *tail;
    L06Quad temp;

    if ((u32)record != 0) {
        record->field10 = *(L06Quad *)position;
        tail = (L06RecordTail *)((u8 *)record + 0x20);
        record->field04 = 0x50502010;
        record->field09 = (u8)(FloatToInt(2.0f) + 0x40);
        record->field03 = 0x48;
        record->field01 = 0;
        record->field02 = *g_particle_record_byte_ptr;
        record->field0C = size * 105000.0f;
        record->field08 = (u8)math_random_int_below(0xFF);
        record->field0A = (u16)angle;
        temp = *(L06Quad *)direction;
        record->field20 = temp;
        tail->field0C = IntToFloat((s16)angle);
        tail->field10 = 0.5f;
        tail->field14 = size;
        tail->field18 = 0;
        tail->field1C = second_size;
        tail->field1A = (s16)(math_random_int_below(6) - 3);
    }
}
