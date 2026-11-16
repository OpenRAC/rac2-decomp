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

extern s32 g_current_game_mode;
extern s32 g_moby_marker_max_alpha __attribute__((sda));
extern DebugMarks g_hud_reticle_marks;

/* Adds a marker (for an object or a position) to the list of markers drawn this frame. */
void hud_add_moby_marker(void *moby, f32 scale, u32 color, void *pos, s32 type, f32 size, s32 arg, f32 angle, s32 unused) {
    DebugMark *mark;

    if (g_current_game_mode != 2 && g_hud_reticle_marks.count < 6) {
        mark = &g_hud_reticle_marks.e[g_hud_reticle_marks.count];
        mark->moby = moby;
        mark->scale = scale;
        mark->size = size;
        mark->color = color;
        mark->type = type;
        if (g_moby_marker_max_alpha < (s32)(color >> 24)) {
            mark->color = (color & 0xFFFFFF) | (g_moby_marker_max_alpha << 24);
        }
        if (pos != 0) {
            qcopy(mark->pos, pos);
            mark->hasPos = 1;
        } else {
            mark->hasPos = 0;
        }
        if (arg == -1) {
            switch (type) {
            case 13:
            case 31: case 32: case 33: case 34: case 35:
            case 36: case 37: case 38: case 39:
                mark->arg = 2;
                mark->angle = 1.5707965f;
                mark->mode = 0;
                break;
            }
        } else {
            mark->mode = 4;
            mark->angle = angle;
            mark->arg = arg;
        }
        g_hud_reticle_marks.count++;
    }
}
