#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned int u32;

typedef unsigned char u8;

typedef unsigned short u16;

typedef float f32;

typedef int L04Quad __attribute__((mode(TI)));

/* the object the level's spawner allocates: a sixteen-byte block, a flag byte,
   a pointer to the second object and the caller's own pointer */
typedef struct {
    u8  pad00[0x10];
    L04Quad field10;
    u8  pad20[0x10];
    u8  field30;
    u8  pad31[0x68 - 0x31];
    u32 field68;
    u8  pad6C[0xB8 - 0x6C];
    u32 fieldB8;
} L04Object;

/* the second object: four sixteen-byte blocks and the words that follow them */
typedef struct {
    L04Quad field00;
    L04Quad field10;
    L04Quad field20;
    L04Quad field30;
    u32 field40;
    u32 field44;
    u32 field48;
    u32 field4C;
    u32 field50;
    u32 field54;
    u32 field58;
    f32 field5C;
} L04Target;

/* the level's own object: the blocks the spawner copies into */
typedef struct {
    u8  pad00[0x10];
    L04Quad field10;
    u8  pad20[0x11];
    u8  field31;
    u8  pad32[2];
    u16 field34;
    u8  pad36[0x98 - 0x36];
    u32 field98;
    u8  pad9C[0xC0 - 0x9C];
    u8  padC0[0x30];
    L04Quad fieldF0;
} L04Level;

extern void *func_0029EFD0(s32 size);
extern void func_002833F0(f32 *dst, f32 *src);
extern f32 func_00283CE0(s32 value);
extern void func_002A04B8(void *a, s32 *b, s32 *c, s32 *d);

/* Builds the level's spawn record: the caller's blocks are copied into the
   level's object and into the one the spawner allocated, and the colour and
   the scale are computed from what the engine's helpers return. */
void *func_L04_0030C4C0(void *levelObj, void *block0, void *block1, void *block2, void *block3, void *block5,
                       s32 divisor, void *userPtr, u32 userValue) {
    L04Object *newObject = (L04Object *)(u32)CreateMoby(0xE44);
    L04Level *lv = (L04Level *)levelObj;
    L04Target *targetBlock;
    u32 red, green, blue;
    u32 packed;

    if ((u32)newObject != 0) {
        lv->field10 = *(L04Quad *)block2;
        lv->fieldF0 = *(L04Quad *)block5;
        euler_rotation_basis((f32 *)((u8 *)lv + 0xC0), (f32 *)((u8 *)lv + 0xF0));
        newObject->fieldB8 = (u32)levelObj;
        newObject->field30 = 0xFF;
        newObject->field10 = lv->field10;
        targetBlock = (L04Target *)(u32)newObject->field68;
        targetBlock->field48 = (u32)levelObj;
        targetBlock->field50 = lv->field34;
        targetBlock->field00 = *(L04Quad *)block0;
        targetBlock->field20 = *(L04Quad *)block2;
        targetBlock->field10 = *(L04Quad *)block1;
        targetBlock->field30 = *(L04Quad *)block3;
        targetBlock->field40 = (u32)userPtr;
        targetBlock->field44 = userValue;
        targetBlock->field5C = 1.0f / IntToFloat(divisor);
        get_moby_color(levelObj, (s32 *)&red, (s32 *)&green, (s32 *)&blue);
        packed = (green << 8) + 0x80000000;
        targetBlock->field54 = (blue << 16) + packed + red;
        lv->field98 = 0;
        lv->field31 = 0;
        lv->field34 = (u16)(lv->field34 | 0x103);
    }
    return (u32)newObject;
}
