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

extern void *func_002B9030(s32 kind);
extern s32 func_00283CF0(f32 value);
extern f32 func_00283CE0(s32 value);
extern s32 func_002A77E0(s32 limit);

/* the level's pointer to the byte the record carries in its second flag byte */
extern u8 *D_L06_001FF50C;

/* func_PAL_L06_00380B10, the PAL copy of func_L06_0037E6B0: the same C, where the
   spin halfword a2 is scaled for 50 Hz once before its two uses. */
void func_PAL_L06_00380B10(void *a0, void *a1, u32 a2, f32 f3, f32 f4) {
    L06Record *p = (L06Record *)(u32)func_002B9030(0x53);
    L06RecordTail *q;
    L06Quad t;

    if ((u32)p != 0) {
        p->field10 = *(L06Quad *)a0;
        q = (L06RecordTail *)((u8 *)p + 0x20);
        p->field04 = 0x50502010;
        p->field09 = (u8)(func_00283CF0(2.0f) + 0x40);
        p->field03 = 0x48;
        p->field01 = 0;
        p->field02 = *D_L06_001FF50C;
        p->field0C = f3 * 105000.0f;
        p->field08 = (u8)func_002A77E0(0xFF);
        a2 = ((s32)a2 * 5 + 2) / 6;
        p->field0A = (u16)a2;
        t = *(L06Quad *)a1;
        p->field20 = t;
        q->field0C = func_00283CE0((s16)a2);
        q->field10 = 0.5f;
        q->field14 = f3;
        q->field18 = 0;
        q->field1C = f4;
        q->field1A = (s16)(func_002A77E0(6) - 3);
    }
}
