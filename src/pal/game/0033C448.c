#include "include_asm.h"
#include "names.h"

/* func_PAL_0033C448, the PAL copy of func_0033A520: the same C, where the
 * fields at 0x1F8-0x204 move to 0x208-0x214 and func_003369A8 becomes
 * func_PAL_00338688. */
typedef struct { float x, y, width, height; } TitlePosition;
extern void object_init_derived_c(void *, void *, void *);
extern void object_set_second_float4(void *, float, float, float, float);
extern int *object_get_fourth_field(void *);
extern void hud_init_widget_defaults_pal(void *, void *, void *);
extern int *ui_return_second_arg(int, int);
extern void *pool_alloc_cell(void *);
extern char g_circle_menu_icon_data[];
extern float g_hud_scale __attribute__((sda));
/* Sets up the title screen's icon sprite and its label text, placing the icon at a screen position scaled by the HUD scale. */
void title_screen_init_labels_pal(unsigned char *screen, void *owner)
{
    float value;
    TitlePosition *anchor;
    char *icon_data;

    *(int *)(screen + 0x208) = 0;
    *(void **)(screen + 0x210) = owner;
    if (owner != 0) {
        int *alloc = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(screen + 0x20C) = alloc;
        alloc[1] = 0;
        alloc[2] = 0;
        alloc[3] = 0;
        alloc[0] = 0;
    }
    do {
        float position;
        int y;
        anchor = *(TitlePosition **)(screen + 0x20C);
        anchor->x = 70.0f;
        position = 300.0f;
        y = (int)(g_hud_scale * position + 0.5f);
        value = y;
    } while (0);
    icon_data = g_circle_menu_icon_data;
    anchor = *(TitlePosition **)(screen + 0x20C);
    anchor->y = value;
    object_init_derived_c(screen + 0x134, icon_data, *(void **)(screen + 0x210));
    object_set_second_float4(screen + 0x134, 24.0f, 24.0f, 0.0f, 0.0f);
    *(int *)object_get_fourth_field(screen + 0x134) = 0x60F0F0B0;
    value = 65.0f;
    *(float *)(screen + 0x214) = value;
    hud_init_widget_defaults_pal(screen + 0x170, icon_data, *(void **)(screen + 0x210));
    *(int *)object_get_fourth_field(screen + 0x170) = 0x80F0F0F0;
    object_set_second_float4(screen + 0x170, 0.7f, 0.7f, 0.0f, 0.0f);
}
