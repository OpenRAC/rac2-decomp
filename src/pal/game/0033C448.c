#include "include_asm.h"
#include "names.h"

/* func_PAL_0033C448, the PAL copy of func_0033A520: the same C, where the
 * fields at 0x1F8-0x204 move to 0x208-0x214 and func_003369A8 becomes
 * func_PAL_00338688. */
typedef struct { float x, y, width, height; } TitlePosition;
extern void object_init_derived_c(void *, void *, void *);
extern void object_set_second_float4(void *, float, float, float, float);
extern int *object_get_fourth_field(void *);
extern void func_PAL_00338688(void *, void *, void *);
extern int *ui_return_second_arg(int, int);
extern void *pool_alloc_cell(void *);
extern char g_circle_menu_icon_data[];
extern float g_hud_scale __attribute__((sda));
void title_screen_init_labels_pal(unsigned char *obj, void *arg)
{
    float v;
    TitlePosition *p;
    char *text;

    *(int *)(obj + 0x208) = 0;
    *(void **)(obj + 0x210) = arg;
    if (arg != 0) {
        int *alloc = ui_return_second_arg(16, pool_alloc_cell(arg));
        *(int **)(obj + 0x20C) = alloc;
        alloc[1] = 0;
        alloc[2] = 0;
        alloc[3] = 0;
        alloc[0] = 0;
    }
    do {
        float position;
        int y;
        p = *(TitlePosition **)(obj + 0x20C);
        p->x = 70.0f;
        position = 300.0f;
        y = (int)(g_hud_scale * position + 0.5f);
        v = y;
    } while (0);
    text = g_circle_menu_icon_data;
    p = *(TitlePosition **)(obj + 0x20C);
    p->y = v;
    object_init_derived_c(obj + 0x134, text, *(void **)(obj + 0x210));
    object_set_second_float4(obj + 0x134, 24.0f, 24.0f, 0.0f, 0.0f);
    *(int *)object_get_fourth_field(obj + 0x134) = 0x60F0F0B0;
    v = 65.0f;
    *(float *)(obj + 0x214) = v;
    func_PAL_00338688(obj + 0x170, text, *(void **)(obj + 0x210));
    *(int *)object_get_fourth_field(obj + 0x170) = 0x80F0F0F0;
    object_set_second_float4(obj + 0x170, 0.7f, 0.7f, 0.0f, 0.0f);
}
