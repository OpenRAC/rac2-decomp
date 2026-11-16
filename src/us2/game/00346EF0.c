#include "include_asm.h"
#include "names.h"





extern void Fd1c2476b_FUN_00336320(char *p);
extern void Fd1c2476b_FUN_00336A78(char *p);
extern void Fd1c2476b_FUN_003462A8(char *p);
extern void Fd1c2476b_FUN_003463C8(char *p);
extern void Fd1c2476b_FUN_003464D0(char *p);

/* func_00345F70 is built from 00345358-layout-g8.c. */

/* func_003462A8 is built from 00345358-descriptor-g8.c for small-data access. */

/* func_003463C8 and func_003464D0 are built from 00345358-g8.c for small-data access. */


/* Draws the large menu screen: its parts and three item grid pages, when it is active (USA v2.00 copy). */
void menu_screen_large_draw_parts_us2(char *menu)
{
    if (*(int *)(menu + 1272) == 0)
        return;
    Fd1c2476b_FUN_00336320(menu);
    Fd1c2476b_FUN_00336320(menu + 76);
    Fd1c2476b_FUN_00336320(menu + 152);
    Fd1c2476b_FUN_00336320(menu + 228);
    Fd1c2476b_FUN_00336A78(menu + 456);
    Fd1c2476b_FUN_003462A8(menu);
    Fd1c2476b_FUN_003463C8(menu);
    Fd1c2476b_FUN_003464D0(menu);
    Fd1c2476b_FUN_00336320(menu + 380);
    Fd1c2476b_FUN_00336A78(menu + 784);
    Fd1c2476b_FUN_00336A78(menu + 696);
    Fd1c2476b_FUN_00336A78(menu + 872);
    Fd1c2476b_FUN_00336A78(menu + 960);
    Fd1c2476b_FUN_00336A78(menu + 1048);
}


extern void *F449e2f67_FUN_003361A8(char *p);
extern char *F449e2f67_FUN_00336968(char *p);
extern void *F449e2f67_FUN_003366D0(char *p);
extern void *object_construct_derived_b(char *p);
extern char *hud_construct_widget_base(char *p);
extern void *object_construct_derived_c(char *p);

extern void *object_construct_derived_a(char *p);

/* Constructs the parts of the large menu screen (USA v2.00 copy). */
char *menu_screen_large_init_parts_us2(char *menu)
{
    object_construct_derived_a(menu);
    object_construct_derived_a(menu + 76);
    object_construct_derived_a(menu + 152);
    object_construct_derived_a(menu + 228);
    object_construct_derived_a(menu + 304);
    object_construct_derived_a(menu + 380);
    object_construct_derived_b(menu + 456);
    hud_construct_widget_base(menu + 528);
    hud_construct_widget_base(menu + 616);
    hud_construct_widget_base(menu + 704);
    object_construct_derived_c(menu + 792);
    object_construct_derived_a(menu + 852);
    object_construct_derived_a(menu + 928);
    object_construct_derived_a(menu + 1004);
    return menu;
}






