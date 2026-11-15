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
extern unsigned char D_00211A10[], D_00210DA0[];
extern int g_current_map_index MACRO_ADDR;
extern unsigned char D_0019B2E8[], D_0019B4A8[];
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
extern SnapshotDF3F8 D_002119B0;
extern struct { char pad[0x64]; int word; unsigned char bytes[3]; } g_sound_state;
extern struct { char pad[0x48]; short count; } g_music_state;
extern int D_001C4F40;
extern unsigned char D_001B1640 MACRO_ADDR, D_001B1641 MACRO_ADDR, D_001B1642 MACRO_ADDR;
extern float D_001B1644 MACRO_ADDR, D_001B1648 MACRO_ADDR, D_001B164C MACRO_ADDR, D_001B1650 MACRO_ADDR;
extern void mem_copy_aligned(void *, void *, int);

/* Takes a snapshot of the map progress, two positions and several game values so they can be restored later. */
void level_capture_checkpoint_state(void *vecA, void *vecB) {
    unsigned char *dst;
    unsigned char *src;
    int i;
    int level;
    int offset;
    if (g_hero_state.mode == 4)
        return;
    mem_copy_aligned(D_00211A10, D_00210DA0, 0x404);
    level = g_current_map_index;
    offset = level * 16 - 2;
    dst = D_00211A10 + 0x404;
    src = D_00210DA0 + 0x404;
    for (i = 0; i < 0x7FF; i++, src++) {
        unsigned int value = *src;
        if ((unsigned char)value &&
            ((unsigned char)value == 1 ||
             (D_0019B2E8[(unsigned char)value + offset] & 0x80))) {
            unsigned char *p;
            *(unsigned char *)(i + (unsigned int)dst) = value;

            if (i & 1) {
                p = D_0019B4A8 + ((i >> 1) + level * 1024);
                if (((*p >> 4) & 7) != 7)
                    *p += 16;
            } else {
                p = D_0019B4A8 + ((i >> 1) + level * 1024);
                if ((*p & 7) != 7)
                    *p += 1;
            }
        }
    }
    D_002119B0.active = 1;
    qcopy_nc(D_002119B0.a, vecA);
    qcopy_nc(D_002119B0.b, vecB);
    {
        ObjectDF3F8 *obj = g_hero_state.object;
        D_002119B0.obj_a = obj->a;
        D_002119B0.obj_b = obj->b;
        D_002119B0.mode = g_hero_state.mode;
        D_002119B0.object = obj;
        D_002119B0.count = g_hero_state.count;
        D_002119B0.word = g_sound_state.word;
        D_002119B0.bytes[0] = g_sound_state.bytes[0];
        D_002119B0.bytes[1] = g_sound_state.bytes[1];
        D_002119B0.bytes[2] = g_sound_state.bytes[2];
        D_002119B0.other_count = g_music_state.count;
        D_002119B0.other_word = D_001C4F40;
        D_002119B0.bytes[3] = D_001B1640;
        D_002119B0.bytes[4] = D_001B1641;
        D_002119B0.bytes[5] = D_001B1642;
        D_002119B0.values[0] = D_001B1644;
        D_002119B0.values[1] = D_001B1648;
        D_002119B0.values[2] = D_001B164C;
        D_002119B0.values[3] = D_001B1650;
    }
}

