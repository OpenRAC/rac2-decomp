#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pos[16];
    f32 scale;
    u32 color;
    s32 type;
    f32 size;
    void *moby;
    s16 hasPos;
    s16 mode;
    f32 angle;
    s32 arg;
} DebugMark;

typedef struct {
    DebugMark e[6];
    s32 count;
} DebugMarks;

extern s32 D_001A8BB0;
extern s32 D_001A8630 __attribute__((sda));
extern DebugMarks D_001B7600;

/* Queues a debug mark for a moby (up to six per frame) with its scale, colour, type and size. */
void func_00273318(void *moby, f32 scale, u32 color, void *pos, s32 type, f32 size, s32 arg, f32 angle, s32 unused) {
    DebugMark *e;

    if (D_001A8BB0 != 2 && D_001B7600.count < 6) {
        e = &D_001B7600.e[D_001B7600.count];
        e->moby = moby;
        e->scale = scale;
        e->size = size;
        e->color = color;
        e->type = type;
        if (D_001A8630 < (s32)(color >> 24)) {
            e->color = (color & 0xFFFFFF) | (D_001A8630 << 24);
        }
        if (pos != 0) {
            qcopy(e->pos, pos);
            e->hasPos = 1;
        } else {
            e->hasPos = 0;
        }
        if (arg == -1) {
            switch (type) {
            case 13:
            case 31: case 32: case 33: case 34: case 35:
            case 36: case 37: case 38: case 39:
                e->arg = 2;
                e->angle = 1.5707965f;
                e->mode = 0;
                break;
            }
        } else {
            e->mode = 4;
            e->angle = angle;
            e->arg = arg;
        }
        D_001B7600.count++;
    }
}
