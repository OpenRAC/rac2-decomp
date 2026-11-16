#include "common.h"

/* Only the fields copied into the saved state are described here. */
typedef struct {
    char pad[0x38];
    int a, b;
} ObjectDF3F8;
typedef struct {
    char pad[0x2290];
    ObjectDF3F8 *object;          /* 0x2290 */
    char pad2[0x20];
    unsigned char mode;          /* 0x22B4 */
    char pad3[0x23D];
    short count;                 /* 0x24F2 */
} StateDF3F8;
extern StateDF3F8 g_hero_state;
extern unsigned char g_checkpoint_state_buffer_a[], g_checkpoint_state_buffer_b[];
extern int g_current_map_index MACRO_ADDR;
extern unsigned char g_moby_group_flags[], g_moby_nibble_table[];
typedef struct {
    int active;
    char pad[12];
    float a[4], b[4];             /* 0x10, 0x20 */
    int obj_a, obj_b, word;       /* 0x30 */
    unsigned char bytes[6];      /* 0x3C */
    char pad2[2];
    float values[4];             /* 0x44 */
    int mode;                    /* 0x54 */
    ObjectDF3F8 *object;          /* 0x58 */
    int count;                   /* 0x5C */
    char pad3[0xC04];
    int other_count, other_word;  /* 0xC64 */
} SnapshotDF3F8;
extern SnapshotDF3F8 g_bolt_collection_checkpoint;
extern struct { char pad[0x64]; int word; unsigned char bytes[3]; } g_sound_state;
extern struct { char pad[0x48]; short count; } g_music_state;
extern int g_map_mode;
extern unsigned char g_fog_color MACRO_ADDR, g_fog_color_green MACRO_ADDR, g_fog_color_blue MACRO_ADDR;
extern float g_checkpoint_float_a MACRO_ADDR, g_checkpoint_float_b MACRO_ADDR, g_checkpoint_float_c MACRO_ADDR, g_checkpoint_float_d MACRO_ADDR;
extern void mem_copy_aligned(void *, void *, int);

/* Takes a snapshot of the map progress, two positions and several game values so they can be restored later. */
void level_capture_checkpoint_state(void *vec_a, void *vec_b) {
    unsigned char *dst;
    unsigned char *src;
    int i;
    int level;
    int offset;
    if (g_hero_state.mode == 4)
        return;
    mem_copy_aligned(g_checkpoint_state_buffer_a, g_checkpoint_state_buffer_b, 0x404);
    level = g_current_map_index;
    offset = level * 16 - 2;
    dst = g_checkpoint_state_buffer_a + 0x404;
    src = g_checkpoint_state_buffer_b + 0x404;
    for (i = 0; i < 0x7FF; i++, src++) {
        unsigned int value = *src;
        if ((unsigned char)value &&
            ((unsigned char)value == 1 ||
             (g_moby_group_flags[(unsigned char)value + offset] & 0x80))) {
            unsigned char *p;
            *(unsigned char *)(i + (unsigned int)dst) = value;

            if (i & 1) {
                p = g_moby_nibble_table + ((i >> 1) + level * 1024);
                if (((*p >> 4) & 7) != 7)
                    *p += 16;
            } else {
                p = g_moby_nibble_table + ((i >> 1) + level * 1024);
                if ((*p & 7) != 7)
                    *p += 1;
            }
        }
    }
    g_bolt_collection_checkpoint.active = 1;
    qcopy_nc(g_bolt_collection_checkpoint.a, vec_a);
    qcopy_nc(g_bolt_collection_checkpoint.b, vec_b);
    {
        ObjectDF3F8 *obj = g_hero_state.object;
        g_bolt_collection_checkpoint.obj_a = obj->a;
        g_bolt_collection_checkpoint.obj_b = obj->b;
        g_bolt_collection_checkpoint.mode = g_hero_state.mode;
        g_bolt_collection_checkpoint.object = obj;
        g_bolt_collection_checkpoint.count = g_hero_state.count;
        g_bolt_collection_checkpoint.word = g_sound_state.word;
        g_bolt_collection_checkpoint.bytes[0] = g_sound_state.bytes[0];
        g_bolt_collection_checkpoint.bytes[1] = g_sound_state.bytes[1];
        g_bolt_collection_checkpoint.bytes[2] = g_sound_state.bytes[2];
        g_bolt_collection_checkpoint.other_count = g_music_state.count;
        g_bolt_collection_checkpoint.other_word = g_map_mode;
        g_bolt_collection_checkpoint.bytes[3] = g_fog_color;
        g_bolt_collection_checkpoint.bytes[4] = g_fog_color_green;
        g_bolt_collection_checkpoint.bytes[5] = g_fog_color_blue;
        g_bolt_collection_checkpoint.values[0] = g_checkpoint_float_a;
        g_bolt_collection_checkpoint.values[1] = g_checkpoint_float_b;
        g_bolt_collection_checkpoint.values[2] = g_checkpoint_float_c;
        g_bolt_collection_checkpoint.values[3] = g_checkpoint_float_d;
    }
}

