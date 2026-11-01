#include "include_asm.h"

/* The 23-word descriptor func_00337210 takes, filled from the object: the defaults
   first, then the object's own fields. The same shape as func_00344F98, in the -G8
   unit where the small data comes out $gp-relative. */
extern void func_00337210(int *);

extern char D_001AA898[];

extern int D_001AE4A0 __attribute__((sda));

extern int D_001AE4A4 __attribute__((sda));

extern int D_001AE4A8 __attribute__((sda));

extern int D_001AE4B0 __attribute__((sda));

extern int D_001AE4B8 __attribute__((sda));

extern int D_001AE4C0 __attribute__((sda));

extern int D_001AE4C8 __attribute__((sda));

void func_003464D0(char *o)
{
    int f[23];

    f[20] = 0;
    f[14] = 1;
    f[11] = 0;
    f[13] = 0;
    f[21] = 1;
    f[19] = *(int *)(o + 0x494);
    f[21] = ((*(int *)(o + 0x498) ^ 1) == 0);
    f[3] = *(int *)(o + 0x48C);
    f[4] = *(int *)(o + 0x490);
    f[16] = (int)(o + 0x448);
    f[9] = (int)&D_001AE4C8;
    f[1] = D_001AE4A0;
    f[2] = D_001AE4A4;
    f[0] = (int)D_001AA898;
    f[17] = (int)(o + 0x210);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x258);
    f[18] = *(int *)(o + 0x400);
    f[8] = (int)&D_001AE4C0;
    f[7] = (int)&D_001AE4B8;
    f[6] = (int)&D_001AE4B0;
    f[5] = (int)&D_001AE4A8;
    f[22] = 1;
    func_00337210(f);
}

extern char D_001AA7D8[];

extern int D_001AE470 __attribute__((sda));

extern int D_001AE474 __attribute__((sda));

extern int D_001AE478 __attribute__((sda));

extern int D_001AE480 __attribute__((sda));

extern int D_001AE488 __attribute__((sda));

extern int D_001AE490 __attribute__((sda));

extern int D_001AE498 __attribute__((sda));

void func_003463C8(char *o)
{
    int f[23];

    f[20] = 0;
    f[11] = 0;
    f[13] = 0;
    f[21] = 1;
    f[19] = *(int *)(o + 0x494);
    f[21] = ((*(int *)(o + 0x498) ^ 3) == 0);
    f[3] = *(int *)(o + 0x48C);
    f[4] = *(int *)(o + 0x490);
    f[16] = (int)(o + 0x448);
    f[9] = (int)&D_001AE498;
    f[14] = 3;
    f[1] = D_001AE470;
    f[2] = D_001AE474;
    f[0] = (int)D_001AA7D8;
    f[17] = (int)(o + 0x210);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x258);
    f[18] = *(int *)(o + 0x400);
    f[8] = (int)&D_001AE490;
    f[7] = (int)&D_001AE488;
    f[6] = (int)&D_001AE480;
    f[5] = (int)&D_001AE478;
    f[22] = 1;
    func_00337210(f);
}

/* Pad input on the 3 x 2 selection grid: up/down/left/right move the cursor (sound 3) and
   cross confirms an available entry (sound 4, else 5); the entry under the cursor is kept
   at +0x494 and, when available, its table value in D_001ADB10. */
typedef struct { short v[5]; } SelectionEntry;
typedef struct { char pad[0x48C]; int column, row, selected, state; } SelectionOwner;
typedef struct { char pad[6]; short material; char tail[0xD8]; } SelectionMaterial;

extern int func_002E5E58(int, int, void *);
extern unsigned char D_001A7AF8[] __attribute__((section(".sdata")));
extern unsigned char D_00139568[];
extern char D_00239BA0[];
extern int D_001F2880[];
extern int D_001ADB10 __attribute__((sda));
extern SelectionEntry D_00259CE0[];

void func_003458F8(SelectionOwner *owner, int buttons)
{
    if (buttons & 0x1000) {
        int row;
        func_002E5E58(3, 0, 0);
        row = owner->row - 1;
        owner->row = row;
        if (row < 0) {
            owner->row = 0;
            owner->state = 1;
        }
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        if (owner->row == 0) {
            if (owner->column == 0) {
                owner->column = 1;
                owner->row = 1;
            } else
                owner->row = 1;
        } else if (owner->row == 1) {
            owner->state = 3;
            owner->row = 0;
            owner->column--;
        }
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        --owner->column;
        if (owner->row == 0)
            owner->column = owner->column < 0 ? 2 : owner->column;
        else
            owner->column = owner->column < 1 ? 2 : owner->column;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        ++owner->column;
        if (owner->row == 0)
            owner->column = owner->column > 2 ? 0 : owner->column;
        else
            owner->column = owner->column > 2 ? 1 : owner->column;
    } else if (buttons & 0x40) {
        int id = D_00259CE0[owner->column + owner->row * 3].v[3];
        if (id && D_001A7AF8[id]) {
            func_002E5E58(4, 0, 0);
            D_001F2880[0] = id;
            owner->selected = id;
        } else
            func_002E5E58(5, 0, 0);
    }
    {
        int id = D_00259CE0[owner->column + owner->row * 3].v[3];
        owner->selected = id;
        if (id && D_001A7AF8[id])
            D_001ADB10 = ((SelectionMaterial *)(D_00239BA0 + D_00139568[id] * 0xE0))->material;
    }
}
