#include "include_asm.h"
#include "names.h"

extern unsigned char *level_get_slot_body(int id, int index);
extern void table_clear_entry_flag(int index);
extern void moby_mark_spawned(void *object);
extern int *level_get_slot_header(int id, int index);
extern float math_random_float_range(float a, float b);
extern int FloatToInt(float value);
extern void DrawTwoLayerPolylineRibbon(int a0, int a1, int a2, int a3, int a4, int a5,
                              float f12, float f13, float f14);
extern void rocket_draw_ribbon_strip(void *self, int flags, int mode);
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_weapon_l00_table[];
typedef struct {
    unsigned char pad000[4];
    unsigned char flag;
} Entry262570;
extern float math_random_float_range(float a, float b);
extern int FloatToInt(float a);

/* Looks the object's record up in the level's table (the resident byte at D_00139568 + 0x16
   is the record's number), asks the level's builder for a matrix with the flags the object's
   own word selects, then reads the record's two colour bytes and hands the level's renderer
   the object's record. */
void rocket_draw_trail_pal(void *moby)
{
    unsigned char *self = moby;
    unsigned char *rec;
    int handle;
    int flags;
    int mode;
    int base;
    float scale;
    unsigned int c1;
    unsigned int c2;

    rec = *(unsigned char **)(self + 0x68);
    handle = level_get_slot_body(*(int *)(rec + 0x50), *(int *)(rec + 0x3C));
    if (handle == 0) {
        table_clear_entry_flag(*(int *)(rec + 0x6C));
        moby_mark_spawned(self);
    } else {
        if (((Entry262570 *)(g_weapon_l00_table + g_item_slot_to_record[0x16] * 224))->flag != 0) {
            flags = 0x802080;
            if (*(int *)(rec + 0x68) != 0)
                flags = 0x802020;
            mode = 0x7F;
        } else {
            flags = 0x202080;
            mode = 0x50;
        }
        rocket_draw_ribbon_strip(self, flags, mode);
        if (((Entry262570 *)(g_weapon_l00_table + g_item_slot_to_record[0x16] * 224))->flag == 0)
            return;
        base = handle + level_get_slot_header(*(int *)(rec + 0x50), *(int *)(rec + 0x3C))[2];
        scale = math_random_float_range(0.5f, 1.0f);
        c1 = (unsigned int)FloatToInt(scale * 127.0f) << 24;
        c2 = (unsigned int)FloatToInt(scale * 48.0f) << 24;
        DrawTwoLayerPolylineRibbon(*(int *)((char *)base + *(int *)(rec + 0x30) * 4),
                          0x17, 0xE, 0x7,
                          0xFF5050 | c1, 0xFF1010 | c2,
                          0.0f, 3.0f, 0.0f);
    }
}

