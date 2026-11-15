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


void func_US2_00347550(char *a0)
{
    if (*(int *)(a0 + 1272) == 0)
        return;
    Fd1c2476b_FUN_00336320(a0);
    Fd1c2476b_FUN_00336320(a0 + 76);
    Fd1c2476b_FUN_00336320(a0 + 152);
    Fd1c2476b_FUN_00336320(a0 + 228);
    Fd1c2476b_FUN_00336A78(a0 + 456);
    Fd1c2476b_FUN_003462A8(a0);
    Fd1c2476b_FUN_003463C8(a0);
    Fd1c2476b_FUN_003464D0(a0);
    Fd1c2476b_FUN_00336320(a0 + 380);
    Fd1c2476b_FUN_00336A78(a0 + 784);
    Fd1c2476b_FUN_00336A78(a0 + 696);
    Fd1c2476b_FUN_00336A78(a0 + 872);
    Fd1c2476b_FUN_00336A78(a0 + 960);
    Fd1c2476b_FUN_00336A78(a0 + 1048);
}


extern void F449e2f67_FUN_003361A8(char *p);
extern void F449e2f67_FUN_00336968(char *p);
extern void F449e2f67_FUN_003366D0(char *p);
extern void object_construct_derived_b(char *p);
extern void hud_construct_widget_base(char *p);
extern void object_construct_derived_c(char *p);

extern void object_construct_derived_a(char *p);

char *func_US2_003475F0(char *p)
{
    object_construct_derived_a(p);
    object_construct_derived_a(p + 76);
    object_construct_derived_a(p + 152);
    object_construct_derived_a(p + 228);
    object_construct_derived_a(p + 304);
    object_construct_derived_a(p + 380);
    object_construct_derived_b(p + 456);
    hud_construct_widget_base(p + 528);
    hud_construct_widget_base(p + 616);
    hud_construct_widget_base(p + 704);
    object_construct_derived_c(p + 792);
    object_construct_derived_a(p + 852);
    object_construct_derived_a(p + 928);
    object_construct_derived_a(p + 1004);
    return p;
}






