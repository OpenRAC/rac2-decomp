#include "include_asm.h"
#include "names.h"

extern void *prompt_bar_destroy_pal(void *);
extern void *object_construct_derived_a(void *);

void *func_PAL_0033B520(char *object) {
    prompt_bar_destroy_pal(object + 0x8);
    object_construct_derived_a(object + 0x2D8);
    return object;
}

extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts_pal(void *, void *, void *, void *);
extern void prompt_bar_set_spacing_pal(void *, float);

/* looks up three objects by numeric id, runs a four-argument routine and a (pointer,float) routine on a sub-object at self+8, then stores 1 at self+764 */
void popup_init_texts_shown_pal(int *self)
{
    void *a;
    void *b;
    void *c;
    void *sub = (void *)(self + 2);

    a = GetLocalizedString(2990);
    b = GetLocalizedString(2989);
    c = GetLocalizedString(2912);

    prompt_bar_set_texts_pal(sub, a, b, c);
    prompt_bar_set_spacing_pal(sub, 0.0f);

    self[203] = 1;
}

extern int g_menu_prompt_flag_a __attribute__((sda));
extern int g_menu_prompt_flag_b __attribute__((sda));
extern void prompt_bar_set_extras_enabled_pal(int *p, int flag);
extern void prompt_bar_draw_pal(int *p);
extern void gfx_draw_screen_element_stored(int *p);

/* Lazily initialises a sub-object of the argument behind two global flags and a field, runs one guarded setup step on it, then hands it to two callees. */
void menu_draw_with_prompts_pal(int *obj)
{
    if (g_menu_prompt_flag_a != 0 || g_menu_prompt_flag_b != 0 || obj[204] != 0)
        prompt_bar_set_extras_enabled_pal(obj + 2, 0);
    if (obj[203] == 1)
        prompt_bar_set_extras_enabled_pal(obj + 2, 1);
    prompt_bar_draw_pal(obj + 2);
    gfx_draw_screen_element_stored(obj + 182);
}
