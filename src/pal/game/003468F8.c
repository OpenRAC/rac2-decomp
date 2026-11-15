#include "include_asm.h"
#include "names.h"







extern void F6402b823_FUN_00336320(char *a);
extern void F6402b823_FUN_00336A78(char *a);
extern void F6402b823_FUN_00335E68(char *a, int b);
extern void F6402b823_FUN_00345268(char *a);
extern void F6402b823_FUN_00345088(char *a);
extern void F6402b823_FUN_00344F98(char *a);
extern void F6402b823_FUN_00345178(char *a);
extern void F6402b823_FUN_00344938(char *a);

void func_PAL_00347438(char *obj)
{
    if (*(int *)(obj + 1192) != 0) {
        char *s0 = obj + 456;

        F6402b823_FUN_00336320(obj);
        F6402b823_FUN_00336320(obj + 76);
        F6402b823_FUN_00336320(obj + 152);
        F6402b823_FUN_00336320(obj + 228);
        F6402b823_FUN_00336A78(s0);
        F6402b823_FUN_00336A78(obj + 696);
        F6402b823_FUN_00336A78(s0);
        F6402b823_FUN_00335E68(obj + 544, 0);
        F6402b823_FUN_00345268(obj);
        F6402b823_FUN_00345088(obj);
        F6402b823_FUN_00344F98(obj);
        F6402b823_FUN_00345178(obj);
        F6402b823_FUN_00344938(obj);
        F6402b823_FUN_00336320(obj + 380);
    }
}


extern void F449e2f67_FUN_003361A8(char *p);
extern void F449e2f67_FUN_00336968(char *p);
extern void F449e2f67_FUN_003366D0(char *p);

char *func_PAL_003474E0(char *p)
{
    F449e2f67_FUN_003361A8(p);
    F449e2f67_FUN_003361A8(p + 76);
    F449e2f67_FUN_003361A8(p + 152);
    F449e2f67_FUN_003361A8(p + 228);
    F449e2f67_FUN_003361A8(p + 304);
    F449e2f67_FUN_003361A8(p + 380);
    F449e2f67_FUN_00336968(p + 456);
    F449e2f67_FUN_00336968(p + 544);
    F449e2f67_FUN_003366D0(p + 632);
    F449e2f67_FUN_00336968(p + 696);
    F449e2f67_FUN_00336968(p + 784);
    F449e2f67_FUN_00336968(p + 872);
    F449e2f67_FUN_00336968(p + 960);
    F449e2f67_FUN_00336968(p + 1048);
    return p;
}


/* func_PAL_00347570, the PAL copy of func_00345490: the same C with the fields moved
 * and the text ids renumbered, plus the func_00336A30 calls, the two stores at 0x220 + 0x48 and the
 * 0.8 scale on the items at 0x310 and 0x2b8. */
extern int pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void func_PAL_00338688(void *, void *, void *);
extern void object_init_derived_c(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void object_set_flag_value(void *, int);
extern void object_set_second_float4(void *, float, float, float, float);
extern void hud_set_widget_field_b(void *, void *);
extern void hud_set_widget_field_a(void *, int);
extern void *GetLocalizedString(int);
extern void func_PAL_003480C8(void *, int, void *);
extern char *D_001A8CFC[] __attribute__((sda));
extern char D_001ADC10[];
extern char D_001ADC18[];
extern char D_001ADC20[];
extern char D_001ADC28[];
extern char D_001ADFC0[];
extern char D_001ADFC8[];
extern char D_001ADD68[];
extern char D_001ADD60[];
extern char D_001AE3C8[];
extern char D_001AE3D8[];
extern char D_001AE3E8[];
extern char D_001ADD58[];
extern char D_001AE030[];
extern char D_001ADFD8[];

void func_PAL_00347570(char *self, void *owner)
{
    int scratch;
    *(void **)(self + 0x474) = owner;
    if (owner) {
        int *p = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(self + 0x470) = p;
        p[1] = 0; p[2] = 0; p[3] = 0; p[0] = 0;
    }
    *(int *)(self + 0x4f8) = 1;
    (*(float **)(self + 0x470))[0] = 250.0f;
    (*(float **)(self + 0x470))[1] = 207.0f;
    object_init_derived_arrays(self + 0x0, D_001ADC10, owner);
    object_init_derived_arrays(self + 0x4c, D_001ADC18, owner);
    object_init_derived_arrays(self + 0x98, D_001ADC20, owner);
    object_init_derived_arrays(self + 0xe4, D_001ADC28, owner);
    object_init_derived_arrays(self + 0x130, D_001ADFC0, owner);
    object_init_derived_arrays(self + 0x17c, D_001ADFC8, owner);
    func_PAL_00338688(self + 0x2b8, D_001ADD68, owner);
    func_PAL_00338688(self + 0x310, D_001ADD60, owner);
    func_PAL_00338688(self + 0x368, D_001AE3C8, owner);
    func_PAL_00338688(self + 0x3c0, D_001AE3D8, owner);
    func_PAL_00338688(self + 0x418, D_001AE3E8, owner);
    func_PAL_00338688(self + 0x1c8, D_001ADD58, owner);
    func_PAL_00338688(self + 0x220, D_001AE030, owner);
    *object_get_fourth_field(self + 0x0) = 0x60442d00;
    *object_get_fourth_field(self + 0x98) = 0x55f0c070;
    *object_get_fourth_field(self + 0xe4) = 0x55f0c070;
    *object_get_fourth_field(self + 0x130) = 0x55f0c070;
    *object_get_fourth_field(self + 0x17c) = 0x70fffeed;
    *object_get_fourth_field(self + 0x4c) = 0x60241700;
    *object_get_fourth_field(self + 0x310) = 0x80f0f0f0;
    *object_get_fourth_field(self + 0x2b8) = 0x80f0f0f0;
    *object_get_fourth_field(self + 0x368) = 0x80f0f0f0;
    *object_get_fourth_field(self + 0x3c0) = 0x80f0f0f0;
    *object_get_fourth_field(self + 0x418) = 0x80f0f0f0;
    object_set_helper_result(self + 0x0, D_001A8CFC[0] + 0x8710, 0x59);
    object_set_helper_result(self + 0x98, D_001A8CFC[0] + 0x8710, 0x5b);
    object_set_helper_result(self + 0xe4, D_001A8CFC[0] + 0x8710, 0x5c);
    object_set_helper_result(self + 0x130, D_001A8CFC[0] + 0x8710, 0x5d);
    object_set_helper_result(self + 0x17c, D_001A8CFC[0] + 0x8710, 0x5e);
    object_set_helper_result(self + 0x4c, D_001A8CFC[0] + 0x8710, 0x5a);
    object_set_flag_value(self + 0x17c, 0);
    *(int *)(self + 0x4fc) = 0;
    *(int *)(self + 0x500) = 0;
    *(int *)(self + 0x508) = 0;
    object_init_derived_c(self + 0x278, D_001ADFD8, owner);
    *object_get_fourth_field(self + 0x278) = 0x60f0f0b0;
    object_set_second_float4(self + 0x278, 32.0f, 32.0f, 0.0f, 0.0f);
    *object_get_fourth_field(self + 0x1c8) = 0x80f0f0f0;
    *object_get_fourth_field(self + 0x220) = 0x80f0f0f0;
    hud_set_widget_field_b(self + 0x1c8, GetLocalizedString(0xb63));
    self[0x4b8] = 0;
    hud_set_widget_field_b(self + 0x220, self + 0x4b8);
    *(int *)(self + 0x504) = 0;
    hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xb60));
    hud_set_widget_field_b(self + 0x2b8, GetLocalizedString(0xb6c));
    hud_set_widget_field_a(self + 0x310, 0);
    hud_set_widget_field_a(self + 0x2b8, 2);
    {
        char *label = self + 0x220;
        *(int *)(label + 0x48) = 1;
        *(int *)(label + 0x4c) = 0x78;
    }
    object_set_second_float4(self + 0x310, 0.8f, 0.8f, 0.0f, 0.0f);
    object_set_second_float4(self + 0x2b8, 0.8f, 0.8f, 0.0f, 0.0f);
    hud_set_widget_field_b(self + 0x368, GetLocalizedString(0xb68));
    hud_set_widget_field_b(self + 0x3c0, GetLocalizedString(0xb69));
    hud_set_widget_field_b(self + 0x418, GetLocalizedString(0xb6b));
    func_PAL_003480C8(self, 0, &scratch);
}
