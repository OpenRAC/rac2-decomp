#include "include_asm.h"
#include "common.h"

/* func_PAL_L03_002FFA00, the PAL copy of func_L03_002FDE30: the USA v2.00 C (a level test
   of 0x33 around the 0xFA0 objects' update, the object list read through a local base),
   where the 0xFA0 update's float goes from 0.061086535f to 0.07330384f (x 6/5) and the
   mode 7 timer test from 0x424 to 0x373 (x 5/6). */

typedef unsigned int Quad __attribute__((mode(TI)));

/* The level's runtime block: its mode word and timer, and a counted list of objects. */
typedef struct {
    u8 pad00[0x30];
    u32 mode;
    s32 timer;
    u8 pad38[0xC];
    s16 count;
    u8 pad46[0x146];
    u8 *objects[0];
} EndakoState;

extern EndakoState D_L03_001BD680;
extern s32 D_001A79F0 __attribute__((sda));
extern f32 D_L03_001A9420 SDATA(D_L03_001A9420);
extern s32 D_L03_001A9424 SDATA(D_L03_001A9424);
/* Four rows of three quadwords, filled from twelve joints of one object. */
extern Quad D_L03_001C64A0[][3];
extern void func_L00_002FC980(void);
extern void func_PAL_002E7270(void *);
extern void func_L00_00326048(void *, void *, u32, u32, f32);
extern void func_PAL_L03_00328558(void *);
extern void func_0029FCC0(void *, s32, void *);

void func_PAL_L03_002FFA00(void)
{
    EndakoState *state;
    u8 *object;
    s32 i;
    Quad a, b;

    func_L00_002FC980();
    for (i = 0; i < D_L03_001BD680.count; i++) {
        u8 *base = (u8 *)&D_L03_001BD680;
        object = *(u8 **)(base + i * 4 + 0x18C);
        if (object != 0 && *(s16 *)(object + 0xAA) == 0xE29)
            *(u16 *)(object + 0x34) |= 0x800;
        if (*(s16 *)(object + 0xAA) == 0xD54)
            func_PAL_002E7270(object);
        if (object != 0 && *(s16 *)(object + 0xAA) == 0xFA0 && D_001A79F0 != 0x33) {
            u8 *vars = *(u8 **)(object + 0x68);
            if (vars != 0)
                func_L00_00326048(object, vars + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
        }
    }
    if (D_001A79F0 != 3)
        return;
    state = &D_L03_001BD680;
    if (state->mode < 3) {
        u8 *p = state->objects[1];
        *(f32 *)(p + 0x2C) = *(f32 *)(*(u8 **)(p + 0x24) + 0x24) * D_L03_001A9420;
    }
    if (state->mode == 6)
        func_PAL_L03_00328558(state->objects[1]);
    if (state->mode == 8)
        func_PAL_L03_00328558(state->objects[3]);
    if (state->mode == 7 && state->timer == 0x373) {
        u8 *target;
        s32 row, col, k;

        D_L03_001A9424 = state->timer;
        target = state->objects[2];
        for (row = 0; row < 4; row++)
            for (col = 0; col < 3; col++)
                func_0029FCC0(target, row * 3 + col, &D_L03_001C64A0[row][col]);
        for (k = 0; k < 4; k++) {
            Quad (*rows)[3] = D_L03_001C64A0;
            qcopy(&a, &rows[k][0]);
            qcopy(&b, &rows[k][1]);
            qcopy(&a, &rows[k][0]);
            qcopy(&b, &rows[k][2]);
        }
    }
}
