#include "include_asm.h"
#include "names.h"

/* The threshold lives in small data, so this file is built with -G8. It differs
   from program to program, so it carries no level. */
extern float ref_L00_00327D08_00 __attribute__((sda));
extern void gfx_append_vu1_preset_c(void);
extern void gfx_draw_distortion_ring(char *);

/* Runs the shared update, then advances the object's sub-record while its
   stored float is still below the small-data threshold. */
void ring_update_if_below_threshold(char *a0)
{
    float value;

    gfx_append_vu1_preset_c();
    value = *(float *)(*(char **)(a0 + 0x68) + 0x24);
    if (value < ref_L00_00327D08_00)
        gfx_draw_distortion_ring(a0);
}

extern int g_game_time;
extern char *g_moby_list_head;
extern float ref_L00_00327A60_00 __attribute__((sda));
extern float fast_vec_dist(void *, void *);
extern int pickup_start_fly_if_idle(void *, void *);

/* The camera block the level keeps, with the fields this body writes. */
typedef struct {
    unsigned char pad_000[0x218];
    int field_218;
    float field_21C;
    unsigned char pad_220[8];
    float field_228;
    float field_22C;
    int field_230;
    int field_234;
    int field_238;
} Ref_L00_0032E4F0_Block;

extern Ref_L00_0032E4F0_Block ref_L00_0032E4F0_00;
extern float g_cam_zoom_scale __attribute__((sda));
extern int g_cam_zoom_effect_source __attribute__((sda));
extern int g_cam_zoom_effect_target __attribute__((sda));
extern float ref_L00_0032E4F0_04;
extern void UpdateViewContext(void);

/* Scales the resident zoom value by the argument's size, keeps it in the
   camera block and hands the block to the shared update. */
void cam_set_zoom_effect(float size)
{
    Ref_L00_0032E4F0_Block *block = &ref_L00_0032E4F0_00;
    float zoom = size * (g_cam_zoom_scale * 1024.0f);

    g_cam_zoom_effect_target = g_cam_zoom_effect_source;
    block->field_228 = 255.0f;
    block->field_22C = 100.0f;
    block->field_21C = zoom;
    ref_L00_0032E4F0_04 = size;
    block->field_218 = 0;
    block->field_230 = 0xFF;
    block->field_234 = 0xFF;
    block->field_238 = 0xFF;
    UpdateViewContext();
}

/* Looks through the live objects and reacts to each one of a certain kind that is close to this object. */
void moby_notify_nearby_of_kind(char *object)
{
    char *cursor;
    if (g_game_time & 1) {
        cursor = g_moby_list_head;
        while (cursor) {
            int kind = *(unsigned char *)(cursor + 0x20);
            if (kind == 0xfe) return;
            if (kind == 0xfd) return;
            if (cursor && *(char **)(cursor + 0x24) &&
                *(short *)(*(char **)(cursor + 0x24) + 0x46) == 0x13) {
                if (fast_vec_dist(cursor + 0x10, object + 0x10) < ref_L00_00327A60_00)
                    pickup_start_fly_if_idle(cursor, object);
            }
            cursor = *(char **)(cursor + 0x28);
        }
    }
}
