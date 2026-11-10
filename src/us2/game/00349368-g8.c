#include "common.h"

/* func_US2_00349C00, the v2.00 copy of func_00348EC0 (src/game/00345358-g8.c): the same C, where the
   menu's fields lie 0x70 bytes further in and each label slot is 88 bytes, not 72.
   func_00348EC0 draws the list menu's rows centred on the screen. The row spacing is rounded with
   label_y after the row count is read; that block end is what gives retail's count, spacing and
   0.5 registers. Standalone declarations, the boot's addresses. */

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
    char pad[0x4A4];
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
    char reserved48[0x10];
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

void func_US2_00349C00(char *o)
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
            v = *(ListVtable **)(o + i * 88 + 0x248);
            sp = v->offset;
            v->call(slot + sp);
        }
    }
}
