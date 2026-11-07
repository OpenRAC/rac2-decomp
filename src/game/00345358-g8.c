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

/* func_00348EC0: draws the list menu's rows centred on the screen. The row spacing is rounded with
   label_y after the row count is read; that block end is what gives retail's count, spacing and
   0.5 registers. Standalone declarations, the boot's addresses. */
#include "common.h"

extern int func_002A9588(int, int, int, int, int);
extern void func_00336320(char *);
extern int func_00335E10(char *);
extern int func_00335E20(char *);
extern float D_001AE5F0 __attribute__((sda));
extern float D_001B23A4[] MACRO_ADDR;
extern int D_001A7344[] MACRO_ADDR;
extern float D_001AE5D0 __attribute__((sda));
extern float D_001AE5D4[] MACRO_ADDR;
extern float D_001AE5D8 __attribute__((sda));
extern float D_001AE5E0 __attribute__((sda));
extern float D_001AE5E4[] MACRO_ADDR;
extern float D_001AE5E8 __attribute__((sda));

typedef struct { float x, y, w, h; } ListRect;
typedef struct {
    char pad[0x434];
    ListRect *origin;
    int unknown438;
    int selected;
    int enabled;
    int count;
    int showSpecial;
} ListMenu;
typedef struct { short pad[4]; short offset; short pad2; void (*call)(char *); } ListVtable;
typedef struct {
    ListRect *position;
    ListRect *scale;
    void *parameter08;
    unsigned int *colors;
    float *visibility;
    char lifetime[0x1C];
    ListVtable *table;
    void *metrics;
    unsigned long style;
    char *text;
    int alignment;
} ListSlot;

extern int D_001B23A0;

/* label_y, the HUD label idiom (the shared definition in src/levels/15_gorn/L15_00431590-g8.c, its
   mode word the boot's D_001B23A0). Its tests do not change the result: flow deletes their stores
   and jump2 their jumps, but only after allocation and both scheduling passes, which see the block
   they end. Here it rounds the list row spacing. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_00348EC0(char *o)
{
    int color = func_002A9588(0x20FFFEED, 0x70FFFEED, 20, 0, 0);
    int start, i, sp, h, n;
    float half, spf;
    ListMenu *menu = (ListMenu *)o;

    if (menu->enabled) {
        func_00336320(o);
        func_00336320(o + 0x130);
        func_00336320(o + 0x4C);
        func_00336320(o + 0x98);
        func_00336320(o + 0xE4);
        n = menu->count;
        half = (float)n * 0.5f;
        sp = label_y(o, D_001AE5F0, D_001B23A4[0], 0.5f, 1);
        spf = (float)sp;
        h = D_001A7344[0] >> 1;
        start = (int)((float)h - spf * half);
        for (i = 0; i < menu->count; i++) {
            ListRect *p;
            char *slot;
            ListVtable *v;
            int c;

            if (i == 7 && !menu->showSpecial)
                continue;
            p = (ListRect *)((float *)func_00335E10(o + 0x17C));
            p->x = D_001AE5D0 + menu->origin->x;
            p->y = (D_001AE5D4[0] + (float)i * D_001AE5D8) + (float)start;
            c = i == menu->selected ? color : 0x55F0C070;
            *((int *)func_00335E20(o + 0x1C8)) = c;
            func_00336320(o + 0x17C);
            p = (ListRect *)((float *)func_00335E10(o + 0x1C8));
            p->x = D_001AE5D0 + menu->origin->x;
            p->y = (D_001AE5D4[0] + (float)i * D_001AE5D8) + (float)start;
            func_00336320(o + 0x1C8);
            slot = (char *)&((ListSlot *)(o + 0x218))[i];
            p = (ListRect *)((float *)func_00335E10(slot));
            p->x = D_001AE5E0 + menu->origin->x;
            p->y = (D_001AE5E4[0] + (float)i * D_001AE5E8) + (float)start;
            v = *(ListVtable **)(o + i * 72 + 0x248);
            sp = v->offset;
            v->call(slot + sp);
        }
    }
}
