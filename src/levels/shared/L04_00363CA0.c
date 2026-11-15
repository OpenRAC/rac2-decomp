#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned int u32;

typedef unsigned char u8;

typedef unsigned short u16;

typedef float f32;

/* the object the level's spawner builds: a 0x67-byte record with a few flag bytes,
   a halfword, a float and a sixteen-byte block copied from the caller */
typedef int L04Quad __attribute__((mode(TI)));

typedef struct {
    u8 pad00;
    u8 field01;
    u8 field02;
    u8 field03;
    u32 field04;
    u8 field08;
    u8 field09;
    u16 field0A;
    f32 field0C;
    L04Quad field10;
} L04Spawned;

extern void *func_002B9030(s32 kind);

extern s32 func_00283CF0(f32 value);

extern s32 func_002A77E0(s32 limit);

/* the level's pointer to the byte the record carries in its second flag byte */
extern u32 ref_L04_00363CA0_00;

/* Creates a small effect record, fills it with random values and the caller's data, and returns it. */
void *func_L04_00363CA0(void *quadSrc, void *owner, f32 scale) {
    L04Spawned *rec = (L04Spawned *)(u32)AllocParticle(0x67);

    if ((u32)rec != 0) {
        rec->field04 = (u32)owner;
        rec->field09 = (u8)(FloatToInt(2.0f) - 0x10);
        rec->field03 = 0x48;
        rec->field01 = 0;
        rec->field02 = *(u8 *)ref_L04_00363CA0_00;
        rec->field0C = scale;
        rec->field08 = (u8)RandomIntBelow(0xFF);
        rec->field0A = 2;
        rec->field10 = *(L04Quad *)quadSrc;
    }
    return (u32)rec;
}
