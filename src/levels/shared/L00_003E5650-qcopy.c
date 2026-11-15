#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;

extern int save_is_record_value(short id, int mode);
extern int math_fast_helper_a(Vec16_Fc936841d *v, float scale);
extern void blast_clear_state(void);
extern void moby_mark_spawned(char *object);
extern void blast_draw_ring_mesh_large(char *object);
extern void blast_draw_ring_mesh_small(char *object);
extern void blast_draw_screen_flash(char *object);
extern void blast_draw_shell_mesh(char *object);
extern void blast_draw_ripple_mesh(char *object);
extern void blast_finish_effect_records(char *object);

/* Draws the Mini-Nuke blast when it is close to the camera, or removes it if its data is gone. */
void mini_nuke_blast_draw(char *object)
{
    char *data;
    Vec16_Fc936841d local;
    int result;

    data = *(char **)(object + 0x68);
    if (save_is_record_value(*(short *)(object + 0xAA), *(int *)(data + 0x28)) == 0) {
        blast_clear_state();
        moby_mark_spawned(object);
        return;
    }
    *(TI128 *)&local = *(TI128 *)(object + 0x10);
    local.w = 2.0f;
    result = math_fast_helper_a(&local, 100.0f);
    if (result != -1) {
        if (*(unsigned char *)(object + 0x20) != 6) {
            blast_draw_ring_mesh_large(object);
            blast_draw_ring_mesh_small(object);
            blast_draw_screen_flash(object);
        }
        blast_draw_shell_mesh(object);
        blast_draw_ripple_mesh(object);
        blast_finish_effect_records(object);
    }
}
